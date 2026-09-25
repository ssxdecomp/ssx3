<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/scripter/

## `src/scripter/datamanager.cpp`

Segment `0x00275828`-`0x00278358`.

- **`0x00276388`** - NIS step start: sends HUD command 0 (hide HUD) at every step start. *[PS2]*
- **`0x00276F48`** - NIS skip: on Cross (NISSkip) cuts to the next step with no fade. *[static]*
- **`0x00277980`** - NIS step fade handling: a list's first step fades in with its own fade-in record, later steps with the previous step's fade-out record; starts the fade via `0x002E4370`, and the script clock starts after out + hold. *[PS2]*
- **`0x00277C08`** - NIS list hold step, called from `0x00279040`. *[static]*
- **`0x00277DE8`** - NIS step fade-out: calls `0x002E44F0` over the step's last ticks. *[PS2]*

## `src/scripter/ssxscriptengine.cpp`

Segment `0x00278358`-`0x00281F30`.

- **`0x00278358`** `cSSXScriptEngine_Load` - Associated with NISLists: two NIS list players, each a 5-step FIFO {list or script, flags, D, E, F}, with the manager at [gp-0x84C] (`0x004A28A4`). *[static]*
- **`0x00278B98`** - Preloads a location's NIS scripts (scdat_<LOC>.big) together with the location; calls `0x0027B370`. *[static]*
- **`0x00278DE8`** - Transport departure sequence step (state 14 arg 1, after the overlay); works with `0x0027A860` and `0x00279148`. *[static]*
- **`0x00278E20`** - Adds an FMV step (movies 29-31) to an NIS list. *[static]*
- **`0x00278E50`** - Adds an NIS step from a choice list; used for example to play cinematics 0x16 + 0x17 (lodge walk-in, world state 14 arg 0). *[static]*
- **`0x00278F38`** - Starts an NIS list (one of the pair `0x00278F38`/`0x00278F68`). *[static]*
- **`0x00278F68`** - Starts an NIS list (one of the pair `0x00278F38`/`0x00278F68`). *[static]*
- **`0x00279040`** - Holds the NIS list (via `0x00277C08`) when the fly-over ends before the riders are loaded. *[PS2]*
- **`0x00279070`** - Advances an NIS list to the next step. *[static]*
- **`0x002790A0`** - Clears an NIS list; also stops the start-gate idle when the round card closes. *[static]*
- **`0x00279148`** - Transport departure sequence step (with `0x00278DE8` and `0x0027A860`). *[static]*
- **`0x002797A0`** - Non-race caller of the visual RNG `0x003177F0` (load/menu/replay-time consumer). *[static]*
- **`0x002797C8`** - NIS load-group loader: streams a script's .big group (script, animation bank, sound bank) on demand. *[static]*
- **`0x00279A70`** - Chooses one alternative per NIS script track: actor tracks keep only alternatives whose character mask matches the bound rider, then pick rand() % n. *[static]*
- **`0x00279F18`** - Returns the character used for BC_Challenge / Hey contact speech. *[static]*
- **`0x0027A0D8`** - Resolves an NIS anchor frame from table `0x00481D00`: p = Rz(yaw) Ry(-pitch) [ext rotation * p + ext.t] + pos. *[PS2]*
- **`0x0027A860`** - Queues the transport ride NIS lists (world state 14 arg 1), part of the transport departure sequence with `0x00278DE8`/`0x00279148`: heli when either end is backcountry, else gondola: [12 heli_dep / 18 gond_dep (flags 1)] -> [13 heli_inair / 19 gond_inair (0)] -> [14/20 per-character in-air (8, held until loaded)]; departure only from stations. Also starts the travel music via `0x0028E8C0`(20, 1). *[PS2]*
- **`0x0027AAF8`** - Queues an event-intro NIS list from a list table (`0x00481E68` Single Event, `0x00481E48` CTM). CTM (world state 1 arg 1): [2 fly-over, flags 0] -> [3 approach, flags 3] -> [5 idle, flags 0]; Single Event: [4 start hut, flags 3] -> [5 idle, flags 0]. *[PS2]*
- **`0x0027AC60`** - Queues the podium NIS list (table `0x00481E90`) and the rival challenge when due. Podium: winner win_ps_<char>, 2nd, 3rd, fallback placeshow_ps; D/E/F = places 1-3. Rival (not for cheat skins 10-20) uses `0x001464D0` unlocked, `0x00146150` not shown, `0x00146320` marks shown; rival D is the race's first computer rider (list +0x48). *[PS2]*
- **`0x0027B0C0`** `cSSXScriptEngine_GetScriptFromCategory` - NIS ScriptChoice: picks a cutscene script per location from scfilter data. Keeps entries whose non-zero masks all intersect the condition words built by `0x0027BDB8` (CHARDB rider bits), then the least played, then rand % n via the visual RNG `0x003177F0` (non-race caller); scripts listed three times are three times as likely. *[PS2]*
  - `0x0027B214`: Visual-RNG draw site hit during load-time audio/HUD set-up (presumably the random candidate pick). *[PS2]*
- **`0x0027B370`** - Location NIS preload step, called from `0x00278B98`. *[static]*
- **`0x0027B750`** - Returns the start-grid node (AIP kind-0 row of the rider's slot) for NIS anchors 1-18. *[PS2]*
- **`0x0027BB08`** - Locator lookup (world record kind 18): pos = matrix row 3, yaw = atan2(m01, m00), pitch = asin(m02). *[PS2]*
- **`0x0027BDB8`** - Builds the ScriptChoice condition words as 1 << CHARDB base character per rider role: words 0-2 participants D/E/F, 3-4 humans, 5-9 computer riders, 10-14 second list, 15-20 race riders 0-5; a cheat skin counts as its base rider. *[static]*
- **`0x0027C9B0`** - Builds the contact list used by the speech-id dispatch at `0x00123E30`. *[static]*
- **`0x0027F9F8`** - NIS actor start (with `0x001241C0`). *[static]*
- **`0x00280640`** - NIS kind-7 audio/control object handler: stage-script calls, music codes (-> `0x0028E8C0`(code, 0), e.g. code 21 for the fly-over), PA/DJ cues, sounds, weather off. *[PS2]*
- **`0x002808E8`** - Contains NIS kind-7 audio code: the PA/DJ cue dispatch call and the CHARACTER-bus sound start below. *[PS2]*
  - `0x00280B3C`: Kind-7 handler call site of the PA/DJ cue dispatcher `0x002A19D8`. *[PS2]*
  - `0x00280F3C`: Channel 3 sound start block: plays an NIS sound on the CHARACTER bus at speaker 0's gain (`0x00287968`(audio, 4, 0) -> `0x002906B8`), volume 127, NIS bank slots 17 + group. *[PS2]*
- **`0x00281018`** - NIS cut-list director (kind-4 object), with `0x002816A0`: selects the active camera per range. *[static]*
- **`0x002816A0`** - NIS cut-list director function, paired with `0x00281018`. *[static]*
