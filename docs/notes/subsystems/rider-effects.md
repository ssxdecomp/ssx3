# Rider visual effects

Each rider owns a set of effect components that are rebuilt from the rider's pose, contact and control state
every game tick and drawn afterwards: a persistent textured track cut into the snow (board trail), a noise-driven
ribbon of disturbed snow beside the board (board wake), ten snow particle emitters (spray, chunks, impacts, cloud,
breath and others), and the boost ribbons. The updates run in fixed passes over all riders inside the rider
manager, share one small visual LCG, and hand their geometry to GS strip renderers or to the VU particle program.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

Hex constants that are not addresses are written with an `h` suffix (for example `3F800000h`). Positions are in
the game's Z-up centimetres.

## Where it lives

Source files are from the decomp's current split.

- `src/visualfx/boardtrailfx.cpp`: the board track. `0x002E81E8` (`cBoardTrailFX_initialize`), reset
  `0x002E8560`, sample admission `0x002E86F0`, eligibility `0x002E87E8`, update `0x002E8938`, draw window
  `0x002EA538`.
- `src/visualfx/boardwakefx.cpp`: the current split puts several effect classes in this one file:
  - wake: `0x002DCB88` (`cBoardWakeFX_cBoardWakeFX`), configuration `0x002DCF28`, frame driver `0x002DD0B8`,
    draw `0x002DDAB8`, row creation `0x002DDD30`, cursor/colour `0x002DE058`;
  - snow FX: profile constructor `0x002DE4A8`, board jitter `0x002DE398`, per-rider snow update `0x002DF920`,
    chunk emission `0x002E02B8`, SnowTrail `0x002E0EE8`, breath `0x002E1120`, impact `0x002E1598`, cloud
    `0x002E1A80`, impact set-up `0x002E23E0`;
  - boost: constructor `0x002E6640`, parameters and side history `0x002E66B8`, main ribbon `0x002E6C08`, draw
    `0x002E7A10`.
- `src/visualfx/boardsparkfx.cpp`: `0x002DA390` (`cBoardSparkFX_cBoardSparkFX`). The spark component is not
  described in this note.
- `src/render/particle.cpp`: the board-track GS passes `0x00386E78` with its helpers `0x00386D10` and
  `0x00386DD0`; the wake strip callback `0x003883B8` and strip submitter `0x003885E0`; the rider particle emitter
  class (`0x00370DC8` construction, `0x003710D0` birth update, `0x003717C0`, draw `0x00371380`).
- `src/render/graphicsman.cpp`: particle coefficient preparation (`0x0036CBF8`, `0x0036CE00`, `0x0036CE28`,
  `0x00370058`) and a second emitter class (`0x003705E0`, `0x00370018`, `0x00370788`, `0x003708C0`).
- `src/render/ps2graphicsman.cpp`: the texture binder `0x00368970`.
- `src/object/railmodifier.cpp`: the blend setter `0x00362478` and the deferred state builder `0x00363C20`
  (placement by the current split).
- `src/visualfx/renderstateman.cpp`: board-track texture ID set-up (inside `0x002EFF98` and `0x002F0000`).
- `src/visualfx/lensfx.cpp`: the environment-property loop `0x002ED490` and the breath environment reader
  `0x002EE6F0`.
- `src/worldpainter/worldpainterqueryctor.cpp`, `src/worldpainter/worldpaintermanquery.cpp`,
  `src/worldpainter/quadtree.cpp`, `asm/1BA100.s`: environment regions and properties (`0x002C0778`,
  `0x002C0A10`, `0x002C1608`, `0x002C1CD8`, `0x002BAF90`, `0x002BCAF8`, `0x002BD698`).
- `src/util/menu.cpp`: the wake noise helpers `0x002D18B0` and `0x002D1928` (placement by the current split).
- `src/ai/ai.cpp`: the rider manager `0x00128AF0`, which contains the per-rider effect loops.
- `src/main/debugmenu.cpp`: `0x0024B0E8` (`cBoardTrailMenu_cBoardTrailMenu`), the board-track tweakables menu.

## Scheduling and shared state

### Pass order

- Inside the rider manager `0x00128AF0`, the loop at `0x00128F80` updates **all riders' board tracks** before the
  loop at `0x001290A0` runs **all riders' snow FX** (`0x002DF920`). Several other effect loops run between them.
  So every rider's track update comes before any rider's snow update in a tick. The random-streams note lists the
  full pass order.
- Within one rider's `0x002DF920`, the emitters are called in this order:
  1. Chunky emitters 2 then 1 (small, then large);
  2. Rock 3;
  3. SnowTrail 0;
  4. RiderBreath 4;
  5. impacts: the selected one of 5/6, then the other as an inactive call. When both are inactive the order is
     6, 5;
  6. Cloudy 7, BodySnow 9, Kicker 8.
- Each emitter gets one birth call per tick, including inactive calls. Leaving out an emitter call shifts the
  shared LCG sequence for everything after it.

### Random streams

- **Visual LCG, gp+0xA0C (`0x004A3AFC`).** One word, stepped inline:
  `w = ((w * 18FCDh + E9507Ch) & 7FFFFFh) | 3F800000h`. The value used is the float with bits w, minus 1, which
  lies in [0, 1). The board track, the snow emitters and the breath emitter share it. It is separate from the
  gameplay generator.
  - Each committed track sample consumes exactly two steps.
  - Cloudy consumes its first draw even when airborne or otherwise unable to emit.
- **Presentation generator `0x003177F0` (`BXrand__Fv`, state `0x004FF018`).** It supplies the particle birth
  seeds and, for some constructions, the initial flipbook phase.
- **VU random.** Each retained birth seeds the particle program's own generator. That program makes nine draws per
  child (position, velocity, colour, size, lifetime), and these do not advance either CPU stream.

### Rider fields read by the effects

| Offset | Meaning | Used by |
|---|---|---|
| `+0x110` | target position, returned by the virtual getter `0x001408F0` (slot 28) | boost main ribbon |
| `+0x150` | detached flag (selects crash corners) | track |
| `+0x1E0` | velocity | track |
| `+0x1F0`, `+0x208`, `+0x214` | effective turn, extra lean, brake | wake targets |
| `+0x274` | presentation roll | wake control |
| `+0x2E8`, `+0x2FC` | speed-pickup window, boost amount | boost |
| `+0x320` | reverse stance | track, wake |
| `+0x330` | manual flag | track, boost, snow cache |
| `+0x370` | ground normal | track |
| `+0x438` | surface (material) type | track |
| `+0x454` | contact distance; negative means the board is sunk below the surface | track |
| `+0x460`, `+0x464` | contact point (x, y used for environment regions) | track, boost, breath |
| `+0x6C0` | interface vtable; its entry at `+0x38`/`+0x3C` is the environment-index getter `0x00140B80` | track, breath |
| `+0x77C` | motion object; the crash submode is at motion `+0x30` | track |
| `+0x780` | geometry; bone matrix banks at geometry `+0x30` (unit axes) and `+0x34` (axes times model scale) | all |
| `+0x784` | animation | track |
| `+0x86C` | environment index (what `0x00140B80` returns) | track, breath |
| `+0x8A4` | board bone index (23 in the observed riders) **(PS2)** | track, snow, boost |
| `+0x8A8` | head bone index (5 observed) **(PS2)** | breath |
| `+0x8B0`, `+0x8B8`, `+0x8E8`, `+0x918` | bone indices used for crash corners | track |
| `+0xAC4`, `+0xAD0`, `+0xAFC`, `+0xB00` | special-state words, meaning unknown | track |

The owning object for `+0x1F0`/`+0x208`/`+0x214`/`+0x274` is assumed to be the rider (unconfirmed). Bone
matrices are 64 bytes and indexed by bone number: axis 0 at `+0x00`, axis 2 at `+0x20`, translation at `+0x30`.
The unit-axis bank (geometry `+0x30`) and the scaled bank (geometry `+0x34`) have identical translations
**(PS2)**. Snow particles, wake unit axes and breath use `+0x30`. The board track and the wake's scaled board axis
use `+0x34`.

## Common rendering conventions

### Environment colour

The effect colour comes from the rider's current environment entry. The index comes from `0x00140B80`
(rider `+0x86C`), and the entry is an ARGB float4 at `0x004FA398 + index*0xF0`. The table is updated as world
lighting changes, so the colour baked into effect vertices changes over time **(PS2)**:

- At a Snow Jam glide savestate, the newest track slices hold RGBA (31, 39, 70, 127). That is the environment
  ARGB (0.5, 0.125412, 0.156419, 0.277877) times 255, truncated.
- Older retained slices are warmer.

### Texture IDs

The table `0x004891B0` has 12-byte entries that start with a four-character texture tag. The game's texture-ID
enum string gives the symbolic names.

| ID | Enum name | Tag | Used by |
|---|---|---|---|
| 5 | DYNAMICSPRY | `spry` | snow emitters |
| 6 | IMPACTSPRAY | `impt` | snow emitters |
| 14..21 | TUMBLE1..TUMBLE8 | `tmb1`..`tmb8` | chunk flipbooks (emitters 1, 2, 3) |
| 25 | BREATH | `brth` | breath emitter |
| 55 | BOARDTRAIL | `btrl` | board track, 128x64 RGBA |
| 56 | BOARDWAKE | `wake` | wake, 64x64 RGBA |
| 57..61 | YELLOW/ORANGE/RED/BLUE/PURPLERIBBON | `yrbn`, `orbn`, `rrbn`, `brbn`, `prbn` | boost, all 32x32 |

`brbn` (BLUERIBBON) actually contains a green luminous stripe.

### EFFECTS.SSH records

The effect textures are in `DATA/TEXTURES/EFFECTS.SSH`, an `SHPS` container.

- **Container.** The entry count is at `+8`. The directory starts at `+16` and has 8-byte entries (four-character
  name, offset).
- **Full-colour records.** These have a 16-byte header: a type byte (5 for 32-bit), a 3-byte extent (16 +
  w·h·4), and width/height as u16 at `+4`/`+6`. The texels are raw RGBA8 with alpha in GS range 0..128.
- **Indexed records.** Type 2 records use a type 33 (CSM1) palette whose index bits 3 and 4 are swapped (`brth`
  is 32x32 indexed). A palette chunk can be shorter than 256 colours, and its stored extent gives the real size.
  For example, `orbn` has 147.

### Texture binding and blend state

- **Texture binding.** The binder `0x00368970` turns a descriptor's TEX0 template into the final TEX0. Board-track
  and wake textures bind as TFX=0 (MODULATE) and TCC=1 (RGBA). The snow textures 5, 6, 14 and 25 were seen bound
  the same way **(PS2)**.
- **Blend enum.** The blend enum is stored in material word 4, bits 2..6. The deferred state builder (at
  `0x00363F30`..`0x00363F68` inside `0x00363C20`) extracts it and calls `0x00362478`, which dispatches through
  the table `0x00491FB0`:

  | Enum | Case | GS ALPHA | Equation (on framebuffer bytes, >>7) | Used by |
  |---|---|---|---|---|
  | 5 | `0x003624DC` inside `0x00362478` (loads 44h at `0x003624E4`) | 44h (A=Cs, B=Cd, C=As, D=Cd) | `((Cs−Cd)·As >> 7) + Cd` | track, wake, snow particles |
  | 7 | (not given) | 48h (A=Cs, B=0, C=As, D=Cd) | `(Cs·As >> 7) + Cd`, additive | boost strips |

- **Snow particle mapping.** Snow particle profiles store `BlendMode` 1, and the table `0x0044B420` maps entry 1
  to enum 5.
- **Colour arithmetic.** MODULATE computes `Cs = T·Cv >> 7` and `As = At·Av >> 7`, and saturates RGB at 255 before
  blending. All blending is integer arithmetic on the encoded framebuffer bytes.

### The strip VU1 program

The board track and the wake use the same VU1 microprogram, VU1 program 3, which is DMA'd from `.vutext` at
`0x00435BD0`. It interleaves two bands into a strip and fades only the integer vertex alpha:

```
fade_i  = fade_0 + i*step          (accumulated by repeated addition, unclamped)
alpha'  = ftoi0( itof0(alpha) * clamp(fade_i, 0, 1) )
```

- RGB, UVQ and position pass through unchanged.
- The common continuation then transforms positions, perspective-corrects UVQ and clips. It does no lighting and
  no other colour change.
- Because the accumulator is advanced by addition, `fade_0 + i*step` computed by multiplication rounds
  differently.
- Vertices are 48 bytes: UVQ floats, RGBA as four integers, then XYZW floats.

## Board track (cBoardTrailFX)

The persistent textured groove cut into the snow. It is separate from the SnowTrail spray.

### Object layout

| Offset | Content |
|---|---|
| `+0x00` | rider |
| `+0x04`, `+0x08` | left and right jitter (floats, from the visual LCG) |
| `+0x0C` | parity, toggled every update |
| `+0x10`..`+0x24` | six band pointers; each band is 54 vertices of 48 bytes (`0xA20` bytes) |
| `+0x8C`, `+0x90` | ring head, retained count (at most 54) |
| `+0x94` | phase: 0 stopped, 1 just restarted, 2 running |
| `+0x9C`, `+0xA0` | material depth, lip height |
| `+0xB0` | contact point at the last committed sample |
| `+0xC0`, `+0xD0` | previous direction, previous lateral |
| `+0xE0` | restart cooldown |

Bands in spatial order across the track are 2, 0, 3, 4, 1, 5 (outer edge, lip crest, trough, trough, lip crest,
outer edge). Their texture U values are 0, 0.25, 0.375, 0.625, 0.75, 1 in that order, and V alternates 0/1 per
ring slice.

### Tweakables

These are gp-relative globals. The labels are from the game's Board Trail debug menu (`0x0024B0E8`); entries
with no menu string are described by role.

| Address | Label / role | Default |
|---|---|---|
| `0x004A457C` | enable word (unconfirmed) | 1 |
| `0x004A4580` | Inner Width Scale | 5 |
| `0x004A4584` | Outer Width Scale | 2.9 |
| `0x004A4588` | Height Scale | 9 |
| `0x004A458C` | Depth to Height Scale | 0.2 |
| `0x004A4590`..`0x004A459C` | Packed / Loose / Powder / Deep Powder Depth Scale | 5, 0, −20, −40 |
| `0x004A45A0`..`0x004A45A8` | Top Bias Front / Behind / Clear | 0, 1000, 1000 |
| `0x004A45AC` | Inner Position Jitter | 3 |
| `0x004A45B0`..`0x004A45B8` | middle, inner and outer band U | 0.375, 0.25, 0 |
| `0x004A45BC`..`0x004A45C4` | Outer / Inner / Base Normal Offset | −0.5, 0, 0.25 |
| `0x004A45C8` | Num Fade Segments | 16 |
| `0x004A45CC` (gp+0x14DC) | Draw Fixup Layer | 1 |
| `0x004A45D0` | Use Slice Caps | 0 |
| `0x004A45D4` (gp+0x14E4) | bound texture ID (55, written at `0x002F0008` inside `0x002F0000`) | |
| `0x004A3B28`, `0x004A3B2C` | plane offset, backwards offset | 0, 5 |

The update also uses these float literals:

| Address | Value | Role |
|---|---|---|
| `0x0049F720` | 0.999 | turn cosine |
| `0x0049F724` | 0.01 | minimum speed |
| `0x0049F738` | π/4 | angle peak |
| `0x0049F73C` | 4/π | angle scale |
| `0x0049F744` | 0.0036 | speed scale |

The Top Bias and Normal Offset globals are not read by the track generator or renderer path.

### Eligibility (`0x002E87E8`)

- **Motion state** (read through `0x0011FE98`):
  - state 0 (ground) passes;
  - state 2 (wipeout/crash) passes only when the crash submode at motion `+0x30` is 0;
  - any other state, airborne included, passes only in the **special state** with `+0xB00` set. The special state
    is `+0xAC4` set, `+0xAD0` clear and `+0xAFC` set.
- **Animation.** Animation semantic 22 (read through `0x00312AA0`) suppresses tracks while sequence marker 0 is
  set and marker 1 is not. The markers are queried through `0x001446A0`.
- **Material.** A 14-entry jump table at `0x00487B40` selects the material depth from the surface type:

  | Surface type | Depth tweakable | Lip height (9 − depth·0.2) |
  |---|---|---|
  | 0, 5, 6, 12 | packed (5) | 8 |
  | 1 | loose (0) | 9 |
  | 2, 13 | powder (−20) | 13 |
  | 3 | deep powder (−40) | 17 |
  | 4, 7..11 | none: no track | |

### Update (`0x002E8938`)

**When ineligible**, the phase decides the action:

- Phase 0: nothing happens.
- Phase 1: the three slices reserved by the restart are discarded (head −3, count −3, floor 0).
- Phase 2: the track is closed.
  - The preceding slice's outer bands collapse onto its crest bands (3 and 2 onto 0, 4 and 5 onto 1).
  - Band 1's alpha at that slice is zeroed.
  - Every band's head slice becomes a copy of that band-1 vertex with alpha 0, which forms the end cap.

The phase then becomes 0.

**When eligible:**

1. If the phase is 0, the head first advances by 3.
2. The height is computed from the lip height formula above.
3. **Board corners.** X is the scaled board axis 0 and P the board position.
   - Ground motion, or the special state with `+0xB00`: the ends are `P ± 87.5·X`, and the corners are each end
     ± `17.5·axis2`.
   - With the manual flag set, one end moves 140 toward the other. Which end moves depends on whether animation
     semantics 23..30 (front manuals) disagree with the reverse-stance flag.
   - Otherwise (crash): the corners are the bones at `+0x8B0` and `+0x8B8`, then either the bones at
     `+0x918`/`+0x8E8` (when detached) or the two rear corners.
4. **Direction.**
   - d is the velocity normalised, or the previous direction when speed < 0.01. It is projected into the contact
     plane and renormalised. A zero vector stays zero because the reciprocal square root of 0 saturates to the
     largest float.
   - The lateral is `l = d × n`, flipped if its dot product with the previous lateral is negative.
5. **Corner selection.**
   - Each corner's lateral extent is `(corner − contact)·l`.
   - The corners with the strictly largest and smallest extent are chosen, testing candidates in order 1, 0, 3
     with 2 as the fallback. Both are projected onto the contact plane plus the plane offset.
   - In state 2 they are replaced by `contact + 0.75·extent·l + n·planeOffset`.
   - The head slice gets the max point in bands 2, 0 and 3, and the min point in bands 4, 1 and 5. This is the
     pending end.
6. **Shape and centre.**
   - `θ = atan(|along_max| / |across_max|)`, computed through `0x0031C228`.
   - `shape = clamp(θ·4/π)` below π/4, else `clamp(2 − θ·4/π)`.
   - If `speed·0.0036 ≤ 1`, shape is multiplied by it.
   - `centre = contact + n·planeOffset + d·shape·min(along_max, along_min)`,
     `a = centre + l·across_max`, `b = centre + l·across_min`.
7. **Preceding slice.** The slice before the head is rewritten, with `û = normalize(b − a)`,
   `pen = n·min(contactDistance, 0)` and jL/jR the retained jitters:

   ```
   band2 = a − û·2.9·(|min(contactDistance,0)| + 10) + 2·pen
   band0 = a − û·5·jL + n·height        band1 = b + û·5·jR + n·height
   band3 = a + pen                      band4 = b + pen
   band5 = b + û·2.9·(|min(contactDistance,0)| + 10) + 2·pen
   ```

8. **Colour.** The preceding and head slices of all bands get RGBA from the environment ARGB times 255,
   truncated and clamped.
9. **Backward-edge collapse.** If both head crest points lie behind the preceding slice along d, the head bands
   are set to the preceding crest points plus `d·5` (the backwards offset). If only one lies behind, that side's
   head bands collapse onto the other side's head position.
10. **Restart.** If the phase was 0:
    - a temporary end cap is written one slice before the preceding slice (a copy of band 1 with alpha 0, and the
      preceding slice's alpha is also zeroed);
    - the preceding slice's outer bands are collapsed;
    - count += 3 (at most 54), and the phase becomes 1.
11. **Commit test** (`0x002E86F0`, described below). On commit:
    - the lateral is stored;
    - two jitters are drawn, left then right. The step is at `0x002EA2C0`, inside `0x002E8938`:
      `j = 1 + 3·u`, where u is the LCG value;
    - the phase becomes 2, the head advances by 1 and the count by 1 (at most 54);
    - the new head slice copies the old head's payload.
12. The parity toggles and the direction is stored.

### Sample admission (`0x002E86F0`)

```
if cooldown > 0: cooldown -= 1; reject
if phase == 1: cooldown = 2; accept            (restart commits immediately)
elif |contact − lastContact| < (special ? 30 : 110) and cos(d, d_prev) >= 0.999: reject
lastContact = contact; accept
```

So a sample is committed after 110 cm of contact travel (30 cm in the special state) or on a turn sharper than
the 0.999 cosine. The track has no lifetime in seconds. It lives in a bounded 54-slice ring and fades by
segments.

### Draw window (`0x002EA538`)

```
if count < 2: none
start = head + 57 − count;  n = count − 2
if count > 50: start += count − 50;  n −= count − 50
if n < 2: none
start %= 54;  fade = 0;  step = 1 / NumFadeSegments
```

- At most 48 slices are sent, and the pending end is left out.
- The oldest slice has fade 0, and fade rises by 1/16 per slice.
- `0x002EA538` fills a descriptor for each trail (start `+0x04`, count `+0x08`, fade `+0x0C`, step `+0x10`) and
  passes the list to `0x00386E78`.

### GS pass sequence (`0x00386E78`)

`0x00386E78` runs each pass over the whole supplied list of trails; it does not run the full sequence rider by
rider. The texture is the bound ID 55: `0x002EFFAC` (inside `0x002EFF98`) loads it and `0x00386FD0` selects it.
The material blend enum is set to 5 at `0x00386FC8`. The `btrl` descriptor's TEX0 template (descriptor `+0x38`)
is `59C008000h`. After binding it becomes `59C00BAE9h`: MODULATE, RGBA, PSMCT32, 128x64, and the extra low bits
are the VRAM address **(PS2)**.

The GS treats larger Z as nearer. The TEST values below decode as: `30000h` means Z test ALWAYS; `50000h` means Z
GEQUAL; `3C000h` means Z ALWAYS with DATE=1, DATM=1; `54000h` means Z GEQUAL with DATE=1, DATM=0.

| Pass | Call site in `0x00386E78` | Bands | State | Effect |
|---|---|---|---|---|
| 1. Clear mask | `0x003872F8` | 0, 1 untextured | FRAME RGB mask `00FFFFFFh`, ZMSK=1, TEST `30000h`, alpha 0 | clears the framebuffer alpha bit under the crest-to-crest strip; no RGB or Z writes |
| 2. Mark visible top | `0x00387490` | 0, 1 untextured | TEST `50000h`, FBA=1, still alpha-only, no Z writes | sets the alpha bit where the top strip passes depth |
| 3. Clear terrain depth | `0x00387750` | 0, 1 untextured | ZMSK=0, TEST `3C000h`, FBA=0, viewport Z scale and bias 0 | writes the farthest depth and clears the bit, only where the bit was set |
| 4. Trough and lips | `0x00387A00`..`0x00387A80` | pairs (2,0), (0,3), (3,4), (4,1), (1,5), textured | viewport restored, FRAME unmasked, TEST `50000h`, FBA=1, Z writes on | draws the track and sets the alpha bit |
| 5. Fix gaps | `0x00387C30` | 0, 1 textured | TEST `54000h`, FBA=0 | fills pixels whose alpha bit is still clear; runs only if Draw Fixup Layer is set |

- **Fade parameters.** Passes 1 to 3 go through `0x00386D10` with both fade parameters 0, so their vertex alpha
  is 0. Passes 4 and 5 go through `0x00386DD0` with the trail's fade window.
- **Why the depth passes exist.** They let the sunken trough replace the terrain depth where the top of the track
  is visible. Without them, the five shaded strips against the unchanged terrain depth hide the centre and leave
  only the two raised lips visible.
- **Alpha tests.** With ATE=0, transparent texels are not discarded and still write depth and the destination
  alpha mask.

## Board wake (cBoardWakeFX)

A ribbon of rows spawned beside the board while carving. Each row holds a fan of per-column velocities that move
its render points until the row expires. The newest row's outer tip is also an input to
snow chunk emission.

### Configuration (`0x002DCF28`)

| Rider | Columns | Rows | Lifetime (s) |
|---|---|---|---|
| bound to an input device (human) | 5 | 32 | 1.25 |
| other | 4 | 22 | 0.8000000119 |

- It also computes five per-column vertical increments and initial texture V values.
- An existing render buffer is refreshed only under a quality-change condition (the condition itself is not
  described).
- Reset clears the count, head and phase.

### Ring and row layout

The effect owner reaches the ring through `+0x3B0` (records) and `+0x3B4` (retained count). Physics rows have a
`0x70`-byte stride:

| Row offset | Content |
|---|---|
| `+0x00`..`+0x40` | one velocity vector per column (16 bytes each) |
| `+0x50` | drag vector |
| `+0x60` | value supplied by the caller (initial growth term) |
| `+0x64` | age, zeroed at creation |

Separate render buffers hold 48-byte vertices per row and column band, with positions, UV, RGB and alpha.

Wake control fields on the wake object:

| Offset | Content |
|---|---|
| `+0x40` | row counter (drives U) |
| `+0x50` | point |
| `+0x60`, `+0x70` | fan coefficients (normal and side) |
| `+0x80` | drag direction |
| `+0x90` | amplitude |
| `+0x94` | alpha |

### Frame driver (`0x002DD0B8`)

It runs once per tick, in three stages.

1. **Aging** (`0x002DD0B8`..`0x002DD2A0`, expiry branch at `0x002DD378`).
   - Rows are processed newest first. Age rises by 1/60.
   - The first row strictly older than the lifetime truncates the count there and ends the pass. Later rows are
     left untouched.
   - Surviving render positions get the decaying drag contribution. Columns 1..N−1 also get their velocity term
     and their per-column vertical increment, and a short initial growth term comes from row `+0x60`.
   - The row's drag and value fields and its render UV, RGB and alpha are not changed.
2. **Targets** (`0x002DD2A4`..`0x002DD6F0`). The inputs are:
   - the scaled board axis (geometry `+0x34`), the unit axes and origin (geometry `+0x30`);
   - the ground normal and lateral, the velocity;
   - the effective turn `+0x1F0`, extra lean `+0x208`, brake `+0x214` and stance `+0x320`;
   - surface fields `+0x48`, `+0x4C` and `+0x84`.
3. **Control** (`0x002DD6F4`..`0x002DDA88`).
   - Gates on motion, roll (`+0x274`), strength, turn and material.
   - Reverses the side when the carve side changes.
   - Filters the vectors and amplitude 0.8/0.2 and the alpha 0.7/0.3.
   - Starts a new row every 50 cm, emits closing rows, and starts a wake with two initial rows of zero amplitude.
   - Each new row first calls the cursor advance (`0x002DE058`), then row creation (`0x002DDD30`).

### Row creation (`0x002DDD30`) and noise

- **Noise.** `0x002D18B0` samples a 161-float table at `0x00445AB0`, which repeats every 160 cells, and
  interpolates between entries. Its domain is a nonnegative wake phase.
- **Octaves.** `0x002D1928` sums octaves; row creation asks for 3. The loop's accumulation happens in a branch
  delay slot, and the last weighted sample is added after the loop. A matching rewrite must keep that final
  addition.
- **Row fields.** Per column, the fan velocity comes from the `+0x60`/`+0x70` coefficients scaled by the noise and
  by the amplitude `+0x90`. The last column gets an extra factor of 0.9. The drag vector comes from `+0x80` and the
  rider velocity. The caller's value is stored at `+0x60` and age `+0x64` is cleared.
- **Render anchors.** Each column's render anchor is `point − normal·5`. Alpha is `+0x94` converted to GS scale
  (·128).

### Cursor advance and colour (`0x002DE058`)

- `0x002DE058`..`0x002DE0D4`:
  - phase += 0.033333335, wrapping once at 4;
  - count saturates at the capacity;
  - head decrements with wrap.
- `0x002DE110`..`0x002DE348`:
  - each environment channel is doubled and clamped to [0, 1], then RGB = trunc(channel·128);
  - U is `c/2 − (64·trunc(c/128) + 32)`, where c is the row counter (a signed, repeating U);
  - the counter goes up once per row advance.

When a row is re-created, the U and RGB set at the advance are kept.

### Draw (`0x002DDAB8`)

`0x002DDAB8` is the render dispatch only. It does no physics.

1. It checks the suppression word gp+0x1438 (`0x004A4528`), rejects a ring with one row, and reads the column
   count.
2. The draw window (`0x002DDC68`..`0x002DDCE4`) takes the initial fade from the oldest row's age against the
   lifetime, the head, and a count limited to capacity − 2. The fade decreases per row.
3. It pushes a material with blend enum 5 and calls the graphics dispatcher's slot `+0x2D4`, which is
   `0x003883B8`. That function submits adjacent column pairs through `0x003885E0` with the strip VU1 program. The
   fade step is negative, and VU1 accumulates it row by row.
4. It restores the material-stack pointer.

The texture is ID 56 `wake`. The renderer table holds a handle (`675h`) that the texture manager resolves
through `manager + 8 + handle*4`. The TEX0 template is `598004000h` (64x64, PSMCT32, MODULATE, RGBA). In the
Snow Jam glide savestate the wake texture had no VRAM allocation **(PS2)**. No additive blend or brightness
multiplier is involved. The RGB is the doubled environment colour, which the GS can saturate.

### Consumer: chunk emission

`0x002E02B8` checks the surface's `+0x78` flag and the owner's count at `+0x3B4`. For a nonempty ring, the block
at `0x002E08FC`..`0x002E0938` (inside `0x002E02B8`) reads:

```
records + head*0x70 + (columns − 1)*0x10
```

That is the last column's velocity of the newest row. There is no new world query here. That vector is the
optional wake velocity for chunk emission, and it changes both the velocity construction and the later LCG
consumption. A ring with count > 0 counts as present even if the tip is zero. An empty ring takes the no-wake
branch.

## Snow particles (per-rider snow FX)

The snow FX object sits at `+0xB40` of the rider's effect parent **(PS2)**.

### Emitter profiles (`0x002DE4A8`)

The constructor `0x002DE4A8`..`0x002DF178` fills ten profiles (580 parameter words). The values match the
GameCube version's `cmrender.h` bit for bit.

| Index | Profile | Notes |
|---|---|---|
| 0 | SnowTrail | 36 retained births, two particles per birth |
| 1 | LargeChunky | NumFlipTextures 8, FlipTextureRate 30 |
| 2 | SmallChunky | 8 frames, rate 45 |
| 3 | Rock | 8 frames, rate 45 |
| 4 | RiderBreath | texture 25 |
| 5 | LargeImpact | |
| 6 | SmallImpact | |
| 7 | Cloudy | |
| 8 | Kicker | |
| 9 | BodySnow | |

Static emitters have single-frame sequences. All ten profiles have infinite duration.

The emitter colour is RGBA `(2·envR, 2·envG, 2·envB, 1)`. The particle path clamps RGB to 128 (GS scale) before
output.

### Rider cache (`0x002DF960`..`0x002DFB5C`, inside `0x002DF920`)

- Speed is the length of the velocity vector.
- The board frame is the unit-axis matrix (geometry `+0x30`) for the board bone at `+0x8A4`, with its centimetre
  origin. It is not multiplied by rider scale.
- The edge bias at `+0x12C` is usually 0. It is chosen from the manual flag `+0x330`, the animation and the
  stance. It is not the steering input.

### Producers

- **SnowTrail** (`0x002E0EE8`, board jitter `0x002DE398`).
  - It emits only when grounded, faster than 222.222229 cm/s, with surface `+0x58` allowing it and a suppression
    flag clear.
  - The point is the posed board origin plus 15 along board Y, followed by board-X and board-Z jitter.
  - The profile velocity, normal and speed-normal coefficients are applied in VU operation order.
- **Chunks** (`0x002E02B8`).
  - It covers ordinary carve and brake, the optional wake velocity, a landing burst, inactive slots and the
    chance tests, in a fixed random-draw order.
  - It produces SmallChunky 2, then LargeChunky 1.
  - Surface `+0x70`/`+0x74` are their chance scales. Surface `+0x78`/`+0x7C`/`+0x80` are wake-related.
- **Impact** (`0x002E1598`, set up by `0x002E23E0`).
  - It updates the retained strength `+0xE0`, build-up `+0x4` and alpha `+0x120`.
  - It emits an ordered pair of births and issues a secondary impact request through `0x002F4118`.
- **Cloudy** (`0x002E1A80`).
  - It uses a slip/turn/speed chance, height scatter along the board normal, a backward position offset and
    carve-side velocity.
  - It uses surface `+0x50`/`+0x54` and profile 7's velocity coefficients.
- **Breath** (`0x002E1120`): see the breath section below.

### Emitter object and birth ring

- **Class.** The live rider emitters are a `0x210`-byte class with vtable `0x004930D0` at `+0x1F8`, initialised
  by `0x00370DC8` **(PS2)**. Its fields:

  | Offset | Content |
  |---|---|
  | `+0x04` | texture base ID |
  | `+0x0C` | frame count |
  | `+0x10` | flipbook phase |
  | `+0x14` | flip rate |
  | `+0x200` | particle program mode |

- **Births.** The birth path is `0x003717C0`/`0x003710D0`. Birth seeds come from the presentation generator, and
  births are recorded in a ring. The velocity supplied by the caller is stored as given, and the
  birth position is not subtracted from it.
  - Birth positions, velocities and colours are interpolated between adjacent retained records within each birth
    group.
- **Phase.** `0x003710D0` advances the phase at `0x00371220`..`0x00371248` after every birth call, inactive calls
  included, using that call's elapsed time. The draw `0x00371380` reads the phase at
  `0x003713A8`..`0x003713C4` and selects one texture per emitter (base + phase). The animation is emitter-wide; it
  is not chosen per particle.
- **Fresh construction.** In `0x00370DC8`, the check at `0x00370DFC` skips randomisation for frame counts below 2.
  Otherwise, `0x00370E14` calls `BXrand__Fv`, and `0x00370E30`..`0x00370E48` forms
  `float((w & 7FFFFFh) | 3F800000h) − 1` times the frame count as the initial phase.
- **Savestate values.** At a Snow Jam savestate, chunk emitters 1/2/3 had phases 1.5/4.5/3.0, and the others
  0.666666687 **(PS2)**.
- **Second emitter class.** `0x003705E0` stores NumFlipTextures at `+0x180` and FlipTextureRate at `+0x188`, and
  `0x00370018` zeroes the phase at `+0x184`.
  - `0x00370788` adds `rate·elapsed` when the emitter's initial lifetime is nonzero.
  - `0x00370838`..`0x00370860` truncates for the frame comparison and resets the phase to zero on overflow, with
    no modulo remainder.
  - The draw (`0x00370A3C`..`0x00370A60` inside `0x003708C0`) picks base + trunc(phase) once per emitter.
  - This class is not the rider emitter class. Whether the rider class wraps its phase the same way is not stated.

### Particle program (VU1)

- **Program and modes.** The particle microprogram is the fifth `.vutext` DMA/MPG stream, loaded from
  `0x00439A40`. The emitter's `+0x200` word selects the entry point: 0 selects the normal path and nonzero selects
  a distinct alternate colour mode. All ten human emitters used the normal path in the glide, brake, jump and
  glide-later savestates that were checked **(PS2)**.
- **Coefficients.** Preparation (`0x0036CBF8`, `0x0036CE00`, `0x0036CE28`, `0x00370058`) scales source age by
  damping. It divides force by damping twice and the random velocity coefficients once.
- **Position.** Position uses the polynomial `−0.7300000190734863·t + 0.11299999803304672·t²` with
  `t = min(scaledAge, 2.7)`. It is not a gravity/drag integrator.
- **Size.** The billboard size is a half-extent. The projected half-size is clamped to 128 pixels per axis
  (absolute value, then a minimum against 128) in a 512x448 viewport **(PS2)**.
- **Zero-alpha quad.** Walking the whole history can emit one more quad than there are visible particles: the
  oldest record, with zero alpha.

## Breath

The breath emitter (profile 4, texture 25 `brth`) is updated by `0x002E1120`. `0x002DF920` calls it after
SnowTrail and before the impacts.

### State

The offsets are relative to the effect object that `0x002E1120` works on:

| Offset | Content |
|---|---|
| `+0x14` | emission accumulator |
| `+0x18` | breath-cycle phase (integer, toggles) |
| `+0x1C` | effort |
| `+0x20` | cycle clock |
| `+0x24` | cycle duration |
| `+0xBC` | cached speed |

The constructor zeroes the accumulator, phase, clock and duration (stores at `0x002DE610`, `0x002DE618`,
`0x002DE620` and `0x002DE628`, inside `0x002DE4A8`). No constructor store to effort `+0x1C` was found. A duration
of 1 seen in a savestate is therefore not a constructor default **(PS2)**.

### Update (`0x002E1120`)

1. **Speed gate.** If the cached speed `+0xBC` > 1111.111083984375 cm/s, the accumulator is reset and the call
   returns inactive. The breath cycle does not step.
2. **Effort.** The effort target is 1 when the animation class of channel 2 (through `0x00311AE8`) equals 30, and
   0 otherwise. Effort snaps up to the target. Above the target it falls by 0.0016666668 per call.
3. **Cycle clock.** The clock goes up by 1/60. When it reaches the duration, the clock resets to 0 and the phase
   toggles. The duration is 0.4 in the active phase and `(1 − effort)·0.6 + 0.4` otherwise.
4. **Environment scalar.** `0x002EE6F0` reads the environment scalar (see below). Then
   `alpha = clamp((effort + 0.5)·(1 − (T + 5)·0.04), 0, 2)`. The scalar behaves like a temperature: colder values
   give more visible breath (unconfirmed).
5. **Emission.**
   - If the phase is 0 or alpha ≤ 0.01999999955, the accumulator resets and an inactive request is submitted.
   - Otherwise the call steps the visual LCG and adds `(u·6 + 18)/60` to the accumulator.
   - It emits only when the accumulator > 1, subtracting 1. Otherwise the request is inactive and the accumulator
     is kept.
6. **Birth.**
   - The mouth position is the head matrix times `(−3, 0, 4, 1)`.
   - The direction is the head matrix times `(0, 0, 150)`, with the translation replaced first. The block at
     `0x002E13BC`..`0x002E13D4` copies `(0, 0, 0, 1)` from `0x004FF130` over the copied matrix's translation, so
     the direction is rotation only.
   - The profile's velocity, normal and speed scales are then applied.

### Environment property source

- **Reading the scalar.** The environment object's class pointer is at object `+4` (class `0x00484058`). Its
  vtable entry at `+0x180`/`+0x184` (`0x002C1608`) returns the property block at object `+0x30`. The block holds
  19 (current, target) float pairs, and breath reads pair 5.
  - The constructor `0x002BCAF8` sets pair 5 to 10/10.
  - At the Snow Jam start the current value was 9.99995136 and the target 10 **(PS2)**.
- **Blend** `0x002BD698` (class slot `+0x210`). For each of the 19 pairs:
  `current = (1 − w²)·current + w²·incoming`, `target = incoming`, with no clamp on w. The default hook
  `0x002BDA90` is called before and after, and does nothing.
- **Per-rider driver.** The rider code at `0x00121928` (inside `0x001218D0`) passes three things: the environment
  index (from `0x00140B80`), the coordinates rider `+0x460`/`+0x464`, and the sentinel −99999 from gp−0x7910
  (`0x0049B7E0`). `0x002ED490` loops over nine properties (the counter runs from 8 down to 0 inclusive) and calls
  the wrapper `0x002C0778` (slot 10 of the wrapper vtable `0x00483E00`).
- **Wrapper `0x002C0778`.** It keeps the accumulated travel distance in property object `+0` (this is not a time
  clock) and the last coordinates in wrapper `+0x8`/`+0xC`. Its branches:
  - the uninitialised −99999 sentinel;
  - explicit weight;
  - target distance / negative weight;
  - reset to default;
  - outside the map / default region;
  - the "current already exact" reset.
- **Region selection.** `0x002C0A10` calls `0x002BAF90`, which finds a leaf through the quadtree lookup
  `0x002C1CD8` and uses leaf `+4` as an index into the property-payload table.
  - The lookup transforms and truncates the coordinates, bounds them to unsigned 0..32767, walks encoded four-child
    nodes (keeping the X/Y bit order), and falls back to a default leaf.
- **Snow Jam data** **(PS2)**. The course tree has 125 nodes. Its three class-12 payloads have (transition, breath
  target) = (−0.1, 10), (−0.08, 2) and (−0.15, −2), so the breath scalar differs across the course. The starting
  region's weight is 0.1.

## Boost effect

### Construction

The side-history capacity is set at `0x002E6698`..`0x002E66A8` (inside `0x002E6640`): 18 when the rider's device
index is negative, 20 otherwise.

### Parameters (`0x002E66B8`..`0x002E68A4`)

- **Emission condition.** The effect emits when the motion state is not 1 (airborne) and either the boost amount
  `+0x2FC` or the speed-pickup window `+0x2E8` is positive.
- **Landing reset.** On the tick the rider lands (was airborne, now not), it clears the side count `+0x3A0`, the
  primary count (integer `+0x14`) and the primary distance (float `+0x18`).
- **Texture and scroll step.** Checked in this order:

  | Condition | Texture | Scroll step |
  |---|---|---|
  | tier 11 | 61 | 0.01 |
  | pickup > 0.01 | 60 | 0.01 |
  | debug pickup override | 60 | 0.01 |
  | tier ≥ 10 or debug high override | 59 | 0.01 |
  | tier ≥ 5 or debug medium override | 58 | 0.005 |
  | otherwise | 57 | 0.002 |

  An active pickup branches into `0x002E677C` (a delay-slot path) to get the 0.01 step. What the tier value is
  derived from is not described.
- **Size and fade.** Speed is `|velocity|`.
  - While emitting, with `a = clamp(max(pickup, boost), 0, 1)`: length = `(400 + 400·a)·(speed / 3333.3335)`,
    width = 50 at tier 11 and otherwise `6 + 9·a`, and alpha = 1.
  - Otherwise length, alpha and width are each multiplied by 0.95 per update.

### Side history (`0x002E68A8`..`0x002E6BEC`, inside `0x002E66B8`)

A 20-slot ring of left/right four-component positions.

- **While emitting.**
  - The cursor advances and the count grows up to the capacity.
  - The previous pair is copied into the new slot.
  - All 20 slots are pushed apart along the physical right vector: left −= 1.4·right, right += 1.4·right.
- **Otherwise,** the count shrinks with a signed rule: above 1 it decrements; above −2 it becomes 0; otherwise it
  increments.
- **Empty or disabled.** If the count ≤ 0, or the effect is disabled, the rest is skipped.
- **Newest pair.**
  - The two supplied bone translations are ordered by their projection on the physical right.
  - 0.7 times a reference bone translation is subtracted from both. The draw adds 0.7 times that translation back.
  - The inputs are pose bones 0, 23, 10 and 15 and the physical right/contact frame (their exact roles beyond the
    board bone are not described).
- **Scroll.** `scroll −= speed·(1/60)·step`, followed by a single ±1 correction (not a modulo).

### Main ribbon (`0x002E6C08`)

Thirty packed 28-byte rows (a distance plus two xyz endpoints), a ring cursor, the previous target position and a
continuous side vector. All three stages below run within one call to `0x002E6C08`. The address `0x002E6C6C`,
inside the seed stage, is referenced from data (possibly a jump-table target, unconfirmed); it is not the start
of a separate function.

1. **Seed** (`0x002E6C08`..`0x002E71B8`).
   - The stage runs only if length or primary distance > 0 and the velocity is nonzero.
   - The cursor moves backwards modulo 30. When 30 rows are full, the overwritten row's distance is subtracted;
     otherwise the count rises.
   - Travel is the distance between the current target position (virtual getter `0x001408F0`, rider `+0x110`)
     and the stored previous one.
   - Four anchors are built from the board bone matrix at ±75 along board X and ±17.5 along board Z. Switch stance
     negates X.
   - If the manual flag `+0x330` is set, one end moves by 150 along X. Semantics 23..28, 37 and 38 shift the rear
     pair forwards; all others shift the front pair backwards.
2. **Endpoints** (`0x002E71BC`..`0x002E7948`).
   - The side is `velocity × groundNormal`, kept sign-continuous with the previous side.
   - The four anchor offsets from the contact point `+0x460` are projected on the side and normalised by the
     largest absolute projection.
   - The min and max corners are chosen with an asymmetric 0.5 preference and strict/non-strict ties.
   - The chosen corners are projected to 10 cm above the contact plane.
3. **Tail** (`0x002E794C`..`0x002E79F4`). While the count is above its minimum and the distance exceeds the length,
   the oldest intervals are dropped. The minimum is 3 rows when length > 1, otherwise 0. The sample array itself
   is kept.

### Draw (`0x002E7A10`)

- **Gate.** The effect is drawn only if the side count ≠ 0, length ≥ 3, alpha ≥ 0.05 and an enable flag is set.
- **Vertex packets** (`0x002E7C3C`..`0x002E81B8`) use 48-byte vertices. Vertex alpha is `trunc(alpha·128)`.
- **Side strips** (two, when the count ≥ 2). For sample j of n:
  - position = sample + 0.7·reference ± right·width/2;
  - U is 0/1 and V = scroll + j/n;
  - alpha = `α·(1 − j²/(n−1)²)`, floored at 0.
- **Main strip** (when the count ≥ 2). With cumulative distance D_j and `f = D_j / min(length, primaryDistance)`:
  - V = scroll + f;
  - alpha = `clamp(α·(1 − f), 0, 1)`;
  - distances are read in linear row order, but endpoints are read through the ring (cursor + j). The draw keeps
    this asymmetry as is.
- **Blend.** Textures 57..61 bind as MODULATE/RGBA, and the strips use blend enum 7 (ALPHA 48h, additive).

## Unknowns

- The spark component (`0x002DA390`) is not described in this note.
- The meanings of the rider words `+0xAC4`, `+0xAD0`, `+0xAFC` and `+0xB00` behind the track's special state are
  unknown.
- How `0x002DD0B8` builds the wake coefficients `+0x60`/`+0x70`/`+0x80` is only partly described, and so is the
  quality-change condition for refreshing the wake render buffer.
- For the environment wrapper, the caller's blend weight, target selection and update cadence are not fully
  described. Reading breath pair 5 as a temperature is unconfirmed.
- The source of the boost tier, the enable flag checked by the boost draw, and the role of each boost pose bone are
  not described.
