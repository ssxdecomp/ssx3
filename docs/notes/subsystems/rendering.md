# Rendering and lighting

Each frame SSX 3 draws the world (terrain patches, static models, riders and their board tracks) into one sorted
render list, then works on the finished framebuffer in screen space: a depth-palette fog composite, a layer of
additive effects (snow spray, light halos, sun glow and lens flare), an optional glare/bloom pass, and a full-screen
colour tint. Most of the atmosphere is authored per location as "world painters": point-quadtree regions that
select payloads (fog, tint, sun, glare, rider lighting) which are blended in as the camera or rider moves. Riders
are lit per vertex on VU1 from a 10-row irradiance coefficient bank built from the IRR.DAT database, a terrain-
sampled brightness, a view-dependent rim term and up to eight authored local lights.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

Decomp translation units (per the current splits; several renderer methods currently land in unrelated-looking
files):

- `src/object/railmodifier.cpp` (current split): sorted render-list draw `0x00363490`, material-state to GS
  registers `0x00363C20`, TEST/ZTST decode `0x003626D8`, blend-enum setter `0x00362478`, VU1 template upload
  `0x00364CD0`.
- `src/render/bezierman.cpp`: terrain patch list walk `0x0038B0F8`, patch DMA builders `0x0038CA70`/`0x0038CE20`,
  environment-map layer `0x0038D168`, extra per-patch draw `0x0038D690`, shadow receivers `0x0038CA08`/`0x0038D448`,
  patch LOD helpers `0x0038B178`/`0x0038B190`.
- `src/render/graphicsman.cpp`: fog palette `0x0036A428`, palette upload `0x0036AA60`, depth pass `0x0036AE20`,
  composite sprites `0x0036B158`, fog composite `0x0036AC00`, fog context copy `0x0036ABA0`; glare pass
  `0x0036C790` with `0x0036C740`, `0x0036B9D8`, `0x0036C188`, `0x0036C398`.
- `src/render/lightman.cpp`: ScreenTint context copy `0x00390458`, draw `0x003904A0`/`0x003905E8`.
- `src/render/particle.cpp` (current split): static-model draw `0x0037E238`, point projection
  `0x0037DBE8`/`0x0037DD20`, sprite emit `0x00377CF0`, halo quad `0x003781A0`, perspective setup `0x00376C58`,
  rider part draw `0x0037A610`, skin palette `0x00386BD0`, irradiance helpers `0x00389308`..`0x0038ABF8`, CPU
  texture sampler `0x003889F0`, shadow fit `0x00374D00`, frame-flip state machine `0x00382760`, per-view render
  setup `0x00386640`/`0x00386688`.
- `src/render/irradiance.cpp`: `0x0038ACD0` (`cIrradianceDataBase_Load`).
- `src/render/font.cpp` (current split): renderer matrix stack and view `0x003956E8`, `0x00395730`, `0x00395750`,
  `0x00395C38`, `0x00395C68`; lighting-bank setter `0x003954D0`; VU1 coefficient upload `0x00396B40`.
- `src/render/ps2graphicsman.cpp`: TEX0 texture-function writer `0x003691B0`, GS restore chain `0x00368138`.
- `src/worldpainter/worldpainterqueryctor.cpp`: `0x002C0408` (`cWorldPainterQuery_cWorldPainterQuery`), painter
  driver `0x002C0778`, payload lookup `0x002C0A10`. `src/worldpainter/worldpaintermanquery.cpp`: painter getters
  `0x002C14F0`..`0x002C15D8`. `src/worldpainter/quadtree.cpp`: point query `0x002C1CD8`.
- `asm/1BA100.s` (not yet split): painter item constructors and methods `0x002BC7C8`..`0x002BF700`, section
  lookup wrapper `0x002BAF90`, reference compare `0x002BB100`.
- `src/visualfx/lensfx.cpp`: per-block environment update `0x002ED490`, terrain colour `0x002EDB20`, colour
  filters `0x002ED1D0`/`0x002ED338`, brightness curve `0x002EDF00`, bank getters `0x002EDFB8`, `0x002EE010`,
  Z-buffer visibility query `0x002EC478`, camera far-cap query `0x002EE3B8`.
- `src/visualfx/renderstateman.cpp`: painter-to-globals copy `0x002F00A0`, painter getters `0x002EE9C0`..`0x002EF0E8`.
- `src/visualfx/boardwakefx.cpp` (current split): light halos `0x002E2B00`, `0x002E2868`, `0x002E3578`; sun/halo
  object update/draw `0x002E30D0`, `0x002E3338`, `0x002E3478`; visibility callback `0x002E3130`.
- `asm/1F1548.s` (not yet split): sun placement `0x002F4DB8`, glow `0x002F4A08`, flare `0x002F4690`.
- `src/visualfx/worldlightman.cpp`: local-light ranking and selection `0x002F5B68`, `0x002F5D30`, `0x002F6168`.
- `src/main/game.cpp`: `0x0022C790` (`cGame_renderLightHalos`), `0x0022C708` (`cGame_renderFogVolumes`).
  `src/main/ssxapp.cpp`: visible-cell collectors `0x0022A4A8`, `0x0022A5A0`, `0x0022A770`.
- `src/ai/rider.cpp`: rider irradiance assembly `0x001220D8`, light selection `0x00122088`, query refresh
  `0x00120E50`, query bounds `0x0011E150`, rider draw `0x00122448`, shadows `0x001225F0`/`0x00122898`.
- `src/animation/animmodel.cpp`: pose matrices `0x00310120`/`0x00310530`, skinned geometry draw `0x00310640`.
- `src/main/debugmenu.cpp`: glare tweakables are registered inside `0x00249148` (`cLightGlowMenu_cLightGlowMenu`).

## Frame structure and draw order

`0x00363490` draws the depth-sorted render list in three layers, split at material priorities 6 and 9 (the
constants at `0x004A4058`):

| Step | Content |
| --- | --- |
| Layer 0 (priority < 6) | world: terrain, static models, riders; board track at priority 3; rider shadow receivers |
| `0x0036AC00` | fog composite over the whole frame |
| Layer 1 (priorities 6..8) | priority 7: snow emitters, wake, boost strips, board sparks, light halos, fog-volume sprites, static models on the `0x0037ECB0` path; priority 8: sun glow and flare, air streamers, reset fade, models on the `0x0038057C` path |
| `0x0036C790` | framebuffer glare (painter type 6) |
| `0x003904A0` | ScreenTint |
| Layer 2 (priority >= 9) | HUD (unconfirmed that nothing else lives here) |

Consequences: layer-1 effects are not fogged; the sun and halos are added after fog and are then scaled by
ScreenTint **(PS2)** (the sun core reads (243,235,255): white clamped, then tinted). All blending is in the 8-bit
framebuffer domain; there is no linear-light arithmetic anywhere in these passes.

### Material state word

The per-draw material state (for terrain, `[renderer+0xE84]`) is turned into GS registers by `0x00363C20`:

| Field | Meaning |
| --- | --- |
| word0 bits 4..5 | CLAMP_2 mode (terrain: clamp/clamp) |
| word1 bits 2..6 | ALPHA_1 blend enum |
| word1 bits 7..11 | ALPHA_2 blend enum (context 2) |
| word1 bits 20..21 | alpha-test mode (0 = ATST ALWAYS); AREF seen as 0x14 |
| word1 bits 23..24 | Z test, decoded by `0x003626D8`: 0 GREATER, 1 GEQUAL, 2 ALWAYS |
| word2 bits 5..9 | sort priority (written as `and ~0x3E0 / or p<<5`) |

Blend enums go through the table at `0x00491FB0`, applied by `0x00362478` (the per-enum setters are code
locations inside it, e.g. `0x003624D0` and `0x003624DC`):

| Enum | GS ALPHA | Equation |
| --- | --- | --- |
| 1 | `0x2A` | `Cs` (opaque) |
| 5 | `0x44` | `(Cs - Cd) * As >> 7 + Cd` (ordinary alpha blend) |
| 7 | `0x48` | `Cd + Cs * As >> 7` (additive) |
| 8 | `0x81` | `(Cd - Cs) * As >> 7` |

Other ALPHA values used directly: `0x58` (`Cd + Cs * Ad`) for the terrain environment-map layer, value 1
(`(Cd - Cs) * As >> 7 + Cs`) for the fog composite.

## World painters

A world painter is a per-location section of authored data: a point quadtree over the XY plane whose leaves select
one of several payloads of a given painter type. At run time each painter type has a typed item object that holds
current values and blends toward the selected payload as the sampling point moves.

### Environment blocks

`0x002ED490` updates an array of environment blocks at `0x004FA370`, stride `0xF0`. Block 0 is the human rider,
blocks 1 and 2 hold the computer riders, and blocks `6 + view` belong to the camera views (the sun uses views 6/7).
The camera caller is the call at `0x0015EBBC`..`0x0015EBD0` inside `0x0015E668`, which runs after camera
collision `0x0015EE00` and shake `0x0015E460` and passes the final outer-camera X/Y (`+0x20`/`+0x24`), view index
+ 6 and the automatic-weight sentinel. The rider path (`0x001218D0`) uses separate painter instances and passes
the rider's contact point (`rider+0x460`/`+0x464`); the rider breath effect's painter is driven the same way.

| Offset | Content |
| --- | --- |
| `+0x00`..`+0x20` | nine painter-wrapper pointers, run in order by `0x002ED490` (layout inferred from the known slots) |
| `+0x08` | type-6 (glare) wrapper |
| `+0x14` | Sun wrapper |
| `+0x1C` | Lighting wrapper |
| `+0x24` | alternate-bank selector (float) |
| `+0x28` | environment ARGB (4 floats): colours board trails and snow |
| `+0x38` | lighting ratio ARGB (4 floats) |
| `+0x50` | 160-byte environment irradiance bank (10 rows x 4 floats), returned by `0x002EDFB8` (`0x004FA3C0 + i*0xF0`) |

The Fog and ScreenTint wrapper offsets are not recorded.

### Painter types and the factory

These notes read `0x002C0408` as the painter-item factory: a switch on the painter type that constructs the typed
item (case 6, 7 and 9 are traced below). The decomp names this function `cWorldPainterQuery_cWorldPainterQuery`
and carries evenly spaced local labels in it (`lbl_002C0470` onward, every 0x28 bytes), which fits a jump-table
switch; whether it is a query constructor that also builds the typed item, or purely a factory, is unresolved.

| Type | Item | Constructor | Vtable | Blend | Compare | Reset |
| --- | --- | --- | --- | --- | --- | --- |
| 5 | Fog | `0x002BC7C8` | `0x00484FE0` | `0x002BCF38` | `0x002BDB38`* | `0x002BE108` |
| 6 | glare ("light glow" menu) | `0x002BC830` | `0x00484DA8` | `0x002BD068` | `0x002BDBD0`* | `0x002BE140`* |
| 7 | ScreenTint | `0x002BC890` | `0x00484B70` | `0x002BD1B8` | `0x002BDC78` | `0x002BE170`* |
| 9 | Sun (`tWPIGD_Sun`) | `0x002BC910` | `0x00484700` | `0x002BD378` | `0x002BDD38`* | `0x002BE1A8`* |
| 11 | Lighting (`tWPIGD_Lighting`) | `0x002BC9B0` | `0x00484290` | `0x002BD5A8` | `0x002BDE30` | `0x002BE1F8`* |

\* Not recognised as function starts in the current split of `asm/1BA100.s`; the lookup places `0x002BDB38` inside
`0x002BDABC`, `0x002BDBD0` inside `0x002BDBC4`, `0x002BE140` and `0x002BE170` inside `0x002BE108`, `0x002BDD38` inside
`0x002BDD04`, and `0x002BE1A8` and `0x002BE1F8` inside `0x002BE198`.

Snow Jam (ARA1) authors types 1, 2, 4, 5, 7, 9, 11 and 12; types 1, 2, 4 and 12 are not described here. A
"Weather" painter value also exists (it gates the lens snow splats, see below); its type number is not recorded.

Item vtable entries are 8 bytes; these offsets are documented for Fog, glare and Lighting:

| Offset (entry) | Method |
| --- | --- |
| `+0x200` (64), `+0x208` (65) | stream serializers (Fog `0x002BF580`/`0x002BE518`, glare `0x002BF700`/`0x002BE698`) |
| `+0x210` (66) | blend toward a payload with a weight |
| `+0x218` (67) | notify hook, called before and after the blend (empty for Fog `0x002BDA48`, glare `0x002BDA50`, Lighting `0x002BDA58`) |
| `+0x220` (68) | compare current values with a payload |
| `+0x228` (69) | reset to defaults |

Item layout: `+0x0` is the travel-distance accumulator (the constructor stores the -99999 sentinel there, reset
stores 0); for Fog and glare the values follow from `+0x8` as (current, latest sample) float pairs. Blend methods
square the weight without clamping and compute, per value, `cur = w*w*sample + (1 - w*w)*cur`, then store the
sample; the payload's rate word is not consumed by the blend.

### Driver `0x002C0778`

Each wrapper's virtual slot 0x10 is the driver `0x002C0778` (Lighting wrapper vtable `0x00483E00`). Per call
with (x, y, weight):

1. Accumulate the planar distance from the last sample point into the item's `+0x0` and store the new X/Y at
   `+0x8`/`+0xC` (of the wrapper, unconfirmed which object).
2. Resolve the current region's painter section through the level manager; reject sections of another type.
3. Look up the payload for (x, y): `0x002BAF90` then `0x002C0A10`. A missing region or missing payload resets the
   item through `+0x228` (distinct paths; the first missing-section dispatch resets twice).
4. Call compare (`+0x220`), then blend (`+0x210`) with a weight chosen as follows. On first use (item `+0x0` holds
   the init sentinel at `0x0049EE6C`, -99999.0) the weight is -1, which squares to 1. An explicit weight is used
   as given. With the automatic sentinel (`0x0049EE70`, -99999.0) the weight is `-rate`, except that a
   non-negative rate acts as a travel-distance threshold: once passed, weight 1 is used and the distance is
   cleared (comparison direction as read, unconfirmed). There is no time-based lerp.

**(PS2)** In a Metro-City race the Lighting wrapper re-seeded itself once mid-race (distance 0, rim scalar exactly
the payload value, i.e. a weight -1 blend); the trigger is not found.

### Section format and quadtree query

The painter section has an 8-byte `(type, payload pointer)` table and a point quadtree
(`src/worldpainter/quadtree.cpp`, where the decomp also has `cQuadTree_*` functions). `0x002C1CD8` subtracts the
tree origin X/Y, multiplies by the stored scale, converts with truncation (so small negative fractions become 0)
and accepts integers 0..32767; anything else returns the explicit outside leaf at tree `+0x18`. Header: root
index `+0x14`, relocated node pointer `+0x20`, serialized nodes from `+0x28`. Nodes are 8 bytes; a set low bit in
the first halfword marks an internal node, whose four halfwords are child indices shifted left by one. Successive
high bits of the doubled 15-bit X/Y choose the quadrant. A leaf's second 32-bit word is the payload index; -1 (all
bits set) means no payload.

Each payload starts with the rate float. Sizes seen: ARA1 fog 333 nodes / 9 payloads; the Metro-City (BRA2)
Lighting tree 1013 nodes / 5 payloads.

### Painter to render context

`0x002F00A0` (per view) copies painter values into globals, and the renderer's per-view setup `0x00386640`
copies the globals into the render context (`0x0036ABA0` fog, `0x00390458` ScreenTint, `0x0036C740` glare):

| Painter | Getters | Globals | Render context |
| --- | --- | --- | --- |
| Fog | `0x002EE9C0` density, `0x002EEA08`/`0x002EEA50` near/far, `0x002EEA98`/`0x002EEAE0`/`0x002EEB28` RGB | density `0x004A4338` (gp+0x1248), near/far `0x004A432C`/`0x004A4330`, equation `0x004A4334` (set to 1) | `+0x6C64`: near, far, equation, density, alpha, RGB |
| ScreenTint | - | scale/add `0x004A45E4`..`0x004A45F8` (gp+0x14F4..0x1508) | `+0x6CA4` |
| type 6 | `0x002EEDB0`..`0x002EEF60` | `0x004A43D4`..`0x004A43E4`, `0x004A43F0`, `0x004A43F4` (skipped when Override is set) | `+0x6CD4 + view*0x1C` (7 floats) |

The camera far clip comes from a different painter slot, through `0x002EE3B8`; fog far distance does not drive
the far plane.

## Terrain patches

`0x0038B0F8` walks the patch lists and calls the DMA builders `0x0038CA70`/`0x0038CE20`. Terrain is a set of
bicubic patches; the contact code queries the analytic surface, while the renderer draws a tessellated
approximation (the LOD rule in `0x0038B178`/`0x0038B190` and the "tier-2" and stitched patch lists are not
recovered).

| Patch field | Meaning |
| --- | --- |
| `+0x0C` | three 3-bit layer types: base, light, extra. ARA1 uses `0x29` (base type 1 + light type 5) and, on 87 start-ramp patches, `0x1A9` (adds type 6) |
| `+0x10` | PS2 light-page UV |
| `+0x156` | streaming chunk index (not a material id) |
| `+0x1A0`/`+0x1A2`/`+0x1A4` | layer texture indices |

### Two-pass lightmap combine **(PS2)**

The builders set the material state to ALPHA_1 enum 1 (`0x2A`, opaque), ALPHA_2 enum 8 (`0x81`), CLAMP_2
clamp/clamp, and alpha test enabled with ATST ALWAYS. `0x00364CD0` mode 2 uploads VU1 GIF templates with PRIM
`0x5C` for context 1 and `0x25C` (CTXT=1) for context 2, plus a constant vertex RGBA of `0x80`. The patch display
list carries one V3-32 position block and two V2-32 UV blocks (base UV, light UV). Both textures use TFX
MODULATE, TCC 1; the light pages (`strm_lpg`) are PSMCT32 with alpha 0..255. Per pixel:

```
pass 1 (ctx 1): Cd = T_base
pass 2 (ctx 2): C  = clamp(((T_base - L.rgb) * L.a) >> 7)   // L.a up to 255, so up to ~2x
```

The render queue at `*(renderer+0x18F0)` in a savestate holds these terrain records, and frames drawn with this
combine closely match PS2 screenshots. The same formula, in float with a rider tint, is the CPU terrain-colour routine
`0x002EDB20` (see "Environment colour").

### Extra layers

- Layer type 6 (texture 62, start-ramp patches), `0x0038D168`: a VU environment map whose UVs come from normals
  through a camera-derived, 0.5-scaled matrix at terrain renderer `+0x360`, blended with ALPHA `0x58`
  (`Cd + Cs * Ad`). The destination-alpha source (possibly a FRAME mask of the light pass) is unverified.
- A patch flag at bit 23, `0x0038D690`: a distance-scaled per-patch extra draw, probably sparkle (unconfirmed).
- Rider shadow receivers `0x0038CA08`/`0x0038D448` (see "Rider shadows").

Boards sinking into powder is authored, not a render error: the powder surface (surface 2) has a depth target of
about 50 cm.

## Static models, sky and draw eligibility

`0x0037E238` draws static model instances; its material setup lives at `0x0037F2A4`..`0x0037F6C8` inside it.
Texture function MODULATE with the VIF UNPACK V4-5 vertex colour:

```
Cs = T * (c5 << 3) >> 7        As = Ta * (bit15 << 7) >> 7
```

The sky dome is such a model; its vertex colour 16 (of 31) gives unity modulation. Blend class:

- Model header `+0x10` bit 3: additive `0x48`, ATST GREATER 20.
- Otherwise material word `+0x0C` (the group flag bit 3 adds bit 18) is masked to bits 17, 18, 21, 22: nothing
  set = opaque, no test; bit 17 = `0x44` with ATST GREATER 92; bit 18 (with or without 17) = `0x44` with ATST
  GREATER 20, depth-sorted. Bits 21/22 mark environment-map variants (not traced).
- All alpha tests use AFAIL FB_ONLY (failing texels still write colour, not depth).
- A per-instance distance fade (`0x0037E238` argument f12 into a FIX alpha) and culling exist (not traced).
- Vertex alpha bit 15 is clear on the fading parts of searchlights, pinlights and snow streams.

Eligibility: static instances draw only when `(flags & 3) == 3` (collector `0x0022A5A0`); dynamic entities draw
through vtable `+0x20`, which is empty for DeadNode, RestoreNode and type-16 nodes, and the draw at `0x00356298`
also requires flags bit 2. **(PS2)** Helper instances (reset planes, collision volumes, RaceRideState boxes,
emitter/trigger placeholders, camera-flash models, free-ride Big Challenge gates) have these bits clear and are
absent from PS2 frames; a PS2 Z buffer confirms that a large helper box around the start does not write depth.
The renderer-side test that the instance list applies is not traced.

Texture chunks stream by race progress (`W+0x3F0`; e.g. ARA1 chunks 30-32 at the start, the finish connector's
chunk only near the finish), driven by `mdl_*_Load`/`mdl_*_Unload` helper volumes; items of non-resident chunks
are not drawn. A Snow Jam race keeps the course and both connector locations resident.

## Fog

Fog payload (after the rate): **density**, near (cm), far (cm), R, G, B. (Older notes called the first value a
mode; it is a float density, not an enum.) Reset `0x002BE108` reloads near/far/RGB from globals, clears the
distance and the density (the density clear is in the return delay slot), and keeps the sample slots. Compare
`0x002BDB38` compares the six current values only.

### Depth palette `0x0036A428`

1. Project near and far into depth bins (`0x0036A478`..`0x0036A618`, inside `0x0036A428`): transform
   `(0, 0, distance, 1)` through the four projection columns, divide by W, truncate projected Z, shift right 8,
   clamp 0..255. RGB is multiplied by 255 and truncated.
2. Fill a 256-entry CLUT (`0x0036A6EC`..`0x0036AA20`). Equation 0: integer linear; 1: seventh-order polynomial
   approximation of an exponential, with a 0.1 density scale; 2: squares the density term first. Values clamp to
   0..1, scale by 128, truncate, and pack with RGB. CLUT indices have bits 3 and 4 swapped. An unknown
   equation leaves the entries between the bins unchanged; entries past the near bin are still filled with
   alpha 128. Equal or reversed bins use a minimum span of 1.

The projection comes from `0x00376C58`: if the depth format at context `+0x5A40` is 31 (PSMZ24) the range is
16777215, else 65535 (constants at `0x004A0930`/`0x004A093C`, gp-0x27C0/-0x27B4). Reverse depth:

```
delta  = far - near
slope  = (-range * near) / delta
offset = (-far * slope) + viewportDepthOffset      // projected W = view Z
```

`0x00386688` copies the active matrix at context `+0x6AF0` into the per-view `+0x5930` before later draws replace
it. **(PS2)** The Snow Jam countdown context uses format 31; its render-context pointer is the word at
`0x004A289C` (gp-0x854).

### Composite `0x0036AC00`

Builds the CLUT, uploads it (`0x0036AA60`), runs the depth pass `0x0036AE20`, then draws the composite sprites
`0x0036B158`.

- Depth pass: FRAME_1 PSMCT16 with FBMSK `0x3FFF`, TEX0_1 PSMZ16 (DECAL, RGBA), TEXA TA0=0/TA1=128, PRIM
  `0x116` (textured sprite, UV, no blend). Sprites are 8 px wide; the loop steps 2 columns (columns = width/8),
  UV from (0.5, 0.5) to (8.5, height + 0.5) moving 16 px per iteration, destination X starting 8 px past the
  origin. The net effect, derived from the GS memory layout (not checked on a real framebuffer): each pixel's
  alpha byte becomes `(Z >> 8) & 255` with RGB unchanged, and the T8H view reads that byte.
- Composite: ALPHA_1 value 1 (`(Cd - Cs) * As >> 7 + Cs`), PABE 0, TEX0_1 PSM T8H with TCC 1, TFX DECAL, PRIM
  `0x156`, RGBAQ unity. TEST_1 `0x70000`: Z test GREATER against sprite Z `0xFFFF`. So per encoded byte:

```
out = fog + (((scene - fog) * paletteAlpha) >> 7)     // 128 keeps the scene, 0 gives fog
```

  and only pixels with 24-bit Z below 65535 are fogged; nearer pixels keep their colour. The index wraps
  (`(Z >> 8) & 255`), so the Z gate is what protects the foreground.

The context fields `+0x5A80`/`+0x5A84` hold `0xE0` and 0 in the countdown **(PS2)**; `0xE0 << 5` = block 7168
is the Z buffer (the glare pass reuses it).

## ScreenTint

Type 7 painter, driven by `0x002C0778` from the camera X/Y. The payload holds a scale colour and an add colour
(the exact payload layout is not recorded). `0x003904A0` calls `0x003905E8`, which returns immediately for
identity; otherwise it re-reads the framebuffer as a PSMCT32 texture (nearest, MODULATE, no blend) drawn with
vertex RGB `trunc(scale * 127.5)`, then optionally adds a `0x48` sprite of colour `trunc(add * 127.5)`.

ARA1 has 8 ScreenTint payloads, e.g. start (1.1, 0.85, 1.0), glide (0.9, 0.85, 1.15), later identity.
**(PS2)** One driver step from a captured glide state reproduces the next frame's values; during the glide the
live tint is still transitioning (about (0.925, 0.873, 1.120)).

## Framebuffer glare (painter type 6)

The game's debug menu (inside `0x00249148`, `cLightGlowMenu_cLightGlowMenu`, at `0x00249200`) names the globals:

| Global | Name | Retail |
| --- | --- | --- |
| `0x004A43C8` (gp+0x12D8) | Enable | 1 |
| `0x004A43CC` | Override World Painter | 0 |
| `0x004A43D0` | PS2 Capture Size (2^x) | 8 |
| `0x004A43D4` | Minimum Intensity Cutoff | painter |
| `0x004A43D8` | Post-Cutoff Scale | painter |
| `0x004A43DC` | Copy Intensity | painter |
| `0x004A43E0` | Frame Source Intensity | painter |
| `0x004A43E4` | Frame Blend Intensity | painter |
| `0x004A43E8`/`0x004A43EC` | Blend Texture 0/1 | 0 |
| `0x004A43F0`/`0x004A43F4` | Blend Texture 2/3 | painter |
| `0x004A43F8` | Texture Jitter | 2.0 |

Retail values are from the ELF and every inspected savestate **(PS2)**. Painter item: constructor sets `+0x0` to
-99999, `+0x8`..`+0x2C` to 1 and `+0x30`..`+0x3C` to 0; seven (current, sample) pairs; reset gives 1,1,1,1,1,0,0;
payload = rate + seven values; getters `0x002C14F0`..`0x002C1520` (vtable entries 13..19).

`0x0036C790`, per view (render context values `+0x6CD4 + view*0x1C`):

1. Return if Enable is 0. `A = trunc(127.5 * (BT0, BT1, BT2, BT3))`; return if all four are 0. BT0/BT1 are the
   debug globals, BT2/BT3 come from the painter, so only the painter can enable the pass in retail.
2. Level L0 (256x256 PSMCT24, placed in the Z-buffer area at block 7168; L1/L3 at +0x400 from it): `0x0036B9D8`
   copies the 512x448 viewport (TBP 0) with bilinear filtering as eight 32-px column sprites, UV
   `(0.5 + 2x, 0.5 + 1.75y)`, MODULATE by `trunc(FrameSource * 127.5)`, no blend.
3. `0x0036C188`: untextured sprites over L0 with ALPHA `(Cd - Cs) * FIX >> 7`, `Cs = trunc(Cutoff * 127.5)`,
   `FIX = trunc(PostCutoffScale * 127.5)`: a threshold.
4. For i = 0..2: if `A[i]`, composite L_i; then `0x0036B9D8` halves it (L1 128, L2 64, L3 32) with four bilinear
   samples at `(-J,-J), (+J,+J), (+J,-J), (-J,+J)`, `J = trunc(Jitter * 16)` in 1/16 texel units (32 = 2 texels),
   over a source span shrunk by 2J, each MODULATE `trunc(trunc(Copy * 127.5) / 4)`; sample 0 is written, 1..3
   added with ALPHA `Cs + Cd`. Columns = `dstW / 32` (signed; a 16-wide level draws nothing, reachable only with
   a debug capture size of 2^7).
5. If `A[3]`, composite L3. Composite `0x0036C398`: 16 column sprites over the viewport, region-clamped level
   texture, `u = 0.5 + x*W/512`, `v = y*H/448` (no half-texel on v), MODULATE by `(A,A,A,A)`, ALPHA
   `Cd * FIX >> 7 + Cs` with `FIX = trunc(FrameBlend * 127.5)`: every composited level also scales the frame.
6. Restore FRAME/XYOFFSET and chain the static restore packet at `0x0044B200` (`0x00368138`).

With the retail painters (BT2 = 0 except one location at 0.6, BT3 = 1 or 0) the effect is: threshold the
half-resolution frame, blur it to 32x32 with three jittered 2x2 passes, scale the frame by FrameBlend
(0.75..1) and add the 32x32 glow scaled by BT3. 16 of the 43 world painter records author type 6 (e.g.
Metro-City); ARA1 has none, so its context stays at the reset values and the pass never runs **(PS2)**.
**(PS2)** In two savestates the painter item was a whole number of driver steps (9 and 14) ahead of the
render-context copy; the reason for the lag is not traced.

## Sun glow and lens flare

Sun payload (10 words): rate, elevation (deg), azimuth (deg), R, G, B, glow alpha, texture index (integer, blended
as a float and truncated), flare alpha, glow half size. Weight squared as usual. Getters `0x002C1560`..`0x002C15A0`,
reached through `0x002EE070`..`0x002EE2B0`. Reset defaults: angles 0 (then 107 and 16 degrees from the constants
at `0x0049F834`/`0x0049F838`, gp-0x38BC/-0x38B8), colour 1, alphas 1, texture 0, size 1. ARA1 paints one payload:
elevation 9.15, azimuth 160, white, glow alpha 0.95, texture 0, flare alpha 0.85, half size 280 **(PS2)**.

The sun object lives at owner `+0x6070 + view*0x210` (owner = `*(game+0x1C)`); `0x0022C790` calls `0x002E30D0`,
which runs update `0x002E3338` and draw `0x002E3478`.

- Placement `0x002F4DB8` (per camera): texture index -1 hides it. Direction
  `(cos az cos el, sin az cos el, sin el)` (Z up); point = eye + dir * (far - 500 cm), far = camera `+0x58`
  (300 m). The outcode test `0x0037DBE8` hides it unless the point projects inside the viewport; `+0x1F0` gets the
  screen xyz from `0x0037DD20` (integer pixels of the 512x448 viewport, `pixel = trunc(continuous - 0.5)`
  **(PS2)**), and a 16x16 query rect at (x-8, y-8) is clamped to the viewport.
- Visibility: `0x002E3130` calls the query object at owner `+0x649C` (vtable `0x00487F00`, slot `+0x24` =
  `0x002EC478`), a GS local-to-host transfer of that Z-buffer rectangle counting pixels whose Z does not exceed the
  sun's. `vis = open/256` when the rect is fully on screen, else `max((open - 128)/128, 0)`; stored at `+0x204`.
- Glow `0x002F4A08`: FX texture 51 + index (`sun1`/`sun2`, 128x64, EFFECTS.SSH), one sprite through `0x00377CF0`
  centred on the sun, half extent from `+0x48` (320 when it is 1), vertex ARGB
  `trunc(128 * (vis*glowAlpha, R, G, B))`.
- Flare `0x002F4690`: nine sprites (table built by `0x002F43E0`, colours from a gp pool read at `0x002F6BC0` and
  `0x002F7804` inside `0x002F6B88`) from the 256x256 `lens` atlas (FX 45; quadrants ring, soft blob, star, disc),
  at `centre + (sun - centre) * t`, half extent `300 * s`, alpha `a * vis * flareAlpha`.
- Both use enum 7 (`0x48`), MODULATE, priority 8.

## Light halos

Sources are world records of kind 7 (80 bytes; runtime entity type 8 in the per-cell entity lists; ARA1 has 128):

| Offset | Field |
| --- | --- |
| `+0x0C` | flags; `& 0x70` = halo class (0x10, 0x20, 0x40) |
| `+0x10` | RGB |
| `+0x1C` | position (cm, Z up) |
| `+0x28`..`+0x3F` | bounds |
| `+0x40 + view*4` | visibility (runtime) |

`0x0022A4A8`/`0x0022A770` append the type-8 entities of visible cells to `+0x7BC0`/`+0x7BC4`. `0x0022C790`
(`cGame_renderLightHalos`) rebuilds the per-view list at owner `+0x60 + view*4` / `+0x68 + view*0x3000`
(0x30-byte records) with clear `0x002E2F98` and add `0x002E2FF8` -> `0x002E2FA8` (record `+0x20` = source;
`+0x28`, `+0x2C`, `+0x2E` cleared), then runs update/draw through `0x002E30D0`. A second list (`+0x7FC4`,
argument 2) was empty in all captured states **(PS2)**. The live list matches the authored records byte for
byte **(PS2)**.

Update `0x002E2B00` per record (view camera at owner `+0x10`):

- Outcode `0x0037DBE8` (inside the view volume, else `+0x2C = +0x2E = 0`); `0x0037DD20` gives integer x/y and a
  24-bit Z (2^24 at the 30 cm near plane, 0 at the far plane); `zf = Z * 2^-24` (constant `0x0049F6B0`).
- `zf <= 0.005` (`0x0049F6B4`, about 50 m): far glow, no query, visibility 1.
- Otherwise `+0x2E = 1`; count rect `+0x0`..`+0xC` = (x - w/2, y - h/2, w, h) with
  `w = clamp(trunc(zf*800), 1, 16)`, `h = clamp(trunc(zf*400), 1, 8)`; read rect `+0x10`..`+0x1C` = 16x8 at
  (x-8, y-4), clamped; `+0x24` = the light's Z pulled toward the camera by 100/80/200 cm for class
  0x10/0x20/0x40; `+0x28` = `((x - vx)*2/vw - 1) * pi/2` (`0x0049F6B8`), the sprite rotation.

Visibility: `0x002E3130` is registered (callback `0x002E3110`) through renderer vfunc `+0x3A8` = `0x003866E0` and
called by the frame-flip state machine `0x00382760` in state 2, i.e. after the whole frame. It runs `0x002EC478`
for each queried record: reads the rect from the PSMZ24 Z buffer (ZBP 7168, width 512), counts count-rect pixels
with Z <= the reference, `vis = open/(w*h)` or `max((open - wh/2)/(wh/2), 0)` when clipped, stored at source
`+0x40 + view*4`. The draw therefore uses the previous frame's visibility.

Draw `0x002E2868`: material from the query object's slot `+0x10` (`0x002E3578`, template at `0x00501420`): enum 7
(`0x48`), MODULATE, priority 7, ATST ALWAYS (AREF 0x14), Z test ALWAYS for queried glows and GEQUAL for far glows.
Texture FX 53 `shal` (class 0x10/0x40, renderer `+0x1024`) or FX 54 `mhal` (class 0x20, `+0x1028`), 64x64 from
EFFECTS.SSH; half size 180/100/350 cm; RGB `trunc(128 * normalize(colour))`, A `trunc(128 * vis)`. Renderer vfunc
`+0x278` = `0x003781A0` projects the light P and the two rotated axes (from the right/up columns of the view
matrix on the renderer matrix stack `+0x13E4`) and emits the strip P-dx-dy, P+dx-dy, P-dx+dy, P+dx+dy with the
Z of P, **twice**.

## Environment colour

`0x002ED490` also computes, per block, a terrain-sampled colour used for rider lighting brightness and for
effects (`+0x28` colours board trails as is; the snow context doubles its RGB).

- `0x003889F0` samples CPU-side textures (indexed4/indexed8 with the GS swizzle and palette permutation, or raw
  RGBA with alpha 0..128). Sample indices clamp inclusively to width/height, so a fetch can touch one texel past
  the last row/column (what data is read there is unconfirmed).
- `0x002EDB20` samples the base texture at the PS2 base UV and the light page at the PS2 light UV. The light alpha
  is doubled to form a strength; per RGB channel
  `target = (base - light) * tint * (lightAlpha * 2)` with tint (0.55, 0.535, 0.55); ratio `+0x38 = target/base`;
  alpha 0.5.
- Filters `0x002ED1D0`/`0x002ED338`: on the ground the colour keeps about 0.1 of the previous value and takes 0.9
  of the new target. A shared force-next flag makes the next eligible ground update immediate. Missing resident
  patch data fades toward white; rails keep the colour and set the flag.
- In the air it reads the live trajectory status (`trajectory+0x788`), predicted landing patch/time/UV and the
  elapsed time, and blends toward airborne white or toward the predicted landing colour.
- A patch is eligible only when its track is in state 6 and its chunk (`patch+0x156`) in state 3.

**(PS2)** Starting from a captured glide filter state, the next frame's four ambient floats are reproduced exactly;
the CPU texture data matches the game's cached texels.

## Rider lighting

### IRR.DAT

`DATA/WORLDS/IRR.DAT` is loaded by `0x0038ACD0` (`cIrradianceDataBase_Load`), which copies the name table and the
records into separate allocations. Format (little-endian): `u32 count`, `count` 8-byte names, `count` 160-byte
records of ten 4-float rows (RGBA lanes). The shipped file has 45 records; the GameCube `irrngc.dat` holds the same
values big-endian. `0x0038AC50` resolves a name to an index; `0x0038ABF8` returns `base + index*160`.

Row order (basis of each row, evaluated with the transformed normal):

| Row | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Term | 1 | X^2 | Y^2 | Z^2 | XY | XZ | YZ | X | Y | Z |

### Coefficient helpers (`src/render/particle.cpp` split)

| Address | Operation |
| --- | --- |
| `0x00389590` | `dest += (weight * modulation) * record` over ten rows; modulation in ARGB order, lanes RGBA; no clamp or normalization |
| `0x00389308` | project a directional RGB contribution into the rows (uses X^2-Y^2 and 3Z^2-1 forms; eleven constants at `0x004A09C4`..`0x004A09EC`); RGB lanes only, direction not normalized |
| `0x00389520` | wrapper for `0x00389308` with a direction and unit weight |
| `0x00389558` | ambient RGB contribution |
| `0x00389620` | fourth-lane-only accumulation |
| `0x00389730`, `0x003897A0`, `0x00389810` | bank sum, scale and copy-scale (VU add/mul) |
| `0x00389840` | rotate the quadratic, cross and linear rows by a 3x3 matrix over an inclusive lane range; constant row kept |
| `0x00389C38` | calls `0x00389590` then `0x00389CB8` |
| `0x00389CB8` | view-dependent rim (below) |

### Environment bank

Inside `0x002ED490`:

- `0x002ED5B4`..`0x002ED5DC`: selector `+0x24 = previous * 0.9 (+ 0.1 if rider+0x3FC != 0)`. `rider+0x3FC` is
  cleared by `0x00120F20`; getter/setter `0x00140C28`/`0x00140C30`. Its gameplay meaning is unconfirmed; it is 0
  in every inspected state **(PS2)**.
- `0x002EDA4C` builds the bank from Lighting references 0/1/2 (bright, dark, alternate) through
  `0x002EE318`/`0x002EE340`/`0x002EE368` -> `0x002EE010`, and the gain through `0x002EEFF0` (item `+0x48`).
  It passes the ratio `+0x38` to the brightness curve `0x002EDF00`.
- `0x002ED92C`..`0x002EDB18`: if the selector exceeds 0.1, the alternate bank is blended toward the previous
  state; otherwise `weight = brightness * gain` mixes bright and dark, then the result is blended with the previous
  bank using the incoming weight at `0x004A3B70` (gp+0xA80, 0.5). No clamps.

Brightness `0x002EDF00`: luma `0.299R + 0.587G + 0.114B` (alpha unused), clamped below 0.1 and above 0.45, in
between normalized by 0.35 and raised to 0.6001175642 through log/exp (wrappers `0x0040DA10`/`0x0040D758`, kernels
`0x0040E550`/`0x0040E048`).

`0x002EE010` resolves an empty reference (`0x004A53D0`, gp+0x22E0) to the per-course default IRR index at
`0x004A43C4` (gp+0x12D4) **(PS2)**: BPBR1 (3) on Metro-City and The Junction, APBR1 (12) on Snow Jam. An override
(`0x004A3B64`, gp+0xA74, returning `0x004A55B0` from `0x002EF0E8`) is 0 in every inspected state **(PS2)**.

### Lighting painter (type 11)

44-byte payload: rate, four 8-byte bank references, two scalars (gain, rim). A reference holds a name until it is
resolved, then a tag word (hex 123400) and the bank index **(PS2)**. Blend `0x002BD5A8` copies the four references
directly (keeping previous-reference slots) and blends the two scalars at `+0x48` (gain) and `+0x50` (rim) with the
squared weight. Compare `0x002BDE30` checks all four references (via `0x002BB100`) and both scalars. Reset stores
the empty reference in all four slots and scalars (1, 0.75). Getters: `0x002C15D0` returns `+0x48` (reached from
`0x002EEFF0` through vtable `+0x148`/`+0x14C`), `0x002C15D8` returns `+0x50` (reached from `0x002EEFA8`).

ARA1 has three identical payloads (APBR1, APDK1, APTN1, AOBR1; scalars 1 and 0.75). Metro-City has five payloads
that differ only in the bright bank (scalars 1 and 0.65, rate -0.05), selected by area. **(PS2)** Over a
2300-tick Metro-City race the selected reference follows the tree exactly for the human rider; computer riders run
their own blocks.

### Local lights

Authored lights are world nodes of kind 6 (ARA1: 190 records). Runtime fields used by the lighting code:

| Offset | Field |
| --- | --- |
| `+0x14` | intensity |
| `+0x18` | stored brightness (ranking) |
| `+0x1C` | radius |
| `+0x2C` | axis |
| `+0x38` | position |
| `+0x5C`, `+0x60` | cone cosine thresholds (outer/inner assignment not recorded) |
| `+0x64`, `+0x65` | distance and angular attenuation modes (signed bytes) |

Light kind: 1 spot, 2 point; kinds 0 and 3 contribute nothing to shading (kind 0 still ranks by its stored
brightness). **(PS2)** Light parameters do not change between savestates and match the authored records.

Geometric query `0x0038A530`: `d = lightPos - samplePos`, reject only if `|d|^2 > radius^2` (radius squared, so
negative radii act positive), then normalize; returns distance, inverse distance and the negative dot with the
axis. Coincident points give distance/inverse 1 and direction (0,0,0,1); rejection leaves outputs untouched.

Contribution `0x0038A6A8` (kinds 0 and 3 contribute nothing):

- Spot (kind 1, `0x0038A710`..`0x0038AA74` inside it): reject below the outer cosine. Fade: radius < 5000 or
  distance <= 3750 gives 1, else `1 - (distance - 3750) * 0.0008` (unclamped). Distance factor
  `min(100 * invDistance, 1)`, raised to 1/2/3 for modes 1/2/3 (other modes: 1), times intensity.
  Angular (p = the signed angular mode byte): inside the inner cone `cos^p`; between cones
  `inner^p * (cos - outer)/(inner - outer)`; powers 0..4 by explicit multiplication, others by squaring
  (negative = reciprocal, zero base special-cased). Final weight clamped to 0..5, times RGB, then projected with
  `0x00389520`/`0x00389308`.
- Point (kind 2, query `0x0038A618`, branch `0x0038AAA0`..`0x0038ABE0`): inclusive radius, the same inverse-distance
  modes and 5000/3750 fade, clamp 0..5, RGB, directional projection. Coincidence uses the EE divide saturation and
  a zero direction.

Selection (`0x00122088`): gets the posed primary bone (`0x0011FF48`) and asks `0x002F5B68` for up to 8 lights from
the rider's query scope (`rider+0x860`, list at `+0x210`/`+0x214`). It filters kind-6 nodes and ranks them with
`0x002F5D30` using `0x002F6168` (radius/cone query with the unnormalized-displacement dot then times inverse
distance, attenuation and intensity times stored brightness, no 0..5 clamp; kind 0 ranks by stored brightness,
kinds 1/2 by influence, others 0). Insertion keeps positive ranks in descending order; a new rank equal to
existing ones goes before them, but an equal rank at the cutoff of a full list is rejected. The result is stored
at `rider+0x794` (eight pointers).

Spatial candidates: `0x00120E50` refreshes the scope with `0x00332DB8` on the query bounds (`rider+0x400`/`+0x410`)
and then calls `0x00122088`. Bounds `0x0011E150`: eight corners from the rider's right/forward/up at +-150 cm
forward, +-100 cm sideways, +250/-50 cm up around `rider+0x110`, plus a sphere of radius 250. `0x00332DB8` walks up
to 8 region roots (20-byte records: signed exponent, three signed cell coordinates, root pointer); `0x00328360`
classifies a cell (scale from the exponent bits, padding 0.2, with asymmetric final tests); `0x0033B748`/
`0x00340DC0` visit node lists before children, partially covered children in Gray order 0,1,3,2,6,7,5,4 and fully
covered ones in 0..7, stopping partial recursion at exponent 11.

Refresh timing: `0x0012B788` iterates the riders and calls `0x00120E50`; it is called at `0x0026DD90` inside
`0x0026DBF0` (`cReplay_restoreFrame` in the decomp, which these notes describe as the world/stream update).
**(PS2)** In one run the refresh ran at ticks 369, 372, 375, 378, 381, and a retained list can hold a light that a
fresh query would drop. The world wrappers `0x0026CC48`/`0x0026CD20` and the deferred
`0x0026F850` (all in `src/replay/` in the current split) include stateful job gating; the selection code has no
tick counter, and a fixed period is unconfirmed.

### View-dependent rim `0x00389CB8`

1. Reconstruct the eye from the view matrix (transpose times negated translation, W forced to 1); direction =
   normalize(point - eye); horizontal magnitude.
2. `pitch = -atan(Z / horizontal)`; `yaw = pi/2 - asin(d)` with `d` the dot with the X axis (vector at
   `0x004FF140`, in .bss) over a denominator recomputed with a scalar sqrt, clamped to [-1, 1]; threshold 0.001;
   `2*pi - yaw` when Y < 0; yaw 0 when vertical (math callees `0x0031C228`, `0x0031C128`, sin/cos `0x0031BE50`).
3. Build rotations by -pitch about Y and -yaw about Z, multiply, transpose, apply a fixed axis conversion
   (initialized lazily), pack a 3x3.
4. Rim shape (fourth lane only): rows 0, 2, 3, 7 = 0.4954159856, -0.0 (from `0x004A43C0`), -1.4862500429,
   0.2046655864.
5. Rotate lane 3 with `0x00389840` (range 3..3) and add it into the bank's lane 3 scaled by
   `inputScale * 0.7500065565` (`0x004A0A08`, gp-0x26E8). RGB is untouched.

### Assembly `0x001220D8`

Result at `rider+0x7C0` (160 bytes):

```
bank  = copy(environment bank of the rider's block)          // 0x002EDFB8
rim(bank, primary bone point, view, painter rim scalar)       // 0x0011FF48, 0x002EEFA8, 0x00389CB8
for each of the 8 selected light pointers at rider+0x794:     // in order, null skipped
    0x0038A6A8(bank, light, point)
if (rider+0x77C) owner exists: its +0xD30 block adds ambient RGB (0x00389558)
    and a counted list of direction/colour pairs (0x00389520 / 0x00389308)
```

**(PS2)** At draw time the renderer's matrix stack head (`renderer+0x13E4`, view getter slot `+0x11C` =
`0x00395C68`) holds the camera's view matrix (outer camera `+0x40`); it is restored to identity after drawing, so
end-of-frame savestates show identity. That matrix is built in `0x0015E968`..`0x0015EAE8` inside `0x0015E668`:
quaternion `+0x30` to matrix, left-multiplied by the axis matrix at `0x004C53A0`
(`0,0,1,0; -1,0,0,0; 0,1,0,0; 0,0,0,1`), plus the negated eye `+0x20`. The Euler setter `0x00395750` (slot
`+0x10C`) and the copy setter `0x00395C38` (slot `+0x114`, used at `0x0022B23C` inside `0x0022B008` and at
`0x002D9260` inside `0x002D9130`) exist but are not the producer for the rider draw. Stack push/pop:
`0x003956E8`/`0x00395730`.

### Upload and per-vertex evaluation (VU1 program 2)

- The rider draw (inside `0x00122448`, at `0x001224C8`) calls graphics slot `+0x228`/`+0x22C` = `0x003954D0`,
  which copies the 160 bytes into `renderer+0x6BB0` (renderer vtable `0x00493260` **(PS2)**).
- `0x00310640` draws active model parts through renderer slot `+0x31C` = `0x0037A610`, which calls slot `+0x3E4`
  = `0x00396B40` (at `0x0037A6A0`) before its part loop. `0x00396B40` uploads the ten rows to VU1 data memory
  (V4-32 unpack) and starts program 2's coefficient-preparation entry, which multiplies all 40 floats by 255.
  Program 2's code is at `0x00434990` (.vutext); templates built at `0x00365968` inside `0x00364CD0` DMA-call it.
- Per vertex: decode packed signed 16-bit normals with ITOF15 (/32768), multiply by the first three columns of
  the vertex's weighted skin matrix (no inverse-transpose, no renormalization), evaluate the ten-term polynomial
  per lane, clamp 0..255 and truncate (FTOI0) into the vertex colour. Lane 3 is the rim highlight.
- `0x0037A610` calls `0x0037CBC8` at `0x0037A950` with 3, which reaches `0x003691B0` and writes TEX0.TFX = 3
  (HIGHLIGHT2), preserving other bits. Byte result: `RGB = min(255, (T.rgb * L.rgb >> 7) + L.a)`, `A = T.a`.
  **(PS2)** All rider texture descriptors are TFX 3 / TCC 1.
- Materials: model header `+0x48` is a signed material count; records are 20 bytes; texture handles resolve
  through `renderer+0x18F4`. Records with flag `0x8000` use blend enum 5 (`0x44`, at `0x0037A9A4`); others enum 1
  (`0x2A`, at `0x0037AA90`). Alternate draw modes and per-part depth/alpha state are not fully traced.

### Skinning palette

- `0x00310120`: matrix from the posed position/quaternion at geometry `+0x2C` (quaternion not normalized) into
  `+0x30`; columns scaled by geometry `+0x140` XYZW into `+0x34` (`+0x140` = (0.85, 0.85, 0.85, 1) **(PS2)**).
  `0x00310530` adds a late contact displacement to the pose and to both cached position columns.
- `0x00310640` multiplies each scaled pose by the inverse bind at geometry `+0x38` (`0x003106B8`..`0x00310778`)
  into `0x004FC420`, then the draw path calls renderer slot `+0x37C` = `0x00386BD0`.
- `0x00386BD0`: 12-byte group headers point to 4-byte influences (signed 16-bit percentage weight, 8-bit bone
  index); weight = int-to-float times 0.01f; the first matrix initializes, the rest accumulate; all 16 words; no
  normalization. Program 2 keeps the first three columns of each weighted matrix as the normal matrix; the
  projection matrices are a separate bank.
- **(PS2)** Rider geometry has 29 bone slots; slots 24/25 are the eyes of an inactive part.

## Rider shadows

Per visible rider (`rider+0xB18`) and tick, `0x001225F0` -> `0x00122898`:

- Fit `0x00374D00`: light `L = (0, 0, -1)`; `N` = the rider's up column (`rider+0x1C0`); `C` = midpoint of bones
  18/21 (feet); `A = normalize(N x L)`, `B = normalize(L x A)`; bones 5, 10, 15, 18, 21, 0 (head, hands, feet,
  hips) projected to light space with +-70 cm margins;
  `u = (A.p - A.C - minx)/w`, `v = (maxy - (B.p - B.C))/h`; a culling slab from the feet down 30 m.
- Silhouette: a 128x128 PSMCT16 texture per rider, the LOD-3 meshes drawn flat with value 38 (which reads back as
  32 through PSMCT16), painter's order by part slot, no depth test; board and bindings paint 0 while grounded
  (motion 0), 38 otherwise.
- Receivers `0x0038CA08`/`0x0038D448`: only near terrain patches (tier-2 and stitched lists), redrawn with the
  light layer's draw and blend `0x81` with As `0x80`, i.e. `Cd = max(Cd - T, 0)`, before fog and ScreenTint.

**(PS2)** Fits match the game's shadow objects; frame deltas are about (34, 33, 28.5) near the camera and
(20, 18, 23) when fogged. The `shad` texture (FX 50) is never loaded. The occluder part of the visibility test
`0x00122278` and PSMCT16 dithering are unconfirmed.

## Effects drawn after fog

Layer-1 producers, by the priority they store: priority 7 - snow emitters (`0x00370950` inside `0x003708C0`,
`0x00371380`), wake (`0x002DDC4C` inside `0x002DDAB8`), boost strips (`0x002E7BDC` inside `0x002E7A10`), light
halos, board sparks (`0x002DABC8`/`0x002DB478`), a depth-sorted `fog0` sprite list `0x002DBF98` called every frame
from `0x0022C708` (`cGame_renderFogVolumes`, which these notes also call the instance-list draw), `0x002D9130`
(vtable `0x00488664`, in the avalanche split), static models via `0x0037ECB0` (inside `0x0037E238`); priority 8 -
sun, air streamers `0x002EF950`, a timed full-screen 640x480 fade `0x002E47E8` (vtable `0x0048817C`, constructor
`0x002E4228`; the white fade of a forced reset, alpha from `+0x48`/`+0x54`/`+0x58`/`+0x5C`), models via
`0x0038057C` (inside `0x00380518`). The notes call `0x002D5778` that class's constructor; the decomp names it
`tActiveAvalancheNode_getFrameData`.

Rider FX container `RFX = *(rider+0x77C)`: components reset by `0x00111890`, updated by `0x00111948` and the rider
passes at `0x00128F20`..`0x001290F0` (inside `0x00128AF0`), in this order: `+0xD30` light list, `+0x3B0` wake,
`+0x470` board sparks, `+0x520` board track, `+0x610` boost, `+0x9C0` power-up aura, `+0xAD0` air streamers,
`+0xAF0` rival indicator, `+0xB00` locator beam, `+0xB40` snow FX, `+0xC70` fist sparkle, `+0xD20` cheat toggle.

- Board sparks (`+0x470`): update `0x002DABC8` each tick before the board track. Gates: speed > 277.778 cm/s;
  sparks when the surface record `+0x8C` is set (metal surfaces), glints also on rails (30 % of rail ticks, three
  `sprk` quads of 20..30 cm), grind chunks on surface 9 (chance `min(speed/1666.67*0.1, 0.1)`). The surface is
  `rider+0x438`, kept in the air. Kernel: `0x0036D428` age/seed, `0x0036D318` colours, `0x0036D1F0` velocities,
  `0x0036CEF8` emit box. Draw `0x002DB478`: chunks (GS `0x44`), then the kernel through renderer slot `+0x290`
  (`0x00380518`, VU1 program 4: 30 slots of up to 8 trail sprites 0.012 s apart, alpha falling 1/8 per sprite,
  half size capped at 64 px, GS `0x48`), then glints via `0x00377CF0`. Random draws use the visual LCG at
  `0x004A3AFC` (gp+0xA0C), and `0x003177F0` (`BXrand__Fv`, which the notes call the particle-birth generator)
  for chunk births.
- Fist sparkle (`+0xC70`): while `rider+0x350 > 0` and a punch clip is in its hit window, four `ospk` sprites
  (texture 24, GS `0x48`) are rebuilt each tick 8 cm along the hand axis.
- Impacts: the crash entry `0x0010EB30` and landings/rail attaches through `0x0010E910` call `0x00111AA0`, which
  spawns the snow impact `0x002E23E0` (kind 0) with strength = closing speed (for landings, `|rider+0x1E0|` before
  the landing response, read at `0x00139D54` inside `0x00139C88`). Lens snow splats (`0x002F3810`, spawned through
  `0x002E1598` -> `0x002F4118` -> `0x002F4260`) happen only when the Weather painter value exceeds 1.0
  (never on Snow Jam, whose range is 0..0.3). **(PS2)** Spark kernel words and impact strengths match captures.

## Open questions

- Whether `0x002C0408` is a query constructor or the painter factory switch (see above).
- The trigger of the mid-race Lighting wrapper re-seed.
- The fog depth-byte mapping and the terrain environment-map layer's destination alpha are not checked against a
  real GS framebuffer.
- Patch LOD selection (`0x0038B178`/`0x0038B190`) and the renderer-side instance visibility test.
- The world-job cadence that schedules local-light refreshes.
