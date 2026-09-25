<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/main/

## `src/main/ssxapp.cpp`

Segment `0x00226830`-`0x0022C078`.

- **`0x00226B60`** `cSSXApp_loadInputMap` - Registers the input action names by index via `0x00320E18`: 0..26 main actions, 27..30 UberGrind1..4, 31..45 Trick1..15, 46 ResetPath, 47..204 camera/menu/editor actions. *[static]*
- **`0x00227E98`** `cSSXApp_preUpdate` - Contains the controller-port-0 front-end pad read call below. *[PS2]*
  - `0x00227E98`: Calls the front-end pad read `0x00321298` for controller port 0. *[PS2]*
- **`0x00228C08`** - Applies the widescreen mode (Off / 16:9 / Anamorphic) by passing it to the render context vtable `+0x140` (`0x00377950`). 16:9 letterboxes 3D and HUD into lines 56..392 with GS scale x0.75/x0.75; Anamorphic renders a 16:9 stage (x scale 0.75, full height, HUD stretched); both keep the 4:3 vertical fov. Called at boot (`0x00152DBC`) and after the options menu store (`0x00189D34`). *[PS2]*
- **`0x002292E0`** - Arms the 128 CrowdMan2d flash timers at event load, one visual/presentation RNG draw each. *[PS2]*
  - `0x00229340`: Timer-arming loop: one presentation RNG draw (via `0x003177F0`) per timer, 128 at event load. *[PS2]*
- **`0x002294C8`** - CrowdMan2d update entry; calls `0x00229530`. *[static]*
- **`0x00229530`** - CrowdMan2d flash timer update: for each registered slot (0..127, stride 0x40, registered when the slot word != -1) countdown -= 10*|cheer| + 4, with cheer from the audio call `0x002A77C8`(gp+0x410 = `0x004A3500`). On expiry draws c1 and c2 in [-1,1) from the visual/presentation RNG, spawns a camera flash at centre + axis1*c1 + axis2*c2, and re-arms with a third draw: 300 + r % 300 frames. *[PS2]*
  - `0x0022961C`: Return address of flash draw c1 (offset along axis 1), first of the two expiry draws. *[PS2]*
  - `0x00229638`: Return address of flash draw c2 (offset along axis 2). *[PS2]*
  - `0x002296D0`: Return address of the timer re-arm draw (300 + r % 300 frames). *[PS2]*
- **`0x0022A4A8`** - Appends type-8 (light glow) entities of visible cells to the `+0x7BC0`/`+0x7BC4` list; `0x0022A770` is a second routine doing the same. *[static]*
- **`0x0022A5A0`** - Static instance draw collector: an instance is drawn only when runtime (flags & 3) == 3, its location is active, its chunk is resident (instance `+0x7D`/`+0x7E`), and it passes the frustum test. *[PS2]*
- **`0x0022A698`** - Static terrain patch draw collector: requires the location active, the chunk (patch `+0x155`/`+0x156`) resident, then the frustum test. *[static]*
- **`0x0022A770`** - Second routine that appends type-8 (light glow) entities of visible cells to the `+0x7BC0`/`+0x7BC4` list (see `0x0022A4A8`). *[static]*
- **`0x0022B008`** - Contains the hand-off of the selected camera's view matrix to the renderer (vtable slot 0x114) described below. *[static]*
  - `0x0022B23C`: Copies the selected camera's `+0x40` matrix to the renderer through vtable slot 0x114 (range `0x0022B23C`..`0x0022B254`). *[static]*
  - `0x0022B250`: Slot 0x114 call of that view copy (used with `0x002D9270`). *[static]*

## `src/main/game.cpp`

Segment `0x0022C078`-`0x0022E180`.

- **`0x0022C708`** `cGame_renderFogVolumes` - Draw pass described as the world instance list draw: calls the fog0 sprite list `0x002DBF98` every frame and dispatches to a renderer slot `+0x10`. The renderer-side runtime bit-0 test is not traced. *[static]*
  - Possible mismatch with the current name: Name says fog volumes, but the records describe it as the world instance list draw that also calls the fog0 sprite list `0x002DBF98` every frame.
- **`0x0022C790`** `cGame_renderLightHalos` - Rebuilds the per-view light-glow list, then runs sun/glow processing `0x002E30D0`. Clears with `0x002E2F98` and adds with `0x002E2FF8` -> `0x002E2FA8` (record `+0x20` = source; `+0x2C`/`+0x2E`/`+0x28` cleared) into owner `+0x60+view*4` / `+0x68+view*0x3000`. A second list (`+0x7FC4`) is built with a3=2 (observed empty). *[static]*
- **`0x0022CD40`** - Builds the streaming location table `0x00442168`. *[static]*
- **`0x0022CEA8`** - Streaming location unload request, reached from connectors' Unload trigger volumes via stage builtin 68 (action 0) and from the in-world transport as (dest, 7). Rows outside the new residency row go states 1/2/6 -> 5 and 3 -> 0, rows in 4/8 are kept, skies and TRANSP are never released; wanted rows go 0/7 -> 3 and 5 -> 1. Old locations stop drawing the next pass, leave the octree 8 passes later, and new reads start at +9. *[PS2]*
- **`0x0022D088`** - Streaming location load request, used by Load trigger volumes (stage builtin 68 action 2), the initial load, and transport arrival as (dest, 7) (dome switch allowed). Moves wanted rows to load-and-activate/active states within the trigger tick (0/3/7 -> 4, 6 -> 8, 1/5 -> 2) and calls the default irradiance bank setup `0x0022E180`. A load entering a station fires the peak-run split; the Load trigger typically comes 629-665 ticks after the Unload. *[PS2]*
- **`0x0022D278`** - Residency-ready check; the transport loading loop `0x00236960` (screen 11 with the transport flag `+0x1C8`) waits on it until the destination rows are resident. *[static]*
- **`0x0022D6C8`** - RaceRideState gate handler (stage builtin 67; volumes in ARA1, BRA2, BHP1, ASS1, ABA1): in CTM free ride (event type 4) in world state 4 at a non-backcountry course, turns the ride into that course's event: sets event type and game mode, commits/clears the free-ride score, swaps the handler (e.g. race init `0x0023A108` via `0x00238160`) and requests world state 1 arg 1 via `0x00231250`(S,1,1,0); also calls `0x00144DF0`, `0x001451E8`, `0x0012B180`. No prompt, world load or streaming change; a 30-tick fade to black, venue fly-over, approach and round card follow. *[PS2]*
- **`0x0022D8D8`** - World loader/streamer pass driving the streaming location table, run once at the start of every game tick: (1) rows 5 -> 7, and 7 -> 0 at eviction 7 passes later, with any row in 5/7 blocking new load starts that pass; (2) 3 -> 6, 4 -> 8; (3) from the next pass one disc read at a time, priority sky 0.92 > TRANSP 0.91 > location 0.90, then lowest chunk index; (4) after the resolver delivers, next pass 6 -> 1 / 8 -> 2 and the next read starts. *[PS2]*
- **`0x0022DE58`** - Activates a sky row as soon as it reaches resident state 1; `0x0022DE98` then swaps the dome when the sky switch flag (`+0x1A4`) allows it. *[static]*
- **`0x0022DE98`** - Sky switch: replaces the active sky dome with a newly resident sky when the dome switch flag (`+0x1A4`) allows it. Probably also the region-list loop that handles mdl_<AREA>_<X>_skybox_trigger helpers (region indices 44..48) to switch skies at peak transitions (containing function not confirmed). *[static]*
- **`0x0022DF50`** - Updates the current course byte `0x00535C08` on the first streamer pass after a request. At a free-ride location crossing this is the only audio-relevant change (audio `+0x6254`/`+0x5814` stay 0, the song is unchanged). *[PS2]*
- **`0x0022E0E0`** - Patch location id lookup; called from `0x001218D0`. *[PS2]*

## `src/main/sectionman.cpp`

Segment `0x0022E180`-`0x0022E3B8`.

- **`0x0022E180`** `cSectionMan_setSky` - Sets the default rider irradiance (IRR lighting) bank `0x004A43C4` (gp+0x12D4) by course through jump table `0x0047B4E0`: APBR1 for courses 0, 5, 8, 14, 17; BPBR1 for 1, 11, 18; EPBR1 for 4, 7, 10, 13, 16, 21. Called from the location load `0x0022D088` (Load trigger and initial load). An empty Lighting reference (painter reset `0x002BE1F8`) reads this bank. *[static]*
  - Possible mismatch with the current name: Name suggests it sets the sky, but the records describe it selecting the default rider irradiance (lighting) bank per course; the sky dome swap is `0x0022DE98`.

## `src/main/gamerender.cpp`

Segment `0x0022E3B8`-`0x0022EBC8`.

- **`0x0022E840`** `cGameViewMan_updateAll` - Camera pass: for each camera calls the vtable at cam `+0x90`, slot `+0x1C` (`0x0015DF98`). Called from the race game update at `0x00230D7C`. *[static]*
- **`0x0022E968`** - Creates the in-game overlay UI sound listener. *[static]*

## `src/main/gameload.cpp`

Segment `0x0022EBC8`-`0x00232348`.

- **`0x0022EBC8`** `cGame_load` - Event load / game construction: seeds the roster generator from one presentation RNG draw per load (return address `0x0022EFF0`) via `0x00237CB0` -> `0x00317958`, calls the race outfit preparation `0x0014BD98`, and builds the race game-info. *[PS2]*
  - `0x0022ED5C`: Calls `0x0014BD98` (race outfit preparation). *[static]*
  - `0x0022EFE8`: Roster generator seeding call chain `0x00237CB0` -> `0x00317958`. *[PS2]*
  - `0x0022EFF0`: Return address of the roster seed presentation RNG draw (one per load). *[PS2]*
  - `0x0022F010`: Race game-info construction block: calls `0x001286A0`; interface marker `0x00458488` at `+0xCC`. *[static]*
- **`0x0022F6B0`** `cGame_loadTrack` - Calls the world audio load `0x002867E8`. *[static]*
- **`0x002302A8`** `cGame_restart` - Event restart: requests world state 1 arg 2. *[static]*
- **`0x00230338`** - Sets activation manager A `+0xD0` = -1 so the next section pass rescans. *[static]*
- **`0x00230360`** - Location unload start (row state 5 -> 7): drops the location's section instances, stage programs, entities, missions and collectible slot. Calls `0x00103308` (drop instances without leave handlers) and `0x00308FE0` (frees collectible slot ctx `+0x2C0`, drops the stage's WScript missions). *[static]*
- **`0x002306A8`** - Getter: returns *(a0+0x68+4*a1), the camera-splash object belonging to camera a1 (4 instructions); called from `0x00111890` when a rider's FX components are built. Not the race game update, which starts right after at `0x002306B8`. *[static]*
- **`0x002306B8`** - Race game update (race game vtable `0x0047D130` slot `+0x14`), once per game tick. Normal-path order: group 1 (`0x00354F98`), groups 5/6, `0x00355028` group-1 slot `+0x1C`, rider manager `0x00128AF0`, groups 2 and 3, WScriptMan `0x00309270`, CrowdMan2d, CrowdMan3d/MultiParticleMan/flush, group 4, cameras `0x0022E840`, then audio/HUD. Also opens the pause (Start at `0x00231840` -> overlay state 2 -> `0x00289B70` -> UI sound `0x00294F48`). `0x00230D24` is an alternate, probably frozen/pause, branch. Possibly also holds the streaming '+0x1D0 wait' while an active or activating location has no data (unconfirmed). *[PS2]*
  - `0x00230AFC`: Pause opened: UI sound 0 via `0x00294F48`, right after `0x00289B70`. *[static]*
  - `0x00230C54`: Start of the normal (unpaused) component order through `0x00230D18`: groups 1, 5, 6; `0x00355028` on group 1; world callback; groups 2, 3; other managers; drain `0x00354C98` group 1. Pause/debug branches differ. *[static]*
  - `0x00230C64`: Group-1 pass call `0x00354F98`(`0x004A5988` = gp+0x2898, 1): all world entities, newest first; script programs (LiveComp slot 5), static emitter seeds and DynamicParticle emitters draw here. Skipped when `0x004A2A50` (gp-0x6A0) & 2. *[PS2]*
  - `0x00230C70`: Group-5 pass call (`0x00244948`); no visual-RNG draws. *[PS2]*
  - `0x00230C7C`: Group-6 pass call (`0x00244948`); no visual-RNG draws. *[PS2]*
  - `0x00230C98`: Call `0x00355028`(`0x004A5988` = gp+0x2898, 1): group-1 slot `+0x1C` pass, gated with group 1; no draws. *[PS2]*
  - `0x00230CB0`: Rider manager call (`0x00128AF0`) via jalr through the vtable at *(s1+0xC)+0xCC (`+0x18`/`+0x1C`). *[static]*
  - `0x00230CCC`: Group-2 pass call `0x00354F98`(mgr, 2): snowfall, flag manager wind, camera splash; skipped when `0x004A2A50` (gp-0x6A0) & 0x10. Draws: flag wind 1 per wrap of its 1 s timer, camera splash 1 per tick (camera-0 object only). *[PS2]*
  - `0x00230CE8`: Group-3 pass call `0x00354F98`(mgr, 3): environment object and ScreenTint lightning (plus a `0x002EA900` object and two `0x002E46C8` objects, which don't draw); skipped when `0x004A2A50` (gp-0x6A0) & 4. Also runs in the `0x00230D24` branch. *[PS2]*
  - `0x00230CF0`: WScriptMan global-script update call (`0x00309270`). *[PS2]*
  - `0x00230CF8`: CrowdMan2d update call (`0x002294C8` -> `0x00229530`). *[PS2]*
  - `0x00230D00`: CrowdMan3d update call (`0x003440C8`); no draws. *[PS2]*
  - `0x00230D08`: MultiParticleMan update call (`0x00357BF8`); no visual-RNG draws. *[PS2]*
  - `0x00230D14`: Flush call `0x00354C98` after the crowd/particle managers. *[static]*
  - `0x00230D24`: Alternate branch taken when s0 = 1 (`0x00270280`(state) true and (`0x002379C8` == 0 or `0x0026CE50` != 0)): runs groups 5, 3, 4 and the cameras, skips groups 1, 2, 6, riders, WScript and crowd. Probably the frozen/pause path (unverified). *[unconfirmed]*
  - `0x00230D50`: Group-4 pass call (`0x002449F8` -> `0x002D21B0`); no draws. *[PS2]*
  - `0x00230D7C`: Camera pass call `0x0022E840` (skipped when game-flow S == 3). *[PS2]*
  - `0x00230DC0`: Start of the post-camera part: audio emitters, per-rider `+0x98`, HUD updates (no visual-RNG draws in the race). *[PS2]*
- **`0x00231250`** - Requests a world-state change (S, state, arg, 0). *[static]*
- **`0x00231840`** - Handles the Start press that pushes overlay state 2 (pause) from the game update. *[static]*
  - `0x00231840`: Start press that pushes overlay state 2 (pause) in the game update. *[static]*
- **`0x00231AB8`** - Contains the pause check that keeps Start from pausing during a cutscene. *[static]*
  - `0x00231AB8`: Pause handling check that stops Start from pausing during a cutscene. *[static]*

## `src/main/loadscreens_prestart.cpp`

Segment `0x00232348`-`0x00233438`.

- **`0x00232E20`** - cGameLoadState init: chooses and builds the event load state. If flag `0x004A19D8` (gp-0x1718) is set or game mode byte `0x00535BC8`+0x48 is 5 or 6, builds cGameLoadStateOutLodge (vtable `0x0047C878`, screen 118loadoutlodge); else if byte `0x00535BC8`+0x49 is 0 (Conquer the Mountain) cGameLoadStateConquer (vtable `0x0047C7A8`); otherwise (Quick Play) cGameLoadState (vtable `0x0047C948`). Screens come from GL.LUI (110ctrl_load / 99QPEvent / 102MPMatch). *[PS2]*
- **`0x00233048`** `cGameLoadScreen_loadTexture` - Loading screen routine that starts the loading music loop (`0x0028F768`); paired with `0x00233640`. *[static]*
  - Possible mismatch with the current name: Name suggests texture loading, but the only recorded role is starting the loading-screen music loop (`0x0028F768`).

## `src/main/gamestate.cpp`

Segment `0x00234AD0`-`0x00237CF8`.

- **`0x00234AD0`** `cGFGateState_gainFocus` - World state 3 (countdown) entry, paired with the update `0x00234C68`: countdown digits every 60 ticks from t3, GO at t182. Selects the Countdown race state for ordinary race modes; on the objectives overlay Continue, event kinds 4..6 go to the rolling start `0x00233AA0` instead of the Countdown `0x00113B10`. *[PS2]*
- **`0x00234BE8`** - GO routine; calls the GO handler `0x0029C7B0`. *[static]*
- **`0x00234C68`** `cGFGateState_update` - World state 3 (countdown) update, paired with `0x00234AD0`: dispatches StartgateOpen when the countdown field is nonpositive. *[PS2]*
- **`0x00234E20`** - Race tick routine; exact role not described. *[unconfirmed]*
- **`0x00234F40`** - World state 10 enter (Single Event / reload path): queues the event intro via `0x0027AAF8`; a new career's first visit queues FMV 29 plus the drop. At free-ride start it sets audio `+0x578C`/`+0x6254` and clears `+0x5790` for a new career. *[PS2]*
- **`0x00235080`** - World state 10 update, used for the new-career plane FMV and drop into Happiness. *[static]*
  - `0x002351A8`: First-arrival block: first CTM arrival at The Throne plays FMV 31 (EBC3), then ebc3_heli_arr (#127) and heli_arrb_<char>; later arrivals with the transport flag play the two lists without the movie. Black Top Station has no arrival cinematic. *[static]*
- **`0x00235AA0`** - World state 13: next heat (CTM gondola ride-up): world reset, gond_inair, then a per-character loop held until loaded, then world state 1 -> idle under the card. The final heat queues [4 start hut, 5 idle] (branch at `0x00235C58`, reads GMM `+0x98`). *[PS2]*
  - `0x00235C58`: Final-heat branch (reads GMM `+0x98`) that queues [4 start hut var1/var2, 5 idle]. *[static]*
- **`0x00236058`** - CTM world state 15 (session placement): calls `0x0011DE60`(rider, k + 1, 2) at the current course, then `0x0011DF18`. *[static]*
- **`0x00236208`** - World state 14 arg 0: lodge/station walk-in (cinematic list 22, lodge_arr3), then prompt 0x1F. *[PS2]*
- **`0x00236250`** - World state 14 transport handler part, paired with `0x00236418`: the transport arrives (cinematic list 11), then the Map overlay 0x21 opens. One reading lists this case as arg 2, another as arg 1. *[PS2]*
- **`0x00236418`** - World state 14 transport handler part (arg 1 in the source reading), paired with `0x00236250`. *[static]*
- **`0x00236960`** - Transport loading loop (screen 11 with transport flag `+0x1C8`): waits on the residency check `0x0022D278` while the destination rows stream in. *[static]*
- **`0x00236BB0`** - World state 2 enter: round/objectives card over the start-gate idle (overlay 8 '40race_pre', pause context 1); idle and world are frozen (script #73 time 1.0). Card enter plays UI sound 0xE and, for qualifiers, PA_Sponsor_Intro via `0x001FB588` -> `0x002A31C0`. *[PS2]*
- **`0x00236CD8`** - World state 2 exit: stops the idle NIS (`0x002790A0`), issues HUD commands 1 and 5, switches to the race camera (camera vtable `+0x28` with 3), starts race audio `0x002871B0`, and moves world state 2 -> 3. Race HUD flags 0x1530C047. *[PS2]*
- **`0x00236DA0`** - World state 7: results screen. *[static]*
- **`0x00236EE8`** - Calls the podium music `0x0028CDF8`. *[static]*
- **`0x00237948`** - Post-camera game-update step (no visual-RNG draws in the race). *[static]*
- **`0x002379C8`** - Condition for the race game update's alternate branch `0x00230D24`, which is taken when this returns 0 while `0x00270280` is true (role otherwise unconfirmed). *[unconfirmed]*
- **`0x00237CB0`** - Seeds the roster generator `0x004C9548` (calls `0x00317958`); called from the event load. *[PS2]*
- **`0x00237CD8`** - Roster RNG draw: calls `0x00317A08` on the roster generator `0x004C9548`. *[PS2]*

## `src/main/gamemode.cpp`

Segment `0x00237CF8`-`0x0023C808`.

- **`0x00237CF8`** `cGameModeMan_getGM` - Creates the GameModeMan event handlers and fills the handler table `0x00536668`. *[static]*
  - Possible mismatch with the current name: Name suggests a simple getter, but the records describe it creating the GameModeMan event handlers and filling the handler table `0x00536668`.
- **`0x00238160`** `cGameModeMan_initGameMode` - GameModeMan handler selection: in single player (`0x00535C11` != 2) maps the game mode byte through jump table `0x0047C0F0` into GMM `+4` (handler slot of table `0x00536668`), e.g. swapping the free-ride handler for the race/freestyle one. *[static]*
- **`0x00238348`** - Pause Restart: copies GMM `+0x74` (round just played) into `+0x70` (next round). *[static]*
- **`0x00238358`** - Step of the CTM finish chain `0x001251B8` -> `0x00238358` -> `0x00154AB8`. *[static]*
- **`0x00238510`** - Checkpoint bonus eligibility check, called with (G `+0xC0`, rider id, checkpoint). *[static]*
- **`0x00238B70`** - Ranks riders by score (called as (GMM, 2)); ranks a run against the round's five posted scores, clamped to 6th. *[static]*
- **`0x00238BF8`** - Ranks riders by time (called as (GMM, 10)); orders the Single Event results rows. *[PS2]*
- **`0x00238C80`** - Resets the race rules object on event choice: sets roster `+0x84` = 1 and round 0. *[static]*
- **`0x00238E20`** - Freestyle event handler (id 0) init (vtable `0x0047CFA0` slot `+0x10`): sets posted riders GMM `+0x14` = 4 for kind 1, else 5; sets GMM `+0x98` = 1 for round 3 only. *[PS2]*
- **`0x00239230`** - Freestyle event handler results (handler 0, vtable `0x0047CFA0` slot `+0x40`): stores scores[round][slot] = score `+0x198` (0 on DNF) and decides the round once every human has finished (`0x0012A250`). Heat 1: player's heat-1 score vs all heat 1 + heat 2, top 3 straight to the final; heat 2: combined, top 3 to the final else back to heat 1; final: 1st-3rd medal. An opponent still riding keeps 0 in heats but gets the `0x00122E50` estimate in the final; runs again for slot 1 if the opponent finishes later. Also sets rider `+0x2F8` by finishing place. *[PS2]*
- **`0x002398E8`** - Freestyle kind-1 checkpoint accept: adds value x 60 ticks to the time limit GMM `+0x78` while the new limit >= race ticks (each R&B checkpoint adds a minute); drives the '+60' popup together with `0x001194C0`. *[PS2]*
- **`0x00239938`** - Freestyle roster / opponent selection (e.g. Style Mile): player in GMM `+0x18`, peak rival in `+0x1C`, others shuffled into `+0x20`.. . In Single Event (`0x00535C11` != 0) the last shuffled character goes in `+0x1C`, so a Quick Play opponent is random. *[PS2]*
- **`0x00239AA0`** - Freestyle posting of the computer riders' scores for all rounds (via `0x001453D0`): n = GMM `+0x14`, live = GMM `+0x10` - n + 1. Slope style: slot 0 player, slot 1 riding opponent, slots 2..5 columns 0..3 (5th column unused); pipe/big air: slots 1..5 columns 0..4. Results at `0x00536640`. *[PS2]*
- **`0x0023A108`** - Race event handler (id 1) init (vtable `0x0047CF38` slot `+0x10`): builds the computer-rider roster (`0x0023A4F0`) and fills the heat slots; sets GMM `+0x98` = 1 for round 3 only. Single Event rebuilds the roster whenever an event is chosen (restart keeps it); career builds it in round 1 and reuses it. Heats: round 1 entries 0..4 -> slots 1..5; semi = qualifier top three without the human (`0x00536708`) + entries 5..7; final = rival + semi top three + entries 8, 9. *[PS2]*
- **`0x0023A4F0`** - Race roster build from the roster/lineup RNG `0x004C9548` (52 draws): two distinct Tricky cheat riders 10 + r%7, then 10 + r%6 (+1 if >= the first); base riders 0..9 in id order except the human's character and the peak rival (`0x00145750`); 25-swap shuffle `0x0023C770`; cheat skins go on the human's base character. Yields the five computer riders per human heat. *[PS2]*
- **`0x0023A668`** - Copies the heat's roster into *(gp-0x480 = `0x004A2C70`) `+0x18[]`/`+0x40[]` and then into the race copy `0x00535B20` (via `0x002342B8`), filling the computer rider slots with character ids. Value < 10 = that base rider; >= 10 = that cheat skin on the human's base character (why Snow Jam's Luther can have gameplay character 4 with Zoe as the human). *[PS2]*
  - `0x0023A700`: Loads each computer slot's character id from the roster copy (lw v1,0(a2)). *[PS2]*
- **`0x0023A760`** - Race event handler results (handler 1, vtable `0x0047CF38` slot `+0x40`): Qualifier/Semi Final/Final with 6 riders, top 3 advance, otherwise the same round repeats; final places 1-3 give gold/silver/bronze, other places complete the event without a medal. Decided when the player crosses the line; other riders' times use the estimate `0x00122D78`. Never reads the course. *[PS2]*
  - `0x0023A860`: Holds the race DNF time constant, 360000 ticks. *[static]*
- **`0x0023B170`** - Free-ride rules init (handler 2): sets GMM `+0x9C` = 1 (event complete from the start); no rounds, results or AI. *[static]*
- **`0x0023B268`** - Time challenge (peak race) init, handler 4. All Peak init sets GMM `+0x68` = 16 (start at The Throne). *[static]*
- **`0x0023B468`** - Time challenge (peak race) results, handler 4. *[static]*
- **`0x0023B5F8`** - Time challenge split (handler 4): when a location load `0x0022D088` enters a station (current course 17..21), shows the difference to tier row split k for 5 s as +-H:MM:SS, with split time = int(ticks x 0.016666668) - split. Five splits in modes 8/11. *[static]*
- **`0x0023B6C0`** - Rival Time init (handler 5): two riders, the peak rival (`0x00145750`) in the slot after the player, round 1, no time limit. Sets GMM `+0` = 1, `+0x10` = 1, `+0x14` = 0, `+0x68` = `+0x6C` = -1, `+0x70` = `+0x74` = 1, `+0x78`..`+0x94` = 0, `+0x98` = 1, `+0x9C` = 0; lineup `+0x18[]`/`+0x40[]` memset -1; slot `0x00146E98`(profile,0) gets `0x00147398` (player character), the next slot gets the rival with `+0x40` = 0. *[static]*
- **`0x0023B8C8`** - Rival Time results per finishing rider (handler 5 slot `+0x40`): DNF/give-up (`+0x480`) stores time 360000 (0x57E40) and gave-up 1, else time = rider `+0x478`. When the human finishes, unfinished riders (`+0x470` < 0) get the estimate `0x00122D78`, then `0x00238BF8`(GMM, 10) ranks and `+0x9C` = 1. Win (place 0 and `+0x480` == 0): rider `+0x100` = 1, GMM `+0x84` = 1, `+0x74` = `+0x70`, `+0x70` = 0; otherwise `+0x100` = 0 and the round stays. *[static]*
- **`0x0023BB98`** - Rival Points init (handler 6): as Rival Time plus the freestyle time limit GMM `+0x78` = `0x001454F8`(profile, 1) x 60 and `+0x88` = 1 (the Happiness row gives 300 s). *[static]*
- **`0x0023BDB8`** - Rival Points results (handler 6 slot `+0x40`): score from score object `+0x198` (0 with gave-up 1 when `+0x480` is set); when all humans are done, unfinished riders get the points estimate `0x00122E50`, then `0x00238B70`(GMM, 2) ranks by score. Win = place 0 and not given up. *[static]*
- **`0x0023C0D0`** - Points challenge (peak jam) init, handler 7. *[static]*
- **`0x0023C2D8`** - Points challenge (peak jam) results, handler 7. *[static]*
- **`0x0023C560`** - Points challenge per-tick/split handler (handler 7): at station entry shows score - split x 100. *[static]*
- **`0x0023C770`** - Shuffles the race roster: 25 swaps of entries r%10 and r%10 drawn from the roster RNG. *[PS2]*

## `src/main/ssxappdtor.cpp`

Segment `0x002438F0`-`0x00245950`.

- **`0x00244478`** - Update of the entity-group-3 object that drives the environment: calls *(obj+0x10)'s vtable (at `+0x44`) slot 0x14. (A heap object at run time.) *[static]*
- **`0x00244880`** - Not one function: this range spans several functions, including the alternate game update body at `0x00244E60` (a copy of the game update used by `0x00233C10`) with the same pause-open path and entity-group pass calls to `0x00354F98`. *[static]*
  - `0x00244DF0`: Pause opened in the game update copy: UI sound 0 via `0x00294F48`. *[static]*
  - `0x00244F94`: Start of the entity-group pass calls (`0x00354F98`) in the alternate game update, through `0x00245074`. *[static]*
- **`0x00244948`** - Entity group pass used for groups 5 and 6 in the race game update. *[static]*
- **`0x002449F8`** - Entity group-4 pass; calls `0x002D21B0`. *[static]*
- **`0x00244E60`** - Alternate game update body: runs the entity-group passes (`0x00244F94`..`0x00245074`) and the camera pass (`0x002450A0`) in the same order as the race game update `0x002306B8`. Lies inside the range that starts at `0x00244880`. *[static]*
  - `0x002450A0`: Camera pass call in the alternate game update. *[static]*
- **`0x002453E0`** - Panel sound query for the pre-race/results/toptimes/bc_fail/progressive panels: Cross gives UI sound 3, other buttons 0. *[static]*
- **`0x00245418`** - cGameLoadState enter (vtable `0x0047C948`, slot not given): opens 99QPEvent (course card), or 102MPMatch when byte `0x00535C11` is 2. The card fades in over about 20 frames and no input skips it. *[PS2]*
- **`0x00245730`** - cGameLoadStateConquer enter (vtable `0x0047C7A8`, slot not given): opens the 110ctrl_load Basic Controls load screen (Default layout: grab L1/L2 R1/R2, boost/tweak Square, jump Cross, turn/spin/flip D-pad, turn left stick, reset Select). *[PS2]*

## `src/main/debugmenu.cpp`

Segment `0x00247E60`-`0x00251718`.

- **`0x00249148`** `cLightGlowMenu_cLightGlowMenu` - Contains the debug-menu build for the glare pass globals (gp+0x12D8..gp+0x1308, `0x004A43C8`..`0x004A43F8`) described below. *[static]*
  - `0x00249200`: Glare debug-menu items: Enable, Override World Painter, PS2 Capture Size (2^x), Minimum Intensity Cutoff, Post-Cutoff Scale, Copy/Frame Source/Frame Blend Intensity, Blend Texture 0..3, Texture Jitter. *[static]*
- **`0x0024A228`** `cScreenTintMenu_cScreenTintMenu` - ScreenTint tweakables debug menu: tint colours, lightning enable/frame/chance, flash phases, intensities, colours at gp+0x1500.. (`0x004A45F0`..). *[static]*
- **`0x0024BF60`** `cSplashTogglesMenu_cSplashTogglesMenu` - Camera Splash Menu tweak menu, presumably its builder, with values at gp+0x115C..gp+0x11A4 (`0x004A424C`..`0x004A4294`). *[unconfirmed]*
