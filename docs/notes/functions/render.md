<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/render/

## `src/render/ps2graphicsman.cpp`

Segment `0x00367150`-`0x003698E0`.

- **`0x00368138`** - Chains the static GS restore packet at `0x0044B200`; used at the tail of the glare pass. *[static]*
- **`0x00368970`** - Texture binder: builds the final GS TEX0 for a texture descriptor from the template at descriptor +0x38, adding the VRAM address bits (e.g. template 0x000000059C008000 becomes 0x000000059C00BAE9 for the board trail texture: TFX=0 MODULATE, TCC=1 RGBA, PSMCT32, 128x64). *[static]*
- **`0x003691B0`** - Writes the TEX0.TFX field (bits 35..36) of a texture descriptor, preserving the other bits. *[static]*

## `src/render/graphicsman.cpp`

Segment `0x003698E0`-`0x00370C60`.

- **`0x0036A428`** - Fog depth palette builder: projects fog near/far into depth bins, caches the settings and fills a 256-entry CLUT; the upload follows at `0x0036AA24`. First step of the fog composite `0x0036AC00`. *[static]*
  - `0x0036A478`: Projection block (to `0x0036A618`): transforms (0,0,d,1) by four projection columns, divides by W, truncates Z, shifts right 8, clamps 0..255; packs fog RGB*255 truncated. Cache lookup follows at `0x0036A61C`. *[static]*
  - `0x0036A6EC`: CLUT fill loop (to `0x0036AA20`): equation 0 integer linear, 1 seventh-order exponential polynomial, 2 squares the density term first; 0.1 density scale; result clamped 0..1, *128, packed with RGB; CLUT index bits 3/4 swapped; min bin span 1. *[static]*
- **`0x0036AA60`** - Fog palette upload/setup preceding the fog depth pass; not a scene colour/depth copy. *[static]*
- **`0x0036ABA0`** - Copies the fog globals into the per-view render context at +0x6C64 (near, far, equation, density, then alpha/RGB). Run from renderer vfunc `0x00386640`. *[static]*
- **`0x0036AC00`** - Fog composite pass: builds the depth CLUT (`0x0036A428`), prepares the depth image (`0x0036AA60`/`0x0036AE20`) and draws the final fog sprite (`0x0036B158`). Palette alpha is scene transmittance: out = fog + (((scene - fog)*alpha) >> 7), clamped; 128 keeps the scene, 0 gives fog. Called by `0x00363490` after layer 0; the sun glow/flare draws after it. *[PS2]*
- **`0x0036AE20`** - Fog intermediate depth pass: writes the Z high byte into framebuffer alpha, so scene alpha = (rawZ >> 8) & 255 with RGB unchanged. *[static]*
  - `0x0036AF10`: Packet block (to `0x0036AFD8`): FRAME_1 PSMCT16 FBMSK 0x3FFF, TEX0_1 PSMZ16 DECAL/RGBA, TEXA TA0=0/TA1=128, PABE 0, PRIM 0x116. *[static]*
  - `0x0036AFF0`: Second packet block (to `0x0036B048`) with the same GS modes. *[static]*
  - `0x0036B04C`: Sprite strip loop (to `0x0036B0E4`): columns = width/8, one 8-px sprite per iteration, UV (0.5,0.5)..(8.5,height+0.5) shifting 16 px per step, destination X starting 8 px past the origin; 12.4 fixed-point coords. *[static]*
- **`0x0036B158`** - Fog final pass: draws a T8H CLUT-textured sprite blended over the scene. *[static]*
  - `0x0036B300`: Emits ALPHA_1 = 1 ((Cd-Cs)*As>>7 + Cs) and PABE = 0 for the fog sprite (to `0x0036B35C`); containment assumed. *[unconfirmed]*
  - `0x0036B330`: Emits TEST_1 = 0x70000 (ZTE on, ZTST GREATER) for the fog sprite (with `0x0036B334`); containment assumed. *[unconfirmed]*
  - `0x0036B374`: Emits TEX0_1 PSM T8H (27), TCC 1, TFX DECAL, PRIM 0x156 and RGBAQ 0x3F80000080808080 (to `0x0036B3E4`); containment assumed. *[unconfirmed]*
  - `0x0036B440`: Sets both sprite vertices' Z to 0xFFFF (to `0x0036B464`), so fog applies only where scene depth < 65535; nearer pixels fail GREATER and keep scene RGB. Containment assumed. *[unconfirmed]*
- **`0x0036B9D8`** - Glare downsample: bilinear column-sprite copy of the 512x448 viewport into the 256x256 L0 level, or halving of a level. L0 uses eight 32-px column sprites, UV (0.5+2x, 0.5+1.75y), MODULATE trunc(FrameSource*127.5). Halving takes four jittered bilinear samples (J=32), each MODULATE trunc(trunc(Copy*127.5)/4), sample 0 written and 1..3 added (ALPHA Cs+Cd, FIX 128). Columns = dstW/32; size 1 << the value at `0x004A43D0` (gp+0x12E0). *[PS2]*
- **`0x0036C188`** - Glare threshold: untextured sprites over L0 with ALPHA (Cd - Cs)*FIX >> 7, where Cs = trunc(Cutoff*127.5) and FIX = trunc(PostCutoffScale (`0x004A43D8`, gp+0x12E8)*127.5); colour clamps to 0..255. *[PS2]*
- **`0x0036C398`** - Glare composite: 16 column sprites blending a glare level back onto the frame, Cd*FIX>>7 + Cs with FIX = trunc(FrameBlend*127.5) (so each composite also scales the frame), texture MODULATE by (A,A,A,A). UV u = 0.5 + x*W/512, v = y*H/448 (no half-texel on v). *[PS2]*
- **`0x0036C740`** - Copies the glare globals (`0x004A43D4`..`0x004A43E4` and `0x004A43F0`/`0x004A43F4`, i.e. gp+0x12E4..0x12F4 and gp+0x1300/0x1304) into the render context at +0x6CD4 + view*0x1C. *[static]*
- **`0x0036C790`** - Framebuffer glare/bloom pass (world painter type 6), per view, after layer 1 and before ScreenTint. Returns if Enable (`0x004A43C8`, gp+0x12D8) is 0 or all A = trunc(127.5*BT0..BT3) are 0. L0 is 256x256 PSMCT24 in the Z buffer (block ctx+0x5A80<<5 = 7168): copy `0x0036B9D8`, threshold `0x0036C188`, levels halved to 128/64/32 by `0x0036B9D8`, composite `0x0036C398` where A[i] != 0. Tail restores FRAME/XYOFFSET and chains `0x00368138`. *[PS2]*
- **`0x0036CBF8`** - Particle kernel init / emitter coefficient preparation: age step = Duration * Damp / NumParticles, force divided by damping^2, random velocity divided by damping. Related to `0x0036CE00`, `0x0036CE28` and `0x00370058`. *[static]*
- **`0x0036CCB8`** - Seeds a static particle emitter with 9 visual-RNG draws (`0x003177F0`, draw sites `0x0036CCE4`..`0x0036CDCC`); runs for set-piece emitters when track sections activate and from particle effect creation `0x003705E0`. Per-emitter LFSR seeding details are inferred. *[PS2]*
  - `0x0036CCE4`: First of the 9 emitter-seed visual-RNG draw sites (range to `0x0036CDCC`). *[PS2]*
  - `0x0036CDCC`: Last of the emitter-seed visual-RNG draw sites (range from `0x0036CCE4`). *[PS2]*
- **`0x0036CE00`** - Particle emitter coefficient preparation routine (with `0x0036CBF8`, `0x0036CE28`, `0x00370058`). *[static]*
- **`0x0036CE28`** - Particle emitter coefficient preparation routine (with `0x0036CBF8`, `0x0036CE00`, `0x00370058`). *[static]*
- **`0x0036CEF8`** - Spark kernel emission box: +/-row2*10/15 and +/-row0*10/90 of the scaled board matrix. *[PS2]*
- **`0x0036D1F0`** - Spark kernel velocity setup. *[PS2]*
- **`0x0036D318`** - Spark kernel colour setup: (77,77,255,153) -> (255,51,51,102); magenta variant for Tricky. *[PS2]*
- **`0x0036D3E8`** - Advances the particle kernel age by dt * Damp. *[static]*
- **`0x0036D428`** - Spark kernel age/seed advance, run every tick. *[PS2]*
- **`0x00370018`** - Initializes the emitter flipbook phase (+0x184) to zero for the `0x003705E0` emitter class. *[static]*
- **`0x00370058`** - Applies the instance matrix to particles (snow VU equations); listed with the emitter coefficient preparation routines `0x0036CBF8`, `0x0036CE00`, `0x0036CE28`. *[static]*
- **`0x003705E0`** - Particle emitter setup for builtin-16 particle effects: remaining time = Duration + Life + LifeR/2; passes Duration (not lifetime) to `0x0036CBF8`; stores NumFlipTextures at emitter +0x180 and FlipTextureRate at +0x188; calls `0x0036CCB8` to seed emitters. This class (with `0x00370788`/`0x003708C0`) is not the live rider snow emitter. *[static]*
- **`0x00370788`** - Emitter update for the `0x003705E0` class: with Duration >= 0 it only advances kernel age (`0x0036D3E8`) and never runs continuous birth; steps the shared flipbook phase += rate*elapsed when the initial lifetime is nonzero, resetting to 0 on overflow (no modulo). Not used by the live rider snow emitter class `0x004930D0` (which uses `0x003710D0`). *[static]*
  - `0x00370838`: Truncates the phase for the frame-count compare and resets it to zero on overflow (to `0x00370860`). *[static]*
- **`0x003708C0`** - Routine of the non-rider emitter class paired with `0x00370788` (the `0x003705E0` class); the exact role is unconfirmed. The live rider snow emitter does not use it. *[static]*
  - `0x00370950`: Emitter draw path, called with a3=7 (render priority 7, drawn after the fog composite). *[static]*
  - `0x00370A3C`: Draw path (to `0x00370A60`) selecting texture = base texture id + integer flipbook phase once per emitter; the rider emitter draws with `0x00371380` instead. *[static]*

## `src/render/particle.cpp`

Segment `0x00370C60`-`0x0038ACD0`.

- **`0x00370DC8`** - Constructor/initializer of the 0x210-byte particle emitter class: randomizes the initial flipbook phase from the visual RNG `0x003177F0`. Used for builtin-26 particle trail creation (9 + 1 visual-RNG seeds with `0x0036CCB8`) and for seeding set-piece emitters in the section pass. *[PS2]*
  - `0x00370DFC`: Skips flipbook phase randomization when frame count < 2. *[static]*
  - `0x00370E14`: Calls visual RNG `0x003177F0` for the initial flipbook phase. *[static]*
  - `0x00370E1C`: Return site of the visual-RNG draw that seeds the emitter (one draw per emitter, on top of the 9 from `0x0036CCB8`). *[PS2]*
  - `0x00370E30`: Builds a [0,1) float from the RNG word, ((w&0x7FFFFF)|0x3F800000)-1, and scales it by frame count (to `0x00370E48`). *[static]*
- **`0x003710D0`** - Particle emitter birth update, used by the live rider snow emitter (class `0x004930D0`), DynamicParticle effects, board-spark grind chunks (`0x002E8938`) and rider snow FX (`0x002DF920`). Makes one visual-RNG draw per active emitter per tick (return address `0x003711D0`) and advances the flipbook phase (emitter +0x10) after each birth call using the call's F12 elapsed. Used with the birth store `0x003717C0`. *[PS2]*
  - `0x003711D0`: Return address of the per-emitter per-tick visual-RNG draw (all riders' snow, sprays and set pieces). *[PS2]*
  - `0x00371220`: Advances the rider emitter flipbook phase (to `0x00371248`), including for inactive births. *[PS2]*
- **`0x00371380`** - Rider snow emitter draw (class `0x004930D0`), called with a3=7 (render priority 7); reads the flipbook phase at `0x003713A8`..`0x003713C4` to select the texture. *[PS2]*
  - `0x003713A8`: Reads the emitter flipbook phase (to `0x003713C4`) for texture selection. *[PS2]*
- **`0x003717C0`** - Particle birth request: consumes the particle program seeds from the visual RNG and fills the birth ring, storing the supplied vector directly (no subtraction of birth position). Used with `0x003710D0`. *[static]*
- **`0x00374D00`** - Rider shadow projection fit: light L = (0,0,-1), N = rider up column (rider +0x1C0), C = feet midpoint (bones 18/21); A = normalize(N x L), B = normalize(L x A). Bones 5,10,15,18,21,0 are fitted in light space with +/-70 cm margins; UV u = (A.p-A.C-minx)/w, v = (maxy-(B.p-B.C))/h; culling slab extends 30 m down from the feet. *[PS2]*
- **`0x00376A70`** - Render set-viewport(x, y, w, h): clamps y = max(y, top*448) and h = min(h, height*448); mode 1 draws 3D into lines 56..392 with black bars. *[PS2]*
- **`0x00376C58`** - Render set-projection: builds the perspective matrix with reverse depth. GS x scale = 0.5*w/tan(fov), y = x*1.3333*448/512 (1.3333 at `0x004A0940` (gp-0x27B0)), then multiplied by the widescreen scales ctx+0x6BA0/+0x6BA4 (normalised copies at +0x5860/+0x5874); keeps the 4:3 vertical angle (Hor+), GS centre 2048/2048. Depth format ctx+0x5A40 == 0x31 (PSMZ24) selects range 16777215, else 65535; slope = (-range*near)/(far-near), offset = -far*slope + viewport depth offset; projected W is view-space Z. *[PS2]*
- **`0x00377950`** - Render context set-widescreen-mode (vtable +0x140), called from `0x00228C08`: stores the mode at ctx+0x6B94 plus top/height/x-scale/y-scale. Mode 0: 0, 1, 1, 1; mode 1 (16:9 letterbox): 0.125, 0.75, 0.75, 0.75; mode 2 (anamorphic): 0, 1, 0.75, 1. *[PS2]*
- **`0x00377CF0`** - Renderer sprite draw helper, used by the sun glow and board-spark glints. *[static]*
- **`0x003781A0`** - Renderer vfunc +0x278, the sprite submit used by the LightGlow draw `0x002E2868`: projects a glow centre and rotated corners (light + size*(cos a*right + sin a*up) and light + size*(-sin a*right + cos a*up), right/up from the world->view matrix at renderer +0x13E4) and emits the halo strip P-dx-dy, P+dx-dy, P-dx+dy, P+dx+dy with ST 0/1 and P's Z, twice (t2=2). *[static]*
- **`0x00379860`** - GPU quad submission (used by the boost HUD). *[static]*
- **`0x0037A610`** - Renderer vtable slot 0x31C: model part draw used for riders, invoked by `0x00310640` for active parts. Calls slot 0x3E4 (coefficient upload `0x00396B40`) before its part loop, sets TFX HIGHLIGHT2 via `0x0037CBC8`, and picks blend enum 5 for batches with material flag 0x8000 (hair/TopB secondary batch), else blend enum 1. *[static]*
  - `0x0037A6A0`: Call to renderer slot 0x3E4 (coefficient upload `0x00396B40`) before the part draw loop. *[static]*
  - `0x0037A94C`: Rider material setup: TEX0 TFX=3 (HIGHLIGHT2), TCC=1; RGB = texture*lighting/128 + lighting alpha (rim), clamped; alpha from the texture. *[static]*
  - `0x0037A950`: Call to `0x0037CBC8` with a2=3, selecting TFX HIGHLIGHT2 for the material texture. *[static]*
  - `0x0037A9A4`: Selects blend enum 5 for batches whose material flag has 0x8000. *[static]*
  - `0x0037AA90`: Selects blend enum 1 for ordinary batches. *[static]*
- **`0x0037CBC8`** - Sets a material's texture function by forwarding to `0x003691B0`; a2=3 selects HIGHLIGHT2. *[static]*
- **`0x0037D938`** - Renderer texture descriptor lookup (renderer vtable slot +0x1CC). *[static]*
- **`0x0037DBE8`** - Outcode / view-volume test for a world point, used by the sun and light glows. *[static]*
- **`0x0037DD20`** - Projects a point to integer screen x/y in the 512x448 viewport and 24-bit Z (2^24 at the 30 cm near plane, 0 at the far plane); pixel = trunc(continuous - 0.5). *[static]*
- **`0x0037E238`** - Static model draw. TFX0 MODULATE with the VIF UNPACK V4-5 colour: Cs = T*(c5<<3)>>7, As = Ta*(bit15<<7)>>7. Per-instance distance fade comes from f12 into the FIX alpha; all alpha tests use AFAIL FB_ONLY. *[static]*
  - `0x0037ECB0`: Static-model draw path that uses render priority 7. *[static]*
  - `0x0037F2A4`: Material state setup (to `0x0037F6C8`): model header +0x10 bit3 selects additive 0x48 with ATST GREATER 20; else material +0x0C & 0x660000 selects the blend class; AFAIL FB_ONLY. *[static]*
- **`0x00380518`** - Renderer slot 0x290: VU1 particle burst / spark kernel sprite draw with VU1 program 4 entry 0. 30 slots x up to 8 trail sprites 0.012 s apart, colour per slot, alpha fading 1/8 per drawn sprite, half size capped at 64 px, GS ALPHA 0x48. *[static]*
  - `0x0038057C`: Draw path that uses render priority 8. *[static]*
- **`0x003807A0`** - VU1 particle trail sprite draw (used by set pieces). *[static]*
- **`0x00382760`** - Frame-flip state machine; state 2 (after the whole frame) runs the registered renderer callbacks (see `0x003866E0`). *[static]*
- **`0x00382AF0`** - Contains the NTSC display set-up block below, which positions the picture from the screen-position setting. *[PS2]*
  - `0x00382DC0`: NTSC display set-up block: DISPLAY DX = 636 + 5 + 8x (VCK, 2560 per line), DY = 50 - 2y (480 lines) from the screen position; one step = 1/320 of the width right, 1/240 of the height up (2 lines per step). *[PS2]*
- **`0x00386640`** - Renderer vfunc that copies the per-view post-process parameters: fog `0x0036ABA0`, ScreenTint `0x00390458`, glare `0x0036C740`. *[static]*
- **`0x00386688`** - Copies the active matrix (context +0x6AF0) into the per-view projection at +0x5930. *[static]*
- **`0x003866E0`** - Renderer vfunc 0x3A8: registers a renderer callback (run by the frame-flip state machine `0x00382760`). *[static]*
- **`0x00386BD0`** - Renderer vtable slot 0x37C: builds the rider skin palette as a weighted sum of matrices. 12-byte influence-group headers point to 4-byte influences (signed 16-bit percent weight, 8-bit bone index); weight converted with VITOF0 then multiplied by 0.01f (0x3C23D70A). First matrix initialises the result, later ones accumulate (VU order), all 16 words, no normalisation; the first 3 columns also serve as the normal palette. Called from `0x00310640` after the pose (`0x00310120`) and bind-product (`0x003106CC`) stages. *[static]*
- **`0x00386D10`** - Board-track band submit helper with both fade parameters 0 (vertex alpha 0), used by the three preparatory passes at `0x003872F8`, `0x00387490`, `0x00387750`; FBA overrides the alpha high bit during the visible-top pass. *[static]*
- **`0x00386DD0`** - Board-track band submit helper using the per-trail fade parameters, used by the five shaded strips (`0x00387A00`..`0x00387A80`) and the gap fixup `0x00387C30`. *[static]*
- **`0x00386E78`** - Board-track renderer: submits the mask/depth/shaded/fixup pass sequence once for the whole list of trails (each trail descriptor carries its ring draw window; not one sequence per rider). Order: clear mask, mark visible top, clear terrain depth, shaded strips, gap fixup (if `0x004A45CC` (gp+0x14DC) is set). All GS alpha tests are off (ATE=0), so transparent texels still write depth/dest-alpha; GS uses larger Z for nearer. *[static]*
  - `0x00386FC8`: Track material setup sets blend enum 5 (standard source-alpha) in material word4 bits 2..6, decoded later by the deferred state builder at `0x00363F30`. *[static]*
  - `0x00386FD0`: Track material setup selects the board-trail (btrl) texture held at `0x004A45D4` (gp+0x14E4). *[static]*
  - `0x003872F8`: Pass 1, clear track mask: bands 0,1 untextured, FRAME RGB mask 0x00FFFFFF, ZMSK=1, TEST 0x30000 (depth always), vertex alpha 0 via `0x00386D10`; clears the dest-alpha high bit under the top strip. *[static]*
  - `0x00387490`: Pass 2, mark visible top: bands 0,1 untextured, TEST 0x50000 (GEQUAL), FBA=1 sets the alpha high bit where depth passes; alpha-only, no depth writes; uses `0x00386D10`. *[static]*
  - `0x00387750`: Pass 3, write far depth under the visible top so the sunken centre shows: ZMSK=0, TEST 0x3C000 (always, DATE=1, DATM=1), FBA=0, viewport Z scale/bias 0; uses `0x00386D10`. *[static]*
  - `0x00387A00`: Pass 4 (to `0x00387A80`): five textured strip pairs (2,0),(0,3),(3,4),(4,1),(1,5) forming trough and lips; band U 0,.25,.375,.625,.75,1; V alternates per slice; TEST 0x50000, FBA=1, depth writes, source-alpha blend; uses `0x00386DD0`. *[static]*
  - `0x00387C30`: Pass 5, gap fixup: bands 0,1 textured where the dest-alpha mark is clear; TEST 0x54000 (GEQUAL, DATE=1, DATM=0), FBA=0, depth writes; only when gp+0x14DC (`0x004A45CC`, default 1) is set; uses `0x00386DD0`. *[static]*
- **`0x003883B8`** - Wake draw callback (graphics dispatch virtual slot +0x2D4): submits adjacent column pairs via the strip submitter `0x003885E0`. *[static]*
- **`0x003885E0`** - Strip submission routine for wake/board strips. *[static]*
- **`0x003889F0`** - CPU texture sampling of terrain base/lightmap textures (indexed 4/8-bit swizzle and palette); clamps indices inclusively. *[static]*
- **`0x00389260`** - Clears a lighting (irradiance) bank. *[PS2]*
- **`0x00389308`** - Projects a directional RGB contribution into the ten irradiance coefficient rows (order: constant, X^2, Y^2, Z^2, XY, XZ, YZ, X, Y, Z). Computes X^2-Y^2 and Z*(Z*3)-1 as separate operations; eleven float constants at gp-0x272C..gp-0x2704 (`0x004A09C4`..`0x004A09EC`). Accumulates only RGB lanes (fourth lane untouched); no direction normalisation, no colour/weight clamp. *[static]*
- **`0x00389520`** - Wrapper that calls the directional projection `0x00389308` with a direction vector and unit weight; used for the RFX+0xD30 directional pairs in rider assembly and by the kind1/kind2 local-light paths. *[static]*
- **`0x00389558`** - Adds an ambient RGB contribution into an irradiance bank (used for the RFX+0xD30 ambient). *[static]*
- **`0x00389590`** - Irradiance accumulate: adds an IRR.DAT lighting record into a destination bank with a weight and RGBA modulation, multiplying weight by the modulation colour once and adding the ten coefficient rows. Modulation input is in A,R,G,B order while coefficient lanes are R,G,B,A; uses scalar FPU adds (unlike the VU-arithmetic helpers `0x00389730` family); no clamp or normalisation. *[PS2]*
- **`0x00389620`** - Fourth-lane-only irradiance accumulation: adds lane 3 of each row, RGB untouched (used by the rim tail of `0x00389CB8`). *[static]*
- **`0x00389730`** - One of three irradiance bank helpers (sum, scale, copy-scale; `0x00389730`, `0x003897A0`, `0x00389810`) with VU ADD/MUL semantics, distinct from `0x00389590`; which role this address has is not mapped. Sum and copy-scale stage all ten rows before copying (alias-safe); each returns the destination pointer. Used by the environment mix `0x002ED92C`. *[static]*
- **`0x003897A0`** - One of three irradiance bank helpers (sum, scale, copy-scale; `0x00389730`, `0x003897A0`, `0x00389810`) with VU ADD/MUL semantics, distinct from `0x00389590`; which role this address has is not mapped. Sum and copy-scale stage all ten rows before copying (alias-safe); each returns the destination pointer. Used by the environment mix `0x002ED92C`. *[static]*
- **`0x00389810`** - One of three irradiance bank helpers (sum, scale, copy-scale; `0x00389730`, `0x003897A0`, `0x00389810`) with VU ADD/MUL semantics, distinct from `0x00389590`; which role this address has is not mapped. Sum and copy-scale stage all ten rows before copying (alias-safe); each returns the destination pointer. Used by the environment mix `0x002ED92C`. *[static]*
- **`0x00389840`** - Transforms irradiance coefficient rows through a 3x3 (9-float) matrix over an inclusive channel range; quadratic, cross and linear rows are transformed, the constant row and channels outside the range are kept. The rim tail of `0x00389CB8` calls it with range 3..3. *[static]*
- **`0x00389C38`** - Calls the irradiance accumulate `0x00389590`; runs ahead of the rim preparation `0x00389CB8` in the lighting path (exact relationship not described). *[static]*
- **`0x00389CB8`** - View-dependent rider rim lighting: evaluates a lighting bank at a world position (args bank, position, 1.0) with the camera view matrix from the renderer view getter, building a fourth-lane rim contribution and adding it into the bank. Sparse shape rows 0,2,3,7 = 0.4954159856, -0.0 (`0x004A43C0`), -1.4862500429, 0.2046655864, others 0. *[PS2]*
  - `0x00389D50`: Eye/view-direction block (to `0x00389E94`): eye = transposed view matrix times negated translation (W forced to 1), normalised point-minus-eye, horizontal magnitude. *[static]*
  - `0x00389E98`: Pitch/yaw block (to `0x00389F9C`): pitch = -atan(Z/horizontal); yaw = pi/2 - asin(clamped ratio), 2*pi - yaw if horizontal Y < 0, 0 for vertical (denominator < 0.001); X reference axis at `0x004FF140`. *[static]*
  - `0x00389F9C`: Rotation construction (to `0x0038A4D0`), common exit of the angle block: negative-pitch Y and negative-yaw Z rotations via sin/cos `0x0031BE50`, VU multiply, transpose, lazily initialised axis-conversion matrix, packed 3x3. *[static]*
  - `0x0038A4D4`: Rim tail (to `0x0038A4EC`): transforms channel 3 via `0x00389840` (range 3..3) and adds it into lane 3 via `0x00389620` with scale = inputScale * rim scale at gp-0x26E8 (`0x004A0A08`, 0.7500065565). *[static]*
- **`0x0038A530`** - Local-light geometric query for a sample point: reads radius +0x1C, axis +0x2C, position +0x38; rejects only when squared distance > squared radius (exact radius accepted), leaving outputs untouched. Returns distance, 1/distance, normalised direction and the negative dot with the axis; a coincident point gives distance = inverse = 1, direction (0,0,0,1). *[static]*
- **`0x0038A618`** - Kind2 point-light query (inclusive radius) that starts the point-light contribution, which continues in `0x0038A6A8` at `0x0038AAA0`..`0x0038ABE0`. Coincident points follow EE DIV saturation (signed max) with zero direction. *[static]*
  - `0x0038A678`: Inline zero-divisor branch for coincident points. *[static]*
- **`0x0038A6A8`** - Local-light irradiance contribution, called per rider light slot by `0x001220D8`: kind1 spotlight (query `0x0038A530`, outer-cone gate, distance fade, angular weight, RGB scale, projection via `0x00389520`/`0x00389308`) and kind2 point light (query `0x0038A618`, then `0x0038AAA0`); kinds 0 and 3 contribute nothing. *[static]*
  - `0x0038A710`: Spot distance attenuation (to `0x0038A7FC`): rejects cosine below outer; radius<5000 full fade, else full to 3750 then 1-(d-3750)*0.0008 (no clamp); factor = 100/d saturated to 1, modes 1/2/3 linear/squared/cubed; times intensity +0x14. *[static]*
  - `0x0038A7FC`: Spot angular attenuation (to `0x0038AA74`): inside inner cone power of the cosine; between cones power of inner threshold times (cos-outer)/(inner-outer); modes 0..4 explicit, others by squaring; weight clamped 0..5. *[static]*
  - `0x0038AAA0`: Kind2 point-light branch (to `0x0038ABE0`): inverse-distance modes 1/2/3, 5000/3750 cm long-distance fade, intensity clamp 0..5, RGB multiply, projection via `0x00389520`/`0x00389308`. *[static]*
- **`0x0038ABF8`** - Returns the irradiance record address for an index (160-byte stride); out-of-range indices are not guarded. *[static]*
- **`0x0038AC50`** - Resolves an irradiance bank name to its record index. *[static]*

## `src/render/irradiance.cpp`

Segment `0x0038ACD0`-`0x0038AE10`.

- **`0x0038ACD0`** `cIrradianceDataBase_Load` - Loads the IRR.DAT irradiance bank, copying the 8-byte name table and the 160-byte coefficient records into separate allocations. Layout: u32 count, count 8-byte names, then count 160-byte records (ten rows of four floats, lanes R,G,B,A); little-endian; the shipped bank has 45 records. *[static]*

## `src/render/bezierman.cpp`

Segment `0x0038AEF8`-`0x0038DBD0`.

- **`0x0038B0F8`** - Terrain patch list walk feeding the patch DMA builders `0x0038CA70`/`0x0038CE20`. *[static]*
- **`0x0038B178`** - Terrain patch LOD rule routine (role inferred; not recovered). *[unconfirmed]*
- **`0x0038B190`** - Terrain patch LOD rule routine (role inferred; not recovered). *[unconfirmed]*
- **`0x0038CA08`** - Shadow receiver draw over near terrain patches; the source pairs `0x0038CA08`/`0x0038D448` with the tier-2 and stitched patch lists. Redraws with the light layer draw and blend 0x81 with As 0x80 (Cd = max(Cd - T, 0)), before the fog composite and ScreenTint, using a 128x128 PSMCT16 silhouette per rider (LOD-3 meshes). *[static]*
- **`0x0038CA70`** - Terrain patch DMA builder for the layer draw packets (one of two, with `0x0038CE20`). Sets material state [renderer+0xE84]: ALPHA_1 enum 1, ALPHA_2 enum 8, CLAMP_2 clamp/clamp, ATE with ATST ALWAYS. Display list: one V3-32 position block plus two V2-32 UV blocks (base UV, light UV at patch+0x10); pixel = clamp(((T_base - L.rgb) * L.a) >> 7). *[static]*
- **`0x0038CE20`** - Terrain patch DMA builder for the layer draw packets (one of two, with `0x0038CA70`). Sets material state [renderer+0xE84]: ALPHA_1 enum 1, ALPHA_2 enum 8, CLAMP_2 clamp/clamp, ATE with ATST ALWAYS. Display list: one V3-32 position block plus two V2-32 UV blocks (base UV, light UV at patch+0x10); pixel = clamp(((T_base - L.rgb) * L.a) >> 7). *[static]*
- **`0x0038D168`** - Probably the terrain layer type 6 draw: VU environment map (UV from normals) blended 0x58 (Cd + Cs*Ad), using a camera-derived 0.5-scaled matrix at terrain renderer +0x360; used on start-ramp patches. The destination-alpha source is unverified. *[unconfirmed]*
- **`0x0038D448`** - Shadow receiver draw over near terrain patches; the source pairs `0x0038CA08`/`0x0038D448` with the tier-2 and stitched patch lists. Redraws with the light layer draw and blend 0x81 with As 0x80 (Cd = max(Cd - T, 0)), before the fog composite and ScreenTint, using a 128x128 PSMCT16 silhouette per rider (LOD-3 meshes). *[static]*
- **`0x0038D690`** - Per-patch extra draw for terrain patches with flag 0x800000, distance-scaled (probably sparkle; unconfirmed). *[unconfirmed]*

## `src/render/lightman.cpp`

Segment `0x0038DBD0`-`0x00391788`.

- **`0x0038F460`** - DMA packet allocator routine used by render passes (including the glare pass); paired with `0x0038F668`. *[static]*
- **`0x0038F668`** - DMA packet allocator routine used by render passes (including the glare pass); paired with `0x0038F460`. *[static]*
- **`0x00390458`** - Copies the ScreenTint scale/add globals into render context +0x6CA4; run from renderer vfunc `0x00386640` alongside fog `0x0036ABA0` and glare `0x0036C740`. *[static]*
- **`0x003904A0`** - ScreenTint draw, run right after the glare pass and before the HUD (see `0x00363490`). *[static]*
- **`0x003905E8`** - ScreenTint pass: re-reads the framebuffer as a PSMCT32 texture (TEX1 nearest, MODULATE, no blend) tinted by trunc(scale*127.5), then an optional additive sprite (GS ALPHA 0x48) adding trunc(add*127.5); skipped for identity tint. *[static]*
- **`0x00390C60`** - ScreenTint environment component update (vtable `0x00492FA0` slot +0x14), run once per race frame: lightning flash state machine. Returns if Enable Lightning (`0x004A460C`) is 0; decrements thunder delay `0x004A46B4`. Idle (counter `0x004A4698` < 0): one visual-RNG draw; if u < chance^2, a second draw gives dist = (u2*1.98 + 0.02)*100000 cm and calls `0x00390EC8`. Running: counter++, intensity `0x004A469C` = c/2*0.4 col1 (c<=2), 0.4 col1 (c<=4), 1.0 col2 (c<=6), (1-(c-6)/7)*0.5 col3 (c<=13), else 0 with counter -1 and base colour; mode `0x004A46AC` = 5. *[PS2]*
  - `0x00390CA0`: Return address of lightning draw 1 (u compared with chance squared); one draw per update while enabled. *[PS2]*
  - `0x00390CE0`: Return address of lightning draw 2 (strike distance), made only when draw 1 succeeds. *[PS2]*
- **`0x00390EC8`** - Starts a lightning strike at distance dist: counter 0, intensity 0, stores dist, thunder delay = (int)(dist*0.0018072289). Called by the ScreenTint update `0x00390C60` and by a WScript builtin (`0x00305778`) for scripted strikes. *[static]*
- **`0x00390EF8`** - Thunder poll: returns 1 once when the ScreenTint thunder delay reaches 0; polled by audio function `0x00285BF8`, which then plays the thunder (bank 8 sound 16). *[static]*
- **`0x00390F20`** - ScreenTint render (vtable `0x00492FA0` slot +0x1C): draws the tint when intensity `0x004A469C` (gp+0x15AC) != 0; makes no RNG draws. *[static]*

## `src/render/font.cpp`

Segment `0x00391788`-`0x00397140`.

- **`0x00391CB0`** - Font glyph submission; can add shadow and offsets. SUPER/UBER HUD letters use HUDFONT (texture handle 0x5DE). *[static]*
- **`0x00391FB0`** - Text measure helper used by the trick HUD. *[static]*
- **`0x003921F0`** - Measures a text run (used for the Uber hint layout). *[static]*
- **`0x00392DF0`** - Probably a sine table / sine lookup, used by the flag grid code (unconfirmed). *[unconfirmed]*
- **`0x00393FB8`** - Applies the screen position to the display live (cFEPopupScreenPos vtable `0x0046B230` slot +0x60). *[static]*
- **`0x003947D8`** - Contains the renderer setter block below. *[static]*
  - `0x003948B0`: Setter block writing renderer+0xF50+index*4 (no direct jal caller found). *[static]*
- **`0x00395330`** - Helper used by the glare pass; role not described. *[unconfirmed]*
- **`0x00395350`** - Helper used by the glare pass; role not described. *[unconfirmed]*
- **`0x003954D0`** - Renderer lighting-coefficient setter (vtable `0x00493260` slot 0x228/0x22C, this-adjustment 0): copies a 160-byte lighting bank (rider coefficients) unchanged into renderer+0x6BB0; VU program 2 later scales it by 255. Called from the rider draw at `0x001224C8`..`0x001224E4`. *[PS2]*
- **`0x003956E8`** - Renderer view matrix stack push. *[static]*
- **`0x00395730`** - Renderer view matrix stack pop. *[static]*
- **`0x00395750`** - Renderer Euler view setter (vtable `0x00493260` slot 0x10C): applies an authored Y/Z permutation, multiplies negative f12/f13/f14 rotations about X/Z/Y, then transforms the negated eye (W negated twice). Not the active gameplay view producer; the draw-time view comes from the quaternion path `0x0015E968`. *[PS2]*
- **`0x00395C38`** - Renderer slot 0x114: copies a supplied matrix onto the view matrix stack head. *[PS2]*
- **`0x00395C68`** - Renderer view getter (slot 0x11C): returns the pointer stored at renderer+0x13E4 (matrix stack head); used by the rim lighting. *[PS2]*
- **`0x00396B40`** - Renderer slot 0x3E4: uploads the ten lighting coefficient rows to VU1 (V4_32 unpack to VU data addresses 7..16) and starts the lighting prep microcode with MSCAL entry 0x1150 of VU1 program 2 (DMA source `0x00434990`), which multiplies all 40 floats by 255. Called from `0x0037A610` at `0x0037A6A0`. *[static]*
