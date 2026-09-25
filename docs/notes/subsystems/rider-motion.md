# Rider motion and physics

Each rider has a motion owner that runs one of six motion modes: ground cruise, airborne, wipeout and three
others. Cruise motion builds surface forces, steps position and velocity at 60 Hz, finds contact on the
bicubic terrain patches, and turns the board toward its velocity and the slope. Takeoff turns the jump charge
into an impulse. Airborne motion runs a ballistic integrator and a trajectory predictor that forecasts the
landing. The air controller turns spin/flip input into a presentation pose, which is kept separate from the
physical orientation. Landing probes the terrain from the posed board and returns the rider to cruise.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2 emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and **(unconfirmed)** marks inferences.

## Where it lives

Source files are from the decomp's current split.

- `src/ai/computer.cpp`: the motion-mode dispatcher `0x00111408`, the mode/control entry chain `0x00111538`
  and `0x00111630`, and the landing scoring/boost event `0x0010E910`.
- `src/ai/control/handplantcontrol.cpp`: most of cruise and air motion. This includes the cruise update
  `0x0013D818`, its force helpers, the ground contact query `0x0013D1B8`, the second cruise phase `0x0013F178`,
  the air update `0x00139A20`, air focus `0x001399E0`, landing `0x00139C88`/`0x0013A7B0`/`0x0013AA48` and
  ground re-entry `0x0013C7A8`. The mode 4/5 targets `0x0013AF28` and `0x001391A8` are also here.
- `src/ai/motion/wipeoutmotion.cpp`: wipeout motion (mode 2), including `0x00136C40` (`cWipeoutMotion_gainFocus`).
- `src/ai/ai.cpp`: the controller-state handlers (cruise `0x00131620`, prewind `0x0012E9B8`, passive air
  `0x0012F620`/`0x0012F730`/`0x0012FB68`, air `0x00133128`/`0x00133308`) and the air presentation
  `0x00134DD0`/`0x00135180`. Also here: the control-5 exit `0x00134CB0`, the global tick accessor `0x001298C8`,
  the shared world update `0x00128AF0` and the mode-3 target `0x00136958`.
- `src/ai/rider.cpp`: world-axis rotation `0x0011DFE0`, `0x0011E098` (`cRider_updateOrientationImplicit`), the
  bounds rebuild `0x0011E150`, the motion/control setters `0x0011FE78`/`0x0011FEC8`, triplet smoothing
  `0x001211F8`, air physical alignment `0x00121AA0`, `0x00125970` and the human input provider `0x00127998`.
- `src/ai/ridermetrix.cpp`: the dynamic speed limit `0x0011B3F8`.
- `src/ai/airpredictor.cpp`: the trajectory predictor. `0x00113198` (`cAirPredictor_reset`), `0x001135B8`
  (`cAirPredictor_startLaunchIntoAir`), `0x00113618` (`cAirPredictor_initLaunch__FPcP5sQuadT1`), `0x00113200`,
  `0x00113648` and `0x001139A0`.
- `asm/14B10.s` (not yet split): the turn and crouch/brake target setters `0x00113E80`/`0x00113F88`, jump
  takeoff `0x00114298`, reverse stance `0x00114CC0`/`0x00115168`, stance restoration `0x00115640`, air input
  snapping `0x001158B8` and the control 0→2 request `0x001162C8`.
- `src/be/beintstat.cpp`, `src/be/beintplayer.cpp`: rider stat getters.
- `src/bx/ps2main.cpp`: math helpers, namely sin/cos `0x0031BE50`, atan `0x0031C228`, arcsine `0x0031C128`,
  standalone sine `0x0031BF60` and up alignment `0x0031BB30`.
- `src/intersect/riderspheretree.cpp`, `src/intersect/worldsphtree.cpp`: terrain and instance ray queries.

The equations in this note reproduce position, velocity and physical quaternion bit-exactly at short Snow Jam
checkpoints (PS2). These cover 1, 30 and 120 ticks of straight glide, 30-tick left-turn and brake runs, a
charged jump and 31/60/90 ticks after release, isolated flight, one speed-cap step and a 30-tick air spin.
They are short cases on one course. Other courses, long runs and all branches have not been checked this way.

## Floating-point behaviour (matters for matching)

Float constants below are given as IEEE single bit patterns in hex, for example bits `3C888889` = 1/60.

- **Scalar FPU (COP1).** ADD.S, SUB.S and MUL.S round toward zero. When ADD.S and SUB.S align the smaller
  operand they keep one guard bit, as PCSX2's `FPU_CORRECT_ADD_SUB` path models. Their results can therefore
  differ from plain IEEE round-toward-zero. Plain round-toward-zero does not reproduce the game's live bone
  poses, but the guard-bit model does (PS2).
- **DIV.S and SQRT.S** round to nearest. Examples are the stat normalisations and the trajectory speed-cap
  divide at `0x00113A74`.
- **VU0 arithmetic** chops and keeps its own behaviour, including VU DIV/RSQRT. This covers macro-mode
  vector/quaternion code and microprograms, and the scalar exceptions above do not apply to it. The
  orientation rebuild and quaternion code depend on the VU operation order.
- **No fused operations.** Each multiply and each add is rounded separately, and the order of operations
  matters. For example, the air step's `p + v*dt` is a multiply followed by an add.
- **The game's own math routines** are polynomial approximations: sin/cos `0x0031BE50`, atan `0x0031C228`,
  arcsine `0x0031C128`, and the standalone sine `0x0031BF60`, whose polynomial differs from sin/cos. Their
  results differ from correctly rounded values. For example, the takeoff ramp uses cos 50° = bits `3F248DBA`
  and cos 70° = bits `3EAF1D41`, where correctly rounded values would be `3F248DBB` and `3EAF1D44`.
- **SQRT.S operand.** At `0x0031BEEC` inside sin/cos, encoding `46050044` is `sqrt.s f1, f5`, which takes the
  root of 1 − sin². The EE reads SQRT.S's source from the ft field. A decoder that reads fs would take f0, the
  sine polynomial, instead. In the arcsine both fields name f0, so the distinction does not arise there.
- **Terrain bicubic powers.** A VU0 microprogram evaluates the patch grid using precomputed, separately
  rounded powers from a ten-row table at `0x0043CCB8` (in `.vutext`). Recomputing u² and u³ in floats gives
  different coordinates.

## Object layout

### Motion owner (`*(rider + 0x77C)`)

| Offset | Meaning |
|---|---|
| +0x000 | Mode-0 (cruise) motion. The dispatcher passes the owner itself as the receiver |
| +0x004 / +0x008 | Smoothed contact depths (h1, h3). They approach the body-scaled surface depth targets at no more than 100 cm/s. The force helpers' first argument ("controller") is assumed to be the owner (unconfirmed) |
| +0x010 | Global tick at which ground motion last gained focus |
| +0x014 | Set to −1 by passive takeoff (meaning unconfirmed) |
| +0x020 | Mode-1 air motion |
| +0x030 | Mode-2 wipeout motion. Its +0 selects the sub-stage |
| +0x0A0 / +0x0B0 / +0x110 | Mode-3 / mode-4 / mode-5 motion objects |
| +0x210 | Passive air (control 4) state, see below |
| +0x230 | Air control (control 5) object. Actor pointer at its +0x58 |
| +0xDE0 | Motion mode (0..5) |
| +0xDE4 | Control state |
| +0xDF8 | Human rider: accepted-command RLE recorder. NPC provider `0x0010A768`: NPC state instead |

### Rider fields used by motion

All vectors use the original Z-up axes and centimetres.

| Offset | Meaning |
|---|---|
| +0x110 | Position |
| +0x120 | Physical quaternion (x, y, z, w) |
| +0x180 | Retained presentation up vector (last pose) |
| +0x1A0 / +0x1B0 / +0x1C0 | Right / forward / up columns rebuilt from +0x120 by `0x0011E098` |
| +0x1E0 | Velocity, cm/s. Glide displacement agrees with old velocity/60 to within 0.014 cm (PS2) |
| +0x1F0 | Passed negated to the lateral force term (meaning unconfirmed) |
| +0x220 / +0x224 / +0x228 | Charge (crouch) triplet: current, rate, target |
| +0x280 | Balance triplet |
| +0x2A4, +0x2B0 | Filtered prewind spin and flip triplets |
| +0x2DC | Transient heading angle used by the cruise heading stage |
| +0x2E4 | Cruise speed limit (dynamic, see `0x0011B3F8`) |
| +0x2EC | Modifier read by the air-control angular update |
| +0x300 | Frame-time multiplier. It is 1.0 at ready, glide and wipeout (PS2). dt = +0x300 × float(1/60) |
| +0x308 | Contact/sticking flag that gates passive takeoff (full meaning unresolved) |
| +0x320 | Reverse-stance flag |
| +0x328 | Temporary (prewind/side) style, cleared by `0x00115640` |
| +0x360 | Jump request latch |
| +0x370 / +0x380 | Current / previous contact normal. +0x380 is copied from +0x370 before every ground query, including failed ones |
| +0x390 | Filtered board normal |
| +0x3A0 / +0x3B0 | Forward / lateral surface tangents |
| +0x3D0 | Contact surface velocity (subtracted to form relative velocity) |
| +0x430 | Packed contact patch `(resourceId << 8) | track` |
| +0x434 | Rider state (11..13 are exempt from reduced takeoff after landing) |
| +0x438 | Surface record index (−1 and no contact map to 0) |
| +0x454 | Signed contact distance from the query centre, cm |
| +0x460 | Contact point |
| +0x758 | Contact compression ratio, ≥ 0 |
| +0x864 | Pointer to the terrain-cell query cache, shared by the cruise query and the landing probe |
| +0x868 | Pointer to a separate body-collision query cache |
| +0x89C | Skeleton point index of the air presentation pivot |
| +0x8A0 | Board-root bone index used by the landing probe (bone 22 for Zoe) |
| +0xAA0 | Pre-landing body spheres read on the touchdown tick (offset base inferred) |
| +0xAAC / +0xAB0 | Solved patch U / V of the contact |

### Control triplets

Many control values are float triplets (current, rate, target). A request sets both the target and the rate.
`0x001211F8` then advances every triplet once per tick, in every motion mode. The step at
`0x0012130C..0x00121348` moves current toward target by rate and snaps to the target without overshoot. The
rate is not recomputed each tick. For example, the crouch released at takeoff falls linearly through the whole
flight at the rate requested on release. Known triplets include charge/crouch, brake, turn, extraLean,
animationTurn, balance and the two prewind channels.

`0x00113E80` requests the turn target. `0x00113F88(rider, crouch, brake)` requests crouch and brake targets,
which exclude each other. For the default non-braking charge path it sets the target to 0 or 1 with rate:

```
gap  = abs(target - current)
rate = gap >= bits 3DCCCCCD (0.1) ? gap * bits 3DCCCDC2 (~0.1000018) : bits 3C23D7CF (~0.0100002)
```

### Surface (material) records

The surface records form an array with stride 0xB0 (44 words). It is reached as
`*(*(*(0x004A28A8) + 0x84) + 0x44)`, where `0x004A28A8` is gp−0x848 and gp = `0x004A30F0`. The captured
Snow Jam state holds 19 records (PS2). The contact's record index is rider +0x438.

| Record offset | Use |
|---|---|
| +0x00 | Cruise gravity G, cm/s². Surface 0 in Snow Jam: 1300.850341796875 (PS2) |
| +0x10 | Passive-takeoff distance threshold |
| +0x14 / +0x18 | Powder depth parameters. Scaled by body scale, they give the targets that owner +0x4/+0x8 approach (pairing with h1/h3 assumed). Snow Jam glide values after smoothing: 0.425 cm and 2.1285 cm (PS2) |
| +0x1C | Normal damping D. Surface 0: 5.005756855010986 (PS2) |
| +0x28, +0x2C, +0x30, +0x34 | Cruise heading response coefficients |
| +0x38 | Ground alignment rate |

Surface IDs 2, 3 and 13 have special handling (see velocity correction and extra lean). The trajectory
predictor also uses ID 13 for instance-only hits.

## Per-tick order

- The shared world update `0x00128AF0` builds the list of selected participants and refreshes manager
  proximity (`0x0010F560`). It then runs each phase for **all** actors before starting the next phase:
  `0x00120F20`, `0x00121068`, `0x001210B0`, `0x001211F8`, `0x001216E0`, `0x00121700`, `0x00121728`, `0x00121750`,
  `0x001217F8`, `0x00121818`, `0x001218D0`, `0x00121950`. It does not complete one rider before starting the
  next.
- Local-pose sampling and animation completion events come before world-pose generation.
- Rider-pair overlap uses the current collision spheres. Reaction points use proximity that is refreshed every
  6 manager ticks. Player-owned pair records drive the checks, and reciprocal timestamps suppress duplicate
  impulses.
- Physics runs at 60 Hz. Within a tick the controller (control-state handler) runs before the motion update.
  A takeoff requested by the controller therefore gets its first airborne step on the same tick (see Jump).
  This order is inferred from the jump and passive-air timing.

## Motion modes

`mode = *(owner + 0xDE0)`. The dispatcher `0x00111408` jumps through the six-entry table at `0x00456B50`.

| Mode | Target | Receiver | Role |
|---|---|---|---|
| 0 | `0x0013D818` | owner | Ground cruise (PS2) |
| 1 | `0x00139A20` | owner + 0x20 | Airborne (PS2) |
| 2 | `0x00136E98` | owner + 0x30 | Wipeout (PS2) |
| 3 | `0x00136958` | owner + 0xA0 | Active at the race-ready gate (PS2). Also called the reset motion (unconfirmed) |
| 4 | `0x0013AF28` | owner + 0xB0 | Not classified. Jump takeoff treats this mode specially |
| 5 | `0x001391A8` | owner + 0x110 | Not classified |

Modes have further entry points besides the update:
- gain focus: air `0x001399E0`, wipeout `0x00136C40`;
- a second phase: cruise `0x0013F178`, air `0x0013AA48`;
- a companion stage for wipeout: `0x00136EE0`;
- a contact/landing stage for air: `0x00139C88`.

Their vtable slots are not documented here. `0x0011FE78(rider, 1)` sets air mode, which triggers the air gain
focus.

**Wipeout.** `0x00136E98` calls `0x00136F30`, then runs `0x00137D18` if the wipeout object's +0 is zero,
otherwise `0x00137750`. The companion stage `0x00136EE0` selects `0x00138640` or `0x00137860`. Wipeout uses a
fixed gravity of 1800 cm/s² and its own drag. These differ from cruise.

## Control states

The control state is at owner +0xDE4. It is the controller layer that sits above motion. The update handlers
are listed below. `0x00127998` switches on the state through a 14-entry table at `0x00457EA0` to build the
command.

| State | Update | Role |
|---|---|---|
| 0 | `0x00131620` | Cruise |
| 1 | `0x0012FC80` | Not named in the notes |
| 2 | `0x0012E9B8` | Prewind / jump charge (gain focus `0x0012E980`) |
| 3 | `0x0012E778` | Soft collision |
| 4 | `0x0012F730` | Passive air (entry `0x0012F620`, exit `0x0012FB68`) |
| 5 | `0x00133308` | Air tricks (entry `0x00133128`, exit `0x00134CB0`) |
| 6 | `0x0012BF68` | Race start |
| 7 | `0x00131D30` | Rail |
| 8 | `0x0012CB68` | Crash |
| 9 | `0x0012F398` | Reset |
| 10 | `0x0012C678` | Not named in the notes |
| 11 | `0x00132A30` | Handplant |
| 12 | `0x00136508` | Rail Uber |

## Ground cruise (mode 0)

### Phase 1: `0x0013D818`, in order

1. Call `0x00125970`.
2. Clamp speed to rider +0x2E4 (`0x0013D89C..0x0013D8C4`). This is the first of two speed clamps.
3. Compute `dt = rider[+0x300] * float(1/60)` (`0x0013D8E0..0x0013D8F0`). Cache the current surface record
   pointer (`0x0013D8F4`).
4. Smooth the contact depths (owner +0x4/+0x8). Project the relative velocity `v − surfaceVelocity` onto the
   normal (+0x370), forward (+0x3A0) and lateral (+0x3B0) axes.
5. Force terms:

   | Helper | Called at | Arguments | Role |
   |---|---|---|---|
   | `0x0013C878` | `0x0013DA38` | controller, surface, contact distance, normal relative speed | Normal acceleration and compression |
   | `0x0013C948` | `0x0013DA48` | controller, surface | Forward drive and auto-boost, heading alignment, crouch and animation-state effects |
   | `0x0013CCF0` | `0x0013DA64` | controller, surface, forward speed, normalised normal term | Longitudinal friction/braking. Uses surface depth factors, stance and stats |
   | `0x0013D028` | `0x0013DA80` | controller, surface, lateral speed, forward speed, −rider[+0x1F0] | Lateral response with a speed curve and stats |

6. Assemble the acceleration from terms along all three surface axes, rotate the normal force, and add explicit
   gravity `(0, 0, −G)` (`0x0013DCD0..0x0013DCE4`). The force direction used here is a temporary vector,
   distinct from the board normal +0x390.
7. Apply penetration correction/contact clipping and low-speed braking.
8. Integrate position first, using the **old** velocity: `p += v*dt` (`0x0013E0A8..0x0013E0DC`). Then
   `v += a*dt` (`0x0013E0E8..0x0013E120`).
9. Heading stage `0x0013E22C..0x0013EB98`, using the relative velocity from before integration.
10. Terrain contact query `0x0013D1B8`, called at `0x0013EBA0` (see Terrain contact).
11. Post-contact velocity correction `0x0013EBF4..0x0013ED24`.
12. Passive-takeoff test at `0x0013ED28`.
13. Surface alignment `0x0013ED68..0x0013EE9C`.
14. Ground tail `0x0013EEA0..0x0013F064`.
15. Unconditionally call `0x0011E098` at `0x0013F11C`.

### Normal response `0x0013C878`

Let d = signed distance (+0x454), vn = outward normal relative speed, h1/h3 = smoothed depths, G = surface
gravity and D = damping.

```
d > 0:          a = G * (d * float(-0.03333299979567528));  if vn > 0: a -= D*vn
-h1 < d <= 0:   a = (-G*d)/h1 - D*vn
d <= -h1:       d = max(-h3, d);  a = G*(1 - 2*(d + h1)/(h3 - h1)) - D*vn
compression (rider +0x758) = max(-d/h3, 0)
```

Operation order is as written. The stat getters used by the other force helpers are listed under Stats.

### Heading stage `0x0013E22C..0x0013EB98`

- **Inputs.** The pre-integration relative velocity, the physical and surface axes, filtered turn and charge,
  the control state, the frame time, the stance flag and the transient angle at +0x2DC.
- **Parameters.** Surface +0x28..+0x34, plus three four-point curves reached through pointers at
  `0x004A1130` (gp−0x1FC0), `0x004A1138` (gp−0x1FB8) and `0x004A1158` (gp−0x1F98).
- **Velocity alignment** runs in every control state. It needs nonzero speed. Control state 2 adds the gate
  `normal.z > 0.65`.
- **Desired rotation.** This is the signed arcsine of the normalised cross product of velocity and forward,
  taken about the surface normal, plus turn and charge biases. The response depends on speed, slope, steering
  sign and the surface coefficients, and it is limited to a fixed angle per tick.
- **The +0x2DC path.** It measures orientation against the velocity in the ground plane. It respects stance,
  wraps the angle and handles rotations beyond π, and it combines with the automatic alignment. +0x2DC is
  reduced by the rate step only when its magnitude exceeds π. A smaller value is cleared once the heading
  error is small enough.
- **A separate direct steering term** uses the body's forward-facing fraction of speed and the curve at
  `0x004A1158`. That curve's four ordinates are all zero in the Snow Jam data (PS2), so this term adds nothing
  there.

### Post-contact velocity correction `0x0013EBF4..0x0013ED24`

This runs for surface IDs other than 2, 3 and 13. It uses the new contact's ID:

```
add = normal * (-0.4 * dot(relVel, normal));  add.z = max(add.z, -40)
relVel' = rescale(relVel + add) to |relVel|;   v = relVel' + surfaceVelocity
```

### Passive takeoff

The test at `0x0013ED28` reads the threshold at +0x10 of the surface record cached **before** the contact
query. Passive takeoff is requested in either of two cases:

- the query finds no contact;
- +0x308 is nonzero and the contact distance is above that threshold.

The takeoff itself is `0x00114298` with a negative charge. It runs at the end of this ground tick, in the second
phase. Airborne integration starts on the **next** tick.

### Surface alignment `0x0013ED68..0x0013EE9C`

This stage runs only when a contact-result value kept in a local of `0x0013D818` (stack +0x148) is below 5 cm.
It reads +0x38 of the old cached surface (at `0x0013EE84`).

```
target = normalize(n.x, n.y, 1.5*n.z);  axis = cross(target, physicalUp);  s = length(axis)
if s > 0.001: rotate about normalize(axis) by -asin(min(s,1)) * float(1/60) * surface[+0x38]
```

### Ground tail `0x0013EEA0..0x0013F064`

- Once the rider leaves the landing animation class, this stage restores the board-alignment targets. The
  ordinary rate is dt×3. Animation classes 10 and 5, and semantics 2 and 22, disable alignment.
- Extra lean follows the curve at `0x004A1128` (gp−0x1FC8), but only on surfaces 2 and 3 and outside control
  state 1. Otherwise its target is 0.

### Phase 2: `0x0013F178`

- Body and board pose queries during the tick use the **old** +0x390. Only afterwards does
  `0x0013F2E4..0x0013F354` write `+0x390 = normalize(old390 + 0.5 * current370)` for the next tick (PS2).
- A final speed clamp at `0x0013F358..0x0013F3A8` is separate from the first clamp.
- The pending passive takeoff runs here.

Collision-phase direction changes are handled in `0x0013F488` (not decoded).

### Surface transitions

The contact query updates +0x438 during the tick (at `0x0013D64C` inside `0x0013D1B8`). Velocity correction branches on the new ID.
Passive-takeoff height and alignment still read the old cached record. Forces use the new material from the
next tick. The speed limit computed at frame begin is kept across the change.

### Dynamic speed limit `0x0011B3F8`

This runs at frame begin and writes +0x2E4. Its inputs are the 48-float table at `0x004A6310` (in `.bss`), the
normalised top-speed stat, a surface factor, charge/boost and stance.

1. Interpolate between the standing and crouched limits for the minimum and maximum stat.
2. Convert km/h to cm/s.
3. Smooth with retention 0.9 when the limit rises and 0.97 when it falls.

### Stats

A stat is an integer progress byte divided by 5, then divided in floats by the character's maximum byte. The
float division rounds to nearest. A special player flag can make the result 0.5. Zoe's baseline stats come out
as nearest(1/11), bits `3DBA2E8C` (PS2).

| Getter | File | Progress byte / max byte | Use |
|---|---|---|---|
| `0x001494C0` | beintstat | +0 / +8 | Top speed (dynamic limit) |
| `0x001493D8` | beintstat | +1 / +9 | Ground force helpers (unconfirmed which) |
| `0x00148D80`, `0x00148E68` | beintplayer | +3 / +11 | Ground force helpers (unconfirmed which) |
| `0x001495A8` | beintstat | +4 / +12 | Air/trick stat |

## Terrain contact

### Cruise ground query `0x0013D1B8`

1. Copy +0x370 to +0x380.
2. **Query centre** = position + previousLateral × 45 cm × filteredTurn × geometryScale. This uses the lateral
   tangent from **before** the query; +0x3B0 after the query is the recomputed tangent (PS2). Zoe's
   geometryScale is 0.8499999642372131 (PS2).
3. The endpoints are centre − 100 cm and centre + 200 cm along the previous normal, which is not renormalised.
4. **Candidates** must have authored flag bit 0. Loaded candidates must also have bit 0x40, which world
   streaming sets (PS2).
5. **Grid.** Each bicubic patch is evaluated as 9×9 cells, a 10×10 point table ordered outer U, inner V. A
   VU0 microprogram computes it from the power table (see Floating-point behaviour).
6. **Cell scan** `0x0032B6E0`. If the cache's patch matches, the cached cell/triangle is tried first. Otherwise
   cells are scanned with U outer and V inner, trying triangles (d, b, c) then (c, b, a). `0x0032E4D0`
   intersects the triangle plane and a VU0 microprogram tests inclusion. The first hit cell seeds refinement.
7. **Refinement** `0x0032E9A0` performs exactly four Newton updates. It returns early if U or V leaves [0, 1],
   and the caller then keeps the coarse point and normal. The refined normal is `cross(dv, du)`. The coarse
   fraction remains the ranking key.
8. **Selection** (in `0x0013D42C`, inside `0x0013D1B8`). Candidates with `dot(normal, prevNormal) >=
   0.30000001192092896` are preferred. Within that group the smallest `abs(coarseFraction − 0.5)` wins, with
   ties broken by packed resource ID. The generic selector `0x003342D0` does not have this normal preference.
9. **Distance.** +0x454 = `dot(centre − point, normal)`. The clearance (`0x0013D7F8`) is the length of the
   tangential remainder. Both use the query centre, not the bare position.

Contact points, normals and UVs from this procedure match the game at glide, brake, charge, jump and turn
checkpoints (PS2).

**Cache** (`*(rider+0x864)`):

| Offset | Field |
|---|---|
| +0x0 | Patch pointer |
| +0x4 | U cell (u16) |
| +0x6 | V cell (u16) |
| +0x8 | Triangle half (1 = first, 0 = second) |
| +0xC | Query kind |

The cache is updated as candidates are visited, including candidates that are not finally selected.

**Surface ID.** The patch's signed 16-bit field at +8 is copied by `0x00335960` into query result +0x4C.
`0x0013D1B8` then stores it in +0x438, with −1 and no contact mapped to 0.

### Query kinds

| Kind | User | Terrain handling | Ranking |
|---|---|---|---|
| 1 | Trajectory predictor | 9×9 coarse grid, no Newton. Returns the coarse triangle point and normal, plus the cell-centre UV | Fraction closest to 1. Instances win ties |
| 2 | Landing probe | 9×9 grid plus four Newton updates, using the cell cache | Fraction nearest 0.574999988079071, with the generic instance/terrain tie break |
| (not given) | Cruise query `0x0013D1B8` | As kind 2 | Normal preference, then fraction nearest 0.5 |

- `0x0032E100` builds the ray query. Its f12 argument is the preferred fraction, not a radius.
- `0x00336850` queries terrain and instances. `0x003378C0` queries instances only.
- The instance primitives in `riderspheretree.cpp` are:
  - `0x0032E288`: bounds.
  - `0x0032E398`: transform.
  - `0x0032E690`: box entry/exit.
  - `0x0032E4D0`, `0x0032E5E8`: authored-normal triangles (VU0 barycentrics).
  - `0x0032E688`: returns zero sphere-tree ray contacts.
- Kind-1 terrain results match the game's captured caches (PS2).

## Orientation primitives

- **`0x0011DFE0` (world-axis rotation).** Forms `(axis·sin(angle/2), cos(angle/2))` and composes it with the
  physical quaternion as a world-axis rotation. It does not normalise; an immediate call to `0x0011E098`
  follows.
- **`0x0011E098` (`cRider_updateOrientationImplicit`).** Normalises +0x120 and rebuilds +0x1A0/+0x1B0/+0x1C0
  in VU operation order.
- **`0x0011E150`.** Rebuilds actor bounds only. It does not rebuild posed bones.
- Steering uses the game's sin/cos `0x0031BE50` and atan `0x0031C228` (see Floating-point behaviour).

## Jump: charge, prewind and takeoff

### Controller flow

1. **Cruise (control 0, `0x00131620`).** The first jump press calls `0x001162C8` at `0x00131794`, which
   changes control 0 to control 2. A nonzero return exits at `0x0013179C` before any charge request. The jump
   latch +0x360 controls this: a press always requests control 2, while a held button alone requests it only
   when the latch is zero. Control 2 releases when the held input is gone, including after a press-only pulse.
   Gain focus `0x0012E980` leaves the charge triplet unchanged.
2. **Held (control 2, `0x0012E9B8`).** `0x0012EA24` tests bit 0x2000 (JumpHeld) of the decoded command.
   - While held, `0x00113F88(rider, 1, 0)` is called at `0x0012EB70`.
   - Spin and flip are thresholded at ±0.2 to request prewind targets of −1, 0 or +1.
   - Style 0 uses rate `5.000027179718018 * abs(target − current) * float(1/60)`. Other styles use
     `5.0000901222229` in place of the first factor.
   - Animation class 10 and animation index 21 request zero with rate 0.08333379030227661.
   - The reverse-turn branch (`0x00114CC0`) has its own physical and animation effect.
3. **Release** (branch from `0x0012EA30`):
   - Snap the already-filtered prewind using angle step bits `3F490FDC` (≈π/4; one ulp above float π/4) and
     deadzone 0.2.
   - Call `0x00114298(rider, rider[+0x220])` at `0x0012EAFC`, unless the motion mode is already airborne.
   - `0x0011FE78(rider, 1)` at `0x0012EB08` switches to air motion. Its gain focus `0x001399E0` starts the
     trajectory from the updated position and velocity.
   - Request zero turn, crouch and brake (`0x00113F88(rider, 0, 0)`).
   - Enter control 5 through `0x0011FEC8` → `0x00111538` → `0x00111630` → `0x00133128`.

Control 5 is entered inside the release handler, and its update handler first runs on the next tick. The air
motion update does run on the release tick. The launch reads the charge from before that tick's triplet
advance.

### Takeoff `0x00114298(rider, q)`

Let `v` = velocity, `speed = |v|`, n = +0x370 and f = +0x3A0.

```
if q >= 0:  base    = speed < 972.1808471679688 ? speed*0.357146680355072 + 361.203125 : 708.4142456054688
            impulse = clamp(q*q*base, 361.203125, 708.4142456054688)
else:       impulse = 0.16339834034442902    (passive; no clamp; also owner[+0x14] = -1)
```

- **Direction.** In motion mode 4 the impulse follows physical up (+0x1C0). Otherwise
  `dir = normalize(n + 0.2*f)`. If the forward tangent is descending, the velocity is descending, or the slope
  factor is below zero, then `v += dir*impulse`.
- **Rising-ramp branch** (`0x001144C4..0x00114794`):
  1. `slope = (n.z − cos50)/(cos70 − cos50)`, using bits `3F248DBA`, `3EAF1D41` and sin20 = bits `3EAF1D45`.
  2. Remove the horizontal normal component from forward and from velocity, and normalise both.
  3. `blend = clamp(slope * projForward.z / sin20, 0, 0.95)`.
  4. Take the normalised blend of the ordinary direction and the projected forward.
  5. Blend the original velocity with `projVelocity * (blend*speed)`.
  6. Add half the impulse along the blended direction.
- **The remaining code** covers:
  - horizontal velocity lost in the launch;
  - nearly vertical takeoff surfaces, using +0x380;
  - the speed cap at +0x2E4;
  - reduced takeoff soon after landing. This applies to active charge unless +0x434 is 11..13. Its time is
    seconds since owner +0x10 (ground focus). The factor is 0.6939882636070251 up to 0.5388872623443604 s,
    then rises linearly to 1 with multiplier 1.2326725721359253.
- **Global tick accessor** `0x001298C8` returns `*(*(*(*(0x004A28A8)+0x84)+0x0C)+8)`.

A real downhill release reproduces the post-launch position, velocity and charge bit-exactly (PS2).

## Air motion (mode 1)

### Update `0x00139A20`

1. Trajectory update `0x00113648`.
2. Orientation tail `0x00139A64..0x00139C68`:
   - At `0x00139A70..0x00139A8C`, copy the retained presentation up (+0x180, from the previous pose) into
     +0x370 and clear +0x3D0.
   - Physical alignment `0x00121AA0`, gated by prediction status, surface and flags, with a remaining-time
     gain. Heading correction is suppressed during manual adjustment.
   - A final unconditional normalisation.
3. The contact/landing stage `0x00139C88` follows (see Landing).

### Fixed-step integrator `0x001139A0`

Called in 60 Hz steps by `0x00113648`:

```
p += v*dt                                  (multiply and add rounded separately)
vx += vx*drag;  vy += vy*drag
vz += (vz > 0) ? rise : fall
if |v| > cap (trajectory +0xA8): scale v to cap    (divide at 0x00113A74, round to nearest)
```

| Constant | Bits | Value |
|---|---|---|
| dt | `3C888889` | 1/60 s |
| drag | `BB5A740F` | −0.2/s × dt |
| rise | `C162AAAB` | −850 cm/s² × dt (while rising) |
| fall | `C1FD5556` | −1900 cm/s² × dt (otherwise) |

The trajectory cap in the Snow Jam data is 3333.33349609375 cm/s (PS2). All position and velocity bits match
the game at falling and rising checkpoints and at a speed-cap step (PS2).

### Trajectory predictor (`cAirPredictor`)

The predictor keeps predicted and current integrated positions and velocities separately.

**Extension `0x00113200`.**
- Advances 60 Hz steps until the step count exceeds `270000/speedLimit`, or until
  `dot(initialUnitDir, v) < 0.99*|v|`.
- Records the last non-descending position and time as the apex.
- Extends the chord by 2% at each end and queries **backwards** from the predicted end, with kind 1 and
  preferred fraction 1.
- Uses `0x00336850` in status 0 and `0x003378C0` (instances only) in status 2.
- A hit with nonnegative fraction is accepted only if the extended forward chord faces against the normal.
- The reverse fraction interpolates heading between the old and new velocities and adjusts the prediction
  time. It does not compensate for the 2% extension.
- A status-2 hit becomes status 3, with surface 13 and world up. Ordinary hits keep surface, normal, patch ID,
  flags and coordinates.

**Update `0x00113648`.**
- Extends the prediction lazily.
- Reseeds a status-1 prediction that is more than 0.2 s behind the current elapsed time. The reseed copies
  current motion into both state pairs and sets prediction time to elapsed. It keeps elapsed time and the
  integrated-cache time.
- A prediction beyond 60 s switches to status 2, and falls back to status 3 if that also passes the horizon.
- Actual motion advances a separate fixed-step cache. It takes the interpolation branch only when the
  remainder exceeds 0.01 s.

| Status | Meaning (from the transitions above; labels partly unconfirmed) |
|---|---|
| 0 | Searching terrain and instances |
| 1 | Landing predicted |
| 2 | Secondary search, instances only |
| 3 | Instance hit or horizon exhausted (surface 13, world up) |

An isolated flight that starts in status 0 is in status 1 thirty ticks later. At that point it has a predicted
ground contact 5.263 s after the initial epoch (PS2). `cAirPredictor_reset` and
`cAirPredictor_startLaunchIntoAir` leave the stored hit position untouched, so stale bytes stay there while it
is inactive (PS2).

### Physical alignment `0x00121AA0`

This covers up alignment (`0x0031BB30`), optional heading correction, a quaternion delta with the shortest
sign, a gain-limited and capped angular rate, and a final normalisation.

## Air control (control 5)

- **Object.** Owner +0x230, with the actor pointer at +0x58.
- **Entry `0x00133128`** starts from the filtered prewind triplets at +0x2A4/+0x2B0. Prewind produces different
  initial rates and a continuation mode.
- **Update `0x00133308`.** `0x001333E0..0x00134334` handles the command-prefix modes and the ungrabbed
  angular phase, target, rate and offset updates.
- **`0x001158B8`** applies the deadzone and angular snapping of the spin/flip pair.
- **State.** Spin and flip each have a target, progress, total angle, air-adjust offset, hold timer and
  completion phase.
  - The initial target is 180° for spin and 360° for flip.
  - Holding the input extends the target, and releasing it lets the angle settle toward a completion target.
  - Input reversal, stat factors (`0x001495A8`), prewind continuation and the +0x2EC modifier follow the
    original branch order.
- **Timing.** The angular update runs before translation in the tick, and the pose is formed after the
  position update.

A 30-tick positive spin from an isolated airborne state matches every angular field, rate, timer and position
and velocity float (PS2).

**Presentation (`0x0011EB98` calls `0x00134DD0` in control 5; `0x00135180` is also part of this stage).** Spins
do not write +0x120. The rendered pose is built from the physical pose:

1. Shift the position to the animated skeleton pivot, which is the scaled skeleton point indexed by +0x89C.
2. Append a local-Z rotation by `−(totalSpin + adjustSpin)`.
3. Update the flip-axis blend from the two angular rates.
4. Append a rotation by `totalFlip + adjustFlip` about the blended local axis.
5. Shift back from the pivot using the new quaternion.

`0x00134DD0` advances its axis blend, so the normal update runs it exactly once per tick.

**Control-5 command** (from the human provider `0x00127998`):

| Field | Content |
|---|---|
| word0 bit 12 / 13 / 14 / 15 | ResetPath / Handplant / Tweak (Square, same button as BoostHeld) / LateSpin (the input map compiles LateSpin to literal 0, so it is never set) |
| word0 bits 16..23 | Grab index 0..14 as a signed byte. −1 (FF) means none; 0 is a real grab |
| word0 bits 24..29 | Spin, signed 6 bit |
| word1 bits 0..5 | Flip |
| word1 bits 6..11 | AirAdjRotFB (action 10, written inside `0x00127998` at `0x00128500`/`0x00128528`) |
| word1 bits 12..17 | AirAdjRotLR (action 11) |
| word1 bits 18..19 | Board-press step: raw < −0.5 gives 3 (−1), > 0.5 gives 1, else 0 |

- Axes are packed as `trunc(value*31) & 63` and decoded as signed 6 bit × bits `3D042108` (≈1/31).
- Grab indices 0..14 are the first active of Trick1..15 (`0x001276F0`). They correspond to the shoulder
  masks 1, 2, 4, 8, 3, 5, 9, 6, 10, 12, 7, 11, 13, 14, 15, with bits in the order L1, L2, R1, R2.

## Passive air (control 4)

**Entry.** `0x00131620` calls `0x00131CC0` before its ordinary input handling. If motion is already airborne,
`0x00131CC0` requests control 4 and returns 1, and `0x00131620` returns immediately. Entry `0x0012F620` runs on
that tick. Update `0x0012F730` starts on the next controller tick, and `0x001211F8` still runs in between.
Control 4 is a separate path from explicit-jump control 5.

**State at owner +0x210:**

| Offset | Field |
|---|---|
| +0x0 | Entry angle |
| +0x4 | Entry magnitude |
| +0x8 | Upper latch |
| +0xC | Identity latch |
| +0x10 | Signed last identity |
| +0x14 | Actor backlink |

**Entry `0x0012F620`.**
- Sets `angle = atan2(currentCrouch, currentTurn)` and `magnitude = max(abs(currentTurn), currentCrouch)`.
- Both latches start at 1 and the last identity at −1.
- Prewind rates are set to float 1/30 and targets to 0. Current prewind values and the ordinary turn, crouch
  and brake controls survive.
- No animation is requested.

**Command** (provider case at `0x00128280` inside `0x00127998`):

| Field | Content |
|---|---|
| word0 bit 12 | ResetPath (recovery) |
| word0 bit 13 | Handplant |
| word0 bit 14 / 15 | AttackLeft / AttackRight |
| word0 bits 16..23 | Signed identity (grab) |
| word0 bits 24..29 | CruiseTurn |
| word1 bits 0..5 | CruiseCrouch |

**Update `0x0012F730`.**
- Calls, in order: recovery `0x00116120`, upper action `0x001163B0`, optional handplant `0x00107578`, and
  automatic rail attachment `0x00106848`.
- The upper-action return is checked only while the upper latch is set. After release,
  `0x001163B0(false, false)`'s return is ignored.
- A failed handplant changes the crouch request to 1.
- Boost `0x00114130` receives (false, false).
- The identity latch tracks a continuously held identity. If the identity changes or is released, or the
  directional input drops enough or turns more than a quarter turn from entry, the magnitude becomes −1 and
  both directional targets become 0.
- Turn, animationTurn, crouch and brake use target rate bits `3D4CCCCE` (≈0.05). AnimationTurn targets the old
  filtered physical turn, and brake targets 0.
- While settling, class-9 clips are left alone. Otherwise class 9 or 10 is chosen from the filtered
  turn/crouch blend.
- Once filtered turn, brake and crouch are all exactly 0 and the identity latch is released, it requests
  animation 287 (unless 287 or a class-9 clip is already current). It then requests control 5, after the
  target writes.

**Exit `0x0012FB68`.** Upper class 3 or 13 triggers a 0.1 s fade on channel 0 and sets channel 1's sequence rate
to 1. The two channels differ.

## Landing

### Probe (`0x00139C88` → `0x0013A7B0`)

- The presentation `0x00134DD0` advances once per tick before the probe.
- The ray is centred on the posed board-root bone (+0x8A0). Its endpoints are centre ∓ 200 cm × presentation
  up (+0x180). It uses neither the actor position, the physical up nor the previous terrain normal.
- The query is kind 2 and uses the +0x864 cache (PS2: query results and cache contents match captured
  states).
- **Touchdown** requires fraction ≥ 0.5 and `dot(v − surfaceVelocity, hitNormal) < 0`. There is no segment
  test between successive positions.

### Transition on touchdown

1. **Exit control 5 through `0x00134CB0`.**
   - Run the presentation function once more as an exit event (separate from the per-tick advance).
   - Bake its position and quaternion into the physical pose and normalise with `0x0011E098`.
   - Reset the prewind triplets and quantise the retained manual spin.
   - The channel-1 fade is an animation event.
2. **Contact response `0x00139D78..0x0013A148`** (inside `0x00139C88`).
   - Clear the predicted landing time and check the authored recovery flags.
   - Resolve penetration using the material's **unscaled** depth3.
   - Apply the normal impulse and the material's normal-speed limit.
   - Update the contact frame, surface, point, patch/UV and signed distance.
3. **Classification `0x0013A14C..0x0013A4CC`** (inside `0x00139C88`). Uses the animation class and flags, the physical orientation,
   the manual state and the roster landing stat. The upright-crash branch depends on the RNG.
4. **Clean ordinary landing: `0x0013C7A8` enters ground motion.**
   - Reset the board oscillator, scale the authored depths by body scale and set the board normal.
   - Multiply velocity by a factor based on ticks since leaving the ground: 0.7 up to 40 ticks, then
     `0.7 + (ticks − 40) * bits 3C23D70B (0.01)`, capped at 1.
   - Store the new ground-focus tick. Normal control entry clears the jump latch.
   - The charge triplets are not reset.
   - Landing clips 0x3D, 0x3E, 0x3F, 0x42 and 0x43 follow the impact and manual-spin branches. Reverse
     touchdown selects 0x40/0x41; the hex base is inferred from the neighbouring clip numbers.
   - The scoring and boost award is a separate event (`0x0010E910`).
5. **Second phase `0x0013AA48`** runs on the touchdown tick.
   - Reads the cached pre-landing body spheres (+0xAA0) and presentation up.
   - Body pushes move the actor position and the cached sphere centres, then the air bounce is applied.
   - Uses the +0x868 body cache with authored surface filter 2.

## Stance

### Reverse stance (`0x00114CC0`, `0x00115168`)

**`0x00114CC0`.**
- Projects velocity onto the contact forward (+0x3A0).
- Requires brake 0 and forward speed ≤ −111.1111145 cm/s.
- Composes the physical orientation with the exact quaternion `(boardUp, 0)`, a 180° rotation, and normalises.
  A trigonometric 180° rotation gives different bits.

**`0x00115168`.**
- Toggles stance (+0x320).
- Negates the contact forward and lateral axes.
- Negates current and target of turn, brake, extraLean, animationTurn and balance.
- Animation gets a separate reverse event for its per-sequence root transforms and base root/mirror state.

**Call sites.** Cruise control calls these at `0x001318EC` (inside `0x00131620`), after target requests and
before the landing-class hold branch. Reverse is also evaluated at touchdown, where it selects clips 0x40/0x41.

### Stance restoration `0x00115640`

This runs when a temporary prewind/side style (+0x328) ends, including when soft control completes. It does not
choose a control or motion mode.

| Condition | Physical state | Animation |
|---|---|---|
| style = 0 | No-op | None |
| motion 1, style 3 | Unchanged | Reset default root; request 282 |
| motion 1, style 4 | Unchanged | Reset default root; request 277 |
| motion 1, other style | Unchanged | Request 268 |
| motion 0, style 3 | Rotate about old physical up (+0x1C0) by +π/2 (bits `3FC90FDB`) | Transform sequence roots; reset default root; request 5 |
| motion 0, style 4 | Rotate by −π/2 (bits `BFC90FDB`) | As above |
| motion 0, other style | Unchanged | Request 5 |
| other motion | Unchanged | None |

- **Order.** Publish the physical rotation (`0x0011DFE0` then `0x0011E098`), transform the existing sequence
  roots, reset the default root, then request the clip. +0x328 is cleared after the request. The final
  `0x00116930` call is a no-op.
- **Sequence roots.** `0x00311B48` (`cRiderAnimBase_changeHeadingOffset`) rotates the existing sequences on
  six channels with a Z quaternion from `sincos(−angle*0.5)`. It does not touch the default root.
- **Default root.** Direct stores then set the default root to position zero and the quaternion from
  `sincos(−0)`, which keeps the signed zeros.
- **Requests** go through `0x003128E8` (`cRiderAnimBase_play`) with blend −1 and flags 0.
- **Not modified:** reverse stance +0x320, mirror flags, contact axes, prewind triplets and velocity.
