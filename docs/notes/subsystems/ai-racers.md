# Computer riders

In race events the player shares the course with five computer riders. A computer rider is the same rider actor
class as the human, run through the same controllers, motion, animation, collision, crash, reset, rail and
handplant code; only the source of its command words, a few actor-interface methods and some human-only
reactions differ. Its commands come from an NPC input provider that paces the rider against the human
(rubber-banding through a per-rider time scale), follows authored AI paths, makes ground decisions (cruise,
jump, peer and designated-peer behaviours) and chooses grabs in the air. A rider manager ranks the riders,
maintains pair-proximity records and rivalries, and the results code estimates finish times for riders still on
course when the human finishes.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

The six-rider race described here (pass order, pair dispatch, shared random generator order, ranking and pair
records) was compared frame by frame against PS2 controller-replay captures of Snow Jam races, including one
with human/computer rider contacts, and matched bit for bit for every rider, the random state, the ranks and the
pair records to the end of each capture **(PS2)**.

## Where it lives

Per the current decomp split:

- `src/ai/ai.cpp`: `cAI` (`0x001286A0` `cAI_cAI`) and its rider set-up functions (`0x001298E0`
  `cAI_InitPlayers`, `0x00129C00` `cAI_initMissionRiders`, `0x00129E20` `cAI_initComputerRiders`,
  `0x00129FF8` `cAI_initComputerActors`), the per-tick pass loop `0x00128AF0`, the finish control `0x0012C678`,
  passive flight `0x0012F730`, `0x00131620`, and the rotation-time estimates `0x00135CB0`/`0x00135DB0`.
- `src/ai/computer.cpp`: difficulty (`0x0010C4F8` `cComputer_setIndividualRiderDifficulty`, `0x0010C758`
  `cComputer_updateRiderDifficulty`), the grab chooser `0x0010CAD8`, path/recovery state `0x0010D1A0`, the
  computer route score `0x0010D410`, interaction decisions `0x0010DA10`/`0x0010DBF0`, pacing `0x0010DEF0`,
  reactions `0x0010E028`/`0x0010E098`/`0x0010E910`/`0x0010EB30`, the manager refresh `0x0010F560`, designated
  peer `0x0010F878`, ranking `0x0010F998`, course progress `0x00112338`, AI route progress `0x001125C0`, track
  selection `0x001127F0`, route selection `0x00112A50`, and the progress getters `0x00113128`/`0x00113130`.
- `asm/1218.s` (not yet split): the NPC input provider `0x0010A768`, its serialisers and control producers
  (`0x0010A898`..`0x0010C140`), the ground behaviours `0x00100680`, `0x001009E0`, `0x00100B90`, `0x00100F88`,
  the world pass `0x00101B60`, `0x00105398`, `0x00106538`, `0x00106828`, and the rider-pair pass `0x00107888`
  with `0x00107E70`/`0x00108388`.
- `src/ai/rider.cpp`: the rider constructor (`0x0011B698` `cRider_cRider`), the per-rider pass stages
  `0x00120F20`..`0x00121818`, the time-scale step `0x00120090`, the reaction masks `0x0011C298`, the finish
  estimate `0x00122D78`, and the human pad provider `0x00127998`.
- `asm/14B10.s`: controller start `0x00116378`, reset request `0x00116120`, the upper-body peer reactions
  `0x00115D48`, `0x00115B58`, and the finish turn-around `0x00114CC0`/`0x00115168`.
- `src/ai/control/handplantcontrol.cpp`, `src/ai/motion/wipeoutmotion.cpp`: the ground, air, rail and crash
  "post" functions in which rider pairs are dispatched (`0x0013F178`, `0x0013F488`, `0x00139C88`, `0x0013BFA8`,
  `0x00137860`, `0x00138640`), the human route score `0x001446E8`, and the slot getter `0x00140B80`.
- `src/be/beintaggression.cpp`: rider relationships (`0x00155BF0`, `0x00155E58`).
- `src/bx/bxrandom.cpp`: the shared random generator `0x00317810` (`AIrand__Fv`).
- `src/bx/bxstringctor.cpp` (as split): path projection/sampling primitives `0x0026A428`..`0x0026AFB8`.
- `src/main/gamemode.cpp`: roster build `0x0023A4F0`, results ordering `0x00238BF8`, race results `0x0023A760`.
- `src/fe/ovstatehud.cpp` and `asm/1137E8.s`: the in-race place display (`0x001EA930`, `0x0021E1B0`,
  `0x0021E7E0`).

## Set-up and identity

### Creation

`cAI_initComputerRiders` creates the computer riders in a loop. For each one it stores the running rider index
into the actor at `+0x86C`, stores -1 at `+0x870`, and calls `cComputer_updateRiderDifficulty` on the new computer
object. The index continues from the count kept at `cAI` `+0x78`, which is written back afterwards.
`cAI_InitPlayers` numbers the human players from 0, and `cAI_initMissionRiders` and `cAI_initComputerActors`
continue from `+0x78` in the same way. The rider constructor `cRider_cRider` initialises both `+0x86C` and `+0x870`
to -1. No other store to rider `+0x86C` was found, so `+0x86C` is the rider's slot. `0x00140B80` (actor-interface
entry `+0x38`, the same in the human and computer vtables) returns it.

What `cComputer_setIndividualRiderDifficulty` and `cComputer_updateRiderDifficulty` compute is not covered here.
The career race difficulty level (0..2, adapted by `0x00147D20` / `0x00147E18` in `src/be/beintplayer.cpp`) is
covered with the career events.

### Lineup and relationships

- The five computer riders are chosen per human character by the roster build `0x0023A4F0`.
- Rider relationships age at each course load (`0x00155E58`) and change when a pair reaction happens
  (`0x00155BF0`). A relationship of 2 or more makes the rider a rival in the manager's pair records (below).
- At the countdown the shared random state equals seeding with 0 at the course load, followed by the load's own
  draws and 10 further draws **(PS2)**.

### The Snow Jam field (PS2)

A Snow Jam savestate during the start glide has six participants, the human in slot 0 and five computer riders:

| Slot | Character ID | Body scale | Initial AI path | Control at that moment |
|---:|---:|---:|---:|---:|
| 1 | 8 | 0.92 | 0 | 2 |
| 2 | 2 | 0.83 | 1 | 0 |
| 3 | 0 | 0.94 | 3 | 2 |
| 4 | 5 | 0.70 | 4 | 0 |
| 5 | 4 | 1.0 | 5 | 0 |

In the captured races slots 1-5 are Psymon, Allegra, Moby, Griff and Luther. Apart from body scale, the only
per-character differences in the computer riders' state are the Uber grab table, stance, the hair slot and the
channel-1 reaction masks; all attribute stats equal the human's in that state **(PS2)**.

## Actor class differences

A computer rider uses the actor-interface vtable `0x00458660` (at actor `+0x6C0`); the human uses `0x004583A8`.
They differ in two places only:

| Vtable entry | Human (`0x004583A8`) | Computer (`0x00458660`) |
|---|---|---|
| `+0x80`..`+0x9C` feedback hooks | write motion owner `+0xDFC`/`+0xE00` | no-ops (those owner words are NPC state on a computer rider) |
| `+0xA4` route score | `0x001446E8` | `0x0010D410` |

Other identity facts **(PS2)**:

- `+0x434` (rider type) is 0 for every computer rider and also for the human, so it cannot identify a human.
- The ground-contact cache `+0x864` is of kind 2 for both. The body cache `+0x868` is kind 0 for a computer rider
  and kind 1 for the human; the kind selects a coarse world-body query path for computer riders and a detailed
  one for the human, and the two select different collision results.
- Several human-only paths are gated on actor `+0x874` (see "Human-only parts").

## Field reference

### Rider actor

| Offset | Meaning |
|---|---|
| `+0x100` | finish-reaction selector (non-zero: reaction kind 1, else 4) |
| `+0x110` / `+0x120` / `+0x1E0` | position / orientation quaternion / velocity |
| `+0x2DC` | retained manual spin (see passive flight) |
| `+0x2E4` | speed limit, set at frame begin by `0x0011B3F8` from the motion mode (crash 2, reset 3) |
| `+0x300` | time scale; written only by `0x00120090` |
| `+0x35C` | upper-body timer read by `0x00115D48` |
| `+0x434` | rider type (0 for all six riders in the Snow Jam state) |
| `+0x470` | finish state; >= 0 once finished (the finish control is requested) |
| `+0x478` / `+0x480` | finish tick / did-not-finish flag |
| `+0x4B0` | route lookahead point copy |
| `+0x4C0` / `+0x4C4` | previous / current distance along the AI path |
| `+0x4CC` | route heading |
| `+0x4D0` / `+0x4D4` / `+0x4D8` | current course remaining / best remaining / progress origin (getters `0x00113128`, -, `0x00113130`) |
| `+0x6C0` | actor-interface vtable pointer |
| `+0x77C` / `+0x780` / `+0x784` / `+0x788` | motion owner / rig / animation / ragdoll predictor |
| `+0x864` / `+0x868` | ground-contact cache / body cache (kinds above) |
| `+0x86C` / `+0x870` | rider slot / set to -1 at creation |
| `+0x874` | human/computer gate for several human-only paths |
| `+0x8C0` / `+0x8C8` / `+0x8D0` | channel-1 reaction masks |
| `+0xAA0` | body collision spheres built at pose time |
| `+0xAB4` / `+0xAC0` | course / race progress |
| `+0xAB8` / `+0xABC` | selected AI path index / its path cache |

### Motion owner and NPC extension

| Offset | Meaning |
|---|---|
| `+0xDE0` / `+0xDE4` | mode / current control (common to human and computer) |
| `+0xDE8` | input provider object; `0x004585F0` for a computer rider |
| `+0xDF0`..`+0xF40` | NPC extension (0x150 bytes): driving, pacing, score and trick-plan state |
| `+0xDF8` | a float parameter (at this offset the human's owner layout has a recorder pointer; it does not apply) |
| `+0xDFC`, `+0xE00` | NPC state; `+0xE00` is the route-score role |
| `+0xE04` / `+0xE08` | route-score allow flag / randomise flag |
| `+0xE20` | rail-producer output byte (see control 7) |
| `+0xE24` | cleared on grab release |
| `+0xE2C` | grab release threshold |
| `+0xE34` | cleared by the provider whenever the control is not 5 |
| `+0xF44` | ground behaviour delegate (member-function descriptor) |

### Pair records

Each rider holds one record per other participant, indexed by slot. Known fields:

| Offset | Meaning |
|---|---|
| `+0x4` | peer is a human |
| `+0x10` | tick of the last pair impact (written into both riders' records) |
| `+0x1C` | rival flag, set by the manager refresh when the relationship is >= 2 |

A savestate after a landing keeps a human/slot-3 pair collision: both records hold the impact tick at `+0x10`, 33
ticks after the landing. The two stores are at `0x00107BCC`/`0x00107BD4` inside `0x00107888`, after the two
`0x00107E70` impulses **(PS2)**.

## Frame order and shared state

`0x00128AF0` runs each pass over all riders in slot order before starting the next pass; completing one rider's
whole frame before the next is not equivalent **(PS2)**:

1. `0x0010F560` rider-manager refresh (every sixth game tick, before any rider pass).
2. `0x00120F20`, `0x00121068`: input providers and controllers.
3. `0x001210B0`, `0x001211F8`, `0x001216E0`: motion update.
4. `0x00121700`, `0x00121728`: pose; `0x0011EB98` calls `0x00106828`, which builds the body spheres at `+0xAA0`.
5. `0x00121750`: second motion phase: touchdown, `0x0013F488`/`0x0013AA48`, `0x00105398`, rider pairs
   `0x00107888`, the velocity clamp at `0x0013F358` (inside `0x0013F178`), rail and crash posts.
6. `0x001217F8`, `0x00121818`: course progress, route progress, triggers.
7. After all riders: the world pass `0x00101B60` (section activation).

### Manager refresh `0x0010F560`

- Ranking `0x0010F998`: a shell sort with Knuth gaps (`0x003E6328`); the ranking result is kept at `+0xEC`.
- Pacing bounds of +/-50000.
- Pair-proximity records; `+0x1C` = relationship >= 2.
- The designated peer, from `0x0010F878`.

### Rider pairs `0x00107888`

The pair pass is called from inside each rider's own second motion phase, not in a separate pass **(PS2)**:

- in the ground post `0x0013F178` and the air post `0x00139C88`: after `0x00105398`, before the `0x0013F358` clamp;
- in the rail post: at `0x0013C098` inside `0x0013BFA8`;
- in the crash posts `0x00137860` and `0x00138640`: after `0x00105398`.

A rider later in slot order can therefore be bumped before its own `0x00121750` runs. It presents its unclamped
velocity and its pose-time spheres; a velocity set on it by an earlier rider becomes its unclamped velocity and is
clamped by its own `0x00121750`. The pair pass translates riders with `0x00106538`, sets velocities with
`0x00107E70` followed by the air-predictor restart `0x001135B8` (`cAirPredictor_startLaunchIntoAir`), and reacts
with a soft reaction `0x00108388` or a crash knock-down `0x0010EB30`.

### Shared random generator

All riders draw from one generator, `AIrand__Fv`, whose six-word state is at `0x004FF030`. Draws happen in pass
order **(PS2)**:

- controller pass (`0x00121068`): the NPC providers, `0x00115D48` and `0x00131620`, in slot order;
- then the second motion phase and progress passes in slot order (pair reactions, route changes);
- then the world pass: section activation's builtin-3 key-8/key-6 draws and the random starts of `0x00341AA0`,
  in resource order.

### Shared world entities

Rollers (`0x0035E850`), log teeters (`0x00342358`), splines and multi-splines, crash bags, boost pickups and
triggers are single world objects; a change one rider makes (a scripted contact that creates a crash bag or
re-kicks a roller modifier, a pickup taken, a teeter attach force, a trigger or stage-trigger contact, a section
multi-spline activation) is visible to riders that run later in the same tick. Course-script spline launches go
from `0x00121818` to `0x0030A060` (slot 2).

## NPC input provider

The motion owner's provider (`+0xDE8`) is the object at `0x004585F0`. Its input method is `0x0010A768`
(this-adjust 0); `0x0010A898` and `0x0010A8E8` serialise the common owner and then the NPC extension
`+0xDF0..+0xF40`. The human's provider is `0x00127998`.

`0x0010A768` per tick:

```
clear the 8-byte output command
pacing 0x0010DEF0; time-scale step 0x00120090
producer = table 0x00456A30 [current control]; producer(...)
if control != 5: owner+0xE34 = 0
```

| Control | Producer | Meaning (where known) |
|---:|---|---|
| 0 | `0x0010A960` | ground |
| 1 | `0x0010AD78` | |
| 2 | `0x0010AA70` | |
| 4 | `0x0010B590` | passive air |
| 5 | `0x0010B250` | active air (grab) |
| 6 | `0x0010B790` | start |
| 7 | `0x0010AED8` | rail |
| 8 | `0x0010B750` | |
| 3, 9, 10, 11, 12, 13 | zero command | 9 is reset, 10 is the finish stop |

The producers write the same control-specific packed command layouts as the pad path. Neither the provider nor
its producers call the replay recorder (`0x0026D178`/`0x0026D2B0`), so computer riders' commands are not in the
accepted-command history.

Steering detail: above a speed threshold of 833.3334 the crouch magnitude used is 0.97, before it is packed into a
signed six-bit field.

### Ground producer (control 0) and behaviours

`0x0010A960` first updates path/recovery state (`0x0010D1A0`), then the interaction decisions `0x0010DBF0` and
`0x0010DA10` (attack/defence), then calls the behaviour delegate at owner `+0xF44`: a member-function descriptor
of signed 16-bit this-adjust, signed 16-bit virtual index and 32-bit target (it is not a command cache).

| Behaviour | Address |
|---|---|
| cruise | `0x00100680` |
| jump | `0x001009E0` |
| designated peer | `0x00100B90` |
| peer | `0x00100F88` |

In a savestate at the ready state all five riders use cruise; during the start glide slots 1/3/4 use jump and
slots 2/5 use peer; in a later savestate all five use jump **(PS2)**.

The behaviours use the path/event functions `0x0010B980`, `0x0010BB18`, `0x0010BBF8`, `0x0010BD10` and the
control writers `0x0010BFA8`, `0x0010C0A8`, `0x0010C140`. Together these provide steering, jump-zone queries,
recovery requests and attack/defence decisions; the provider's random draws are part of the shared stream above.

### Rail producer (control 7)

`0x0010AED8` launches jumps at jump zones on rails. On its no-jump-zone path it copies a stack output of
`0x0010B980` to owner `+0xE20`, but `0x0010B980` does not write its output flags on a miss, so the copied byte is
uninitialised stack. In every captured rail sequence `+0xE20` was 0 **(PS2)**; whether the value is overwritten
before any read is not established.

### Reset and controller start

- Controllers 0-3 begin with `0x00116378`; when `+0x470 >= 0` they request control 10 (the finish).
- A reset request (`0x00116120`) switches to control 9 from the next tick.

## Airborne decisions and trick choice

- `0x00135CB0` / `0x00135DB0`: rotation-time estimates.
- `0x0010B0E8`: stop planning.
- `0x0010CAD8`: grab selection. Inputs: the normal, tweak and Uber grab mappings, per-grab usage counters,
  capability, boost tier, stat-dependent timing, and the shared random generator. The plan and counters live in
  the NPC extension.
- `0x0010B250` (control 5) outputs the grab; its release branch (remaining <= owner `+0xE2C` + 0.3) also clears
  `+0xE24`.
- Grab timing uses the authored marker 1/2 times of the animation files, read through `0x00312820`, not clip
  durations. Every grab semantic in the data has a single mapping variant; with several variants the marker
  getter could draw from the random generator (unconfirmed).
- Command updates for passive air (control 4), active air (5) and start (6) all come from this plan state.
- Passive flight `0x0012F730` leaves `+0x2DC` unchanged, so the landing (`0x0013A968`) uses the retained manual
  spin rather than the air spin rate **(PS2)**.

## Routes

### AI path data

The course path object at `0x004D33A0` holds, for Snow Jam **(PS2)**:

| Offset | Content |
|---|---|
| `+0x4` | 14 start/lane marker records (40 bytes each) |
| `+0x8` / `+0xC` | 129 AI paths |
| `+0x10` / `+0x14` | 8 course-progress paths |

- Each AI path has a 64-byte runtime header with interface `0x00481478`. Its first 56 bytes follow the course
  path's geometry/event layout. `+0x38` is authored flags (in a course path it is the remaining-distance float);
  `+0x3C` is a separate authored field.
- Path origins, bounds, direction/length segments, flags and event extents match the course's AIP file.
- Raw AIP event IDs map to runtime IDs as 100 -> 12, 102 -> 14, 103 -> 15, 110 -> 16, 111 -> 17, 300 -> 20,
  and -1 -> 0. What each ID triggers is not yet known.
- A marker's position and direction are the six floats of the AIP marker region; its final pointers resolve to
  the raw track and AI-path indices. Runtime marker flags can differ from the raw flags. The first six markers are
  the start lanes, but riders' positions at the countdown already differ slightly from the marker origins, so the
  start-up/countdown motion moves them (unconfirmed which code).

### Route selection `0x00112A50`

Separate from track selection `0x001127F0`. It filters and orders candidates with `0x0026AFB8`, then uses
`0x0026A428`, `0x0026AC48` and the sampler `0x0026AB20` (`0x0026A638` is the projection primitive), and finally
updates the path cache `+0xABC` and the distances `+0x4C0`/`+0x4C4`. Its route-flag filtering and state
transitions are its own and differ from the course-progress selector.

- Computer riders score candidates with `0x0010D410` (actor vtable `+0xA4`). The score context is shared-world
  data: role `+0xE00`, allow flag `+0xE04`, randomise `+0xE08`, the current and followed path indices, and the
  current AI paths of all computer riders. Terms: route affinity, authored speed thresholds, geometric proximity,
  an occupied-route penalty, followed-target priority, and a random branch drawing from the shared generator.
- The occupied-route penalty ignores humans; the designated-peer / followed-path lookup includes every
  participant.
- The human branch instead minimises the sum of two squared geometric distances.
- At zero speed the score arithmetic follows the EE's saturating float behaviour (division by 0 gives
  +/-FLT_MAX, and 0 x FLT_MAX gives 0).

### Route progress `0x001125C0`

`0x00121818` calls course progress `0x00112338`, then `0x001125C0`, for every rider including the human.
`0x001125C0`:

1. copies `+0x4C4` to `+0x4C0`;
2. projects onto the path using `+0xABC`'s horizontal cache;
3. computes a lookahead point 796 cm ahead and copies it to `+0x4B0`;
4. may change route: near a path end, after crossing event 18 or 20, or every 60 ticks while more than 500 cm
   from the path; it tests `+0x4D4` (best remaining, after course progress);
5. computes the heading `+0x4CC` after any change.

The provider reads these values on the next tick, so the retained previous-phase values drive steering.

## Pacing and rubber-banding

- `0x0010DEF0` compares the rider's own current course remaining (`+0x4D0`) with that of the first enabled pair
  record whose peer is a human, in slot order. It does not use the designated peer.
- A signed event variant byte at `0x00535C11` selects the pacing variant.
- The result is a target time scale. `0x00120090` moves `+0x300` toward it by a fixed increment and publishes it
  before control handling. `+0x300` is written nowhere else.
- Ground motion applies `+0x300` for computer riders, and boost timers use it.
- The manager refresh also keeps pacing bounds of +/-50000; how they limit the pacing is not described.

## Reactions and peer interactions

### Upper-body peer reactions `0x00115D48`

- Runs in the controller pass for every normal-control rider. Its peer loop tests pair record `+0x1C` (rival),
  not `+0x4` (peer is human) **(PS2)**.
- With an empty upper-body channel the timer at `+0x35C` advances; the draws at `0x00115E4C` and `0x00115FA4`
  inside `0x00115D48` then take two values from the shared generator. An active upper-body animation resets
  `+0x35C` and returns without drawing, so the number of draws per tick is not fixed.
- On the first tick after a start-glide savestate this gave 0/0/2/0 draws for slots 0/2/4/5; slot 4's timer went
  from 1.4999988 to 1.51666545 and its two draws made the random state equal to the next frame's **(PS2)**
  (a 1.5 threshold is suggested, unconfirmed).
- `0x00115B58` issues upper-body requests.

### Reaction kinds

| Kind | Source | Riders |
|---|---|---|
| 1-3 | Uber landing, `0x0010E910` | human only (`+0x874`) |
| 4 | get-up, at `0x0012E6BC` inside `0x0012E690` | human only (`+0x874`) |
| 5 | full meter, `0x0010E098` | every rider |
| 6 | super-boost timer end, `0x001200D0` | every rider |

Pair reactions: soft `0x00108388`, crash `0x0010EB30`. The finish uses `0x0010E028`.

### Channel-1 reaction masks

`0x0011C298` builds `+0x8C0` (via `0x00310CE8` over the bone list `0x00457A90`) and `+0x8C8` (bone list
`0x00457B38`), and ORs the "morph" mask from `0x004A1090` into both; `+0x8D0` holds that morph mask. The values
differ by character **(PS2)**: `0x8000_FFFE` / `0x8000_FFF8` for Zoe, Sam and Griff; values beginning `0x4000` for
Psymon and Luther; a different pattern for Allegra and Moby (the source gives only prefixes); `+0x8D0` is `0x870`
for all. They gate `0x00115D48` reactions, `0x00115B58` requests, the finish reaction and attacks.

## Rider-pipeline details seen in multi-rider races (PS2)

These are shared with the human but only show up with several riders:

- Obstacle query near the route: the check at `0x0013F4CC` inside `0x0013F488` skips the `0x003342D0` query for a
  rider with `+0x874 == 0` within 50 cm of its route. `0x00105398` and the pair pass still run.
- The rail post's body query `0x0013C140` has no `0x0013F488`-style normal filter (it is built at `0x0013C1A0`
  inside `0x0013C140` without one); the response only rejects an opposed normal.
- Terrain departure: the switch to air motion happens at `0x0013F2CC` inside `0x0013F178` (`0x0011FE78` with 1),
  after `0x0013F488`, `0x00105398` and `0x00107888`. A crash entered from the obstacle response on a departure tick
  starts sliding (previous motion 0), and the pair pass still sees a grounded actor.
- A touchdown that enters a landing crash before `0x0013AA48` (inside the air post `0x00139C88`): the rest of the
  air post runs on the ragdoll; the `0x0013AA48` response moves the crash actor and `0x00105D98` dispatches a
  ragdoll impact, restarting the crash predictor from the post-response state.
- `0x00137860` (crash, airborne body contact, not landed) only pushes, removes the closing velocity and restarts
  the predictor; it does not call `0x00105D98`, so the collision history is unchanged.

## Finish (control 10)

`0x0012C678` runs for every rider, human or computer, once `+0x470 >= 0`:

| Phase | Behaviour |
|---:|---|
| 0 | turn target +/-0.1, boost off, animation semantic 11, velocity x0.97, brake target 1 |
| 1 | velocity x0.93 until abs(brake) < 0.2 and turn is 0; then reaction `0x0010E028` (kind 1 if `+0x100` else 4) and semantic 4 |
| 2 | the pending reaction plays at rate 0.75; afterwards `+0x470 = max(+0x470, 10)` |
| 3 | stopped |

In phase 0, when `+0x2DC == 0`, `0x00114CC0` first turns a rider that is moving backwards through 180 degrees
(`0x00115168`, semantic 21); only after that does phase 0 require ground contact (`0x0011FE98`).

## Standings, place display and results

### In-race place `0x0021E1B0`

Drawn while the race is running (race phase 5).

- Atlas `OV_1-3`: `nm1w`..`nm6w`, st/nd/rd/th, slash and the rider count.
- Position (20, 20); the number is 26x42 for 1st, otherwise 40x42.
- Colour gold (1, 0.8, 0) for 1st, blue (0, 0.494, 0.7) otherwise.
- Place change animation (from `0x001EA930`): 1st scales by 1 + sin(4 pi t) x 0.1996 x (1 - t^2); other places fade
  alpha by 0.5 t + 0.5.
- 1st-place glow: `0x0021E7E0` is called twice at draw order 10, behind the number and suffix. While the rider
  leads, the place object's `+0x4C` timer runs 0 -> 2 and wraps, +0.026782159 per tick (at `0x001EBC10` inside
  `0x001EA930`); otherwise it is -1. The glow texture (HUD `+0x474`, handle `0x5F5`) in the number colour covers
  each rect grown about its centre by 1.8101751 (`0x0049DD94`, gp-0x535C), with alpha A x (0.5 + 0.5 tri(g)),
  where tri is a triangle wave of the timer g. A rect wider than 72 is drawn as two 36-wide ends and a
  constant-U middle.

### Results

- When the last human finishes, rows are ordered by time with `0x00238BF8`; a did-not-finish rider gets 360000
  ticks (`0x0023A860` inside `0x0023A760`). The Single Event Results show rank, rider and time (mm:ss).
- Riders still on course get the estimate from `0x00122D78`:

```
average = (origin - remaining) / raceTicks        ; origin = +0x4D8 (0x00113130), remaining = +0x4D0
floor   = 30.0 - slot                             ; slot from actor vtable +0x38 = 0x00140B80 (+0x86C)
estimate = raceTicks + trunc(remaining / max(average, floor))    ; cm per tick
```

The 30.0 is loaded as an immediate at `0x00122DA0` inside `0x00122D78`.

**"30 - place" or "30 - slot".** One source note gives the floor as 30 - place (with `+0x86C` described as the
ranking place), another as 30 - slot. The code reads actor `+0x86C` through `0x00140B80`, and `+0x86C` is only
written by the rider constructor (-1) and the `cAI_init*` functions (the rider's running index); no store from the
ranking code was found. The code therefore supports **30 - slot**: the floor is 30 cm/tick for slot 0 (the human)
and 29..25 for slots 1..5.

## Human-only parts

Not run for computer riders:

- the feedback hooks at actor-interface `+0x80`..`+0x9C`;
- reaction kinds 1-4 (Uber landing, get-up);
- the wind push `0x00125970`;
- the finish-line trick bonus `0x001194C0`;
- presentation hooks: pad rumble, camera shake, fades and HUD cues.
