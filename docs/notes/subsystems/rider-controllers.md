# Rider controllers: attacks, handplants, crashes and resets

Each rider is driven by two small state machines held in its motion owner: a *control* (what the rider is
trying to do: cruise, board press, air, rail, handplant, crash, reset, ...) and a *motion* (how the body is
integrated: ground, air, wipeout, reset, rail, handplant). This note covers the dispatch tables and the
request/exit mechanics that switch them, and the special controllers built on top of them: the upper-body
attacks, the board press, the handplant, the hard crash with its ragdoll-style wipeout motion and recovery,
the forced reset after a fall, and the snow spray the board-wake effect produces during a crash.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a
PS2 emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

Translation units per the current splits (several key functions are still in `asm` catch-all segments):

- `src/ai/ai.cpp`: the per-tick rider update `0x00128AF0`, most controllers (cruise `0x00131620`, board press
  `0x0012FC60`.., natural air `0x0012F730`, air/spin `0x00133308`, rail `0x00131D30`, handplant control
  `0x001328B0`.., crash control helpers `0x0012CB68`/`0x0012D160`/`0x0012D4E8`, reset control `0x0012F230`/`0x0012F398`).
- `src/ai/motion/wipeoutmotion.cpp`: motion 2 (wipeout), from `0x00136C40` (`cWipeoutMotion_gainFocus`) to the
  crash contact probe `0x00138960`.
- `src/ai/control/handplantcontrol.cpp`: motion 5 (`0x00138B48` `cHandplantMotion_gainFocus` and neighbours).
  The same TU range currently also covers the air-motion enter `0x001399E0`, the landing routine `0x00139C88`,
  rail motion 4 and ground motion 0 (`0x0013C7A8`, `0x0013F410`), and the animation marker helpers
  `0x00144670`/`0x001446A0`/`0x001446B8`.
- `src/ai/rider.cpp`: control/motion getters and request wrappers (`0x0011FE78`..`0x0011FEE8`), triplet approach
  `0x001211F8`, reset placement `0x0011D660`, `0x0011E098` (`cRider_updateOrientationImplicit`),
  `0x0011FA10` (`cRider_doLeanPoseAdjust`).
- `src/ai/computer.cpp`: control/motion dispatchers `0x001112B8`/`0x00111538`, hard-crash entry `0x0010EB30`,
  crash-snow impact wrapper `0x00111AA0`, reset route selection `0x00112D58`.
- `src/ai/ridermetrix.cpp`: scoring hooks for board press, handplant, crash and reset.
- `src/visualfx/boardwakefx.cpp`: the board-wake effect's crash snow (`0x002DF920`, `0x002E2260`, `0x002E23E0`).
- `asm/14B10.s` (unsplit): attacks `0x001163B0`, board-press entry `0x001161D0`, jump request `0x001162C8`,
  forced reset `0x00116120`, and other controller helpers.
- `asm/1218.s` (unsplit): handplant entry test `0x00107578`, rail attach `0x00106848`, collision reaction
  `0x00105D98`, soft reaction `0x00108388`, board-press animation kinds.

## Control and motion dispatch

### Motion owner

The motion owner is the object pointed to by `rider+0x77C`. Fields used here:

| Owner offset | Meaning |
|---|---|
| `+0xB0` | rail motion state (motion 4) |
| `+0x1D0` | board-press control state (control 1), see below |
| `+0x210` | natural-air control state (control 4): `+0` entry angle, `+4` entry magnitude, `+8` upper-action latch, `+0xC` identity latch, `+0x10` signed last identity, `+0x14` rider back-link |
| `+0x2B0` | rail control state (control 7) |
| `+0x350` | set by the forced reset: whether the reset reason was > 0 |
| `+0xB40` | the board-wake effect object (crash snow) |
| `+0xDE0` | current motion id |
| `+0xDE4` | current control id |

Getters: `0x0011FE98` returns the motion id, `0x0011FEE8` the control id. Requests: `0x0011FE78(rider, motion)`
and `0x0011FEC8(rider, control)`, which forward to `0x001112B8` and `0x00111538`.

### Dispatch tables

Controls use three tables indexed by `+0xDE4`: update `0x00456C10`, enter `0x00456BD0`, exit `0x00456B90`.
Motions use four tables indexed by `+0xDE0`: exit `0x00456B10`, enter `0x00456B30`, update `0x00456B50`,
post `0x00456B70` (post runs every tick after the pose).

| Control | Role | Enter | Update | Exit |
|---|---|---|---|---|
| 0 | cruise (riding on the ground) | `0x00131608` | `0x00131620` | `0x00131C30` |
| 1 | board press | `0x0012FC60` | `0x0012FC80` | `0x0012FE98` |
| 2 | jump charge (semantic 245) | | | `0x0012E9B0` |
| 3 | soft collision | | | none |
| 4 | natural (passive) air | `0x0012F620` | `0x0012F730` | `0x0012FB68` |
| 5 | air control / spin | | `0x00133308` | `0x00134CB0` (air-spin bake) |
| 6 | not described in these notes | | | none |
| 7 | rail | `0x00131D08` | `0x00131D30` | `0x00132048` |
| 8 | crash | | | `0x0012E690` |
| 9 | forced reset | `0x0012F230` | `0x0012F398` | none |
| 10 | race finish (`0x0012C678` belongs to it; slot not stated) | | | none |
| 11 | handplant | `0x001328B0` | `0x00132A30` | `0x00132F98` |
| 12 | rail über trick | | | none |
| 13 | transition placeholder, no handlers | none | none | none |

Blank cells are not given in these notes.

| Motion | Role | Enter | Update | Post | Exit |
|---|---|---|---|---|---|
| 0 | ground | `0x0013C7A8` | | | `0x0013F410` |
| 1 | air | `0x001399E0` | | | `0x00139A18` (empty) |
| 2 | wipeout (crash) | `0x00136C40` (`cWipeoutMotion_gainFocus`) | | | `0x00136F28` |
| 3 | reset | | `0x00136958` | `0x00136978` (no-op) (unconfirmed which slot) | none |
| 4 | rail | `0x0013AD20` | `0x0013AF28` | `0x0013BFA8` | `0x0013C5A0` |
| 5 | handplant | `0x00138B48` (`cHandplantMotion_gainFocus`) | `0x001391A8` | `0x00139528` | `0x00139178` |

The two motion enter handlers that already have decomp names are both `..._gainFocus`, so the motion "enter"
slot corresponds to what the decomp calls `gainFocus`.

### Request mechanics

- Requests are immediate. `0x001112B8`/`0x00111538` run the old handler's exit, store the new id, then run the
  new handler's enter, all inside the caller. Code after a request therefore already sees the new state
  (for example, a motion-4 request runs `0x0013AD20` before the caller's next line).
- Requesting control 13 is how callers flush the current controller: it runs the old control's exit (for
  control 5 that is the air-spin bake `0x00134CB0`; for 0, 4 and 11 the exits listed above) without entering
  anything.
- The control-0 enter `0x00131608` zeroes the idle clock `rider+0x35C` and the board-press jump latch `rider+0x360`.
- The motion-0 exit `0x0013F410` does not zero the smoothed triplets at `rider+0x208`, `+0x2BC` and `+0x2C8`; it
  sets their targets to 0 with fixed rates (0.05 for the first), so they decay after the rider leaves the
  ground. Accordingly, on a ground crash `+0x20C` and `+0x2BC` are not cleared on the crash tick **(PS2)**. The motion-0 enter `0x0013C7A8` resets the bounce phase and depths and scales velocity on
  touchdown.
- Deferred first update: cruise `0x00131620` first calls `0x00131CC0`. If the motion is already 1 (the rider has
  left the ground), `0x00131CC0` requests control 4 and returns 1, and cruise returns at once. Control 4's enter
  therefore runs on that tick but its first update runs on the next controller tick.
- Controllers 0 to 3 start their update with `0x00116378`, which requests control 10 once `rider+0x470 >= 0`
  (race finish).

### Per-tick order

The rider update `0x00128AF0` (stage list at `0x00128C00`) runs: control update, boost timers `0x001200D0`,
the triplet approach `0x001211F8` (turn, crouch, brake and other smoothed inputs), the motion update, the pose,
then the motion post stage and contacts. `0x001211F8` still runs on the airborne control-0 tick of a passive
departure, before control 4 has had an update **(PS2)**.

## Attacks (`0x001163B0`)

`0x001163B0(rider, attackLeft, attackRight)` drives punches and blocks on the upper-body animation channels.
All behaviour in this section was matched tick for tick against the PS2, including channel semantics, rates,
weights, fades and the 24 body bones **(PS2)**.

### Semantics

The upper channel is channel 1; channel 0 carries the held cycle.

| Semantic | Meaning | Animation class |
|---|---|---|
| 322 | BLOCK | 3 |
| 323 | PUNCH_TS | 13 |
| 324 | PUNCH_HS | 13 |
| 325 | BLOCK_CYC (channel 0) | |
| 326 / 327 | charge cycle for 323 / 324 (channel 0) | 13 |

- Right only: 323 in regular stance, 324 in switch. The attack facing `rider+0x340` is set to the right vector
  `rider+0x1A0`.
- Left only: 324 in regular stance, 323 in switch. `rider+0x340 = -rider+0x1A0` (all four lanes negated).
- Both: 322 (block).

### Hold, charge and release

- When animation marker 2 fires (latched and newly raised) while the matching button is held: the channel-1
  rate is frozen at 0; channel 0 plays the cycle (325 for a block, 326/327 for a punch); for the block cycle the
  channel-1 weight, target and fade are copied to channel 0.
- While channel 0's class is 13 (charging), the strength `rider+0x350` moves toward 1 by
  `timeScale * 0.0111111` per tick (EE FPU add/sub rounding matters for exact results) and is written to the
  channel-0 weight and target.
- Releasing the button, or switching sides, restores the channel-1 rate to 1 and fades channel 0 over 0.1 s.
- A second press is ignored until marker 1. Pressing both buttons early in a punch (gated on marker 0) turns
  it into a block.
- Returns 1 while the channel-1 class is 3 or 13.

`rider+0x340` (facing) and `rider+0x350` (strength) are the values the opponent-contact code reads.

### Animator calls used

`0x00311AE8` (class of a channel), `0x00312AA0` (requested semantic), `0x00311B20` with `0x001446A0`/`0x001446B8`
(latched and newly raised marker bits of the first sequence), sequence fields `+0x90` rate, `+0x94` weight,
`+0x98` target, `+0x9C` fade, `0x00313A10` (`cAnimSequence_fadeWeight__FP13cAnimSequenceff`), `0x00311E88`
(fade), and `0x003128E8` (`cRiderAnimBase_play`). For the play call the bone mask `rider+0x8C0` is placed in
`animator+0x20` and then restored to -1. The mask value seen on the PS2 is `8000FFFE` (hex), the same mask
`0x00115D48` uses **(PS2)**.

The attack pose depends on the per-channel priorities `{3,2,1,0,0,0}` stored at `0x0048D808` and copied to each
sequence's `+0x84` **(PS2)**.

### Callers and exits

- Cruise `0x00131620` reaches the attack call (at `0x001317E8`) only after the handplant, rail, jump and
  board-press attempts. While an attack is held it clamps the turn target to [-0.5, 0.5] (`0x00131804`..`0x0013182C`).
- Natural air `0x0012F730` calls, in order, the forced-reset check `0x00116120`, the attack, the optional
  handplant `0x00107578` and the automatic rail attach `0x00106848`. It checks the attack's return only while the
  owner `+0x218` upper latch is set; a held attack returns before handplant, rail attach and the targets, so the
  rider stays in control 4 **(PS2)**.
- The cruise exit `0x00131C30` (when the next control is not 4) and the natural-air exit `0x0012FB68` (when the
  next control is not 0) fade channel 0 over 0.1 s and set the channel-1 rate to 1 while the upper class is 3 or
  13. An attack therefore survives a passive departure and a landing **(PS2)**.
- The rail controller has its own upper-action callback; whether it matches `0x001163B0` is unconfirmed.

## Board press (control 1)

Pushing the right stick up (nose) or down (tail) while riding presses the board. R3 pops an ollie out of the
press and rotating the stick pivots the board. Nearly all of this section was matched tick for tick on the PS2
(nose, tail, ollie, pivot, full stick circle, re-press, the 1 s crash, jump-out, air press and landing, rail
entry and rail jump) **(PS2)**. Exceptions are marked.

### State

| Field | Meaning |
|---|---|
| `rider+0x268` | press depth (drives the 24/25/32/33 seeks) |
| `rider+0x274` | board depth (kind-15 blend, the 1 s lock, the crash); see the open question below |
| `rider+0x280` | pivot, -1..1 (times pi) |
| `rider+0x320` | switch (reverse) stance flag |
| `rider+0x328` | rail style |
| `rider+0x330` | press style: 0 none, 1 nose, 2 tail |
| `rider+0x360` | jump latch |
| owner `+0x1D0 +0` | phase |
| owner `+0x1D0 +4` | time in the press |
| owner `+0x1D0 +8` | time at full depth |
| owner `+0x1D0 +0xC` | idle time |
| owner `+0x1D0 +0x10` | R3 latch |

### Functions

| Part | Address |
|---|---|
| Entry (from cruise at `0x001317D8` inside `0x00131620`; from rail at `0x00131E80`/`0x00131ED8` inside `0x00131D30`) | `0x001161D0` |
| Enter / update / exit | `0x0012FC60` / `0x0012FC80` / `0x0012FE98` |
| Airborne while in control 1 | `0x0012FFF8` |
| Phase 0 (press in) / 1 (hold) / 2 / 3 (release) | `0x00130228` / `0x001303E0` / `0x001304D0` / `0x001304E0` (phase 2 only sets phase 1) |
| Phase-1 helpers: reverse, R3 ollie, pivot, depth, release | `0x001306B0`, `0x001307B8`, `0x001308D8`, `0x00130DD0`, `0x00131200` |
| Pivot spring / finalise / stance flip | `0x001313A8` / `0x00131428` / `0x0012FEC8` |
| Jump request (`+0x360` latch) / jump-out | `0x001162C8` / `0x00131348` |
| Scoring: press, pivot, end | `0x001199F8`; `0x00119AD8` + `0x00119898`; `0x00119A38` (calls `0x00117838`) |
| Animation kinds 13 / 14 / 15 | `0x001047F0` / `0x00104728` / `0x001046B0` (uses the three-way blend `0x00103CC8`) |
| Completion kind 9 | `0x00104BD8` (calls `0x00312BD0`) |
| `+0x330` write in the air | `0x00133590`..`0x00133634` inside `0x00133308` |
| Landing back into control 1 | `0x0013A5D4` inside `0x00139C88` |
| Rail attach honouring `+0x330` | `0x00106D9C` inside `0x00106848` |

Trigonometry comes from `0x0031BE50` (sine/cosine) and `0x0031C228` (atan).

### Entry `0x001161D0`

Declines a zero stick press, rail styles 3 and 4, and (on the ground only) a rider travelling against the
surface tangent `rider+0x3A0`. Up plays 24 with `+0x330 = 1`, down plays 32 with `+0x330 = 2`, then control 1 is
requested. Cruise calls it after its jump request and before the attack; on the entry tick cruise does no boost,
turn, crouch or animation work.

### Update `0x0012FC80`

1. `0x00116378` (finish), `0x00116120` (forced reset), `0x00106848` (rail attach), `0x0012FFF8` (airborne) and
   `0x001162C8` (jump request) are called in turn; each can end the tick.
2. Boost `0x00114130(BoostHeld, BoostPressed)`, then `0x00113F88(0, 0)`.
3. On a rail (`+0x328 != 0`): `0x00113F38(clamp(RailBalance, -0.5, 0.5))`. On the ground:
   `0x00113E80(clamp(CruiseTurn, +/-||+0x280| - 0.5|))`.
4. `0x00115B58`, `0x00115D48`, then the phase handler.

### Phases

- **Phase 0 (press in).** `+0x274` approaches 0.5 at `ts/60` and `+0x268` approaches 1 at `2*ts/60`. When `+0x268`
  reaches 1 it scores `0x001199F8` and enters phase 1 playing 28 (nose, `+0x280 = 0`) or 36 (tail,
  `+0x280 = 1`). Releasing the stick first goes to phase 3 (25/33).
- **Phase 1 (hold)** runs its helpers in this order:
  - `0x001306B0`: a reverse turn (`0x00114CC0`) swaps nose and tail through 23/31; completion kind 9 then
    continues into 28/36. (Code only; not reproduced on the PS2.)
  - `0x001307B8`: latches R3. Releasing R3 finalises the pivot (`0x00131428`), plays 35 if `|+0x280| > 0.5` else
    27, clears the style, calls `0x00114298(rider, 1.0)` (takeoff), then requests motion 1 and control 5: the ollie.
  - `0x001308D8` (BoardPivot): springs back (`0x001313A8`) when both sticks are under 0.1, when travelling
    backwards, or while R3 is latched. Otherwise it compares the stick angle (atan, quadrant-fixed, wrapped to
    +/-pi) with `+0x280 * pi`. If no pivot is running and the difference is at least 27 degrees it kicks `+0x280`
    to +/-0.85 or +/-0.15; otherwise it rotates at `delta/60 * 2*ts`. Inside 0.15..0.85 it plays 29/30 (nose)
    or 37/38 (tail), flipping the stance (`0x0012FEC8`) when a pivot starts.
  - `0x00130DD0` (depth): the `+0x274` target is the press, limited to `0.5 + t/2` for the first second and then
    snapped to 0 or 1. The approach rate blends two curves at `0x004FE920` and `0x004FE940` (in `.bss`, filled at
    run time) by `min(t * 0.2, 1)`, with rate 1 when crossing 0.5. Holding full depth for more than 1 s is a
    **hard crash**: `0x0010EB30(rider, 358 or 359, 0, rider+0x438, block)` where the block holds the rider
    position, velocity direction, -Z and speed.
  - `0x00131200` (release): 0.5 s with no input, or pushing the opposite way past 0.8, sends the `+0x274` target
    to 0. The press ends (phase 3, 25/33) once `+0x274 < 0.5`.
- **Phase 3 (release).** Waits for `+0x268` to empty (a re-press returns to phase 0 with 24/32), scores
  `0x00119A38`, then either restores stance (`0x00115640`) and returns to control 0, or on a rail plays
  `0x001326C8` and returns to control 7.

### Air, landing and rails

- `0x0012FFF8` (control 1 while in motion 1) plays 27/35 and requests control 5, or first finishes an active
  pivot (phase 2, scoring `0x00119AD8` + `0x00119A38`, semantic 287).
- Control 5 rewrites `+0x330` every tick from the BoardPress input and the pre-step adjust flip. A landing with
  `+0x330 != 0` plays 26/34 and re-enters control 1, skipping the stance restore `0x00115640`, the reverse turn
  and the landing animation. These three branches inside large routines are confirmed by PS2 runs only
  **(PS2)**.
- The air-adjust triplets `rider+0x28C`/`+0x298` are approached in the air after control 5 writes its targets;
  the air-adjust animation choice depends on them **(PS2)**.
- On a rail, control 7 calls `0x001161D0` through `0x00131E80`/`0x00131ED8`, and control 1 then runs with rail
  motion 4. `0x00106848` handles two more cases: a rider already in control 1 stays in control 1 with style 1
  or 2 taken from `+0x320` (code only), and a rider arriving from the air with `+0x330` set plays 26/34 and
  enters control 1 instead of control 7 **(PS2)**. An R3 ollie from a rail press is code only.
- A soft collision during a press goes through `0x00108388`, which runs the jump-out `0x00131348` and then enters
  the soft control 3.
- Cross during a press runs `0x00131348` and requests control 2 (semantic 245), the charged jump, on the ground
  or on a rail **(PS2)**.

### Animation

- Kinds 13 and 14 set slot 0's clock and run only the sequence fade. Kind 13 (29/30) seeks `|+0x280|`, and 37/38
  seek `1 - |+0x280|`. Kind 14 (24/32) seeks `+0x268`, and 25/33 seek `clamp(1 - +0x268)`.
- Kind 15 is the three-way blend `0x00103CC8` driven by `clamp(2 * +0x274 - 1)`. Its leaves are 49/48/50 for
  semantic 28 and 60/58/59 for 36. The three-way maps are read from `*(gp+0xD8C) + 0x1030 + leaf*4` (pointer at
  `0x004A3E7C`); other kinds use a single authored leaf through `0x00311710`.
- Completion kind 9 (`0x00104BD8`) moves latched bit 63 into the raised flags (`0x00144670`) and plays 28 or 36.

### Side effects

Controller rumble `0x002A1560`, an ollie event `0x00294170`, and a jump statistic through `0x002F6AC8`.

## Handplant (control 11 + motion 5)

Holding the handplant input (command bit `0x2000`, Circle) near a rail lip plants a hand on it. A rail qualifies
when bit 1 of its runtime flags is set; every grindable Snow Jam rail has flags `0x30003`. The entry test's
rail query uses mask 2 and a 300 cm radius (which callee performs it is not stated). Entries from cruise,
natural air and spin, phases 3 to 6, the rail attach from phase 6 and the landing were all matched tick for
tick on the PS2 **(PS2)**.

### Functions

| Part | Address |
|---|---|
| Entry test and requests | `0x00107578` |
| Callers | cruise `0x00131620`, natural air `0x0012F730`, spin `0x00133308` (only when the air-control state `+0x0C == 3`) |
| Motion 5 setup | `0x00138BA0` |
| Motion 5 enter / update / post / exit | `0x00138B48` (`cHandplantMotion_gainFocus`) / `0x001391A8` / `0x00139528` / `0x00139178` |
| Launch velocity | `0x00139548` |
| Control 11 setup / enter / update / exit | `0x001329B0` / `0x001328B0` / `0x00132A30` / `0x00132F98` |
| Play (with reflect) | `0x00132FB8`, clip table `0x00459FC8` |
| Scoring | `0x00119BF0` (begin), `0x00119C38` (launch commit) |

The motion-5 post `0x00139528` only calls `0x0011E150`, which updates the body query points. The air-motion enter
`0x001399E0` sets air-motion `+0` when the previous motion was 5; the air orientation step reads that value as
a mode flag.

### Entry `0x00107578`

- Has seven reject paths. The airborne check rejects animation classes 18..20 (`0x00311AE8(anim, 2)`), not
  semantics.
- On entry the old controller's exit runs through the normal request path: the air-spin bake `0x00134CB0` for
  control 5, or the upper-channel attack fade for controls 0 and 4. A ground entry also runs the motion-0 exit.
- In cruise, a failed attempt while the input is held clamps the turn target to +/-0.5, sets crouch 1 and
  brake 0, and skips the rail attach `0x00106848` for that tick **(PS2)**. In natural air a failed attempt
  sets the crouch request to 1 before the later calculations.

### Motion 5

- Setup `0x00138BA0` measures the direction to the lip from the bone whose index is stored at `rider+0x8A8` (5),
  not from the board root.
  Its `relative.w <= 0` branch cannot be reached with finite inputs.
- The pinned motion update computes the launch once (motion-5 `+0x10` becomes nonzero). It then seeds the shared
  air predictor at lip + 5 cm on Z, steps it 8 times, and keeps stepping until the predictor status is 1 or 3.
  On later pinned ticks it aligns the rider with `0x00121AA0`, gain `2*ts`, maximum rate `6.632*ts`.
- The frame-begin speed limit `0x0011B3F8` special-cases only motion 1 (3333.33). Motion 5 uses the ordinary
  formula with terminal 1 and crouch 1.

### Launch velocities `0x00139548`

Each case sets the lateral push and then overwrites the vertical velocity (27.78 = km/h to cm/s):

| Phase | Horizontal | Vertical |
|---|---|---|
| 3 (handspring) | `0.7 * entrySpeed` along the tangent, minus a lateral `2*27.78` (rail variant `15*27.78`) signed by the lip direction | 0 (rail variant `10*27.78`) |
| 4 / 5 | lateral `5*27.78` (rail variant `15*27.78`), toward (4) or away from (5) the lip | 0 (rail variant `5*27.78`) |
| 6 | `833.33` along the tangent | `+416.67` |

Phase 5 is reached when `|b| >= 1` (see balance below) and phase 6 leads into a rail attach (control 11,
style 4) **(PS2)**. The meanings of phases 0, 1, 2 and 7 are not described beyond the phase-2 exit bake.

### Balance fields

- `rider+0x250` is the presentation-roll triplet that `0x0011FA10` (`cRider_doLeanPoseAdjust`) reads. Control 11
  reuses it as the balance `b`, so the phase-2 exit bake leans the rider by `b` before it zeroes the triplet.
- `rider+0x244` is a separate triplet: the seek amount for the kind-9 balance animations (semantics 40/45, the
  HPTS/HPHS balance-through and reflect clips), driven by the HandplantBalance input.
- The board-press notes also use "kind 9" for the completion handler `0x00104BD8`; whether both refer to the
  same animation-kind table entry is not stated.

### Exits

- The exit event (bit 1) calls the ordinary rail attach `0x00106848`, which accepts control 11.
- When the clip finishes, the controller plays 287 and requests control 4 (in the air) or plays 61 and requests
  control 0 (on the ground).
- If the rider lands while control 11 is still active, control 11 stays in charge on the ground until the clip
  completes, then plays 61 (code only).
- Trick names come from table 13 of the trick identity: kind 1 "Handplant", kind 2 "Handspring".
- Side effects: `0x002F6AC8` sets an attempt flag (owner `+0xD27` bit 6), `0x0029DC48` records a results
  statistic, and `0x00161AB0` is the SPOKE handplant camera.

## Hard crash (control 8 + motion 2)

Hard impacts call `0x0010EB30`, which enters control 8 and then motion 2. Motion 2 is the wipeout body
simulation with sliding and airborne submodes; control 8 is the five-phase animation and recovery machine. The
facts in this section come from reading the code; the only PS2-checked crash is the board-press crash above.

### How a crash starts

- The landing classification in the landing routine `0x00139C88`: a result other than `0x1B6` leads to a hard
  crash (the meaning of the result value is unconfirmed).
- The collision reaction `0x00105D98` (cruise and airborne body bounces) picks a soft reaction (control 3, via
  `0x00108388`), a crash (control 8), or a reset request (hazard surfaces and the direction-change accumulator).
- The board press after 1 s at full depth calls `0x0010EB30` directly (semantics 358/359).

The collision event block passed in has the contact point at `+0`, the normal at `+0x20` and the closing speed
at `+0x30`.

### Entry sequence `0x0010EB30`

1. Peak impact.
2. Crash statistics and boost penalty (`0x00119B08` crash count/penalty; the boost-loss test is `0x00117948`).
3. Observers.
4. Temporary control 13 (flushes the old controller; from control 5 this runs the air-spin bake `0x00134CB0`).
5. Optional prewind compensation, including `0x0011DFE0`'s orientation normalisation.
6. Presented-root bake (`0x0011FA10`).
7. Input resets.
8. Preview of the selected clip and root compensation.
9. Animation play.
10. Control 8, then motion 2.

The crash-snow impact report `0x00111AA0` is called from `0x0010EC04`.

`0x00116930` is a no-op. Because control 8 enters before motion 2, control 8's class-22 board detachment sees
the crash submode retained from the previous crash. The crash state is not rebuilt on every entry: angular
vectors and the previous progress sample survive until their own update stages.

### Root bake (entry and the reset-clip transform `0x0012E010`)

The current scaled local root is composed with the inverse of the selected clip's preview root; that delta is
applied to the physical transform and its inverse is passed to `0x00311BF0`
(`cRiderAnimBase_changeOrientationOffset`). The current local root comes from geometry `+0x24/+0x28`, before
world FK/IK. The preview is a separate `0x0030ECD8` sample at time zero using the original sequence, root and
mirror settings. Existing animation roots are compensated before the new semantic is played.

### Motion 2 (wipeout)

| Function | Role |
|---|---|
| `0x00136C40` (`cWipeoutMotion_gainFocus`) | motion enter |
| `0x00136D40` | board detachment |
| `0x00136F30` | detached-board integration |
| `0x00137750` | airborne submode: predictor and alignment |
| `0x00137860` | airborne body/terrain landing response |
| `0x00137D18` | sliding submode: forces and terrain response |
| `0x00138640` | contact finish (block at `0x001388D4`) |
| `0x00138960` | crash contact probe |

- **Detached board.** While motion `+0x150` is set, the board position `+0x130` and quaternion `+0x140` evolve on
  their own: gravity -1800 cm/s^2, XY drag -0.2, the standard speed cap, angular damping, and a fixed quaternion
  integration order. The board collides as four unscaled 20 cm spheres at +70, +30, -30 and -70 scaled cm along
  the X axis of the posed bone whose index is stored at `rider+0x8A4` (23 for Zoe), with a broad radius of
  `90 * scale`. Its contact
  response has bounce and stop thresholds, entity forces, and draws from the shared RNG for angular jitter.
- **Sliding `0x00137D18`.** Uses the surface's `+0x90` slip curve, crash-specific damping and gravity, drives
  angular speed toward `linear speed * 0.0125`, and caps speed. Position is integrated before acceleration. The
  terrain correction keeps the old material's `+0x18` depth even when the hit selects a different surface. It
  distinguishes shallow and deep penetration, applies moving-entity forces, raises a hazardous-surface reset,
  and sets the airborne flag with a delay.
- **Contact probe `0x00138960`.** Probes from the actor position +/-200 cm along the supplied normal with refined
  terrain, preferred fraction 0.575, and rider cache `+0x864`. This differs from the ordinary landing probe,
  which uses the animated board root.
- **Sliding body response.** Uses coarse 3x3 terrain even for human riders, the ground-normal filter, and
  half-speed restitution bounded to 27.777779..555.555542 cm/s. After the scenery and pair callbacks it commits
  the pending airborne flag and zeroes speeds below 50 cm/s.
- **Airborne body response.** A body hit is required before terrain is probed. A valid landing updates the
  impact flags, the surface state and switches to the sliding submode; other collisions push the body and
  restart the prediction.
- **World query policies.** Sliding: coarse, cache `rider+0x868`, ground-normal filter. Air: human/NPC detail,
  cache `rider+0x868`, no normal filter. Detached board: coarse generic world queries with no rider cache.
- **Body pushes** go through `0x00106538`: the physical position, `rider+0x9D0`, the cached centres at
  `rider+0xAA0` and the bounds at `rider+0x400`/`+0x410` move; posed geometry and cached presentation data do not.

### Control 8 (crash recovery)

Control-8 object fields: `+0x54` integer impact flag, `+0x60` impact velocity, `+0x70` recovery meter.

| Phase | Role |
|---|---|
| 0 | initial clip; on completion, angular velocity is derived from consecutive posed quaternions (class 23 derives the detached board's velocity from its own consecutive poses) |
| 1 | air recovery |
| 2 | ground recovery |
| 3 | get-up |
| 4 | reset clip (root rebaked through `0x0012E010`) |

- The recovery meter `0x0012CB68` fills while command bit `0x2000` is held, for human riders (category 1).
- Phases 1 and 2 re-read state after their callbacks, keep clip progress across clip changes, handle impacts,
  and issue reset or get-up requests in a fixed order.
- Clip choice covers air/ground continuation, get-up, special landing and reset clips. Play requests use group 0
  and blend argument -1. Crash semantics span 328..410; their completion pulses (sequence `+0xC0`) drive the
  phase changes. The playback rate is selected per clip.
- Get-up enters control 0 with motion 0 (ground enter `0x0013C7A8`), or control 5 with motion 1.
- Ragdoll body-vs-scenery collisions (`0x00105D98` writing control `+0x54`/`+0x60`) are consumed by `0x0012D4E8`,
  `0x0012D160` and `0x0012CB68`, which report through observer calls (`0x0028B180` and others).

## Crash snow (board-wake effect during motion 2)

The board-wake effect object is at owner `+0xB40` (below, `FX`). Everything here is from reading the code.

### Per-rider update `0x002DF920`

- If `FX+0x60 != 0`, `0x002DF448` deactivates all ten emitters and clears it.
- If `FX+0x80 == 0`, `0x002DF4D0` binds the thirty BodySnow bones and sets it to 1.
- While the motion is 2, the block `0x002DF960`..`0x002DFB5C` clears `FX+0xB0` (ground emission). That switches
  off SnowTrail (0), Cloudy (7), the Chunky (1/2) carve and brake spray, and the deceleration impact request
  (the `kind = true` request further on in `0x002DF920`).
- BodySnow `0x002E2260` is called at `0x002DFE4C` (after Cloudy 7) and Kicker `0x002E1F70` at `0x002DFE64`.

The reset `0x002DF3B0` zeroes `FX+0x4` (buildup), `FX+0x78` (bone cursor), `FX+0x80` (bones bound) and `FX+0xE0`
(impact strength), and sets `FX+0x120 = 0.5` and `FX+0x90 = (1,1,1,1)`.

During a crash the visible spray has exactly two producers:

1. **Impact bursts** `0x002E1598` (emitters 5 and 6), fed by `0x002E23E0` triggers that the crash physics raises
   through `0x00111AA0`. Chunky 1/2 also fire their impact burst from the same retained strength, with an extra
   +/-55 cm jitter when the motion is 2. In motion 2 each burst adds `2 * amount * scale` to the buildup `FX+0x4`,
   up to 2.0.
2. **BodySnow** `0x002E2260` (emitter 9): one puff per tick at a cycling body bone while the buildup is positive.

Kicker (8, `0x002E1F70`), Rock (3, `0x002DFE88`) and RiderBreath (4, `0x002E1120`) are not part of the crash path.

### Bone table `0x002DF4D0`

`FX+0x7C` is a 30-word table allocated during construction (at `0x002DF174` inside `0x002DE4A8`). Each entry is
`0x00310C48(rider+0x780 skeleton, part 0, name)`, a linear `strcmp` (`0x004165A8`) over the skeleton's bone
names that returns `part.firstIndex + i`, or -1 if the name is missing. The order is: left and right shin and
foot, left and right thigh, hips, lower, middle and upper spine, neck, left clavicle, right hand, left bicep,
left bicep twist; then the legs, hips, lower and middle spine again; then left forearm, left hand, right
clavicle, right bicep, right bicep twist, right forearm. Legs, hips and lower spine appear twice, so 20 of every
30 ticks land on the lower body. The head and board bones are never used. The name strings are in `.rodata`
from `0x004879D8`, except "hips" (`0x004A3B00`) and "neck" (`0x004A3B08`) in `.sdata`.

### BodySnow `0x002E2260`

Inputs: buildup `FX+0x4`, speed `FX+0xB8` (the cached speed, the length of `rider+0x1E0`), cursor `FX+0x78`, bone
table `FX+0x7C`, colour `FX+0x90`, motion id `FX+0xD4` (from `0x0011FE98`), emitter 9's VelScale, velocity
`rider+0x1E0`, and the world bone matrices at `rider+0x780` geometry `+0x30` (64 bytes each, row 3 is the
translation in cm).

```
if buildup > 0 and speed > 83.333336:          // 3 km/h
    alpha = clamp(buildup * 1.5, 0, 1)
    emit(emitter 9, pos = boneWorld[table[cursor]].row3,
         vel = rider.velocity * VelScale, colour = (FX.colour.rgb, alpha), active = 1, dt = 1/60)
    cursor = (cursor + 1 < 30) ? cursor + 1 : 0
    if motion != 2: buildup = max(buildup - 1/60, 0)
else:
    emit(emitter 9, pos = boneWorld[bone index at rider+0x89C].row3, no velocity, no colour, active = 0, dt = 1/60)
```

- It never draws from the shared LCG (`0x004A3AFC`); the particle program's own seeds are consumed inside
  `0x003717C0` as for other emitters.
- The buildup does not decay while the motion is 2 and never decays on an inactive tick. A crash that stops the
  rider keeps its buildup until the rider moves again; after get-up the puffs fade over `buildup * 60` ticks (up
  to 2 s) with diminishing alpha. Alpha saturates at buildup >= 2/3.
- The inactive request uses the bone index at `rider+0x89C` (the primary/root bone, bone 0 in the shipped
  riders); that position only matters as the emitter's retained origin.
- Emitter 9's authored settings: start alpha 0.25, life 0.4 s, damping 1.5, final size 51.22, random velocity
  +/-200 cm/s per axis, texture 5 ("spry"), 2 particles per birth.

| Constant | Value | Bit pattern | Where |
|---|---|---|---|
| speed gate | 83.33333587646484 | `42A6AAAB` | `0x0049F6A4` (gp-0x3A4C) |
| dt and buildup decay | 1/60 | `3C888889` | `0x0049F6A8`, `0x0049F6AC` (gp-0x3A48, gp-0x3A44) |
| alpha gain | 1.5 | `3FC00000` | immediate at `0x002E22AC` |
| alpha clamp | 1.0 | `3F800000` | immediate at `0x002E22B4` |
| BodySnow VelScale | 0.8 | `3F4CCCCD` | `0x0049F554` (gp-0x3B9C), stored at construction (`0x002DF15C`) |
| bone count | 30 | | `0x002E2358` |
| emitter 9 offset | `0x1290` = 9 * `0x210` | | `0x002E2290` |

### Impact triggers `0x00111AA0`

`0x00111AA0(rider, position*, normal*, surface, strength)` is a wrapper for
`0x002E23E0(*(rider+0x77C)+0xB40, position, normal, strength, surface, kind = 0)`. `0x002E23E0` takes
`|strength|`, keeps it doubled (for kind 0), and accepts a report only if it is stronger than the retained one
and at least 180 cm (100 cm with wide scatter) from the retained point.

| Caller | Call site | Position | Normal | Strength | Surface |
|---|---|---|---|---|---|
| crash entry `0x0010EB30` | `0x0010EC04` | event `+0` | event `+0x20` | event `+0x30` closing speed | a `0x0010EB30` argument |
| wipeout air landing `0x00137860` | `0x001379D4` | `0x00138960` probe point | probe normal | `dot(velocity, normal)` (<= 0) | probe surface |
| wipeout sliding `0x00137D18` | `0x00138454` | hit point | hit normal | deep branch: surface-velocity length; shallow: velocity length before correction | hit surface |
| ordinary landing award `0x0010E910` | `0x0010EA08` | record `+0` | record `+0x10` | landing speed | record `+0x4C` |
| cruise scenery probe `0x001242B0` | `0x001245BC` | probe (exact argument not recovered) | probe normal | probe speed | probe surface |

`0x00137860` reports only when the probe fraction is at least the constant at `0x0049BE88` (gp-0x7268), the
normal speed is closing (<= 0) and the body is within 10 cm of the hit. `0x00137D18` reports only on
penetration (distance < 0). Ragdoll body-vs-scenery collisions never call `0x00111AA0`.

## Forced reset (control 9 + motion 3)

A reset puts the rider back on the course after a fall, a hazard surface or an explicit request. It is timed by
control 9, which fades to white, moves the rider halfway through, and hands back to the air controller. This
section is from reading the code except where marked.

### Request `0x00116120`

Controllers call it every tick (natural air calls it first). It proceeds only when a reset was requested or the
reason is nonzero. It clears `rider+0x2E8`/`+0x2EC` (boost window and boost modifier); reasons 1 and 4 call
`0x0011A088` (`cRiderMetrix_evAutoResetSurface__FPv`); owner `+0x350` records whether the reason was > 0; it
enters control 9 and then motion 3; and it reports to `0x0029A220` and `0x00270970`.

### Control 9

- **Enter `0x0012F230`.** Progress = 0 and the main channel's rate = 0. If `0x0012F588` allows it for the rider's
  output device, it builds the fade effect with white colour values and binds it to the progress field. The
  fade's opacity follows the progress directly, with no timer of its own (related fade code: `0x002EBB10` and
  the block at `0x002E48AC` inside `0x002E47E8`).
- **Update `0x0012F398`.**
  1. Progress approaches 1 by `0.025 * timeScale` per tick (the float is 0.02500000223517418).
  2. When progress crosses 0.5: select the reset route (`0x00112D58`), get the route direction (`0x0026A8B8`),
     and place the rider (`0x0011D660`) with a vertical clearance of 200 cm (1000 cm on an event-variant branch).
     It then requests semantic 287, calls `0x0011DF18`, resets the score (`0x00119368`) and passes that result to
     `0x0010E098`.
  3. At progress 1: restores the playback rate to 1 and enters control 4 with motion 1. `0x0012F588` gates the
     device-specific completion work.

  At `timeScale = 1` the placement happens on tick 21 and completion on tick 41.

### Motion 3

`0x00136958` calls `0x0011E098` (`cRider_updateOrientationImplicit`) to rebuild the orientation; `0x00136978` is
a no-op. No riding or crash physics runs while control 9 owns the rider.

### Placement `0x0011D660`

The first part, up to `0x0011DACC` (inside `0x0011D660`):

- Clears both of the actor's contact caches.
- For a nonnegative clearance, builds one segment from the target point -7000 cm on world Z to +200 cm on world Z
  (segment constructor flags 2, preferred fraction 0.9791666865348816) and queries it with `0x00336850`, which
  includes terrain. This is a single vertical probe, not a search. A hit supplies position and normal; a miss
  keeps the requested point and uses world up as the normal. The clearance is then added vertically.
- A negative clearance skips both the probe and the offset.
- Heading comes from the horizontal components of the input direction. Heading and slope quaternions plus the
  `0x0011E098` rebuild give the physical frame; projecting and normalising the tangents gives
  `rider+0x3A0`/`+0x3B0`.

The rest, from `0x0011DAD0`: clears velocity, depth and contact state, the 19 filter triplets at
`rider+0x1F0`..`+0x2D0` (the `+0x25C` current and rate become 1), the spin, flip, boost, style and manual fields and
several body timers; sets the time scale and leg weight to 1; restores `+0x320` from `+0x324` (stance); clears the
animation channels; restores the default mirror and root for the stance; plays the requested semantic (287 for a
reset); samples the local and world pose; commits body geometry and bounds; and calls the camera and player
observers.

### Reset route selection `0x00112D58`

Differs from the ordinary human/NPC route selector `0x00112A50`:

- Calls `0x0026AF98`, which asks `0x0026AFB8` for at most 6 candidate routes with a nonzero `+0x3C` field. It uses
  the current position with no velocity lookahead.
- Projects each candidate with `0x0026A428`. A virtual call (slot `+0x40` of the rider interface at `rider+0x6C0`)
  decides whether projections beyond `pathLength - 200 cm` are rejected.
- Scores the squared distances to the projection and to the event-adjusted sample at `projection + 796 cm`; the
  lower score wins. Picking the retained route cancels a pending switch.
- Checks the old route pointer (`+0xAB8`) before installing the winner, so a missing retained route stays missing.
- With a retained route it invalidates the `+0xABC` cache and refreshes the projection and samples even when the
  winner did not change.
- The event-aware sampler updates the distance by reference, so `+0x490` is sampled at the adjusted `+0x4C4`,
  `+0x4A0` uses the adjusted distance + 796 cm with another event-aware sample, and `+0x4C0` receives the adjusted
  `+0x4C4`. (The notes do not say which object owns these route fields.)

`0x00269F18` (event-aware sample): starts two candidate distances at input + 50 cm. For each event interval that
contains the original input distance (inclusive), event 16 extends the alternate to the interval end, event 12
lowers the selected distance to the interval start, and event 14 raises it to the interval end. If the selected
distance still equals the input, the alternate is used. It writes the final distance back and samples with
`0x0026AB20`.

`0x0026A8B8` returns the path segment direction at a distance, using cumulative segment lengths and falling back
to the last segment. Ordinary per-frame human route progress is updated by `0x001125C0`, including on crash and
reset frames.

### Reset route data

The routes come from the AI/NPC route table reached through `0x004D33A8`/`0x004D33AC` (in `.bss`):
64-byte records with origin, bounds, segments, events, flags at `+0x38` and the `+0x3C` field used as the reset
filter. This is not the race-course path table. On Snow Jam the table has 129 records, 117 of them with a nonzero
`+0x3C` **(PS2)**.

## Semantics referenced

| Semantic | Use |
|---|---|
| 23 / 31 | board-press reverse (nose / tail) |
| 24 / 32 | press in |
| 25 / 33 | release |
| 26 / 34 | landing (or rail arrival) straight into a press |
| 27 / 35 | ollie out of a press (35 when `|+0x280| > 0.5`) |
| 28 / 36 | press hold (three-way blend) |
| 29, 30 / 37, 38 | pivot (nose / tail) |
| 40 / 45 | handplant balance seeks |
| 61 | handplant finish on the ground |
| 245 | jump charge (control 2) |
| 287 | played when handing over to air control: handplant finish in the air, pivot finish in the air, reset, natural air to control 5 |
| 322..327 | attacks (see above) |
| 328..410 | crash clips |
| 358 / 359 | board-press crash |

## Open questions

- `rider+0x274`: the board-press notes treat it as the board depth (kind-15 blend, 1 s lock, crash trigger),
  while the wake-effect notes read the same offset as the presentation roll; the handplant notes put the
  presentation-roll triplet at `rider+0x250` instead. This is unresolved.
- Command bit `0x2000`: the handplant and air-controller notes call it the handplant input (Circle, bit 13), and
  the crash notes call the same bit "held jump" when it fills the recovery meter. The bit value agrees; the name
  does not.
- Which crash semantic (358 or 359) belongs to the nose or the tail press is not stated.
- The control-8 enter/update, control-2/3/5 enter and motion-0/1/2 update entries are not given in these notes.
