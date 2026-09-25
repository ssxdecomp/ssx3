# World, camera and render object layouts

Partial layouts of the world, camera and render objects of SSX 3 (PS2, SLUS_207.72), gathered from reading the code and checking the running game. Offsets are byte offsets from the start of the object; a type is given only where it is known, and gaps between rows are simply unmapped. gp-relative globals are written as absolute addresses (gp = 0x004A30F0). **(PS2)** marks fields whose meaning was checked against the game running on a PS2 emulator; **(unconfirmed)** marks inferences. In the tables, the Evidence column reads "PS2" for checked fields, is blank for static reading of the code, and reads "unconfirmed" for inferences.

The game object G, the game world object W = *(G+0x84), the race object at W+0x0C, profile inventory rows, the game mode settings block and the audio file formats are documented in the companion file "Game, front-end and audio object layouts".

## Renderer / render context object

Vtable 0x00493260; pointer at gp-0x854 = 0x004A289C. The vtable entry at +0x140 holds 0x00377950, and slot +0x22C is 0x003954D0, which copies the rider lighting bank in.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xE84 | u32[3] | Current render material state words, set by the terrain builders and converted by 0x00363C20 (see "Render material state words") | |
| +0xF50 | | Renderer-owned texture handle array (the HUD glow takes its handle from here) | |
| +0xFAC | ptr | Texture 'exlm' (relationship icon) | |
| +0xFFC | ptr | Texture 'beam' (white with triangular alpha across S) | |
| +0x1024 | | Texture handle of the glow halo 'shal' (FX 53, light-glow classes 0x10/0x40) | |
| +0x1028 | | Texture handle of the glow halo 'mhal' (FX 54, class 0x20) | |
| +0x13E4 | ptr | View matrix stack head (push 0x003956E8, pop 0x00395730, getter 0x00395C68). Points to the camera view matrix during the human rider draw and to identity at the end of the frame; the light-glow projection reads its right/up columns | PS2 |
| +0x18F0 | ptr | Render queue (sorted render records, including terrain) | PS2 |
| +0x18F4 | ptr | Texture descriptor table used to resolve material texture handles: descriptor = *(table + handle*4 + 8) | |
| +0x5860 | float | Normalised projection x scale copy (y copy at +0x5874), scaled by the widescreen factors | |
| +0x5930 | mat4 | Per-view projection matrix (copied from +0x6AF0 at 0x00386688). Its x/y scales are the GS projection scales: 272.65/318.09 px at 512x448 in 4:3, stored x16 (3271.82/-3817.13 in 16:9 mode) | PS2 |
| +0x5A40 | int | Depth buffer format (0x31 = PSMZ24 selects the 24-bit reverse-depth range) | PS2 |
| +0x5A80 | | Buffer block base: value <<5 gives the GS block of the Z buffer used for the glare levels (0xE0 -> 7168); +0x5A84 was 0. Neighbouring words not traced | PS2 |
| +0x6AF0 | mat4 | Active projection matrix before the per-view copy | |
| +0x6B94 | int | Widescreen mode (0 off, 1 16:9, 2 anamorphic) | PS2 |
| +0x6B98 | float | 3D viewport top fraction (0.125 in mode 1) | PS2 |
| +0x6B9C | float | 3D viewport height fraction (0.75 in mode 1) | PS2 |
| +0x6BA0 | float | Projection x scale factor (0.75 in modes 1 and 2) | PS2 |
| +0x6BA4 | float | Projection y scale factor (0.75 in mode 1) | PS2 |
| +0x6BB0 | float[40] | Rider lighting bank (irradiance coefficients, 160 bytes) copied in by 0x003954D0; used by the rider VU program, scaled by 255 on VU1 | PS2 |
| +0x6C64 | | Per-view fog parameters: near, far, equation, density, then alpha/RGB (copied by 0x0036ABA0) | PS2 |
| +0x6CA4 | | ScreenTint parameters (copied in by 0x00390458) | |
| +0x6CD4 | float[7] | Glare parameters, 7 floats per view (stride 0x1C), copied from gp+0x12E4 = 0x004A43D4 by 0x0036C740; block +0x14/+0x18 (BT2/BT3, x127) also gate the pass. Snow Jam: 1,1,1,1,1,0,0 | PS2 |
| +0x6D20 | | Active projection parameters (near 0 / far 1 at the end of the frame) | PS2 |

## DEFAULT_3 chase camera algorithm

0x390 bytes; vtable slot +0x28 = 0x00176E10. Algorithm type at +0xC. An instance is embedded in the outer camera at +0xC0 (the compositor).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | float | Field of view (ctor pi/4); the half horizontal angle of a 4:3 view (e.g. 0.7539 = 0.9599*pi/4) | PS2 |
| +0x4 | float | Near plane (ctor 10) | PS2 |
| +0x8 | float | Far plane (ctor 30000) | PS2 |
| +0xC | int | Algorithm type (e.g. 0x44 POST_RACE_1; DEFAULT_2/3/4 variants) | |
| +0x20 | vec4 | Look-at point; the compositor averages node look-ats from here | PS2 |
| +0x40 | vec4 | Eye quad (set-target seeds (0,0,0,1)) | PS2 |
| +0x50 | float | Yaw | PS2 |
| +0x54 | float | Pitch | PS2 |
| +0x60 | vec4 | Output eye (w=1); the compositor averages node eyes from here | PS2 |
| +0x80 | vec4 | Filtered travel direction (not unit); seed normalize(fwd*559.744 - Z*300) | PS2 |
| +0xA0 | vec4 | Copy of the head position | PS2 |
| +0xB0 | vec4 | Mode-5 saved eye offset (captured during motion mode 5) | PS2 |
| +0xC0 | vec4 | Mode-4 pull-behind filter state | PS2 |
| +0xF0 | vec4 | Z x forward vector (written at init only) | PS2 |
| +0x100 | vec4 | Lag-filtered horizontal velocity (seed: velocity with z=0) | PS2 |
| +0x110 | vec4 block | Wall-launch swing camera vectors (+0x110..+0x180); set-target zeroes 0x170 bytes from here | PS2 |
| +0x1A0 | vec4 | Slow-speed lock view vector (seed fwd*250) | PS2 |
| +0x1B0 | vec4 | Last velocity; set-target stores the rider forward vector itself (not fwd*250) | PS2 |
| +0x1C0 | vec4 | Last raw velocity (seed fwd*2) | PS2 |
| +0x1D0 | float | Follow distance (200, set in the ctor only) | PS2 |
| +0x1D4 | float | Eye vertical offset (seed 61.687962) | PS2 |
| +0x1D8 | float | Filtered pitch (0, ctor only) | PS2 |
| +0x1DC | float | FOV scale (seed 1) | PS2 |
| +0x1E0 | float | Mode-5 blend timer (seed 10) | PS2 |
| +0x1E4 | float | Look-at height (seed 0) | PS2 |
| +0x1E8 | float | Boost bump | PS2 |
| +0x1EC | float | Last boost level | PS2 |
| +0x1F4 | float block | Jump camera clocks, gains and offsets (+0x1F4..+0x228), including landing decay 0.92 and take-off ramp 1 | PS2 |
| +0x22C | float block | Swing timers and angle (+0x22C..+0x244) | PS2 |
| +0x248 | float | Slow-lock blend (seed 0.5) | PS2 |
| +0x2B8 | float | Extra eye height (mode-5 hold) | PS2 |
| +0x2C0 | int | Mode-5 frame counter (seed 5000) | PS2 |
| +0x2C4 | int | Take-off countdown (seed -1; 15 frames on take-off) | PS2 |
| +0x2CC | int | Last airborne global tick (from 0x001298C8) | PS2 |
| +0x2D0 | int | Wall-launch flag | PS2 |
| +0x2D4 | int | Airborne latch | PS2 |
| +0x2D8 | int | Swing initialised flag | PS2 |
| +0x2E0 | int | Jump camera phase-B flag (seed 0) | PS2 |
| +0x2E4 | int | Jump camera landed flag (seed 1) | PS2 |
| +0x2E8 | int | Jump camera phase-A flag (seed 0) | PS2 |
| +0x2F0 | int | Reset pending (set by the snap guard 0x00168150; forces a set-target before the next update) | PS2 |
| +0x300 | int | Slow-speed lock state (0 in, 2 locked, 1 out, 3 idle; seed 1) | PS2 |
| +0x304 | spline | Jump spline, look-at, phase B (cCSICubicSpline, 0xC bytes; spline flag words compared on bits 0..26) | PS2 |
| +0x310 | spline | Jump spline, eye, phase B | PS2 |
| +0x31C | spline | Jump spline, look-at, phase A | PS2 |
| +0x328 | spline | Jump spline, eye, phase A | PS2 |
| +0x334 | spline | Wall-launch swing ease spline | PS2 |
| +0x340 | float[5] | PID ring X (alignment angle history) | PS2 |
| +0x354 | float[5] | PID ring Y | PS2 |
| +0x368 | float[5] | PID ring E | PS2 |
| +0x37C | int | PID ring index | PS2 |
| +0x380 | float | PID Kp (about 0.0113945) | PS2 |
| +0x384 | float | PID Ki (0) | PS2 |
| +0x388 | float | PID Kd (about 0.00127851) | PS2 |

## Outer camera object

The gameplay camera. Embedded in the camera director at +0x10 and updated by 0x0015E030; holds the compositor at +0xC0. Its vtable pointer is at +0x90. The notes also call it the outer gameplay camera, outer camera Y and camera object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | float | Output FOV (near at +0x4, far at +0x8) | PS2 |
| +0xC | float | FOV limit pi/4 | PS2 |
| +0x10 | float | Near limit 30 | PS2 |
| +0x14 | float | Far maximum 30000 | PS2 |
| +0x20 | vec4 | Final eye position after clearance lift and re-projection. X/Y are also the world painter sampling coordinates; the camera splash reads it as the camera position | PS2 |
| +0x30 | quat | Camera orientation quaternion (converted to the view matrix at 0x0015E968) | |
| +0x40 | mat4 | Final view matrix; copied to the renderer through renderer vtable slot +0x114; equals the draw-time view seen by rider lighting | PS2 |
| +0x90 | ptr | Vtable pointer used by the camera pass 0x0022E840; slot +0x1C is the camera update 0x0015DF98 | |
| +0xC0 | object | Compositor sub-object (DEFAULT_3 node data, also described as an embedded DEFAULT_3 camera algorithm); see "Camera compositor" | PS2 |
| +0xE0 | vec4 | Compositor look-at | PS2 |
| +0x100 | vec4 | Compositor eye | PS2 |
| +0x314 | float block | Shake random-walk state (+0x314..+0x374 and +0x3AC; = compositor +0x254..+0x2B4, +0x2EC) | PS2 |
| +0x450 | vec4 | Shake request (+0x450..+0x45C) | PS2 |
| +0x460 | float | Accumulated clearance lift (x0.97 decay per tick; 0 on restart) | PS2 |
| +0x470 | vec4 | Last clearance probe normal | PS2 |
| +0x490 | | Line-of-sight occlusion state (with +0x4A0/+0x4A4; override-only branch) | |
| +0x4A4 | int | Occlusion-related state set to 1 by the restart 0x0015DB58 | |

## Camera compositor

Sub-object at outer camera +0xC0 (DEFAULT_3 node data). Offsets are relative to the compositor; add 0xC0 for the outer camera offset.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x254 | float block | Shake state (+0x254..+0x2B4) | PS2 |
| +0x278 | float[3] | Shake set-1 timers (+0x278..+0x280), the only ones advanced by 0x00165938 | PS2 |
| +0x2A8 | float[3] | Shake second-octave timers (+0x2A8..+0x2B0); never advanced, inert | PS2 |
| +0x2EC | float | Shake requested amount (stored in the fade branch) | PS2 |

## Camera splash object

Vtable 0x00488230; one per camera (the race game object keeps an array of them at +0x68, unconfirmed). Drops are 0x3C bytes, ice crystals 0x4C bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | int | Camera index; the update returns when it is >= the camera count | |
| +0x14 | int | Live drop count | |
| +0x18 | int | Live crystal count (per-tick crystal draw f = u * crystals / 24) | |
| +0x1C | | Drop array, 0x3C bytes per drop (updated by 0x002F2810); dead drops are replaced by the last one | |
| +0x724 | | Ice crystal array, 0x4C bytes per crystal (updated by 0x002F3030); crystal +0 is its drop-spawn count; dead crystals are replaced by the last one | |
| +0x100C | int | Previous-position-valid flag; on the first update speed is 0 and the flag is set | |
| +0x1010 | vec | Previous camera position (copied from camera +0x20 each update) | |
| +0x1020 | float | Camera speed in km/h: abs(p - prev) * 59.999996 * 0.036; above 1000 it calls vtable +0x70 (reset) and uses 0 | |
| +0x1024 | float | Pending spawn count; spawn 0x002F3810 takes n = trunc(pending) and subtracts it | |
| +0x1028 | float | Current snowfall amount, set by 0x002F4330 | |

## Camera director

Vtable 0x0045B908. The director chain is reached as *(*(W+0x84)+0x4)+0xA0 (W = game world object).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | object | Embedded outer camera (updated by 0x0015E030) | |
| +0x18 | int | Type of the newly inserted algorithm | PS2 |
| +0x2C | int | Override request type (0x5D during replay lock) | PS2 |

## Camera director algorithm node

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xC | float | Smoothstep-smoothed weight 3w^2-2w^3 (capped at 1) | PS2 |

## Viewport object

One per device, held in the array at game world object W+0x5C.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x78 | int | Screen effect active (1 = reset fade running) | |
| +0xA8 | ptr | Camera director used for the second placement camera cut | |

## View camera object (sun placement)

The per-view camera read by the sun update. It may be the view camera held at world render owner +0x10.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x58 | float | Far distance (300 m) used for sun placement | |

## FE camera block

Front-end preview camera; it keeps its view matrix at +0x40 like the outer camera and may share that layout.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x40 | matrix | View matrix used for FE preview lighting | PS2 |

## World instance

A placed world instance (static or entity-driven); also called stage instance and world model instance in the notes. +0xC links the attached entity and +0x88 its loaded kind16 collision descriptor.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | ptr | Spatial instance link (with +0x4) to other instance structures; not an entity or vtable pointer | PS2 |
| +0x8 | u32 | Runtime flags: 0x1/0x2 static drawn (static draw needs (flags & 3) == 3), 0x4 dynamic draw, 0x20 static route, 0x40 entity route, 0x100 renderer list, 0x200 renderer bookkeeping, 0x2000 suppresses contact copy/audio; high half = authored flags. Bit 0 clear on never-drawn helpers (unconfirmed) | PS2 |
| +0xC | ptr | Attached entity (set-piece/script entity; 0 when none), set by base construction 0x0034FB00. 0x00104E70 calls its vtable +0x154, 0x00121818 its vtable +0x144 | PS2 |
| +0x10 | mat4 | World matrix (row-major, row 3 = translation, model scale not included): root of the static collision hierarchy and teleport destination. Entity instances use the entity base matrix instead (e.g. RollerModifier +0x240); MultiSpline writes each clone's car matrix here | PS2 |
| +0x60 | vec3 | Bounds min (inline box, used for instances with flag 0x20); max at +0x6C | PS2 |
| +0x6C | vec3 | Bounds max | PS2 |
| +0x78 | u32 | Resource id; stored in rider +0x5B8 by 0x00104E70; tie-break in 0x00336850 (lower first) | PS2 |
| +0x7D | u8 | Streaming chunk index (with +0x7E) checked by the static draw collector 0x0022A5A0 | |
| +0x88 | ptr | Instance collision descriptor in the loaded kind16 data | PS2 |

## World entity

Script or set-piece entity attached to a world instance (instance +0xC). Its vtable pointer is at +0xC and its node type at +0x10.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xC | ptr | Entity vtable pointer | |
| +0x10 | int | Entity node type (1 LiveComp, 8 Boost/one-way volume, 10 flag, 13 emitter, 16 node, 17 Object) | |
| +0x18 | ptr | Owning world instance | |
| +0x1C | ptr | Modifier/component container: slot +0 primary modifier (matrix via vtable +0x94), slot +4 UVScroll. Used by builtin 69 (0x00302490) and the RollerModifier forwarding | |
| +0x20 | int | Contact guard/cooldown ticks; contacts are rejected while positive. Builtin 87 sets int(60 * seconds); 0x00355770 sets clockRate/2 (30), 0x00355858 sets 30; 0x00356198 decrements | |
| +0x24 | float | Bounds radius: largest authored AABB corner distance from the instance translation (set at attach); used by 0x003568B0 | |

## World entity virtual table

Slots of the entity vtable (entity +0xC) as used by callers; offsets are byte offsets into the vtable.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x20 | vslot | Draw; empty for DeadNode, RestoreNode and type-16 nodes | |
| +0x144 | vslot | Called by 0x00121818 on an instance's entity | |
| +0x154 | vslot | Called by 0x00104E70 on an instance's entity | |
| +0x168 | vslot | Box getter used for flag-0x40 entities in the scope build | |
| +0x170 | vslot | Predicate tested by 0x0013AF28 to set rider +0x5AC | |

## Rail instance object virtual table

Virtual slots of instance rails; this may be the same entity vtable family as above. The range +0x150..+0x174 is otherwise unrecovered.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x158 | vslot | Slots +0x158/+0x15C receive -dv on an instance rail attach | |
| +0x188 | vslot | Binding getter (+0x188/+0x18C) used by the type-3 query; the surface is resolved through it | |

## RollerModifier

Vtable 0x0048F080; 0x2D0 bytes. Rigid-body modifier; its world matrix at +0x240 is used as the entity base matrix.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x20 | float | Timer in seconds: +1/60 per tick, 0 on rider re-contact; phase thresholds at 10, 11 and 16 s | PS2 |
| +0x30 | vec4 | Position | PS2 |
| +0x40 | quat | Orientation quaternion | PS2 |
| +0x50 | vec4 | Linear momentum | PS2 |
| +0x60 | vec4 | Angular momentum | PS2 |
| +0x70 | float | Inverse mass (script mass 1.0) | PS2 |
| +0x80 | mat | World inverse inertia (0x0035E248) | PS2 |
| +0xB0 | vec4 | Linear velocity | PS2 |
| +0xC0 | vec4 | Angular velocity | PS2 |
| +0xE0 | struct | Own sphere-tree collider (kind from 0x0032C508) | PS2 |
| +0x1A0 | struct | Copy of the hit node sphere-tree header: centre of mass, inertia, inverse inertia | PS2 |
| +0x220 | vec4 | Bounds minimum (maximum at +0x230); returned by vtable +0x64 | PS2 |
| +0x230 | vec4 | Bounds maximum | PS2 |
| +0x240 | mat4 | World matrix; used as the entity base matrix | PS2 |
| +0x280 | mat | Body inertia = header inverse inertia x 0.5 | PS2 |
| +0x2B0 | vec4 | Centre-of-mass offset | PS2 |
| +0x2C0 | struct | Terrain cell cache passed to 0x00336850 | PS2 |

## MultiSplineModifier

Vtable 0x0048F168.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xC | float | Rotation angle applied about the z axis after the car's Euler matrix | unconfirmed |

## ParentModifier

Vtable 0x0048F508.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x30 | vec | Child offset, rotated by the parent node matrix and added to its translation | |

## LiveComp entity

Vtable 0x00490B10 (entity node type 1).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4C | ptr | Per-node velocity table used by the LiveComp contact path (0x0034E798 / 0x0034E600) | |

## Surface parameter record

0xB0 bytes (44 words); 19 records in an array at *(W+0x44) (W = game world object). The notes also call it surface/material properties record, surface property record, terrain surface material record and snow surface parameter record; the offsets fit one 0xB0-byte layout.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | float | Cruise gravity (1300.85034 cm/s^2 observed) | PS2 |
| +0x10 | float | Contact distance threshold for passive takeoff; read from the cached old surface by the passive takeoff height/alignment code (0x0013ED28, 0x0013EE84) | |
| +0x14 | float | Powder depth parameter (with +0x18) | PS2 |
| +0x18 | float | Powder depth parameter; also the depth value kept from the old material during crash terrain correction | PS2 |
| +0x1C | float | Normal damping (5.005756855 observed) | PS2 |
| +0x28 | float | Heading response parameter (with +0x2C/+0x30/+0x34) | |
| +0x38 | float | Ground alignment rate multiplier; also read by passive takeoff height/alignment | |
| +0x44 | int | Hazard flag: nonzero makes 0x00105D98 request a reset (control 9 / motion 3) via 0x00116120. Also read by air alignment 0x00139A64, collision reaction classification and the ground reset path of 0x0013F178 | |
| +0x48 | | Wake target input (with +0x4C and +0x84) | |
| +0x4C | | Wake target input | |
| +0x50 | float | Cloudy emitter surface parameter (with +0x54) | |
| +0x54 | float | Cloudy emitter surface parameter | |
| +0x58 | int | SnowTrail enable gate | |
| +0x5C | float | Kicker buildup cap (2/3/4/5 on authored snow types) | |
| +0x6C | float | Rock spray emission chance | |
| +0x70 | float | SmallChunky chance scale | |
| +0x74 | float | LargeChunky chance scale | |
| +0x78 | | Unresolved: wake enable flag (wake notes) vs first of three wake velocity inputs +0x78/+0x7C/+0x80 to chunk emission (snow notes, unconfirmed) | |
| +0x84 | | Wake target input | |
| +0x88 | | Grind-chunk-on-rail flag (none on Snow Jam) | |
| +0x8C | | Spark flag: board sparks emit on surfaces with it set (metal surfaces 7, 8, 10, 16, 17, 18) | |
| +0x90 | | Slip curve | |

## Terrain patch

Terrain patch used by collision and rendering. Patches are listed per octree/scope node at node +0x24.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | s16 | Authored surface id; copied to query result +0x4C by 0x00335960 (0x0013D1B8 maps -1 or no contact to surface 0 in rider +0x438) | |
| +0xA | u16 | Flags: bit 0 collidable, 0x40 active (ORed in by world streaming while the track is active); 0x00335960 requires 0x41 | PS2 |
| +0xC | | Layer type word: three 3-bit layer types (bits 0..2 base, 3..5 light, 6..8 extra); e.g. 0x29 = base 1 + light 5, 0x1A9 adds type 6 (env map) | |
| +0x10 | | PS2 light-page UV used by the light layer | |
| +0x150 | u32 | Patch resource id (rid << 8 \| track); final tie-break in 0x00336850 | PS2 |
| +0x155 | u8 | Streaming chunk index (with +0x156) checked by the patch draw collector 0x0022A698 | |
| +0x156 | | Streaming chunk index read by the environment lighting (not a material RID) | unconfirmed |
| +0x158 | vec3 | Bounding box min (tested by 0x00332DB8) | PS2 |
| +0x164 | vec3 | Bounding box max | PS2 |
| +0x1A0 | u16[3] | Layer texture ids of the three layers (+0x1A0/+0x1A2/+0x1A4) | |

## Octree / scope node

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x24 | list | Terrain patch list of the node (scanned by 0x00332DB8) | PS2 |

## Terrain contact cache payload

Embedded at rider +0x864.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | ptr | Cached patch pointer | |
| +0x4 | u16 | Cached U cell | |
| +0x6 | u16 | Cached V cell | |
| +0x8 | int | Cached triangle half (1 first triangle, 0 second) | |
| +0xC | int | Query kind of the cached entry | |

## Collision query hit packet

Output of 0x00334888 / 0x00336850; 0x00336850 keeps the packet whose depth is closest to -1.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x20 | vec4 | Surface velocity of the hit object (subtracted from the rider velocity for the closing speed) | |
| +0x40 | float | Contact depth; 0x00104E70 returns it (-1 when empty) | |
| +0x48 | ptr | Prebuilt collider of the hit node | |
| +0x4C | int | Surface id of the hit (patch +0x8, copied by 0x00335960); third argument to 0x00105D98 | |
| +0x50 | ptr | Hit instance pointer | |

## Selected-contact packet

Contact with a moving set-piece object. It may be the same packet as the collision query hit packet (both hold the surface velocity at +0x20).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x20 | vec | Surface velocity of the contacted moving object at the contact point | |
| +0x30 | vec | Angular velocity of the contacted moving object | |

## Instance contact record

Built on the stack by 0x00105398 (sp+0x80) and copied to rider +0xA60.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | vec4 | Contact point | |
| +0x10 | vec4 | Normalized rider velocity direction (rider +0x1E0 via VRSQRT) | |
| +0x20 | vec4 | Contact normal after projection | |
| +0x30 | float | Closing speed = max(0, dot(-n, v - hit+0x20)) in the x lane; the y/z/w lanes are stale stack words | |

## Runtime sphere-tree collider object

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x2C | vec4 | Centre of mass (from header +0x1C) | |
| +0x38 | mat | Inertia (from header +0x28) | |
| +0x5C | mat | Inverse inertia (from header +0x4C) | |
| +0x90 | float | Collider scale; not copied by 0x00327CC8, so the scratch collider accumulates 1/instance-scale per processed node | |
| +0x94 | | Collider scratch state (with +0x9C), affected by patch visitation order | |

## Sphere-tree model header

Kind-12 collision resource.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1C | vec4 | Centre of mass; copied to runtime tree objects (+0x2C) and RollerModifier +0x1A0 | |
| +0x28 | mat | Inertia (runtime tree object +0x38) | |
| +0x4C | mat | Inverse inertia (runtime tree object +0x5C); RollerModifier body inertia is this x 0.5 | |

## Body collision query object

Used by 0x0032F650 / 0x003303F0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Query mode word; 0 for mode-1 and coarse queries (0x003303F0 stores 0), making 0x0032F8C0 return -1 instead of twice the broad radius | |
| +0x8 | int | Directional triangle-exclusion enable; 0 in mode-1 queries (no normal filter) | |

## Instance collision descriptor

SSB kind-16 entry after loading (pointed to by world instance +0x88).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | u32 | resource08: selects the authored handler row (e.g. rid 20 speed boost, rid 21 trick boost); kept raw, pickup reward linkage reads the row it selects | |
| +0xC | u32/ptr | Separate collision-mesh resource id (-1 when absent, e.g. boost pickups); replaced by a cache pointer at runtime | |

## Collision descriptor model-node record

12 bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | float | Restitution scalar (clamped 0..1 by 0x001057B8); 0 selects soft collision 0x00108388; nonzero with flag bit 0 marks a priority node; crashbag nodes use 1e30 (flags 3, surface -1) | |

## Nearby cache layer entry

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | int | Layer type: 1 static spline, 2 object rail, 3 sphere-tree/instance rail | |
| +0xC | ptr | Layer object passed to the type-2 query 0x0035C698 | |

## Rail spline record header

SSB kind 8; 48-byte header followed by 144-byte segments (record size = 48 + 144*count).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | u32 | Packed id (rid << 8) \| track (ARA1 track 8, BRA2 16) | |
| +0x4 | float3 | Bounds min (source cm, Z up) | |
| +0x10 | float3 | Bounds max (source cm, Z up) | |
| +0x1C | u32 | Runtime spline flag word: bit 0 rider mask (0 on disc, must be set at load; unconfirmed), bit 2 doubles rail imbalance. Set-piece paths (rocket, dragon, raven, spintwin) are not grindable | PS2 |
| +0x20 | u32 | Segment count | |
| +0x24 | u32 | Tool pointer residue (0x412Dxxxx), unused | |
| +0x28 | int | Surface id: -1 on disc, patched at load (Snow Jam: 10 metal/fence, 9 wood) | |
| +0x2C | u32 | Zero | |

## Rail spline segment

SSB kind 8; 144 bytes. Also used as spline path segments by set pieces.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | u32[3] | Loader-patched words: list link, type = 1 at +0x8 for the 0x00334680 walker (file values are residue) | |
| +0xC | float | Segment arc length | |
| +0x10 | float4[4] | Cubic rows: +0x10 t^3, +0x20 t^2, +0x30 t, +0x40 constant (start point, w=1) | |
| +0x50 | float4 | Arc-length to parameter cubic coefficients used by the set-piece path code 0x00345048; small values (~1e-3), not used by the rail code | |
| +0x60 | int | Previous global segment index (-1 at rail start) | |
| +0x64 | int | Next global segment index | |
| +0x68 | int/ptr | Rail index on disc; at runtime a pointer to the record header | |
| +0x6C | float3 | Segment bounds min | |
| +0x78 | float3 | Segment bounds max | |
| +0x84 | float | Cumulative distance at t=0 | |
| +0x88 | u32 | Pointer residue | |
| +0x8C | u32 | Flags, always 15 | |

## World render owner

Reached as *(game+0x1C). Owns the sun and light-glow state.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | ptr | View camera used by the light-glow update | |
| +0x60 | | Per-view light-glow list headers (+0x60 + view*4); records at +0x68 + view*0x3000, 0x30 bytes each | |
| +0x6070 | | Sun objects, one per view (stride 0x210) | |
| +0x649C | | Z-buffer query object (vtable 0x00487F00) | |
| +0x7BC0 | | Type-8 (light glow) entity list from visible cells (+0x7BC0/+0x7BC4), filled by 0x0022A4A8/0x0022A770; owner of this and a second list at +0x7FC4 not stated | unconfirmed |

## Sun object

World render owner +0x6070 + view*0x210.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1F0 | vec4 | Projected screen x/y/z of the sun (from 0x0037DD20) | |
| +0x204 | float | Sun visibility fraction from the Z-buffer query | |

## Per-view light-glow list record

0x30 bytes; lists live in the world render owner.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | | Count rect (x - w/2, y - h/2, w, h) for the Z query (+0x0..+0xC) | |
| +0x10 | | Read rect (x-8, y-4, 16, 8) clamped to the viewport (+0x10..+0x1C) | |
| +0x20 | ptr | Glow source world record | |
| +0x24 | | Light Z pulled toward the camera by 100/80/200 cm for class 0x10/0x20/0x40 | |
| +0x28 | float | Sprite rotation ((x - vx)*2/vw - 1) * pi/2 | |
| +0x2E | | Queried flag (1 when a Z query is issued); +0x2C is cleared alongside it | |

## Light glow source world record

World record kind 7; 80 bytes. ARA1 has 128 of them (82 class 0x10, 46 class 0x20).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xC | | Flags; flags & 0x70 gives the halo class (0x10, 0x20, 0x40) | PS2 |
| +0x10 | | Glow RGB colour | PS2 |
| +0x1C | vec3 | Glow position (cm, Z up) | PS2 |
| +0x28 | | Bounds (+0x28..+0x3F) | PS2 |
| +0x40 | float[4] | Per-view runtime visibility (+0x40 + view*4), written by the Z query and used the next frame | |

## Local light record

World extra node kind 6.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x14 | float | Light intensity; multiplies the distance attenuation factor | |
| +0x18 | float | Stored brightness used by light ranking (kind-0 rank value) | |
| +0x1C | float | Light radius (squared for the range test) | |
| +0x2C | vec4 | Light axis direction | |
| +0x38 | vec4 | Light position | |
| +0x5C | float | Spotlight cone cosine threshold (paired with +0x60; which is inner and which outer is not known) | |
| +0x60 | float | Spotlight cone cosine threshold (paired with +0x5C) | |
| +0x64 | int8 | Distance attenuation mode (1/2/3 = linear/squared/cubed factor, other values keep 1) | |
| +0x65 | int8 | Angular attenuation exponent/mode (0..4 explicit products, other values exponentiation by squaring) | |

## World painter (common layout)

Shared by the world painters (Fog, Lighting, Sun, glare and others).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | float | Accumulated planar travel distance; -99999 initialisation sentinel. The driver 0x002C0778 accumulates it, Fog blend leaves it, Fog defaults clear it, the glare ctor sets -99999 and reset sets 0 | |

## Fog world painter

Painter type 5; vtable 0x00484FE0. Payload values come in pairs (current value, then the latest sample).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | float[2] | Density (current, sample at +0xC); not a fog-equation mode selector | |
| +0x10 | float[2] | Near distance in cm (current, sample at +0x14) | |
| +0x18 | float[2] | Far distance in cm (current, sample at +0x1C) | |
| +0x20 | float[2] | Red (current, sample at +0x24) | |
| +0x28 | float[2] | Green (current, sample at +0x2C) | |
| +0x30 | float[2] | Blue (current, sample at +0x34) | |

## Lighting world painter

Painter type 11; vtable 0x00484290.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x48 | float | Gain scalar (first authored scalar; 1 on ARA1), returned by 0x002C15D0 | |
| +0x50 | float | Rim scalar (second authored scalar; 0.75 on ARA1, 0.65 on BRA2), returned by 0x002C15D8; blend 0x002BD5A8 treats +0x48/+0x50 as gain/rim (not +0x4C) | |

## Sun world painter

Painter type 9; vtable 0x00484700.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x48 | float | Glow half size (current value); 1 is treated as 320 cm | unconfirmed |

## Environment property object

Vtable 0x00484058. Its +0x0 matches the common painter layout.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | float | Accumulated distance used by the environment transition wrapper | |
| +0x30 | float | Breath scalar, current value (property pair 5; 9.99995136 at Snow Jam start) | PS2 |
| +0x34 | float | Breath scalar, target (property pair 5; 10 at Snow Jam start) | PS2 |

## Painter property wrapper

Vtable 0x00483E00 (also called environment wrapper object). Environment block +0x1C holds one for the Lighting painter; the driver 0x002C0778 writes the sample position.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | float | Last sampled X coordinate | |
| +0xC | float | Last sampled Y coordinate | |

## Environment block

0x004FA370 + index*0xF0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | ptr | Holder of the glare painter (type 6): painter = *(*(block+0x8)) | |
| +0x14 | ptr | Sun painter slot | |
| +0x1C | ptr | Lighting property wrapper (Lighting painter of this block) | PS2 |

## Painter section point tree header

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x14 | | Root node index | |
| +0x18 | | Outside leaf returned for out-of-range coordinates | |
| +0x20 | ptr | Relocated node array pointer | |
| +0x28 | | Start of the serialized 8-byte nodes | |

## Painter point-tree leaf node

8 bytes (also called environment spatial tree leaf).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | u32 | Payload index into the section's (type, payload pointer) table, i.e. the environment property payload table; all ones (-1) = no payload | |

## Environment lighting group

Terrain lighting sample.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x38 | vec4 | Terrain lighting ratio colour passed to the brightness curve 0x002EDF00 (not ambient RGB) | |

## World manager

Reached as **(gp+0x16C8), gp+0x16C8 = 0x004A47B8; the notes also call it world object W and world resource table. It is not the game world object W = *(G+0x84).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | ptr | Per-track pointer array indexed by resource & 0xFF (entries are world track records) | |
| +0x24 | struct[] | Per-track state entries (8 bytes, indexed by track); value 6 = active | PS2 |
| +0x3F0 | struct[] | Per-chunk texture streaming entries (24 bytes each), driven by race progress (e.g. ARA1 chunks 30-32 at the start); state 3 while streamed in. Items of non-resident chunks are not drawn; collision ignores chunks | PS2 |

## World track record

Entry of the world manager's per-track array.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1C | ptr | Per-resource entry array indexed by resource >> 8 | |

## Streaming manager (sky dome)

Owner object not named in the notes; may be the same object as the world streaming manager below.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1A4 | | Sky dome switch allowed flag, set by skybox_trigger volumes through builtin 68 action 5. A sky row reaching state 1 is activated (0x0022DE58) and replaces the dome (0x0022DE98) only if this allows it | unconfirmed |

## World streaming manager (location wait)

Owner object not named in the notes; may be the same object as the streaming manager above.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1D0 | | Wait flag: the game waits if a location would become collidable before its data is read | unconfirmed |

## Section activation manager

The object used by the 0x00101B60 section pass.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xD0 | int | Rescan marker; -1 forces the next section pass to rescan | |

## Streaming table row

Table at 0x00442168.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | int | SDB track number currently loaded for this row; 0x0022E0E0 searches rows by it to map a patch's track byte to a location id | |

## Animation sequence node

Entry of an animation channel list (next at +0xC8); also called animation sequence. Playback slots sit at sequence + i*0x1C.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Semantic state id (not a bank index) | PS2 |
| +0x60 | vec4 | Per-sequence root translation (preserved on reverse stance) | PS2 |
| +0x70 | quat | Per-sequence root quaternion | PS2 |
| +0x80 | int | Per-sequence mirror flag | PS2 |
| +0x84 | int | Priority (from the channel table 0x0048D808) | PS2 |
| +0x88 | u64 | 64-bit bone mask | PS2 |
| +0x90 | float | Sequence playback rate (grab control writes only the first sequence's rate) | |
| +0x94 | float | Value copied (with +0x98) from the old sequence by the completion replacement 0x00312B18 | |
| +0x98 | float | Value copied (with +0x94) by 0x00312B18 | |
| +0x9C | int | When nonzero, 0x00312B18 calls 0x00313A10 | |
| +0xB0 | u64 | Latched event flag word (bit = authored AFB event ordinal; bit 63 completion marker) | |
| +0xB8 | u64 | Raised/new event flag word (0x00144670 moves bit 63 here) | |
| +0xC0 | int | Completion flag, set by the clock wrap in 0x003135B0; returned by 0x00312AE8 | |
| +0xC4 | int | Seek flag | |
| +0xC8 | ptr | Next sequence in the channel list | PS2 |

## Animation playback slot

Sequence + i*0x1C.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | u32 | Packed clip id (low 8 bits bank, rest animation index) | PS2 |
| +0x8 | float | Clip time (s) | PS2 |
| +0xC | float | Rate | PS2 |
| +0x10 | float | Duration = (u16 frames - 1) * float(1/30) | PS2 |
| +0x14 | float | Weight | PS2 |
| +0x18 | int | Enabled (slot init only when this was 0) | PS2 |

## Animator

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x14 | | List of sequence entries (see "Animator sequence entry") | PS2 |
| +0x1C | float | Pending playback rate for the next animation request; a new play request consumes it and resets it to 1. Not the current sequence's rate | |

## Animator sequence entry

Entry of the list at animator +0x14; may be the same structure as the sequence node or playback slot above.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | | Clip | PS2 |
| +0x8 | float | Clip time (seconds) | PS2 |

## Animation state table entry

Table at 0x00446990.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | int | Driver kind (dispatched via 0x00456950) | |
| +0x8 | int | Completion kind (dispatched via 0x00456990) | |

## Animation clip/sequence

Exact owner not stated.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1C | float | Clip scale | unconfirmed |

## Model-part record

0x58 bytes; array at geometry +0x0C, one per model part (also called geometry part entry).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | u32 | Geometry file id of the part | PS2 |
| +0x4 | int | First bone slot (compiled bone base) | PS2 |
| +0x18 | | Active flag | PS2 |
| +0x1C | ptr | Variant table (also called the LOD0 list): 16-byte entries {model header, material names, flags, ...} | PS2 |
| +0x38 | ptr | Part bone data (original bone records) | PS2 |
| +0x44 | int | Part bone count | PS2 |
| +0x50 | | Selects the variant table entry whose model header the part uses (not always entry 0; Zoe's TopB/BottomB/HandsB_NIS/DummyB_NIS and Nate's TopC use variants 1..5) | PS2 |

## Render material state words

Three 32-bit words at renderer +0xE84 describing the current GS material state; offsets are relative to +0xE84.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | u32 | word0: bits 4..5 CLAMP_2 mode (clamp/clamp for terrain) | |
| +0x4 | u32 | word1: bits 2..6 ALPHA_1 blend enum, bits 7..11 ALPHA_2 blend enum, bits 23..24 ZTST mode. Glow material: ATST ALWAYS (bits 20..21 = 0) with AREF 0x14 (word not stated) | |
| +0x8 | u32 | word2: bits 5..9 render priority (stored with and -0x3E1 / ori p<<5) | |

## Static model header (MDR)

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | | Flags; bit 3 selects additive blend 0x48 (Cd + Cs*As) with ATST GREATER 20 | |

## Static model material record

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xC | | Blend class bits (flags & (0x66 << 16)) and env-map variant flags (bit 21, bit 22). Class 0: opaque, no test; 0x20000: 0x44 + ATST GREATER 92; 0x40000/0x60000: 0x44 + ATST GREATER 20 (depth-sorted). Group flag bit 3 adds 0x40000 | |

## Texture descriptor

Input to the texture binder 0x00368970.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x38 | u64 | GS TEX0 template; the binder adds the VRAM address bits (btrl template: 0x000000059C008000) | PS2 |

## Terrain renderer

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x360 | mat4 | Camera-derived 0.5-scaled matrix used for layer type 6 environment-map UVs | unconfirmed |

## Particle emitter

Emitter class associated with 0x003705E0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x180 | int | NumFlipTextures | |
| +0x184 | float | Flipbook phase (zeroed by 0x00370018) | |
| +0x188 | float | FlipTextureRate | |

## Snow emitter

Class 0x004930D0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | float | Flipbook phase; animated chunks start at 1.5 / 4.5 / 3.0 | PS2 |

## Component manager group

Stride 0x44; manager at gp+0x2898 = 0x004A5988.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | struct | Active list sentinel | |
| +0x8 | ptr | First active node; iteration follows node +0x4 and ends at group +0x14 | |
| +0x24 | struct | Pending list sentinel (tail link at +0x28) | |

## Component scheduler node

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | ptr | Next link used by active-list iteration | |
| +0x14 | u32 | Node id compared by the default ordering/equality virtuals 0x00360800/0x00360840 (not assumed to be an instance id) | |

## Debounce component

Ctor 0x00342C08.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x2C | int | Countdown ticks (60 for a 1 s debounce); only strictly positive values are decremented by 0x00342D88 | |
| +0x30 | int | Restore/state mode; 3 makes completion construct a type-19 node | |
