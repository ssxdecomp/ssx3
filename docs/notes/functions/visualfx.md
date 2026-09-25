<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/visualfx/

## `src/visualfx/angerfx.cpp`

Segment `0x002D48F0`-`0x002D5778`.

- **`0x002D4BE0`** - Resets the relationship icon FX component at rider FX +0xAF0; called by `0x00111890`. *[static]*
- **`0x002D4C08`** - Relationship icon update, the rider FX pass for the component at rider +0xAF0 (per game tick): level from `0x00155B50`; colour by level (>= 4 red, 3 orange, 2 yellow, else white); visibility ramps +-0.1 (level >= 2) or +-1/15; pulses: 41-tick pop on a level change, 31-tick loop at level >= 4, 24-tick pop on a rise. *[static]*
- **`0x002D5048`** - Relationship icon draw: alpha-blended quad at bone 5 + 35 cm, size 18(sx + 0.003 z) x 18(sy + 0.003 z), visible for 0 < z < 20 m and fading past 15 m. *[static]*

## `src/visualfx/avalanche.cpp`

Segment `0x002D5778`-`0x002DA390`.

- **`0x002D5778`** `tActiveAvalancheNode_getFrameData` - Constructor of the class with vtable `0x00488664`, whose priority-7 draw method is `0x002D9130`. *[static]*
  - Possible mismatch with the current name: The name suggests a frame-data getter, but the records describe it as the constructor of the class with vtable `0x00488664`.
- **`0x002D66A0`** `tAvalancheNode_calculate` - Non-race caller of the visual RNG `0x003177F0` (a load/menu/replay-time consumer). *[static]*
- **`0x002D9130`** - Priority-7 draw method of the class with vtable `0x00488664` (ctor `0x002D5778`). *[static]*
  - `0x002D9260`: Copies a selected camera's +0x40 view matrix to the renderer through vtable slot 0x114 (`0x002D9260`..`0x002D9274`; with `0x0022B250`). *[static]*
  - `0x002D9270`: Renderer slot 0x114 call of the camera view copy block starting at `0x002D9260`. *[static]*

## `src/visualfx/boardsparkfx.cpp`

Segment `0x002DA390`-`0x002DB6D8`.

- **`0x002DAA78`** - Resets the spark FX component at rider FX +0x470; called by `0x00111890`. *[static]*
- **`0x002DABC8`** - Board sparks update (effect object at rider FX +0x470), a rider FX pass run over all riders each tick before the board track: sparks, glints and grind chunks on metal surfaces and rails. Gates: speed > 277.778 cm/s; sparks when surface +0x8C is set; glints also on rails (motion 4, 30% of ticks, 3 sprk quads); grind chunks on surface 9 or rails with +0x88. Surface = rider+0x438; emit point rider+0x460 + v*0.01; chunk chance min(speed/1666.67*0.1, 0.1). Particle kernel `0x0036D428`, `0x0036D318`, `0x0036D1F0`, `0x0036CEF8`; render priority 7. *[PS2]*
- **`0x002DB478`** - Board sparks draw: grind chunks (snow program, GS 0x44), then the spark kernel through renderer slot 0x290 (`0x00380518`), then glints (`0x00377CF0`). Random draws use only the visual LCG `0x004A3AFC` (gp+0xA0C), plus particle-birth `0x003177F0` for chunk births. *[static]*

## `src/visualfx/boardwakefx.cpp`

Segment `0x002DCB88`-`0x002E81E8`.

- **`0x002DCF28`** - Wake (board trail) profile setup; also the reset of the trail FX component at rider FX +0x3B0 and the first rider FX component constructor called by `0x00111890` (that constructor range ends at `0x002F64E8`). Device riders get 5 columns/32 rows/1.25 s lifetime, others 4/22/0.8; also computes vertical increments and initial texture V values. *[static]*
- **`0x002DD0B8`** - Wake frame driver, the rider FX pass for the component at rider +0x3B0 run over all riders each tick: ages rows (age +1/60), computes targets and control, advances and creates rows. Stages: aging `0x002DD0B8`..`0x002DD2A0`, targets `0x002DD2A4`..`0x002DD6F0`, control `0x002DD6F4`..`0x002DDA88`. *[static]*
  - `0x002DD2A4`: Wake input/target stage start (to `0x002DD6F0`); an empty cache skips here to `0x002DD2A8`. *[static]*
  - `0x002DD378`: Wake row expiry branch. *[static]*
  - `0x002DD6F4`: Wake control stage (to `0x002DDA88`): gates, 0.8/0.2 and 0.7/0.3 filters, 50 cm row advance, two initial zero rows. *[static]*
- **`0x002DDAB8`** - Wake render dispatch (not a physics updater), gated by `0x004A4528` (gp+0x1438). *[static]*
  - `0x002DDC4C`: Wake draw block (render priority 7, not fogged). *[static]*
  - `0x002DDC68`: Wake draw window (`0x002DDC68`..`0x002DDCE4`): oldest-row fade, head, capacity-2 limit, per-row fade decrement. *[static]*
- **`0x002DDD30`** - Wake row creation: noise-driven velocity fan from coefficients +0x60/+0x70 and amplitude +0x90 (final column x0.9); drag from +0x80 and rider velocity; render anchors at point-normal*5 cm; alpha +0x94 scaled to GS 128. *[static]*
- **`0x002DE058`** - Wake row advance: phase +0.033333335 wrapping at 4, count saturates, head decrements; then prepares row colour/UV (doubled/clamped env channels, RGB quantised to 128, signed repeating U, counter per advance). *[static]*
- **`0x002DE398`** - Board jitter for snow trail and kicker emission: random board-X and board-Z offsets. *[static]*
- **`0x002DE4A8`** - Snow effect profile constructor (to `0x002DF178`): ten emitter profiles, 580 parameter words: SnowTrail0, LargeChunky1, SmallChunky2, Rock3, RiderBreath4, LargeImpact5, SmallImpact6, Cloudy7, Kicker8, BodySnow9. Also zeroes the breath state and allocates the 30-word BodySnow bone table at FX+0x7C. *[static]*
  - `0x002DE610`: Stores at `0x002DE610`/`0x002DE618`/`0x002DE620`/`0x002DE628` zero the breath accumulator, phase, clock and duration (no store to effort +0x1C found). *[static]*
  - `0x002DF15C`: Loads BodySnow VelScale 0.8 from `0x0049F554` (gp-0x3B9C). *[static]*
  - `0x002DF174`: Allocates the 30-word BodySnow bone table stored at FX+0x7C. *[static]*
- **`0x002DF3B0`** - Snow FX component reset (rider FX +0xB40, called by `0x00111890`): zeroes FX+4 buildup, +0x78 cursor, +0x80 bones-bound and +0xE0 strength; sets FX+0x120 = 0.5 and FX+0x90 = (1,1,1,1). *[static]*
- **`0x002DF448`** - Deactivates all ten snow emitters and clears FX+0x60. *[static]*
- **`0x002DF4D0`** - Binds the 30 BodySnow bones by name into FX+0x7C via `0x00310C48` (missing name -> -1) and sets FX+0x80 = 1. Order: shinL, footL, shinR, footR, thighL, thighR, hips, lowerspine, middlespine, upperspine, neck, clavicleL, handR, bicepL, biceptwistL, then legs/hips/spine repeat, forearmL, handL, clavicleR, bicepR, biceptwistR, forearmR. *[static]*
- **`0x002DF920`** - Per-rider snow FX update (component at rider +0xB40), run for the human then each CPU rider after the board-sparks pass: deactivate/bind prefix, rider cache, then emitters Chunky 2 and 1, Rock3, Trail0, Breath4 (`0x002E1120`), Impact (selected 5/6, then the other inactive one; [6,5] when both inactive), Cloudy7, BodySnow9 (`0x002E2260`), Kicker8 (`0x002E1F70`). One visual-RNG draw per enabled emitter (return address `0x003711D0`). *[PS2]*
  - `0x002DF938`: If FX+0x60 != 0, calls `0x002DF448` (deactivate all ten emitters, FX+0x60 = 0). *[static]*
  - `0x002DF94C`: If FX+0x80 == 0, calls `0x002DF4D0` to bind the thirty BodySnow bones. *[static]*
  - `0x002DF960`: Rider snow cache block (to `0x002DFB5C`): FX+0x12C = 0, edge bias, speed from source velocity, board frame (unit axes of the geometry+0x30 world matrix of bone rider+0x8A4, bone 23); clears groundEmission FX+0xB0 in motion 2. *[static]*
  - `0x002DFE4C`: Calls BodySnow `0x002E2260` (after Cloudy 7, before Kicker 8). *[static]*
  - `0x002DFE64`: Calls the Kicker emitter `0x002E1F70`. *[static]*
- **`0x002DFE88`** - Rock spray emitter (3): chance from surface +0x6C together with speed/brake/skid/turn, ground gate, spawn 15 cm board-forward with jitter, ordered velocity/normal/side components; keeps the argument updates and LCG draw count even when emission is inactive. *[static]*
- **`0x002E02B8`** - Chunky snow emitters (Small 2 then Large 1): carve/brake, wake velocity, landing burst, chance tests and draw order. Chance scales from surface +0x70/+0x74, wake inputs +0x78/+0x7C/+0x80; checks surface +0x78 and count owner+0x3B4 and reads the newest wake row tip (records + head*0x70 + (columns-1)*0x10 of owner+0x3B0) as wake velocity, with no world query. In motion 2 it fires an impact burst from retained strength with extra +/-55 cm jitter. *[static]*
  - `0x002E08FC`: Reads the newest wake row tip vector (`0x002E08FC`..`0x002E0938`). *[static]*
- **`0x002E0EE8`** - SnowTrail emitter (0): gated on ground emission, speed > 222.222229 cm/s, surface +0x58 and a suppression flag; point = board origin + 15 cm along board Y, then board jitter `0x002DE398` (board X and Z); profile velocity/normal/speed-normal coefficients applied in VU order. *[static]*
- **`0x002E1120`** - Breath particle emitter (emitter 4) update, puffing from the head bone 5 with class-12 environment transitions. Called from `0x002DF920` after the snow trail and before impacts. Speed > 1111.111 cm/s resets and exits; channel-2 class 30 gives effort 1. Alpha = clamp((effort+0.5)*(1-(env+5)*0.04),0,2); phase 0 or alpha <= 0.02 resets. Otherwise an LCG-timed accumulator += (rand*6+18)/60 emits when > 1; birth direction is local (0,0,150). *[static]*
  - `0x002E13BC`: Loads (0,0,0,1) from `0x004FF130` over the copied matrix translation (through `0x002E13D4`) so the direction transform has no translation; the world translation is used only for the mouth position. *[static]*
- **`0x002E1598`** - Snow impact bursts (emitters 5/6): mutates strength FX `+0xE0`, buildup FX `+0x4` and alpha FX `+0x120`, and emits an ordered birth pair. The motion-2 branch adds 2*amount*scale to the buildup (capped at 2.0). Large impacts near the camera chain the secondary request `0x002F4118` -> `0x002F4260` to lens snow splats. *[static]*
- **`0x002E1A80`** - Cloudy snow emitter (emitter 7): emission chance from slip/turn/speed, board-normal height scatter, backward offset and carve-side velocity. Uses surface `+0x50`/`+0x54` and the profile-7 velocity coefficients. Consumes its first LCG draw even when it cannot emit. *[static]*
- **`0x002E1F70`** - Kicker carry-off snow emitter (emitter 8) with per-rider buildup: FX `+0x10` grows by 0.0100000007 per call on eligible ground up to surface `+0x5C`, else decays by 1/60. Emits during carry-off behind a 277.77777 cm/s speed gate and a -3333.3335 cm/s vertical-speed gate; jitter via `0x002DE398`. *[static]*
- **`0x002E2260`** - BodySnow emitter (emitter 9): puffs at a cycling body bone (30-entry table FX `+0x7C` indexed by FX `+0x78`, wraps at 30) while impact buildup FX `+0x4` > 0 and speed > 83.33 cm/s. alpha = min(buildup*1.5,1); position = row 3 of the bone matrix at geometry `+0x30`; velocity = rider `+0x1E0` * VelScale; colour FX `+0x90` rgb; dt 1/60. If FX `+0xD4` != 2 buildup -= 1/60 (min 0). When inactive it requests at bone rider `+0x89C`. No LCG draws. *[static]*
  - `0x002E2290`: Emitter 9 offset `0x1290` (= 9 * `0x210` emitter stride) within the FX emitter array. *[static]*
  - `0x002E22AC`: Immediate 1.5 (`0x3FC00000`): BodySnow alpha gain. *[static]*
  - `0x002E22B4`: Immediate 1.0 (`0x3F800000`): BodySnow alpha clamp. *[static]*
  - `0x002E2358`: Bone cursor wrap constant 30 (`0x1E`). *[static]*
- **`0x002E23E0`** - Snow impact request/spawn with a kind argument (0 for rider impacts). Takes |strength| (doubled for kind 0) and accepts it only if stronger than the retained impact and at least 180 cm (100 cm wide) away. *[static]*
- **`0x002E2868`** - Light-glow draw: two copies of a rotated camera-facing additive halo quad per glow, render priority 7. Material from `0x002E3578`: blend enum 7 (`0x48`), MODULATE, ATST ALWAYS, ZTST 2 for queried glows / 1 for far glows (vis 1). Texture FX 53 `shal` (class `0x10`/`0x40`) or FX 54 `mhal` (`0x20`); half size 180/100/350 cm; RGB = trunc(128*normalize(colour)), A = trunc(128*vis). Geometry via renderer vfunc `+0x278`; calls `0x003781A0`. *[PS2]*
- **`0x002E2B00`** - Per-record light-glow update (kind-7 world lights): projection, query rects, pulled Z and sprite rotation. View camera at owner `+0x10`; outcode `0x0037DBE8`, screen x/y/Z via `0x0037DD20`; zf = Z*2^-24 (`0x0049F6B0`, gp-0x3A40). zf <= 0.005 (`0x0049F6B4`) is a far glow with no query; else `+0x2E`=1, count rect w=clamp(trunc(zf*800),1,16), h=clamp(trunc(zf*400),1,8), read rect 16x8 at (x-8,y-4). `+0x24` Z pulled 100/80/200 cm by class; `+0x28` = ((x-vx)*2/vw-1)*pi/2. *[PS2]*
- **`0x002E2E18`** - Registers the renderer callback used for the sun/light-glow Z-buffer visibility queries (probably the end-of-frame callback `0x002E3110`). *[static]*
- **`0x002E2F98`** - Clears a per-view light-glow list. *[static]*
- **`0x002E2FA8`** - Light-glow record add helper: sets the source pointer at `+0x20` and clears `+0x28`/`+0x2C`/`+0x2E`. *[static]*
- **`0x002E2FF8`** - Adds a light-glow record via the helper `0x002E2FA8`. *[static]*
- **`0x002E30D0`** - Runs the sun/light-glow update pass `0x002E3338` and then the draw pass `0x002E3478`; called via `0x0022C790`. *[static]*
- **`0x002E3110`** - Renderer end-of-frame callback that performs the sun/light-glow Z queries via `0x002E3130`. Registered through renderer vfunc `+0x3A8` (`0x003866E0`); called by the frame-flip state machine `0x00382760` in state 2. *[static]*
- **`0x002E3130`** - Z-buffer visibility pass: runs the 16x8 query `0x002EC478` for every queried sun/glow record. Glow vis = open/(w*h), or max((open-wh/2)/(wh/2),0) when clipped, stored at source `+0x40+view*4` (the draw uses the previous frame's value). Sun vis = open/256 or max((open-128)/128,0), stored at sun `+0x204`. *[PS2]*
- **`0x002E3338`** - Sun and light-glow update pass (per view). *[static]*
- **`0x002E3478`** - Sun and light-glow draw pass (per view). *[static]*
- **`0x002E3578`** - Light-glow material push: uses the query object vtable `0x00487F00` slot `+0x10` and material template `0x00501420`. *[static]*
- **`0x002E3930`** - Resets the rival locator beam FX component at rider `+0xB00`; called by `0x00111890`. *[static]*
- **`0x002E39D8`** - Rival locator beam update (rider FX component at `+0xB00`). Active only in single-player rival modes on courses 14..16; the pulse update runs for the human rider only. *[static]*
- **`0x002E3AF8`** - Rival locator beam draw: 8-vertex additive strip along camera up from the rival's bone 5. Alpha 0 at base, full colour at +130 cm and +20130 cm, alpha 0 at +20260 cm; half width 85 cm along camera right; texture `beam` (renderer `+0xFFC`); colour from component `+0x28`, initially (a 0.5, r 1, g 0, b 0). *[static]*
- **`0x002E4228`** - Constructor of the full-screen fade overlay (vtable `0x0048817C`). *[static]*
- **`0x002E4370`** - Starts a screen fade; used for the NIS header fade-in record. *[PS2]*
- **`0x002E44F0`** - Screen fade-out that rewrites the running fade's in phase (the next step starts bright when in = 0). *[PS2]*
- **`0x002E4578`** - Stops a viewport's screen effect (resets the white fade). *[static]*
- **`0x002E46C8`** - Contains the fade-time conversion block below for screen colour effects. *[static]*
  - `0x002E4760`: Block (no separate function start) that converts a bound progress value into elapsed fade time for screen colour effects. *[static]*
- **`0x002E47E8`** - Timed full-screen 2D fade overlay draw at priority 8 (also the control-9 forced-reset white fade): 640x480 ortho, alpha fade from `+0x48`/`+0x54`/`+0x58`/`+0x5C`. vtable `0x0048817C`, constructor `0x002E4228`. *[static]*
  - `0x002E48AC`: Fade opacity selection and clamping block (through `0x002E492C`) for in/out screen colour effects, including the white reset fade driven by reset progress. *[static]*
- **`0x002E4CE8`** - White full-screen fade, used on the placement path. *[static]*
- **`0x002E4D88`** - Load-time snowfall set-up that draws from the visual (presentation) RNG; one record labels it the load-time audio/HUD set-up. Its draw count matches the generator's own count. *[PS2]*
  - `0x002E4E14`: Visual RNG draw site (call to `0x003177F0`) during load-time set-up; first of three with `0x002E4E1C` and `0x002E4E24`. *[PS2]*
  - `0x002E4E1C`: Visual RNG draw site (call to `0x003177F0`) during load-time set-up. *[PS2]*
  - `0x002E4E24`: Visual RNG draw site (call to `0x003177F0`) during load-time set-up. *[PS2]*
- **`0x002E5920`** - Snowfall object function that, together with the snowfall update `0x002E5DA0`, feeds snowfall into the camera splash `0x002F4330`. *[static]*
- **`0x002E5DA0`** - Snowfall object update (entity group 2). Makes no visual-RNG draw; feeds the camera splash pending count. *[PS2]*
- **`0x002E6640`** - Resets/initialises the boost effect FX component at rider `+0x610`; called by `0x00111890`. *[static]*
  - `0x002E6698`: Boost effect constructor stores (through `0x002E66A8`): history capacity 18 when deviceIndex < 0, else 20. *[static]*
- **`0x002E66B8`** - Boost effect update, the rider FX pass for the component at `+0x610`. Parameter stage (to `0x002E68A4`): active when motion != 1 and rider `+0x2FC` > 0 or inside the `+0x2E8` window; texture 57/58/59 by tier 5/10, 60 for a pickup, 61 for tier 11; width 50 cm at tier 11 else 6+9*boost; length (400+400*boost)*(speed/3333.3335); when inactive the fields decay by *0.95; scroll step 0.002/0.005/0.01. *[static]*
  - `0x002E677C`: Branch target for an active speed pickup (scroll step 0.01). *[static]*
  - `0x002E68A8`: Boost side history stage (through `0x002E6BEC`): 20-slot paired position ring, spread 1.4, UV scroll with a single +-1 wrap. *[static]*
- **`0x002E6C08`** - Boost main ribbon update: history of 30 rows of 28 bytes with seed, endpoint and trim stages. The seed stage (to `0x002E71B8`) anchors at +-75 board X and +-17.5 board Z; `+0x330` shifts the end by 150 (positive for semantics 23..28/37/38). *[static]*
  - `0x002E71BC`: Boost ribbon endpoint stage (through `0x002E7948`): endpoints along velocity x normal, 10 cm above the plane. *[static]*
  - `0x002E794C`: Boost ribbon trim stage (through `0x002E79F4`): drops the oldest rows over length, keeping >= 3 when length > 1. *[static]*
- **`0x002E7A10`** - Boost ribbon draw: consumes the side count `+0x3A0` and primary count `+0x14`, gated on length/alpha; builds two side strips and the main ribbon. *[static]*
  - `0x002E7BDC`: Boost strip draw block (no separate function start): render priority 7, not fogged. *[static]*
  - `0x002E7C3C`: Boost vertex packet build (through `0x002E81B8`) for the two side strips and the main ribbon. *[static]*

## `src/visualfx/boardtrailfx.cpp`

Segment `0x002E81E8`-`0x002EC3E0`.

- **`0x002E81E8`** `cBoardTrailFX_initialize` - Board-trail FX initialize: sets up a rider's persistent textured snow-track ring (six vertex bands of 54 slices each), in source Z-up centimetre coordinates. Companions: reset `0x002E8560`, sample admission `0x002E86F0`, eligibility `0x002E87E8`, update `0x002E8938`, draw window `0x002EA538`. Separate from the snow-trail particles and spray. *[static]*
- **`0x002E8560`** - Board-trail reset: resets the FX component at rider `+0x520`; called by `0x00111890`. Part of the board-trail group (init `0x002E81E8`, update `0x002E8938`); a restart after a stop inserts a two-update cooldown with three-slice stop/restart bookkeeping (not tied to a specific routine). *[static]*
- **`0x002E86F0`** - Board-trail sample admission: decides when to commit a new ring slice. The gate commits after 110 cm of contact displacement or when the cosine between projected travel directions falls below 0.999; a special state reduces the distance to 30 cm. The exact split of this gate between here and the update `0x002E8938` is unconfirmed. *[static]*
- **`0x002E87E8`** - Board-trail eligibility check (whether the rider currently lays a track). Gates (not individually assigned to this routine): material IDs 0,5,6,12 (packed), 1 (loose), 2,13 (powder) and 3 (deep powder) make tracks, others do not; airborne motion normally stops tracks; a special `+0xAC4`/`+0xAD0`/`+0xAFC`/`+0xB00` path and the grounded crash submode have their own gates; semantic 22 suppresses tracks between its two sequence flag markers. *[static]*
- **`0x002E8938`** - Board-trail per-rider update (FX component at rider `+0x520`): builds six-band, 54-slice track slices from posed board bone 23 (axis0/axis2, board geometry `+0x34`), crash-corner bones 10/15/18/21, the contact point/normal/distance, velocity, board angle, material depth profile, markers, stance, crash submode and two retained jitter values. Keeps a preceding-slice rewrite, temporary end cap, backward-edge collapse, 3-slice stop/restart and 2-update restart cooldown; each commit takes 2 steps of the visual LCG `0x004A3AFC`, before the snow producers. Zero direction relies on VU rsqrt saturation. Also holds a grind-chunk emitter via `0x003710D0` with 1 visual-RNG draw (PS2-observed). *[PS2]*
  - `0x002E8F24`: Reads rider velocity (rider `+0x1E0`) for the trail edges. *[static]*
- **`0x002EA538`** - Board-trail draw-window builder: yields ring start/count and fade parameters for rendering. Sends at most 48 slices, excluding the pending end slice; the track uses a bounded ring with per-segment fade, not a lifetime in seconds. *[static]*
- **`0x002EADC0`** - Resets the effect FX component at rider `+0x9C0`; called by `0x00111890`. *[static]*
- **`0x002EADD0`** - Rider FX pass for the component at rider `+0x9C0`. *[static]*
- **`0x002EBB10`** - Screen colour effect draw: multiplies the colour alpha by the opacity and draws the viewport quad; used for the white reset fade driven by reset progress. *[static]*
- **`0x002EBE20`** - Non-race caller of the visual RNG `0x003177F0` (load/menu/replay-time consumer). *[static]*

## `src/visualfx/lensfx.cpp`

Segment `0x002EC3E0`-`0x002EE7C8`.

- **`0x002EC478`** - Z-buffer visibility query (query object vtable `0x00487F00` slot `+0x24`): GS local->host transfer of a Z rect, counting pixels with Z <= reference. PSMZ24 Z buffer at ZBP 7168, width 512. Used by the light glows (16x8 rect) and the sun (16x16). *[PS2]*
- **`0x002ED1D0`** - Environment colour filtering routine. *[static]*
- **`0x002ED338`** - Environment colour filter. *[static]*
- **`0x002ED490`** - Environment update for a sample point and weight: runs every environment block's nine painter property wrappers (driver `0x002C0778`; loop counter starts at 8 and includes 0). The camera calls it as a render-listener notification (`0x0015EBBC`..`0x0015EBD0`) with outer camera `+0x20`/`+0x24` X/Y, view index+6 and weight -99999; block 0 (human) samples at rider `+0x460`/`+0x464`, blocks 1/2 at the computer riders. Also the per-rider colour update into `0x004FA370` + slot*0xF0: ground keeps ~0.1 old + 0.9 target, a shared force-next flag makes the next update immediate, a missing patch fades to white, rails keep colour and set the flag; air uses trajectory status `+0x788` and predicted patch/time/UV. *[static]*
  - `0x002ED5B4`: Alternate-bank selector update (through `0x002ED5DC`): slot `+0x24` = previous*0.9, plus 0.1 when rider `+0x3FC` is nonzero. Starts at 0; gameplay meaning unconfirmed. *[static]*
  - `0x002ED92C`: Irradiance mix (to `0x002EDB18`): selector `+0x24` > 0.1 blends the alternate bank toward the previous state, else weight = brightness*gain mixes banks 0/1; then blends by `0x004A3B70` (gp+0xA80, 0.5) against the previous coefficients (unclamped). *[static]*
  - `0x002EDA4C`: Bank-building step: passes group `+0x38` lighting ratio to `0x002EDF00`, fetches bank references 0/1/2 via `0x002EE318`/`0x002EE340`/`0x002EE368` -> `0x002EE010` and the gain via `0x002EEFF0`. *[static]*
- **`0x002EDB20`** - Terrain patch UV sampler and CPU environment colour formula. Base UV corners in order (0,0), (0,1), (1,0), (1,1) with a u + 4*v power basis (the corner order defines the base texture axes). Colour per channel = (base-light)*tint(0.55,0.535,0.55)*(lightAlpha*2), the terrain GS combine plus a rider tint; ratio = target/base; alpha 0.5. Items in non-resident chunks are treated as ineligible. *[PS2]*
- **`0x002EDF00`** - Lighting brightness curve from the terrain lighting ratio colour (environment group `+0x38`, passed from `0x002EDA4C`): luma 0.299R+0.587G+0.114B (alpha ignored), clamped at lower/upper thresholds 0.1/0.45; the interior normalises by 0.35 and computes exp(log(v)*0.6001175642) via `0x0040DA10` and `0x0040D758`, with an output clamp. *[static]*
- **`0x002EDFB8`** - Returns a rider's environment irradiance bank pointer: `0x004FA3C0` + index*0xF0. *[static]*
- **`0x002EE010`** - Resolves a lighting bank reference to an IRR bank index; an empty reference uses the per-course index at `0x004A43C4` (gp+0x12D4). *[static]*
- **`0x002EE070`** - First of the environment-slot wrappers for the Sun values (range `0x002EE070`..`0x002EE2B0`); the Sun painter lives at environment block `+0x14` (views 6/7). *[static]*
- **`0x002EE318`** - Lighting bank reference 0 getter used to build the rider environment bank; resolved through `0x002EE010`. *[static]*
- **`0x002EE340`** - Lighting bank reference 1 getter used to build the rider environment bank; resolved through `0x002EE010`. *[static]*
- **`0x002EE368`** - Lighting bank reference 2 getter used to build the rider environment bank; resolved through `0x002EE010`. *[static]*
- **`0x002EE3B8`** - Camera far-plane cap query (the camera's farCap input, observed 29999.34). Reads a different painter slot from Fog; the fog far distance is not the camera clip distance. *[static]*
- **`0x002EE6F0`** - Reads the environment breath scalar (object `+0x30`) through environment vtable `+0x184`. *[static]*
- **`0x002EE738`** - Region getter returning the lightning chance (vtable slot `+0x1AC` of the region payload). *[static]*

## `src/visualfx/renderstateman.cpp`

Segment `0x002EE7C8`-`0x002F0548`.

- **`0x002EE9C0`** - Environment getter for the Fog painter density value; used by the render-global copy `0x002F00A0`. *[static]*
- **`0x002EEA08`** - Environment getter for the Fog painter near distance value; used by the render-global copy `0x002F00A0`. *[static]*
- **`0x002EEA50`** - Environment getter for the Fog painter far distance value; used by the render-global copy `0x002F00A0`. *[static]*
- **`0x002EEA98`** - Environment getter for the Fog painter red value; used by the render-global copy `0x002F00A0`. *[static]*
- **`0x002EEAE0`** - Environment getter for the Fog painter green value; used by the render-global copy `0x002F00A0`. *[static]*
- **`0x002EEB28`** - Environment getter for the Fog painter blue value; used by the render-global copy `0x002F00A0`. *[static]*
- **`0x002EEDB0`** - First of the environment wrappers for the glare values (range `0x002EEDB0`..`0x002EEF60`); the painter is found at *(*(`0x004FA370` + view*0xF0 + 8)). *[static]*
- **`0x002EEFA8`** - Rim scalar getter: dispatches to the Lighting painter getter `0x002C15D8`, which returns painter `+0x50` (the second authored scalar, 0.75 on ARA1). Not `+0x4C`. *[static]*
- **`0x002EEFF0`** - Gain getter: dispatches to Lighting painter slot `0x148`/`0x14C` (`0x002C15D0`), returning painter `+0x48`. Used by `0x002EDA4C` when building the rider bank (weight = brightness*gain). *[static]*
- **`0x002EF0E8`** - Getter that returns the value at `0x004A55B0` (gp+0x24C0) when the override `0x004A3B64` (gp+0xA74) is set; the override was 0 in every inspected state. *[static]*
- **`0x002EF6A0`** - Resets the air streamers FX component at rider `+0xAD0`; called by `0x00111890`. *[static]*
- **`0x002EF6D0`** - Rider FX pass for the air streamers component at rider `+0xAD0`. *[static]*
- **`0x002EF950`** - Air streamers draw (rider FX component `+0xAD0`; `strm`/`prbn` textures), render priority 8. *[static]*
- **`0x002EFF98`** - Loads the board-track texture `btrl` (effects texture ID 55); see below. *[static]*
  - `0x002EFFAC`: Loads effects texture ID 55 (`btrl`, the board-track texture); the result is stored at `0x002F0008` to `0x004A45D4` (gp+0x14E4). *[static]*
- **`0x002F0000`** - Stores the loaded board-track texture; see below. *[static]*
  - `0x002F0008`: Stores the loaded `btrl` texture (ID 55) to `0x004A45D4` (gp+0x14E4); later selected at `0x00386FD0` for board-track rendering. *[static]*
- **`0x002F00A0`** - Per-camera region environment refresh, run after the component updates: copies painter values into render globals. Fog density `0x002EE9C0` -> `0x004A4338`, near/far `0x002EEA08`/`0x002EEA50` -> `0x004A432C`/`0x004A4330`, RGB via `0x002EEA98`/`0x002EEAE0`/`0x002EEB28`, equation `0x004A4334` = 1; ScreenTint scale/add -> `0x004A45E4`..`0x004A45F8`; glare -> `0x004A43D4`..`0x004A43E4`, `0x004A43F0`/`0x004A43F4` unless the override `0x004A43CC` is set. Also sets lightning chance `0x004A4614` from `0x002EE738` and enable `0x004A460C` = (S == 1) || (S == 0), S = game-flow word, so the lightning update reads the previous update's flag. *[static]*

## `src/visualfx/worldlightman.cpp`

Segment `0x002F5298`-`0x002FAE38`.

- **`0x002F5B68`** - Local light selector: ranks kind-6 extra nodes with `0x002F5D30` and keeps up to N (8 for riders) in descending rank order. Non-light nodes are skipped and only positive ranks insert; a new equal rank goes before existing equals, but an equal rank at a full list's cutoff is rejected. *[static]*
- **`0x002F5D30`** - Local light ranking: influence of a kind-6 light at a point (subkind 0 uses the stored brightness `+0x18`, 1 spot, 2 point, other kinds 0). Uses the radius/cone query `0x002F6168`, attenuation/intensity and stored brightness with no 0..5 clamp. Axis cosine = dot(unnormalised displacement, axis) * inverse distance (operation order differs from `0x0038A530`); when coincident, distance = inverse = 1. *[static]*
- **`0x002F6168`** - Radius/cone query used by the local light ranking `0x002F5D30`. *[static]*
- **`0x002F64E8`** - Resets the FX component at rider `+0xD20`; the last of the rider FX component constructors/resets called by `0x00111890` (range `0x002DCF28`..`0x002F64E8`). *[static]*
- **`0x002F6518`** - Rider FX pass for the component at rider `+0xD20`. Applies a late velocity blend toward board forward with weight rider `+0x310`, active only while boosting. *[static]*
- **`0x002F6AC8`** - Sets flag bits in the feedback byte owner `+0xD27`: the boost feedback call (owner+0xD20, 0) ORs in 0x10. Also acts as a statistics recorder (jump statistic; the handplant attempt flag is bit 6 of `+0xD27`). *[static]*
- **`0x002F6B88`** - Contains blocks that fetch lens-flare colours from a gp constant pool (inferred). *[unconfirmed]*
  - `0x002F6BC0`: Block (no separate function start), probably fetching lens-flare colours from a gp constant pool. *[unconfirmed]*
  - `0x002F7804`: Block (no separate function start), probably fetching lens-flare colours from a gp constant pool. *[unconfirmed]*
- **`0x002F7BE0`** - Tests whether the game-flow word S equals 0. *[static]*
