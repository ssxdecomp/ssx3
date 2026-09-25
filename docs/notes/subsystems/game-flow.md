# Game modes, race flow and career

SSX 3 decides what kind of event runs through a GameModeMan that maps the game-mode byte to a mode handler; the
handler sets up rounds, the rider lineup, posted scores and time limits, and turns each finished rider
into a round result. Around it, a world-state machine sequences the intro cutscenes, the round card, the countdown,
the finish, podium, results and the way back to free ride, while a separate race clock inside the `cAI` game-info
object counts pre-race, countdown and race ticks. The back-end (BE) interfaces hold the persistent career: course
and peak tables, medals, cash, goals, locks, records, attributes, shops and awards.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

Translation units per the current decomp split:

- `src/main/gamemode.cpp`: the GameModeMan (`0x00237CF8` `cGameModeMan_getGM`, `0x00238160`
  `cGameModeMan_initGameMode`), the pause-restart helper `0x00238348`, the rankers `0x00238B70`/`0x00238BF8`, and
  every mode handler's init and results functions (`0x00238E20`..`0x0023C560`).
- `src/main/gamestate.cpp`: the gate/countdown state (`0x00234AD0` `cGFGateState_gainFocus`, `0x00234C68`
  `cGFGateState_update`), next heat `0x00235AA0`, transport `0x00236250`, the round card `0x00236BB0`/`0x00236CD8`.
- `src/fe/festateloadscreen.cpp`: world state 1 (`0x002341D0`, `0x002343B0`, `0x00234750`), finish `0x00233C50`,
  the post-finish wait `0x00233CD8`, the no-countdown start `0x00233AA0`.
- `src/main/game.cpp`: the free-ride event gate `0x0022D6C8`. `src/main/gameload.cpp`: `0x0022EBC8` (`cGame_load`),
  `0x002302A8` (`cGame_restart`), the world-state request `0x00231250`.
- `src/be/beintnewrace.cpp`: race settings (`0x00144D98` `cBENewRaceInterface_setNumberAI`, `0x00144DF0`
  `cBENewRaceInterface_setGameMode`, `0x001451E8` `cBENewRaceInterface_setGameEvent`), course peak `0x00144C78`,
  posted scores `0x001453D0`, time limits `0x001454F8`, platinum `0x001456A0`, peak rival `0x00145750`.
- `src/be/beintplayer.cpp` (profile, `0x00147398` `cBENewPlayerInterface_getRiderCharID__FPvi`, difficulty
  `0x00147D20`/`0x00147E18`), `src/be/beintstat.cpp` (attribute getters), `src/be/beintscore.cpp` (medals and cash),
  `src/be/beintreward.cpp` (goals, awards, rewards, songs), `src/be/beintecon.cpp` (attributes, gear inventory),
  `src/be/beintbagt.cpp` (uber tricks), `src/be/belibrary.cpp` (`0x0014AB68` `cBELibrary_getScoreType`, gear
  purchase), `src/be/beintaggression.cpp` (rider relationships).
- `asm/14B10.s`: the race clock (`0x00113B10` `cAI_setAIState`, `0x00113B48` `cAI_forceAIState`, `0x00113C20`,
  `0x00113D38`, `0x00113DB0`).
- `src/ai/ai.cpp`: `0x001286A0` (`cAI_cAI`), `0x00129E20` (`cAI_initComputerRiders`), rider loading and grid
  placement, the all-humans-finished test `0x0012A250`, the start-gate controller `0x0012BE20`..`0x0012C408`.
  `src/ai/rider.cpp`: finish `0x00125108`, time limit `0x00125228`, give up `0x001253D0` (`cRider_quitEvent`),
  finish estimates `0x00122D78`/`0x00122E50`. `src/ai/computer.cpp`: course progress, path events, ranking.
  `src/ai/ridermetrix.cpp`: the score object and checkpoint bonus.
- `src/fe/ovstatehud.cpp` (HUD: `0x001EA930`, `0x001EC3F8` `cOVStateHUD1P_onRender2D`), `src/fe/fepopupmisc.cpp`
  (results rows), `src/fe/ovtemplatedialog.cpp` (pause and results dialogs, `0x0020D590`
  `cOVTemplate_Dialog_onWidgetEvent`), `src/fe/uitemplatemap.cpp` (the transport map), `asm/1137E8.s` (finish banner
  and finish panel).
- `src/scripter/datamanager.cpp`, `src/scripter/ssxscriptengine.cpp` (cutscene lists and fades), `src/sound/*.cpp`
  (event music and announcer cues).

## Globals and settings

| Address | Meaning |
|---|---|
| `0x004A28A8` (gp-0x848) | G, the game object. G+0x84 = the race world S, G+0xC0 = the GameModeMan (GMM) |
| `0x004A2C68` (gp-0x488) | a second copy of S |
| `0x004A2C70` (gp-0x480) | GMM pointer as used by the mode handlers (one note gives `0x004A2C6C` instead; unresolved) |
| `0x004A28A4` (gp-0x84C) | the cutscene (NIS) manager |
| S+0x0C | game-info / race clock object (`cAI`), constructed in `cGame_load` at `0x0022F010` through `0x001286A0` (`cAI_cAI`); interface marker `0x00458488` at +0xCC |
| S+0x214 | world state (next section but one) |

Race settings block:

| Address | Meaning |
|---|---|
| `0x00535C04` | number of computer riders to spawn (`cBENewRaceInterface_setNumberAI`; GMM+0x10 − GMM+0x14) |
| `0x00535C08` | course index |
| `0x00535C10` | event type: 4 free ride, 5 time challenges (including Rival Time), 6 points challenges (including Rival Points); other values not described |
| `0x00535C11` | game type: 0 Conquer the Mountain (CTM), non-zero Single Event / Quick Play, 2 multiplayer (read as "single player" when ≠ 2) |
| `0x00535C12` | game mode (table below) |

The gate code sets the event type with `cBENewRaceInterface_setGameMode` and the game mode with
`cBENewRaceInterface_setGameEvent`, so the decomp's "GameMode" setter writes what these notes call the event type.

Game modes (names at `0x0043E978`):

| Mode | Event | Mode | Event |
|---|---|---|---|
| 0 | Race | 6-8 | Time Challenge, Peaks 1-3 (peak race) |
| 1 | Slope Style | 9-11 | Points Challenge, Peaks 1-3 (peak jam) |
| 2 | Half Pipe (super pipe) | 12 | Free ride |
| 3 | Big Air | | |
| 4 | Rival Time | | |
| 5 | Rival Points | | |

## GameModeMan

`cGameModeMan_initGameMode` (`0x00238160`): in single player (game type ≠ 2) the mode byte indexes the jump table
`0x0047C0F0`, and the result is stored at GMM+4 as an index into the handler table `0x00536668`, whose objects are
created by `0x00237CF8` (`cGameModeMan_getGM`). The multiplayer mapping is not described.

| Mode | Event | Handler | vtable | init (vt+0x10) | results (vt+0x40) |
|---|---|---|---|---|---|
| 0 | Race | 1 | `0x0047CF38` | `0x0023A108` | `0x0023A760` |
| 1-3 | Slope style / pipe / big air | 0 | `0x0047CFA0` | `0x00238E20` | `0x00239230` |
| 4 | Rival Time | 5 | `0x0047CD30` | `0x0023B6C0` | `0x0023B8C8` |
| 5 | Rival Points | 6 | `0x0047CCC8` | `0x0023BB98` | `0x0023BDB8` |
| 6-8 | Time challenge | 4 | `0x0047CD98` | `0x0023B268` | `0x0023B468` |
| 9-11 | Points challenge | 7 | `0x0047CC60` | `0x0023C0D0` | `0x0023C2D8` (plus per-tick `0x0023C560`) |
| 12 | Free ride | 2 | `0x0047CE00` | `0x0023B170` | - |

The results method is called once per finishing rider, with that rider's slot.

### GMM fields

| Offset | Meaning |
|---|---|
| +0x00 | current round (1 qualifier / heat 1, 2 semi / heat 2, 3 final) |
| +0x04 | handler index |
| +0x08 | the handler's copy of the game mode ("kind") |
| +0x10 | number of other riders (race 5, freestyle 5, rival 1) |
| +0x14 | number of posted (non-riding) riders: 4 slope style, 5 pipe and big air, 0 rival |
| +0x18[slot] | character per slot (+0x18 the player, +0x1C the peak rival, +0x20.. the rest) |
| +0x40[slot] | a second per-slot array (memset −1 by the rival init, the rival's entry set to 0; meaning not given) |
| +0x68, +0x6C | set to −1 by the rival init |
| +0x70 | next round |
| +0x74 | round just played |
| +0x78 | time limit in ticks (0 = none) |
| +0x84 | "fresh event" flag; set to 1 on a rival win |
| +0x88 | time limit enabled |
| +0x94 | differs for big air; no reader found |
| +0x98 | final-round flag (selects the final's start-hut cutscene); set to 1 by the rival init |
| +0x9C | event complete |

Per-slot result arrays in `.bss`: `0x00536640` times or scores (posted freestyle scores appear here), `0x005366A8`
the rival handlers' gave-up flags, `0x005366D0` the give-up flag set by `cRider_quitEvent` (read by the results rows
and the finish panel), `0x00536730` place per slot. Rankers: `0x00238B70(GMM, n)` sorts by score, `0x00238BF8(GMM, n)`
by time. The pause menu's Restart goes through `0x00238348`, which copies +0x74 into +0x70 so the same round is
replayed.

## Race clock (`cAI` states)

The race clock lives in the game-info object (S+0x0C). `0x00113B48` (`cAI_forceAIState`) holds the state names and
handler selection:

| State | Name | Enter / update |
|---|---|---|
| 1 | GameInit | update selects Freeride |
| 2 | Freeride | enter clears the race-enabled flag +0x14; update selects Race |
| 3 | PreRace | enter clears race ticks and the handler-local +0xB8 |
| 4 | Countdown | enter (`0x00113D38`) sets +0x1C to the literal 180; update decrements a positive count, otherwise selects Race; exit clears the count |
| 5 | Race | update (`0x00113DB0`) increments race ticks before the rider update; requests EndRace/results when every human has finished |
| 6 | EndRace | external finish notification; race ticks stop |
| 7 | Shutdown | requests external cleanup |

`0x00113B10` (`cAI_setAIState`) only records the requested state and keeps the previous handler. `0x00113C20` runs
the old state's exit and the new state's entry on the following update, then the current handler; a transition
requested during that update waits for the next one. Game-info fields: +0x08 total simulation ticks (incremented near
the end of the per-tick world update, at `0x00129134` inside `0x00129100`; the notes treat this as the tail of
`0x00128AF0`), +0x0C race ticks, +0x14 race enabled, +0x1C countdown count, +0x74 rank mode (1 by time, 2 by score),
+0x78 event riders.

Snapshots **(PS2)**: the ready state before a race is state 3, previous 0, total and race ticks 0; a countdown
savestate has total ticks 18, race ticks 0, count 162, with all six riders stationary in control 6 / motion 3; a
mid-race state is 5 with 338 total and 158 race ticks.

## World states (S+0x214)

Requested with `0x00231250(S, state, arg, 0)`.

| State | Role | Code |
|---|---|---|
| 1 | cutscene list before a round (arg 1 = CTM intro, arg 2 = restart), computer-rider loading | enter `0x002341D0`, update `0x002343B0`, exit `0x00234750` |
| 2 | round card over the start-gate idle | enter `0x00236BB0`, exit `0x00236CD8` |
| 3 | gate / countdown | `0x00234AD0` (`cGFGateState_gainFocus`), `0x00234C68` (`cGFGateState_update`) |
| 4 | playing (free ride or an event run) | |
| 5 | finished | `0x00233C50`; post-finish wait `0x00233CD8` |
| 7 | results | |
| 10 | Single Event / reload path (not used by the free-ride gate) | |
| 12 | podium (final only) | |
| 13 | next heat | `0x00235AA0` |
| 14 | transport after an event (arg 2) | `0x00236250` |
| 15 | return to free ride on the same course | |

## CTM: starting an event from free ride

### The gate

- Each event course has a `*_RaceRideState_0` trigger volume at its start area. Its program calls stage builtin 67
  (handler `0x00302048`, listed under `0x002FC2C0`): human rider only, key1 = 0, and key0 checked through the entry
  table `0x00445E40` (value 1 marks the FreeRideState volumes, which are rejected). It ends an active Big Challenge
  (`0x0030B7F8`) and calls `0x0022D6C8`.
- `0x0022D6C8` requires CTM, event type 4 (free ride), a course outside the backcountry, and world state 4. It sets
  the course's event type and game mode, commits and then clears the free-ride score (`0x0012B180`), replaces the
  free-ride handler with the event's through `cGameModeMan_initGameMode` (for a race, init `0x0023A108`), and requests
  world state 1 with arg 1.
- There is no prompt, no pending-event record, no world load and no streaming call: the location's resident data stays
  and the free-ride tick keeps counting. World state 10 is not used. No DJ line, Radio_Big_Intro or Free_Ride_Intro is
  posted (the world-load audio `0x002867E8` does not run). The 4 → 1 transition was observed when the rider rode into
  the volume, including with a neutral pad **(PS2)**.

### World state 1: intro list and rider loading

- Arg 1 queues the CTM intro list (`0x0027AAF8`, table `0x00481E48`): group 2 venue fly-over (flags 0), group 3
  approach (flags 3), group 5 start-gate idle (flags 0). The approach script is chosen at random on every entry
  (Snow Jam has eight approach variants; repeated Metro-City entries played different ones **(PS2)**).
- The computer riders are created a tick after the gate (`0x00128958`, `0x00129E20` `cAI_initComputerRiders`) and
  load one step per tick (`0x001296F8` → `0x0011C298`) while the fly-over plays. The "Loading..." caption
  (`0x001F30D8`, world-state bit 2) stays up until every rider is loaded (`0x0012A180`); if the fly-over ends first
  the list is held (`0x00279040` → `0x00277C08`) (a 7-tick black hold at Metro-City **(PS2)**).
- Riders are placed on the start grid only when the list reaches the idle (`0x001289F0` → `0x001297C8` →
  `0x0011D390`, start-grid control 6).

### Presentation timeline (PS2)

Frame timings below were read from PS2 recordings of Snow Jam and Metro-City; the code references come from the code.

| Moment | On screen and in the audio | Code |
|---|---|---|
| WS1 enter | free-ride view keeps running, HUD hidden (HUD command 0 at each cutscene step start), letterbox bars slide in 2 lines a tick (full after 30), yellow "Loading..." with a spinning snowflake, view fades to black over 30 ticks | fly-over header fade-in record {out 30, hold 0, in 30}: `0x00277980` → `0x002E4370`; HUD command `0x00276388`; the script clock starts after out + hold (+0xB8) |
| fly-over t0-30 | fades in from black, bars full, caption over the fade | same record |
| fly-over t0 | music code 21 (24 at Metro-City, 23/25 for freestyle): the free-ride song fades out over 1 s, the next playlist song is forced 3 s later (PlayMusic 36) with the EA RADIO BIG box | `0x00280640` → `0x0028E8C0(21, 0)` → `0x0028D488`, `0x002B3D48(1.0)`, `0x002ADCA0(3000, kind 3)` |
| fly-over t30 | PA_Venue_Intro (speech 0x20BB) | kind-7 cue 0xF → `0x002A19D8` → `0x002A39E0` |
| fly-over | the script's own sound (bank slot 18 = the location's `scdat_<LOC>`, sound 0) on the CHARACTER bus at speaker 0's gain | `0x00280F3C` inside `0x002808E8`: `0x00287968(audio, 4, 0)` → `0x002906B8` |
| fly-over end | fades to black over its last 30 ticks (fade-out record {out 30, in 0}) | `0x00277DE8` → `0x002E44F0` |
| approach t0 | hard cut, bright at once ("Press ✕ to skip"); the approach's own fade-in record is not used | `0x002E44F0` rewrote the running fade's in phase to 0 |
| approach t0 | PA_Rider_Race_Intro (0x20C2; freestyle approaches use PA_Rider_Intro 0x20C1) | cue 2 → `0x002A3358` (cue 1 → `0x002A32B0`) |
| approach end | fade to black over 30 (fade-out record {out 30, in 30}) | |
| WS2 enter | the start-gate idle fades in over 30 under the round card; the card grows in (title bar from the left over ~12 ticks, then frame, box, text at ~33); Cross is ignored until it is open | `0x00236BB0`: overlay 8 `40race_pre`, pause context 1 (idle and world frozen) |
| card enter | UI sound 0xE; PA_Sponsor_Intro in the qualifier only | `0x001FB588` → `0x002A31C0` |
| Cross | card gone after 5 samples, hard cut to the race camera, race HUD, EA RADIO BIG box back; WS 2 → 3 | `0x00236CD8`: `0x002790A0` stops the idle, HUD commands 1 and 5, race camera (vt+0x28(3)), race audio `0x002871B0` |
| countdown | digits 3, 2, 1 every 60 ticks from t3, GO at t182; beep sound 0x4E; at GO the DJ artist intro (round 1) or PA_Medal_Run_Intro (final) | `0x00234AD0`, `0x00234C68`, `0x0029C420`, `0x0029C7B0` |

Announcer (PA) lines do not duck other audio.

### Cutscene list mechanics

- Fades chain through `0x00277980`: the first step of a list uses its own fade-in record; each later step fades in with
  the in-ticks of the previous step's fade-out record (which is why the approach cuts in bright). The held gondola
  ride-up of a next heat fades out before it is released **(PS2)**.
- Cutscene sounds play on the CHARACTER bus at speaker 0's gain (`0x00280F3C`); actor sounds are positional at the
  actor root.
- `0x002A19D8` kind-7 announcer cues: 1 Rider_Intro, 2 Rider_Race_Intro, 7 Medals, 0xF Venue_Intro.
- Cutscene music codes (`0x00280640`): 19/20 do nothing when the second argument is 0; 21-25 pick the next song, fade
  out over 1 s and force PlayMusic(36) after 3 s; other codes post a Pathfinder music event.

### Start-gate controller (rider control 6)

- The controller state lives at owner +0x290 (phase, steady time, low/high, pose). `0x0012BF68` dispatches the phase
  functions `0x0012C230`, `0x0012C408`, `0x0012C0C0`, `0x0012C130`; `0x0012C028`/`0x0012C078` are the release gates.
- Entry `0x0012BE20`: copies the reference stance into the active and animation mirror, clears the animation graph,
  resets the root translation, requests a root half-angle of −π/2 when riding switch (negative zero otherwise),
  chooses animation semantic 1 when the incoming phase is 2 and semantic 0 otherwise, and clears all four phase
  values.
- Input is the GateAnticipate action (action 26, mapped at `0x00127DFC`..`0x00127E04` inside `0x00127998`), a signed
  6-bit value in bits 12..17 of command word 0.
- Phase 0 updates the lean and computes a timed push-off; the timed formula applies while steady time < 0.4. Phase 1
  handles the crouch, launch velocity and the hand-off of motion. Phases 2/3 follow the manual-start animation rules.
  Boost is stopped while this controller runs. The attribute tilt comes from `0x00115AB0` as 75 − 90 × the resolved
  attribute.
- The start pose is a kind-8 animation driver: entry 8 of the driver table `0x00456950` points to `0x001037E0`
  (inside `0x00103578` in the current split), which calls `0x001045D8`. It seeks slot 0 to duration × owner+0x2A0
  and only advances fades, so the pose does not play with time. Semantic 0 resolves to leaf 0 / clip 8192.

### Rolling start (no countdown)

`cGFGateState_gainFocus` (`0x00234AD0`, entered when the round card is dismissed) selects Countdown with
`cAI_setAIState` for ordinary events, and `cGFGateState_update` (`0x00234C68`) dispatches StartgateOpen once the
countdown field is not positive. Event types 4..6 (free ride, time challenges, points challenges) are sent to
`0x00233AA0` instead, which takes the clock straight from PreRace to Race. In the Happiness rival ready state both riders
already sit at their start spots in control 0 / motion 0 with a start velocity, and on game tick 0 both leave the
ground; race tick 1 follows tick 0 **(PS2)**. The Cross that closed the card is still held on the first race ticks,
so control 0 requests control 2 on the departure tick (`0x001162C8`) and the rider stays in control 2 in the air
until it is released (then control 5) **(PS2)**.

## Course progress, checkpoints and the finish

- Course paths come from the location's AIP resource (Snow Jam: SSB kind 14, track 8, resource 0; 63,148 bytes with
  129 AI paths and 8 track paths). A raw segment is a float4: horizontal direction X/Y, vertical change per horizontal
  unit Z, horizontal segment length W. Every track-path origin and segment matches the runtime copy byte for byte
  **(PS2)**. The global path manager is `0x004D33A0` (count +0x10, array +0x14); runtime path records have a stride
  of 60.
- `0x0026A638` projects a position onto a path (horizontal metric, segment clamping, closest-point ties, a cached
  forward search reaching 3000 cm past the cached segment start; a valid cached interior projection can stop early).
  `0x001127F0` selects the path (three candidates ordered by bounding box through `0x0026B178`, 796 cm velocity
  lookahead, a current-path cache reset threshold of 1592 cm).
- `0x0026A090` converts remaining distance to local path distance and `0x0026AA80` returns the authored path events in
  an inclusive interval (at most twelve per rider). The per-tick progress update is `0x00112FB0`/`0x00112338`.
  Rider +0x4D0 is the current remaining distance, +0x4D4 the best (smallest) reached, so riding backwards does not move
  the event boundary back. +0x4D8 is the progress origin, copied from +0x4D0 (getter `0x00113128`) at
  `0x0010F500`..`0x0010F50C` inside `0x0010F3B8`. The Snow Jam human starts on path 3 with 353496.15625 cm remaining
  **(PS2)**.
- Snow Jam's authored events (the raw AIP ids map to runtime ids as shown; other ids are not interpreted):

| Path | Local horizontal distance (cm) | Runtime event | Raw AIP event |
|---|---:|---|---|
| 4 | 33742.61 | 11, value 0 (checkpoint) | 18, value 0 |
| 5 | 45287.26 | 11, value 1 (checkpoint) | 18, value 1 |
| 7 | 19361.90 | 1, value 0 (finish) | 0, value 0 |

- The manager allows three checkpoint indices for this event, though only two are authored.
- Checkpoints: the event callback `0x0010E5D8` sends runtime event 11 to `0x00270AB0`, which resolves the human's
  roster index, checks the manager's inhibit fields and the index, and sets the checkpoint bit in rider +0x5FC once;
  a matching bit in the manager's notification byte (manager+0x3B4 → +0x1F) requests downstream processing.
- Finish: runtime event 1 calls `0x00125108` for eligible modes when the rider has not already finished. Rider
  +0x470 is the after-finish timer (negative = unfinished, 0 at the finish, then +1/60 per tick at `0x0012102C`..
  `0x0012104C` inside `0x00120F20`); +0x478 = race ticks + penalty ticks (+0x47C).
- `0x0012A250` is true only when every configured human has a non-negative +0x470 (true for an empty list); computer
  riders are not checked. Once it is true, `0x0011A228` returns at once, so a trick landing after the finish commits no
  points and leaves the combo clock closed **(PS2)**.

## Finish, time limit and Give Up

- Time limit: `0x00125228` (per rider, called from `0x00121818`) ends an unfinished run once race ticks pass
  int(limit/60) × 60 (tick 7201 for 2:00): rider +0x480 = 1 (DNF) and the finish routine `0x00125108` (the Give Up
  path below differs by not playing the time-up sound `0x002A3C00`). It requires rider +0x874, so the slope-style
  opponent is never timed out.
- Give Up (career pause menu only; the Single Event pause menu has Return / Restart / Audio / Options / Quit
  **(PS2)**): the confirm case at `0x0020DA58` inside `cOVTemplate_Dialog_onWidgetEvent` (menu family `0x0020D1D8`)
  sets `0x004A26FC` (gp-0x9F4) = 3 to close the pause menu, sets `0x004A2A50` (gp-0x6A0) from table `0x004428F0`, and
  calls `0x001253D0` (`cRider_quitEvent`) on the human (G+0x84 → +0x0C → +0x40 → +0x18). If the rider is unfinished
  it sets +0x480 = 1 and `0x005366D0[slot]` = 1. On the next tick the second branch of `0x00125228` (`0x00125368`,
  reached whenever the limit has not expired) sees +0x480 with world state 4 and calls `0x00125108` without the
  time-up sound. The run then looks exactly like a timeout, for races too **(PS2)**.
- Banner: the HUD (`0x001EB9E8` inside `0x001EA930`) sets state+0x88 = 2 if +0x480 else 1, and +0x80 = 0xFFEFFFFF
  hides every element except the 0x00100000 banner (`0x0021F660`, descriptor 0x1B at (320,180), 240×41): FINISH!
  (owner+0x4B4, with the run score under it in freestyle) or TIME'S UP (owner+0x49C, no number).
- Finish panel: 3 s into +0x470 the `finishov` panel (constructor `0x0021CF60`, vtable `0x00473D28`) scales and fades
  in with '1st run' / '2nd run' / 'Final run', 'Nth place' (the run ranked against the round's five posted scores with
  `0x00238B70`, clamped to 6th) and '%d pts'. It appears after FINISH only; a TIME'S UP run shows nothing after the 3 s
  banner **(PS2)**. Banner ~3.0 s, panel box ~0.25 s, text ~0.2 s **(PS2)**.
- Results timing **(PS2)**: EndRace (one tick after the finish) requests results, but the results and the replay behind
  them start only when the finish HUD is done: 408 ticks after a FINISH, 288 after TIME'S UP (timeout or Give Up). The
  split follows +0x480, not the stop. Finish control 10 raises +0x470 to 10 when the stop clip ends (`0x0012C964` inside
  `0x0012C678`), and the post-finish state `0x00233CD8` also waits until every human is below 277.78 cm/s (float at
  `0x0049DF7C`, gp-0x5174). In a Give Up run the race ticks stop at the finish tick (= +0x478), +0x470 counts up from 0
  and jumps to 10 at the stop **(PS2)**.

## After the round

- Finish (WS5) → podium (final only, places 1-3, WS12: a header fade {out 30} over the finish view, then the winner's
  podium script; PA_Medals cue 7 at t0; the winner's character tune `0x0028CDF8`) → the rival challenge when due →
  results (WS7).
- Results menu: template `0x0046E488` {1, 5, 6, 7, 8}; item 0 is rewritten by `0x001E5AA0` to "To semi final round" /
  "To Final Round" when advancing, else Transport; then Restart, Replay, Records, Quit. The give-up flag is read by the
  results rows at `0x001E5F6C` inside `0x001E5B80` and by the finish-panel setup at `0x001E8D38` inside `0x001E8920`.
- Next heat (WS13, `0x00235AA0`): world reset, the gondola in-air cutscenes held until the heat is loaded, then WS1
  with [5 idle] under the card; for the final (GMM+0x98, at `0x00235C58`) the list is [4 start hut (two variants), 5].
- Restart (after a confirm): the same gondola ride-up, then the card **(PS2)**; path `0x0020D7DC` inside
  `cOVTemplate_Dialog_onWidgetEvent` → `0x002302A8` (`cGame_restart`) → WS1 arg 2.
- Transport (`0x0020CF80` inside `0x0020CCF8` → WS14 arg 2, `0x00236250`): cutscene list 1 group 11
  (`endevent_trans_arr`) where the course has one (Snow Jam's is empty **(PS2)**), then the map (overlay 0x21).
  Choosing a free-ride row or the same event again restores free ride (`0x002018A8`: event type 4, mode 12, the
  free-ride handler); on the same course that is WS15 with `0x0011DE60(rider, 1, 2)` (session point 1) and a white
  fade of about 58 ticks; another location uses the gondola or helicopter transport. The rider must ride into the gate
  again to start another event.
- Quit asks "Save progress before quitting?" and goes to the front end.
- Post-event DJ commentary is recorded by `0x002A45C0` and played by `0x002A4770` at the next hub chatter.

## Race events (handler 1)

- CTM always runs Qualifier, Semi Final and Final with six riders each; the handler never reads the course. In every
  round 1st-3rd advances, otherwise the same round repeats. In the final 1st/2nd/3rd win gold/silver/bronze; any other
  place completes the event without a medal and the final repeats next time. Single Event forces round 3.
- The round is decided when the player crosses the line. Riders still on course get the estimate `0x00122D78`:

  ```
  estimate = raceTicks + remaining / max((origin - remaining) / raceTicks, 30 - place)   // cm per tick
  ```

  A DNF time is 360000 ticks (the constant at `0x0023A860` inside `0x0023A760`).
- Adaptive difficulty lives in the character profile at +0x280/+0x282 and is updated by `0x00147D20`/`0x00147E18`.
  The level stays in 0..2 and needs two steps to move up or down. A win steps up if time[slot 1] − time[slot 0] ≥
  601 / 301 / 181 ticks in rounds 1 / 2 / 3; it steps down on a qualifier fail, 5th-6th in the semi, or last in the
  final. Computer-rider attribute levels per peak are 1, 4 and 7 (per the progression notes, not detailed).

## Freestyle events (handler 0)

- Init `0x00238E20` sets GMM+0x14 posted riders to 4 for slope style, else 5. The number of live slots is
  GMM+0x10 − GMM+0x14 + 1; the computer riders spawned are GMM+0x10 − GMM+0x14 (race 5, slope style 1, pipe and big air
  0).
- Roster `0x00239938`: GMM+0x18 = the player, +0x1C = the peak rival (`0x00145750`), the other characters shuffled into
  +0x20... In a Single Event the last shuffled character goes into +0x1C, so a Quick Play opponent is random while a
  career opponent is the peak rival.
- Posted scores: at event start `0x00239AA0` → `0x001453D0` posts all three rounds from table `0x00440B38`, whose rows
  are {course, round, 5 × score/100, time limit in s}. Slope style: slot 0 the player, slot 1 the opponent who rides,
  slots 2..5 post columns 0..3 (the 5th column is unused). Pipe and big air: slot 0 the player, slots 1..5 post columns
  0..4 (slot 1 is the peak rival).

  ```
  s = column * 100
  if not the leader: s *= levelScale         // 0.9 at level 0, 1.2 at level 2
  s += trunc(s * (rand() % 200 - 100) * 0.0005)
  s = s rounded down to a multiple of 20
  ```

  `rand` is the game's shared random stream (the same one gameplay draws from). The formula reproduces the posted
  scores of the R&B and Crow's Nest savestates at level 1 **(PS2)**.
- Heat 1 ranks the player's heat-1 score against every posted rider's heat 1 + heat 2 total; top 3 go straight to the
  final, otherwise heat 2 follows. Heat 2 ranks combined totals; top 3 go to the final, otherwise back to heat 1. The
  final is a solo run against the posted final scores; 1st-3rd win a medal, otherwise the final repeats. A Single Event
  runs the final only, and its posted final scores are the round-1 values.
- Results `0x00239230` (per rider at its finish) stores scores[round][slot] = score object +0x198, or 0 on DNF. The round
  is decided when every human has finished (`0x0012A250`). In heats an opponent still riding keeps 0 (or an older heat's
  value, since a heat-1 retry clears only slot 0). In the final it gets the points estimate `0x00122E50`:

  ```
  s1  = score + 1
  est = s1 + int(max(rem - 1000, 0) * s1 / max(orig - rem, 1))   // rem = +0x4D0, orig = route origin
  ```

  (One note writes the product as max(rem − 1000, 0) × (s1 / max(orig − rem, 1)) with orig = +0x4D8; the other takes
  orig from `0x00113130`. The evaluation order is not settled between them.) If the opponent crosses the line after
  the player but before the race stops, `0x00239230` runs again for slot 1.
- Time limit: GMM+0x78 = `0x001454F8(course, round)` × 60 when +0x88 is set. On a timeout the heat score is stored as 0.
- Difficulty: profile +0x284/+0x286; up on a heat-2 win or a final medal, down on a final fail.

### HUD flags

`0x001EA930` sets owner+0x3CC from table `0x00478078` indexed by the mode byte:

| Bit | Element |
|---|---|
| 0x1 | race place |
| 0x2 | score (inferred from the pipe/big-air set) |
| 0x4 | clock |
| 0x10 | standings rows |
| 0x40 | progress meter (`0x0020EDA0`) |
| 0x00100000 | FINISH! / TIME'S UP banner |
| 0x08000000 | OPPONENT line |

Values: race and rival modes 0x1530C047, slope style 0x1530C056, pipe and big air 0x1530C016. During an R&B slope-style
run owner+0x3CC reads 0x1D31C047 (place, clock, score, progress, OPPONENT; no standings); the rival notes say
`0x001EA930` adds the OPPONENT bit for event type 6 only. How the slope-style value is derived is not explained.

- Standings: three rows over the posted scores, best first, with the player's row (name, score +0x198 plus the heat-2
  carry) inserted where it is at least the posted score (type-7 case at `0x001ECFFC` inside `cOVStateHUD1P_onRender2D`,
  descriptor 0x17 at (20,20), rows from `0x001EB160` inside `0x001EA930`).
- Clock (drawn by `0x001EC3F8`, descriptor 0x1A) counts down int(limit/60) × 60 − race ticks, shown as hours, minutes
  and seconds of ceil(ticks/60), and turns red (colour at `0x004C8688`) for half of each second under 10 s
  (owner+0x3D0). The "Time Left" label belongs to the split-screen HUD only.

### Slope style (mode 1)

- R&B (ASS1, course index 5) has a 1:30 limit plus 60 s per checkpoint; the checkpoint list at `0x004D33B8` holds
  {60, 176456.97} and {60, 75402.55} (read as {bonus seconds, remaining distance in cm}; field names inferred). When the human's best remaining distance passes
  one (mode 1 only, human only), `0x00112FB0` → `0x0010E558` → `0x001194C0` posts HUD popup 0x29 with the value for
  2.5 s through `0x00117B88` and the speech AE_ARCADE_BONUS (29). The handler's accept method `0x002398E8` adds
  value × 60 ticks to GMM+0x78, only while the new limit is at least the race ticks. Checkpoint 1 in a PS2 run showed
  the '+60' popup and the extra minute **(PS2)**.
- Place: `0x0010F998` rank mode 2 keys each rider on score +0x198 (0xFFFF0001 when rider +0x878 is set); the place
  HUD `0x0021E1B0` shows "1ST/2".
- OPPONENT line: type-7 case `0x001ED5C8`..`0x001ED78C` inside `cOVStateHUD1P_onRender2D`. The label is the ASCII
  literal at `0x0046EB60` at (20,65), the value at (20,78), both at scale 0.7. N = opponent score − player score,
  printed "+%d" when N ≥ 0; red (`0x004C88C8`) when N > 0, pale yellow (`0x004C88A8`) when −5000 ≤ N ≤ 0, green
  (`0x004C8888`) below −5000.
- The opponent runs the normal computer-rider pipeline; its score object accumulates like the human's (`0x00117C28`,
  `0x0011A228`, `0x001193E0`), with no checkpoint bonus or time extension. The PS2 results rank it by the score of its
  own run among the four posted riders **(PS2)**.
- Stage-program pickups: point icons (builtin 27 type 6 → `0x0010E8B8` → `0x00119608`; 2000/3000/5000/10000) and
  multiplier icons (builtin 27 type 3, x2/x3/x5/x10 → `0x0010F1C0` → rider vt+0x78 `0x0010E830`). In the air or on a
  rail only (`0x0011FE98` returns 1 or 4) the multiplier calls `0x00119448`: increment +0x130; if the bank exists and
  +0x18 < value, set HUD slot 4 = `0x001171A8(4, int(value), 0, 0)` and +0x18 = value; then `0x0010E098(rider, 4, 0)`
  and the pickup sound `0x0029CED8(audio, 2, rider, value)`.
- Course data: the ASS1 train-box instances' slot-2 handlers only break a MeshAnim (builtin 13 run by the stage VM);
  28 ASS1 splines carry runtime rail flags 0x10001 (rail only).

### Big air (mode 3)

Nothing separates big air from the pipe except the table row (Crow's Nest ABA1, course index 8: 60 s), GMM+0x94 (no
reader), the reset clearance (`0x0012F468` inside `0x0012F398` selects 1000 cm only for mode 2; modes 1 and 3 keep
200 cm) and the pause-menu case. There is no jump counting or best-jump rule: a run is scored like the pipe. The ABA1
car instances are inert at the countdown (runtime flags lack 0x60 and every route is skip).

## Rival challenges and backcountry (handlers 5 and 6)

- Happiness is course row 14 (code ABC1, world BAM, career peak 0, station flag 0, map region 15); rows 15/16 are
  Ruthless (DBC2) and The Throne (EBC3). The location table `0x0043E250` marks ABC1 as an event course (kind 0). Single
  Event lists it twice, in the race list (mode 4) and as "Happiness Jam" in the freestyle list (mode 5) **(PS2)**.
  A free-ride entry into ABC1 is event type 4 with no rival; the rival challenge always loads its own event world.
- Peak rival `0x00145750` (by the course's career peak via `0x00144C78`): peak 0 Mac (3), or Griff (5) if the player is
  Mac; peak 1 Nate (7) / Zoe (4); peak 2 Psymon (8) / Elise (6). Indices follow `CHARDB.DBL` (0 Moby ... 9 Viggo).
- Rival Time init `0x0023B6C0`: +0 = 1, +0x10 = 1 (two riders in all), +0x14 = 0, +0x68 = +0x6C = −1, +0x70 = +0x74
  = 1, +0x78..+0x94 = 0 (no limit), +0x98 = 1, +0x9C = 0. The lineup arrays are memset to −1; the player's slot
  (`0x00146E98(profile, 0)`) gets its character (`0x00147398`), the next slot the peak rival with +0x40 = 0.
- Rival Time results `0x0023B8C8(slot)`: if +0x480 is set, time = 360000 and `0x005366A8[slot]` = 1; else time =
  +0x478 and the flag 0. When the human finishes (tested as a vtable +0x40 call returning 1) every unfinished rider
  gets the race estimate `0x00122D78`, `0x00238BF8(GMM, 10)` ranks by time and +0x9C = 1.
- Win = place 0 (`0x00536730[player slot]` == 0) and not given up: rider +0x100 = 1 (celebrate), GMM+0x84 = 1,
  +0x74 = +0x70, +0x70 = 0. Otherwise +0x100 = 0 and the round stays. There is no semi or final; the challenge must be
  won, and pays gold for a win only.
- Rival Points init `0x0023BB98`: as Rival Time plus the freestyle limit (+0x78 = `0x001454F8(profile, 1)` × 60, +0x88
  = 1). The table row for course 14 round 1 has all posted scores 0 and a 300 s limit (the DBC2/EBC3 rows 28/29 also
  300 s). Results `0x0023BDB8`: score = 0 and gave-up = 1 if +0x480, else the score object (rider+0x790)+0x198; when all
  humans are done unfinished riders get `0x00122E50` and `0x00238B70(GMM, 2)` ranks by score. The rival rides and
  scores its own tricks; there are no posted scores.
- Both use the rolling start. The rival runs the normal computer-rider provider `0x0010A768`; the jam rival's score
  state marks it as planning tricks.
- HUD: table entries [4] and [5] = 0x1530C047. Rival Time is the race HUD with the clock counting up; Rival Points uses
  the slope-style layout (place by score, clock counting down from 5:00, OPPONENT line, progress) **(PS2)**.
- Audio: `0x002872A8` (event start without countdown, event types 5/6) starts song event 0 or a new playlist song at
  the GO tick; in rival modes outside multiplayer it queues the rider speech BC_Challenge (0x5788: rival slot 1
  speaks to the human, `0x002A1138`), otherwise the DJ Radio BIG intro; then the artist intro (0x5778 = 1). Finish
  `0x00286EA0` → `0x002A4078`: event type 5 plays PA_Finish_Line, type 6 in round 1 PA_Rider_Position. Music category
  (`0x0028D8A0`) is 4 BackCountry for courses 14..16; ABC1's mix painter selects mix 1 (effects and speech 70%).
- Locator beam over the rival (RFX+0xB00, update `0x002E39D8`, draw `0x002E3AF8`): an 8-vertex additive strip along
  the camera up from the rival's bone 5 (alpha 0 at the base, full colour at +130 and +20130 cm, alpha 0 at +20260 cm),
  half-width 85 cm along the camera right, texture `beam`, colour (a 0.5, r 1, g 0, b 0) from the component's initial
  +0x28 (the pulse update runs for the human only). Only in rival modes on courses 14..16, single player.
- Relationship icon '!' (RFX+0xAF0, update `0x002D4C08` per tick, draw `0x002D5048`; all computer-rider races): level
  = the rider's relationship record about the human (`0x00155B50`; 3 for the peak rival); colour ≥4 red, 3 orange, 2
  yellow, else white; visibility ramps ±0.1 (level ≥ 2) or ±1/15; pulse tables at `0x00488EA0`, `0x00488F48`,
  `0x00488FF0`, `0x00489070`, `0x004890F0`, `0x00489150` (41-tick pop on a level change, 31-tick loop at level ≥ 4,
  24-tick pop on a rise); quad 35 cm above bone 5, 18 × (sx + 0.003 z) wide and 18 × (sy + 0.003 z) tall, visible
  for 0 < z < 20 m and fading past 15 m, texture `exlm`, alpha blended.
- Finish: Rival Time shows the race FINISH banner; Rival Points the freestyle FINISH! with the score, then the finish
  panel with only "Nth place  N pts" (no run label), placed against the rival. Results read "<course> - Race|Jam /
  Single Event Results" and "Sorry, you didn't win." on a loss **(PS2)**.

Peak challenges (modes 6-11, handlers 4 and 7) are solo runs against table `0x00440D18`.

## Career data (BE interfaces)

### Courses, peaks and goal lists

Course table `0x0043D950`, stride 0x64:

| Offset | Field |
|---|---|
| +0x00 | index |
| +0x04 | name |
| +0x24 | short name |
| +0x34 | code |
| +0x44 | world |
| +0x54 | career peak (0-based), read by every progression function through `0x00144C78` |
| +0x58 | station flag |
| +0x60 | map region |

| Peak | Races | Freestyle | Rival | Peak event |
|---|---|---|---|---|
| 1 | ARA1, BRA2 | ASS1 (slope), ABA1 (big air), BHP1 (pipe) | ABC1 | Peak 1 Race / Jam |
| 2 | CRA3, DRA4 | DSS2, CBA2, CHP2 | DBC2 | Peak 2 Race / Jam |
| 3 | ERA5 | ESS3, EBA3, EHP3 | EBC3 | All Peak Race / Jam |

The per-peak goal lists at `0x0045AAD8` are ordered as the Transport screen lists them: races, then the rival race,
then the peak race; freestyle as slope style, big air, pipe, rival jam, peak jam.

### Medals, platinum, cash (`0x00154EE8`)

- Medal encoding (`0x00155328`): 0 platinum, 1 gold, 2 silver, 3 bronze, −1 none. Medals are placement-based; the
  "Gold medal at %d" strings belong to the free-ride goal screen.
- Platinum (`0x001456A0`, table `0x00440E80`, career only) upgrades any earned medal: races need time ≤ T × 60 ticks
  (150-165 s per course), freestyle score ≥ T × 100. Peak events have no platinum.
- Cash: standard and rival events from `0x004405A0` [course][plat/gold/silver/bronze] × 100; peak events from the
  `0x00440D18` row's cash × 100, gold and platinum both paying the gold value. The full amount is paid only if the medal
  improves the stored best, otherwise half; no medal pays nothing. Cash goes to profile +0xAC4 and lifetime earnings
  +0xAC8.

### Goals, locks and peak passes

- Goals (`0x00157BF0`): RACE / FREESTYLE = a medal on every entry of the goal list; EXPLORE = collectible and Big
  Challenge medals (tables `0x0045AFE8`/`0x0045B018`); EARNINGS = lifetime earnings of $100,000 / $250,000 /
  $1,000,000 (`0x0045B048`). Completing any goal of peak N clears the peak N+1 pass bit (profile +0x278 bits 12/13).
- Event locks in +0x278: the rival challenge opens when every standard event of the list has a medal (bits 6+peak /
  9+peak); the peak event opens when the rival also has one (bits 14+peak / 17+peak). The help texts read "LOCKED.
  Complete all race events on this peak." and "LOCKED. Complete Happiness to unlock." **(PS2)**.

### Records

Defaults at `0x0043FB28`: 26 slots × 5 entries of {value, character, name}; the value is whole seconds for times and
points for scores. The slot comes from `0x0014AB68` (`cBELibrary_getScoreType`) through table `0x0045A2F8` (Snow Jam
is slot 12, whose top default time 02:57 is what the PS2 shows **(PS2)**).

### Profile fields

| Offset | Meaning |
|---|---|
| +0x278 | peak pass and event lock bits (above) |
| +0x280/+0x282 | race difficulty |
| +0x284/+0x286 | freestyle difficulty |
| +0xAC4 | cash |
| +0xAC8 | lifetime earnings |
| +0xBB8 | stat-medal tiers (not described further) |
| +0xF28 | one-shot award bits |
| +0xF30..+0xF57 | reward ownership bits |

### Attributes

Buy Attributes (`0x00150C20`): each point costs `0x00440550`[raw/5 − 1] ($250 up to $5,000); raw values run 5..55
(shown 1.0..11.0). The rider ranking is (Σraw − Σraw % 5) / 35 (`0x00181BD0`). The menu rows map to attribute indices
through `0x004780B0`. Each stat getter computes

```
stat_k = int(raw_k / 5) / max_k      // single-precision divide
raw_k  = byte at 0x00535538 + bank*70 + char*7 + k
max_k  = byte at 0x005308D8 + char*15 + 8 + k    // 11 for every rider on the disc
```

Level 1 gives 1/11 (0x3DBA2E8C) **(PS2)**.

| k | Attribute | Getter | Consumers |
|---|---|---|---|
| 0 | top speed | `0x001494C0` | speed limit `0x0011B3F8`, `0x0013CCF0` |
| 1 | acceleration | `0x001493D8` | `0x0013C948`, `0x0013CCF0` |
| 2 | tricks | `0x00149690` | grab rate `0x00120038` (`0x0010E098` calls it without using the value) |
| 3 | edging | `0x00148D80` / `0x00148E68` | `0x0013CCF0`, `0x0013D028`, `0x0013D818` |
| 4 | spin | `0x001495A8` | air control `0x00133128` / `0x00133308` |
| 5 | toughness | `0x00148F50` (`cBEStatInterface_getCollisionAttrib`) / `0x00149038` | collision weight `0x0011FF98` (`cRider_getMass`), `0x00107888` |
| 6 | stability | `0x00149120` / `0x00149208` | landing `0x00139C88`, rails `0x0013AF28` |

### Rewards, awards, gear, uber tricks, songs

- Rewards catalog `DATA/BE/RWRDPS2.DAT`, parsed by `0x0015A818`: 100 art, 43 posters, 28 toys, 116 trading cards, 20
  cheat characters, 2 videos. Each item has a price and is sold only in its own peak's lodge (elsewhere the help reads
  "Buy this item in Peak N lodge."). Pictures are in `DATA/CHAR/RWRDPS2.BIG` (SHPS images; flag 0x2000 marks a PSMT8
  swizzle). Trophies show 12 pictures, one per completed peak goal.
- Awards (`0x00159CD0`, one-shot bits at +0xF28 except 17-19):

| Award | Trigger | Grant |
|---|---|---|
| 0-4 | conquer / all goals / all goals of Peak 1, 2, 3 | a cheat character each |
| 5-16 | a peak goal (id = 5 + goal × 3 + peak) | Peak 1: 4 random cards + 1 poster; Peak 2: 1 toy + 2 art; Peak 3: a cheat character |
| 17-19 | first gold or platinum in a standard event of that peak (`0x001591E8`); repeatable | a random unowned gear item from the rider's peak pool (flag 0x100 << peak) |
| 20-31 | first gold or platinum in a rival race, rival jam, peak race or peak jam | a random unowned item from the rider's special board pool (flag 0x800) |

  Random picks (`0x00157080`) take any unowned item in the category regardless of price or peak. Owning a whole
  category (cards, toys, posters, art) unlocks a cheat character.
- Gear `DATA/CHAR/BOLTPS2.DAT` (4829 entries): per rider items, menu tree, prices (× 10), lodge tier (Peak 1/2/3 lodge,
  or reward pools 11-13 / 14), 7327 equip rules and default outfits. Inventory init `0x001513B8`, equip `0x00151C90`
  with rules `0x00151EF0`, buy (including bundled items) `0x0014B560`, Buy Gear list `0x0019B180`/`0x0019B098`. The
  starting owned/equipped flags of all ten riders match a fresh-career savestate, and Zoe's Peak 1 Buy Gear menus
  match the PS2 screens **(PS2)**.
- Uber tricks (table `0x0045AEB8`, lists read by `0x0014FF90`): setup rows Mute (category 1), Indy (3), Stalefish (2),
  Method (0), Nose Grab (4), Tail Grab (9); prices $10,000 / $15,000 / $30,000; per-rider starting state from
  `0x00150558` (matches savestate bytes **(PS2)**). Buying (`0x00184F40` → `0x0014FE08`) clears the lock bit; selecting
  writes the entry (`0x0014FD80`).
- Songs: the `MUSIC.INF` entries with `ADDTOFE=1` (35); the first 6 are bought with free credits, then $5,000 each
  (`0x00158558` / `0x001988D8`).
- `DATA/BE/{STATDB,GLOBAL,MODECHAL,BEHILOC}.DBL` are not referenced by name in the executable; their use is unresolved.

### Career menus (PS2)

- MCOMM: Return / Transport / Session / Messages / Audio / Options / Quit. Transport → Select Peak → Select Peak Goal →
  Select Race / Freestyle / Freeride Event; locked peaks show a lock; Square toggles MAP/INFO (goal progress, and per
  event Run / Event / Medal / Top time).
- Riding into a Green/Blue Station asks to enter the lodge: Return to Game / Equip Gear / Buy Gear / Buy Attributes /
  Rider Details / Music / Save Game / Quit. Square toggles Buy Gear and Equip Gear.
- Career pause in an event: Return / Restart (confirm) / Messages / Audio / Options / Give Up (confirm).
- The round card shows the round's objective, the Riders or Current-standings lineup and the course record. Results
  show "<Course> - <Event>", "Qualifier / Semi Final / Final Results" or "Qualifier Heat N Standings", the ranked rows
  and a message (a qualifier fail reads that a 3rd place or better is needed); a completed event first shows the medal
  card with the medal, the cash and any peak pass.
