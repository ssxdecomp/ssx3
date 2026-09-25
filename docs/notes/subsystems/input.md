# Controller input

The game reads the DualShock 2 through the pad library and converts each packet into 24 float channels. A
consumer keeps a per-button history (edges, debounce, auto-repeat) for every consumed sample. A compiled input
map (`DATA/CONFIG/INPUT.MAP`, or `INPUT2.MAP` for the "Pro" controller setting) turns buttons into named
actions through a small expression VM. For a human rider, an input provider packs those actions into two 32-bit
command words per tick, laid out according to the rider's current control state; the rider controllers decode
the words. Computer riders use a different provider that writes the same layouts. The same map also drives the
front-end UI actions, and a separate model drives pad vibration.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a
PS2 emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

Translation units as reported by the address lookup:

- `src/input/inputparse.cpp`: the device reader `0x00326EB0` (calls `scePadRead`, then converts the packet in the
  block `0x00327210`..`0x003276BC`), the mapping VM `0x00325450` (its MAX handler is at `0x003259C8`), the
  context default-property reset `0x00325250`, and the motor stop `0x00326CF0`.
- `src/input/inputmap.cpp`: `0x00320E18` (`cInputMap_compileMap`), the button-history update `0x00321298`, and the
  boolean action getter `0x00321108`.
- `src/bx/execman.cpp`: the float action getter `0x00320BF0` and the boolean getter `0x00320C48`.
- `src/main/ssxapp.cpp`: `0x00226B60` (`cSSXApp_loadInputMap`), and `0x00227E98` (`cSSXApp_preUpdate`), which makes
  the port-0 history update call used by the front end.
- `src/ai/rider.cpp`: the human input provider `0x00127998`, grab selection `0x001276F0`, rail Uber selection
  `0x00127848`, the vibration motor model `0x00125B18` and its gate `0x001278E8`, and the control-state getter
  `0x0011FEE8`.
- `src/replay/playbackman.cpp`: the accepted-command recorder `0x0026D178` / `0x0026D2B0`.
- `asm/1218.s` (unsplit): the computer-rider input method `0x0010A768` and its serialisers `0x0010A898`,
  `0x0010A8E8`.
- `asm/14B10.s` (unsplit): the air direction filter `0x001158B8` and the rail balance consumer `0x00113F38`.
- `src/fe/debugfe.cpp`: the front-end UI input methods starting at `0x0017FDF0`.

## Data flow

Per consumed input sample:

1. **Device read** `0x00326EB0`. Reads the pad and converts the packet to 24 float channels (next section).
   Device records go into a ring whose pointer is at `0x004A28A0` (gp-0x850): 30 entries of 0x190 bytes, each
   holding four 0x64-byte device records. The read cursor is at ring `+0x2EE0`, the write cursor at `+0x2EE4`.
   Because producer and consumer are decoupled by this ring, emulator frames, game ticks and consumed pad
   samples are not necessarily the same count.
2. **Button history** `0x00321298`. Updates one 0x1C-byte record per channel.
3. **Actions.** The compiled map evaluates action expressions on demand (VM `0x00325450`). `0x00320BF0` returns
   the float result, `0x00320C48` / `0x00321108` return `value != 0`.
4. **Command packing** (human rider) `0x00127998`. Packs actions into two words for the current control state,
   then calls `0x0026D178`, which records the accepted command.
5. **Decode.** The control-state update handler (see [rider-controllers.md](rider-controllers.md)) reads the
   fields it needs from the words.

## Pad packet and the 24 channels

The conversion inside `0x00326EB0` produces these channels:

| Indices | Channels |
|---|---|
| 0..3 | Select, Start, L3, R3 |
| 4..7 | D-pad right, left, up, down |
| 8..11 | Triangle, Circle, Cross, Square |
| 12..15 | L1, R1, L2, R2 |
| 16..19 | Right stick left, right, up, down |
| 20..23 | Left stick left, right, up, down |

- **Digital buttons.** Packet bytes 2 and 3 hold the button bits in the standard DualShock 2 layout. Bits are
  active low: a clear bit gives 1.0, a set bit 0.0.
- **Pressure mode.** Channels 4..15 instead use the twelve pressure bytes (packet bytes 8..19, in the order
  right, left, up, down, Triangle, Circle, Cross, Square, L1, R1, L2, R2) times the float `3B808081h`
  (about 1/255).
- **Sticks.** Packet bytes 4..7 are right X, right Y, left X, left Y. Each byte `b` is split into a negative and a
  positive channel, with integer division truncating toward zero:

```
negative = max(((79 - b) * 255) / 79, 0) * float(3B808081h)
positive = max(((b - 176) * 255) / 79, 0) * float(3B808081h)
```

- The result is an **axial dead zone**: bytes 79..176 read as zero on each axis independently, and there is no
  radial dead zone. Byte 0 is full left/up, 255 full right/down.
- The float multiplies round toward zero (the EE MUL.S behaviour).

## Button history (`0x00321298`)

The pad object holds the record count at `+0` (as read from memory) and the records from `+4`, one per channel at
stride 0x1C (`button[i] = pad + 4 + i*0x1C`).

| Offset | Field |
|---|---|
| `+0x00` | value (float, raw channel value) |
| `+0x04` | pressed (u32) |
| `+0x08` | released (u32) |
| `+0x0C` | held (u32) |
| `+0x10` | repeat (u32) |
| `+0x14` | repeat timer |
| `+0x18` | edge age |

Per sample:

```
value = sample                          // always updated
if edgeAge < 3: edgeAge += 1; pressed = released = 0      // held is left unchanged
else:
    h = value > 0
    if h != held: held = h; pressed = h; released = !h; edgeAge = 0
    else: pressed = released = 0
if held:
    if repeatTimer == 0: repeat = 1; repeatTimer = 24
    else: repeatTimer -= 1; if repeatTimer > 0: repeat = 0 else: repeat = 1; repeatTimer = 12
else: repeat = repeatTimer = 0
```

- After an edge, the next three consumed samples cannot produce another edge. Repeat fires immediately, then after
  24 samples, then every 12.
- A new record starts with edge age 0, so the first three samples of a fresh record cannot report an edge.
- **(PS2)** In practice the pad has been read for many frames before any race starts, so the history is settled
  (edge age 3) and a button held from the first race sample reports its press edge (for example the boost press
  bit `0x10000` of the control-0 command appears on the first tick it is held).
- The raw value stays available independently of the debounced flags. A bare button name in the map reads the
  raw value, not `held`.

## Input maps

### Files and selection

- `DATA/CONFIG/INPUT.MAP` is the Controller Settings "Default" layout, `DATA/CONFIG/INPUT2.MAP` the "Pro" layout.
  Both are expression files compiled at load by `0x00320E18` (`cInputMap_compileMap`). `0x00226B60`
  (`cSSXApp_loadInputMap`) registers the action names by index.
- The Controller Settings screen is FE.LUI `22control` (`cFEStateOptionsController`): Vibration 1P/2P and
  Controller 1P/2P, with the DualShock picture and Default/Pro labels.
- **(PS2)** In a race, the race copy of the Controller 1P setting at `0x00535B30` (1 = Pro) selects the Pro
  compiled map: the pad context's map pointer (`+4`) then points at the INPUT2.MAP compilation.

### Action indices

| Index | Actions |
|---|---|
| 0..6 | CruiseTurn, CruiseCrouch, CruiseBrake, BoardPress, BoardPivot, AttackLeft, AttackRight |
| 7..11 | PrewindTurn, PrewindSpin, PrewindFlip, AirAdjRotFB, AirAdjRotLR |
| 12..16 | LateSpin, RailSpin, Spin, Flip, WipeoutRecover |
| 17..22 | JumpPressed, JumpHeld, BoostPressed, BoostHeld, Tweak, OllieHeld |
| 23..26 | RailBalance, HandplantBalance, Handplant, GateAnticipate |
| 27..30 | UberGrind1..4 |
| 31..45 | Trick1..15 |
| 46 | ResetPath |
| 47..204 | camera, menu and editor actions; the rider provider never reads them |

The front-end UI actions are among the later ids: UIStart `0x70`, UISelect `0x71`, UIUp/UIDown/UILeft/UIRight
`0x72`..`0x75`, UINext `0x7A`, UIPrevious `0x7B`, UIOption `0x7C`,
UIMisc `0x7D`.

### Compiled map and the expression VM (`0x00325450`)

The compiled map object, as read by the evaluator:

| Offset | Meaning |
|---|---|
| `+0x04` | table of entry points, one word index per action |
| `+0x0C` | program length in words |
| `+0x14` | program words |

- **Instruction word.** Opcode bits 0..5, destination register bits 6..11, left operand bits 12..21, right operand
  bits 22..31. Evaluation starts at the action's entry point and ends at opcode 32, which returns register 0.
- **Operands.** 0..63 are registers. From 96 on, `index - 96 = button * 6 + property`, with property 0 value,
  1 held, 2 pressed, 3 released, 4 repeat, 5 bare name. Operands 64..95 do not occur in the first 27 actions.
- **Bare name.** Property 5 redirects to the context's default property, which `0x00325250` zeroes, so a bare name
  reads the raw `value`.
- **Flag properties** (held/pressed/released/repeat) are u32 converted with CVT.S.W plus the unsigned fix-up,
  rounding toward zero.
- **Opcodes used by the Default map:** 0 literal (the next program word is the float), 1 move, 5 `&&`, 13 SUB.S,
  16 MAX, 31 `!`, 32 return.
  - MAX (`0x003259C8`) is `right < left ? left : right`, so a tie (including +0 against -0) returns the right
    operand.
  - `&&` and `!` produce 1.0 or 0.0 from zero tests.
  - Subtraction rounds toward zero. Under a guard-bit add/sub model the raw difference can differ for some pad
    values, but never after the six-bit command quantisation, and no unquantised provider field subtracts two
    nonzero operands, so command words are the same either way.
- **Getters.** `0x00320BF0` returns the VM result; `0x00320C48` and `0x00321108` return `value != 0`.

### Default layout (INPUT.MAP)

Physical meaning of the gameplay actions:

| Action | Input |
|---|---|
| CruiseTurn | Turn: the MAX of D-pad and left stick per direction, right minus left |
| Spin | D-pad right minus D-pad left |
| PrewindSpin | D-pad |
| RailBalance | left stick right minus left stick left |
| AirAdjRotFB | left stick up minus left stick down |
| BoardPress, BoardPivot | right stick |
| JumpPressed / JumpHeld | Cross |
| BoostPressed / BoostHeld, Tweak | Square (Tweak is the same physical input as BoostHeld) |
| WipeoutRecover | Square, pressed edge |
| Handplant | Circle |
| AttackLeft / AttackRight | L1 / R1 |
| ResetPath | Select, pressed edge |
| UberGrind1..4 | L1, L2, R1, R2 held, each exclusive of the others (a combination is not another Uber identity) |
| Trick1..15 | shoulder combinations (see grab selection below) |
| LateSpin | literal 0: the Default map never sets the late-spin bit |

- NISSkip is `Cross.pressed`. It skips the current step of a skippable cutscene list (`0x00276F48` cuts to the
  next step without a fade).
- **(PS2)** The game's own "Basic Controls / Default" load screen (GL.LUI `110ctrl_load`) labels: grab board
  L1/L2 and R1/R2, Boost/Tweak Square, Jump Cross, Turn/spin/flip D-pad, Turn left stick, Reset Select.

### Pro layout (INPUT2.MAP)

**(PS2)** INPUT2.MAP differs from INPUT.MAP only in these gameplay expressions (Turn and Tilt are the MAX-combined
D-pad/left-stick differences; the Trick and UberGrind chords are identical):

| Action | Pro expression |
|---|---|
| PrewindTurn, Spin, Flip | 0 |
| PrewindSpin, HandplantBalance, AirAdjRotLR | Turn |
| PrewindFlip, AirAdjRotFB | Tilt |
| RailBalance | Cross (raw value) nonzero ? 0 : Turn |
| LateSpin | Cross (raw value) |
| RailSpin | 0 if abs(Tilt) < 0.5 or abs(Turn) > 0.2, otherwise Tilt |
| Handplant | Triangle |

In INPUT2.MAP, LookBack is mapped to Circle, but no code reads LookBack.

## Rider pointers

| Path | Meaning |
|---|---|
| `rider+0x77C` | motion owner |
| owner `+0xDE8` | input provider interface; the provider function is at interface `+0x0C` (this-adjust at `+0x08`, 0) |
| owner `+0xDF0` | pad context: `+0` pad object, `+4` compiled map |
| owner `+0xDF8` | accepted-command recorder (human riders only) |
| owner `+0xDE4` | control state, read by the provider through `0x0011FEE8` |

## Human input provider (`0x00127998`)

- Zeroes the 8-byte command, reads the control state through `0x0011FEE8` (motion owner `+0xDE4`), and switches
  through the 14-entry table at `0x00457EA0`. States 9 and 13, and anything >= 14 compared unsigned, produce two
  zero words.
- The control state is the only rider field it reads. The pad context is its input and the recorder call is a
  side effect.
- **Axes** are packed as `trunc(value * 31) & 63` (MUL.S toward zero, then CVT.W.S), after the map expressions.
  Controllers decode a field as a signed 6-bit integer times the float `3D042108h` (about 1/31), so full scale
  decodes to 0.99999994.
- **Flags** are boolean-getter results.
- **Grab identity** `0x001276F0`: the first active Trick1..15 as 0..14, otherwise -1. Stored as a signed byte in
  word0 bits 16..23. Index i corresponds to the shoulder mask (bits L1 1, L2 2, R1 4, R2 8):

| Grab | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Mask | 1 | 2 | 4 | 8 | 3 | 5 | 9 | 6 | 10 | 12 | 7 | 11 | 13 | 14 | 15 |

- **Uber identity** `0x00127848`: the first active UberGrind1..4 as 0..3, otherwise -1 (signed byte). Both
  selectors read only actions.
- **Neutral in states 4 and 5** is word0 = `00FF0000h`, because "no grab" (-1) goes into byte 2. A zero byte there
  is grab 0, not neutral.
- word0 bits 0..11 are always zero from the provider (the recorder uses them for the run length).
- The provider's exit block is at `0x00128630` inside `0x00127998`.

### Command layout per control state

Unlisted bits are zero. Axis fields are 6 bits unless noted.

| Control (update) | word0 | word1 |
|---|---|---|
| 0 cruise (`0x00131620`) | 12 ResetPath, 13 Handplant, 14 JumpPressed, 15 JumpHeld, 16 BoostPressed, 17 BoostHeld, 18 AttackLeft, 19 AttackRight, 20..25 CruiseTurn, 26..31 CruiseCrouch | 0..5 CruiseBrake, 6..11 BoardPress |
| 1 (`0x0012FC80`) | 12 ResetPath, 13 BoostPressed, 14 BoostHeld, 15 JumpHeld, 16 JumpPressed, 17 OllieHeld, 18..23 CruiseTurn, 24..29 RailBalance | 0..5 BoardPress, 6..11 BoardPivot |
| 2 prewind (`0x0012E9B8`) | 12 ResetPath, 13 JumpHeld, 14 BoostHeld, 15..20 PrewindSpin, 21..26 PrewindFlip | 0..5 PrewindTurn, 6..11 RailBalance |
| 3 soft collision (`0x0012E778`) | 12 ResetPath, 13 BoostPressed, 14 BoostHeld, 15..20 CruiseTurn, 21..26 RailBalance | - |
| 4 passive air (`0x0012F730`) | 12 ResetPath, 13 Handplant, 14 AttackLeft, 15 AttackRight, 16..23 grab (signed byte), 24..29 CruiseTurn | 0..5 CruiseCrouch |
| 5 air (`0x00133308`) | 12 ResetPath, 13 Handplant, 14 Tweak, 15 LateSpin, 16..23 grab, 24..29 Spin | 0..5 Flip, 6..11 AirAdjRotFB, 12..17 AirAdjRotLR, 18..19 board-press step |
| 6 race start (`0x0012BF68`) | 12..17 GateAnticipate (no ResetPath bit) | - |
| 7 rail (`0x00131D30`) | 12 ResetPath, 13 JumpPressed, 14 JumpHeld, 15 BoostPressed, 16 BoostHeld, 17..24 Uber identity (signed byte), 25..30 RailBalance | 0..5 RailSpin, 6..11 BoardPress |
| 8 crash (`0x0012CB68`) | 12 ResetPath, 13 WipeoutRecover | - |
| 9 reset (`0x0012F398`) | - | - |
| 10 (`0x0012C678`) | 12..17 CruiseTurn | - |
| 11 handplant (`0x00132A30`) | 12 ResetPath, 13 Handplant, 14..19 HandplantBalance | - |
| 12 rail Uber (`0x00136508`) | 12 ResetPath, 13 BoostPressed, 14 BoostHeld, 15..22 Uber identity, 23..28 RailBalance | - |
| 13 | - | - |

Notes on the fields:

- **Board-press step** (control 5, word1 bits 18..19): the raw BoardPress value < -0.5 gives 3 (-1), > 0.5 gives
  1, otherwise 0.
- **Air adjust axes** (control 5): word1 bits 6..11 are AirAdjRotFB (action 10, written at `0x00128500` /
  `0x00128528` inside `0x00127998`) and bits 12..17 are AirAdjRotLR (action 11). An earlier reading of these two
  fields had them swapped; the later provider round-trip analysis corrects it to this order.
- **Control 3 bits 21..26** carry RailBalance (left stick only), not a board-press value and not CruiseTurn
  (which includes the D-pad).
- **Control 5 bit 14** is Tweak, the same physical input as BoostHeld.
- **Bit 12** in every state that has it is ResetPath (Select pressed).
- **GateAnticipate** (control 6) is packed at `0x00127DFC`..`0x00127E04` inside `0x00127998`.
- **Control 4** is written by the case at `0x00128280` inside `0x00127998`. It uses CruiseTurn, CruiseCrouch, AttackLeft,
  AttackRight, Handplant and the grab identity. These are not the control-5 spin/flip/boost fields. The identity is
  compared as a signed byte, -1 meaning no grab.

## Accepted-command recording (`0x0026D178`, `0x0026D2B0`)

After packing, the provider calls `0x0026D178`. In ordinary gameplay it dispatches to `0x0026D2B0`, which appends
the command to a run-length-encoded history. Both are in `src/replay/playbackman.cpp`, so this is probably the
replay recorder (unconfirmed).

```
recorder     = *(owner + 0xDF8)
recordCount  = *(recorder + 0x00)
recordBuffer = *(recorder + 0x0C)
record[i]    = two little-endian u32 words
runLength    = word0 & FFFh
command0     = word0 & FFFFF000h        // word1 is stored unchanged
```

- The computer-rider provider never calls these functions. On a computer rider, owner `+0xDF8` is a float
  parameter, not a recorder pointer.
- **(PS2)** Recorded histories show the expected run structure. For example, a glide into a full jump charge is
  one neutral tick, one press-transition tick, 28 held ticks and one release tick. Different recordings of the
  same scripted input do not always start at the same point: some runs consumed one extra neutral sample at the
  start.

## How the controllers use the words

- **Jump request.** Cruise uses a latch at `rider+0x360`: JumpPressed always requests control 2, JumpHeld alone
  requests it only while the latch is zero. Control 2 releases when JumpHeld is absent, including after a
  pressed-only pulse.
- **Prewind release.** On Cross release, `0x0012EA30` (inside `0x0012E9B8`) snaps the filtered prewind with an
  angular step of float `3F490FDCh` (about pi/4) and a dead zone of 0.2, then performs the takeoff and enters
  control 5 in the same handler.
- **Air direction** `0x001158B8`: dead zone and angular snapping of the spin/flip input pair.
- **Late spin** (only reachable with the Pro map): the air controller's command-prefix modes at `0x001333E0`
  inside `0x00133308`. Mode 0 plus LateSpin with an adjust input goes to mode 2, spin/flip input goes to mode 0,
  mode 2 without LateSpin goes to mode 1, and modes 1/2 take spin/flip from the air-adjust axes. **(PS2)** A Pro
  race replay matches the PS2 command words and state through the whole run; replaying the same pad with the
  Default map diverges partway through.
- **Rail balance (PS2).** Every consumer passes RailBalance to `0x00113F38` unnegated, with only a scale multiply
  between decode and call, so the stick pushed left (negative) slides the rider toward screen left. Call sites:

| Controller | Call site | Field |
|---|---|---|
| Control 7 | `0x00131E00` inside `0x00131D30` | word0 bits 25..30 |
| Control 12 (Uber) | `0x001365DC` inside `0x00136508` | word0 bits 23..28 |
| Control 3 on a rail | `0x0012E850` inside `0x0012E778` | word0 bits 21..26 |
| Control 2 on a rail (style not 0) | `0x0012EC1C` inside `0x0012E9B8` | word1 bits 6..11, clamped to +-0.5 |

- With the left stick at -0.6, control 7's word0 bits 25..30 hold 54 (-10/31).
- **Reset (PS2).** ResetPath (bit 12, mask `0x1000`) leads to the forced reset `0x00116120` from ground, air,
  crash and rail states.
- **Crash recovery (PS2).** Control 8 recovers on WipeoutRecover (Square pressed), not on a held jump.
- **Cutscenes.** Start does not pause during a cutscene (`0x00231AB8`); only the NISSkip edge acts.

## Computer riders

The motion owner of a computer rider points `+0xDE8` at the interface object `0x004585F0`. Its input method is
`0x0010A768` (this-adjust 0), with serialisers `0x0010A898` and `0x0010A8E8`, which save the common owner and
then a 0x150-byte extension at `+0xDF0..+0xF40`. The pad-context layout above does not apply.

- `0x0010A768` clears the 8-byte command, calls the pacing logic `0x0010DEF0` and `0x00120090`, reads the current
  control and dispatches through the table at `0x00456A30`. Controls 3 and 9..13 give a zero command.
- When the control is not 5, it clears owner `+0xE34` afterwards.
- The producers write the same per-control layouts as the human provider.
- The actor vtables differ too: the computer rider's feedback hooks at `+0x80..+0x9C` are no-ops (the human ones
  feed the vibration values below). See [ai-racers.md](ai-racers.md).

## Front-end UI input

The front end reads the pad through the same history update: `0x00321298` is called for port 0 from `0x00227E98`
(`cSSXApp_preUpdate`). The UI input object (FEUIInput, vtable `0x0046D1D0`, methods from `0x0017FDF0`) exposes
the map's UI actions:

| Vtable slot | Action | Default binding |
|---|---|---|
| `+0x10` IsPressed(id) | id 0..3 UIUp/UIDown/UILeft/UIRight, 4..7 UIUp2..UIRight2 (right stick) | D-pad or left stick, with repeat |
| `+0x18` | UIStart | Start |
| `+0x20` | UISelect | Select |
| `+0x28` | UINext | Cross or Start |
| `+0x30` | UIPrevious | Triangle |
| `+0x38` | UIOption | Square |
| `+0x40` | UIMisc | Circle |
| `+0x88`..`+0xA0` | UIUp/UIDown/UILeft/UIRight (list box, slider and states) | |

## Vibration

- **Motor model** `0x00125B18`, per tick in single precision, with v0 = owner `+0xDFC` and v1 = owner `+0xE00`:
  - decay: v0 = v0 * 0.9133333 - 18.518518, v1 = v1 * 0.9916667;
  - large motor: f = max((v1 - 0.5) * 0.01, (v0 - 2) / 972.2222), sent as the byte f * 205 + 50;
  - small motor: switched on from the terms (v1 - 70) * 0.00625 and (v0 - 100) / 5000 (the exact comparison is
    unconfirmed).
- **Gate.** `0x00127900` inside `0x001278E8` runs the model only when the vibration option is on (checked through
  `0x001474E8`) and the game state is below 10. Pause, quit and the Off setting stop the motors through
  `0x00326CF0`.
- **Impact input** (actor vtable `+0x88`): owner `+0xDFC` = max(v0, a). Callers include the landing award at
  `0x0010EAD8` inside `0x0010E910` (0.5 times the landing speed, for board, rail and instance landings), the crash
  entry `0x0010EB78` inside `0x0010EB30`, obstacle notifications `0x00105E7C` inside `0x00105D98`, instance contacts
  `0x00105C30` inside `0x001057B8`, and the wipeout impacts at `0x0012D28C` (inside `0x0012D160`), `0x0012D6F8`
  (inside `0x0012D4E8`) and `0x0012D8A0` (inside `0x0012D848`).
- **Slide input** (actor vtable `+0x90`): owner `+0xE00` = a. Callers: the crash slide at `0x0012D23C` inside
  `0x0012D160` (0.5 times the playback base from `0x0012E528`) and the ground get-up at `0x0012D8E8` inside
  `0x0012D848` (2 * (1 - clip progress)).
- **(PS2)** v0, v1 and both motor values were compared on every tick of several recorded runs and match.

## Constants

| Value | Meaning |
|---|---|
| `3B808081h` | about 1/255: pressure and stick scale |
| bytes 79..176 | stick dead zone per axis |
| 3 samples | edge suppression after an edge |
| 24 / 12 samples | first repeat delay / repeat interval |
| `3D042108h` | about 1/31: command axis decode scale |
| 31, mask 63 | command axis encode (toward zero) |
| 30 x 0x190 bytes | device ring (four 0x64-byte device records per entry) |
| `3F490FDCh`, 0.2 | prewind snap step and dead zone |
