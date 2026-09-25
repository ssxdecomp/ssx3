# Rails and grinding

Grind rails are cubic splines stored as record kind 8 in each course's world data. When the rider's
board passes close enough to a rail, the rider switches to the rail motion (motion mode 4) and the rail
controller (control 7). The rail motion slides the rider along the spline with a lateral balance model. The
controller handles balance input, rail spins between grind styles, jumps, transfers and the hand-off to the
rail Uber controller (control 12). Rail time scores by distance travelled, with rotation rewards,
distance-threshold bonuses and an inverted bonus.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a
PS2 emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

Source files are the decomp's current splits, as reported by the address lookup.

- `src/intersect/worldsphtree.cpp`: the spline rail query `0x00334680`, the per-segment search `0x00335128`,
  the kind-8 rail record constructor `0x00341548`, and `0x003411B8` (reads the descriptor flag word).
- `src/object/railmodifier.cpp`: the type-2 (object-attached) rail query `0x0035C698` and its transform
  composition `0x0035C5A0`. The same unit holds `0x0035C0E8` (`cRailModifier_buildXform`), which the notes
  below do not describe.
- `src/object/flexbridgenode.cpp`: the type-3 rail query `0x00348290`.
- `asm/1218.s` (unsplit): the attach `0x00106848`, the attach test `0x00108A48` and board-proximity test
  `0x001086B8`, the animation sequence driver switch `0x001036A0` and completion switch `0x00103918` with their
  per-kind handlers (`0x00103BE0`, `0x00103CC8`, `0x00104238`, `0x001042E0`, `0x00104C38`, ...), and the contact
  phases `0x00105398` and `0x00107888`.
- `asm/14B10.s` (unsplit): rider helpers used by the rail controllers: `0x00113F38` (steer target),
  `0x00114130` (boost), `0x00114298` (takeoff), `0x00115358`/`0x00115168` (stance alignment), `0x00115640`
  (stance restore), `0x00116120` (recovery), `0x001161D0` (transfer), `0x001162C8` (crouch request).
- `src/ai/ai.cpp`: control 7 (`0x00131D08` enter, `0x00131D30` update, `0x00132048` exit), the rail spin
  `0x00132060`, the Uber hand-off `0x00132620`, the entry-animation picker `0x001326C8`, `0x00132770`, and
  control 12 (`0x00136268` enter, `0x00136508` update).
- `src/ai/control/handplantcontrol.cpp`: the rail motion (`0x0013AD20` enter, `0x0013AF28` update,
  `0x0013BFA8` post, `0x0013C5A0` exit) with `0x0013ADC0` (heading offset), `0x0013BD80` (rail normal) and
  `0x0013C140` (physical contact response). The split puts these next to `0x00138B48`
  (`cHandplantMotion_gainFocus`).
- `src/ai/rider.cpp`: motion/control getters and requests (`0x0011FE78`, `0x0011FE98`, `0x0011FEC8`,
  `0x0011FEE8`), `0x0011E098` (`cRider_updateOrientationImplicit`), `0x0011FA10` (`cRider_doLeanPoseAdjust`),
  `0x00121AA0` (takes a target up/forward and a gain), the triplet approach `0x001211F8`, and the input helpers
  `0x00127848`/`0x00127998`.
- `src/ai/computer.cpp`: the mode switchers `0x001112B8` (motion) and `0x00111538` (control) with their dispatch
  thunks, the meter award `0x0010E098`, and the air-to-rail scoring call `0x0010E910`.
- `src/ai/ridermetrix.cpp`: rail scoring (`0x00119918`, `0x00119938`, `0x00119958`, `0x00119D40`,
  `0x00119E38`, the distance block inside `0x00117C28`, the reset `0x00117838`, the commit `0x0011A228`).
- `src/animation/rideranimbase.cpp` and `src/animation/animsequencer.cpp`: play, replace, fade and slot
  primitives (`0x003128E8` `cRiderAnimBase_play`, `0x00311B48` `cRiderAnimBase_changeHeadingOffset`,
  `0x00311BF0` `cRiderAnimBase_changeOrientationOffset`, `0x00313A10`
  `cAnimSequence_fadeWeight__FP13cAnimSequenceff`, and others listed in the animation section).

## Rail data: world record kind 8

The record-kind switch in `0x0026DED8` (named `cReplay_restoreObject` in the decomp; the notes describe it as
the world loader's record dispatch) handles kinds 0..22 through the jump table at `0x004816C0`. The case for
kind 8 calls the rail constructor `0x00341548`. Other kinds mentioned alongside it:

| Kind | Constructor | Content (as described) |
|---|---|---|
| 8 | `0x00341548` | spline rails |
| 14 | `0x0034ED88` | AI paths |
| 16 | `0x00350F08` | collision bindings |
| 17 | `0x00356E60` | course-progress objects |
| 21 | `0x00349DB0` | course spine |

Kind-8 records sit in the SSB world data inside `DATA/WORLDS/BAM.BIG` (the GameCube `bam.gsb` has the same
records big-endian). Their names come from the "splines" array (group 3) of the
matching PHM/PSM files, for example `spline_ARA1_EventRail_0`, `spline_ARA1_GondolaRail_0`,
`spline_ARA1_LogRail_0`, `spline_ARA1_RAIL_wood_1003`. Scenery instances with rail names
(`mdl_ARA1_EventRail_2002`, `mdl_ARA1_bcrail_1002`, `mdl_BRA2_polyrailslides_*`) lie 0.2 to 7 cm from the
curves. Coordinates are centimetres, Z up.

Record counts in the five race areas (the size rule and chaining below hold for all 831 records):

| Area | Records | Segments | Total length |
|---|---:|---:|---:|
| ARA1 | 171 | 777 | 4991.8 m |
| BRA2 | 252 | 983 | 7394.7 m |
| CRA3 | 190 | 764 | 5125.7 m |
| DRA4 | 80 | 501 | 3372.7 m |
| ERA5 | 138 | 824 | 3419.0 m |

### Record header (48 bytes)

| Offset | Meaning |
|---|---|
| `+0x00` | u32 packed id `(railIndex << 8) \| track` (ARA1 track 8, BRA2 track 16). Copied to rail motion `+0x24` at `0x0013B054` inside `0x0013AF28`. |
| `+0x04` | float3 bounds min; `+0x10` float3 bounds max |
| `+0x1C` | u32 descriptor flag word, 0 in the file. The walkers `0x00334680`/`0x003411B8` test `flags & mask` (riders pass mask 1), so bit 0 must be set at load (unconfirmed which code sets it). Bit 2 doubles the rail imbalance term (`0x0013B66C` inside `0x0013AF28`). |
| `+0x20` | u32 segment count |
| `+0x24` | u32 of the form `412Dxxxx`, different per record; looks like tool pointer residue, unused by the traced code |
| `+0x28` | i32 surface id: −1 in the file, filled at load (Snow Jam: 10 for metal/fence rails, 9 for wood). It reaches the query result `+0x4C` and then rider `+0x438`, which the rider effect passes read (board sparks, snow impacts). |
| `+0x2C` | u32 0 |

### Segment (144 bytes; record size = 48 + 144 x count)

| Offset | Meaning |
|---|---|
| `+0x00..+0x0B` | three words overwritten at load: list link, and type = 1 at `+0x08` for the `0x00334680` walker; the file values are residue |
| `+0x0C` | float arc length of the segment |
| `+0x10` | float4 row for t^3; `+0x20` row for t^2; `+0x30` row for t; `+0x40` row for 1 (the start point, w = 1) |
| `+0x50` | float4 of small values (order 1e-3); not read by the traced code (purpose unknown) |
| `+0x60` | i32 previous global segment index (−1 at a rail start); `+0x64` next global index |
| `+0x68` | i32 rail index in the file; at runtime a pointer to the record header (the descriptor read at `0x0033592C`/`0x00335940` inside `0x00335128`) |
| `+0x6C` | float3 segment bounds min; `+0x78` float3 bounds max |
| `+0x84` | float cumulative distance at t = 0 (previous distance + previous length) |
| `+0x88` | pointer residue; `+0x8C` u32 flags, always 15 |

`point(t) = c0*t^3 + c1*t^2 + c2*t + c3`, evaluated in that order by `0x00335128`. `point(1)` of segment k
equals segment k+1's constant row to float rounding.

## Runtime objects

"Triplet" below means three floats (current `+0`, per-tick rate `+4`, target `+8`), approached each tick by
`0x001211F8`. The rate/target order follows from the control-12 writes (`+0x23C` rate, `+0x240` target).

### Rider fields used by rail code

| Offset | Meaning |
|---|---|
| `+0x110` | position; `+0x120` orientation quaternion |
| `+0x1A0` / `+0x1B0` / `+0x1C0` | right / forward / up basis |
| `+0x1E0` | velocity |
| `+0x1F0` / `+0x1FC` / `+0x208` / `+0x214` / `+0x250` / `+0x2C8` | presentation triplets: turn / animation turn / extra lean / brake / presentation roll / lift |
| `+0x280`, `+0x28C`, `+0x298`, `+0x2BC` | further triplets approached by `0x001211F8` (meaning not given) |
| `+0x22C` | rail steer triplet (written by `0x00113F38`) |
| `+0x238` | balance triplet (drives the balance clips) |
| `+0x244` | control-11 half-pipe balance triplet (written by `0x00132A30`, zeroed by `0x00132F98`) |
| `+0x25C` | attach-tolerance triplet |
| `+0x2E4` | speed limit |
| `+0x2F0` | Tricky time (> 0 while Tricky is active; set to 60.0 when the Uber counter reaches 10) |
| `+0x2F4` | Uber counter (0..10) |
| `+0x2FC` | boost |
| `+0x300` | time scale |
| `+0x320` | switch (reverse stance) flag; `+0x324` reference stance |
| `+0x328` | grind style: 0 none, 1 forward 50-50, 2 backward (fakie) 50-50, 3 frontside, 4 backside |
| `+0x330` | transfer flag (1 or 2, set by the transfer path) |
| `+0x360` | crouch/press latch read by `0x001162C8`, cleared by `0x00131D08` |
| `+0x370` | contact normal; `+0x3D0` surface velocity; `+0x438` surface id; `+0x460` contact point |
| `+0x3A0`, `+0x3B0` | fields negated by the stance flip `0x00115168`; `+0x3A0` is also dotted with the velocity by the transfer gate |
| `+0x77C` | motion owner (below) |
| `+0x780` | pose object; the board root bone is at `*(pose + 0x2C) + rider[+0x8A0] * 32` (position `+0`, quaternion `+0x10`) |
| `+0x790` | score object passed to the `ridermetrix.cpp` functions |
| `+0x860` | nearby-object cache (count `+0x210`, entries `+0x214`), the same layout the rail query walks |
| `+0x9D0` | board query offset added to the bone position; the contact response accumulates into it and the block at `0x00121020` (inside `0x00120F20`) clears it on the next motion tick |
| `+0xB2C` | ability flags; bit 1 allows rail Ubers. The starting profile has the value 3 **(PS2)**. |

Human rider objects carry the vtable `0x004583A8`.

### Motion owner (`rider+0x77C`)

| Offset | Meaning |
|---|---|
| `+0xB0` | rail motion object (motion 4) |
| `+0x2B0` | rail control object (control 7) |
| `+0x390` | control-12 object: `+0` phase, `+4` held identity (owner `+0x394`), `+8` rider |
| `+0xDE0` | motion mode; `+0xDE4` control state |

Getters: `0x0011FE98` (motion), `0x0011FEE8` (control). Requests: `0x0011FE78(rider, motion)` calls
`0x001112B8`, `0x0011FEC8(rider, control)` calls `0x00111538`.

### Rail motion (`owner+0xB0`)

| Offset | Meaning |
|---|---|
| `+0x00` | rail direction (tangent oriented along travel) |
| `+0x10` | lean (radians) |
| `+0x14` | time on rail |
| `+0x18` | balance, −1..1 (owner `+0xC8`) |
| `+0x1C` | heading offset |
| `+0x20` | lost-rail flag |
| `+0x24` | packed rail id |
| `+0x30` | entry position; later the previous contact position used by `0x0013C140` |
| `+0x40` | word zeroed on entry; used by `0x0013C140` as a float stationary timer |

### Rail control (`owner+0x2B0`)

`+0` accumulated spin (changes by ±π/2 per rotation), `+4` last identity byte (−1 = none), `+8` rider.

### Query result (written by `0x00334680`)

`+0x00` point, `+0x10` unit tangent, `+0x20` normal (zero for splines), `+0x30` velocity (zero for
splines), `+0x44` kind (2), `+0x4C` surface, `+0x50` instance (0 for splines), `+0x58` descriptor (record
header), `+0x68` t.

## Mode dispatch

Mode requests are immediate. `0x001112B8` and `0x00111538` run the old handler's exit, store the new mode, then
run the new handler's enter, all inside the caller.

Motion tables (six entries, motions 0..5; the words are thunks that call the handlers below):

| Table | Stage | Motion 0 (ground) | 1 (air) | 2 (crash) | 3 | 4 (rail) | 5 (handplant) |
|---|---|---|---|---|---|---|---|
| `0x00456B30` | enter | `0x0013C7A8` | `0x001399E0` | `0x00136C40` (`cWipeoutMotion_gainFocus`) | none | `0x0013AD20` | `0x00138B48` (`cHandplantMotion_gainFocus`) |
| `0x00456B50` | update | `0x0013D818` | `0x00139A20` | `0x00136E98` | `0x00136958` | `0x0013AF28` | `0x001391A8` |
| `0x00456B70` | post (after the pose) | `0x0013F178` | `0x00139C88` | `0x00136EE0` | `0x00136978` | `0x0013BFA8` | `0x00139528` |
| `0x00456B10` | exit | `0x0013F410` | `0x00139A18` (bare return) | `0x00136F28` | none | `0x0013C5A0` | `0x00139178` |

Control tables (enter `0x00456BD0`, update `0x00456C10`, exit `0x00456B90`; the exit dispatcher is
`0x00111578`). Rail-relevant rows:

| Control | Enter | Update | Exit |
|---|---|---|---|
| 0 (ground) | `0x00131608` | `0x00131620` | `0x00131C30` |
| 1 (requested by transfers) | `0x0012FC60` | `0x0012FC80` | `0x0012FE98` |
| 2 (crouch/jump) | `0x0012E980` | `0x0012E9B8` | `0x0012E9B0` |
| 3 (soft/light impact) | none | `0x0012E778` | none |
| 4, 5 (air) | `0x0012F620`, `0x00133128` | `0x0012F730`, `0x00133308` | `0x0012FB68`, `0x00134CB0` |
| 7 (rail) | `0x00131D08` | `0x00131D30` | `0x00132048` |
| 11 (half-pipe balance) | `0x001328B0` | `0x00132A30` | `0x00132F98` |
| 12 (rail Uber) | `0x00136268` (via the thunk at `0x00111714` inside `0x00111630`) | `0x00136508` (via the thunk at `0x0011181C` inside `0x00111728`) | empty (`0x00111624` inside `0x00111578`) |
| 13 | none | none | none (placeholder requested just before control 7) |

### Per-tick order while on a rail (PS2)

1. Controller update (control 7, 3 or 12). An attach happens here, inside the old controller's update.
2. `0x001200D0`, whose `0x001211F8` approaches every triplet (including `+0x280`, `+0x28C`, `+0x298`,
   `+0x2BC`, `+0x2C8`).
3. Motion update `0x0013AF28` (runs on the attach tick too).
4. Pose.
5. Motion post `0x0013BFA8`, every rail tick, not only on a loss.

## Spline query `0x00334680` and segment search `0x00335128`

`0x00334680(world, point, out, mask, radius)` builds the box `point ± radius` and walks the layer entries
(`world+0x214`, count `world+0x210`). Each entry has its type at `+0x08`:

- type 1: a static spline segment; if `descriptor+0x1C & mask`, search it with `0x00335128`.
- type 2: an object rail (entry `+0x0C` is the object), searched by `0x0035C698`.
- type 3: searched by `0x00348290`.

Every rider caller passes mask 1 and radius 300.

`0x00335128` per segment:

1. Reject when the box misses the segment bounds (`+0x6C..+0x80`).
2. Coarse pass: evaluate the curve at t = 0, 0.25, 0.5, 0.75, 1. Start with best = |q − P(0)|, index 0. For
   each chord i = 1..4 (P(i−1) to P(i)), take the closest point on the chord (fraction = dot(q − Pprev, chord) /
   dot(chord, chord), clamped to [0, 1]); when it is strictly closer, index = i.
3. Bracket from the tables `0x0048E560` (low = {0, 0, 0, 0.25, 0.25}) and `0x0048E578`
   (high = {0.75, 0.75, 1, 1, 1}), indexed by the coarse index.
4. Golden-section search, c1 = 0.381966, c2 = 0.618034, tolerance 0.0005, at most 24 iterations:

```
x1 = lo + (hi-lo)*c1;  x2 = lo + (hi-lo)*c2      // P(lo), P(x1)->d1, P(x2)->d2, P(hi) evaluated
while |hi - lo| > tol:
    if d2 < d1: lo = x1; x1 = x2; d1 = d2; x2 = x1*c2 + hi*c1   // then evaluate P(x2)
    else:       hi = x2; x2 = x1; d2 = d1; x1 = x2*c2 + lo*c1   // then evaluate P(x1)
```

5. The output point is the last evaluated curve point, t the last chosen abscissa, and the distance is that
   point's distance. The tangent is `M * (3t^2, 2t, 1, 0)`, normalized with VRSQRT. The result replaces the
   accumulated best only when strictly closer.

### Object rails (types 2 and 3)

- Type 2 (`0x0035C698`): resolves the packed rail descriptor at object `+0x30` through `0x002D1BD8`, checks
  `descriptor+0x1C` against the mask, and composes the instance/binding transform (`0x0035C5A0`, which uses
  `0x0034FED8` with object `+0x40`/`+0x34`) with object `+0x50`. It transforms the descriptor's linked cubic
  segments before searching, and returns the instance and the binding.
- Type 3 (`0x00348290`): checks the flags at object `+0x24`, loops over (object `+0x20` − 1) segments, and
  samples 64-byte cubic coefficient matrices at object `+0x50`. The result includes the instance (object
  `+0x18`), the segment index, and the binding from the virtual getter at `+0x188`/`+0x18C`; the surface comes
  from that binding.
- When the rider attaches to an instance rail, the instance receives −Δv through its virtual `+0x158`/`+0x15C`.
  The instance virtuals `+0x150..+0x174` are involved in these paths; they were not traced further.
- None of 33 saved Snow Jam rider caches (`rider+0x860`) contained a type-2 or type-3 entry **(PS2)**. This
  covers only the saved positions, not a whole-course census.

## Attach test `0x00108A48` and `0x001086B8`

`0x00108A48`:

1. Motion must be 0 or 1.
2. q = board bone position + rider `+0x9D0`; run the rail query.
3. If |v| > 0.001: reject when dot(hit − q, v) < −0.2·|v| (the rail is behind the board). The −0.2 is read
   at `0x00108B1C` from `0x0049B2BC` (gp−0x7E34).
4. Channel-2 animation class gate (`0x001446A0` tests a bit of sequence `+0xB0`): class 18 needs flag bit 2 set
   or bit 0 clear; classes 19 and 20 need bit 2.
5. `0x001086B8` board-proximity test.

`0x001086B8`: board x-axis from the bone quaternion; f2 = rider `+0x25C` (tolerance current).

```
halfWidth = 50*f2 + 30*(1 - f2)
reach     = 170*f2 + (rider+0x330 ? 50 : 100)*(1 - f2)
s = clamp(dot(hit - q, boardX), -(reach - halfWidth), reach - halfWidth)
accept if |q + boardX*s - hit| <= halfWidth
```

Otherwise, if the rail is parallel to the board (1 − dot² < 0.001) reject; else re-project through the rail
direction, query again at the new board point, and accept when that hit is within halfWidth.

## Attach `0x00106848`

Called from the updates of controls 0, 1, 2, 3, 4, 5, 11 and 12 (`0x00131620`, `0x0012FC80`, `0x0012E9B8`,
`0x0012E778`, `0x0012F730`, `0x00133308`, `0x00132A30`, `0x00136508`). In order **(PS2)**:

1. **Velocity.** d = tangent oriented along v; along = dot(v, d); v = d · min(|v|, max(|along|, 555.5555));
   then v.z *= 0.1.
2. **Style** from angle = atan2(dot(boneZ, d), dot(boneX, d)) (`0x0031C228`), first match wins:
   - control 1: switch ? 2 : 1
   - rider `+0x330` ≠ 0: |angle| > 90° ? 2 : 1
   - control 12: 3
   - board inverted (bone y-axis z < 0): dot(boneZ, d) < 0 ? 4 : 3
   - |angle| > 150°: 2; |angle| < 30°: 1; angle < −30°: 4; otherwise 3
3. rider `+0x438` = surface.
4. **Scoring.** From motion 1: `0x0010E910(rider, 0, style, +0x330, out, speed)`. Otherwise
   `0x00119D40(rider+0x790, +0x320 != +0x324, 0, style, +0x330)` and `0x0010E098(rider, 1, value)`.
5. **requestMotion(4)**, which runs at once: the old motion's exit (motion 1: `0x00139A18`, empty; motion 0:
   `0x0013F410`), then the rail motion enter `0x0013AD20` (below).
6. The surface id is written to `+0x598C` of the object pointed to by the global at `0x004A3500` (gp+0x410).
7. **Controls 0, 4, 5, 11:** request control 13, which runs the old controller's exit (control 5
   `0x00134CB0`: fade channel 1 by 0.33, zero the prewind, bake the `0x00134DD0` air presentation, run
   `0x0011E098`, and quantize `+0x2DC`; control 0 `0x00131C30`; 4 `0x0012FB68`; 11 `0x00132F98`). Control 13
   has no enter. Then `0x00115358` (stance alignment). Then, if `+0x330` = 0: play the entry semantic from
   `0x001326C8` (airborne when coming from controls 4/5) and request control 7 (runs `0x00131D08`). If `+0x330`
   is 1 or 2: play semantic 26 or 34 and request control 1.
8. **Other controls** whose style changed: if the old style was 3 or 4, rotate the physical quaternion by
   ±90° about up (`0x0011DFE0`, which ends in `0x0011E098`), call `0x00311B48` and reset the animation root;
   then `0x00115358`.
9. `0x0013ADC0`: the heading offset, from the already rebuilt forward vector.

Control 3 (soft control) attaches too: `0x0012E778` runs `0x00116378`, `0x00116120`, then `0x00106848`, and
returns when the attach succeeds. It does not request controls 13/7, so `0x00131D08` does not run; the rider
stays in control 3 on the rail until the soft clip ends and `0x0012E778` requests control 7 **(PS2)**. While on
the rail, control 3 steers with RailBalance, and when it finishes it plays the `0x001326C8` entry semantic.
The light impacts that use control 3 on a rail are semantics 55..60.

## Stance alignment `0x00115358` / `0x00115168`

- Required switch flag: style 2 needs `+0x320` = 1; styles 1, 3 and 4 need 0.
- On a mismatch the quaternion is multiplied by the pure quaternion (up, 0) (a VU product), `0x0011E098` runs,
  then `0x00115168`:
  - toggles `+0x320` and calls `0x00311B48(anim, π)`;
  - sets anim `+0x30` = `0x004FF130` (0,0,0,1) and anim `+0x40` = (0, 0, sin a, cos a) with a = −π/2 or −0
    (about the Z axis constant `0x004FF160`);
  - writes anim `+0x18` (mirror) = `+0x320`;
  - negates `+0x3A0`, `+0x3B0` and `+0x280`, and both current and target of `+0x1F0` (turn), `+0x1FC`
    (animation turn), `+0x208` (extra lean) and `+0x214` (brake).
- Styles 3/4 then call `0x0011DFE0` by +π/2 (style 4) or −π/2 (style 3) about up (it ends in `0x0011E098`, so
  the basis `0x0013ADC0` reads is already rotated). They also call `0x00311B48` by the same angle and set the
  root quaternion from (0, 0, sin a, cos a) with a = −π/4 (style 4) or +π/4 (style 3).
- Every path ends in `0x00116930`, which is empty.

`0x00311B48(anim, a)` rotates the sequence roots by **−a**: it takes sincos(−a/2), scales `0x004FF160` =
(0,0,1,0) by the sine, and calls `0x00311BF0`.

## Rail motion (motion 4)

### Enter `0x0013AD20` (PS2)

1. `0x0011FA10(rider, rider+0x110)`: bakes the turn/lean/roll presentation around the sampled board bone into
   the physical root (no `0x0011EB98` lift). Then `0x0011E098`.
2. Zero the `+0x1F0`, `+0x208` and `+0x250` triplets and `+0x2DC`. The `+0x2C8` lift triplet is not touched.
3. Zero the motion's lean, time, balance, lost flag, heading offset and word `+0x40`.
4. `+0x25C` tolerance triplet: rate 0.05, target 0.
5. Entry position (`+0x30`) = rider position.

### Heading offset `0x0013ADC0`

normal from `0x0013BD80`; side = normal × direction; angle = atan2(dot(forward, side), dot(forward,
direction)), clamped to ±0.7853982; stored in motion `+0x1C`.

### Rail normal `0x0013BD80`

- |tangent.z| ≤ 0.92: normal = normalize(Z − tangent·tangent.z), sign-matched to the rider's up; lean
  unused.
- Otherwise: side = normalize(up × tangent), perp = tangent × side, normal = perp·cos(lean) − side·sin(lean).

### Update `0x0013AF28` (PS2)

dt = timeScale/60 (timeScale = rider `+0x300`).

1. Control 12 zeroes the heading offset. Clamp |v| to rider `+0x2E4`.
2. lost = 1. Query at the board bone position (radius 300). No hit: orientation rebuild only, return.
3. Store the rail id, surface, contact point (`+0x460`); zero the surface velocity. f20 = 0.5, or
   |v|·0.0009 when |v| ≥ 555.5555 (time on rail plays no part); f24 = f20². If time on rail < 0.6, set
   tolerance current `+0x25C` = 2.
4. If `0x001086B8` fails, **detach**: dir = normalize(bone − hit), pointing away from the rail (tangent when
   the vector is tiny or |dot(dir, tangent)| > 0.5). If dot(v, dir) < 0, dir = normalize(dir −
   v·dot(v,dir)/|v|) (fallbacks: tangent, then v/|v|). v += dir·277.7778. Rebuild and return (lost stays 1).
5. lost = 0; time += dt. Tangent oriented along v − surfaceVelocity; store it as the direction.
   lateral = dot(right, hit − bone); vertical = dot(hit − bone, up), clamped to ±1000·dt; position +=
   up·vertical.
6. rel = v − surfaceVelocity. v = normalize-to-|rel|(tangent·along·30dt + rel·(1 − 30dt)) + surfaceVelocity.
   accel = tangent·dot((0,0,−980), tangent), plus tangent·(±2450·boost) when boost > 0. v += accel·dt;
   position += v·dt.
7. Lateral slide:

```
slide = steer(+0x22C, negated when up.z < 0) * 180 * clamp(f20, 0.5, 2)
if time < 0.6 or |tangent.z| > 0.92:  imb = -5
else:
    imb = (style 1/2) ? 0.3 : 1.8
    if descriptor bit 2:        imb *= 2
    else if |lateral| < 2.5:    imb = min(imb, -1)
    imb /= 1 + 1.650076 * stat          // stat from 0x00149208, bytes +6/+14
offset = imb >= 0 ? clamp(lateral, -20, 20) : lateral
slide -= offset * imb * clamp(1/f24, 1, 4)
if up.z < 0 and |lateral| < 20: |slide| forced to >= 360, away from the rail
position += right * slide * dt
```

   A negative imbalance (−5 on entry and on near-vertical rails, or the −1 cap near the centre) pulls the
   board onto the rail. The stat returned by `0x00149208` may be the rider's balance stat (unconfirmed).
8. Balance, lean and pose:
   - styles 3/4: balance = clamp(lateral/70, ±1), target lean = balance·30°, heading clamp ±40°;
   - styles 1/2: balance = clamp(lateral/30, ±1), target lean = balance·20°, heading clamp ±20°;
   - the target lean is negated when up.z < 0; lean approaches it at 300 rad/s·dt (in effect it snaps);
   - normal (`0x0013BD80`) goes to rider `+0x370`;
   - targetUp = normal·cos(lean) + (normal × tangent)·sin(lean);
   - targetForward = normalize((side·cos(h) − tangent·sin(h)) × targetUp), h = heading offset;
   - w = dot(targetForward, forward)·0.5 + 0.5; gain = (w·15 + (1 − w))·timeScale;
   - `0x00121AA0(rider, targetUp, targetForward, gain, 1e10)`, then `0x0011E098`.

### Post `0x0013BFA8`

Runs every rail tick after the pose **(PS2)**, in this order:

1. `0x0011E150`.
2. If lost: steer target 0 at rate 1/30, and the takeoff helper `0x00114298` called with −1 (the source
   describes this as negative-charge arithmetic).
3. Contact phases against the freshly posed body (`0x0013BFF0..0x0013C09C` inside `0x0013BFA8`). Each
   phase first sets a temporary body-sphere mask. The mask ends at −1 (all bits set); the incoming value is
   not saved and restored:
   - `0x00105398` (non-solid, selected-contact/trigger phase) with mask 0x16, or for control 12 the entry of
     table `0x00458230` for the held identity (identities 0..3: 0x141, 0x16, 0x2, 0x2);
   - `0x0013C140` (physical world query and response) with mask 3, set at `0x0013C078`;
   - `0x00107888` (rider-pair separation, impulse and attack dispatch; it does not attach to rails) with mask
     −1 (all bits set), set at `0x0013C094`.
4. If lost and still motion 4: request motion 1 (air).
5. `0x00294170` (in the sound system).
6. Speed clamp.

The post plays no animation: `0x00105398`, `0x0013C140` and `0x00107888` do not call `0x003128E8`. The air
controllers choose the airborne clips afterwards. `0x0013A968` is the ordinary snow landing classifier
(semantics 61/62/63/66/67), not a rail routine.

### Physical contact response `0x0013C140`

After its physical world query:

- Rejects opposing contacts with alignment below −0.9999; projects and normalizes normals with negative
  alignment.
- Translates the rider by 1.1 × depth, applies the same translation to the companion body (rider `+0xAA0`,
  through `0x00106538`), accumulates it into `+0x9D0`, and rebuilds orientation (`0x0011E098`).
- Tracks the previous contact position (motion `+0x30`) and a stationary timer (motion `+0x40`). After 0.5 s
  within 2 cm, it applies the stuck response: a push of 1111.111 cm/s along the physical forward vector or its
  projection.
- A closing velocity gets the rebound max(0.5·closing, 27.77778) and emits a collision notification with
  direction, normal and impulse (`0x00105D98` is probably that notification; unconfirmed).
- This is separate from the ordinary ground contact rebound (0.05).
- The notification can select a light impact (control 3), a crash or a reset. The crash enter
  `0x00136C40` (`cWipeoutMotion_gainFocus`) uses the airborne crash for any previous motion other than 0, which
  includes motion 4.

## Rail controller (control 7)

### Command words

Bit positions as the source numbers them, after removing the command's run-length bits:

| Bits | Meaning |
|---|---|
| word0 bit 12 | recovery → `0x00116120` |
| word0 bits 13/14 | crouch (13 pressed, 14 held) → `0x001162C8(bit14, bit13)` |
| word0 bits 15/16 | boost (15 pressed, 16 held) → `0x00114130(held, pressed)` |
| word0 bits 17..24 | signed identity (Uber choice, −1 = none) → `0x00132620` |
| word0 bits 25..30 | RailBalance × 1/31 → `0x00113F38` (call at `0x00131E00` inside `0x00131D30`) |
| word1 bits 0..5 | rotate |
| word1 bits 6..11 | transfer (× 1/31) |

Other controllers that steer on a rail pass RailBalance to `0x00113F38` the same way (PS2):

| Controller | Call site | Source field |
|---|---|---|
| control 12 | `0x001365DC` inside `0x00136508` | word0 bits 23..28 |
| soft control 3 | `0x0012E850` inside `0x0012E778` | word0 bits 21..26 (RailBalance, not CruiseTurn) |
| control 2 on a rail (style ≠ 0) | `0x0012EC1C` inside `0x0012E9B8` | clamp(word1 bits 6..11, ±0.5) |

On a rail, control 2's prewind spin/flip targets still come from PrewindSpin and PrewindFlip (the D-pad, word0
bits 15..20 and 21..26).

### Balance direction (PS2)

`DATA/CONFIG/INPUT.MAP` defines RailBalance as LStickR − LStickL, so pushing the stick left gives a negative
value (lx −0.6 packs as 54 in bits 25..30, i.e. −10/31). The value reaches `0x00113F38` unnegated; only a scale
multiply sits between the decode and the call. The slide `right · steer · 180` then moves the rider toward
−right, which is screen left with the chase camera. The rail is then to the rider's right, so balance
(dot(right, hit − bone) scaled by 1/30 or 1/70) rises and the lean and balance clips follow. With the stick left, `+0x22C`'s target
was −0.323 and `+0x238` went from −0.2 to +0.4. Stick left moves the rider left. The PS2 HUD draws no rail
balance meter.

### `0x00113F38` (steer target)

rate = clamp(|input − current|·7, 0.1, 8)/60, target = input, on the `+0x22C` triplet.

### Enter `0x00131D08` and exit `0x00132048`

- Enter: control `+0` = 0, `+4` = −1, rider `+0x360` = 0, animation-turn triplet `+0x1FC` rate 1/15 target 0.
- Exit: balance triplet `+0x238` target 0, rate 1/15.

### Update `0x00131D30`

```
0x00116120 (recovery)
0x00132770: in motion 1, wait for a class-14 clip's event bit 0, then 0x00115640 (stance restore)
            and request control 4 (rotate == 0) or 5
0x001162C8 (crouch), 0x00132620 (identity; returns on a successful Uber entry)
0x00114130 (boost), 0x00113F38 (RailBalance), 0x00113F88(0, 0), 0x00115B58, 0x00115D48
if a class-14 (rail spin) clip is playing:
    return until its event bit 0 fires
    0x001161D0(transfer)
    if rotate != 0: balance target 0; 0x00132060(left = rotate < 0)
else:
    0x001161D0(transfer)
    input = rotate, or transfer when rotate == 0; if input != 0: rotation (0x00132060)
    else if a class-10 clip is playing (0x00131F7C..0x00131F98): set the balance target and return
    else: balance target = clamp(1.2 * railMotion.balance, ±1), rate 1/15;
          if 0x00312AA0 != cycle for the style: 0x003128E8(anim, 18/19/20, -1, 0)
```

The class-10 early return means no cycle is requested while the 68/69/70 air entry plays, so the entry clip
keeps its fade-in. `0x00115B58`/`0x00115D48` appear to gate idle upper-body reactions (unconfirmed).

### Rail spin `0x00132060`

Semantics 49..54 are class 14 ("RailSpin"). The root values are the (0, 0, sin a, cos a) quaternion angle a.

| Style | Left | Right |
|---|---|---|
| 1 | → 3, sem 49, root +π/4 | → 4, sem 50, root −π/4 |
| 2 | → 4, sem 53, switch 0, balance negated, root −π/4 | → 3, sem 52, switch 0, balance negated, root +π/4 |
| 3 | → 2, sem 51, switch 1, balance negated, root −π/2 | → 1, sem 51, root −0 |
| 4 | → 1, sem 54, root −0 | → 2, sem 54, switch 1, balance negated, root −π/2 |

Then control `+0` changes by ∓π/2 (sign by direction), and `0x00119918(rider+0x790, style, spin)` is followed
by `0x0010E098(rider, 1, ·)`.

### Transfer `0x001161D0`

Acts only when input ≠ 0, the style is 1 or 2, and (motion ≠ 0 or dot(v, rider `+0x3A0`) ≥ 0). It plays
semantic 24 (input > 0) or 32, sets `+0x330` = 1/2 and requests control 1. The rest of the transfer path
(control 1 `0x0012FC80`, landing semantics 26/34) was not traced.

### Jump, release and leaving

- `0x001162C8` is a crouch request, not an upper-body action. It checks the `+0x360` held/pressed gate and
  requests control 2 through `0x0011FEC8` at `0x00116344` (inside `0x001162C8`). That request runs control 7's
  exit `0x00132048`, so the balance target goes to 0 on the jump tick (PS2).
- The motion-1 post that follows a jump release is `0x00139C88`.
- On an air release, control 2 (`0x0012E9B8`) resets the default root when `+0x328` is 3 or 4: anim `+0x30` =
  `0x004FF130`, anim `+0x40` = (0,0,sin −0, cos −0) about `0x004FF160` (`0x0012EA4C..0x0012EAC0`). This happens
  before `0x0012EE30` plays the release clip. Afterwards `+0x328` is cleared (`0x0012EAD8`). Without this, a
  later crash would be rotated by the old style: `0x0010EB30` rotates the crash root by the style (PS2).

## Rail animation

### Semantics

| Semantics | Class | Driver kind | Completion | Notes |
|---|---|---|---|---|
| 18, 19, 20 | 15 | 5 | 0 | rail cycles; channel 2, blend 0.23 s, no first/end fade |
| 68, 69, 70 | 10 | 0 | 6 | air entries `L_RS_NORMAL`, `L_RSBS_NORMAL`, `L_RSFS_NORMAL`; blend 0.10 s |
| 49..54 | 14 | - | 6 | rail spins |
| 26, 34 | 10 | - | - | transfer clips played on attach with `+0x330` set (24/32 are the launch semantics; their row is not given) |
| 40, 45 | - | 9 | - | half-pipe balance |
| 213..244 | 21 | 1, 2 or 10 | 8 on OUTOF | rail Uber (below) |

"-" means the source does not give the value. The state table is `0x00446990` (driver kind at `+4`,
completion kind at `+8`).

Ordinary grinds have no INTO/OUTOF/LAND clips. The attach plays the cycle directly through `0x001326C8` (blend
−1, which means the state table's 0.23 s crossfade), or one of the landings 68/69/70 when the attach comes
from air controls 4/5.

### Entry picker `0x001326C8`

| Style (`+0x328`) | grounded (a1 = 0) | airborne (a1 ≠ 0) |
|---|---|---|
| 1, 2 | 18 | 68 `L_RS_NORMAL` |
| 3 | 19 | 70 `L_RSFS_NORMAL` |
| 4 | 20 | 69 `L_RSBS_NORMAL` |

Callers: the attach `0x00106848` (a1 = its airborne flag), control 3 `0x0012E778`, the control-5 path
`0x001304E0`, and the control-12 finish. The fourth argument of its `0x003128E8` call is 0 (unconfirmed).

Style 2 has no mirror or root change of its own: it uses semantic 18 like style 1, the balance sign flips
through `+0x320`, and the spin table sets the root when the style changes.

### Driver and completion switches

`0x001036A0` switches on the state table's driver kind through `0x00456950` (16 cases, `0x1C` bytes apart).
Rail-relevant cases: kind 5 → `0x00104238`, kind 9 → `0x00104660`, kind 10 → `0x001042E0`.

`0x00103918` switches on the completion kind through `0x00456990` (11 cases). The result is written into the
animator's requested-semantic slot for that channel:

| Kind | Handler | Action |
|---|---|---|
| 0 | `0x00104CA0` | remove (semantic 438) |
| 1 | `0x00104A40` | replace → 287 |
| 2 | `0x00104A60` | keep when the semantic is outside table `0x004569E0`, else replace |
| 3 | `0x00104B78` | replace → 5 |
| 4 | `0x00104C18` | play → 5 |
| 5 | `0x00104B48` | play |
| 6 | `0x00104C38` | play 20 after 69, 19 after 70, else 18, through `0x00312BD0`; the finished clip stays and fades out |
| 7 | `0x00104B98` | replace → 3 (`0x00312B18(..., 3)`) |
| 8 | `0x00104BB8` | replace → 19 |
| 9 | `0x00104BD8` | play |
| 10 | `0x00104C80` | play → 434 |

"Replace" is `0x00312B18`, "play" is `0x00312BD0`. Kind 6 covers the air entries 68/69/70 and the spins 49..54.
It is a play, not a replacement: the finished entry clip keeps fading out under the new cycle (PS2).

### Kind 5: rail cycle `0x00104238` (drives `0x00103CC8`)

```
rider  = animator+0x60
amount = rider+0x238 (balance current); if rider+0x320: amount = -amount
18   -> negative RS_BAL_R_CYC,   centre RS_FWD_CYC,   positive RS_BAL_L_CYC
19   -> negative RSFS_BAL_R_CYC, centre RSFS_FWD_CYC, positive RSFS_BAL_L_CYC
else -> negative RSBS_BAL_R_CYC, centre RSBS_FWD_CYC, positive RSBS_BAL_L_CYC
0x00103CC8(animator, sequencer, sequence, timeScale, amount, negative, centre, positive)
```

`0x00103CC8` each tick:

- slot 0 ← centre (`0x00313C50`);
- slot 1 ← positive with side weight = amount when amount > 0, else negative with side weight = −amount (so zero
  balance gives −0.0);
- slot 0 weight = 1 − side; slot 0 loops;
- slot 0's clock advances by rate·sequenceRate·(timeScale/60) through `0x003135B0` (wraps, sets seq `+0xC0`);
- slot 1's time = slot0.time / slot0.duration × slot1.duration (`0x00313CF0`, with seek);
- `0x00313800` steps the fade, and `0x003145F8` removes the sequence when a stop fade completes.

The balance clips are weight blends that loop in phase with the centre cycle. The driver has no thresholds; the
shaping is all in the `+0x238` triplet.

### Kinds 9 and 10: seek by magnitude (`0x00103BE0`)

- Kind 10 (`0x001042E0`, the Uber `RSFS_GRINDn_BAL_L` states): semantic 218 → BAL_L/BAL_R of GRIND1, 226 → GRIND2,
  234 → GRIND3, otherwise GRIND4. amount = rider `+0x238`, not negated by `+0x320`.
- Kind 9 (`0x00104660`): semantic 45 → `HPHS_BAL_THROUGH`/`_REFLECT`, otherwise the HPTS pair; amount = rider
  `+0x244`.
- `0x00103BE0`: amount < 0 → slot 0 = the second clip (BAL_R) at −amount·duration, otherwise the first clip
  (BAL_L) at amount·duration. The clock does not advance; only the fade steps, and a finished stop fade removes
  the sequence.

### Animation primitives

| Address | Role |
|---|---|
| `0x003128E8` (`cRiderAnimBase_play`) | play a semantic (blend −1 = state-table blend) |
| `0x00312B18` | replace: `0x003145F8` remove, `0x003128E8(anim, semantic, −1, 0)`, copy `+0x94`/`+0x98`, `0x00313A10` if `+0x9C` ≠ 0; returns the semantic |
| `0x00312BD0` | play keeping the old clip: `0x00144670` moves bit 63 from `+0xB0` to `+0xB8`, then `0x003128E8` with the state blend |
| `0x00312AA0` | current semantic on a channel |
| `0x00312AE8(anim, 2)` | the primary channel-2 sequence is complete (`+0xC0`) |
| `0x00311AE8` | current class |
| `0x001446A0(seq+0xB0, bit)` | event/flag bit test |
| `0x00311E88(anim, channel, time)` | fade a channel: `0x00314718` removes marker 63, `0x003146D0` fades the list, then writes 438 into the requested slot (`0x00311EE0`) |
| `0x00313C50` | slot assign: `+4` clip, `+0x10` duration = (u16 frames − 1)/30; time, rate, weight, enabled and loop are set only when `+0x18` was 0; seq `+0xC4` seek |
| `0x00313CF0` / `0x00313D28` / `0x00313D40` | set slot time (with seek) / weight / loop |

### Clip leaves and bank indices (PS2, read from a savestate)

Packed clip id = bank index << 8.

| Leaves | Clips | Bank indices |
|---|---|---|
| 63, 64, 65 | `RS_FWD_CYC`, `RS_BAL_L_CYC`, `RS_BAL_R_CYC` | 210, 211, 212 |
| 66, 67, 68 | `RSFS_FWD_CYC`, `RSFS_BAL_L_CYC`, `RSFS_BAL_R_CYC` | 213, 214, 215 |
| 69, 70, 71 | `RSBS_FWD_CYC`, `RSBS_BAL_L_CYC`, `RSBS_BAL_R_CYC` | 216, 217, 218 |
| 72..77 | `RSREG_INTO_FS`, `RSREG_INTO_BS`, `RSFS_INTO_REG`, `RSFAKIE_INTO_FS`, `RSFAKIE_INTO_BS`, `RSBS_INTO_REG` | 219..224 |
| 90, 91, 92 | `L_RS_NORMAL`, `L_RSBS_NORMAL`, `L_RSFS_NORMAL` | 157, 158, 159 |
| 346, 347 / 352, 353 | HPTS pair / `HPHS_BAL_THROUGH`, `HPHS_BAL_REFLECT` | 384, 385 / 390, 391 |
| 357..365 | GRIND1 family | 347..353, 355 (LAND), 354 (OUTOF) |
| 366..374 | GRIND2 family | 356..362, 364, 363 |
| 375..383 | GRIND3 family | 365..371, 373, 372 |
| 384..392 | GRIND4 family | 374..380, 382, 381 |

In every GRINDn group, LAND and OUTOF swap their bank order. Within a group, BAL_L and BAL_R are leaves 362/363
(GRIND1), 371/372, 380/381 and 389/390.

## Rail Uber (control 12)

### Input

- `DATA/CONFIG/INPUT.MAP` defines UberGrind1..4 as exclusive held expressions on L1, L2, R1 and R2. Combined
  shoulder buttons do not form another identity.
- `0x00127848` queries mapped actions 27..30 and returns 0..3, or −1.
- `0x00127998` packs the command. Control 7 carries the identity in word0 bits 17..24. Control 12 carries it in
  bits 15..22 (packed at `0x00127FEC..0x00127FF8`), i.e. `(int8)((cmd << 9) >> 24)`. In control 12, bits 13/14
  feed the boost handler `0x00114130`.
- The trick-name formatter names the four Ubers Handstand, Edge Grind, Butt Stand and Foot Surf. Which identity
  gets which name is not confirmed.

### Hand-off `0x00132620` (from control 7)

```
if identity == -1: control7.lastIdentity = -1; return 0
if rider+0x2F0 > 0 and (rider+0xB2C & 2):
    owner+0x394 = identity; request control 12; return 1     // lastIdentity not updated
if identity != control7.lastIdentity:
    call 0x00299B70 once, then lastIdentity = identity
return 0
```

The animation notes describe the ineligible case as a trick-naming update through `0x0028B180`/`0x00299B70`.
Both functions are in the sound code, so it is probably an audio cue (unconfirmed).

### Records `0x0045A038`

Four records, stride `0x24`, indexed by identity 0..3. Each has eight u32 semantics and a tier.

| `+0x00` | `+0x04` | `+0x08` | `+0x0C` | `+0x10` | `+0x14` | `+0x18` | `+0x1C` | `+0x20` |
|---|---|---|---|---|---|---|---|---|
| entry from style 4 (`RSBS_INTO_FS_GRINDn`) | from 3 (`RSFS_INTO_FS_GRINDn`) | from 2 (`RSFAKIE_INTO_FS_GRINDn`) | from 1 (`RSREG_INTO_FS_GRINDn`) | `RSFS_GRINDn_CYC` | `RSFS_GRINDn_BAL_L` | `RSFS_GRINDn_LAND` | `RSFS_OUTOF_GRINDn` | tier n |
| 213+8k, kind 1 | 214+8k | 215+8k | 216+8k | 217+8k, kind 2 (loop) | 218+8k, kind 10 | 219+8k, kind 1 | 220+8k, completion 8 | k+1 |

### Enter `0x00136268`

- By style:
  - 4: root (anim `+0x30` = `0x004FF130`, anim `+0x40` = (0, 0, sin π/4, cos π/4) about `0x004FF160`), play
    `+0x00`;
  - 3: play `+0x04` (no root);
  - 2: rider `+0x320` = 0, anim `+0x18` = 0, root as above, play `+0x08`;
  - 1: root, play `+0x0C`.
- `0x00119938(rider+0x790, tier, style)` → `0x0010E098(rider, 1, ·)`.
- rider `+0x328` = 3, phase = 0, `0x00116930(rider)` (empty).
- `0x00311E88(anim, 1, 0.33)` and `0x00311E88(anim, 0, 0.33)` fade out channels 1 and 0 (the upper-body and
  head channels) over 0.33.

### Update `0x00136508`

```
0x00116120 (recovery)
if 0x00106848(rider) attached this tick:            // re-attach during the trick
    if phase == 1: play +0x18 (LAND)
    return
0x00114130(boost bits), 0x00113F38(bits 23..28 * 1/31), 0x00113F88(0, 0)
phase 0: +0x240 = 0, +0x23C = 3.5/60
         if 0x00312AE8(anim, 2): play +0x10 (CYC), seq+0x90 = 1, phase = 1
phase 1: if command identity != held identity or motion (0x0011FE98) == 0:
             play +0x1C (OUTOF), seq+0x90 = 1, phase = 2
         else if 0x00312AA0 != LAND or the primary sequence is complete:
             motion 4: +0x23C = 3.5/60, +0x240 = rail balance (owner+0xC8, raw, no 1.2 factor)
             otherwise: balance target 0
             want = |rider+0x238| < 0.1 ? CYC : BAL_L
             if want != current: play want
phase 2: +0x240 = 0, +0x23C = 3.5/60
         if class (0x00311AE8) == 21 and not complete and event bit 0 not set: return
         motion 4: 0x001326C8(control7, 0) (style is now 3, so cycle 19); request control 7
         otherwise: 0x00115640 (stance restore); request control 5 (motion 1) or 0
         award = 0x00119958(rider+0x790, style); 0x0010E098(rider, 1, award)   // 0x00136888..0x00136890
         if rider+0x2F4 < 10: rider+0x2F4 += 1; when it reaches 10: rider+0x2F0 = 60.0
```

Completion 8 on the OUTOF clip replaces it with semantic 19 on its own, so phase 2 usually finishes through
"class ≠ 21" one tick later unless the clip's event marker (bit 0) fires first. Control 12 can outlast the
rail: its phase-1 and phase-2 branches handle motion ≠ 4, and the exit `0x00111624` does nothing.

## Rail scoring

### Score object fields (`rider+0x790`)

| Offset | Meaning |
|---|---|
| `+0x04` | seeded on commit/reset (meaning not given) |
| `+0x10` | flag word (includes the flag seeded by `0x00119D40`) |
| `+0x14` | pending reward |
| `+0x1C` | inverted-riding accumulator |
| `+0x20` | style |
| `+0x24` | rail distance (cm); −1 when idle (reset by `0x00117838`) |
| `+0x2C` | manual timer; −1 when idle (reset by `0x00117838`) |
| `+0x30` | air seconds |
| `+0x54` / `+0x74` | Uber count fields |
| `+0x5C` | active Uber |
| `+0x6C` | active seconds (timer; negative = inactive) |
| `+0x70` | active flag |
| `+0xA4` | timeout (survives resets) |
| `+0x1C4` | rider multiplier (survives resets) |

### Functions

- `0x00119D40`: entry commit, used by attaches that do not come from motion 1. It commits before resetting.
  A nonzero incoming style adds 0.13 to an already positive pending reward before the commit. It saves `+0x70` before the commit,
  resets through `0x00117838`, seeds stance, `+0x04`, style and flags, starts `+0x24`/`+0x2C` where
  applicable, and restores `+0x70`, `+0x5C` and `+0x6C`.
- `0x00119E38`: takeoff commit, used when leaving the rail by a jump or by losing it. The call site is not
  identified here.
- `0x0010E910`: the air-to-rail case of the attach (not described further).
- `0x0010E098(rider, 1, value)`: meter award.
- `0x00119918` → `0x00119898`: rotation update. It removes the previous absolute spin contribution from the
  pending reward, adds the new one, and updates `+0x20`. The immediate boost return is 0.
- Distance block `0x00117D74..0x00117DFC` inside `0x00117C28`:
  - `+0x24` advances by speed (cm/s) × scaled 1/60;
  - `+0x14` accrues distance × 5e-5;
  - when the board's up vector has negative Z, `+0x1C` accrues distance × 2e-4;
  - the stage ends at `0x00117E00`/`0x00117E04`.
- Distance thresholds, table `0x00459F68`: 11 float pairs (distance cm, points), from (10000, 1000) to
  (30000, 50000) in 2000 cm steps, ended by −1. At most one threshold is processed per tick, and it raises score
  event 29. `0x00119210` clears events 28..32 in that order and uses a 1.5 s display duration.
- Inverted bonus: `0x00117908` converts `+0x1C` × 10000 to a rounded multiple of 10. `0x0011A458` (inside the
  commit `0x0011A228`) adds it after the normal repeat division. It gets no trick or rider multiplier and does
  not raise the meter award.
- Uber boundaries:
  - `0x00119938` initializes `+0x6C`, `+0x70`, `+0x5C` and the scoring style without resetting accumulated
    points.
  - `0x00119958` increments `+0x54`/`+0x74` before `0x0011A228`, resets through `0x00117838`, then restores
    `+0x24`, `+0x30` and the new style.
- Active-time accrual `0x00117E58..0x00117E84` inside `0x00117C28`: if `+0x6C` ≥ 0, `+0x6C` += dt and `+0x14`
  += dt × 0.05 (0.04999999701976776). A negative timer branches to `0x00117E8C`; the active path reaches
  `0x00117E88`.

## Constants

| Value | Bits | Use |
|---|---|---|
| 555.5555 | `440AE38E` | attach speed floor; f20 speed switch |
| 277.7778 | `438AE38E` | detach push |
| 0.1 | `3DCCCCCD` | attach v.z factor; Uber CYC/BAL threshold (`0x0049BE28`, gp−0x72C8) |
| π/2, 1.5707965 | `3FC90FDB`, `3FC90FDC` | spin step, style rotations |
| π | `40490FDB` | stance flip |
| 150°, ±30° | `40278D37`, `3F060A93`/`BF060A93` | style bins |
| π/4 | `3F490FDC`, `3F490FDB` | heading clamp (`...DC`); root quaternions (`...DB`, at `0x0049BE08`..`0x0049BE10`, gp−0x72E8..−0x72E0) |
| 0.0009 | `3A6BEDFB` | f20 speed factor |
| 0.6 | `3F19999A` | entry time window |
| 0.001 | `3A83126F` | minimum speed / parallel test |
| −0.2 | `BE4CCCCD` | behind tolerance (`0x0049B2BC`) |
| 0.92 | `3F6B851F` | near-vertical rail threshold |
| 0.3, 1.8 | `3E99999A`, `3FE66666` | imbalance by style |
| 1.650076 | `3FD335B2` | stat divisor factor |
| 1/70 | `3C6A0EA1` | balance scale, styles 3/4 |
| 20°, 40° | `3EB2B8C4`, `3F32B8C4` | lean/heading clamps |
| 1e10 | `501502F9` | `0x00121AA0` limit |
| 1000 | `447A0000` | vertical correction clamp factor (`0x0013B1D8` inside `0x0013AF28`) |
| ±2450 | `45192000`/`C5192000` | boost acceleration |
| −980 | `C4750000` | gravity, runtime global `0x004A5E50` (gp+0x2D60, `.bss`) |
| 1/60 | `3C888889` | tick (`0x0049B180`/`0x0049B184`, gp−0x7F70/−0x7F6C) |
| 1/15 | `3D888889` | balance/animation-turn rates |
| 1/31 | `3D042108` | command axis scale (`0x0049BE18`, gp−0x72D8) |
| 0.05 | `3D4CCCCE` | tolerance rate |
| 1.2 | `3F99999A` | control-7 balance gain |
| 3.5/60 | `3D6EEEF0` | Uber balance rate (`0x0049BE1C`..`0x0049BE2C`, gp−0x72D4..−0x72C4 except −0x72C8) |
| 0.33 | `3EA8F5C3` | Uber channel fade (`0x0049BE14`, gp−0x72DC) |
| 60.0 | `42700000` | `+0x2F0` value set when the Uber counter reaches 10 |
| −1 | `BF800000` | "use state-table blend" |
| 1/30 | `3D088889` | balance scale for styles 1/2; steer rate on loss; clip duration factor (`0x0049FECC`, gp−0x3224) |
| 0.381966, 0.618034, 0.0005 | `3EC3910C`, `3F1E377A`, `3A03126F` | golden-section search |
| 5e-5, 2e-4 | `3851B717`, `3951B717` | distance and inverted accrual |

Vector constants in `.bss`, initialized by `0x00320550`: zero `0x004FF120`, root translation `0x004FF130`
(0,0,0,1), Z axis `0x004FF160` (0,0,1,0).

## Not traced

- The transfer path after `0x001161D0` (control 1, semantics 24/26/32/34, attaches with `+0x330` set).
- Control 11's own behaviour (`0x001328B0`/`0x00132A30`), beyond its half-pipe balance triplet.
- Reset-onto-rail `0x0013AA48`.
- The rail motion exit `0x0013C5A0`.
- The object-rail callbacks (instance virtuals `+0x150..+0x174`).
- The code that sets descriptor bit 0 and fills the record surface id at load.
