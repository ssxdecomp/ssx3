# Collision, pickups and instance events

SSX 3 tests each rider's posed collision body (a broad sphere plus bone-attached spheres) against the world:
terrain patches, and authored instances whose collision is a triangle mesh, model-node boxes or a sphere tree.
Contacts are answered by several phases (the obstacle push/bounce for terrain and surfaced geometry, an
instance-contact phase for solid scenery and trigger volumes, a hips-vs-rail check, and a rider-vs-rider phase),
which all report into one collision reaction routine that picks a soft or crash reaction. When a contact selects
a scripted instance, its stage-script handler runs: this is how boost pickups are awarded, how crashbags become
rigid bodies, and how instances are swapped into DeadNode/RestoreNode states, with runtime instance flags
deciding which instances each collector and the renderer see.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

Decomp translation units (per the current splits) holding the main functions:

- `src/intersect/riderspheretree.cpp`: rider body query setup `0x0032F650`, body-vs-triangle `0x0032A1C0`,
  body-vs-box `0x0032B2B8`, sphere-tree contact `0x0032CDB0`, sphere-mask cache `0x0032DF28`, body ray
  `0x0032E688`, rider pair overlap `0x00329F98`, body translation `0x00329B40`.
- `src/intersect/aifwddiff.cpp`: box face test `0x00329590`, sphere-tree walk `0x00327F18`, mesh helper
  `0x00328030`, spatial relocation `0x003291E0`, coarse terrain grid `0x00327C00`.
- `src/intersect/worldsphtree.cpp`: instance collectors `0x00333EF8`, `0x00334458`, per-instance dispatch
  `0x00334888`, terrain/body query `0x003342D0`, ray collectors `0x00335B90`/`0x00336D40`, whole-world query
  `0x00336850`, rail query `0x00334680`, octree walks.
- `src/ai/control/handplantcontrol.cpp`: ground contact phase `0x0013F178` and obstacle phase `0x0013F488`, air
  phase `0x00139C88`/`0x0013AA48`, rail leave `0x0013BFA8`, landing probe `0x0013A7B0`.
- `asm/1218.s` (not yet split): instance contact `0x00104E70`/`0x00105398`/`0x001057B8`, collision reaction
  `0x00105D98`, soft collision `0x00108388`, body translation `0x00106538`, heading response `0x001065B0`,
  hips/rail contact `0x00106F78`, rider pair `0x00107888`/`0x00107E70`, rail attach test `0x00108A48`.
- `src/ai/rider.cpp`: scripted-contact dispatch `0x00121818`, collision timers `0x001210B0`, collision weight
  `0x0011FF98` (`cRider_getMass`), query scope refresh `0x00120E50`.
- `src/ai/computer.cpp`: crash entry `0x0010EB30`, powerup dispatch `0x0010F1C0`, pair record table
  `0x0010F3B8`/`0x0010F560`.
- `src/ai/motion/wipeoutmotion.cpp`: crash-motion contact calls `0x00137860`/`0x00138640`.
- `src/object/movenode.cpp` (Object entity), `src/object/instancenode.cpp`, `src/object/debouncenode.cpp`,
  `src/object/deadfadenode.cpp` (type-19 node constructor), `src/object/bucketman.cpp` (component scheduler),
  `src/object/modifierblock.cpp`, and `src/object/railmodifier.cpp`, where the current split places the
  RollerModifier functions and the shared empty node callbacks. The Debounce constructor `0x00342C08` currently
  falls in `src/intersect/worldsphtree.cpp`.
- `asm/1FBE38.s` (not yet split): stage-script builtins (`0x002FC0D0`, `0x002FC7D0`, `0x002FD250`,
  `0x002FF850`, `0x00301D78`, `0x00302490`) and the instance state fallback `0x002FC2C0`.
- `src/wscript/wscriptman.cpp`: per-instance handler dispatch `0x0030A060`; `src/luno/lunovm.cpp`: the LUN
  interpreter; `src/sound/soundsys.cpp` and `src/sound/bankmonitor.cpp`: pickup feedback.

## Conventions

Rider motion modes and control states as these routines test them:

| Value | Motion mode | Control state |
| --- | --- | --- |
| 0 | ground | ordinary ground control (`0x00131620`) |
| 1 | air | - |
| 2 | crash; submode word owner+0x30: 0 ground/sliding, 1 air | - |
| 3 | frozen (reset) | soft-collision reaction (`0x0012E778`) |
| 4 | rail | - |
| 8 | - | crash (`0x0012CB68`) |
| 9 | - | reset (`0x0012F398`); most contact phases skip in this state |
| 10 | - | ignored by the pair impulse `0x00107E70` |
| 13 | - | transient state on the way into a crash or the air "land on top" path |

Vtable entries appear to be 8 bytes: a signed this-adjustment word followed by the function pointer (the
rider interface entry at +0x18/+0x1C is read that way). Offsets below are given either as the entry
(e.g. contact entry +0x140) or as its function-pointer word (+0x144); the pairs quoted for the same entry
(+0x160/+0x164, +0x110/+0x114) fit this layout.

Speed constants are in cm/s. Several are round km/h values (27.78 = 1 km/h, 55.56 = 2, 277.78 = 10,
555.56 = 20, 833.33 = 30, 1388.89 = 50), which may be how the source wrote them (unconfirmed).

Hex numbers given as flag words (such as `0x40214023` or `0x00210023`), masks and event IDs are values, not
addresses.

## Per-tick order around collision

Within one game tick:

1. World entities update first: each RollerModifier runs `0x0035E850` and its entity `0x003568B0`, before any
   rider's pose provider and controllers. A bag created during rider physics in tick T first updates in tick
   T+1. **(PS2)**
2. `0x001210B0` (collision timers and reset request) runs after the controller dispatch and before the motion.
3. Ground motion, `0x0013F178`: store the core sphere mask (below), run the obstacle phase `0x0013F488`,
   restore the full mask, run the instance-contact phase `0x00105398`, then the rider pair phase `0x00107888`,
   then the passive-departure check at `0x0013F2B0`..`0x0013F2CC`: with the departure flag set and
   `0x0011FE98` returning 0 it calls `0x0011FE78(rider, 1)` → `0x001112B8` → motion-1 entry `0x001399E0`,
   which seeds the air predictor `0x001135B8` (`cAirPredictor_startLaunchIntoAir`) from the post-contact
   position and velocity. **(PS2)** The ground speed clamp at `0x0013F358` (inside `0x0013F178`) runs after
   `0x0013F488` and `0x00105398`, so contact responses see the unclamped velocity. **(PS2)**
4. Air motion, `0x00139C88`: core mask, air body phase `0x0013AA48`, full mask, then `0x00105398` with the
   bounced hit normal as its second argument (0 when there was no bounce).
5. Crash motion calls `0x00105398` from `0x00137860`/`0x00138640`; rail leave `0x0013BFA8` calls it with its
   own rail-exit sphere mask.

These contact phases belong to a second motion phase that runs after every rider's first motion phase and
pose phase for the tick; the rider pair phase relies on this interleaving (one complete rider update after
another would give different results).

## Rider collision body (rider+0xAA0)

The body object pointed to by rider+0xAA0:

| Offset | Field |
| --- | --- |
| +0x10 | broad sphere centre (float4) |
| +0x20 | broad sphere radius |
| +0x28 | active sphere mask |
| +0x2C | sphere count |
| +0x30 | 20 sphere slots of 32 bytes: centre float4, radius float, bone index u32, two further words |

Ten slots are used. Bone IDs and radii are the same for all riders **(PS2)** (24 rider bodies from four race
savestates, all six racers):

| Slot | Bone | Radius (cm) |
| --- | --- | --- |
| 0 | 1 lower spine | 25 |
| 1 | 5 head | 20 |
| 2 | 7 left upper arm | 15 |
| 3 | 9 left forearm | 15 |
| 4 | 12 right upper arm | 15 |
| 5 | 14 right forearm | 15 |
| 6 | 16 left thigh | 25 |
| 7 | 17 left shin | 20 |
| 8 | 19 right thigh | 25 |
| 9 | 20 right shin | 20 |

The centres follow the posed skeleton of the current tick. Zoe's broad radius was 78.199989 cm in the
savestates. **(PS2)** Because the pose matters, the animation chosen in the same tick feeds collision: for
example control 0 `0x00131620` calls `0x00114130` at `0x00131844`, which sets the boost scalar +0x2FC (0.25),
before the main animation selection starting at `0x00131878` reads +0x2FC at `0x00131A4C`/`0x00131B24`; a
tucked rider pressing boost therefore selects the boost-tuck animation in that same tick. **(PS2)**

**Core sphere mask.** `0x0013F178` (store at `0x0013F278`, word `0x004A115C`, gp-0x1F94) and `0x00139C88`
(store at `0x0013A734`, word `0x004A1120`, gp-0x1FD0) write the word's value into the body's active mask
+0x28 around `0x0013F488` and `0x0013AA48`, and store 0xFFFFFFFF again before `0x00105398`. Both words are 3
in the ELF and in race savestates **(PS2)**, so the ground and air obstacle queries test only spheres 0 and 1
(lower spine and head); the instance-contact phase and `0x00106F78` use every sphere. **(PS2)**

`0x00106538` is the rider translation used by the contact responses. It moves the rider position, the
secondary presentation offset, the +0xAA0 broad and child sphere centres (together with `0x00329B40`), the
query AABB at rider+0x400/+0x410 and rider+0x9D0. It does not move the posed bone arrays.

## Query packets and collectors

**Body query setup `0x0032F650`** builds a query from the +0xAA0 body. The obstacle caller enables the
normal-direction filter and passes the ground normal: terrain primitives whose normal dotted with it exceeds
0.8000000119 are excluded. Instance and box handling have their own paths and are not affected by this filter.
In mode 1 (used by the instance-contact phase) the query word +0x0 is 0, so the shape-radius getter
`0x0032F8C0` returns -1 instead of twice the broad radius, and +0x8 is 0, which disables the directional
triangle exclusion.

**Surface filter.** Collision descriptor nodes carry a surface ID; most scenery nodes use -1. The filter in
`0x00334888` (block `0x00334D00`..`0x00334D6C`):

| Filter | Nodes kept |
| --- | --- |
| 0 | all |
| 1 | only surface -1 nodes (solid scenery without a surface, trigger volumes) |
| 2 | only nodes with a real surface (surface != -1) |

`0x00334458` scans instances only (no terrain) and selects filter 1 when its t0 argument is 0, otherwise
filter 2. The obstacle phases (`0x0013F488`, `0x0013AA48`, `0x0013C140` and the crash body responses) see
terrain plus surfaced nodes; solid surface -1 scenery is answered only by the instance-contact phase
`0x00105398`. In Snow Jam only five nodes carry a real surface; of the surface -1 nodes, 276 are solid
(flags 3), 892 have flags 0 and 97 are triggers (flags 2).

**Instance routing by runtime flags.** Before any geometry test, each collector routes an instance by its
runtime flags (instance+0x08):

- Body collector `0x00333EF8`, block `0x003340F4`..`0x003341A0`: bit 0x20 selects static geometry (then the
  authored bounds are checked); otherwise bit 0x40 requires an entity, whose vtable predicates (entries
  +0x160/+0x168, function pointers at +0x164/+0x16C) supply the dynamic path; otherwise the instance is
  skipped without any geometry test. The entity route is not permission to test a static approximation.
- Ray collectors `0x00335B90` (mode 0, block at `0x00335BB0`) and `0x00336D40` (mode 2, block at
  `0x00336D64`) also prefer 0x20 over 0x40. Mode 0 checks the entity pointer and skips when it is null; mode 2
  reads the entity's vtable without a null check.
- Mode-0 rays include only surfaced nodes and mode-2 rays only surface -1 nodes. Air prediction's mode-0
  rays test coarse terrain (plus surfaced nodes) and its mode-2 rays test scenery only. The body ray
  `0x0032E688` returns no sphere-tree contacts at all.

**Contact packet** (entries produced by `0x00334888`; the selected one is copied to rider+0x9E0):

| Offset | Field |
| --- | --- |
| +0x20 | vector subtracted from the rider velocity for the closing speed (the hit surface's velocity; unconfirmed) |
| +0x40 | depth; -1 means no contact |
| +0x48 | the hit node's prebuilt collider |
| +0x4C | surface ID passed to `0x00105D98` |
| +0x50 | instance pointer (hence rider+0xA30 = selected instance) |

**Rider caches and scope.** Rider queries read the rider's scope list at rider+0x860, which `0x00120E50`
rebuilds from the query AABB (+0x400/+0x410) with `0x00332DB8`. The terrain contact cache is rider+0x864 and
the body contact cache rider+0x868. The ground contact, the landing probe `0x0013A7B0`, the `0x0013F488` /
`0x0013AA48` body queries and the crash motion (`0x00137860` body query with +0x868, `0x00138960` terrain probe
through `0x003342D0` with +0x864) share them, and entering control 8 does not clear them; which of two
overlapping patches is reported at a seam depends on this cache. **(PS2)**

**Octree.** The walks (`0x00335D78`, `0x0033CCF8`, `0x00340FA0`) visit children in the order
0,1,3,2,6,7,5,4. `0x00332DB8` builds its scope list in the same Gray order for partially covered cells.
Patches and instances are inserted at list heads. Collision ignores texture-streaming chunks:
`0x00335960`, `0x0033CCF8` and `0x00335D78` test only the patch flags at patch+0x0A.

**Whole-world query `0x00336850`** (used by the crashbag rigid bodies). It keeps the packet whose depth is
closest to -1 (`0x003306D8`); ties go instance before terrain, then lower instance+0x78, then lower
patch+0x150. Terrain goes through `0x00335960` (patch flags 0x41, strict bounds) and `0x0032B6E0` in coarse
mode (3x3 cells, stride 3, cached cell first). Instances go through `0x00335B90`, which always uses filter 2,
so every surface -1 node (all crashbags and almost all scenery) is skipped; the surfaced Snow Jam nodes are
type-1 meshes, handled by `0x00330540` and `0x0032C0F8` → `0x00330828` → `0x00328030` → `0x0032CA78`. There
is no 64-packet cap on this path. Zero-area terrain cells in savestates carry a (1e11, 0, 0, 0) marker, which
arises only from VU VRSQRT(0) giving FLT_MAX. **(PS2)**

## Authored instance collision data

**SSB kind 16 descriptor table** (per location):

| Header offset | Meaning |
| --- | --- |
| +0x38 / +0x3C | LUN program count / offset table (see stage scripts) |
| +0x40 | collision descriptor data offset (also the end of the program area) |
| +0x44 | instance count |
| +0x48 | offset of a u16 descriptor index per instance resource ID |
| +0x4C | descriptor count |
| +0x50 | offset of u32 descriptor offsets, relative to the descriptor data |

A descriptor is a 16-byte header followed by 12 bytes per model node. Header +0x08 selects the instance's
stage-script handler row (shown for the pickups, see below); +0x0C is the separate collision-mesh resource and
becomes a cache pointer at runtime (`0x003A6CC8`). Node data includes at least flags, a scalar value, an
auxiliary word and a surface ID (exact packing not established). Node flag bit0 makes a contact physical
(`0x001057B8` is called; a node value of 0 means a soft collision there), and bit0 with a non-zero value makes
it a priority contact in the selection. Bit1 marks a trigger whose contact is copied to the rider for script
dispatch.

`0x00334888` dispatches on descriptor type: 0 no collision, 1 separate triangle mesh, 2 model-node boxes,
3 sphere tree. Snow Jam has 1,136 / 1,497 / 404 / 15 instances of these types. Instance names containing
"trig" are not a reliable guide to the type.

Instance fields used here: +0x00/+0x04 spatial list links, +0x08 runtime flags, +0x0C entity pointer, +0x10
world matrix (64 bytes), +0x78 resource ID, +0x7D/+0x7E streaming chunk, +0x88 pointer to its collision
descriptor. For sixteen live instances, +0x88 pointed at the descriptor that the kind-16 table gives for their
resource ID (same type, flags and collision resource). **(PS2)**

**SSB kind 12 collision geometry.** Dedicated collision meshes, not tessellated render geometry: triangle
indices are byte triples, vertices and normals float4, and bounding boxes group 16 triangles. Coordinates are
local, Z-up centimetres. Type-3 resources hold sphere trees ("format 3"): a root centre, radius/offset/stride
per level, and a bounded signed-byte RLE occupancy stream. The tree header also holds mass properties used by
the crashbags: +0x1C centre of mass, +0x28 inertia, +0x4C inverse inertia (the runtime tree object keeps them
at +0x2C/+0x38/+0x5C).

**Transforms.** Local node translations are scaled, the node hierarchy is composed with the instance rotation
and translation (the uniform instance scale is applied after the node hierarchy and before the instance
rotation/translation; negative scales occur), and the rotation is transposed for the inverse. The reciprocal
uniform scale is applied separately to body positions and radii. Result points are scaled before the world
transform; the local penetration value is kept unscaled for response and selection. The query direction is
kept for local triangle filtering.

**Runtime instance flags** (instance+0x08). The high half holds the authored flags; the low half is live state:

| Bit | Meaning |
| --- | --- |
| 0x1, 0x2 | both set: drawn by the static collector; instances with bit0 clear are helpers (reset planes, trigger and load volumes, emitters) |
| 0x4 | required by the dynamic draw `0x00356298` (tested at `0x0035636C`) |
| 0x20 | static collision route |
| 0x40 | entity collision route |
| 0x100 | in the renderer's dynamic list (set by `0x001032C0`) |
| 0x200 | renderer bookkeeping (set by `0x001032C0`) |
| 0x2000 | suppresses the trigger copy and contact audio in `0x00105398` |

Authored flags `0x00200000` (static; the restore below turns it into runtime 0x20) and `0x40000000`
(dynamic instance) classify instances. Instance node destruction `0x0034FBF0` detaches the node through
`0x0034FC80`, then restores the flags: it masks them with `0xFFFF0300`, ORs in the arithmetically
right-shifted high half and sets bit1, before the base destructor `0x00354920` runs. Ordinary pickup flags
`0x00210004` become `0x00210023`. This transform (at `0x0034FC1C`, inside `0x0034FBF0`) also produces the
countdown flags of the dynamic instances and the mode-1 restore of `0x002FC2C0`.

## Narrow-phase kernels

- **Body vs triangle `0x0032A1C0`.** Reject against the broad sphere, then test enabled body spheres: first
  the centre's projection onto the triangle plane, then vertex/edge overlap. The chosen sphere is the one with
  the smallest signed centre-to-plane distance (not the largest penetration). The returned point is the
  centre's plane projection even when an edge test admitted the overlap.
- **Body vs box `0x0032B2B8`, `0x00329590`.** Tests box face projections and rejects overlaps confined to edges
  or corners. The loop consults the enabled-mask bits but keeps testing the broad sphere: it never advances to
  the child sphere coordinates.
- **Body vs sphere tree `0x00327F18` / `0x0032CDB0`.** Rejects on ancestor overlap, visits children in
  ascending order, returns the first successful bone sphere, and ignores the active-sphere mask.
- **Sphere-mask cache `0x0032DF28`.** Ten shallow and two deep round-robin entries (depth threshold 5). The
  key omits the model-node index, so the first visited node's masks are reused for later nodes of the same
  resource even when their authored masks differ.
- **Tree vs triangle** (`0x00330788` → `0x0032CA78`): child order from the corner directions (`0x0032DB40`,
  sorted by the shell sort `0x0032DA40`), recursion `0x0032D470`, point-in-triangle `0x0032D440` →
  `0x0032B6A8`. The scratch collider's scale accumulates 1/instance-scale per processed node because
  `0x00327CC8` does not copy +0x90.

## Obstacle response (`0x0013F488`)

Gate: skipped in control 9. Otherwise it is skipped only when rider+0x874 is 0, rider+0x4C8 < 50, and
|position Z - rider+0x498| < 50 cm (the meaning of these fields is not established).

The linear response (`0x0013F5C4`..`0x0013F7C4`, inside `0x0013F488`):

1. Reject normals almost opposite the ground normal. A slightly downward normal is projected onto the ground
   tangent plane and renormalised.
2. Translate by n * 1.1000000238 * penetration.
3. If the relative velocity is separating, stop here: no impulse, no `0x001065B0`, no `0x00105D98`. Ticks that
   still overlap the same face while separating only translate. **(PS2)**
4. Otherwise add, along n: `closing + max(0.0500000007 * closing, 27.7777786255)`.
5. `0x001065B0` corrects the heading toward the wall by at most 20 degrees per call, up to a 110 degree
   wall-facing limit, using the post-multiplied quaternion convention; the quaternion is then rebuilt.
6. `0x00105D98` reports the contact.

Dynamic surface callbacks can alter the hit before this response.

## Instance-contact phase (`0x00105398`)

Arguments: rider and a1 (a normal from the caller, or 0).

1. Skip in control 9.
2. Call `0x00106F78` (hips/rail contact, below); its return value is ignored and the query runs on the moved
   body.
3. Build the query with `0x0032F650` (mode 1) and call `0x00104E70`. Nothing more happens unless the returned
   depth is >= 0.
4. Choose the normal: when `0x001231A8` holds (motion 0, or motion 2 with owner+0x30 == 0) the hit normal is
   projected off rider+0x370; otherwise off a1; with neither, in motion 4 the normal becomes plus or minus
   owner+0xB0 (the rail direction). If the projection is shorter than 0.001, the axis itself is used.
5. Build a contact record: +0x00 point, +0x10 normalised velocity (rider+0x1E0), +0x20 normal, +0x30 closing
   speed `max(0, dot(-n, v - hit+0x20))` in the x lane (the other lanes are uninitialised stack).
6. If the node has flag bit1 and the instance lacks flag 0x2000, copy the hit packet and record to
   rider+0x9E0 and rider+0xA60 (rider+0xA30 then holds the selected instance, which drives `0x00121818`).
   If the node has flag bit0, call `0x001057B8`. If the instance lacks 0x2000, call the contact audio
   `0x00296088`.

**Selection `0x00104E70`.** Calls `0x00334458` with the scope list rider+0x860, the body query, capacity 64
and t0 = 0 (filter 1). It records the distinct resource IDs (instance+0x78) of the contacted instances in
rider+0x5B8 (at most 64, terminated by 0xFFFFFFFF). Ranking uses node priority (flag bit0 and a non-zero
value), the sign of dot(contact - centre, normal), the absolute distance from the query radius, and the
unsigned resource ID as tie break; a facing latch is kept when a higher-priority node wins, so it is not a
plain tuple sort. With two or more contacts the normals of the priority contacts are summed starting from the
zero vector at `0x004FF120`, and the sum is normalised only when longer than 0.001. It then calls the selected
entity's callback (instance+0x0C, vtable +0x154) and returns the selected depth (+0x40, -1 when empty).

**Response `0x001057B8`.**

- Node value 0: call the soft collision `0x00108388` and return.
- Otherwise closing = max(0, n·(hit+0x20 - v)) and restitution r = clamp(node+0x4, 0, 1).
- Static instances, or entities whose vtable +0x74 predicate returns non-zero: push by n * (depth * 1.1)
  through `0x00106538` (the operation order differs from `0x0013F5C4`), impulse =
  `closing + clamp(r * closing, 55.5556, 1388.8889)`, `0x001065B0` only in motion 0, then `0x0011E098`
  (`cRider_updateOrientationImplicit`).
- Entities whose predicate returns 0 use a mass formula with h = closing / (100/m + 1):
  `impulse = sqrt(max(0, h*h - (1 - r) / (100/m + 1))) - h`, where m appears to be the node value (for a
  crashbag, value 1e30, the result is about -1/(2*closing); unconfirmed).
- In the air (motion 1, or crash motion 2 with owner+0x30 == 1), below 833.33 cm/s, the air bounce counter
  rider+0x3F4 grows by `(2.5 - up·n) * max(n.z, 0.2)`.
- Motion 1 with animation channel-2 class 1, 2, 9 or 11 and presentation-up·n > 0.3 takes a "land on top"
  path: velocity rebuilt from the tangential part, peak impact updated, `0x0010E910`, `0x00119E38`, control
  13 then 5, clip 268 (unless clip 268 is already past 0.2), and an air predictor restart.
- Every other case adds n * impulse to the velocity and calls `0x00105D98(rider, record, hit+0x4C)`.

There is no separating-contact skip here: a closing speed of 0 still bounces by 55.5556 cm/s. **(PS2)**

## Hips/rail contact (`0x00106F78`)

The first step of every `0x00105398` call. It is not an instance query.

- Returns 0 in motion 4. Otherwise it takes the hips bone (rider+0x89C, bone 0) and its local Y axis, and
  queries the rail spline layers of the scope list (type 1 = grind rails) with
  `0x00334680(list, hips, out, mask 1, 300)`. That query finds the closest rail point by golden-section search
  (`0x00335128`); out+0x10 is the unit rail tangent, out+0x20 the zero vector, out+0x50 = 0.
- Exits without contact when: no rail; speed > 0.001 and (rail point - hips)·v < -0.2 * speed (rail behind);
  the rail point is more than 50 cm from the hips segment (hips plus or minus 50 cm along the axis); or the
  board-root rail attach test `0x00108A48` would attach (a rider who can grind does not bounce).
- Response: the record normal is the rail tangent flipped to point along v, with closing = |v·tangent|. The
  push direction e is hips - point with its tangent component removed (and its rider+0x370 component when
  `0x001231A8` holds), normalised; if that is shorter than 0.001 the tangent is used. Inside 50 cm, push by
  e * (50 - gap·e) through `0x00106538`; then v += e * (max(0, e·(0 - v)) + 55.5556); in motion 0 call
  `0x001065B0` with e as the hit normal, then `0x0011E098`; finally `0x00105D98(rider, record, rail surface)`.
  The `0x00105D98` call from here returns to `0x00107554`. **(PS2)**
- Constants at `0x0049B24C`, `0x0049B250`, `0x0049B254`, `0x0049B258` (gp-0x7EA4..gp-0x7E98): 0.001, -0.2,
  0.001, 55.5556.
- `0x001211F8` moves the rail tolerances rider+0x22C/+0x238/+0x25C toward their targets every tick, also while
  off a rail; +0x25C is -0.25 on leaving a rail and climbs by 1/30 per tick. The attach test's axis half-width
  in `0x001086B8` depends on it (50 cm in the observed cases). **(PS2)**

## Collision reactions (`0x00105D98`) and timers (`0x001210B0`)

`0x00105D98(rider, record, surface)` receives the world point, pre-bounce incoming direction, adjusted normal,
closing speed and raw surface ID. It classifies with the pre-impact presentation frame (rider+0x160..+0x190)
and, separately, with the rebuilt physical frame.

Each contact first updates rider+0x3E0 (previous normal) and rider+0x3F0 (direction-change accumulator):
`acc += 1 - max(dot(n, previous), 0)`. Then:

| Condition | Result |
| --- | --- |
| control 9 | ignored before the history update |
| surface property +0x44 non-zero | `0x00116120` requests control 9 / motion 3 (forced reset) |
| already in motion 2 | marks another crash collision; may restart the air predictor |
| soft grounded impact | plays animation semantic 55..60, may change manual spin, enters control 3 |
| hard impact | `0x0010EB30`, which ends in control 8 / motion 2 (control 13 is transient) |

Other contacts update the peak impact scalar and choose a reaction from motion/control mode, presentation
axes, contact height, post-bounce speed and authored thresholds. Some glancing side reactions change manual
spin and consume exactly one draw from the shared random generator; paths that do not change spin draw
nothing.

In crash motion 2 with owner+0x30 == 1 (air), the block `0x00105EA0`..`0x00105EEC` calls
`0x001135B8(rider+0x788, position, velocity, rider+0x2E4)`, i.e. `0x00113198`
(`cAirPredictor_reset`) followed by `0x00113618` (`cAirPredictor_initLaunch__FPcP5sQuadT1`): a full restart
that clears the times, the hit, the heading and the normal. rider+0x2E4 is the speed limit; it also sets the
predictor's speed cap and chord limit. **(PS2)** Air motion 1 contacts restart the predictor the same way.

**Soft collision `0x00108388`** plays the soft-collision semantic with an ordinary play,
`0x003128E8` (`cRiderAnimBase_play`)`(anim, semantic, 0, -1)`. `0x00311F00` therefore inherits a fading-out
sequence with the same clip, root, mask and mirror, keeping its clock and weight: its target becomes 1 and its
fade becomes blend * (1 - weight). A second soft collision during the fade of the first does not restart the
clip. **(PS2)** Control 3 then updates through `0x0012E778`, which only retargets turn, crouch and brake; it
does not write the velocity.

Other lifecycle routines: crash motion `0x00136E98`/`0x00136EE0` (air and sliding submodes), frozen motion 3
`0x00136958`/`0x00136978`.

**Timers `0x001210B0`** (once per tick): the previous normal decays by 0.980000019, the direction-change
accumulator by 0.955999970 and a secondary counter by 0.978333354. It requests `0x00116120(rider, 0, 2)` when:

- the decayed accumulator +0x3F0 is above 4.5 (any motion); or
- in the air (motion 1, or motion 2 submode 1): a live prediction (status 1 or 3) has more than 45 s left, or
  the air bounce counter +0x3F4 is above 5.

The reset begins at once, so that tick's motion is already motion 3; the reset controller `0x0012F398` first
steps on the next tick. A new request while the reset runs restarts its progress from 0. **(PS2)**

## Rider-vs-rider collision (`0x00107888`)

Pair records: each actor has six 36-byte records, one per opponent slot; the reciprocal record is the other
actor's record at the initiating actor's slot.

| Record offset | Meaning |
| --- | --- |
| +0x08 | starts at 1e10 (probably the planar distance; unconfirmed) |
| +0x10 | last-contact tick |
| +0x14 | last-checked tick |
| +0x18 | attack cooldown tick |

`0x0010F3B8` enables an owner's records only when owner+0x880 == 7 and the other slot exists and differs;
other actors still receive reciprocal timestamps. `0x0010F560` refreshes the reciprocal planar XY distances
and bearings once every six manager ticks, plus separate proximity/ranking fields not used by the overlap.

Order in `0x00107888` (called from the initiating actor's ground phase `0x0013F178`):

1. Cache the initiating actor's collision weight (and its attack animation window), then loop over the six
   slots. Later participants' weights and eligibility are re-read live, so a reaction callback can change them.
2. Skip a disabled owner record or an opponent with +0x878 != 0.
3. If the reciprocal +0x14 is older than the current signed tick, write the current tick into both records
   before the query; otherwise the other actor has already checked the pair this tick and the ordinary query
   is skipped.
4. `0x00329F98` rejects disjoint broad spheres and returns the first overlapping child-sphere pair in authored
   order, ignoring the active masks.
5. Separate: -0.55 * penetration to A and +0.55 * penetration to B, each projected against that actor's
   ground normal in motion 0 or crash motion 2 submode 0, applied through `0x00106538`.
6. If A's +0x10 < currentTick - 3: normalise the penetration vector, compute both signed impulses from the
   pre-response velocities and weights, dispatch A then B, and only then write the current tick into both
   +0x10. The cooldown suppresses impulses, not separation.
7. Evaluate the attack branch separately (also when the query missed or the pair was already checked).

**Weight** `0x0011FF98` (`cRider_getMass`): integer weight from `0x00530970 + characterId*0x88 + 0x40`, times
`1 + stat * 1.5003352165222168`, times `1 + boost(+0x2FC) * 10`. The stat comes from `0x00148F50`
(`cBEStatInterface_getCollisionAttrib`): progress byte 5, maximum byte 13, with the usual override and a fixed
NPC value.

**Impulse `0x00107E70`.** Ignores control 10. Caps the signed impulse at plus or minus 555.555542 cm/s,
applies it along its direction and projects against the ground tangent where appropriate. In motion 1 and
crash-air (2/1) it restarts the air predictor; there an upward impulse suppresses the later reaction
magnitude but keeps the velocity change. After the velocity change, motion 2 and control 9 skip the reaction.
Otherwise the uncapped magnitude must exceed 39.995327 cm/s; above 599.974 cm/s a crash semantic is chosen
from presentation-axis dominance and the shared random generator and `0x0010EB30` is called; otherwise the
soft routine `0x00108388`. The knockdown cheat sets the magnitude to exactly the hard threshold, so the strict
comparison takes the soft branch. The reaction point uses the cached planar distance, not the overlap point.
`0x00107E70` does not rotate the heading.

**Attack branch.** Requires the owner's animation channel 1 class 13 with marker 0 active and marker 1
inactive, and excludes an opponent in class 3 in the same window. It checks its reciprocal +0x18 cooldown,
distance in [0.001, 150] cm and the owner's facing vector +0x340, combines the attack stat with the +0x350
strength scalar, and uses 0.5 * separation direction + 0.5 * owner velocity direction (not renormalised). It
dispatches to the other actor with the attack flag set, then updates that actor's reciprocal attack timestamp.

## Stage-script handlers for instances

**Handler rows.** Kind 16 header +0x18/+0x1C give the count and offset of six-word handler rows (231 rows at
+0x70 in Snow Jam). Each word references a LUN program or is -1 (0xFFFFFFFF). In these rows the references
look like 0x1C08 = program 28, with the program index in bits 8 and up (unconfirmed encoding). Slots used by
the instances described here: slot 1 (the pickups' programs 27/29, apparently initialisation; unconfirmed),
slot 2 (contact handler), slot 4 (Debounce-completion override), slot 5 (timer handler). `0x003A6B78` looks up
a slot and returns -1 when it is empty.

**LUN programs.** Kind 16 header +0x38 is the program count and +0x3C the offset table; the programs end where
the collision data begins (+0x40). Each program starts with the magic "LUN\0", then +0x4 relative code end,
+0x8 extent, +0xC a duplicate extent; bytecode runs from +0x10 to the code end, followed by trailer words.

**Interpreter.** Inside `0x002227D0` (`luno_cLunoVM_execute`), the dispatch at `0x002228C4` masks the low byte
of the instruction and jumps through the 43-entry table `0x004797B0`. Opcodes 0x14-0x17, 0x1D and 0x24-0x27
take one inline operand word. Opcode 0x21 (handler at `0x00223F58`) calls a builtin: index in bits 16..23,
argument count in bits 24..31, destination in bits 8..15, through the function table `0x00441F38` (111 entries).

Builtins used here:

| Index | Function | Use |
| --- | --- | --- |
| 0 | `0x002FC0D0` | construct an Object entity for the current instance |
| 1 | `0x002FC7D0` | create or update a Debounce component |
| 2 | `0x002FC420` | instance event 6; falls back to `0x002FC2C0` |
| 15 | `0x002FD250` | attach a RollerModifier (via `0x00355DB8`) |
| 16 (0x10) | `0x002FD420` | make a particle emitter |
| 27 (0x1B) | `0x002FF850` | award a powerup effect |
| 65 (0x41) | `0x00301D78` | instance-contact predicate |
| 69 (0x45) | `0x00302490` | set the state of attached components |
| 99 (0x63) | `0x003061B0` | global feature-bit query |

**Dispatch `0x00121818`.** Runs when rider+0xA30 (the selected trigger instance) is non-null. With an entity
on the instance, `0x00121840`..`0x00121858` calls the entity's contact entry (+0x140/+0x144) with rider+0xA60
(record), rider+0x9E0 (contact packet) and rider+0x6C0 (rider interface). Without an entity,
`0x00121864`..`0x00121870` calls `0x0030A060` directly.

**`0x0030A060`** installs the current player, instance and contact context, applies player/ghost
restrictions, looks up handler slot 2 through `0x003A6B78`, and runs it through `0x00309C88` (or nested-context
handling). On exit it calls an optional entity callback (entry +0x14C) and clears the context.

**Entity contact entry `0x00355770`** (shared by the Object entity and the type-1 entity): if an attached
component exists, call its methods +0x54 and +0x4C (with the rider identity from `0x002D1B30`) and abort when
the predicate rejects; abort while entity+0x20 > 0; otherwise set entity+0x20 = clockRate/2 (30 at 60 Hz) and
forward through `0x0034FE00` → `0x002D19B8` → `0x0030A060`. The entity update `0x00356198` decrements a
positive entity+0x20 before the component predicate and before the component update (entry +0x78); zero or
negative values are left unchanged.

**Contact predicate (builtin 65).** `0x00301D78` resolves an authored resource through the world table at
gp+0x16C8 (`0x004A47B8`) (block `0x00301E5C`..`0x00301EA4`), gets the current rider from the player manager
(`0x00301EAC`..`0x00301EDC`), calls the rider interface's instance-contact test at `0x00301EF0`, and writes the
result through `0x00226610` from `0x00301EF8`. The rider interface (rider+0x6C0, vtable `0x004583A8`) entry
+0x18/+0x1C resolves to `0x00108C28` (the decomp currently places it inside `0x00108A48`), which checks whether
instance+0x78 is in rider+0x5B8 (bounded to 64 entries, stopped by 0xFFFFFFFF). `0x0030BFC0` also uses this
predicate (at `0x0030C10C`..`0x0030C120`) for up to three resources before further position tests. Snow Jam's
stage bytecode contains 17 builtin-65 calls. This predicate is separate from the slot-2 collection route.

## Boost pickups

Snow Jam has three trick boosts and two speed boosts (by authored name; 30 `collecta` and one `collectabreak`
instances also exist). Their descriptors: type 2, flags `0x00210000`, no collision mesh (-1), node flags 2
(trigger only, not solid), surface -1, so only filter 1 (the instance-contact phase) sees them. Header +0x08 is
0x1408 for speed boosts (row 20) and 0x1508 for trick boosts (row 21).

| Row | Slot 1 | Slot 2 |
| --- | --- | --- |
| 20 (speed) | program 27 | program 28 |
| 21 (trick) | program 29 | program 30 |

Other slots are empty, including slot 4, so the standard Debounce completion runs.

**Programs 28/30 (slot 2).** Set the arguments (type 1 in program 28, type 2 in program 30; amount 5) and call
builtin 27; then builtin 69 with argument 1; then builtin 1 with arguments 2 = 3 and 3 = 0.

- **Builtin 27 `0x002FF850`** gets the player (default current), effect type and float amount and calls
  `0x0010F1C0` at `0x002FF95C`. `0x0010F1C0` dispatches types 0..7 through `0x00456AF0`. Type 1 calls rider
  interface entry +0x6C → `0x0010E770`, which adds the amount to rider+0x2E8 (ground boost window); type 2
  calls +0x74 → `0x0010E7D0`, which adds it to rider+0x2EC (boost modifier). These are counter additions, not
  awards to the stored boost meter +0x2F8. A speed-boost contact set rider+0x2E8 to 5. **(PS2)** A positive
  +0x2EC feeds the air control's spin modifier and the air animation selection.
- **Builtin 69 `0x00302490`** resolves the instance, checks instance+0x0C, queries entity vtable +0x84 and
  reads entity+0x1C (the modifier container). Argument 1 calls `0x00353278`, which walks the attached entries
  from head+0x10, gets each type via vtable +0x14 and requests state 3 via vtable +0xC for type-3 entries;
  argument 0 calls `0x00353228`. The effect on collection eligibility is not established.
- **Builtin 1 `0x002FC7D0`** defaults: target -1 (current instance), duration 1.0, state 1, mode -1. The
  pickups pass state 3 and mode 0. It updates an existing component through `0x002FAE38` (`checkActiveNode`)
  or allocates a `Debounce` (allocation tag `0x004896E8`, constructor `0x00342C08`).

**Debounce.** The constructor stores ticks = int(duration * clockRate): the clock pointer is at gp+0x2A74
(`0x004A5B64`), pointing to `0x004C9428` with rate 60 at +0x10 in a race savestate **(PS2)**. Mode 0 clears the
instance's low four flag bits; the state (3) is kept at +0x30. The update `0x00342D88` decrements a strictly
positive count at +0x2C; on the transition 1 → 0 it calls the completion entry (+0x110/+0x114) with reason 1 and
returns 0, otherwise returns 1. Zero or negative counts stay unchanged and active. Its contact entry is the empty
`0x003614F8`. The contact cooldown (entity+0x20, 30 ticks) and the debounce (60 ticks) are separate fields
advanced in the same entity update `0x00356198`.

**Completion `0x00342E98`.** Calls the guard `0x0034FCC0` → `0x002D19E8` → `0x0030A598` → `0x003A6B78`
(handler slot 4; if present, `0x0030A5C0` installs the instance as script context and runs it through
`0x00309C88`). With state 3 it removes the Debounce (its destructor applies the `0x0034FBF0` flag restore),
allocates a 0x1C-byte node and constructs it as type 19 on the same instance, in bucket 1, with `0x00350F60`.

**Type-19 node (`RestoreNode`, allocation tag `0x004896C8`).** `0x00350F60` calls the base `0x0034FB00(19,
instance)`, installs vtable `0x00491680`, clears instance bits 0x20, 0x40 and 0x2, and sets 0x4. Its draw entry
(+0x20) is the empty `0x00360790`, its contact entry (+0x140) the empty `0x003609F0`, its outer update
`0x003608E8` calls `0x00360910`, which returns 1 (ignored by the scheduler), and its completion `0x00360AE0` is
empty. The specialised entry +0x10C, `0x00350288`, rebuilds model-node matrices from the source hierarchy.
Despite the name, nothing in its own update restores the pickup: after the debounce the pickup stays consumed
until some later reset or replacement (not traced).

**Live entity observation.** With the rider moved onto a speed boost in a race savestate, an entity (type 1,
vtable `0x00490B10`, with a wrapper whose component pointer was 0) appeared on the instance and its flags went
from `0x00210023` to `0x00210125`. **(PS2)** With a null component pointer `0x00355770` skips the component
predicate. What creates this entity was not traced. Its entry +0x154 (`0x0034E698`) adjusts contact surface
motion and is not the reward path; several of its entries have non-zero this-adjustments.

**Initialisation programs 27/29 (slot 1)** call builtin 99 and then, conditionally, property/FX builtins. Builtin
99 (`0x003061B0`; the test is at `0x00306260`..`0x003062C8`) tests bits 6/8/7 of the global `0x005308D0` for
selectors 0/1/2 and returns "enabled" when the bit is clear (other selectors return 1); both programs use selector
1. This looks like an FX or debug gate (unconfirmed).

**Feedback.** After the counter addition, `0x0010E770`/`0x0010E7D0` call `0x0028B180` → `0x0029CED8` (kind 0
or 1, scalar 1; it selects IDs 70/71, other kinds use 75/76/74) and then `0x0028B180` → `0x002A3B18` (pickup
type 1 or 2). `0x002A3B18` checks `0x0029F160`, a non-null rider, rider+0x470 < 0, the current-rider lookup
`0x00285D98(-1)` and the suppression test `0x00288AE0`, then asks `0x002B1458` on manager+0x5560 to admit key
(0, 0x20A7). Only on admission does it pack event `0x010020A7` with `0x003D8008` and call the function pointer
at gp+0x173C (`0x004A482C`; `0x003D76F0` in the captured state) with 1 and the pickup type; `0x003D76F0` builds
an argument packet for `0x003D7418`, and `0x003D7110` searches eight event banks. The event is a speech event:
the loaded bank matches `data/speech/char/eventdat/Events.evt` (23,016 bytes, stored in both
`DATA/AUDIO/SPEECH.BIG` and `DATA/AUDIO/ENGLISH.BIG`) byte for byte. **(PS2)** The bank callback at `0x0044FF90`
leads to `0x002AF8A8` → `0x002B0F48` → `0x002B04D8`. Visual boost particles are a separate path (not traced).

The admission queue: ten 32-byte slots; the first empty slot wins; new entries get 180 ticks; a duplicate key
is rejected unless the refresh flag is set, and a refresh changes only the existing timer; a full queue
rejects. `0x002B1720` decrements active timers (32-bit wrap) and clears the active flag when the new signed
value is <= 0; inactive entries are not ticked. `0x002B1428` only clears active flags.

## Component scheduler (bucket manager)

Object nodes register at construction (`0x00354648` → `0x00354C08` (`cBucketMan_add`)) with the manager at
gp+0x2898 (`0x004A5988`). Buckets are 0x44 bytes apart; bit 0 of a bucket's flags chooses the pending list
(sentinel +0x24, tail +0x28) or the active list (sentinel +0x04, tail +0x08). Active iteration starts from the
word at +0x08 and follows node+0x04, so a directly inserted node comes first.

The update walk `0x00354F98` fetches the head (`0x00354EA8`, `cBucketMan_first__FP10cBucketMani`), saves the next
node (`0x00354EF8`, `cBucketMan_next__FP10cBucketManPvi`) before calling the node's update (vtable +0x14), then
visits the saved node; the return value is ignored. A node registered while the bucket's flag bit 0 is set goes to
the pending list and is not updated in the current walk. `0x00354C98` drains pending entries into the active list
using ordering/equality virtuals (defaults `0x00360800`/`0x00360840` compare the IDs at node+0x14) and may destroy
replaced entries.

Gameplay order (the normal branch `0x00230C54`..`0x00230D18` inside `0x002306B8`, with the suppression flags
clear; the order of calls, not a traced frame): update buckets 1, 5, 6; secondary phase `0x00355028` on bucket 1;
another world callback; update buckets 2, 3; other managers; drain bucket 1 with `0x00354C98`. Pause/debug
branches differ. `0x00354F98` is also called from `0x00244A18` (at `0x00244F94`). `0x0026DBF0`
(`cReplay_restoreFrame`), `0x0026DDC0` (`cReplay_restoreBucket`) and `0x0026DED8` (`cReplay_restoreObject`)
deserialize saved components; they are not the gameplay tick.

## Crashbags: Object entity and RollerModifier

Snow Jam has 16 dynamic instances (descriptor flag `0x40000000`): 13 crashbags (type 3 sphere tree, one node:
flags 3, value 1e30, auxiliary 0, surface -1) and 3 snowcrumbs (type 1). At the countdown none has an entity:
their runtime flags are `0x40214023` and instance+0x0C is 0, so the collectors take the static route with the
authored bounds and matrix. **(PS2)** Snowcrumbs have no slot-2 handler and stay static. The Junction's
crashbag (a different sphere tree) takes the same route. **(PS2)**

Crashbag slot 2 is program 49: `builtin0(); builtin15(); return`.

- **Builtin 0 `0x002FC0D0`** constructs an Object entity (`0x00356DB0`, vtable `0x00490E80`); `0x0034FB00`
  sets instance+0x0C, and `0x001032C0` sets flag 0x100 (renderer dynamic list) and 0x200. With its default
  arguments it turns flags & 3 == 3 into bit 0x4.
- **Builtin 15 `0x002FD250` → `0x00355DB8`** allocates a 0x2D0-byte `RollerModifier` (allocation tag
  `0x0048E908`, constructor `0x0035DA70`, vtable `0x0048F080`) from the rider's contact packet (rider+0x9E0) and
  record (rider+0xA60). The constructor clears 0x20, sets 0x40 (entity route), clears 0x2 and sets 0x4 and 0x1:
  `0x40214023` becomes `0x40214345`.

**Entity route.** After this, collectors reach the modifier through entity+0x1C (container) → modifier:

| Caller | Object entity entry | Modifier entry | Result |
| --- | --- | --- | --- |
| `0x00334458` collidable / bounds | +0x164 `0x003569D0`, +0x16C `0x00356A00` → `0x00352B88` | +0x64 `0x00361D18` | bounds = modifier +0x220/+0x230 |
| `0x00334888` override | +0x134 `0x00356A28` | +0xA4 `0x00360BC8` | 0: ordinary node path |
| `0x00334888` base matrix | +0xD4 `0x00360990` (returns 0), +0xCC `0x00356128` | +0x9C `0x00361D38` | modifier +0x240 replaces instance+0x10 as hierarchy root |
| `0x00104E70` selected-entity callback | +0x154 `0x00356AE0` → `0x00353098` | +0xB4 `0x00360BD8` | no-op |
| `0x001057B8` rigid predicate | +0x74 `0x00355420` | +0x44 `0x00361CA8` | 0: mass path |
| `0x00121818` contact | +0x144 `0x00355770` | +0x54 `0x00361CD8`; gate +0x4C `0x00361CF8` | timer reset and re-kick; the gate returns 0, so the script is not re-run |
| `0x0030A060` end callback | +0x14C `0x00355858` | - | entity+0x20 = 30 ticks |

**RollerModifier layout** (constants are the words at `0x004A06F0`..`0x004A0720`, gp-0x2A00..gp-0x29D0):

| Offset | Field |
| --- | --- |
| +0x20 | timer (seconds) |
| +0x30 | position |
| +0x40 | orientation quaternion |
| +0x50 / +0x60 | linear / angular momentum |
| +0x70 | inverse mass (script mass 1.0) |
| +0x80 | world inverse inertia |
| +0xB0 / +0xC0 | linear / angular velocity |
| +0xE0 | own sphere-tree collider (`0x0032C508`); the hit node's tree header data (centre of mass, inertia, inverse inertia) is copied to +0x1A0 |
| +0x220 / +0x230 | bounds |
| +0x240 | world matrix |
| +0x280 | body inertia (header inverse inertia x 0.5) |
| +0x2B0 | centre-of-mass offset |
| +0x2C0 | terrain cell cache |

**Construction `0x0035DA70`.** Quaternion from the instance matrix (`0x0031B748`/`0x0031B7A8`), centre of mass
rotated in, transform `0x0035E770`, world inverse inertia `0x0035E248`, velocities `0x0035D288`; restitution
0.1, friction 0.4, bounce threshold 277.78 cm/s. Then the kick `0x0035DDE8`: velocity = rider direction *
closing / 2 + (0, 0, min(5000/mass + 100, 600)); angular velocity = normal * 10 (`0x0035CFF0` solves the
angular momentum). The attach `0x003554B0` → `0x00356780` (`cMoveNode_setupOverlapSystem`) → `0x00350570`
(`cInstanceNode_getBoundBoxInfo`) sets the bounds to the authored AABB and the entity radius +0x24 to the
largest corner distance from the instance translation.

**Update `0x0035E850`** (every tick, before the riders). timer += 1/60. Below 10 s: energy blend, gravity
-980 * mass, a contact-time damping force/torque, integrate (`0x0035D340`), inertia and velocities, collider
update `0x0032C648`, then the contact step `0x0035EDC8`: world query, push out by (depth - leaf radius/2 + 2)
along the normal, angular damping 0.975, impulse response `0x0035D4A0`/`0x0035D908` (restitution only above
277.78 cm/s; friction with a 0.001 slip threshold). A contact after 5 s sets the timer to 10. Energy below
10000 (or timer >= 10) zeroes the momenta and sets the timer to 11; from 11 to 16 s the bag is frozen; from
16 s it sinks 10 cm per tick. The entity update `0x003568B0` sets its bounds to the +0x240 translation plus or
minus radius +0x24 and relocates the instance in the spatial tree with `0x003291E0`. A rider re-contact
(`0x00361CD8`) resets the timer to 0 and kicks again. These dynamics match the game tick for tick over a whole
bag flight. **(PS2)**

**Contact step query.** `0x0035EDC8` builds a query with `0x003303F0` (`cWorldSphTree_cWorldSphTree`) from the
collider in mode 1, then calls `0x00336850` with the world from `0x002D1BE0()`, that query, the output packet and
the terrain cell cache modifier+0x2C0. The query is coarse (query+0 = 0) and unfiltered, with bounds = collider
centre plus or minus the level-0 radius. The sphere-mask cache `0x0032DF28` is shared
with the rider queries and is resolved on every `0x0032CA78` call.

## Instance state changes and event activation

**`0x002FC2C0`** is the fallback that builtin 2 (`0x002FC420`) calls when the instance's event-6 handler
returns false (call site `0x002FC590`):

| Mode | Behaviour |
| --- | --- |
| 0 | keep an existing type-6 node; otherwise destroy the current node with mode 3 and construct type 6 (DeadNode) |
| 1 | keep type 6; otherwise destroy the current node with mode 3, then restore the instance flags from the authored high half and retained runtime bits |
| 3 | keep type 6 or 19; otherwise destroy the current node with mode 3 and construct type 19 (RestoreNode) |
| other | nothing |

In mode 1 the flags are read after the destruction callback, which can change them; the restore is the
`0x0034FC1C` operation.

**DeadNode (type 6, allocation tag `0x004896B8`)** and RestoreNode (type 19, tag `0x004896C8`) both use the empty
draw `0x00360790` and the empty contact entry `0x003609F0`. In the Snow Jam race countdown 81 instances have
DeadNodes, and all of them take the skip route in the body collector and in both ray collectors. At the
countdown the body collector routes 1,798 instances static, 2 entity and 1,252 skip (including instances with
no collision geometry). **(PS2)**

**Type-16 node entities** (vtable `0x00491800`): 74 Snow Jam instances with authored flags `0x00210000` carry
one, with runtime flags `0x00210005`/`0x00210305`. Having neither 0x20 nor 0x40, they are never tested by the
body collectors (`0x00333EF8`, `0x00334458`) or the rays (`0x00335B90`, `0x00336D40`). **(PS2)** They are the
free-ride Big Challenge gates, flags and arrows; their draw entry is the empty `0x00360790`, so they are also
invisible in the race. **(PS2)** The race's other Big Challenge gates are ordinary static instances (flags
`0x00210023`) and remain.

**Inert collision instances.** Five `mdl_ARA1_endmode_collide_*` instances have authored flags 0 (neither
`0x00200000` nor `0x40000000`); their runtime flags are 2, and every body and ray collector skips them. **(PS2)**

**Which locations are live.** The location table `0x0043E250` (24-byte records: id, name[16], kind; read by
`0x00144D38`/`0x00144D50`; kind 0 course, 1 peak hub, 2 connector, 3 TRANSP, 4 sky) feeds the streaming table
`0x00442168` (50 x 16 bytes: id, SDB location index = resource track, state, kind), built by `0x0022CD40` and
driven by the loader state machine `0x0022D8D8`. The world manager is W = **(gp+0x16C8) (`0x004A47B8`); W+0x24
+ 8*track = 6 marks an active track. During the Snow Jam race exactly five locations are resident (state 2)
and active: the course ARA1 (track 8), its connectors A_ARA1 (3) and ARA1_B (9), TRANSP (0) and ASKY (10);
they are loaded before the countdown and never unloaded during the race. **(PS2)**

The event octree (`*(*(*(gp-0x848)+0x84)+0x20)`, gp-0x848 = `0x004A28A8`) holds every authored patch and
instance of these locations, all rail segments (type-1 entities), the kind-7 glow sources (type-8 entities) and
188 of the 190 course kind-6 local lights (connector kind-6 records are not inserted). Only the course painter
record is instantiated (eight `tWPIGD_ScreenTint` objects). The sets are the same in every race savestate; only
runtime instance flags change. Event versus free-ride is runtime instance state set by the course scripts at
race load, not a different file set. **(PS2)**

**Draw eligibility.** Static instances are drawn by `0x0022A5A0` (patches by `0x0022A698`) when
(flags & 3) == 3, the location is active, the item's chunk (instance+0x7D/+0x7E, patch+0x155/+0x156) is
resident, and it passes the frustum. Dynamic entities are drawn when flag 0x100 puts them in the renderer list,
through vtable entry +0x20: `0x00356298` (Object `0x00490E80`, type-1 `0x00490B10`, type-13 `0x0048EE60`) needs
flag 0x4; DeadNode, RestoreNode and type-16 nodes use the empty `0x00360790`; type-10 cloth flags (empty
`0x0034AF18`) are drawn by `cFlagManager` near the rider and statically once their entity is dropped. At the
countdown this gives 2,933 static, 35 entity, 15 flag-manager and 513 undrawn instances. **(PS2)** Texture
chunks stream by race progress (W+0x3F0 + 24*chunk, state 3); items of non-resident chunks are not drawn and
the terrain lighting `0x002EDB20` treats them as ineligible, but collision ignores chunks (see above).

**Example: the start-gate spark fountains.** The trigger `mdl_ARA1_startfireTrig_1000` has slot-2 program 116,
which creates a Debounce (state 3) and calls builtin 3 with key 5 = 90 on the timer instance
`mdl_ARA1_startfireTimer`. The timer's slot-5 program 118 creates six emitters with builtin 16 (`0x002FD420`,
MakeParticleData) in three left/right pairs, gated by builtin 0x37 with 1, 20 and 29, and plays sound 82 between
pops. This chain was read from the stage data and the ELF only. Emitter profile: 150 particles, Duration 0.5, Damp
1.5, Life 1.5, Size 25 plus or minus 15 → 100, velocity (0, 0, 3000), force z -3000, colour alpha 1 → 0, texture
28 `spx2` from PARTICLE.SSH, blend mode 0 (additive). `0x003705E0` sets the remaining time to Duration + Life +
LifeR/2 and passes Duration (not the lifetime) to `0x0036CBF8`, giving an age step of Duration * Damp /
NumParticles; with Duration >= 0, `0x00370788` only advances the kernel age (`0x0036D3E8`, + dt * Damp) and never
runs the continuous birth path. Particles use the instance matrix in `0x00370058`. `0x0036CCB8` draws from the
`0x003177F0` (`BXrand__Fv`) stream. Inferred and not verified: the builtin 0x37 argument is a time in 1/30 s since
the trigger; particle i is emitted at i * age step; the per-emitter random seeding; the trigger volume is the
instance AABB rather than the authored slab; only the player triggers it (all unconfirmed).