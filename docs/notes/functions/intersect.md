<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/intersect/

## `src/intersect/aifwddiff.cpp`

Segment `0x00327890`-`0x00329910`.

- **`0x00327C00`** - Coarse collision grid builder that runs the VU0 grid program. *[static]*
- **`0x00327CC8`** - Scratch collider setup per processed node; does not copy `+0x90` (scale), so the scratch collider scale accumulates 1/instance-scale per node. *[static]*
- **`0x00327F18`** - Body vs sphere-tree contact (with `0x0032CDB0`): ancestor overlap rejection, ascending child visitation, the first successful bone sphere wins. Omits the active-sphere mask. *[static]*
- **`0x00328030`** - Step of the sphere-tree vs type-1 triangle mesh chain `0x0032C0F8` -> `0x00330828` -> `0x00328030` -> `0x0032CA78`. *[static]*
- **`0x00328360`** - Padded region classifier: classifies a spatial region cell against query bounds (three return codes). The scale is built from exponent bits; low/high cell edges are padded by 0.20000000298 (ELF constant). Final tests are asymmetric: the Y condition is repeated and there is no final minimum-Z test. *[static]*
- **`0x003284B8`** - Removes a location's instances from the activation octree at eviction; a later read brings them back without entities, at their authored flags. *[static]*
- **`0x00328C20`** - Inserts a location's instances into the activation octree when its read completes (resolver kind 3); runs while the row is still in state 6/8. *[static]*
- **`0x003291E0`** - Relocates an instance in the spatial tree after its bounds change. *[static]*
- **`0x00329590`** - Body vs box contact (with `0x0032B2B8`): tests box face projections and rejects overlaps confined to edges/corners. The loop repeatedly tests the broad sphere while reading enabled-mask bits and never advances to child sphere coordinates. *[static]*

## `src/intersect/riderspheretree.cpp`

Segment `0x00329910`-`0x003303F0`.

- **`0x00329B40`** - Body translation helper used with `0x00106538` in rider pair separation (the push); role beyond translation not detailed. *[static]*
- **`0x00329F98`** - Rider pair body overlap: rejects disjoint broad spheres and returns the first overlapping child-sphere pair in authored order. Ignores the active mask bits. *[static]*
- **`0x0032A1C0`** - Body vs triangle contact: broad-sphere reject, then enabled body spheres by plane projection and vertex/edge overlap. Chooses the sphere with the smallest signed center-to-plane distance (not the largest penetration); the returned point is the center's plane projection even when an edge test admitted the overlap. *[static]*
- **`0x0032B2B8`** - Body vs box contact helper paired with `0x00329590` (face projection tests). *[static]*
- **`0x0032B6A8`** - Point-in-triangle test (reached from `0x0032D440` in the sphere-tree kernel). *[static]*
- **`0x0032B6E0`** - Terrain segment intersection with a coarse cell scan on the 9x9 patch grid: checks the cached cell first if the patch matches, else scans U outer, V inner, triangles (d,b,c) then (c,b,a), plane via `0x0032E4D0` plus a VU0 inclusion test; the first hit seeds refinement and the cache updates per visited candidate. For kind-2 queries it then calls the query `+0x44` refinement callback, which replaces point/normal/UV but keeps the coarse fraction. Coarse roller mode: 3x3 cells, stride 3, callback `0x00330788`. *[static]*
  - `0x0032BE28`: Region (to `0x0032BE70`) that calls the query refinement callback `0x0032E9A0` for kind-2 queries. *[static]*
- **`0x0032C0F8`** - Head of the sphere-tree vs type-1 triangle mesh chain `0x0032C0F8` -> `0x00330828` -> `0x00328030` -> `0x0032CA78`. Type-2/type-3 surface nodes throw on this path (none exist). *[static]*
- **`0x0032C508`** - Sphere-tree collider kind/initializer used for RollerModifier `+0xE0` (constructor vs type routine unconfirmed). *[unconfirmed]*
- **`0x0032C648`** - Updates the RollerModifier sphere-tree collider from the body transform. *[static]*
- **`0x0032CA78`** - Sphere-tree vs triangle kernel with recursive child visitation and the `0x0032DF28` mask cache. Child order by `0x0032DB40` (corner directions, shell sort `0x0032DA40`), recursion `0x0032D470`, point-in-triangle `0x0032D440` -> `0x0032B6A8`. End of the type-1 mesh chain from `0x0032C0F8`. *[static]*
- **`0x0032CDB0`** - Sphere-tree contact helper paired with the body vs sphere-tree contact `0x00327F18`. *[static]*
- **`0x0032D440`** - Point-in-triangle wrapper for sphere-tree contacts; calls `0x0032B6A8`. *[static]*
- **`0x0032D470`** - Recursion step of the sphere-tree vs triangle kernel `0x0032CA78`. *[static]*
- **`0x0032DA40`** - Shell sort used by `0x0032DB40` for sphere-tree child ordering. *[static]*
- **`0x0032DB40`** - Orders sphere-tree children by corner directions (uses the shell sort `0x0032DA40`); used by the kernel `0x0032CA78`. *[static]*
- **`0x0032DF28`** - Sphere-tree occupancy mask cache: ten shallow and two deep round-robin entries (depth threshold 5). The key omits the model-node index, so later nodes of the same resource reuse the first node's masks even if their authored masks differ. Shared by rider and roller queries; resolved on every `0x0032CA78` call. *[static]*
- **`0x0032E100`** - World collision swept-segment query construction (kind and preferred fraction arguments). Camera clearance uses kind 2 with preferred fraction 0.5; the air trajectory predictor uses kind 1 with preferred fraction 1 (its f12 argument is this fraction, not a collision radius). Kind 2 triggers the query `+0x44` refinement callback `0x0032E9A0` after the coarse intersection; kind 1 uses the coarse 9x9 grid without Newton refinement. *[static]*
- **`0x0032E288`** - Ray/instance query node bounds test. *[static]*
- **`0x0032E398`** - Ray/instance query node transform. *[static]*
- **`0x0032E4D0`** - Ray vs triangle plane intersection using the authored normal (with `0x0032E5E8`; VU0 barycentric microcode); used by the coarse terrain cell scan `0x0032B6E0`. *[static]*
- **`0x0032E5E8`** - Authored-normal ray/triangle intersection, companion of `0x0032E4D0`. *[static]*
- **`0x0032E688`** - Type-3 (static sphere-tree) ray callback: a literal zero return, so ray queries never report sphere-tree contacts and air prediction rays never hit sphere-tree geometry. The world ray query skips static sphere trees before the unsupported checks; the crash-bag object/particle override callbacks do not replace it. *[static]*
- **`0x0032E690`** - Ray/box entry and exit contacts. *[static]*
- **`0x0032E9A0`** - Terrain query refinement callback (query `+0x44`): bicubic patch refinement with exactly four Newton updates, refining point, normal and UV after the coarse intersection. Returns early if U/V leaves [0,1] (callers keep the coarse point/normal). Refined normal = cross(dv,du); the coarse fraction stays the ranking parameter. *[static]*
- **`0x0032F650`** - Body collision query constructor: builds a query object from a collision body pointer and mode; feeds `0x00334458` or `0x003342D0`. Obstacle callers enable a normal-direction filter with the ground normal: terrain triangles whose normal dot it exceeds 0.8000000119 are excluded (instance/box paths differ). Mode 1 (`0x00105398`, pickups) sets query `+0` = 0, so `0x0032F8C0` returns -1, and query `+8` = 0, so there is no directional triangle exclusion. *[static]*
- **`0x0032F8C0`** - Query radius getter: returns -1 when query `+0` is 0, otherwise twice the broad radius. Supplies the distance metric for the `0x00104E70` contact ranking. *[static]*

## `src/intersect/worldsphtree.cpp`

Segment `0x003303F0`-`0x00342D10`.

- **`0x003303F0`** `cWorldSphTree_cWorldSphTree` - Builds a coarse, unfiltered query from a sphere-tree collider: query `+0` = 0, bounds = collider centre +/- level-0 radius. Called as `0x003303F0(collider, 1)` by `0x0035EDC8`. *[static]*
- **`0x00330540`** - World-query handler for type-1 mesh surface nodes. *[static]*
- **`0x003306D8`** - Contact packet comparison used by `0x00336850`: depth closest to -1 first, then tie rules. *[static]*
- **`0x00330788`** - Sphere-tree vs terrain triangle callback for coarse queries (the coarse roller mode of `0x0032B6E0`); calls `0x0032CA78`. *[static]*
- **`0x00330828`** - Step of the sphere-tree vs type-1 mesh chain `0x0032C0F8` -> `0x00330828` -> `0x00328030` -> `0x0032CA78`. *[static]*
- **`0x003309D8`** - Collision-instance list collector / inline-box instance test used during the spatial traversal of `0x00332DB8`: instance flag 0x20, box `+0x60`/`+0x6C`. *[PS2]*
- **`0x00332DB8`** - World spatial query / scope list builder: initialises the output lists and walks up to 8 roots of the scope's region manager (20-byte records: signed exponent, three signed cell coords, root pointer; empty roots skipped), visiting partially covered octree cells in Gray order. Keeps terrain patches (node `+0x24` lists, box patch `+0x158`/`+0x164`) and inline-box instances (`0x003309D8`) overlapping the query bounds inclusively (c.le.s); flag-0x40 entities use their virtual `+0x168` box. Uses `0x00328360`, `0x0033B748`, `0x00340DC0`. Refreshed every third game tick from the rider query bounds; also backs light candidate traversal. Called from `0x00120E50` and in `0x0011D660`. *[PS2]*
- **`0x00333EF8`** - Instance body collector for rider body queries; skips type-16 nodes, DeadNodes and flags-2 instances. *[static]*
  - `0x003340F4`: Flag routing (to `0x003341A0`): flag 0x20 static first (then the authored bounds check), else 0x40 requires an entity whose vtable `+0x160`/`+0x168` predicates decide, else skip. *[static]*
- **`0x003342D0`** - Generic rider terrain/body world query with standard candidate selection; walks only the rider query scope lists collected by `0x00332DB8`. Used as `0x0032F650` -> `0x003342D0` for rider body queries, by the landing probe, and by `0x00138960` with cache rider `+0x864`. Lacks the cruise normal-alignment preference. Computer riders near their route skip it. *[PS2]*
- **`0x00334458`** - Instance body collector: walks a query instance list, routes each instance as static (flag 0x20) or entity (0x40), checks bounds and calls `0x00334888`. t0 = 0 selects node filter 1, otherwise filter 2; filter-1 queries scan instances only (no terrain). The entity path uses entity vtable `+0x164`/`+0x16C` collidable/bounds predicates (`0x003569D0`/`0x00356A00`). *[static]*
- **`0x00334680`** - Rail spline world query (world, point, out, mask, radius): nearest rail point over nearby layers in box = point +/- radius. Iterates layers world `+0x214`[0..world `+0x210`): layer `+8` type 2 -> `0x0035C698` (modifier-bound rails, with layer `+0x0C`, when the modifier bounds overlap the box), type 3 -> `0x00348290`, type 1 with desc `+0x1C` & mask -> `0x00335128`; the result replaces the accumulator only when strictly closer. Riders call it from hips/rail contact `0x00106F78` as (rider `+0x860` nearby cache, hips, out, mask 1 = grind rails, 300). out `+0x10` = unit rail tangent, out `+0x20` = zero (`0x004FF120`), out `+0x50` = 0. *[PS2]*
- **`0x00334888`** - Per-instance node collision dispatcher: tests a query against the instance model-node collision by descriptor type (0 none, 1 separate triangle mesh, 2 model-node box, 3 sphere tree) and node surface filter. For entity instances an attached entity's override (vtable `+0x134`) is checked before ordinary node filtering; base matrix via vtable `+0xD4`/`+0xCC`. Output packet: `+0x20` surface velocity, `+0x40` depth, `+0x48` node collider, `+0x4C` surface, `+0x50` instance. Snow Jam has 1136/1497/404/15 nodes of types 0..3. *[static]*
  - `0x00334D00`: Node surface filter (to `0x00334D6C`): filter 2 skips every surface -1 node, filter 1 keeps only surface -1 nodes, filter 0 keeps all. There is no flag-bit0 exception under filter 2. *[static]*
- **`0x00335128`** - Per-segment rail closest-point search: coarse 5-sample chord scan, then golden-section refinement of the cubic. Rejects when the box misses segment bounds `+0x6C`..`+0x80`; samples t = 0, .25 .. 1, picks the best index, brackets from tables `0x0048E560`/`0x0048E578`, golden section c1 = 0.381966, c2 = 0.618034, tol 0.0005, <= 24 iterations. Returns the last evaluated point, t, distance and tangent = M*(3t^2,2t,1,0) normalized. Called by the rail query `0x00334680`. *[static]*
  - `0x0033592C`: Uses the rail descriptor pointer stored at segment `+0x68` (record header) during the spline search. *[static]*
  - `0x00335940`: Second use of the segment `+0x68` rail descriptor pointer during the spline search. *[static]*
- **`0x00335960`** - Terrain patch query: tests patches with flags 0x41 and strict bounds; copies the patch surface (`+0x8`) into result `+0x4C`. Only patch flags (`+0xA`) are tested; streaming chunk state is ignored. *[static]*
- **`0x00335B90`** - Instance collector for mode-0 rays and whole-world queries; always uses node surface filter 2, so every surface -1 node (all crashbags, most scenery) is skipped. *[static]*
  - `0x00335BB0`: Flag routing block: static flag 0x20 first, else entity flag 0x40 (skipped when the entity pointer is null), else skip. *[static]*
- **`0x00335D78`** - Octree walk (together with `0x0033CCF8` and `0x00340FA0`) that visits children in order 0,1,3,2,6,7,5,4. Tests only patch flags (`+0xA`), not streaming chunks. *[static]*
- **`0x00336850`** - Whole-world sphere-tree query: gathers terrain and instance hit packets and keeps the one whose depth is closest to -1 (compare via `0x003306D8`; ties prefer instance over terrain, then lower instance `+0x78`, then lower patch `+0x150`). Terrain comes via `0x00335960`/`0x0032B6E0`, instances via `0x00335B90` (filter 2). Used by the crashbag rigid body (RollerModifier; no 64-packet cap on that path), air trajectory kind-1 rays and status-0 prediction queries, camera clearance, and the reset placement probe. *[PS2]*
- **`0x003369D8`** - Ground snap: picks the collision hit with the smallest |dz|. *[PS2]*
- **`0x00336D40`** - Instance collector for mode-2 (scenery-only) air trajectory rays. Unlike the mode-0 collector `0x00335B90`, its flag routing does not check the entity pointer before reading its vtable. *[static]*
  - `0x00336D64`: Flag routing block: static flag 0x20 first, else entity flag 0x40 dispatch with no null check on the entity pointer. *[static]*
- **`0x003378C0`** - Mode-2 air trajectory ray query (trajectory prediction status 2): instance/scenery collision only, omits terrain. *[static]*
- **`0x0033B748`** - Recursive spatial-tree (octree) traversal helper used by `0x00332DB8`, paired with `0x00340DC0` (roles of the two not split): node lists are visited before children; partially covered nodes visit children in Gray order 0,1,3,2,6,7,5,4, fully contained subtrees 0..7; child boxes use half scale/padding with strict comparisons; partial recursion stops at exponent 11. Contains recursive calls. *[static]*
- **`0x0033CCF8`** - Octree walk helper, part of the walk with `0x00335D78` and `0x00340FA0`. *[static]*
- **`0x00340DC0`** - Recursive spatial-tree (octree) traversal helper used by `0x00332DB8`, paired with `0x0033B748` (roles of the two not split): node lists are visited before children; partially covered nodes visit children in Gray order 0,1,3,2,6,7,5,4, fully contained subtrees 0..7; child boxes use half scale/padding with strict comparisons; partial recursion stops at exponent 11. Contains recursive calls. *[static]*
- **`0x00340FA0`** - Octree walk helper, part of the walk with `0x00335D78` and `0x0033CCF8`. *[static]*
- **`0x003411B8`** - Tests the rail descriptor flag word (`desc+0x1C & mask`), like the query walker `0x00334680`; its role is otherwise not described. *[static]*
- **`0x00341388`** - One of the one-way volume (stage-script builtin 7) functions; which slot (constructor/update/test) is not stated. *[PS2]*
- **`0x00341548`** - Constructor for SSB record kind 8: rail (grind) spline records, named in the PHM/PSM splines array (e.g. spline_ARA1_EventRail_0). Header is 48 bytes plus 144 bytes per cubic segment; the loader patches segment link words, sets segment type 1, replaces segment `+0x68` rail index with a header pointer and patches header `+0x28` surface. Header `+0x1C` bit 0 must be set at runtime (inferred). *[static]*
- **`0x003415D0`** - One of the one-way volume (stage-script builtin 7) functions; which slot (constructor/update/test) is not stated. *[PS2]*
- **`0x00341818`** - One of the one-way volume (stage-script builtin 7) functions; which slot (constructor/update/test) is not stated. *[PS2]*
- **`0x00341AA0`** - LiveComp animation player constructor (stage-script builtin 3). Argument keys: 1 mode once/loop/ping-pong, 2 reverse, 3/4 time range in 1/30 s, 5 rate, 6 random rate spread, 7 start time, 8 random start drawn from the gameplay RNG `0x004FF030` (a world-pass draw), 9 hide static draw. *[PS2]*
- **`0x00341D48`** - LiveComp animation player tick: advances 1/60 s per game tick and runs owner handler slot 5 (`0x0034EBA0` -> `0x0030A688`); when a once-mode player finishes it runs slot 4 (`0x0034FCC0` -> `0x0030A598`) and returns 0. A LiveComp's effects skip the tick on which its once-mode player finishes. *[PS2]*
- **`0x003421A0`** - AnimTeeter constructor (vtable `0x004908F8`): damped spring driving the model animation time 0..1 (used for log teeters). *[static]*
- **`0x00342358`** - AnimTeeter update (entity pass), e.g. log teeters: accel = -0.5*(time-rest) + 0.001*torque - 0.6*vel, with the step clamped to +-1/15 per tick. Logs move only when a rider lands on their rail; torque, angle and speed read 0 in every sampled state. *[static]*
- **`0x00342538`** - AnimTeeter torque input (entity vtable `+0x15C`): torque = dot(node Y, (hit - node origin) x F), applied only when |F| > 100. Called by the rail attach `0x00106848` (F = v_before - v_after) and the rail snap `0x00106F78` (with a x60 factor). *[static]*
- **`0x00342C08`** - Debounce (stage-script builtin 1) constructor: stores ticks = int(duration x clockRate) at `+0x2C`, using the clock read via gp+0x2A74 (`0x004A5B64`; clock object `0x004C9428`, rate 60 at clock `+0x10`); mode 0 clears the instance flag's low four bits; restore state is kept at `+0x30`. *[static]*
