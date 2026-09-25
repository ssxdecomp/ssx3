<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/object/

## `src/object/debouncenode.cpp`

Segment `0x00342D10`-`0x003454E8`.

- **`0x00342D88`** - Debounce (stage-script builtin 1) update: decrements a positive count at `+0x2C`; on 1 -> 0 requests completion (reason 1) and returns 0, otherwise returns 1. Zero/negative counts stay unchanged. The completion call is cited as vtable `+0x110` or `+0x114` in different notes (8-byte vtable entries). *[static]*
- **`0x00342E98`** - Debounce (builtin 1) completion (slot `+0x114`): checks `0x0034FCC0`, then for state 3 removes the component (old one destroyed with mode 3) and constructs a type-19 node via `0x00350F60` (allocation 0x1C bytes, flags 0x20000000, group 1). *[static]*
- **`0x00343C60`** - Reachable from global scripts via `0x00303B38`; a potential visual-RNG consumer, though it makes no draws in the race (role unconfirmed). *[unconfirmed]*
- **`0x003440C8`** - CrowdMan3d update; called from the race game update at `0x00230D00`. *[static]*
- **`0x00345048`** - Spline arc length to parameter: evaluates the segment's `+0x50` cubic with VU0 row products. *[static]*
- **`0x003451C0`** - Binds a spline path (kind-8 spline/grind-rail record) to a modifier. *[static]*
- **`0x00345248`** - Spline path distance wrap and segment cursor lookup (handles negative and over-length distances and arbitrary starting cursors). *[PS2]*

## `src/object/spline3d.cpp`

Segment `0x003454E8`-`0x00345700`.

- **`0x003454E8`** `cSpline_calcLength__FP7cSpline` - Computes a spline path's length. *[static]*

## `src/object/effectlink.cpp`

Segment `0x00345700`-`0x003466A0`.

- **`0x00345B40`** - Particle effect update (no visual-RNG draw). *[PS2]*
- **`0x00345F90`** - DynamicParticle effect update; calls the emitter update `0x003710D0`. *[PS2]*

## `src/object/flexbridgenode.cpp`

Segment `0x003466A0`-`0x00348B90`.

- **`0x00348290`** - Rail query for layer type 3 (sphere-tree/instance rails; object-owned cubic rail arrays of dynamic rail types 2/3) using 64-byte cubic coefficient matrices: checks object `+0x24` flags and loops (object `+0x20` - 1) segments sampling the matrices at object `+0x50`. The result holds the object `+0x18` instance, segment index and the virtual `+0x188`/`+0x18C` binding getter, which supplies the surface. *[static]*

## `src/object/flexrailnode.cpp`

Segment `0x00348B90`-`0x0034B228`.

- **`0x00349DB0`** - Constructor for SSB record kind 21: course spine. *[static]*
- **`0x0034AC88`** - Flag entity creation, called by stage-script builtin 12. *[static]*
- **`0x0034ADD8`** - Flag entity constructor: hides the static draw and registers with the 15-slot flag manager (`0x0034C548`). *[static]*
- **`0x0034AF18`** - Empty draw callback of type-10 cloth flag entities; those flags are drawn by the flag manager near the rider. *[static]*
- **`0x0034B038`** - Flag manager step between registration `0x0034C548` and grid build `0x0034B228`. *[static]*
- **`0x0034B168`** - Flag manager slot allocation helper, used in the registration chain `0x0034C548` -> `0x0034B038` -> `0x0034B228`. *[static]*

## `src/object/flagset.cpp`

Segment `0x0034B228`-`0x0034E448`.

- **`0x0034B228`** `cFlagSet_CreateMesh` - Builds a shared flag grid from the first registered instance, making 4 visual/presentation RNG draws (random start phases) per new flag slot. *[PS2]*
  - `0x0034B288`: Return address of the flag-grid phase RNG draws. *[PS2]*
- **`0x0034B818`** - Advances each flag slot's phases per tick; a grid is recomputed only on ticks whose parity matches its slot. *[PS2]*
- **`0x0034B9B0`** - Flag draw: each instance draws the shared grid with its own matrix. *[static]*
- **`0x0034BCA0`** - Computes a shared 8 x 5 sine-wave flag grid (not a cloth simulation); instances with the same model and parameters share one grid. Flags use amplitudes 70/0/30/30 fixed at the pole; streamers 80/0/10/0 hanging. *[PS2]*
- **`0x0034C548`** - Flag manager registration (15-slot flag manager): called when a flag entity is built; allocates cloth slots (with `0x0034B168`) and runs `0x0034B038` -> `0x0034B228` (grid build, 4 RNG draws per new slot). *[PS2]*
- **`0x0034C668`** - Flag manager wind update (entity group 2): moves a random wind value toward a new target once per second, with 1 visual/presentation RNG draw per timer wrap. Wind target range +-0.15 on Snow Jam; wind mode = course table `0x0043D950` row `+0x54` plus 1. *[PS2]*
  - `0x0034C71C`: Return address of the flag wind RNG draw. *[PS2]*
- **`0x0034DC90`** - LiveComp node-matrix helper (keyframe channel sampling / hierarchy compose). *[PS2]*

## `src/object/animnode.cpp`

Segment `0x0034E448`-`0x0034EEB8`.

- **`0x0034E600`** - LiveComp contact helper using the per-node velocity table entity `+0x4C`; used with `0x0034E798` by the selected-contact handler `0x0034E698`. *[static]*
- **`0x0034E698`** - Type-1 component slot 0x154 target (called with a this-adjustment): LiveComp selected-contact handler that adjusts the contact surface motion/angular contribution: -> `0x00356AE0` -> `0x00353098` -> modifier `+0xB4` (contact velocity), using the per-node velocity table entity `+0x4C` via `0x0034E798`/`0x0034E600`. Not the reward callback. *[static]*
- **`0x0034E798`** - LiveComp contact helper using the per-node velocity table entity `+0x4C`; used with `0x0034E600` by the selected-contact handler `0x0034E698`. *[static]*
- **`0x0034EBA0`** - Runs a LiveComp owner's handler slot 5 (-> `0x0030A688`) each LiveComp tick. *[static]*
- **`0x0034EBE0`** - LiveComp timer test used by stage-script builtin 55: true when the player time crossed key1/30 s this tick. *[static]*
- **`0x0034ED88`** - Constructor for SSB record kind 14: AIP (AI path) resource. ARA1's AIP (kind 14, track 8, resource 0) holds 129 AI paths and eight track/course-progress paths. *[static]*

## `src/object/floatingnode.cpp`

Segment `0x0034EEB8`-`0x0034FB90`.

- **`0x0034FB00`** - Node/entity base construction attaching to an instance (sets instance `+0xC`); args (kind, instance), e.g. kind 19 from `0x00350F60`. *[static]*

## `src/object/instancenode.cpp`

Segment `0x0034FB90`-`0x00350750`.

- **`0x0034FBF0`** - Node base destruction: detaches via `0x0034FC80`, restores the low instance flags from the authored high half (mask 0xFFFF0300, then OR of the arithmetic-shifted high half, e.g. 0x00210004 -> 0x00210023), sets bit 1, then calls `0x00354920`. *[static]*
  - `0x0034FC1C`: Authored-flag restore block: rebuilds the runtime low flags from the authored high half. *[static]*
- **`0x0034FC80`** - Detaches a component from its instance (called by `0x0034FBF0`). *[static]*
- **`0x0034FCC0`** - Runs entity handler slot 4 (-> `0x0030A598`), delegating to `0x002D19E8` for an authored slot-4 override; used as the Debounce completion guard and when a once-mode LiveComp player finishes. *[static]*
- **`0x0034FD00`** - Entity handler slot 4 dispatch (entity vtable `+0x114`), run at a Spline path end. *[static]*
- **`0x0034FE00`** - Forwarding step from entity contact `0x00355770` to `0x002D19B8`. *[static]*
- **`0x0034FED8`** - Transform helper called by `0x0035C5A0` with object `+0x40`/`+0x34` (instance/binding transform). *[static]*
- **`0x00350288`** - Type-19 node slot 0x10C: walks model nodes and rebuilds transformed matrices from the source hierarchy. *[static]*
- **`0x00350570`** `cInstanceNode_getBoundBoxInfo` - Sets entity bounds from the authored AABB and the `+0x24` radius (sqrt.s of the largest corner distance); end of the modifier attach chain `0x003554B0` -> `0x00356780` -> here. *[static]*

## `src/object/deadfadenode.cpp`

Segment `0x00350750`-`0x00351030`.

- **`0x00350F08`** - Constructor for SSB record kind 16: collision bindings. *[static]*
- **`0x00350F60`** - Type-19 (RestoreNode-tagged) node constructor: base `0x0034FB00`(19, instance), vtable `0x00491680`; clears instance bits 5/6 and bit 1 and sets bit 2. Does not restore prior low flags or re-enable collection. *[static]*

## `src/object/instanceman.cpp`

Segment `0x00351270`-`0x00352AA8`.

- **`0x00351270`** `cInstanceMan_copyInstance__FPvP15sInstanceStructT0` - Registers a cloned world instance. *[static]*
- **`0x00351B40`** - MeshAnim construction (stage-script builtin 13 break pieces): pose taken from the source LiveComp node or the magnet. *[PS2]*
- **`0x00352230`** - MeshAnim (builtin 13) visual setup: 9 visual-RNG draws per node, N x 4 in a first loop then N x 5 in a second. Construction is `0x00351B40`, update `0x00352500`. *[PS2]*
  - `0x003522B8`: First of the 4 per-node draw return addresses in the first loop (also `0x003522E0`, `0x00352300`, `0x0035231C`). *[PS2]*
  - `0x003523C0`: Start of the 5 per-node draw return addresses in the second loop (through `0x00352444`). *[PS2]*
- **`0x00352500`** - MeshAnim update: life countdown (EE sub.s rounding), end modes 0/1/2, and handler slot 4. *[PS2]*

## `src/object/modifierblock.cpp`

Segment `0x00352AA8`-`0x00353F00`.

- **`0x00352B88`** - Entity-to-attached-modifier forwarding (entity `+0x1C` -> container -> modifier) for collidable/bounds queries. *[static]*
- **`0x00352C70`** - Modifier container update: ticks the attached modifiers (e.g. UVScroll `0x0035F7D0`). *[static]*
- **`0x00352D20`** - Per-entity effect list update: runs Particle `0x00345B40`, DynamicParticle `0x00345F90` and TexFlip `0x0035F410` effects. *[static]*
- **`0x00353098`** - Entity contact forwarding step from `0x00356AE0` to the attached modifier's `+0xB4` contact-velocity slot. *[static]*
- **`0x00353228`** - Counterpart of `0x00353278`, called by stage-script builtin 69 with argument 0. *[static]*
- **`0x00353278`** - Walks attached component entries (from head `+0x10`), queries each type via vtable `+0x14` and requests state 3 via vtable `+0xC` for type-3 entries. Called by stage-script builtin 69 with argument 1. *[static]*
- **`0x00353B10`** - Sky box draw: draws the camera-attached sky dome instance (mdl_?SKY_SkyTop1, about 3 m across) centred on the camera before the world. Copies the identity matrix at `0x004FF1A0`, replaces its translation row with the camera position (`0x002D1C20`), pushes a modified render state and draws the sky instance with draw flag 0x5420. Related debug toggle Disable Sky Box at `0x004A452C` (gp+0x143C). *[static]*

## `src/object/spring.cpp`

Segment `0x00353F00`-`0x00354688`.

- **`0x00354648`** - Component base construction: registers the node with the manager at gp+0x2898 (`0x004A5988`) through `0x00354C08`. *[static]*

## `src/object/objnode.cpp`

Segment `0x00354688`-`0x003549E0`.

- **`0x00354920`** - Base component destruction. *[static]*

## `src/object/bucketman.cpp`

Segment `0x003549E0`-`0x003552D8`.

- **`0x00354C08`** `cBucketMan_add` - Inserts a component node into a manager group, on the pending or active list by group flags bit 0; new nodes come first in traversal order. *[static]*
- **`0x00354C98`** - Drains/merges pending group entries using ordering/equality virtuals and may destroy replaced entries; run as the entity/effect flush after the crowd and MultiParticle managers in the game update. *[static]*
- **`0x00354EA8`** `cBucketMan_first__FP10cBucketMani` - Returns the head node for the group traversal `0x00354F98`. *[static]*
- **`0x00354EF8`** `cBucketMan_next__FP10cBucketManPvi` - Returns the next node for the group traversal `0x00354F98`. *[static]*
- **`0x00354F98`** - Entity/component group update pass (manager, group index): updates every entity of one group, saving the next node before calling node vtable `+0x14`, so nodes registered during the traversal are not updated in it. Head via `0x00354EA8`, next via `0x00354EF8`. Called with manager gp+0x2898 (`0x004A5988`): group 1 at `0x00230C64` (newest entity first), group 2 at `0x00230CCC`, group 3 at `0x00230CE8`, and from the alternate update at `0x00244F94`. *[static]*
- **`0x00355028`** - Entity group slot `+0x1C` pass (secondary phase, probably the group render pass) run on group 1 in the frame update; makes no visual-RNG draws. *[static]*

## `src/object/movenode.cpp`

Segment `0x003552D8`-`0x00358020`.

- **`0x00355420`** - Object entity rigid predicate (vtable `+0x74`), used by `0x001057B8`: forwards to the modifier's vtable `+0x44`. For the RollerModifier that is `0x00361CA8`, which returns 0 so the mass path runs (node value 1e30 makes the impulse about -1/(2c)); `0x00360B60` is also cited as the slot target. *[static]*
- **`0x003554B0`** - Modifier attach (e.g. RollerModifier; chain -> `0x00356780` -> `0x00350570`): sets instance flags &~0x20|0x40 (entity route) and the radius; entity bounds = authored AABB, entity `+0x24` = largest corner distance. *[static]*
- **`0x00355770`** - Object entity contact handler (vtable `+0x144` of `0x00490E80` and `0x00490B10`; also AnimTeeter vtable `0x004908F8` slot `+0x144`): optional component predicate via attached component methods `+0x54`/`+0x4C` with rider identity from `0x002D1B30`; rejects if the predicate rejects or node `+0x20` > 0, else sets node `+0x20` = int(clockRate/2) (30 ticks) and forwards `0x0034FE00` -> `0x002D19B8` -> `0x0030A060` to run the authored slot-2 script. For crashbags it ends in RollerModifier vtable `+0x54`. The 30-tick gate starts after the instance's section enters. *[static]*
- **`0x00355858`** - Entity end callback (vtable `+0x14C`), called from `0x0030A060`: sets entity `+0x20` to 30 ticks (for crashbags it only gates a never-taken script re-run). *[static]*
- **`0x00355AD0`** - Allocates a 0xF0-byte SplineModifier and calls its constructor `0x00359460`. *[static]*
- **`0x00355B30`** `cMoveNode_addSpline` - MultiSplineModifier factory; calls the constructor `0x00359F88`. *[static]*
- **`0x00355DB8`** - Allocates a 0x2D0-byte RollerModifier (constructor `0x0035DA70`, attach `0x003554B0`) and constructs it from the rider contact packet (rider `+0x9E0`) and record (rider `+0xA60`). *[PS2]*
- **`0x00355F10`** - Replaces an instance's entity: effects move to the new one and a magnet's matrix is frozen. Used by the spline-to-emitter handover and by Debounce (builtin 1). *[static]*
- **`0x00356078`** - Object entity vtable `+0xC4`: returns the primary modifier's (container slot `+0`) vtable `+0x94` evaluated matrix, else instance `+0x10`; called from the LiveComp entity update `0x003568B0`. *[static]*
- **`0x00356128`** - Object entity base-matrix getter (vtable `+0xCC`), used by `0x00334888`: forwards to the modifier's vtable `+0x9C`; for the RollerModifier (`0x00361D38`) modifier `+0x240` replaces instance `+0x10` as the hierarchy root. *[static]*
- **`0x00356198`** - World entity (owner) update wrapper, run in the entity pass newest entity first: decrements a positive node `+0x20` cooldown (zero/negative left alone), then runs the component predicate and component update (virtual 0x78, e.g. `0x00342D88`). On a finished path it clears finished and runs handler slot 4 (entity vtable `+0x114`, `0x0034FD00`), used for the Spline set-piece end after which builtin 16 turns the entity into an emitter. *[PS2]*
- **`0x00356298`** - Dynamic entity instance draw (vtable slot 0x20) for Object, type-1 and type-13 entities; draws only with instance flag 0x4 (tested at `0x0035636C` before render submission). Type-16/DeadNode draws are empty. *[PS2]*
  - `0x0035636C`: Tests instance flag bit 2 (0x4) before render submission. *[static]*
- **`0x00356780`** `cMoveNode_setupOverlapSystem` - Attach chain step between the modifier attach `0x003554B0` and the bounds setup `0x00350570`. *[static]*
- **`0x003568B0`** - Object/LiveComp entity update after the modifier: evaluates the modifier (-> `0x00356078` -> modifier `+0x94`), sets bounds = modifier `+0x240` translation +/- entity `+0x24` (car-0 record bounds radius `+0x18` via `0x00361C10`/`0x00361BF0`; modifier `+0xC4` `0x0035A918` handles cars 1..), then relocates the instance in the spatial tree via `0x003291E0`. A crashbag created during rider physics of tick T is first updated in tick T+1. *[PS2]*
- **`0x003569D0`** - Object entity collidable predicate (vtable `+0x164`, cited as `+0x160` where 8-byte entries are counted differently) for `0x00334458`: forwards via `0x00352B88` to the RollerModifier (vtable `+0x64`, `0x00361D18`). *[static]*
- **`0x00356A00`** - Object entity bounds query (vtable `+0x16C`) for `0x00334458`: forwards via `0x00352B88`; the RollerModifier returns bounds `+0x220`/`+0x230`. *[static]*
- **`0x00356A28`** - Object entity node-collision override predicate (vtable `+0x134`), used by `0x00334888`: delegates to the attached modifier (RollerModifier vtable `+0xA4`, `0x00360BC8`, returns 0 so the ordinary node path is used). *[static]*
- **`0x00356AE0`** - Object entity selected-contact callback (vtable `+0x154`), called by `0x00104E70` and from the LiveComp contact `0x0034E698`: forwards via `0x00353098` to the modifier's vtable `+0xB4` (RollerModifier `0x00360BD8`, a no-op). *[static]*
- **`0x00356DB0`** - Object entity (node) construction, vtable `0x00490E80`; invoked by entity script builtin 0. Not a DeadNode. *[static]*
- **`0x00356E60`** - Constructor for SSB record kind 17: course-progress objects. *[static]*
- **`0x00356F10`** - Attaches a PositionModifier holding a fixed matrix (the L - 0.1 spline end pose). *[PS2]*
- **`0x00357038`** - ParentModifier constructor. *[static]*
- **`0x00357108`** - ParentModifier evaluate: child matrix = parent node matrix with translation + R x offset (`+0x30`). *[static]*
- **`0x00357660`** - Magnet pickup reached-rider step: runs the slot-2 program once the pickup reaches the rider. *[PS2]*
- **`0x003578A8`** - Turns an entity into a type-13 emitter (stage-script builtin 16 at a spline end); calls the entity replace `0x00355F10`. *[static]*
- **`0x00357950`** - Type-13 (emitter) entity update, run in the group-1 entity pass. *[static]*
- **`0x00357BF8`** - MultiParticleMan update: updates one static emitter per group once per tick after the entity passes; uses the VU random generator, not `0x004FF018`. *[PS2]*

## `src/object/multiparticle.cpp`

Segment `0x00358020`-`0x003595D8`.

- **`0x003581F0`** - MultiParticle member removal: removes the first matching entry. *[PS2]*
- **`0x00359460`** - SplineModifier constructor: binds the path (`0x003451C0`), speed = km/h * 27.777779, starts at 0 (or L for negative speed), and makes one gameplay-RNG draw (`0x00317830`) even with zero jitter. *[PS2]*

## `src/object/splinemodifier.cpp`

Segment `0x003595D8`-`0x0035C0E8`.

- **`0x00359698`** - SplineModifier tick: distance += speed/60; end mode 1 loops, 2 ping-pongs, 0/4 stop (at 0 / L - 0.1) and set finished. *[PS2]*
- **`0x00359830`** - SplineModifier matrix builder (evaluated lazily via `0x00361B90`): yaw from the normalised first derivative, pitch from the raw derivative, Euler matrix, then roll about Z. *[PS2]*
- **`0x00359F88`** - MultiSplineModifier constructor: clones the authored instance once per extra car via `0x0035A3F0`/`0x00351170`; `0x0035A458` copies the authored 0xA0 instance bytes into clone 0 and registers clones 1.. with `0x00351270` (flags &~0x40|0x20). *[PS2]*
- **`0x0035A3F0`** - MultiSpline instance-clone step (with `0x00351170`) used by the constructor `0x00359F88`. *[static]*
- **`0x0035A458`** `cMultiSplineModifier_setupNodes` - Copies the authored 0xA0-byte instance into clone 0 and registers clones 1.. (`0x00351270`), setting static-route flags (&~0x40|0x20). *[static]*
- **`0x0035A560`** - MultiSplineModifier update: distance += speed * clock dt (G `+0x14`), wraps by path length, marks dirty. *[PS2]*
- **`0x0035A5D8`** - MultiSpline evaluate step; calls the car matrix builder `0x0035AC20`. *[static]*
- **`0x0035A918`** - MultiSpline modifier `+0xC4` slot: updates records and clone bounds of cars 1.. (clone 0 keeps stale authored bounds). *[PS2]*
- **`0x0035AC20`** - MultiSpline car matrices: car k at distance + k*L/count (wrap/cursor via `0x00345248`), yaw/pitch from the path derivative (`0x0031C228`, `0x0031BE50`), Euler matrix into clone `+0x10`, then a rotation by angle `+0xC` about the axis at `0x004FF160` (z), applied as R x M via VU0. *[PS2]*
- **`0x0035B200`** - MultiSpline contact velocity (modifier `+0xB4`): car surface velocity at the contact point into packet `+0x20`, angular velocity into `+0x30`. *[PS2]*
- **`0x0035B418`** - MultiSpline draw path (modifier `+0x5C`): frustum test per car. *[static]*
- **`0x0035B708`** - RailModifier constructor (vtable `0x004911D0`). *[static]*

## `src/object/railmodifier.cpp`

Segment `0x0035C0E8`-`0x00367150`.

- **`0x0035C5A0`** - Composes the instance/binding transform for an object-bound rail (dynamic rail types 2/3) with object `+0x50`, calling `0x0034FED8` with object `+0x40`/`+0x34`; used by the layer-type-2 rail query `0x0035C698`. *[static]*
- **`0x0035C698`** - Rail query for layer type 2 (object/instance rails; the RailModifier answer): resolves the object `+0x30` packed rail descriptor via `0x002D1BD8`, checks descriptor `+0x1C` against the mask, composes the instance/binding transform with `0x0035C5A0`, transforms the object's linked cubic segments and searches them, returning instance and binding. Called from `0x00334680` with layer `+0x0C`. *[static]*
- **`0x0035CFF0`** - Solves angular momentum from a target angular velocity for the RollerModifier. *[static]*
- **`0x0035D288`** - Computes RollerModifier velocities (`+0xB0`/`+0xC0`) from momenta. *[static]*
- **`0x0035D340`** - RollerModifier rigid-body integration step. *[static]*
- **`0x0035D4A0`** - RollerModifier contact impulse response, paired with `0x0035D908` (which of the two does what is not established): restitution applies only above 277.78 cm/s; friction uses a 0.001 slip threshold. *[static]*
- **`0x0035D908`** - RollerModifier contact impulse response, paired with `0x0035D4A0` (which of the two does what is not established): restitution applies only above 277.78 cm/s; friction uses a 0.001 slip threshold. *[static]*
- **`0x0035DA70`** - RollerModifier constructor (entity script builtin 15, used for crashbags; vtable `0x0048F080`): builds a rigid body from the instance, then applies an initial kick from the rider contact (`0x0035DDE8`); supplies the entity bounds/matrix. Flags: clears 0x20 and 0x2, sets 0x40, 0x4, 0x1 (0x40214023 -> 0x40214345). Quaternion from the instance matrix (`0x0031B748`/`0x0031B7A8`), centre of mass rotated in, `0x0035E770` transform, `0x0035E248` world inverse inertia, `0x0035D288` velocities; restitution 0.1, friction 0.4, bounce threshold 277.78 cm/s. *[PS2]*
- **`0x0035DDE8`** - RollerModifier kick, used at construction and on rider re-contact: velocity = rider direction x closing/2 + (0,0,min(5000/mass + 100, 600)); angular velocity = normal x 10, with angular momentum solved by `0x0035CFF0`. *[PS2]*
- **`0x0035E248`** - Computes the RollerModifier world inverse inertia (`+0x80`). *[static]*
- **`0x0035E770`** - RollerModifier transform update; probably builds the world transform from the rigid-body state (inferred). *[unconfirmed]*
- **`0x0035E850`** - RollerModifier (crashbag) per-tick update, run every game tick before the rider providers: timer `+0x20` += 1/60. Below 10 s: energy blend, gravity -980*mass, contact-time damping, integrate (`0x0035D340`), collider (`0x0032C648`), world contact (`0x0035EDC8`); a contact after 5 s sets the timer to 10. Energy < 10000 or timer >= 10 zeroes momenta and sets timer 11; frozen 11..16 s; from 16 s it sinks 10 cm per tick. *[PS2]*
- **`0x0035EDC8`** - RollerModifier world contact: calls `0x00336850`(`0x002D1BE0`(), `0x003303F0`(collider,1), &packet, modifier `+0x2C0`), pushes out by (depth - leaf radius/2 + 2) along the normal, applies angular damping 0.975, then the impulse responses `0x0035D4A0`/`0x0035D908` (restitution only above 277.78 cm/s, friction slip threshold 0.001). *[PS2]*
- **`0x0035F410`** - TexFlip effect update (not used on the sampled courses). *[static]*
- **`0x0035F6E8`** - UVScrollModifier constructor (stage-script builtin 21). *[PS2]*
- **`0x0035F7D0`** - UVScrollModifier tick, called from the modifier container update `0x00352C70`; starts when the instance's section loads. Chevron course fences scroll -0.025 u per tick. *[PS2]*
- **`0x0035FC20`** - UVScroll draw: adds (u, v) to every texture coordinate. *[static]*
- **`0x00360790`** - Empty draw callback (jr/nop) at slot 0x20 of the DeadNode, type-19 and type-16 node vtables. *[static]*
- **`0x00360800`** - Default component ordering virtual: compares node `+0x14` IDs. *[static]*
- **`0x00360840`** - Default component equality virtual: compares node `+0x14` IDs. *[static]*
- **`0x003608E8`** - Base node update (slot 0x10) delegating to `0x00360910`; runs as a group-1 world entity update. *[static]*
- **`0x00360910`** - Common node update delegate; returns 1 (ignored by the group traversal `0x00354F98`). *[static]*
- **`0x00360990`** - Entity base-matrix predicate (vtable `+0xD4`): returns 0. *[static]*
- **`0x003609F0`** - Empty contact callback (jr/nop) at slot 0x140 of the DeadNode, type-19 node and one-way volume entity (vtable `0x004914E0`) vtables. *[static]*
- **`0x00360AE0`** - No-op completion (slot 0x114) of the type-19 node. *[static]*
- **`0x00360B60`** - Modifier rigid predicate (modifier vtable `+0x44`); returns 1 for MultiSpline cars. *[static]*
- **`0x00360BC8`** - RollerModifier node-collision override (vtable `0x0048F080` slot `+0xA4`): returns 0, so the ordinary node path is used. *[static]*
- **`0x00360BD0`** - Modifier query at vtable `0x0048F080` slot `+0xAC` (the RollerModifier vtable): returns 0. *[static]*
- **`0x00360BD8`** - RollerModifier selected-contact callback (vtable `+0xB4`): no-op. *[static]*
- **`0x00361098`** - LiveComp node matrices: samples cubic keyframe segments per masked channel and composes the hierarchy (-> `0x0034DC90`). *[PS2]*
- **`0x003614F8`** - Empty (jr/nop) slot 0x140 contact callback of the Debounce component. *[static]*
- **`0x00361B90`** - Lazy matrix evaluation wrapper that calls the Spline matrix builder `0x00359830`. *[static]*
- **`0x00361BF0`** - Bounds helper used by the LiveComp entity update `0x003568B0` for car-0 record bounds. *[static]*
- **`0x00361C10`** - Bounds-radius helper (reads radius `+0x18`) used by the LiveComp entity update `0x003568B0` for car-0 bounds. *[static]*
- **`0x00361C20`** - Modifier evaluate reached as modifier `+0x94` (vtable slot, inferred); on the MultiSpline path -> `0x0035A5D8` -> `0x0035AC20`. *[static]*
- **`0x00361CA8`** - RollerModifier rigid predicate (vtable `+0x44`): returns 0. *[static]*
- **`0x00361CD8`** - RollerModifier rider re-contact (vtable `+0x54`): sets timer `+0x20` = 0 and applies a new kick `0x0035DDE8` with rider `+0xA60`/`+0x9E0`. *[PS2]*
- **`0x00361CF8`** - RollerModifier script re-run gate (vtable `+0x4C`): returns 0. *[static]*
- **`0x00361D18`** - RollerModifier bounds (vtable `+0x64`): returns modifier `+0x220`/`+0x230`. *[static]*
- **`0x00361D38`** - RollerModifier base matrix (vtable `+0x9C`): returns modifier `+0x240`. *[static]*
- **`0x00362478`** - Blend-mode setter: dispatches on a blend enum through the table at `0x00491FB0` to emit a GS ALPHA_1 value. Called from the deferred GS state builder at `0x00363F30`..`0x00363F68` (inside `0x00363C20`), which extracts the enum from material word4 bits 2..6. *[PS2]*
  - `0x003624D0`: Blend enum 1 case: emits GS ALPHA 0x2A (source colour passthrough). *[PS2]*
  - `0x003624DC`: Blend enum 5 case: emits GS ALPHA_1=0x44 (A=Cs, B=Cd, C=As, D=Cd), i.e. ((Cs-Cd)*As>>7)+Cd, standard source-alpha blending; the `li v0,0x44` is at `0x003624E4`. *[PS2]*
- **`0x003626D8`** - Decodes material state test bits into GS TEST (ATE/ATST and ZTST). ZTST mode comes from material word1 bits 23..24: 0 GREATER, 1 GEQUAL, 2 ALWAYS; terrain uses ATE with ATST ALWAYS. *[static]*
- **`0x00363490`** - Draws the sorted render list in layers with full-screen passes between them, splitting at priorities 6 and 9 (table `0x004A4058`): layer 0 (world; board track is priority 3), fog composite `0x0036AC00`, layer 1 (priorities 6..8), glare `0x0036C790`, ScreenTint `0x003904A0`, then HUD. *[static]*
- **`0x00363C20`** - Converts render material state words into GS registers (ALPHA_1/ALPHA_2, CLAMP_2, TEST). *[static]*
  - `0x00363F30`: Deferred GS state builder block (to `0x00363F68`): extracts the blend enum from material word4 bits 2..6 and calls the blend setter `0x00362478`. *[static]*
- **`0x00364CD0`** - Uploads VU1 GIF templates; mode 2 builds PRIM 0x5C (context 1) and 0x25C (CTXT=1, context 2) with constant vertex RGBA 0x80, used for the two-context terrain base+light draw. *[static]*
  - `0x00365968`: Packet-template branch (to `0x00365990`) emitting a DMA CALL to VU1 program 2 at `0x00434990`. *[static]*
