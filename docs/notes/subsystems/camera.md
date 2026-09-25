# Cameras

Each player view in SSX 3 is driven by a camera object that owns a director: a weighted list of camera algorithms
(the automatic chase camera DEFAULT_3 and its Near/Far siblings, the handplant camera, the post-race orbit, trigger
and replay cameras). Once per 60 Hz game tick the director steps and blends its algorithms, the camera lifts the
blended eye clear of terrain, adds shake, clamps fov/near/far and hands eye, look-at and lens values to the renderer.
The cameras run near the end of the race game update, after the riders and the world passes, so they see every rider
after that tick's physics, contact and pose passes. All positions are centimetres with Z up; speeds are cm/s unless
given in km/h.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

Hex constants that are not addresses are written with an `h` suffix (for example `E9507Ch`). Vtable offsets are the
offset of the function-pointer word (entries are 8 bytes, so a slot quoted elsewhere as "slot 0x28" has its function
pointer at `+0x2C`); rider-target getter "slots" below keep the entry offset used by the source notes.

## Where it lives

- `src/camera/camera.cpp`: the bulk of the chase-camera code: the DEFAULT_3 base helpers (`0x00162568` ..
  `0x00168150`), the director update and requests (`0x00161AB0` .. `0x001624E8`), the per-camera tick `0x0015DF98`,
  the compositor `0x0015E668`, terrain clearance `0x0015EE00`, shake (`0x0015E360`, `0x0015E460`, `0x001656B0`,
  `0x00165938`), the rider-target getters (`0x0015F710`, `0x0015F780`), `0x0015DC70` (`cCamera_cCamera`) and
  `0x0015DE60` (`cCamera_init`).
- `src/camera/cameraalgolist.cpp`: the director's node list: `0x0015C988` (`cCameraAlgoList_insert`), `0x0015CA50`
  (unlink), `0x0015CB08` (push).
- `src/camera/cameracontroller.cpp`: the set-target broadcasts `0x0015CC70` and `0x0015CCF0`, the occlusion gate
  `0x0015D020`, `0x0015CBA0` (`cCameraController_cCameraController`).
- `src/camera/cameraalgorithms.cpp`: the algorithm factory `0x0015D078`
  (`cChaseCameraController_createChaseAlgorithmBlend`) and the restart `0x0015DB58`.
- `src/camera/trigger/cameratriggerfactory.cpp` (per the current split): the per-algorithm vtable entries: DEFAULT_3
  constructor `0x00176D68`, finish entry `0x00176DE0`, update driver `0x00176E10`, set-target `0x00176FE0`; SPOKE
  `0x00177E50`; POST_RACE_1 `0x001789E8` .. `0x00178E90`; the replay camera constructor `0x00174190`.
- `src/camera/trigger/cameratriggerman.cpp`: trigger firing (`0x0016E1D8`). `src/camera/script/scriptcontroller.cpp`
  holds the script camera controller, which the sources here do not cover.
- `src/bx/cubicspline.cpp` and `asm/21E5A8.s`: the natural cubic spline used by the jump and swing cameras.
  `src/bx/ps2main.cpp`: sincos `0x0031BE50`, cos `0x0031C040`, asin `0x0031C128`, atan `0x0031C228`, and the output
  transform helpers `0x0031B748` / `0x0031B7A8`.
- Callers and neighbours: `src/main/gameload.cpp` (race game update `0x002306B8`, splash getter `0x002306A8`),
  `src/main/gamerender.cpp` (`0x0022E840` `cGameViewMan_updateAll`, the per-camera loop), `src/visualfx/lensfx.cpp`
  (`0x002ED490`, `0x002EE3B8`), the camera splash in the unsplit `asm/1F1548.s`, and the projection/viewport setters
  `0x00376A70`, `0x00376C58`, `0x00377950` (in `src/render/particle.cpp` per the current split).

## Object model

Pointer chains below use G = `*(0x004A28A8)` (gp-0x848, the game object) and S = `*(G+0x84)`.

- **Camera count.** `*(*(S+0x84)+0x10)`.
- **Director.** `*(*(*(S+0x84)+4)+0xA0)`, vtable `0x0045B908`. It owns the list of algorithm nodes (weight, rate,
  smoothed weight at node `+0x0C`, algorithm pointer), the current type at `+0x18`, an override request type at
  `+0x2C`, and a flags word (bit 1: lock; bit 2 is set by the SPOKE latch). The finish path also tests an "override
  bit 0" (which word holds it is not recorded). The decomp names in this range
  (`cCameraAlgoList_insert`, `cChaseCameraController_createChaseAlgorithmBlend`) suggest the director is the chase
  camera controller and its node list a `cCameraAlgoList` (unconfirmed).
- **Outer camera.** Holds the composited result, terrain lift and shake state. The set-target broadcasts reach it as
  director`+0x10`; that it is also the per-camera object updated by `cGameViewMan_updateAll` is inferred. It embeds a
  DEFAULT_3-layout algorithm at `+0xC0` (field table below).
- **Algorithms.** Heap objects sharing a base layout used by DEFAULT_3 and POST_RACE_1 (fov/near/far at `+0x00`,
  type at `+0x0C`, look-at `+0x20`, eye `+0x40`, output eye `+0x60`, reset-pending flag `+0x2F0`). DEFAULT_3 is
  `0x390` bytes. During a race two DEFAULT_3 allocations exist: the director node's, which is the one that updates,
  and a second one whose role is not described (PS2).
- **Target.** Each algorithm reads its rider through a target interface of virtual getters (see "Camera inputs").

### Director vtable `0x0045B908`

| Offset | Function | Role |
|---|---|---|
| `+0x14` | `0x00161BB8` | director update |
| `+0x1C` | `0x0015CC70` | set-target for one rider id: every node algorithm's set-target (the algorithm acts only if its target id matches), then `0x0015E030` and `0x002F41A8` on director`+0x10` |
| `+0x24` | `0x0015CCF0` | set-target on every node with no rider check, then `0x0015E030` and `0x002F41A8` |

`0x0015E030` runs `0x00166F28`, the set-target of the embedded algorithm at `+0xC0` (always, with its own target).
`0x002F41A8` is described in the source as a viewport render object's vt`+0x74` call.

### Algorithm types (`+0x0C`)

| Type | Algorithm | Notes |
|---|---|---|
| `3Ch` | Near chase | Same code as DEFAULT_3 with different gp constants (PS2). Pairing with the name DEFAULT_2 inferred. |
| `3Dh` | the value the transition code resets its guard to | presumably the default Mid chase DEFAULT_3 (unconfirmed) |
| `3Eh` | Far chase | Same code, other constants (PS2). Pairing with DEFAULT_4 inferred. |
| `42h` | SPOKE, `0x00177E50` | handplant camera |
| `44h` | POST_RACE_1 | post-race orbit |
| `4Ah` | special | smoothed weight forced to 0; a type-`4Ah` head is copied outright by the compositor |
| `4Ch` | request issued by the outer camera's constructor | the chase camera it produces has had two set-targets |
| `5Bh` | trigger camera | `0x90`-byte object, constructor `0x00174190` when the game state is 1..9; seen replacing the chase camera in the replay (PS2) |
| `5Dh` | override request | used by the replay lock; 10 s auto-revert in game states 1..9 |

Other algorithms named in the sources but not described here: Manual, Spline, SUPERPIPE, Relative and replay-clock
cameras.

## Per-tick call order

The race game update `0x002306B8` (game vtable `0x0047D130`, slot `+0x14`) runs world group 1, groups 5 and 6, the
rider manager (all riders in slot order: controllers, physics, contact programs, effect passes, section pass), group 2
(snowfall, flags, the camera splash objects), group 3 (environment, including the per-camera region refresh
`0x002F00A0`), script manager, crowds, group 4, and only then the cameras: at `0x00230D7C` it calls `0x0022E840`
(`cGameViewMan_updateAll`) unless the game-flow state word equals 3. For each camera the vtable pointer is at camera
`+0x90` and entry `+0x1C` is `0x0015DF98`, which reaches the compositor `0x0015E668` and the shake `0x0015E460`.

- The branch at `0x00230D24` inside `0x002306B8` (probably the frozen or pause path, not verified) runs groups 5, 3
  and 4 and the cameras, skipping groups 1, 2, 6, the riders, scripts and crowds.
- The alternate update body `0x00244E60` runs the cameras at `0x002450A0`, in the same pass order.

Reconstructed per-camera order: director update (each stepped node: set-target first if its `+0x2F0` is set, then the
algorithm's update and finish), compositor, terrain clearance, shake, angle recompute, fov/near/far clamps.

**Timing.** No time scale enters the camera. Every constant is per frame (1/60 is used as 0.016666668). The race
clock tick the camera reads comes from `0x001298C8`, which returns the rider manager's total-tick counter
(`*(*(S+0x0C)+0x08)` with S as above).

**Debug word** `0x004A2A50` (gp-0x6A0):

| Bit | Effect |
|---|---|
| `1h` | disables the camera controller update and the shake |
| `2h` | skips world group 1 (and the two passes after it) |
| `4h` | skips group 3 (environment) |
| `10h` | skips group 2 (including the camera splash) |

## Director

### Update `0x00161BB8`

1. **Transitions `0x00161AB0`.** Resets its guard to `3Dh`. Motion mode 5 (handplant) latches SPOKE through
   `0x001621A8` with a fade rate of 1.2/60 or 0.6/60 (which condition picks which is not recorded). Above 35 km/h the
   latch is released through `0x00162218` with rate 1/150, fading a fresh DEFAULT_3 in over 150 frames.
2. **Node pass** (the block `0x00161BF0` .. `0x00161D7C` inside `0x00161BB8`). The head node is stepped through
   `0x001624E8` (second argument 0) and its weight ramps up to 1 at its own rate. Older nodes ramp down to 0 at the
   **head's** rate. Each weight w is smoothed as min(1, 3w^2 - 2w^3) into node `+0x0C` (forced to 0 for type `4Ah`).
   A node whose weight or smoothed weight is <= 0 is unlinked (`0x0015CA50`) before stepping.
3. **Auto-revert timer** (the block `0x00161D80` .. `0x00161E30` inside `0x00161BB8`). A 10 s revert, only for a `5Dh`
   request and only in game states 1..9.

### Node step `0x001624E8`

If the algorithm's reset-pending flag `+0x2F0` is set, set-target runs first; then the algorithm's update and finish.

### List changes and requests

| Address | Behaviour |
|---|---|
| `0x00161E58`, `0x0015C988` (`cCameraAlgoList_insert`), `0x0015CB08` | insert and push: director `+0x18` = new type; on an empty list the rate is 1; a rate of exactly 1 clears the list first; the push runs the new algorithm's set-target, then inserts it at weight 1 (rate 1) or 0 |
| `0x0015D078` (`cChaseCameraController_createChaseAlgorithmBlend`) | activate: creates the algorithm for the requested type (DEFAULT_2/3/4, POST_RACE_1 among others); lock bit 1 forces rate 1; set-target runs **twice** (once in the push, once in the factory tail) |
| `0x00162060` | override request (type argument) |
| `0x00161FA0` | override selection (sets `+0x2C`) |
| `0x00161EF0` | select: instant cut |
| `0x00162290` | restore (called by the results overlay `0x00234008`) |
| `0x00162258` | race finish: pushes POST_RACE_1 with fade rate 0.016793445, unless override bit 0 is set |
| `0x0015DB58` | restart: clears the flags and latch, instant cut (two set-targets), then the director's set-target-all entry (`0x0015CCF0`, a third set-target); sets the outer camera's lift to 0 and `+0x4A4` = 1 |

## Compositor `0x0015E668`

- With one node, or when the head node has type `4Ah`, the node's result is copied exactly.
- Otherwise it takes running weighted means over the nodes whose smoothed weight exceeds 1e-4, with k = s / sum(s):
  eye from each algorithm's `+0x60`, look-at from `+0x20`. Fov, near and far are running means over the raw weights,
  skipping nodes with weight 0.
- The fov/near/far results are clamped against the outer camera's limits. The far value is also capped by the
  lens/region far cap from `0x002EE3B8`; far came out as min(30000, far cap) and matched the global at `0x004A3B68`
  (gp+0xA78) (PS2).
- Render-listener notifications go through `0x002ED490`, which the tint notes also list as part of the region tint
  driver (call site not recorded).

## Terrain clearance `0x0015EE00`

- Probes vertically by plus/minus a half length around the eye, accumulates a lift (outer `+0x460`) that decays by
  0.97 per tick, and re-projects the eye; the re-projected eye lands in outer `+0x20` (PS2). The last probe normal is
  kept at outer `+0x470`.
- The probe is a swept terrain query through `0x0032E100` with query kind 2 and a preferred fraction of 0.5 (passed at
  `0x0015F0C8` inside `0x0015EE00`), so competing hits are ranked by distance to the probe midpoint. Results come back
  through `0x00336850`.
- Kind 2 makes the query core `0x0032B6E0` call the query's `+0x44` refinement callback `0x0032E9A0` after the coarse
  intersection (around `0x0032BE28` .. `0x0032BE70` inside `0x0032B6E0`), returning a refined point, normal and UV
  while keeping the coarse fraction.
- Both large-push rejection branches (at `0x0015F160` and `0x0015F198` inside `0x0015EE00`) use a 150 cm limit.
- A line-of-sight occlusion branch exists for override cameras only: its gate `0x0015D020` is false for the automatic
  camera. Its state lives at outer `+0x490`, `+0x4A0`, `+0x4A4`.

## Shake

- **Request** `0x0015E360` (request shake: index, fade, scale) stores a request at outer `+0x450` .. `+0x45C`. The
  ground crash handler `0x0012D160` requests at `0x0012D218`: index 4, fade 0, scale = clamp(speed * 0.036 / 100,
  0, 1) (km/h over 100), only when the rider's device index (rider `+0x870`) is >= 0 and rider `+0x87C` is non-zero.
- **Apply** `0x0015E460`: a random-walk displacement of the look-at, scaled by boost and speed. The walk state is in
  the embedded algorithm at `+0x254` .. `+0x2B4` and `+0x2EC` (outer `+0x314` .. `+0x374`, `+0x3AC`). In the fade
  branch the store `+0x2EC` = requested happens regardless of the branch outcome.
- **Start** `0x001656B0` makes 12 draws from the presentation random stream (`0x003177F0` `BXrand__Fv`, state
  `0x004FF018`) when a shake starts. **Tick** `0x00165938` makes 6 draws per shaking tick and advances only the first
  set of timers (`+0x278` .. `+0x280`); the second-octave timers (`+0x2A8` .. `+0x2B0`) never tick, so that octave is
  inert.
- The cameras run after every other in-race consumer of this stream (snow particles, stage effects, the lightning,
  crowds, the camera splash), so the shake depends on all of their draws that tick. At one shake start the walk
  equalled draws 8..19 of that tick (PS2). Over a 12002-tick Snow Jam race with five computer riders the shake drew
  356 + 36 numbers (PS2).
- The shake appears to be suppressed in some race states; the condition is unconfirmed.
- `0x00160028` and `0x00160130` (camera code, labelled director nodes in the sources) also call `BXrand__Fv` but made
  no draws during a race.

## Outer camera fields

| Offset | Field |
|---|---|
| `+0x00` / `+0x04` / `+0x08` | fov / near / far (final) |
| `+0x0C` / `+0x10` / `+0x14` | pi/4, 30, 30000; `+0x14` is the far maximum (PS2), the other two presumably the matching fov and near limits (unconfirmed) |
| `+0x20` | eye after terrain lift and re-projection (PS2) |
| `+0x90` | vtable pointer used by the per-camera loop (that this is the same object is inferred) |
| `+0xC0` | embedded DEFAULT_3-layout algorithm: look-at `+0xE0`, eye `+0x100` |
| `+0x314` .. `+0x374`, `+0x3AC` | shake walk (embedded `+0x254` .. `+0x2B4`, `+0x2EC`) |
| `+0x450` .. `+0x45C` | shake request |
| `+0x460` | accumulated terrain lift |
| `+0x470` | last probe normal |
| `+0x490`, `+0x4A0`, `+0x4A4` | occlusion-branch state (restart sets `+0x4A4` = 1) |

The DEFAULT_3 object words, the compositor look-at and eye, lift, probe normal, shake request and shake walk were
matched against the PS2 on every tick of captures covering event start, racing with computer riders, the Near, Mid
and Far distances, air tricks, rail balance, pipe air and a Metro City run (PS2; the shake walk given the same random
stream position).

## DEFAULT_3 chase camera

### Vtable entries

| Offset | Function | Role |
|---|---|---|
| `+0x1C` | `0x00176FE0` | set-target |
| `+0x2C` | `0x00176E10` | update driver: calls the 15 base helpers with DEFAULT_3's gp constants |
| `+0x3C` | `0x00176DE0` | finish entry: calls `0x00166228` with the finish constants |
| `+0x44` | `0x00166228` | base finish |
| `+0x4C` | `0x001624E8` | node step |

`0x00166228` and `0x001624E8` sit at the same two offsets in every algorithm vtable. Constructor chain:
`0x001622B0`, `0x00162318`, `0x00176D68`.

### Lifecycle

- **Construct** sets the defaults in the layout table below (fov pi/4, near 10, far 30000, follow distance 200).
- **Set-target** `0x00176FE0`: `0x00166C60` resets fields and runs an update and a finish; `0x00166550(559.744, 300)`
  sets the offset direction; then one more update. So a set-target runs two updates and one finish with the current
  rider state. When reached through `0x0015CC70` it acts only if the algorithm's target rider id matches.
  - Seeds: travel direction `+0x80` = normalize(fwd * 559.744 - Z * 300); `+0x1A0` = fwd * 250; `+0x1C0` = fwd * 2;
    lag-filtered velocity `+0x100` = velocity with z = 0; eye offset `+0x1D4` = 61.687962.
  - `0x00166C60` re-reads the target's forward (getter slot `0x20`) into the fwd * 250 scratch just before storing
    `+0x1B0`, so `+0x1B0` ends up equal to the rider forward itself, not fwd * 250. Every countdown and ready-screen
    savestate shows `+0x1B0` = the unit forward (PS2). It matters when the rider moves slower than 1 km/h.
- **Step** (per tick, via `0x001624E8`): update driver `0x00176E10`, then finish `0x00176DE0`.
- **Snap guard** `0x00168150`: when |look-at - eye| < 20 or > 1e20 it resets look-at and eye and sets `+0x2F0`, so the
  next step runs set-target first.
- **Event start.** The countdown DEFAULT_3 state matches four set-targets more closely than the two (constructor
  path) or three (restart `0x0015DB58`) the code gives; the difference is camera history from before the countdown,
  not an extra set-target call (PS2).
- In a normal race the director never left a single DEFAULT_3 node from event start through racing (PS2).

### Update stages

The driver `0x00176E10` calls these in order:

| Stage | Function | Behaviour |
|---|---|---|
| 1 | `0x00162568` | velocity acquisition, lag filter whose strength depends on vertical motion, scratch context |
| 2 | `0x00162998` | mode-5 frame counter `+0x2C0` |
| 3 | `0x00162A20` | airborne latch `+0x2D4`, wall-launch arm `+0x2D0`, 15-frame take-off countdown `+0x2C4` (decremented before its test) |
| 4 | `0x00162B80` | look-at = head bone position |
| 5 | `0x00162C78` | filtered travel direction `+0x80` with a PID-adapted coefficient over a 5-entry history |
| 6 | `0x00163010` | follow distance `+0x1D0` from speed and boost; eye placement |
| B1 | `0x00163270` | filtered eye vertical offset `+0x1D4` (speed drop, boost, crouch) |
| B2 | `0x001633B0` | fov filter (`+0x1DC` fov scale) |
| B3 | `0x00163450` | mode-5 hold/blend and extra eye height `+0x2B8` |
| B4 | `0x00162B90` | look-at height `+0x1E4` |
| B5 | `0x001635F8` | jump camera: two natural cubic spline pairs (phase A and B), landing settle |
| C1 | `0x00164878` | wall-launch swing-around (clamped 9-knot ease spline), return blend, 60 % guard |
| C2 | `0x001646A0` | pull-behind filter `+0xC0` in motion mode 4 (rail) |
| C3 | `0x001641C0` | proximity push from rider `+0x5AC` (300 forward, 100 up, 600 side, factor 0.98) |
| C4 | `0x001643A8` | slow-speed lock state machine (15 km/h, 1.5 s in, 1.5 s out) |

Finish `0x00166228` calls `0x00166640`, `0x001662A0`, `0x00166530` and `0x00166F90`, which compute the yaw `+0x50`
and pitch `+0x54`, the pitch lag filter with an angle limit (`+0x1D8`), the snap guard and the output eye `+0x60`.
`0x00166F90` also builds the output quaternion (conjugated) and matrix, together with `0x0031B748` / `0x0031B7A8`.
The renderer's view is set from Euler angles by `0x00395750`; how the camera output reaches it is unconfirmed. The
forward vector uses the same VU arithmetic as `0x001668B8`, and the render axis permutation lives at `0x004C53A0`.

Stage notes:

- **Stage 5 PID.** Three 5-float rings (X, Y, E) at `+0x340`, `+0x354`, `+0x368`, index `+0x37C`; gains Kp
  0.011394524, Ki 0, Kd 0.0012785085 at `+0x380` .. `+0x388`. The quantity fed in is the alignment angle itself,
  computed with asin `0x0031C128`; during a hard left turn ring X held about 0.54 .. 0.57 rad (PS2).
- **B3 hold/blend.** The offset `+0xB0` is captured **while** the rider is in motion mode 5 and the blend timer
  `+0x1E0` runs after mode 5 ends (`+0x1E0` is stored before its threshold test). In cruise `+0x1E0` stays 10 and
  `+0xB0` is never written (PS2).
- **B1 and B4** use the filtered crouch on the ground and keep their previous terms in the air.
- **B5 jump camera.** Over 121 consecutive updates of a jump (81 airborne, 40 grounded), carried continuously from
  one seeded state, every algorithm word matched the PS2 (PS2).
  - On the first airborne frame the take-off countdown goes 15 -> 14, the phase-A spline pair is built with offsets at
    2/60 s, and `+0x2CC` records the tick (PS2).
  - The early prediction branch (around `0x001636BC` .. `0x00163708` inside `0x001635F8`) also shortens the countdown
    when the trajectory status becomes active.
  - The recent-air test compares tick - `+0x2CC` < 31 (signedness unconfirmed).
  - The landing block (`0x00163E8C` .. `0x00163FD4` inside `0x001635F8`; `0x00163FD8` is the common successor, and the
    unlatched path skips `0x00163FD4`) handles touchdown and the offset decay. It has boundaries at 1.2 s and 2.2 s and
    at 1.05 rad and 1.4 rad, and reads the landing angle lazily through the target getter. The decay starts at 0.92;
    with a landing angle of 0 it is 0.93 (PS2).
  - Splines are `cCSICubicSpline` objects (natural cubic splines with an evaluation cache):
    `0x0031D5A8`, `0x0031D5E8`, `0x0031D660` (`cCubicSplineInterpolant_initCommon`), `0x0031D700`, `0x0031D738`,
    `0x0031D7E0`, `0x0031D8B0`, `0x0031DEE0`. The knot tables are at `0x0049C658` (gp-0x6A98) and `0x0049C700`
    (gp-0x69F0).
- **C1 swing.** Uses the ease spline at `+0x334` with knots at `0x0049C7EC` (gp-0x6904) and timers/angle
  `+0x22C` .. `+0x244`. It is reached only after a near-vertical wall launch; the accumulation order of its VU
  quaternion rotation is unconfirmed.
- **C4 lock states** (`+0x300`): 0 in, 2 locked, 1 out, 3 idle. Lock view vector `+0x1A0`, blend `+0x248`.

### Object layout (`0x390` bytes)

| Offset | Field | Constructor / set-target value |
|---|---|---|
| `+0x00` / `+0x04` / `+0x08` | fov, near, far | pi/4, 10, 30000 |
| `+0x0C` | algorithm type | |
| `+0x20` / `+0x40` | look-at / eye | eye (0,0,0,1) |
| `+0x50` / `+0x54` | yaw / pitch | 0 |
| `+0x60` | output eye (w = 1) | |
| `+0x80` | filtered travel direction (not unit length) | normalize(fwd * 559.744 - Z * 300) |
| `+0xA0` / `+0xB0` | head copy / mode-5 saved offset | |
| `+0xC0` | pull-behind filter | 0 |
| `+0xF0` | Z x fwd (set at init only) | |
| `+0x100` | lag-filtered horizontal velocity | velocity with z = 0 |
| `+0x110` .. `+0x180` | swing-camera vectors | set-target zeroes `+0x170` (whether the whole block is cleared is unconfirmed) |
| `+0x1A0` | slow-lock view vector | fwd * 250 |
| `+0x1B0` / `+0x1C0` | last velocity / last raw velocity | rider forward (see above) / fwd * 2 |
| `+0x1D0` | follow distance | 200 (constructor only) |
| `+0x1D4` | eye vertical offset | 61.687962 |
| `+0x1D8` | filtered pitch | 0 (constructor only) |
| `+0x1DC` | fov scale | 1 |
| `+0x1E0` | mode-5 blend timer | 10 |
| `+0x1E4` | look-at height | 0 |
| `+0x1E8` / `+0x1EC` | boost bump / last boost | 0 |
| `+0x1F4` .. `+0x228` | jump camera clocks, gains, offsets, landing decay, take-off ramp | decay 0.92, ramp 1 |
| `+0x22C` .. `+0x244` | swing timers and angle | 0 |
| `+0x248` | lock blend | 0.5 |
| `+0x254` .. `+0x2B4`, `+0x2EC` | shake walk (used in the outer camera's embedded instance) | |
| `+0x2B8` | extra eye height | 0 |
| `+0x2C0` | mode-5 frames | 5000 |
| `+0x2C4` | take-off countdown | -1 |
| `+0x2CC` | tick of the last airborne frame | 0 |
| `+0x2D0` / `+0x2D4` / `+0x2D8` | wall-launch armed / airborne latch / swing initialised | 0 |
| `+0x2E0` / `+0x2E4` / `+0x2E8` | phase B / landed / phase A | 0 / 1 / 0 |
| `+0x2F0` | reset pending | 0 |
| `+0x300` | lock state | 1 |
| `+0x304` / `+0x310` / `+0x31C` / `+0x328` / `+0x334` | splines: look B, eye B, look A, eye A, swing ease | |
| `+0x340` / `+0x354` / `+0x368`, `+0x37C` | PID rings X / Y / E, ring index | 0 |
| `+0x380` / `+0x384` / `+0x388` | Kp / Ki / Kd | 0.011394524 / 0 / 0.0012785085 |

### Constants (DEFAULT_3; Near and Far use other values)

gp = `0x004A30F0`. All are `.lit4` floats.

| Stage | Address (gp form) | Values |
|---|---|---|
| set-target eye offset | `0x0049CFBC` (gp-0x6134) | 61.687962 |
| velocity filter | `0x0049CFD0` .. `0x0049CFEC` (gp-0x6120 .. -0x6104) | 0.6, 0.27136135, 0.9, 0.29420722, 0.85139298, 0.85, 0.97, 0.1 |
| direction | `0x0049CFF0` (gp-0x6100) | 0.98 |
| distance | `0x0049CFF4` .. `0x0049D00C` (gp-0x60FC .. -0x60E4) | 0.92397803, 0.90741497, 300.92493, 11.549837, 76.68663, 10.755208, 1.7668397 |
| vertical offset | `0x0049D010` .. `0x0049D020` (gp-0x60E0 .. -0x60D0) | 0.97839177, 11.678784, 31.225603, 11.392387, 9.33469 |
| fov filter | | 0, 0.95990783, 1, 0.95 |
| mode-5 hold | | 2.0036807, 0, 0.98, 0.96 |
| look-at height | `0x0049D044` .. `0x0049D054` (gp-0x60AC .. -0x609C) | 0.92419082, 31.102573, 0.37469128, 12.332657, 10.589058 |
| jump | `0x0049D058` .. `0x0049D064` (gp-0x6098 .. -0x608C) | 0.1364145, 0.85366827, 2.4947209, 1.8110173 |
| swing | `0x0049D068` (gp-0x6088) | 1.5269116 |
| pull-behind | `0x0049D06C`, `0x0049D070` (gp-0x6084, -0x6080) | 146.389, 0.97069818 |
| set-target direction | `0x0049D074` (gp-0x607C) | 559.74402 (with 300) |
| proximity push | | 600, 300, 100, 0.98 |
| slow lock | | 15 km/h, 1.5 s, 1.5 s |
| finish (`0x00176DE0`) | | 16.140757 deg, 6.6548877 deg, 0.92642629, 0.84256876 |

Run on a synthetic steady cruise, the algorithm settles at an eye-to-look-at distance of about 380 and a fov of
0.95990783 * pi/4.

### Code-shape notes

- Several stores sit in branch delay slots and execute regardless of the branch: the take-off countdown `+0x2C4` is
  decremented before its test, `+0x1E0` is stored before the threshold test, and `+0x2EC` = requested is stored in
  the shake fade branch.
- VU0 quad arithmetic includes w in every dot product. A VU divide or reciprocal square root of zero saturates to
  FLT_MAX.
- `0x0031C128` is asin; the PID and the landing angle both use it.

## Camera inputs (rider target getters)

The target is read through virtual getters. "Slot" is the entry offset used by the sources.

| Input | Getter / source | Notes |
|---|---|---|
| head position | slot `0x08` -> `0x0011FF48`: head bone (rider `+0x89C`) world row, w = 1 | read from the cached pose; see below |
| velocity | slot `0x18` -> rider `+0x1E0` (w = 0) | |
| forward | slot `0x20` -> rider `+0x1B0` | physical forward |
| previous contact normal | slot `0x48` -> rider `+0x380` | |
| predicted air time | slot `0x60` -> `*(rider+0x788)+0x98` | 0 after landing, as the landing resolve clears it |
| wall normal | slot `0x80` -> rider `+0x3C0` | set when the contact normal's z < 0.05 |
| boost level | slot `0x88` -> rider `+0x2FC` | 0 / 0.25 / 0.625 / 1 |
| jump charge | slot `0x90` -> `0x0015F710` reads rider `+0x220` | the filtered crouch value, not a separate button-charge accumulator |
| trajectory status active | slot `0x98`: `*(rider+0x788)+0xAC` in {1, 3} | |
| surface id | slot `0xA0` -> rider `+0x438` | during a crash it is the crash actor's contact surface (PS2) |
| launch value | slot `0xA8` -> rider `+0x5A4` | the jump launch magnitude; about 649.68 in a sampled jump (PS2); the camera's take-off ramp spans 300 .. 500 |
| landing angle | slot `0xB8` -> `0x0015F780` | asin-based angle from the air-trajectory vectors `*(rider+0x788)+0x10` / `+0x20` and the velocity (vector naming unconfirmed; `+0x20` read (0,0,1,0) in savestates, PS2) |
| proximity flag | slot `0xC0` -> rider `+0x5AC` | |
| motion mode | `0x0011FE98` = motion owner `+0xDE0` | 0 ground, 2 crash, 4 rail, 5 handplant (per the rider's motion exit table) |
| rider type | rider `+0x434` | |
| tick | `0x001298C8` | race clock total ticks |
| terrain probe | `0x0032E100` / `0x00336850` | swept segment query |
| random | `0x003177F0` | presentation stream `0x004FF018` |

Where the inputs come from:

- **Launch value.** The take-off routine `0x00114298` computes rider `+0x5A4` (in its block `0x00114B78` ..
  `0x00114C6C`). At a terrain edge the ground departure `0x0013F178` calls `0x00114298` with charge -1 (at
  `0x0013F194` .. `0x0013F1A0` inside `0x0013F178`) when the ground controller's departure flag is set, so passive
  take-offs also supply a launch value.
- **Proximity flag.** `0x0013AF28` clears rider `+0x5AC` on each rail-motion tick, queries within 300 cm around the
  board bone, and sets it only when the hit instance has an entity whose vt`+0x170` predicate returns non-zero. Static
  spline geometry has no such entity. It was 0 in every sampled savestate (PS2).
- **Head position.** `0x0013AA48` consumes the cached posed geometry and does not rebuild it on landing or impact;
  `0x0011FF48` reads the cached world bone. The collision code (`0x00106538`) accumulates body translations in
  rider `+0x9D0`; after the second motion pass `0x00121750` calls `0x00310530` to add that displacement to the cached
  bone positions and skin matrices before the camera runs. So the camera sees the sampled pose translated by that
  tick's collision displacement, together with post-contact velocity, motion mode and orientation.
- **Crash from the air.** The rider's trajectory predictor is restarted (`0x00136C40` `cWipeoutMotion_gainFocus`)
  before that tick's camera step, so the landing angle is 0 (PS2).
- **Ground crash** requests shake index 4 (see "Shake").

Rider type (`+0x434`) and surface id (`+0x438`) were 0 in the early sampled savestates; how other values change the
stages is not described.

## POST_RACE_1 (type `44h`)

| Function | Behaviour |
|---|---|
| `0x001789E8` (constructor) | direction = normalized horizontal velocity if its length > 1, else the rider forward; normalized if longer than 0.01, else +X |
| `0x00178BB0` (update) | runs the `0x00162568` velocity stage, then the orbit below |
| `0x00178E90` (set-target) | base set-target with eye seed 0 and offset direction (100, 100) |
| `0x00178BA8`, `0x00178B98` | finish: `0x00178BA8` sits where DEFAULT_3 has `0x00176DE0`; `0x00178B98` is grouped with it in the source. The finish has no pitch lag filter |

Update:

```
phase = (phase + 1) mod 1100
yaw   = -0.748278856 * cos(2*pi*phase/1100)        # cos 0x0031C040
dir   = rotate(direction, about Z, yaw)            # half-angle sincos 0x0031BE50
lookat = head - 3 * Z
if roster count (game info +0x78) >= 2: eye = lookat - dir*(126 + 200) + Z*(-27 + 150)
else:                                   eye = lookat - dir*126 + Z*(-27)
```

With six riders the offsets were 326 cm back and 123 cm up (PS2).

## Race finish, post-race and replay (PS2)

- The finish pushes POST_RACE_1 (through `0x00162258`) in the same frame as the camera update that sees the same
  rider state. Construction is the constructor, two set-targets and one step. The director then blends: DEFAULT_3 is
  unlinked on the 60th update.
- Race phase 6 (EndRace) starts one tick after the finish. The rider enters control 10 and coasts to a stop in about
  4 s.
- POST_RACE_1 stays for 409 camera updates. Then the game starts a replay: the tick counter goes back to 1 and the
  director is locked (flags bit 1, `+0x2C` = `5Dh` through `0x00161FA0`); the terrain lift is not reset.
- In the replay a kind-2 camera trigger fired at GO (rider still at the grid): `0x0016E1D8` called
  `0x00162060(5Bh)` and replaced the camera with the type-`5Bh` object. The trigger volume records at the manager
  `0x004C5830` were not enumerated.

## SPOKE and handplants

SPOKE (`0x00177E50`, type `42h`) is entered by the transition code when the rider's motion mode is 5 (handplant),
setting the latch (flags bit 2), and released above 35 km/h, when a fresh DEFAULT_3 fades in over 150 frames. Its own
update is not described in the sources.

## Re-targeting on teleport and placement

Stage builtin 34 ("teleport current player") calls the rider's vt`+0x54`, `0x00123210`, which re-targets the camera
twice:

1. **Before placement.** The director's `+0x1C` entry `0x0015CC70(director, rider id)` runs every node's set-target
   (DEFAULT_3 acts only for its own target) and then `0x0015E030`. The rider state at this point is the old
   position, head and forward, the velocity already scaled by the ground-entry factor, and motion mode 0. For
   computer riders the node set-targets do nothing (the target is the human).
2. **Inside placement** (`0x0011D660`, for devices 0 and 1). Through the device's view object (`+0xA8` points to the
   same director) the `+0x24` entry `0x0015CCF0` runs set-target on every node with no rider check, plus
   `0x0015E030` and `0x002F41A8`, now with the new position, head and forward and zero velocity.

After that the camera updates normally at the end of the frame. Neither call touches the compositor's terrain lift or
first-frame state. Earlier in the teleport, `0x00125038` stops the reset white fade (`0x002E4578`) of the viewport
for the rider's device when that viewport's `+0x78` is 1. After placement the teleport calls the rider effect routine
`0x00111890` (one source describes it as building the rider's effect components, another as resetting them); it
fetches the camera's splash object through `0x002306A8` and, for device >= 0, calls its vt`+0x74` (the splash reset
`0x002F39C8`).

## Projection and widescreen

Front-end Options "Widescreen" (Off, 16:9, Anamorphic) is stored in bits 20..21 of the profile word `0x00535610`
(setter `0x0015BEE8`; menu store at `0x00189D14` inside `0x00189980` `cFEStateOptionsGame_onWidgetEvent`). The bits
take effect through `0x00228C08`, called at boot (`0x00152DBC` inside `0x00152BB0`) and after the menu store
(`0x00189D34`). It passes the mode to the render context's vt`+0x140` = `0x00377950`, which stores ctx `+0x6B94` =
mode and:

| Mode | `+0x6B98` top | `+0x6B9C` height | `+0x6BA0` x scale | `+0x6BA4` y scale |
|---|---|---|---|---|
| 0 Off | 0 | 1 | 1 | 1 |
| 1 16:9 | 0.125 | 0.75 | 0.75 | 0.75 |
| 2 Anamorphic | 0 | 1 | 0.75 | 1 |

- **Viewport** `0x00376A70(x, y, w, h)`: y = max(y, top * 448), h = min(h, height * 448). Mode 1 therefore draws the
  3D view into lines 56..392 with black bars inside the 4:3 signal.
- **Projection** `0x00376C58`: GS x scale = 0.5 * w / tan(fov), y scale = x scale * 1.3333 (`0x004A0940`,
  gp-0x27B0) * 448/512, then x *= `+0x6BA0` and y *= `+0x6BA4` (also applied to the normalized copy at `+0x5860` /
  `+0x5874`). The GS centre stays at 2048/2048. Off gives 272.65/318.09 px (256 / tan(0.95990783 * pi/4), the
  settled chase fov), 16:9 gives 204.49/238.57, Anamorphic 204.49/318.09. So the stored fov acts as the horizontal
  half-angle. Checked live in ARMSX2: ctx `+0x5930` held 16 times these scales, and the viewport was [0, 56, 512, 336]
  in mode 1 (PS2).
- Both widescreen modes keep the 4:3 vertical view angle and widen tan(horizontal) by 1/0.75 (Hor+ to 16:9). Mode 1
  zoomed on a 16:9 TV and mode 2 stretched by a 16:9 TV show the same picture.
- **HUD.** Mode 1 maps the in-race HUD into the band (y' = 56 + 0.75 y, x unchanged); mode 2 leaves the HUD at its
  4:3 framebuffer position (PS2, measured on captured frames). Whether pause and front-end menus letterbox in mode 1
  is not verified.

## Camera splash (lens snow and ice crystals)

One object per possible camera draws snow drops and ice crystals on the lens. The game object holds them at
`+0x68 + 4 * camera` (getter `0x002306A8`). They live in entity group 2 (manager `0x004A5988`, gp+0x2898); on Snow
Jam the camera-1 object precedes the camera-0 object in that list.

Vtable `0x00488230`:

| Offset | Function | Role |
|---|---|---|
| `+0x0C` | `0x002F3618` | |
| `+0x14` | `0x002F39E0` | update |
| `+0x24` | `0x002F3E28` | render (makes no random draws) |
| `+0x74` | `0x002F39C8` | reset: clears the drop and crystal counts, pending count, has-previous flag and stored snowfall |

Fields: `+0x10` camera index, `+0x14` drop count, `+0x18` crystal count, `+0x1C` drops (`0x3C` bytes each), `+0x724`
crystals (`0x4C` bytes each), `+0x100C` has-previous flag, `+0x1010` previous camera position, `+0x1020` speed (km/h),
`+0x1024` pending spawns, `+0x1028` snowfall.

Tweakables ("Camera Splash Menu", built by `0x0024BF60` `cSplashTogglesMenu_cSplashTogglesMenu`; gp-relative,
values as in a race):

| Address (gp form) | Name | Value |
|---|---|---|
| `0x004A424C` (gp+0x115C) | Enable | 1 |
| `0x004A4250` (gp+0x1160) | Render | 1 |
| `0x004A4254` (gp+0x1164) | Max Drops | 30 |
| `0x004A4258` (gp+0x1168) | Max Crystals | 24 |
| `0x004A425C` (gp+0x116C) | Percentage Ice Crystals | 0.6 |
| `0x004A4260` (gp+0x1170) | Percentage Ice Crystal Spawn | 0.01 |
| `0x004A4264` / `0x004A4268` (gp+0x1174 / +0x1178) | Ice Crystal Min / Max in Group | 1 / 3 |
| `0x004A426C` (gp+0x117C) | Max Spawn Per Crystal | 2 |
| `0x004A4270` (gp+0x1180) | Farthest Impact Distance | 450 |
| `0x004A4274` (gp+0x1184) | Lowest Impact Intensity | 105 |
| `0x004A4278` (gp+0x1188) | Lowest Snowfall For Impacts | 1.0 |
| `0x004A427C` (gp+0x118C) | Impact Multiplier | 1.1 |
| `0x004A4280` (gp+0x1190) | Lowest Snowfall Amount | 1.5 |
| `0x004A4284` (gp+0x1194) | Snowfall Multiplier | 0.015 |
| `0x004A4294` (gp+0x11A4) | (crystal drop size threshold) | 4 |

Update `0x002F39E0`, once per game update in the group-2 pass (at `0x00230CCC` inside `0x002306B8`) and also in the
load and overlay updates:

1. Return if Enable is 0 or the camera index is >= the camera count. In single player the camera-1 object returns
   here.
2. p = camera `+0x20`. If the has-previous flag is set, speed = |p - prev| * 59.999996 * 0.036 (`0x0049F7EC`,
   `0x0049F7F0`), in km/h; otherwise speed = 0 and the flag is set. If speed > 1000 the object resets and speed = 0.
   prev = p.
3. Spawn `0x002F3810`: n = trunc(pending); pending -= n. Each unit takes three values from the one-word effects LCG at
   `0x004A3AFC` (w = ((w * 18FCDh + E9507Ch) & 7FFFFFh) | 3F800000h, read as a float in [1, 2)): x = (f-1) * 640,
   y = (f-1) * 480, t = f-1. If t < 0.6 one presentation-stream draw (call site returning to `0x002F3920`) sets the
   group size 1 + r % 2 and a crystal group is spawned (`0x002F3640`); otherwise a drop is spawned (`0x002F37A8`).
4. Drops update in `0x002F2810`; dead drops are replaced by the last one.
5. Crystal selection (call sites at `0x002F3BE0` and `0x002F3C44` in the update): one unconditional draw gives
   u in [0, 1) and f = u * crystals / 24; if f < 0.01 and there are crystals, a second draw picks r2 % crystals,
   otherwise none is picked.
6. Crystals update in `0x002F3030`. The picked crystal, if alive with a spawn count below 2, increments its count and
   spawns a drop when both of its sizes * 0.6 exceed 4. Dead crystals are replaced by the last one.

Pending sources:

- **Snowfall** `0x002F4330`, called once per camera by the snowfall object (`0x002E5920` / `0x002E5DA0`): stores
  `+0x1028` = snowfall; if snowfall > 1.5, pending += snowfall * (speed + 10) * 0.015 * 0.0076923 (`0x0049F7FC`).
- **Impacts** `0x002F4260` (from `0x002F4118`): only when snowfall > 1.0 and the distance d < 450,
  pending += (1 - d/450) * clamp((I * 0.036 - 105) / (120 - 105), 0, 1) * 1.1.

Every sampled savestate on three courses had snowfall <= 0.1, so nothing spawned and the splash drew exactly one
presentation-stream number per game tick (the unconditional crystal draw); a 12440-tick trace had no spawn or
second crystal draws (PS2). Spawns would need heavy snowfall.

## Open questions

- The relationship between the director pointer, director`+0x10` and the per-camera object whose vtable pointer is at
  `+0x90` is only partly pinned down.
- The type-to-name pairing of `3Ch`/`3Dh`/`3Eh` with DEFAULT_2/3/4.
- SPOKE, Manual, Spline, SUPERPIPE, relative/replay-clock cameras and the camera trigger volumes are not described.
- Race-state suppression of the shake; which condition picks the 1.2/60 or 0.6/60 SPOKE entry rate.
