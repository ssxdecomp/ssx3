<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/camera/

## `src/camera/cameraalgolist.cpp`

Segment `0x0015C988`-`0x0015CBA0`.

- **`0x0015C988`** `cCameraAlgoList_insert` - Camera algorithm node list push/insert helper (see `0x00161E58`): push runs set-target, then inserts at weight 1 (rate 1) or 0; the role split with `0x0015CB08` is unclear. *[unconfirmed]*
- **`0x0015CA50`** - Unlinks a camera algorithm node from the director list. *[PS2]*
- **`0x0015CB08`** - Camera algorithm node list push/insert helper (see `0x00161E58`); the role split with `0x0015C988` is unclear. *[unconfirmed]*

## `src/camera/cameracontroller.cpp`

Segment `0x0015CBA0`-`0x0015D078`.

- **`0x0015CC70`** - Camera director vtable +0x1C: runs set-target on every director node whose algorithm targets riderId, then `0x0015E030` and `0x002F41A8`. Uses the rider's pre-placement state (old position/head/forward, scaled velocity, motion 0); skipped for computer riders. *[static]*
- **`0x0015CCF0`** - Camera director vtable +0x24: runs set-target on every node without a rider check, then `0x0015E030` and `0x002F41A8`; used for the second cut after `0x0011D660`. *[static]*
- **`0x0015D020`** - Camera occlusion gate: selects the override-only line-of-sight branch of `0x0015EE00`; false for the automatic chase camera. *[static]*

## `src/camera/cameraalgorithms.cpp`

Segment `0x0015D078`-`0x0015DC18`.

- **`0x0015D078`** `cChaseCameraController_createChaseAlgorithmBlend` - Camera activate: factory that builds DEFAULT_2/3/4, POST_RACE_1 and other (e.g. SPOKE) camera algorithms and pushes them; director lock bit 1 forces rate 1. Set-target runs twice (in the push and in the factory tail). *[PS2]*
- **`0x0015DB58`** - Camera restart: clears flags/latch, does an instant cut (two set-targets) plus director vtable +0x20 (a third set-target), and sets outer lift 0 and outer +0x4A4 = 1. *[PS2]*

## `src/camera/camera.cpp`

Segment `0x0015DC18`-`0x00168FE8`.

- **`0x0015DF98`** - Camera update (camera vtable slot +0x1C); calls `0x0015E668`, which leads to shake `0x0015E460`. *[static]*
- **`0x0015E030`** - Outer camera update after a director set-target: calls `0x00166F28`(Y+0xC0) on the embedded DEFAULT_3. *[static]*
- **`0x0015E050`** - Equip Gear camera: eye (-110,394,0) -> target (-35,0,0) cm, 25 degrees. *[PS2]*
- **`0x0015E360`** - Camera requestShake: queues a boost/speed-scaled look-at shake request (index, fade, scale) at outer +0x450..+0x45C. Ground crash `0x0012D160` calls it at `0x0012D218` with index 4, fade 0, scale clamp(speedCmps*0.036/100, 0, 1). *[static]*
- **`0x0015E460`** - Camera shake step (random-walk look-at displacement in the compositor shake path), called at `0x0015E930`: runs shake start `0x001656B0` and per-tick shake `0x00165938`, drawing from the visual RNG `0x003177F0`. *[PS2]*
- **`0x0015E668`** - Gameplay camera update/compositor: blends algorithm nodes into the outer camera eye/look-at and fov/near/far with clamps. One node, or a head node of type 0x4A, is copied exactly; otherwise eye (+0x60) and look-at (+0x20) are running means over nodes with smoothed weight > 1e-4 (k = s/sum s), fov/near/far running means over raw weights != 0, far = min(30000, farCap). Then runs collision `0x0015EE00` and shake `0x0015E460`, calls `0x00166640` and `0x00166F90`, builds the render view matrix and samples painters. *[PS2]*
  - `0x0015E928`: Calls camera collision `0x0015EE00`. *[static]*
  - `0x0015E930`: Calls camera shake `0x0015E460`. *[static]*
  - `0x0015E968`: Render view matrix block (through `0x0015EAE8`): unnormalised quaternion (outer+0x30) -> matrix, left-multiplied by G at `0x004C53A0`, plus the negated eye (outer+0x20); the result at outer +0x40 is what rider lighting uses. *[PS2]*
  - `0x0015EBBC`: Painter sampling (through `0x0015EBD0`) after final collision/shake: calls `0x002ED490` with outer camera +0x20/+0x24 X/Y, view index+6 and weight -99999. *[static]*
- **`0x0015EE00`** - Camera terrain-clearance stage: vertical +-halfLen probe, accumulated lift (x0.97 decay) at outer+0x460, last normal at outer+0x470, eye re-projection. Builds a kind-2 query (point, normal, UV) via `0x0032E100` with preferred fraction 0.5 and terrain callback `0x00336850`, and rejects pushes larger than 150 cm. Has an override-only line-of-sight occlusion branch gated by `0x0015D020` (false for the automatic camera). Called from `0x0015E668` at `0x0015E928`. *[PS2]*
  - `0x0015F0C8`: Passes preferred fraction F12 = 0.5 to the kind-2 `0x0032E100` query, so hits are ranked by distance to the probe midpoint. *[static]*
  - `0x0015F160`: Loads 150.0 (0x43160000), the first large-push rejection cutoff; the second site is `0x0015F198`. *[static]*
  - `0x0015F198`: Loads 150.0 (0x43160000), the second large-push rejection cutoff. *[static]*
- **`0x0015F710`** - Camera target slot 0x90 (through `0x0015F718`): returns the pose controller's filtered crouch rider+0x220. *[PS2]*
- **`0x0015F780`** - Camera landing-angle getter (target slot 0xB8): uses asin `0x0031C128` on the trajectory vectors *(rider+0x788)+0x10/+0x20 and the velocity. *[static]*
- **`0x00160028`** - Camera-director node that draws from the visual RNG (not during races). *[static]*
- **`0x00160130`** - Camera-director node that draws from the visual RNG (not during races). *[static]*
- **`0x00161950`** - Part of the default DEFAULT_3 Mid chase camera (with `0x001673F8`). *[PS2]*
- **`0x00161AB0`** - Camera director transition decision: guard reset to 0x3D; motion mode 5 (handplant) latches the SPOKE camera via `0x001621A8` (rate 1.2/60 or 0.6/60); above 35 km/h `0x00162218` releases it, fading a fresh DEFAULT_3 in at rate 1/150 (150 frames). *[PS2]*
- **`0x00161BB8`** - Camera director update: runs transitions (`0x00161AB0`), the node weight pass and the auto-revert timer, blending camera algorithms with smoothstep fades; in normal races only one DEFAULT_3 node exists (weight 1). *[PS2]*
  - `0x00161BF0`: Node pass (through `0x00161D7C`): steps the head via `0x001624E8` (a1 0); head ramps to 1, older nodes to 0 by the head rate; smoothstep 3w^2-2w^3 at node +0x0C; type 0x4A forced to 0; nonpositive weights unlink via `0x0015CA50`. *[PS2]*
  - `0x00161D80`: Auto-revert timer (through `0x00161E30`): 10 s revert, only for a 0x5D request in game states 1..9. *[PS2]*
- **`0x00161E58`** - Director insertAlgorithm: sets director +0x18 = new type and inserts a camera algorithm node; an empty list gives rate 1, rate exactly 1 clears the list first, and push runs set-target then inserts at weight 1 (rate 1) or 0. The role split with `0x0015C988`/`0x0015CB08` is not stated. *[PS2]*
- **`0x00161EF0`** - Camera select with instant cut. *[PS2]*
- **`0x00161FA0`** - Camera override selection; replay start locks the director with request 0x5D at +0x2C. *[static]*
- **`0x00162060`** - Camera director override request taking a camera type (e.g. 0x5B from a trigger). *[PS2]*
- **`0x001621A8`** - Director request pushing the SPOKE camera (type 0x42) in motion mode 5, rate 1.2/60 or 0.6/60. *[PS2]*
- **`0x00162218`** - Director release from SPOKE above 35 km/h: fades a fresh DEFAULT_3 in at rate 1/150. *[PS2]*
- **`0x00162258`** - Camera finish fade: pushes the finish camera at rate 0.016793445 unless override bit 0 is set. *[PS2]*
- **`0x00162290`** - Camera restore (used by results overlay `0x00234008`). *[static]*
- **`0x001622B0`** - Camera algorithm constructor defaults (base part); one of three constructor routines (with `0x00162318`, `0x00176D68`) that set the 0x390-byte algorithm defaults: fov pi/4, near 10, far 30000, follow distance 200, etc. *[static]*
- **`0x00162318`** - Camera algorithm constructor defaults (second part; see `0x001622B0`), e.g. +0x2C0 = 5000, +0x2C4 = -1, +0x300 = 1, +0x248 = 0.5, +0x1E0 = 10. *[static]*
- **`0x001624E8`** - Camera algorithm per-tick step: re-runs set-target if the +0x2F0 reset is pending, then update and finish. The director node pass steps the head node through it with a1 = 0; POST_RACE_1 also steps through it. *[PS2]*
- **`0x00162568`** - Chase camera stage 1: acquires rider velocity, applies the vertical-dependent lag filter and fills the per-tick scratch context; writes lag-filtered horizontal velocity (+0x100) and last velocities (+0x1B0/+0x1C0). DEFAULT_3 constants 0.6, 0.27136135, 0.9, 0.29420722, 0.85139298, 0.85, 0.97, 0.1 at `0x0049CFD0`..`0x0049CFEC` (gp-0x6120..gp-0x6104). Also called first by the POST_RACE_1 update `0x00178BB0`. *[PS2]*
- **`0x00162998`** - Chase camera stage 2: mode-5 (handplant) fade frame counter at algorithm +0x2C0 (constructor init 5000). *[PS2]*
- **`0x00162A20`** - Chase camera stage 3: airborne latch +0x2D4, wall-launch arm +0x2D0 and 15-frame take-off countdown +0x2C4 (init -1, decremented in a delay slot before its branch); +0x2CC holds the last airborne tick from `0x001298C8`. Signedness of the tick-lastAirTick < 31 compare is uncertain (int32 assumed). *[PS2]*
- **`0x00162B80`** - Chase camera stage 4: sets the look-at to the rider head bone position from camera-target slot 0x08 (`0x0011FF48`: head bone index rider+0x89C, world row with w=1). *[PS2]*
- **`0x00162B90`** - Chase camera B4: look-at height filter into +0x1E4; constants 0.92419082, 31.102573, 0.37469128, 12.332657, 10.589058 at `0x0049D044`..`0x0049D054` (gp-0x60AC..gp-0x609C). Uses filtered crouch on the ground and keeps the previous term in the air. *[PS2]*
- **`0x00162C78`** - Chase camera stage 5: filtered travel direction into +0x80 (filter 0.98 at `0x0049CFF0`, gp-0x6100) with a PID-adapted coefficient over 5-tap history rings X/Y/E at +0x340/+0x354/+0x368 (index +0x37C); gains Kp 0x3C3AB019, Ki 0, Kd 0x3AA793A0 at +0x380/+0x384/+0x388. The PID alignment term is the angle itself from asin `0x0031C128`. *[PS2]*
- **`0x00163010`** - Chase camera stage 6: follow distance from speed and boost, then eye placement. Constants 0.92397803, 0.90741497, 300.92493, 11.549837, 76.68663, 10.755208, 1.7668397 at `0x0049CFF4`..`0x0049D00C` (gp-0x60FC..gp-0x60E4); follow distance at +0x1D0 (ctor 200), settling around 380 in cruise. *[PS2]*
- **`0x00163270`** - Chase camera B1: filtered eye vertical offset from speed drop, boost and crouch into +0x1D4 (seed 61.687962); constants 0.97839177, 11.678784, 31.225603, 11.392387, 9.33469 at `0x0049D010`..`0x0049D020` (gp-0x60E0..gp-0x60D0). Uses filtered crouch (target slot 0x90 = rider+0x220) while grounded and keeps previous terms in the air. *[PS2]*
- **`0x001633B0`** - Chase camera B2: field-of-view filter; constants 0, 0.95990783, 1, 0.95, fov scale at +0x1DC; settled cruise fov = 0.95990783*pi/4. *[PS2]*
- **`0x00163450`** - Chase camera B3: motion-mode-5 hold/blend of the eye offset and extra eye height +0x2B8. The beqz on ctx+0x5C branches to the timer path, so (contrary to a first reading) the offset +0xB0 is captured during mode 5 and the blend (timer +0x1E0, init 10, stored before its < T test) runs after mode 5 ends. Hold constants 2.0036807, 0, 0.98, 0.96; in cruise +0x1E0 stays 10 and +0xB0 is unwritten. *[PS2]*
- **`0x001635F8`** - Chase camera B5: jump camera using two natural cubic spline pairs (phase A look +0x31C / eye +0x328, phase B +0x304 / +0x310) plus landing settle; flags +0x2E8/+0x2E0/+0x2E4. Constants 0.1364145, 0.85366827, 2.4947209, 1.8110173 at `0x0049D058`..`0x0049D064` (gp-0x6098..gp-0x608C); knot tables at `0x0049C658` (gp-0x6A98) and `0x0049C700` (gp-0x69F0). Landing decay 0.92 (0.93 after an air crash with landing angle 0). Uses predicted air time (slot 0x60) and landing angle (slot 0xB8). *[PS2]*
  - `0x001636BC`: Early prediction/countdown branch (through `0x00163708`); also shortens the take-off countdown when trajectory status becomes active. *[static]*
  - `0x00163E8C`: Touchdown/landing-offset decay block (through `0x00163FD4`; `0x00163FD8` is the common successor): first-landing and decay frames with 1.2/2.2 s and 1.05/1.4 rad boundaries; the unlatched branch skips only `0x00163FD4`. *[static]*
- **`0x001641C0`** - Chase camera C3: proximity push driven by rider+0x5AC (300 forward, 100 up, 600 side, factor 0.98); rider+0x5AC has not been seen set, so the branch's practical use is uncertain. *[static]*
- **`0x001643A8`** - Chase camera C4: slow-speed lock state machine (15 km/h threshold, 1.5 s in / 1.5 s out); state +0x300 (0 in, 2 locked, 1 out, 3 idle; init 1), view vector +0x1A0, lock blend +0x248 (init 0.5). *[PS2]*
- **`0x001646A0`** - Chase camera C2: motion-mode-4 pull-behind filter; constants 146.389 at `0x0049D06C` (gp-0x6084) and 0.97069818 at `0x0049D070` (gp-0x6080), filter state +0xC0. Mode-4 behaviour has not been observed at runtime. *[static]*
- **`0x00164878`** - Chase camera C1: wall-launch swing-around using a clamped 9-knot ease spline, return blend and 60% guard. Swing constant 1.5269116 at `0x0049D068` (gp-0x6088), ease knots at `0x0049C7EC` (gp-0x6904); swing vectors +0x110..+0x180, timers/angle +0x22C..+0x244, init flag +0x2D8, ease spline +0x334. Only reachable after a near-vertical wall launch; exact VU quaternion accumulation order uncertain. *[unconfirmed]*
- **`0x001656B0`** - Camera shake start (boost/speed-scaled random walk): makes 12 visual-RNG draws (`0x003177F0`, state `0x004FF018`) when a shake starts, from call sites returning at `0x00165708`..`0x001658C0`. Paired with per-tick shake `0x00165938`. *[PS2]*
  - `0x00165708`: First of the 12 shake-start visual-RNG draw return addresses (through `0x001658C0`). *[PS2]*
  - `0x001658C0`: Last of the shake-start visual-RNG draw return addresses (range from `0x00165708`). *[PS2]*
- **`0x00165938`** - Camera shake per-tick update. Draws from the visual (presentation) RNG `0x004FF018`: 6 draws per shaking tick, return addresses `0x00165A54`..`0x00165BAC`. Only the set-1 shake timers (`+0x278`..`+0x280`) advance; the second-octave timers (`+0x2A8`..`+0x2B0`) never advance and are inert. Paired with `0x001656B0` as the original camera shake code. *[PS2]*
  - `0x00165A54`: First of the 6 per-tick camera shake visual-RNG draw sites (calls to the draw routine `0x003177F0`; range through `0x00165BAC`). *[PS2]*
  - `0x00165BAC`: Last of the camera shake visual-RNG draw sites (range starts at `0x00165A54`). *[PS2]*
- **`0x00166228`** - Shared chase camera finish: computes the angles, applies the pitch lag filter with angle limit and the snap guard, and writes the output eye. Calls `0x00166640`, `0x001662A0`, `0x00166530` and `0x00166F90`. DEFAULT_3 supplies its finish constants via `0x00176DE0` (16.140757 deg, 6.6548877 deg, 0.92642629, 0.84256876); the POST_RACE_1 finish omits the pitch lag filter. *[PS2]*
- **`0x001662A0`** - Chase camera finish helper, probably the pitch lag filter with angle limit (role assigned by call order only); the filtered pitch is stored at `+0x1D8`. *[unconfirmed]*
- **`0x00166530`** - Chase camera finish helper, probably the snap-guard step (role assigned by call order only); the snap guard proper is `0x00168150`. *[unconfirmed]*
- **`0x00166550`** - Sets the camera offset direction; called by the DEFAULT_3 set-target `0x00176FE0` with (559.744, 300). May also perform part of the update step (exact split unclear). *[static]*
- **`0x00166640`** - Chase camera finish helper called first by the finish `0x00166228`, probably the yaw/pitch angle computation (role assigned by call order only). Also called from `0x0015E668` before the output stage `0x00166F90`. *[unconfirmed]*
- **`0x001668B8`** - Computes the camera forward vector with VU arithmetic. *[static]*
- **`0x00166C60`** - Base camera set-target reset step (used by the DEFAULT_3 set-target): resets fields and seeds history from the rider target. It re-reads target slot `0x20` (rider forward) into the fwd*250 scratch just before storing `+0x1B0`, so the last-velocity field `+0x1B0` equals the rider forward itself, not fwd*250; this matters when speed is below 1 km/h. *[PS2]*
- **`0x00166F28`** - Set-target of the outer camera's embedded DEFAULT_3 algorithm; always runs, using its own target. *[static]*
- **`0x00166F90`** - Camera algorithm output stage: writes the output eye and builds the camera matrix, position and conjugated quaternion from pitch/yaw. Order: identity+translation, negative pitch about Y, negative yaw about Z, VU matrix multiply, matrix-to-quaternion `0x0031B7A8` (via the `0x0031B748` path), final quaternion conjugation. Called from `0x0015E668` after `0x00166640`, and by the chase finish `0x00166228`. The render axis permutation G lives at `0x004C53A0`. *[PS2]*
- **`0x001673F8`** - Part of the default DEFAULT_3 (Mid) chase camera, together with `0x00161950`. *[PS2]*
- **`0x00168150`** - Camera snap guard: resets look-at/eye when |lookat-eye| < 20 or > 1e20 and sets the reset-pending flag `+0x2F0`. *[static]*

## `src/camera/script/scriptcontroller.cpp`

Segment `0x00168FE8`-`0x0016BF20`.

- **`0x001694B8`** - NIS Manual camera algorithm function (pair with `0x00169570`): places eye and target through the anchor frame. *[PS2]*
- **`0x00169570`** - NIS Manual camera algorithm function (pair with `0x001694B8`, which places eye and target through the anchor frame). *[static]*
- **`0x00169CF8`** - NIS Target camera algorithm function (pair with `0x00169DB0`): eye = target - distance*(cos p cos y, cos p sin y, sin p). *[static]*
- **`0x00169DB0`** - NIS Target camera algorithm function (pair with `0x00169CF8`, whose eye = target - distance*(cos p cos y, cos p sin y, sin p)). *[static]*
- **`0x0016A458`** - NIS Subject camera algorithm function (pair with `0x0016A510`): eye through the anchor frame, target on the subject rider. *[static]*
- **`0x0016A510`** - NIS Subject camera algorithm function (pair with `0x0016A458`). *[static]*

## `src/camera/trigger/cameratriggerman.cpp`

Segment `0x0016C9B0`-`0x001712B0`.

- **`0x0016E1D8`** - Kind-2 camera trigger handler: calls `0x00162060(0x5B)` to request an override camera. Fires at GO (tick 202) in a replay; the trigger volumes are held by the manager at `0x004C5830`. *[PS2]*

## `src/camera/trigger/cameratriggerfactory.cpp`

Segment `0x001712B0`-`0x0017ACC8`.

- **`0x00174190`** - Constructor of camera algorithm type 0x5B (0x90-byte object); this type is chosen when the game state is 1..9. *[PS2]*
- **`0x00176B10`** - Chase camera update driver, Near variant (DEFAULT_2): runs the shared chase helpers with its own per-variant gp constants. Siblings: Mid `0x00176E10`, Far `0x00177110`. *[PS2]*
- **`0x00176D68`** - DEFAULT_3 camera algorithm constructor; chains to the base constructor defaults (`0x001622B0`/`0x00162318`). *[static]*
- **`0x00176DE0`** - DEFAULT_3 finish entry: passes its finish constants (16.140757 deg, 6.6548877 deg, 0.92642629, 0.84256876) to the shared chase finish `0x00166228`. *[static]*
- **`0x00176E10`** - DEFAULT_3 (Mid) chase camera update driver, vtable slot `+0x28` of the DEFAULT_3 algorithm object. Runs the 15 shared chase helpers in order `0x00162568`, `0x00162998`, `0x00162A20`, `0x00162B80`, `0x00162C78`, `0x00163010`, `0x00163270`, `0x001633B0`, `0x00163450`, `0x00162B90`, `0x001635F8`, `0x00164878`, `0x001646A0`, `0x001641C0`, `0x001643A8` with DEFAULT_3 gp-relative tuning constants (per-frame, no time scale). Near `0x00176B10` (DEFAULT_2) and Far `0x00177110` (DEFAULT_4) share the helpers with different constants. *[PS2]*
- **`0x00176FE0`** - DEFAULT_3 camera algorithm set-target (vtable `+0x1C`); acts only when its target rider id matches. Calls the field reset `0x00166C60`, an update, the offset direction `0x00166550`, then the vt `+0x28` update (two updates and one finish with the seed input). Seeds eye vertical offset 61.687962 (`0x0049CFBC`, gp-0x6134) and travel direction normalize(fwd*559.744 - Z*300) (559.74402 at `0x0049D074`, gp-0x607C). *[PS2]*
- **`0x00177110`** - Chase camera update driver, Far variant (DEFAULT_4): same shared chase helpers as the Mid driver `0x00176E10`, with its own per-variant constants. *[PS2]*
- **`0x00177E50`** - SPOKE camera algorithm (type 0x42) code, used for the handplant camera; not decoded. *[static]*
- **`0x001789E8`** - POST_RACE_1 camera constructor: the initial direction is the normalised horizontal velocity if |v| > 1, else the rider forward; the unit vector is used if its length > 0.01, else +X. *[PS2]*
- **`0x00178B98`** - POST_RACE_1 set-target/finish entry, one of `0x00178B98`, `0x00178BA8`, `0x00178E90` (exact mapping unconfirmed). The POST_RACE_1 finish has no pitch lag filter. *[unconfirmed]*
- **`0x00178BA8`** - POST_RACE_1 set-target/finish entry, one of `0x00178B98`, `0x00178BA8`, `0x00178E90` (exact mapping unconfirmed). The POST_RACE_1 finish has no pitch lag filter. *[unconfirmed]*
- **`0x00178BB0`** - POST_RACE_1 camera update: slow yaw oscillation around the rider after the finish. Runs `0x00162568`; phase = (phase+1) mod 1100, yaw = -0.748278856*cos(2pi*phase/1100) (cos `0x0031C040`); half-angle sincos `0x0031BE50` rotates the direction about Z. Look-at = head - 3 cm Z; eye = look-at - dir*(126+200) + Z*(-27+150) when game-info `+0x78` (roster count) >= 2, else dir*126 and Z*-27. *[PS2]*
- **`0x00178E90`** - Probably the POST_RACE_1 set-target: base set-target with eye seed 0 and offset direction (100,100). The split among `0x00178B98`/`0x00178BA8`/`0x00178E90` is inferred. *[unconfirmed]*
