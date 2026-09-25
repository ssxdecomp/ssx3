<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/bx/

## `src/bx/bxstringctor.cpp`

Segment `0x00268890`-`0x0026B310`.

- **`0x00269F18`** - Event-aware path position sample used by reset routing: starts two candidate distances at input+50 cm; for event intervals containing the input (inclusive), event 16 extends the alternate to the interval end, 12 lowers the selected distance to the start and 14 raises it to the end; if selected == input the alternate is used. Writes the distance back by reference and samples via `0x0026AB20`. *[static]*
- **`0x0026A090`** - Converts course remaining distance to path-local distance for event queries. *[static]*
- **`0x0026A428`** - Projects a position onto a path candidate; called by route selection `0x00112A50`. *[static]*
- **`0x0026A638`** - Course/AI path projection with cached forward search (horizontal metric, segment clamp, 3000 cm horizon); the cache holds segment start position, accumulated local distance and segment index, and a valid cached interior projection may stop early. `0x00112180` uses it to derive the rider's remaining distance (+0x4D0/+0x4D4). *[static]*
- **`0x0026A8B8`** - Path segment direction at a distance (cumulative segment lengths, inclusive bounds, last-segment fallback). *[static]*
- **`0x0026AA80`** - Inclusive course-event interval query (rider event capacity 12). *[static]*
- **`0x0026AB20`** - Samples a path position at a distance; the authored path sampling primitive used by route selection and reset routing. *[static]*
- **`0x0026AC48`** - Path routine called by route selection `0x00112A50`. *[static]*
- **`0x0026AF98`** - Candidate path gather: calls `0x0026AFB8` with requireField3C=true and at most 6 candidates. *[static]*
- **`0x0026AFB8`** - Candidate path search for AI routes and reset: filters on field +0x3C, orders candidates and applies a candidate limit. *[static]*
- **`0x0026B178`** - Three-candidate bounding-box ordering for course path selection. *[static]*

## `src/bx/bxrandom.cpp`

Segment `0x003177C8`-`0x00317AE8`.

- **`0x003177F0`** `BXrand__Fv` - Draws one value from the visual/presentation random generator (six-word state at `0x004FF018`, same algorithm as the gameplay RNG; each draw increments state word 5). Consumers include particle births and emitter seeds/flipbook phase (`0x00370E14`), grind chunks, emitters `0x003710D0`, camera splash and shake, ScreenTint lightning, crowd flashes, MeshAnim, flag wind, audio helper `0x002ADF60` and awards. All race draws happen in the game update (about 6-10 per tick), never at render time. *[PS2]*
- **`0x00317810`** `AIrand__Fv` - Gameplay RNG draw on the shared state at `0x004FF030`; draws must be consumed in the original order across riders. Used by builtin 77. *[PS2]*
- **`0x00317830`** `AIrandf__Fff` - Draws one value from the gameplay/shared RNG (`0x004FF030`); spline ctor `0x00359460` makes one draw even with zero jitter. *[PS2]*
- **`0x00317958`** `cBxPseudoRng_Seed` - Seeds a six-word add-with-carry generator. *[PS2]*
- **`0x00317A08`** `cBxPseudoRng_NextInt` - Draws from a six-word add-with-carry generator (same generator type as the shared game RNG). *[PS2]*

## `src/bx/ps2main.cpp`

Segment `0x0031ADB0`-`0x0031C350`.

- **`0x0031ADB0`** `systemInit` - Boot init; seeds the presentation RNG from the CD clock (below). *[PS2]*
  - `0x0031AE94`: Seeds the presentation generator from sceCdReadClock: w0 ^ (w1 << 3) of the BCD clock words. *[PS2]*
- **`0x0031B748`** - Matrix-to-quaternion/transform helper paired with `0x0031B7A8`; used by camera output stage `0x00166F90` and the RollerModifier constructor. *[static]*
- **`0x0031B7A8`** - Matrix-to-quaternion conversion paired with `0x0031B748`; used by camera output stage `0x00166F90` and the RollerModifier constructor. *[static]*
- **`0x0031BB30`** - Up-vector alignment helper used by air physical alignment `0x00121AA0`. *[static]*
- **`0x0031BE50`** - Shared sine/cosine (sincos) routine used by steering, cameras, rim rotation construction, stance restore and half-angle rotations; also cited as building Euler rotation matrices for Spline/MultiSpline. Computes cos as sqrt(1 - sin^2) with SQRT.S at `0x0031BEEC`; standalone sine `0x0031BF60` uses a different polynomial. *[static]*
  - `0x0031BEEC`: SQRT.S f1,f5 (opcode 0x46050044) computing sqrt(1 - sin^2); the EE reads the operand from the Ft field (f5), not Fs (f0). *[static]*
- **`0x0031BF60`** - Standalone sine routine (different polynomial from the shared sincos `0x0031BE50`). *[static]*
- **`0x0031C040`** - Cosine polynomial routine; used by the board lift (+0x31C) oscillator and the POST_RACE_1 camera yaw oscillation. *[static]*
- **`0x0031C128`** - Arcsine routine (some earlier camera decodes mislabelled it). Used by the camera PID, the camera landing-angle getter `0x0015F780`, ground alignment and the rim angle block `0x00389E98`..`0x00389F9C`. *[static]*
- **`0x0031C228`** - Arctangent routine, probably two-argument (atan2, inferred from its use in grind style selection: angle = atan2(dot(boneZ,d), dot(boneX,d))). Used by steering, cameras, the rim angle block and to compute yaw/pitch from a path derivative for Spline/MultiSpline matrices. *[static]*

## `src/bx/cubicspline.cpp`

Segment `0x0031D660`-`0x00320920`.

- **`0x0031D660`** `cCubicSplineInterpolant_initCommon` - One of eight cCSICubicSpline routines (`0x0031D5A8`, `0x0031D5E8`, `0x0031D660`, `0x0031D700`, `0x0031D738`, `0x0031D7E0`, `0x0031D8B0`, `0x0031DEE0`) that build/evaluate the natural cubic splines of the jump and swing cameras; coefficients match a Burden-Faires natural spline with a cache tie rule. Per-routine roles are not separated. *[static]*
- **`0x0031D700`** - One of eight cCSICubicSpline routines (`0x0031D5A8`, `0x0031D5E8`, `0x0031D660`, `0x0031D700`, `0x0031D738`, `0x0031D7E0`, `0x0031D8B0`, `0x0031DEE0`) that build/evaluate the natural cubic splines of the jump and swing cameras; coefficients match a Burden-Faires natural spline with a cache tie rule. Per-routine roles are not separated. *[static]*
- **`0x0031D738`** - One of eight cCSICubicSpline routines (`0x0031D5A8`, `0x0031D5E8`, `0x0031D660`, `0x0031D700`, `0x0031D738`, `0x0031D7E0`, `0x0031D8B0`, `0x0031DEE0`) that build/evaluate the natural cubic splines of the jump and swing cameras; coefficients match a Burden-Faires natural spline with a cache tie rule. Per-routine roles are not separated. *[static]*
- **`0x0031D7E0`** - One of eight cCSICubicSpline routines (`0x0031D5A8`, `0x0031D5E8`, `0x0031D660`, `0x0031D700`, `0x0031D738`, `0x0031D7E0`, `0x0031D8B0`, `0x0031DEE0`) that build/evaluate the natural cubic splines of the jump and swing cameras; coefficients match a Burden-Faires natural spline with a cache tie rule. Per-routine roles are not separated. *[static]*
- **`0x0031D8B0`** - One of eight cCSICubicSpline routines (`0x0031D5A8`, `0x0031D5E8`, `0x0031D660`, `0x0031D700`, `0x0031D738`, `0x0031D7E0`, `0x0031D8B0`, `0x0031DEE0`) that build/evaluate the natural cubic splines of the jump and swing cameras; coefficients match a Burden-Faires natural spline with a cache tie rule. Per-routine roles are not separated. *[static]*
- **`0x0031DEE0`** - One of eight cCSICubicSpline routines (`0x0031D5A8`, `0x0031D5E8`, `0x0031D660`, `0x0031D700`, `0x0031D738`, `0x0031D7E0`, `0x0031D8B0`, `0x0031DEE0`) that build/evaluate the natural cubic splines of the jump and swing cameras; coefficients match a Burden-Faires natural spline with a cache tie rule. Per-routine roles are not separated. *[static]*
- **`0x00320550`** - Initializer that sets up vector constants, including root translation `0x004FF130`. *[static]*

## `src/bx/execman.cpp`

Segment `0x00320920`-`0x00320CA0`.

- **`0x00320BF0`** - Input map float getter: evaluates an action expression in the compiled INPUT.MAP VM. *[static]*
- **`0x00320C48`** - Input map bool getter: returns action value != 0; paired with `0x00321108`. *[static]*
