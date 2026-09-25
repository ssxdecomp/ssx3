# Asset formats and their loaders

SSX 3 reads its data from `DATA/` on the disc: BIGF archives (some members RefPack-compressed), SSH texture
containers, models and animation banks in the character archives, one chunked world stream for the whole mountain,
and a set of fixed-layout tables and text files (character database, gear database, irradiance bank, input maps,
audio configuration, UI layouts and localised strings). This note describes each format through what the game's
loaders do with it: which function reads it, where the result goes, and the details the code depends on. Full
field layouts are in SSX-Library (see Credits); other notes cover the audio formats ([audio.md](audio.md)), the
LUN stage programs ([luno-vm.md](luno-vm.md)) and several consumers in detail, and are linked where relevant.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a
PS2 emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

Translation units as reported by the address lookup (several renderer functions currently sit in unrelated-looking
files):

- `src/world/worldview.cpp`: the PS2 chunk resolver's creation `0x003AAD98`, the SDB texture count read in
  `0x003AAE40`, and the record-kind dispatch `0x003AAE68` (texture and light-page cases).
- `src/render/particle.cpp` (current split): the texture record parser `0x0037C8C0`, texture creation `0x0037CAF8`,
  the handle lookup `0x0037D938`, and the irradiance helpers `0x00389590`, `0x0038ABF8`, `0x0038AC50`.
- `src/render/ps2graphicsman.cpp`: GS texture creation `0x00367440`, `0x00367260` (`cPSPGraphicsMan_NewBindTexID`),
  `0x00367150` (`cPSPGraphicsMan_NewNonBindTexID`).
- `src/render/irradiance.cpp`: `0x0038ACD0` (`cIrradianceDataBase_Load`).
- `src/replay/replay.cpp`: `0x0026DED8` (`cReplay_restoreObject`), a type dispatch to deserialising constructors
  (see "Record kinds").
- `src/animation/animmodel.cpp`: `0x0030D8B8` (`cAnimModel_addModelPartLOD`), `0x0030DBD0` (`cAnimModel_compile`),
  and the animation packet selection `0x00311318`.
- `src/ai/rider.cpp`: rider part assembly `0x0011BBE8`, `0x0011C138`, and texture-name resolution `0x0011BE88`.
- `src/be/beintstat.cpp`: the CHARDB copy inside `0x00149BB8`. `src/be/belibrary.cpp`: gear texture rule
  `0x0014B988`, gear icons `0x0014B700`, BOLT table getters `0x0014DC00`..`0x0014DC50`.
- `src/scripter/ssxscriptengine.cpp`: cutscene group loads `0x002797C8`, `0x00278B98`, `0x0027B370`, and
  `0x0027B0C0` (`cSSXScriptEngine_GetScriptFromCategory`).
- `src/sound/bankmonitor.cpp`: `MUSIC.INF` parsing `0x002B28C0` and the speech archive loads `0x002B0088`.
  `src/sound/ssxAudio.cpp`: per-location sound banks `0x00286CA8`.
- `src/object/modifierblock.cpp`: the sky dome draw `0x00353B10`.
- `src/worldpainter/quadtree.cpp` (`0x002C1CD8`) and `src/worldpainter/worldpainterqueryctor.cpp` (`0x002C0A10`):
  painter section queries. `asm/1BA100.s` (unsplit): the query wrapper `0x002BAF90` and the Fog painter
  constructor `0x002BC7C8`.
- `src/ui/uistatestack.cpp`: the LUI widget base constructor `0x0039FB30`.
- `src/hashvalue.cpp`: `0x00317670` (`GetHashValue32__FPc`).
- `src/main/ssxapp.cpp`: `0x00226B60` (`cSSXApp_loadInputMap`), see [input.md](input.md).

## Disc layout

| Path | Format | Read by / notes |
|---|---|---|
| `DATA/WORLDS/BAM.BIG` | BIGF holding `BAM.SDB`, `BAM.SSB`, `BAM.PHM`, `BAM.PSM` | the world stream (below) |
| `DATA/WORLDS/IRR.DAT` | irradiance bank | `0x0038ACD0` |
| `DATA/CHAR/MDLPS2.BIG` | character models | part assembly `0x0011C138` |
| `DATA/CHAR/<PREFIX>TXP.BIG` | per-character SSH textures | material binding by name, gear icons `0x0014B700` |
| `DATA/CHAR/ANM.BIG` | AFL animation banks | animation code, see [animation.md](animation.md) |
| `DATA/CHAR/BOLTPS2.DAT` | gear database | runtime DB `0x004A6750` |
| `DATA/CHAR/RWRDPS2.BIG`, `DATA/BE/RWRDPS2.DAT` | reward pictures (SSH), reward catalog | |
| `DATA/BE/CHARDB.DBL` | character database | copy inside `0x00149BB8` |
| `DATA/TEXTURES/*.SSH` | FX textures (`EFFECTS.SSH`, `PARTICLE.SSH`, `CRWD.SSH`) | FX texture table `0x004891B0` |
| `DATA/UI/*.LUI` + `*_1.SSH` | UI screen packages and their atlases (`FE`, `OV`, `GL`, `FL`) | LUI engine |
| `DATA/FONTS/*.SSH` | fonts and boot-logo images | |
| `DATA/LOCALE/*.LOC` | localised strings (`FEAMER`, `CMNAMER`, `CRAMER`, `OVAMER`) | by key hash |
| `DATA/CONFIG/INPUT.MAP`, `INPUT2.MAP` | input map expressions | [input.md](input.md) |
| `DATA/CONFIG/*.INF` | audio configuration | [audio.md](audio.md) |
| `DATA/CONFIG/SLUSOVF.BIG` | `overlay.dat` and `config.dat` | their loading is not covered here |
| `DATA/AUDIO/*.BIG`, `*.BNK` | music, speech, banks | [audio.md](audio.md) |
| `DATA/SCRIPTS/SCDAT.BIG` | cutscene (NIS) scripts | [set-pieces-cutscenes.md](set-pieces-cutscenes.md) |
| `DATA/MOVIES/*.MPC` | silent MPEG-2 movies (`ABC1`, `DBC2`, `EBC3`, each with a `WS` widescreen master) | |

The GameCube release uses the same formats with big-endian fields (for example SHPG instead of SHPS, AFB instead of
AFL, `irrngc.dat`), and MNF models instead of MPF.

## BIGF archives

- Header: `'BIGF'`, u32 LE archive size, u32 BE entry count, u32 BE header size, then entries of {u32 BE offset,
  u32 BE size, NUL-terminated path}. Offsets are relative to the archive start.
- Archives nest: the speech archives contain `headers.big` / `langhead.big`, and `SCDAT.BIG` contains one `.big`
  load group per cutscene script.
- Some entries have size 0 and a wildcard-like name (for example a `*.bnk` entry in each music archive).
- Members can be RefPack-compressed (for example texture containers). See SSX-Library's `Refpack` for the
  compression format.
- Loaders that build archive names at run time: `%s%08d.big` at `0x00481C68` (cutscene groups, `0x002797C8`),
  `%sheaders.big` `0x004832D8` and `%slanghead.big` `0x004832E8` (speech, `0x002B0088`).

## SSH texture containers

- `SHPS` (PS2) containers are little-endian: an image count and per-image offsets, each image a named shape record.
  (The GameCube `SHPG` keeps its count, offsets and dimensions big-endian even though some header fields use the
  other order.)
- Each shape record has a format byte: 1 and 2 are 4-bit and 8-bit paletted, 5 is 32-bit RGBA. Width and height
  are at `+4`/`+6`. The palette follows as its own record (for example the 32x32 `brth` texture is a
  type-2 image with a type-33 palette).
- **Palettes.** Palettes are stored in the GS CSM1 order (index bits 3 and 4 swapped), short palettes included.
  They can hold any used colour count (for example 98 or 147 entries), and their stored size includes alignment
  and swizzle padding, so the stored extent, not the used count, bounds a palette.
- **Swizzle.** Flag `0x2000` marks PSMT8 texels stored swizzled (the reward pictures in `RWRDPS2.BIG`).
- **Colour domain.** Alpha is the GS range 0..128 (128 = opaque). The rider textures (8-bit CLUT) hold colour at half
  intensity (128 = 1.0) and are drawn with the TEX0 function HIGHLIGHT2: the rider draw `0x0037A610` calls
  `0x0037CBC8` with argument 3, which forwards to `0x003691B0` to set TEX0.TFX. See [rendering.md](rendering.md).
- **(PS2)** Loaded textures stay in EE main memory and are uploaded per draw, so the equipped rider textures can be
  identified by the texel data resident in RAM.

### Texture manager and handles

- The renderer object is `*(0x004A5B80)` (gp+0x2A90). Its texture manager is at renderer `+0x18F4`, with 2000 slots
  at `manager + 8 + 4*handle`.
- **Explicit handle.** `0x00367440` stores the texture in slot `handle`; `0x00367260`
  (`cPSPGraphicsMan_NewBindTexID`) allocates a new 0x58-byte `NBTexInfo` there. There is no lookup of an earlier
  entry: loading the same id again replaces it.
- **Dynamic handle.** A handle < 0 takes a free slot through `0x00367150` (`cPSPGraphicsMan_NewNonBindTexID`),
  using the free list at `+0x1F48`. Dynamic handles are 1500..1999.
- **Lookup.** Renderer vtable slot `+0x1CC` resolves to `0x0037D938`: `descriptor = *(manager + 8 + 4*handle)`.
- **(PS2)** FX and UI textures observed in memory use dynamic handles (`part` at 5F5h, the OV.LUI `UITPage` at 656h,
  `wake` at 675h).
- **FX texture table** `0x004891B0`: 12-byte entries by FX texture id, starting with a packed four-character tag.
  Examples: id 25 `brth`, 51/52 `sun1`/`sun2`, 55 `btrl`, 56 `wake`, 57..61 the boost ribbons (`yrbn`, `orbn`,
  `rrbn`, `brbn`, `prbn`). The board trail's setup (`0x002EFFAC` inside `0x002EFF98`) reads id 55, `0x002F0008`
  (inside `0x002F0000`) stores it at `0x004A45D4` (gp+0x14E4), and `0x00386FD0` (inside `0x00386E78`) selects it.

## The world stream (`BAM.BIG`)

The whole mountain is one stream. `BAM.SDB` is the directory of locations, `BAM.SSB` holds the records in chunks,
and `BAM.PHM`/`BAM.PSM` hold resource names. Streaming (which location is resident when) is described in
[world-streaming.md](world-streaming.md).

- **Framing.** The stream uses CBXS/CEND framing with little-endian compressed block extents. A record can span
  compressed blocks. See SSX-Library's `SSBHandler`.
- **SDB.** An 80-byte header, then 88-byte location records. The third u32 after a record's name is the inclusive
  final chunk index of the location (not its first chunk). Header u16 `+0x2A` is the number of world textures and
  `+0x2C` the number of light pages (788 and 623 on the disc). SSX-Library's `SDBHandler` reads these two values as
  unknown bytes; the code below gives them their meaning.
- **Resource ids.** A record's word `+4` is `(rid << 8) | track`. The track (`& 0xFF`) is the SDB location index,
  numbered differently from the location table (see [world-streaming.md](world-streaming.md)).
- **Names.** `BAM.PHM` and `BAM.PSM` hold matching resource-id and name arrays in five groups: terrain 0, instances 1,
  models 2, splines 3, collision 4. PHM entries are 16 bytes; PSM string groups are 4-byte aligned. Whether retail
  code reads them is not established.
- **Units.** Centimetres, Z up.

### Chunk resolver and record kinds

The PS2 chunk resolver (the class name string `cPS2ChunkResolve` is at `0x00494F70`; the resolver is created at
`0x003AAD98`) dispatches the 23 record kinds through the table at `0x00494FB0`; the cases sit in `0x003AAE68`.

| Kind | Content | What the loader does |
|---|---|---|
| 0 | material | starts with the s16 texture id |
| 2 | model (MDR) | |
| 3 | instance: matrix, model, scale, baked vertex colours | on read completion the location's instances enter the activation octree (`0x00328C20`) |
| 6 | local lights | |
| 7 | light-glow sources, 80 bytes | |
| 8 | rail splines | see [rails.md](rails.md) |
| 9 | texture | `0x003AAF5C`: renderer slot, name `strm_tex` (`0x00494F88`), handle = rid |
| 10 | light page | `0x003AAF88`: name `strm_lpg` (`0x00494F98`), handle = texture count + rid |
| 12 | collision meshes and sphere trees | see [collision.md](collision.md) |
| 14 | AIP path bank | delivered to the rider code (`0x0012A340`) |
| 15 | painter record | see "Painter records" |
| 16 | stage: LUN programs, handler rows and the instance-to-collision descriptor table | see [luno-vm.md](luno-vm.md), [collision.md](collision.md) |
| 18 | anchor locators for cutscenes | |
| 20 | per-location sound banks | rid 0 goes to bank slot 8, rid 1 to slot 9 (`0x00286CA8`) **(PS2)** |

- A second type dispatch, `0x0026DED8` (`cReplay_restoreObject`), switches on kinds 0..22 through the table at
  `0x004816C0` and calls constructors: kind 8 `0x00341548` (rails), 14 `0x0034ED88` (AI paths), 16 `0x00350F08`
  (collision bindings), 17 `0x00356E60` (course-progress objects), 21 `0x00349DB0` (course spine). One reading calls
  it the world loader's record dispatch; a later correction describes `0x0026DED8` as a saved-component loading path
  that reads a type and calls deserialising constructors. How it relates to the resolver is unresolved.

### World textures and light pages (kinds 9 and 10)

- The world has one texture table. Every kind-9 and kind-10 record sits on the global track 255, and the resource id
  is global: kind-9 ids 0..787, kind-10 ids 0..622.
- **Texture registration.** The kind-9 case (`0x003AAF5C` inside `0x003AAE68`) calls the renderer (`*(0x004A5B80)`,
  vtable at `+0x10D8`, slot `+0x170`, which in the PS2 renderer vtable `0x00493260` is `0x0037C8C0`) with the record,
  the name `strm_tex` and handle = rid (record word `+4 >> 8`). `0x0037C8C0` parses the shape header (128-byte
  header, format byte as above, width/height at `+4`/`+6`) and creates the GS texture through `0x0037CAF8` ->
  `0x00367440`.
- **Light pages.** The kind-10 case (`0x003AAF88`) does the same with `strm_lpg` and handle = resolver `+0x10` + rid.
  Resolver `+0x10` is the SDB texture count (read at `0x003AAE54` inside `0x003AAE40`), so light pages use handles
  788..1410, after the textures.
- **Sharing.** A texture id can appear in many locations' chunks. On the disc every copy of an id is byte-identical
  (6,203 kind-9 records for 788 ids). Since draws name the handle and a reload replaces the slot, a texture shared by
  several resident locations is one texture. Each light page belongs to exactly one location.
- **Use.** A material names its texture by id. A terrain patch carries its base texture id and light page id (below).

### Terrain patches

- A PS2 terrain record is 432 bytes. It holds 16 float4 bicubic coefficients from `+0x40`, in reverse power-basis
  order, in centimetres in the Z-up world basis.
- The lighting rectangle is at `+0x10`, the base UV corners at `+0x20`, the base texture id at `+0x1A0` and the light
  page id at `+0x1A2` (the renderer also reads a third layer index at `+0x1A4`). In a loaded patch the resource
  word is at `+0x150`.
- Authored flag bit 0 marks a collision candidate; streaming adds the active bit `0x40` at run time.
- See SSX-Library's `WorldPatch`, and [rendering.md](rendering.md) and [collision.md](collision.md) for the
  consumers.

### Helper geometry

Models named `mdl_...trig...` / `mdl_...trigger...` (for example `mdl_ARA1_startfireTrig_1000`) are trigger-helper
geometry: they have triangles and materials but are not rendered or collided as scenery. Names are not an
authoritative classification: the kind-16 collision descriptor and the runtime instance flags decide (static
instances draw only when `(flags & 3) == 3`, collector `0x0022A5A0`).

### Sky locations

- `BAM.SDB` lists five sky locations, `ASKY` .. `ESKY`, one per mountain area.
- Each sky chunk holds nine kind-9 textures (one 256x256 top and eight 256x128 panels, 8-bit paletted), nine kind-0
  materials, one kind-2 model `mdl_?SKY_SkyTop1` (21 meshes, 365 vertices, 323 triangles) and one kind-3 instance
  with an identity matrix, unit scale and 365 baked vertex colours (all 16/31, the unity multiplier).
- The model is only about 3 m across; it is not placed in the world. The draw `0x00353B10` copies the identity matrix
  at `0x004FF1A0`, replaces its translation row with the camera position (from `0x002D1C20`), pushes a modified
  render state and draws the instance with flag `0x5420`. The debug toggle "Disable Sky Box" is at `0x004A452C`
  (gp+0x143C).
- Every vertex normal points inward and mirrored panels reverse the strip winding. Material short 7 is 25 for the
  top, 27 for the lower panels and 31 for the four horizon panels, whose upper texels are fully transparent.
- **(PS2)** At the ARA1 start the SkyBox object (vtable `0x0048F008`) holds region index 10, which is ASKY.
- `mdl_<AREA>_<X>_skybox_trigger` helper instances switch the sky at peak transitions; the dome swap `0x0022DE98`
  walks the sky region list (indices 44..48).

### Painter records (kind 15)

- A painter record begins with the values 10h, 0Eh, 40h and thirteen section offsets for painter types 1..13
  (5 Fog, 6 glare, 7 ScreenTint, 8 SkyBox on/off weight, 9 Sun, 11 Lighting, 12 breath/weather).
- A section is `header_size, count, 0xC, (type, payload_offset) x count`, then a spatial quadtree, then the payloads.
- **Query.** `0x002C1CD8` (reached through `0x002BAF90`) subtracts the origin X/Y, multiplies by the stored scale,
  converts with truncation and accepts integer coordinates 0..32767. Out-of-range points return an explicit outside
  leaf. Nodes are 8 bytes; a low bit in the first halfword marks an internal node, whose four halfwords are child
  indices shifted left one bit, and successive high bits of the doubled 15-bit X/Y choose the quadrant.
- **Payload.** `0x002C0A10` reads the leaf's second word: `FFFFFFFFh` means no payload, otherwise it indexes the
  section's 8-byte (type, payload pointer) table.
- **Fog payload.** 7 floats: blend rate, density, near (cm), far (cm), R, G, B. (Earlier reading called the second
  value a mode; it is a float density.) The Fog painter class (vtable `0x00484FE0`, constructor `0x002BC7C8`)
  defaults to near 3000, far 30000 and colour (0.43, 0.55, 0.71). **(PS2)** At the ARA1 start the live objects hold
  entry 0: near 30 m, far 100 m, colour (0.70, 0.82, 1.00).
- See [rendering.md](rendering.md) for the painter driver and each payload's use.

## Character models (`MDLPS2.BIG`)

- **Naming.** Files are named by an internal prefix (for example `arielle_*` for Allegra, `rocco_*` for Nate). A gear
  entry names up to four LOD models (H, M, L, Shdw) or one `_NIS` model.
- **Loading.** `0x0011BBE8` collects the equipped gear entries, and `0x0011C138` adds each entry's four LOD models by
  name at its part slot through `0x0030D8B8` (`cAnimModel_addModelPartLOD`). The first model of a file id makes
  the part. Rider init (`0x0011C61C` inside `0x0011C298`) hides slots 5, 6, 8, 9 and 11 (the cutscene head,
  eyes, both cutscene hands and the PDA).
- **Header fix-ups (PS2).** A loaded part's model header matches its `MDLPS2.BIG` LOD0 header byte for byte except
  bytes 56..67, which the loader patches.
- **Variants.** A part's model header comes from its variant table (`+0x1C`, 16-byte entries {header, material
  names, flags, ...}), not always entry 0.
- **Materials.** The model header gives a signed material count and the location of the 20-byte material records.
  A material binds the loaded texture whose SSH entry name equals the material name (`suit`,
  `boot`, `head`, `bord`, `alph`, `eat*`, ...).
- **Texture names.** In a gear entry's texture name, each `$` takes the character at the same position from another
  equipped entry of the same group (`0x0011BE88`, `0x0014B988`); for example a top `zoe_Suit_C01_$$$` and a bottom
  `zoe_Suit_$$$_D01` give `zoe_suit_c01_d01`. Cheat skins use the names unchanged.
- **Morphs.** In the PS2 models, morph targets follow each vertex chunk as VIF packets: an `UNPACK V4-8` of
  {count, 0, 0, 0}, then {dx, dy, dz, slot} with slot = 3 x the chunk vertex. Positions are `V3-32` floats in
  centimetres. **(PS2)** One morph unit is 4 mm.
- **Skeleton.** `0x0030DBD0` (`cAnimModel_compile`) sorts parts by file id and builds the bind data; see
  [animation.md](animation.md).
- See SSX-Library's `SSX3PS2MPF` for the file layout.

## Animation banks (AFL)

- `DATA/CHAR/ANM.BIG` holds little-endian AFL directories (magic `134Ch`); the GameCube `anmb.big` has big-endian AFB
  directories (magic `4213h`).
- Curves use Float24 coefficients; full-rate samples are 16-bit.
- Where two packet segments overlap at a boundary, `0x00311318` selects the first row of the next packet.
- Cutscene load groups carry their own AFL banks (below).

## Irradiance bank (`IRR.DAT`)

`0x0038ACD0` (`cIrradianceDataBase_Load`) reads `u32 count`, `count` 8-byte names and `count` 160-byte records (ten
rows of four floats), and copies the name table and the records into separate allocations. `0x0038AC50` resolves a
name, `0x0038ABF8` addresses a record by the 160-byte stride, and `0x00389590` accumulates a record with a weight
and an ARGB modulation into the RGBA-lane bank. The disc file has 45 records. World Lighting painter payloads refer
to records by name. See [rendering.md](rendering.md) for the row basis and evaluation.

## Character and gear databases

- **`CHARDB.DBL`.** 10 rows of 0x88 bytes, copied by the code at `0x00149C84` (inside `0x00149BB8`) to
  `0x00530970`. The row index is the character id. Fields and their readers are in
  [characters-frontend.md](characters-frontend.md). The display name is the string `kT_CHAR<Name>` (getter
  `0x0014EEC8`).
- **`BOLTPS2.DAT`.** Loaded into the runtime database at `0x004A6750`: 30 character buckets (0..9 riders, 10..29
  cheat skins) of 56-byte gear entries, plus three tables: equip rules (12-byte rows), cutscene-model to race-model
  pairs (getters `0x0014DC00`/`0x0014DC10`) and default-outfit rows (`0x0014DC40`/`0x0014DC50`). The entry layout
  and the equip logic are in [characters-frontend.md](characters-frontend.md).
- **Gear icons** come from the character's `TXP.BIG` (`0x0014B700`; none for ids >= 10).

## UI packages (`.LUI`) and fonts

- A package is `<NAME>.LUI` plus its atlas `<NAME>_1.SSH`, whose images are the atlas pages: `FE` front end, `OV`
  in-game overlay, `GL` game load, `FL` front-end-bound loading and stats screens.
- Individual screens are stored compressed.
- A screen is identified by the hash of its name, the same hash as the LOC keys below (for example `hud` is
  `00006FB4h`, `22control` is `0A65D25Ch`, `popup` is `007767C0h`).
- **Format.** Coordinates are a 640x480 frame. Elements have a frame-0 state record (`21h` property pairs, or `20h`
  binding an animation), later timeline events, and animations of `50h` records with `51h` tracks interpolated
  linearly. Details are in [characters-frontend.md](characters-frontend.md).
- **Widgets.** The base constructor `0x0039FB30` sets the item kind table (`+0x6C` = 4, `+0x70` = 6) and the flags
  `+0x14` (bits 1, 3, 6 set; bits 0, 2, 4, 5, 7 clear). Orientation (bit 0) and wrap (bit 7) come from the LUI data:
  their setters `0x003A4AD8` and `0x003A4AA8` are never called by game code.
- **Fonts.** Bitmap fonts (for example FEFONT) come from SHPS/FNTS files with SFN glyph metric tables. `FLOAD.SSH`,
  `GLOAD.SSH` and `SPLASH.SSH` each hold only the 512x512 boot logo.

## Localised strings (`.LOC`)

- Files: `DATA/LOCALE/FEAMER.LOC` (front end, including biographies), `CMNAMER.LOC` (common: character names, load
  hints, course descriptions), `CRAMER.LOC` (credits), `OVAMER.LOC` (in-game overlay).
- **Layout.** A `LOCH` header whose u32 at `+0x10` is the offset of the string block, a `LOCT` table (tag at `+0x14`,
  pairs from `+0x24`) of (key hash, string index) u32 pairs, and a `LOCL` block with a count at `+0x0C`, u32 string
  offsets from `+0x10` (relative to the block) and NUL-terminated UTF-16LE strings.
- **Keys.** The key is the hash of the `kT_` identifier:

```
h = 0
for each byte c: h = (h << 4) + c; g = h & F0000000h; if g: h ^= (g >> 23) ^ g
```

- Code stores keys as hashes; for example the Big Challenge table `0x0043EE10` holds title, objective and
  description hashes, and the career message records at `0x004C6C08` hold subject and body key hashes.
- Hashes can collide: `kT_HELPBRA2` hashes like `kT_HELPCBA2`, and the Metro-City help text is stored under
  `kT_HELPBRA2Blah`.
- The runtime function that hashes these names is not identified here; `0x00317670` (`GetHashValue32__FPc`) is the
  hash the cheat-code handler `0x00187D38` uses on lowercased codes, and may be the same one (unconfirmed).

## Cutscene scripts (`SCDAT.BIG`)

- `scmaster.dat`: `u32 count` (167), then per script {play count, name hash, offset into `scmasterdbg.dat`};
  `scmasterdbg.dat` holds the names.
- `NNNNNNNN.big`: one load group per script (`scrN.isb`, optional `anmN.afl`, `sndN.bnk`), streamed on demand by
  `0x002797C8` with the name format at `0x00481C68`.
- `scdat_main.big` is resident; `scdat_<LOC>.big` is preloaded with a location (`0x00278B98` -> `0x0027B370`) with one
  combined AFL and sound bank; `scfilter<LOC>.dat` holds the location's choice lists read by `0x0027B0C0`
  (`cSSXScriptEngine_GetScriptFromCategory`).
- The `.isb` script format is in [set-pieces-cutscenes.md](set-pieces-cutscenes.md).

## Configuration text files

- **`MUSIC.INF`** is parsed by `0x002B28C0` into `cSongConfiguration` objects (0xAC bytes, constructor defaults
  `0x002B1A98`), with case-insensitive keys. `PLAYLIST.INF`, `MIX.INF`, `BANKS.INF`, `CROWD.INF` and `SPEECH.INF`
  sit beside it. See [audio.md](audio.md).
- **`INPUT.MAP` / `INPUT2.MAP`** are compiled at load; see [input.md](input.md).

## Credits

Our understanding of the SSX 3 asset formats comes from GlitcherOG's SSX-Library
(https://github.com/GlitcherOG/SSX-Library, GPL-3.0), in particular its world (`SSBHandler`, `SDBHandler`,
`WorldPatch`, `WorldSSH`), compression (`Refpack`), texture (`OldShapeHandler`) and model (`SSX3PS2MPF`, `SSX3GCMNF`)
readers. No SSX-Library code is included here. This note only describes the formats through what the game's loaders
do with them; see SSX-Library for the full layouts.
