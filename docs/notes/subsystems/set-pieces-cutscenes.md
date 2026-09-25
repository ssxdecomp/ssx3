# Set pieces and cutscenes

Set pieces are the scripted, moving or animated parts of a course: chairlifts, bins and traffic running on
splines, waving flags and streamers, scrolling textures, animated props started by riders, particle trails,
pickups, halos and the 2D crowd. Stage (Luno) programs build them by attaching entities and modifiers to world
instances, and the entity pass updates them once per game tick. Cutscenes (EA's "NIS") are in-engine scripts,
streamed from `DATA/SCRIPTS/SCDAT.BIG`, that drive a script camera and animated riders inside the loaded world. They
are queued on NIS list players and chosen from per-location category lists. Only the backcountry first-arrival
shots and the boot and intro videos are movies.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

Hex constants that are not addresses are written with an `h` suffix (for example `210345h`). Resource and program
references in stage programs are words `id << 8 | track` (see luno-vm.md). The spline and rail references below
(`608h`, `1108h`, ...) are written in that form. Where these notes write `modifier+0xNN` or `entity+0xNN` for a
call target, they mean a method slot of that object as the source notes give it. Those notes do not always say
whether the offset is into the vtable.

## Where it lives

Source files are the decomp's current splits, as reported by the address lookup.

- `src/object/movenode.cpp`: the MultiSpline factory `0x00355B30` (`cMoveNode_addSpline`), the Spline factory
  `0x00355AD0`, the attach `0x003554B0`, the entity update / entity pass `0x00356198`, the moving-node update
  `0x003568B0` and `0x00356078`, the contact chain `0x00356AE0`, the rigid predicate method `0x00355420`, the
  emitter hand-over `0x003578A8` / `0x00355F10`, the PositionModifier `0x00356F10`, the ParentModifier
  (`0x00357038` ctor, `0x00357108` evaluate), the magnet hand-off `0x00357660` and the MultiParticle update
  `0x00357BF8`.
- `src/object/splinemodifier.cpp`: the MultiSplineModifier (ctor `0x00359F88`, clone helpers `0x0035A3F0` and
  `0x0035A458` (`cMultiSplineModifier_setupNodes`), update `0x0035A560`, evaluate `0x0035A5D8` / `0x0035AC20`,
  bounds `0x0035A918`, contact velocity `0x0035B200`, draw test `0x0035B418`), the SplineModifier tick `0x00359698`
  and matrix `0x00359830`, and the RailModifier ctor `0x0035B708`.
- `src/object/multiparticle.cpp`: `0x00359460`, which the notes identify as the SplineModifier constructor, and the
  MultiParticle removal `0x003581F0`.
- `src/object/railmodifier.cpp`: the UVScrollModifier (ctor `0x0035F6E8`, tick `0x0035F7D0`, draw `0x0035FC20`),
  the TexFlip ctor `0x0035F0B8`, the modifier-layer rail query `0x0035C698`, and helpers `0x00360B60`, `0x00361098`,
  `0x00361B90`, `0x00361BF0`, `0x00361C10`, `0x00361C20`.
- `src/object/flagset.cpp`: the flag manager and flag grids (`0x0034C548`, `0x0034BCA0`, `0x0034B228`
  (`cFlagSet_CreateMesh`), `0x0034C668`, `0x0034B818`, `0x0034B9B0`) and the node-matrix compose `0x0034DC90`.
- `src/object/flexrailnode.cpp`: the flag entity (`0x0034AC88`, ctor `0x0034ADD8`).
- `src/object/debouncenode.cpp` and `src/object/spline3d.cpp`: the kind-8 spline path helpers (`0x003451C0`,
  `0x00345248`, `0x00345048`) and the length `0x003454E8` (`cSpline_calcLength__FP7cSpline`).
- `src/object/animnode.cpp`, `src/object/instancenode.cpp`, `src/object/modifierblock.cpp`: handler-slot and
  contact plumbing (`0x0034E698`, `0x0034E600`, `0x0034E798`, `0x0034EBA0`, `0x0034EBE0`, `0x0034FCC0`,
  `0x0034FD00`, `0x00353098`) and the modifier container tick `0x00352C70`.
- `src/object/instanceman.cpp`: instance copy `0x00351270` (`cInstanceMan_copyInstance__FPvP15sInstanceStructT0`)
  and the MeshAnim functions `0x00351B40`, `0x00352230`, `0x00352500`.
- `src/intersect/worldsphtree.cpp`: the LiveComp player (ctor `0x00341AA0`, tick `0x00341D48`), the AnimTeeter
  (ctor `0x003421A0`, update `0x00342358`, force `0x00342538`), the one-way volume (`0x00341388`, `0x003415D0`,
  `0x00341818`), the spline rail query `0x00334680` and the ground snap `0x003369D8`.
- `asm/1FBE38.s` (unsplit): the stage builtins that build set pieces (`0x002FBCB8`, `0x002FC9C8`, `0x002FDED0`,
  `0x002FE0C0`, `0x002FF1C8`, `0x003019C8`); `src/wscript/wscriptman.cpp`: the handler-slot runners
  (`0x0030A060`, `0x0030A598`, `0x0030A688`).
- `src/scripter/ssxscriptengine.cpp`: the NIS engine: `0x00278358` (`cSSXScriptEngine_Load`, see the note under
  "NIS list players"), the list operations `0x00278E20`..`0x002790A0`, loading (`0x00278B98`, `0x0027B370`,
  `0x002797C8`), alternative choice `0x00279A70`, anchors `0x0027A0D8` / `0x0027B750` / `0x0027BB08`, the actor
  start `0x0027F9F8`, the control track `0x00280640`, the director `0x00281018` / `0x002816A0`, and the script
  choice `0x0027B0C0` (`cSSXScriptEngine_GetScriptFromCategory`) with its condition words `0x0027BDB8`. It also holds
  the cutscene entry points `0x0027AAF8` (event intro), `0x0027AC60` (podium and rival) and `0x0027A860`
  (transport).
- `src/scripter/datamanager.cpp`: the skip `0x00276F48` and the fade chaining `0x00277980`.
- `src/camera/script/scriptcontroller.cpp`: the three script camera algorithms (`0x001694B8`..`0x0016A510`).
- `src/main/gamestate.cpp`, `src/fe/festateloadscreen.cpp`, `src/main/loadscreens_prestart.cpp`: the world states
  that start cutscenes (listed under "Where cutscenes are started").

## Entities and modifiers

A stage program attaches an **entity** to a world instance, and optionally a **modifier** to the entity. Each game
tick the entity pass walks the entities newest first, before any rider is updated. For each one it runs the
modifier update (modifier vtable +0x14), then the entity update (entity vtable +0x194). The notes give
`0x00356198` both as the entity pass and as the entity update of spline carriers. A second pass, the section pass
`0x00101B60`, runs after every rider has been updated.

**Instance fields used here.** +0x8 runtime flags (`20h` static collision route, `40h` entity route, `100h`/`200h`
renderer bookkeeping), +0xC entity, +0x10 matrix, +0x60 and +0x6C bounds, +0x78 resource id.

**Entity fields.** +0xC vtable, +0x10 node type, +0x18 instance, +0x1C modifier container (container +0 = the
modifier).

| Entity class | vtable | node type |
|---|---|---|
| Object | `0x00490E80` | 17 |
| LiveComp (animation player) | `0x00490B10` | 1 |
| Flag (`Flag Verts`) | `0x0048FC10` | 10 |
| Emitter | `0x0048EE60` | 13 |
| (type-16 node) | `0x00491800` | 16 |
| DeadNode | `0x00491B00` | - |
| AnimTeeter | `0x004908F8` | - |

The modifier class names are strings in the ELF from about `0x0048E8D0`. Builtin numbers are decimal indices into
the builtin table `0x00441F38`. The Luno VM, its builtins and the handler slots are covered in luno-vm.md.

| Modifier | vtable | ctor | builtin |
|---|---|---|---|
| Spline | `0x0048F250` | `0x00359460` | 19 (`0x002FDED0`) |
| MultiSpline | `0x0048F168` | `0x00359F88` | 20 (`0x002FE0C0`) |
| AvaSpline | `0x0048F338` | - | 95 |
| Magnet | `0x0048F420` | - | 90 |
| Parent | `0x0048F508` | `0x00357038` | - |
| Position | `0x0048F5F0` | `0x00356F10` (creates and attaches) | - |
| Roller (crashbags) | `0x0048F080` | - | - |
| Rail | `0x004911D0` | `0x0035B708` | 48 (`0x002FF1C8`) |
| Halo | `0x00491220` | - | 97 (one list in the notes says 92; see "Halos") |
| Particle | `0x004912B0` | - | see "Particles" |
| DynamicParticle | `0x00491268` | - | see "Particles" |
| Boost | `0x00490898` | - | - |
| UVScroll | - | `0x0035F6E8` | 21 |
| TexFlip | - | `0x0035F0B8` | 22 |

Other set-piece builtins mentioned below: 3 LiveComp player (`0x002FBCB8`), 6 AnimTeeter, 7 one-way volume,
12 flag (`0x002FC9C8`), 13 MeshAnim, 16 emitter hand-over at a spline end, 31 (with argument 181, tied to the
raven's flap "AnimObject"), 37/38/39 collectibles, 43 event-kind test, 52 launched-once guard, 55 LiveComp time
gate (`0x003019C8`), 88 crowd, 105/106 MultiParticle, and the node-state builtins (1 Debounce; 2, 29, 58 for
DeadNode / Hide / RestoreNode).

### Handler rows and triggers

A location's stage chunk (Snow Jam: `bam.ssb` chunk 33, kind 16) has handler rows of six words. On Snow Jam the rows
start at +0x70. The Junction's stage is chunk 49 (100 rows, starting at +0x6C) and Metro-City's is chunk 56 (284
rows). An instance's row is its collision descriptor word +0x08 shifted right by 8. The slots used by set pieces
are listed below. Full slot semantics are in luno-vm.md.

| slot | runs when |
|---|---|
| 1 | the instance's course section is activated; builds its set pieces |
| 2 | a rider's selected contact is the instance: rider+0xA30 → `0x00121818` → `0x0030A060` |
| 4 | an attached entity finishes (spline end, once-mode LiveComp end, MeshAnim end) |
| 5 | every tick of a playing LiveComp |

Global handler 2 is program 3 on all three race courses studied. It runs at race GO and starts the start-gate
doors.

The contact store step `0x00105398` writes the selected instance to rider+0xA30. Trigger volumes are type-2 boxes
with node flags 2 and surface −1, which is the same path the speed boosts use. Slot-2 set-piece programs are guarded
by builtin 52 (launched once). A trigger's instance flags go `200022h` → `200322h` (Debounce) → `200104h`
(RestoreNode) → `200022h`. Computer riders take the same contact path, so they fire triggers too. In race captures,
AI riders often fired the rockets, spintwins, ravens, rock slide and trains before the human reached them **(PS2)**.
A set piece created by a slot-2 program is first updated on the next tick.

## Spline paths (world record kind 8)

Moving set pieces follow the same kind-8 spline records as the grind rails:

- `0x003451C0` binds a path.
- `0x003454E8` (`cSpline_calcLength__FP7cSpline`) computes its length L.
- `0x00345248` wraps a distance into range and keeps a segment cursor.
- `0x00345048` turns arc length into the segment parameter with the per-segment cubic at +0x50, using VU0 row
  products.

Distances are in cm. Speeds are given to the builtins in km/h and converted with `27.777779` (km/h → cm/s).

## SplineModifier and PositionModifier (builtin 19)

- **Construction.** Builtin 19 (`0x002FDED0`, key defaults at `0x004FB778`) → `0x00355AD0` allocates `F0h` bytes →
  ctor `0x00359460`. The ctor binds the path, converts the speed, and starts at distance 0, or at L for a negative
  speed. It always makes one random draw through `0x00317830` (`AIrandf__Fff`), even when the jitter is zero (see
  random-streams.md). The attach `0x003554B0` sets instance flags `&~20h | 40h` (entity route) and the radius.
- **Tick `0x00359698`.** `distance += speed / 60`. End mode 1 loops and 2 ping-pongs. Modes 0 and 4 stop at the end
  (0, or L − 0.1) and set the finished flag.
- **Matrix `0x00359830`**, evaluated lazily through `0x00361B90`. Yaw comes from the normalised first derivative and
  pitch from the raw derivative (`0x0031C228`). An Euler matrix (`0x0031BE50`) takes the path point as its
  translation, then the roll about Z is applied.
- **End of path.** The entity update `0x00356198` clears the finished flag and runs handler slot 4 (entity vtable
  +0x114 = `0x0034FD00`). In the Snow Jam pieces, the slot-4 program calls builtin 16. That turns the entity into a
  type-13 emitter (`0x003578A8` → `0x00355F10`), frees the spline and attaches a PositionModifier (`0x00356F10`)
  that holds the L − 0.1 matrix.

Snow Jam spline pieces:

| Piece | Start | Path | Mode, speed | Drawn |
|---|---|---|---|---|
| raven fly-by `ravensplineanima_1000` | slot 1 (section) | `5408h`, L 17,614 cm | loop, 45 km/h, roll −90° | yes |
| `brocket_1000/1001` | contact `triggerRockets_1100` | `A908h` / `AA08h` | stop, 150 km/h | no |
| `spintwin_1000/1001` | contact `spintwintrig_1000` | `A208h` / `A108h` | stop, 160 km/h | no |
| `chasingdragon_1000/1001` | contact `dragontrig_1000` | `A608h` / `A508h` | stop, 90 km/h | no |
| `chasingdragon_1100/1101` | contact `dragontrig_1100` | `A408h` / `A308h` | stop, 120 km/h | no |
| `EZrocketCore_1000/1001` | slot-5 timeline of `EZseqTimer` | `A708h` / `A808h` | stop, 150 km/h | `_1001` only |

The undrawn pieces are carriers for their DynamicParticle trails (smoke, sparks, dragon fire) and have collision type
0. The raven's section activation was seen at about 243,000 cm of course remaining in two captures **(PS2)**. The
frozen PositionModifier translations of the rockets and spintwins, and the raven's path state at later savestates,
match this description **(PS2)**.

## MultiSplineModifier and instance cloning (builtin 20)

The MultiSpline runs N copies ("cars") of one instance, evenly spaced along a closed path. Examples are the Snow Jam
chairlifts, the Metro-City bins and The Junction's traffic.

**Construction.** Builtin 20 (`0x002FE0C0`) → factory `0x00355B30` (`cMoveNode_addSpline`) → ctor `0x00359F88`. The
Snow Jam chairlift call is `MultiSpline(self, path, count 3, ±35 km/h, rotation 90°)`, on paths `608h` / `708h`
(`GondolaRail_0/1`). The ctor clones the authored instance N times (`0x0035A3F0`, `0x00351170`).
`0x0035A458` (`cMultiSplineModifier_setupNodes`) copies the authored `A0h` bytes into clone 0 and registers clones 1..
with `0x00351270` (`cInstanceMan_copyInstance__FPvP15sInstanceStructT0`), setting flags `&~40h | 20h`. Clone
resource ids come from a runtime pool (observed `3F80h`, `3E80h`, `3D80h`, then `3C80h`...). Modifiers loaded at
different times can reuse the same pool ids.

**Per tick.** This runs before the rider: this tick's distance is already in place when the rider update starts
**(PS2)**.

1. `0x0035A560` (modifier update): `distance += speed × dt`, where dt is field +0x14 of the clock at gp−0x848
   (`0x004A28A8`). The distance is wrapped by the length and the modifier is marked dirty.
2. The moving-node entity update `0x003568B0` → `0x00356078` → modifier+0x94 (`0x00361C20`) → `0x0035A5D8` →
   `0x0035AC20`.
3. `0x0035AC20` places car k at `distance + k·L/N` through `0x00345248`. It takes yaw and pitch from the derivative
   (`0x0031C228`, `0x0031BE50`) and writes the Euler matrix into the clone's +0x10. It then pre-multiplies by
   R(axis, angle), where the axis is the vector at `0x004FF160` (Z) and the angle is the rotation at modifier +0xC
   (VU0).
4. Bounds: `0x003568B0` computes car 0's record bounds (radius +0x18 via `0x00361C10`, `0x00361BF0`) and relocates
   it spatially (`0x003291E0`). Modifier+0xC4 (`0x0035A918`) updates the records and clone bounds of cars 1 to N−1.
5. Draw: modifier+0x5C (`0x0035B418`) runs a frustum test per car.

On Snow Jam this gives six chairs, three per cable, on 31,644 cm closed paths at 972.22 cm/s. The distance and all
six car matrices match the PS2 on every tick of an 8,199-tick race capture **(PS2)**. The MultiSpline has modes 0 to
3, which the notes do not describe. The Metro-City bins use mode 3.

**Collision.** The authored instance keeps the entity route (countdown flags `210345h`). Its entity bounds are car
0's record bounds and its hierarchy root is clone 0's matrix. The clones are static-route instances (`210325h` /
`212325h`) on their own +0x10 matrix. Clone 0 keeps the stale authored bounds, because `0x0035A918` relocates only
cars 1 onward. All of them carry the moving entity, so the rigid predicate `0x001057B8` (entity+0x74 = `0x00355420`
→ modifier+0x44 = `0x00360B60`) returns 1, and `0x00104E70` runs the selected-entity callback.

**Contact velocity.** On a selected contact, `0x0034E698` → `0x00356AE0` → `0x00353098` → modifier+0xB4
(`0x0035B200`). This writes the car's surface velocity at the contact point into packet +0x20 and its angular
velocity into +0x30. `0x0034E698` also has a per-node velocity table path (entity+0x4C via `0x0034E798` /
`0x0034E600`) that the notes do not describe further. No capture has a rider touching a chair, so the collision
routing is known from the code only.

## Flags and streamers (builtin 12)

- **Registration.** Section programs call builtin 12 (`0x002FC9C8` → `0x0034AC88`) for each flag instance (41 on
  Snow Jam). The flag entity ctor `0x0034ADD8` hides the instance's static draw and registers it with the 15-slot
  flag manager `0x0034C548`.
- **Shared grids.** Instances with the same model and parameters share one 8 × 5 grid. The grid is a sine-wave
  grid (`0x0034BCA0`), not a cloth simulation. It is built from the first registered instance by `0x0034B228`
  (`cFlagSet_CreateMesh`). The sine comes from `0x00392DF0` (a function in `src/render/font.cpp` per the lookup;
  the notes call it the sine table).
- **Per tick.** `0x0034C668` moves a random wind value toward a new random target once per second (±0.15 on Snow
  Jam), and `0x0034B818` advances each slot's phases. A grid is recomputed only on ticks whose parity matches its
  slot. In race snapshots, 11 of 20 live buffers held the current tick and 9 the previous one **(PS2)**.
- **Draw.** Each instance draws the shared grid with its own matrix (`0x0034B9B0`).
- **Amplitudes.** Flags use 70/0/30/30 and are fixed at the pole. Streamers use 80/0/10/0 and hang.
- **Wind mode** = the value at +0x54 of the course's row in table `0x0043D950`, plus 1 (`0x002D1BA0`). It is 1
  on Snow Jam, Metro-City and The Junction.
- **Randomness.** The wind targets and the random start phases draw from the presentation (visual) stream
  `0x004FF018`. Grid builds happen in the section pass, and the once-per-second wind draw happens later in the
  update (see random-streams.md).

## Texture scrolling (UVScroll, builtin 21; TexFlip, builtin 22)

The UVScroll ctor is `0x0035F6E8`. The modifier container tick `0x00352C70` calls its tick `0x0035F7D0`, and its draw
`0x0035FC20` adds (u, v) to every texture coordinate. Snow Jam has 324 scrolling instances:

- 245 chevron course fences (texture 9-30, −0.025 u per tick);
- speed boosts and blue pinlights;
- podium and stage backdrops;
- snow sheets and streams, rivers and waterfalls.

There are 9 distinct initial states. Metro-City has 200 scrolling instances and The Junction 30. A scroller starts
when its section loads, so distant sections can be out of phase with each other. Consecutive PS2 snapshot pairs
replay exactly under this model **(PS2)**. TexFlip (ctor `0x0035F0B8`) is not used on these three courses.

## LiveComp animation players (builtin 3)

The LiveComp entity (vtable `0x00490B10`) plays a model's keyframe animation. Builtin 3 (`0x002FBCB8`) calls the
ctor `0x00341AA0`, which takes these keys:

| key | meaning |
|---|---|
| 1 | mode: once / loop / ping-pong |
| 2 | reverse |
| 3, 4 | time range, in 1/30 s |
| 5 | rate |
| 6 | random rate spread |
| 7 | start time |
| 8 | random start, drawn from the gameplay stream `0x004FF030` |
| 9 | hide the static draw |

- **Tick `0x00341D48`.** Runs in the entity pass. It advances 1/60 s per game tick, then runs the owner's slot 5
  (`0x0034EBA0` → `0x0030A688`).
- **Time gate.** Inside slot-5 programs, builtin 55 (`0x003019C8`, through `0x0034EBE0`) is true on the tick when
  the player's time crosses (its key-1 argument)/30 s.
- **Once-mode end.** A finished once-mode player runs slot 4 (`0x0034FCC0` → `0x0030A598`). On that tick
  `0x00341D48` returns 0, so the LiveComp's attached effects skip that tick.
- **Node matrices.** `0x00361098` → `0x0034DC90` sample the cubic keyframe segments of each masked channel
  (translation, Euler angles in degrees) and compose the node hierarchy. The rail modifier uses the same channel and
  compose code.

Snow Jam examples (node matrices, the door timing and the raven chain match PS2 savestates tick by tick **(PS2)**):

| Piece | Start | Behaviour |
|---|---|---|
| start-gate doors | global handler 2 at race GO | built one tick after the race phase begins, before that tick's entity pass; 0 → 90° about local Z over 1/6 s (10 ticks); done the tick after |
| searchlights | slot 1 | 4 s loop, Y rotation 1 → 76 → 0° |
| blue pinlights | slot 1 | 2 s loop, random start |
| speed / trick boost pickups | slot 1 | spin loop |
| ravens taking off (`ravenanima_1000..1002`) | trigger contact | 5-node birds, 4.23 s; the slot-5 program starts the 2nd and 3rd bird 11 and 15 ticks later (time gates 5/30 s and 7/30 s) |
| rock slide (`rock_roll_fall_1000..1002`) | trigger contact | 1.4 s each; the others start at +13 and +21 ticks |
| snow crumbs (`snowcrumb_1000..1002`) | trigger contact → a 2 s timer | slot-5 program starts them at +3, +17 and +33 ticks |

Other LiveComp uses: Metro-City's trains (once, 2 s, on a trigger contact), dumpster lids and timers; The Junction's
small start doors and the blimp.

## Log teeters (AnimTeeter builtin 6 + RailModifier builtin 48)

Snow Jam has four logs, built by slot-1 programs.

- **Structure.** Each log has an AnimTeeter (builtin 6, ctor `0x003421A0`, vtable `0x004908F8`): a damped spring on
  the model's animation time 0..1. Node 1 rotates about local Y from 0 to 40.68° (`logbreakteeter`) or to 62.15°
  (`logteetera_3000`). RailModifiers (builtin 48 `0x002FF1C8` → ctor `0x0035B708`) bind the log's rails (for example
  `1108h`, `1D08h`, `6608h`) to node 1.
- **Update `0x00342358`** (entity pass, before the rider):
  `accel = −0.5·(time − rest) + 0.001·torque − 0.6·vel`, with the step clamped to ±1/15 per tick.
- **Torque** comes from entity vtable +0x15C (`0x00342538`): `dot(node Y, (hit − node origin) × F)`, applied only
  when |F| > 100. The rail attach `0x00106848` calls it with `F = v_before − v_after`. The rail snap `0x00106F78`
  also calls it; the notes mark that call "×60" without further detail.
- **Grinding alone applies no force.** A log moves only when a rider lands on its rail. In every race snapshot, the
  logs' torque, angle and speed were exactly 0 **(PS2)**.
- **Rail queries.** The spline rail query `0x00334680` answers modifier-bound rails through the modifier layer
  (`0x0035C698`, with the node transform), after the static layers, when the modifier's bounds overlap the 300 cm
  query box. The rails are bound on section activation.

A triggered falling billboard (`bcvolume_1001` → `fallingbb_1000`, program 144) was never fired in any capture.

## ParentModifier

The ParentModifier (vtable `0x0048F508`, ctor `0x00357038`, evaluate `0x00357108`) positions a child from a parent
node. The child matrix is the parent node's matrix with translation `t + R × offset`, where the offset is at +0x30.
It is used for The Junction's blimp ads and lights and for searchlight glows.

## Script-built effects and pickups

- **Particles** (builtins 16, 25, 26, 69; 16 makes bursts and 26 trails; Particle `0x004912B0`, DynamicParticle
  `0x00491268`). Sprites are drawn by the VU1 burst and trail paths `0x00380518` / `0x003807A0`, with the sprite size
  capped at 64 pixels. Particle births and emitter seeds draw from the presentation stream in the entity pass.
- **MultiParticle** (builtins 105/106; the roadflare flames). One static emitter per group is updated once per tick
  (`0x00357BF8`, after the entity passes) and drawn at every member's translation. At race start a scan registers
  the load's roadflares a second time. Each leave removes one entry, the first match (`0x003581F0`).
- **MeshAnim** (builtin 13; break-apart pieces). Construction is `0x00351B40`, with the pose taken from the source
  LiveComp node or the magnet. `0x00352230` makes the presentation-stream draws, and the update `0x00352500` handles
  life and end modes 0/1/2. It runs slot 4 at the end. The life value is updated with the EE's `sub.s`, whose
  operand handling (the notes call it an operand mask) affects the result at the 1-ulp level.
- **Node states.** Builtin 1 (Debounce) and builtins 2, 29 and 58 set DeadNode / Hide / RestoreNode. These flags
  reach both the collision world and the renderer.
- **Magnets** (builtin 90, the pickups). The entity-route box answers collision filter 1 only. The first human
  contact acquires the magnet. The slot-2 program runs once the pickup has reached the rider (`0x00357660`), and the
  Debounce freezes its matrix (`0x00355F10`). The award timing of The Junction's point pickups follows this
  sequence **(PS2)**.
- **Halos.** The angle advances by the spin and resets at ±360. The effect is FX 37 + key. The position comes from
  the magnet, the LiveComp node or the instance. Halos are depth tested at draw priority 8. The builtin number is 97 in
  the stage-world notes, while an earlier list in the same notes gives 92.
- **Collectibles** (builtins 37/38/39). The byte at `0x00535C11` is 0 in a career and 1 in a single event. A single
  event turns every listed collectible into a DeadNode. A career race keeps the uncollected ones without an entity
  until their section builds them (LiveComp + magnet + halo, with one gameplay-stream draw). Each collect is recorded
  in the career collect row.
- **Event-kind test** (builtin 43). Section-enter programs use it to remove objects that do not belong to the
  current event kind. For example, Snow Jam's finish reset planes kill themselves in a race.
- **One-way volumes** (builtin 7). The functions are `0x00341388`, `0x003415D0`, `0x00341818` and `0x001250A8`, with
  a rider list at rider+0x5B8 filled from `0x00104E70`.
- **Crowd** (builtin 88). The `crowd2d` / `crowdpod` materials are world texture 9-161 on all three courses. The
  crowd image cycles through the 16 frames `an00`..`an15` of `CRWD.SSH`, 3 ticks per frame. Camera flashes (FX
  `flsh`) come from 64 registered slots. The 2D crowd manager update is `0x00229530`, which makes 3
  presentation-stream draws each time a flash timer expires.
- **Avalanches.** An AvaSpline modifier class exists (vtable `0x0048F338`, builtin 95), but no Snow Jam program uses
  it. Snow Jam's "falling rocks" are the rock-slide LiveComps above.

## Order within the race update and the presentation stream (PS2)

Traced on the PS2, the race update `0x002306B8` consumes the presentation stream `0x004FF018` in this order:

1. The group-1 entity pass (DynamicParticle births, script emitter seeds).
2. The rider manager: each rider's contact programs (`0x00121818`), then the rider FX passes (grind chunks, snow
   emitters), then the section pass `0x00101B60` with the flag grid builds.
3. Group 2: the flag wind (once per second, `0x0034C668`) and the camera splash `0x002F39E0` (one draw).
4. Group 3: the ScreenTint lightning `0x00390C60`. It makes one draw per update while the game flow is in countdown
   or race, and until two updates after the finish update. Its lightning chance is 0 on these courses.
5. The 2D crowd `0x00229530`.
6. The cameras (shake).

Nothing draws at render time. For the per-consumer details, see random-streams.md.

## Per-course set pieces

| Course | Set pieces |
|---|---|
| Snow Jam (ARA1) | 2 chairlifts (MultiSpline, 3 chairs each), 41 flags/streamers (8 grid setups), 324 UVScroll, LiveComps (doors, searchlights, pinlights, boosts, ravens, rock slide, snow crumbs), 4 log teeters, spline pieces (raven fly-by, rockets, spintwins, dragons, EZ rockets) |
| Metro-City (BRA2) | 3 MultiSpline bin groups (3, 2 and 4 cars; the last with a LiveComp) on paths `mill_a` / `mill_end` / `mill_end_b` at 35 / −22 / 35 km/h, mode 3, no rotation; trains (LiveComp); dragons (Spline 180 km/h stop + DynamicParticle); 28 flags, 200 UVScroll, 104 LiveComps; teleport beams (builtin 34) |
| The Junction (BHP1) | traffic: 8 MultiSpline modifiers (1 to 6 cars) on `traffanim_1000` at 80 km/h, starting at 0 / 1200 / 2400 cm, resident from load; blimp (Spline loop 10 km/h + LiveComp, ads and lights on ParentModifiers); 12 flags, 30 UVScroll, 33 LiveComps |

Neither Metro-City nor The Junction uses AnimTeeter, Rail or TexFlip modifiers.

The Metro-City bins are created and later destroyed by section streaming as the rider moves along the course
**(PS2)**. The Junction traffic is resident from load, and its distances and car matrices follow the MultiSpline
model exactly in PS2 snapshots **(PS2)**.

These triggers were never fired in the Snow Jam captures: `bcvolume_1001` (falling billboard), 14 tree-top
triggers, `shortcut_03` and `EZrocketCore_1001` **(PS2)**.

## Cutscenes: files on the disc

`DATA/SCRIPTS/SCDAT.BIG` (a BIGF archive) holds the NIS data. There are 167 scripts, for example
`race\ra_sgb_var1` (start hut) and `podium\win_ps_zoeb` (a winner's podium).

| member | contents |
|---|---|
| `scmaster.dat` | `u32 count` (167), then per script `{u32 play count (0 on the disc), u32 name hash, u32 offset into scmasterdbg}`. Record i is script i. The name hash is the same function the animation banks use; all 167 entries match. |
| `scmasterdbg.dat` | the 167 script names |
| `NNNNNNNN.big` | one load group per script: `scrN.isb` (the script), optionally `anmN.afl` (its animation bank, the ANM.BIG AFL format) and `sndN.bnk` (its sound bank, BNKl v5). Streamed on demand by the loader `0x002797C8`, using the name format at `0x00481C68` (`%s%08d.big`). |
| `scdat_main.big` | the resident in-air loops (`heli_inair`, `gond_inair`) |
| `scdat_<LOC>.big` | scripts preloaded with a location (`0x00278B98` → `0x0027B370`), with one combined `anmscdat_<LOC>.afl` and `sndscdat_<LOC>.bnk`. A script present both in its own group and in a location group has different clip and sound indices in the two copies. |
| `scfilter<LOC>.dat` | the location's 28 category lists (see "Selection") |

Some script names use old code names: arielle = Allegra, deiter = Viggo, grommet = Griff, rocco = Nate.

**Movies.** `DATA/MOVIES/ABC1.MPC`, `DBC2.MPC` and `EBC3.MPC` (plus `WS` widescreen masters) are silent MPEG-2
videos, with the `pktrans` music stream playing over them. They are queued as movie ids 29 to 31 (29 = ABC1;
presumably 30 and 31 are DBC2 and EBC3, unconfirmed). The boot and intro videos (`EABIG`, `THX`, `INTRO(_DJ).MPC`)
are played from the front end: the boot at `0x001A1CE8`, and the title idle at a location inside `0x001948A8`.

## Script format (`.isb`, little endian)

**Header, 44 bytes (2Ch).** It starts with the version (1), the track count, the magic `05E68A2Ah` and the size.
The remaining fields:

| offset | field |
|---|---|
| +0x0C | loop flag |
| +0x10 | location mask |
| +0x14 | fade-in record |
| +0x1C | fade-out record |
| +0x24 | script number |

A fade record is `{s8 type (1 colour fade, 8 none), s8 colour (0 black, 1 white), s16 out, s16 hold, s16 in}`, with
the three times in ticks.

**Tracks.** Each track is `{u32 size, u32 n, u32 offset[n]}` followed by n alternative objects. One alternative per
track is used per playback (`0x00279A70`). Actor tracks keep only the alternatives whose character mask matches the
bound rider, then `rand() % n` picks one. Each track picks independently, so two playbacks of the same script can
differ (most scripts have 2 or 3 alternatives per camera track).

**Objects.** An object is `{u16 header size, u8 channel count, u8 kind, u32 duration in ticks, ext}`, followed by
channels `{u16 type, u16 size, payload}`.

| channel type | payload |
|---|---|
| 0 | piecewise cubic `{u16 t, f32 a, b, c, d}`; value `((a·u + b)·u + c)·u + d` with `u = t − key.t` |
| 1 | ranges `{slot, t0, t1, value, start offset, f32 speed, blend ticks, tail[4]}` |
| 2 | cut ranges |
| 3 | point events |

| kind | object | functions | channels |
|---|---|---|---|
| 0 | camera, Manual algorithm | `0x001694B8` / `0x00169570` | eye xyz, target xyz, roll, fov, shakes |
| 1 | camera, Target algorithm | `0x00169CF8` / `0x00169DB0` | target xyz, distance, pitch, yaw, roll, fov, shakes |
| 2 | camera, Subject algorithm | `0x0016A458` / `0x0016A510` | eye xyz, subject forward/up offset, roll, fov, shakes |
| 4 | cut list (director) | `0x00281018` / `0x002816A0` | the active camera per range, by the id at ext +0x21 of each camera |
| 5 | actor (a rider) | start `0x0027F9F8` / `0x001241C0`, clips `0x00124788`; handler at rider+0x6D0 | clip ranges, positional sounds, speech events, x y z, rot x y z |
| 7 | audio / control | `0x00280640` | stage-script calls, music codes (`0x0028E8C0`), PA/DJ cues (`0x002A19D8`), sounds, weather off |

Speech event ids: 2 `Finish_Line`, 100 `BC_Challenge`, 101 `Hey`.

The cut list also supports transitions other than hard cuts, and the fade record has types 2 to 7. According to
the notes, the shipped scripts use neither: their cuts are hard cuts (three of them are type-1 transitions of zero
length).

**Time.** A script advances one tick per game update at 60 Hz (`0x00274A30`), and the world tick equals the script
time **(PS2)**. A script lasts as long as its longest object.

## Anchors and locators

Every camera and actor position is given in an anchor frame (`0x0027A0D8`, table `0x00481D00`), plus the object's
own offset `e` from its ext block:

    p_world = Rz(yaw) · Ry(−pitch) · [ Rz(e.yaw) · Ry(−e.pitch) · Rx(−e.roll) · p + e.t ] + pos

Units are cm, with z up; angles are stored in degrees.

| anchor | frame |
|---|---|
| 0 | world origin |
| 1–18 | start-grid node of subject (anchor + 2), from `0x0027B750` (the AIP kind-0 row of that rider's slot); 1 = the human, 13–18 = race riders 0–5 |
| 19, 23, 26, 27, 28 | locators 7 (`NIS_Lodge`), 0, 2 (helipad), 3 (gondola station), 4 (`NIS_Transport`), snapped to the ground |
| 20 / 21 / 22 | podium steps 1st / 2nd / 3rd: locator 0 + (−20, 0, 340) / (−20, −275, 280) / (−20, 275, 280) |
| 24 | locator 8 (podium floor) |
| 25 | locator 1 (start gate), z − 1000, then snapped to the ground (`0x003369D8`, nearest \|Δz\| hit) |
| 29 / 30 | locator 5 (helicopter) / 6 (gondola); taken from the TRANSP set when the script loops |
| 37 | locator 15 (the second plane in ABC1) |
| 40–60 | a live actor |

Locators are world records of kind 18. Each location has one such record with 18 instance handles
(`track | rid << 8`). The lookup `0x0027BB08` takes the position from matrix row 3, `yaw = atan2(m01, m00)` and
`pitch = asin(m02)`. On Snow Jam, locator 1 (the start-gate model) and anchor 25 after the snap match live RAM
**(PS2)**. The in-air loops play in TRANSP, a terrain-less location that holds only the tilt-rotor and gondola cabin
models.

## Cameras, projection and letterbox

- **Manual:** eye and target both go through the anchor frame.
- **Target:** `eye = target − distance · (cos p · cos y, cos p · sin y, sin p)`, where yaw and pitch are the
  channel values plus the frame's.
- **Subject:** the eye goes through the frame and the target is on the subject rider.

The camera results for the start-hut and gate-idle scripts match live PS2 RAM **(PS2)**.

**Field of view.** The script's fov is a half-angle. The NIS view uses the 16:9 widescreen projection scales
(`272.65 / 318.09` in the widescreen table becomes `204.49 / 238.57` for 16:9, both multiplied by 0.75) in a
letterboxed 512 × 336 viewport. So `tan(vertical half-angle) = tan(fov)`, unlike the race camera, which applies a
× 3/4 factor **(PS2)**.

**Letterbox.** Steps other than the idle loop draw 60-line bars (out of 480) that slide in over the first 30 ticks
**(PS2)**. The idle loop under the objectives card has no bars.

## Actors

**Binding.** The binding value is subject + 1:

| binding | rider |
|---|---|
| 1–3 | the script participants D/E/F (podium places, the rival) |
| 4–5 | human players |
| 6–15 | computer riders |
| 16–21 | race riders 0–5 |

**Head and face.** A bound rider shows the NIS head, eyes and hands (model parts 5, 6, 8, 9) instead of the race
head and hands. The faces and hands are animated by the clip's part streams 5/6/8/9. Scripts have no morph channel.

**Clip time.** `(start offset + (t − t0) · speed) / 60` seconds. Clips play at 30 fps and loop at `(frames − 1)/30`.
The clip index is the AFL index in the load group's bank. Binding, clip index and clip time match live state for
the start-hut script **(PS2)**.

**Root.** The position comes from the actor's curves in the actor frame. The rotation is
`Euler(rotY + pitch, rotX + roll)`, followed by a rotation about Z by `rotZ + frame yaw − 90°`.

**Prop.** `lodge_arr3` shows a PDA model (`board_PDA_NIS`) rigidly attached to the right hand. Clip event id 0 makes
it visible, and the clip's part-11 stream drives its opening morph.

## NIS list players and skipping

There are two NIS list players (`NISLists`; manager pointer at gp−0x84C, `0x004A28A4`). Each is a 5-step FIFO of
`{list or script, flags, D, E, F}`, where D/E/F are the participants. Operations:

| function | operation |
|---|---|
| `0x00278E50` | add a step from a category list |
| `0x00278E20` | add a movie (ids 29–31) |
| `0x00278F38` / `0x00278F68` | start |
| `0x00279070` | advance |
| `0x002790A0` | clear |

The notes attach the `NISLists` label to `0x00278358`, but the decomp names that function `cSSXScriptEngine_Load`.
The notes do not settle whether it is the list-player code itself or a loader that sets up the players.

| step flag | meaning |
|---|---|
| 1 | skippable: `NISSkip` (Cross pressed, from `INPUT.MAP`); `0x00276F48` cuts to the next step with no fade |
| 2 | dropped when a skip happens |
| 4 | Start-pause allowed; never set, so Start does not pause during a cutscene (`0x00231AB8`) |
| 8 | held / looped until the game advances it (transport rides) |

While a step is skippable, a blinking "Press ✕ to skip" prompt is shown (`%s @skip %s`, built from `kT_OVRCMNPress`
and `kT_OVRCMNToSkip` by `0x001E9A30`). Held and looping steps (the in-air rides) show the world's "Loading..."
caption with a spinning snowflake **(PS2)**.

**Fades.** Steps chain their fades (`0x00277980`): a later step fades in with the previous step's fade-out record,
not with its own fade-in record. `lodge_arr3` fades from white.

**Audio.** Sound banks use sfx slot 17 plus the bank's group: 17 for the resident `scdat_main`, 18 for the
location's scdat, 19–26 for per-script groups. Every NIS sound plays on the CHARACTER bus at speaker 0's gain (a
location inside `0x002808E8`). Actor sounds are positional at the actor root.

## Selection (ScriptChoice)

`scfilter<LOC>.dat` is `u32 28`, then 28 × `{count, offset}`, then the entries `{u32 script, u16 mask[21], pad}`.

`0x0027B0C0` (`cSSXScriptEngine_GetScriptFromCategory`) picks a script from a list in three steps:

1. Keep the entries whose non-zero masks all intersect the condition words built by `0x0027BDB8`.
2. Of those, keep the least played (the play count in `scmaster.dat`).
3. Take `rand % n`.

A script listed three times (the `_fast` approaches) is three times as likely. The condition words are:

| word | rider |
|---|---|
| 0–2 | participants D/E/F |
| 3–4 | humans |
| 5–9 | computer riders |
| 10–14 | the second list |
| 15–20 | race riders 0–5 |

Each word is `1 << CHARDB index` of that rider's base character, so a cheat skin counts as its base rider.

| list | purpose |
|---|---|
| 0 / 1 | new career: plane (midway ABC1) / per-character jump |
| 2 | venue fly-over (per location) |
| 3 | approach (random choice) |
| 4 | start hut (race courses; e.g. `ra_sgb_var1`, `var2`) |
| 5 | start-gate idle loop |
| 6 / 7 / 8 | podium: generic / 2nd place / 3rd place |
| 9 | winner, per character with three variants (`win_ps_<char>{a,b,c}`) |
| 10 | winner in a cheat skin (skins 10–20 or 28) |
| 11 | transport arrives (event end / station) |
| 12 / 13 / 14 / 15 | helicopter: depart / in-air / in-air per character / in-air multiplayer |
| 16 / 17 | backcountry heli arrival / per-character jump |
| 18 / 19 / 20 / 21 | gondola: depart / in-air / in-air per character / in-air multiplayer |
| 22 / 23 | lodge walk-in / (empty) |
| 24 / 25 | rival challenge: location shot / the rival's scene (race `ra_bc_<char>` or freestyle `ss_bc_<char>`) |

Per-character content covers the 10 base riders: three podium wins each, a rival scene, the in-air loops and the
heli jumps. Cheat skins use their base rider's scripts, except on the podium (list 10). Unused on the disc: the
`bc_chal` and `gond_inair_down` scripts, list 23, the idle lists, and stage builtin 36.

## Where cutscenes are started

"WSn" is world state n (the game-flow states; see game-flow.md). Step lists are written
`[list (flags)] → ...`.

| Cutscene | Started from | Steps | Notes |
|---|---|---|---|
| Event intro, Single Event / online | WS10 enter `0x00234F40` → `0x0027AAF8`, list table `0x00481E68` | [4 (3)] → [5 (0)] | actors: the 6 race riders at their grid nodes, clip i per slot |
| Event intro, Conquer the Mountain | same, table `0x00481E48` | [2 (0)] → [3 (3)] → [5 (0)] | fly-over: music code 21–25, PA cue `Fh` (`PA_Venue_Intro`); approach: PA cue 2 (`PA_Rider_Race_Intro`; 1 for freestyle); the fly-over is not skippable |
| Objectives card over the idle loop | WS2 `0x00236BB0`; its exit `0x00236CD8` stops the NIS | list 5 | Cross = Continue |
| Podium (Conquer the Mountain final round, one human, placed 1st–3rd) | WS5 update `0x00233CD8` → `0x0027AC60` (table `0x00481E90`) → WS12 (winner's character tune, `0x0028CDF8`) → WS7 | winner list 9 or 10, 2nd list 7, 3rd list 8, fallback list 6 | D/E/F = places 1–3 |
| Rival challenge (once per peak and discipline; not for cheat skins 10–20) | queued after the podium by `0x0027AC60` (`0x001464D0` unlocked, `0x00146150` not yet shown, `0x00146320` marks it shown) | [24 (1)] → [25 (3)] | speech 101 `Hey` at t 200; the rival D is the race's first computer rider (list +0x48), not the peak's named rival **(PS2)** |
| Transport ride | results / MCOMM / booth → WS14 arg 1 → `0x0027A860` | heli [12 (1)] → [13 (0)] → [14 (8)]; gondola [18 (1)] → [19 (0)] → [20 (8)] | heli when either end is a backcountry, otherwise gondola; the departure step plays only from stations; music code 20 (course change); the per-character loop is held until the destination is loaded |
| Transport arrival | booth (stage builtin 68 action 3) → WS14 arg 2 `0x00236250` | [11 (3)] | generic |
| Lodge / station walk-in | door volume `mdl_<hub>_NIS_Lodge_0` → builtin 68 action 4 → WS14 arg 0 `0x00236208` | [22 (3)] → prompt `1Fh` | the PDA prop |
| New career drop | WS10 `0x00234F40` / `0x00235080`, first visit to course 14 | movie 29 → [0] → [1], flags 3 | `pktrans` Peak 1 music; `DJ_BC_Intro`; Cross ends the chain |
| Backcountry heli drop | same, courses 15/16 (Peak 2/3 first visits add the DBC2/EBC3 movie) | [16] → [17] | per character |
| Next round (gondola ride-up) | WS13 `0x00235AA0` | gondola in-air 19/20, then 4 + 5 or 5 alone | music code 20 with argument 1 |

The next-round ride-up was observed on the PS2 releasing the held gondola loop after 340 ticks in a semi-final or
final, before the idle loop under the heat card **(PS2)**.

These are not NIS:

- the event load screen (`cGameLoadState`, `0x00232E20`);
- the countdown and gate: WS3 `0x00234AD0` (`cGFGateState_gainFocus`) and `0x00234C68` (`cGFGateState_update`),
  with sounds `0x0029C420` / `0x0029C7B0`;
- the finish shot and results (WS5 `0x00233C50`, WS7 `0x00236DA0`);
- the rival run's rolling start (`0x002872A8`);
- character-select previews (`0x001A0358`);
- the lodge load screens (`cFELoadStateInLodge` / `cGameLoadStateOutLodge`);
- medal and unlock overlays.

The game has no ending cutscene or movie. It shows only per-character messages (`kT_MSGEN<Char>1..3`) and a popup.

The podium building belongs to a streamed course section (texture chunk 27). After a real finish, that section is
already resident.
