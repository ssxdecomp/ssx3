<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/sound/

## `src/sound/ssxAudio.cpp`

Segment `0x00284BB0`-`0x0028A1E8`.

- **`0x00284BB0`** `SSXAUDIO_Init` - Allocates the SSXAudioSystem (0x7780 bytes), calls its constructor `0x00284C68` and stores the result at *(gp+0x410) (`0x004A3500`). *[static]*
- **`0x00284C68`** - SSXAudioSystem constructor: sets the speech manager vtable at audio+0x5560 to `0x004836D8` and sets mixer channel 0 (master) once to 10/11. *[static]*
  - `0x00285094`: Sets mixer channel 0 (master) to 10/11 using the float at gp-0x4660 (`0x0049EA90`). *[static]*
- **`0x002854F8`** - Speech callback that starts a speech stream (speech vtable `0x004836D8` slot +0x08). *[static]*
- **`0x00285930`** - Sets the audio listener from the camera view matrix: listener 1 m ahead and 25 cm off. *[static]*
- **`0x00285BF8`** - Per-frame audio system update, run before the frame's game tick: runs the mix fade `0x002887F8`; waits for `0x002AB028` to report the DJ stream playing, then releases the duck (`0x00287F00`(3, 0.5, 1.0)) when it stops; auto-resumes after pause; runs the per-frame dispatchers `0x0029AB40`, `0x0029B738` and `0x0028C8C8`; polls `0x00390EF8` and plays thunder (bank 8, sound 16). *[PS2]*
  - `0x00285D40`: Probably the per-frame call of the Super Uber speech dispatcher `0x0029B738`. *[unconfirmed]*
- **`0x00285D98`** - Returns a listener/primary rider for the audio system ((audio, -1) = primary player); also used as the local-human check for speech and as a current-rider lookup. *[static]*
- **`0x00285FB0`** - Front-end audio init: loads the [FE] banks (bank slot 0 = SSX3Menu.bnk) with the FE scale table, releases ducks, plays charsel (id 301, no event) and sets FE music state audio+0x6290 = 10 (none). Called from `0x0018BEF8`, `0x001A1CE8`, `0x001D64C0`. *[static]*
- **`0x00286200`** - FE -> game audio transition: stops (radio mode 2) or FadeOut(1.0 s), then unloads the FE banks. *[static]*
- **`0x002862A8`** `cSSXAudio_FrontEndLoad` - World bank loader: loads the WORLD bank slots and the world channel scale table (`0x00288D18` with a1 = 1). *[static]*
  - Possible mismatch with the current name: The name says front-end load, but records describe it as the world bank loader (the front-end bank load is `0x00285FB0`).
- **`0x002867E8`** - World-load audio, called from `0x0022F6B0`: takes radio mode and custom list from the profile, PickNextSong + PlayMusic (event 0 CTM, 36 single event/MP) unless pktrans plays, posts DJ / Radio_Big_Intro / Free_Ride_Intro lines, creates painter queries, resets triggers, releases ducks and sets first-visit flags audio+0x579C[23]. Not called at the CTM gate. *[static]*
- **`0x00286A80`** - World audio teardown when leaving the world: resume if paused, hard Stop of the song (no fade), stop loops, destroy painters, SetMix(0), cancel timers, stop speech. *[static]*
- **`0x00286CA8`** - Loads the per-location sound banks (SSB kind 20) into slots 8/9. *[PS2]*
- **`0x00286E20`** - Event world audio init / world start: PA venue intro (single event/MP) and starts the board loops (via `0x002929D8`). *[static]*
- **`0x00286EA0`** - Player finish audio, called from the finish routine `0x00125108`: Cheer30 crowd, stop rider loops, event 36 (Big Air/Pipe runs left) or 10, results DJ/PA lines (PA_Rider_Postition for career round < 3 non-race, PA_Finish_Line for race courses or the final round); calls `0x002A4078`. *[static]*
- **`0x002871B0`** - Starts race audio when the round card closes; also releases the duck (`0x00287F00`(3, 0.5, 1.0)). *[PS2]*
- **`0x002872A8`** - Event start audio without countdown (kinds 5/6, e.g. the backcountry rival rolling start): song event 0, GO tick, then in rival modes outside multiplayer queues rider speech BC_Challenge (audio+0x5788; rival slot 1 speaks to the human via `0x002A1138`), otherwise the DJ Radio BIG intro; then sets audio+0x5778 = 1 (artist intro pending). *[static]*
- **`0x002873D8`** - Converts a volume menu step 0..11 to linear volume: clamp(step * 1/11, 0, 1). *[static]*
- **`0x00287410`** - Music/MC volume slider setter (options word `0x00535610` bits 0..3); the music slider also drives AMBIENT (ch8) and DJ (ch2, when enabled). *[static]*
- **`0x00287488`** - SFX volume slider setter (options word `0x00535610` bits 8..11); drives PA, ch5, BOARD, COLLISION and the arcade channels. *[static]*
- **`0x00287520`** - Character speech volume slider setter (CHARACTER bus, ch4). *[static]*
- **`0x00287558`** - DJ Speech option setter (options word `0x00535610` bit 17): DJ bus = Music volume only while DJ is enabled (audio+0x62B8) and radio mode != 2, else 0. *[static]*
- **`0x002875D0`** - Arcade SFX option setter; gates ARCADESFX/ARCADESPEECH via flag audio+0x62B4. *[static]*
- **`0x00287670`** - Volume slider getter returning round(vol * 11); one of the three music/SFX/speech getters (`0x00287670`, `0x002876A0`, `0x002876D0`), not individually assigned. *[unconfirmed]*
- **`0x002876A0`** - Volume slider getter returning round(vol * 11); one of the three music/SFX/speech getters (`0x00287670`, `0x002876A0`, `0x002876D0`), not individually assigned. *[unconfirmed]*
- **`0x002876D0`** - Volume slider getter returning round(vol * 11); one of the three music/SFX/speech getters (`0x00287670`, `0x002876A0`, `0x002876D0`), not individually assigned. *[unconfirmed]*
- **`0x00287700`** - Applies mixer channel volumes: effective = slider * base scale * duck * mix; channel 0 goes to `0x003B8160`(vol*127). *[static]*
- **`0x00287968`** - Returns a pointer to a bus's effective volume (audio, bus[, player/speaker]), used as the voice gain pointer and by the 'bus volume != 0' speech gates. For bus 4 (CHARACTER) with a CHARDB id it returns the per-speaker gain audio+0x636C+4*id; NIS sounds call it as (audio, 4, 0). *[static]*
- **`0x00287A10`** - Converts a duck channel mask to channels, one bit per bus: 0x1 MUSIC, 0x2 ch5, 0x4 CHARACTER, 0x8 DJ, 0x10 AMBIENT, 0x20 BOARD, 0x40 COLLISION, 0x80 PA, 0x100 ARCADESFX, 0x200 ARCADESPEECH. Each block is governed by the andi in the previous branch's delay slot. *[static]*
- **`0x00287C48`** - Per-frame duck tick. *[static]*
- **`0x00287F00`** - Duck fade (audio, mode, seconds, level): fades a group of channels through the per-channel duck factor. Mode 0 = mask 0x173 (MUSIC, ch5, AMBIENT, BOARD, COLLISION, ARCADESFX); mode 3 = release whatever is ducked. DJ talk-over uses (0, 0.9999 s, 0.65); release uses (3, 0.5 s, 1.0). *[static]*
- **`0x00287FC8`** - MIX.INF parser: reads up to 25 [Mix n] records of 0x28 bytes into audio+0x647C (path pointer at gp+0x470 (`0x004A3560`), 'data/config/mix.inf'). Defaults 100 and TIME 0; columns MUSIC, DJ, PA, CHARACTER, BOARD, COLLISION, AMBIENT, ARCADESFX, ARCADESPEECH map to channels 1,2,3,4,6,7,8,9,10; TIME is stored in seconds (ms * 0.001). *[static]*
- **`0x002883B0`** - SetMix(audio, idx): selects a MIX.INF preset, immediately (TIME 0) or as a linear fade; idx < 0 -> 0, ignored if equal to the current audio+0x646C, level -1 keeps the channel. Only callers: the Mix painter `0x00289C98` and world teardown `0x00286A80` (SetMix(0)). *[static]*
- **`0x002887A8`** - Starts a mix fade: per-channel target audio+0x6440[ch], step audio+0x6414[ch] = (target - current)/TIME * 1/60. *[static]*
- **`0x002887F8`** - Per-frame mix fade: adds the step and clamps (linear amplitude, 60 Hz steps); called every frame from `0x00285BF8`. *[static]*
- **`0x00288AE0`** - Audio/feedback suppression check: true while instant-replay playback runs (*(G+0x84+0x28) state 1..9, where session+0x28 is the Replay object from `0x0026EFB8`; 0 = recording in a live race). Results screens report 1 because the run replays behind them; not demo or splitscreen. Blocks PlayMusic (unless audio+0x6294), countdown beeps, the big-air duck and every speech category; also used by `0x002A3B18`. *[PS2]*
- **`0x00288B40`** - Listener range check (within 100 units), used by speech and SFX gates. *[static]*
- **`0x00288D18`** - Per-channel base gain scale lookup (gp+0x414 (`0x004A3504`) + channel slot), applied by `0x00287700`. FE table (a1=0, from `0x00285FB0`): all 1.0 except CHARACTER 0.6. World table (a1=1, from `0x002862A8`): MUSIC 1.0, DJ 0.55, PA 0.43, CHARACTER 0.8 (times per-speaker 0.8..1.0), ch5 0.8, BOARD 0.75, COLLISION 0.8, AMBIENT 0.5, ARCADESFX 0.75, ARCADESPEECH 0.75. *[PS2]*
- **`0x00289470`** - Caches the PLAYLIST.INF section names at audio+0x60A4. *[static]*
- **`0x00289520`** - LoadPlaylist(section): reads PLAYLIST.INF [SSX Mix] and adds each SONG by name (`0x002B3EE8`); the resulting mask is saved as the Radio BIG playlist audio+0x518 (all 35 songs). *[static]*
- **`0x00289688`** - MUSIC duck gate driven by a per-line byte envelope at audio+0x6868 (every 2 frames while audio+0x6C58): would duck MUSIC (mask 1) to 0.0 when the envelope >= 30 and the speech bus `0x0029F088` is 2. No code writes 0x6868/0x6C50 or sets 0x6C58, so it is dead in retail. *[static]*
- **`0x002898A8`** - Audio painter query at a rider's position; called per rider from `0x00121950`. *[static]*
- **`0x002899E8`** - Ambience mode check: returns radio mode == 2. *[static]*
- **`0x002899F8`** - Radio mode 2 ambience playback path (Peak1/2/3Amb on the AMBIENT bus); listed together with `0x0028CF98` and `0x0028D5A0`. *[static]*
- **`0x00289B18`** - Animation event sounds, called from `0x00104CC8`: animation event ids 0x8050/0x8051/0x8052 play bank 0 sounds 0x51/0x50/0x52 on bus 5. *[static]*
- **`0x00289B70`** - Game pause audio: pauses SFX voices (`0x0029CE28`) and music (pitch 0); no mix/fade/filter change. Called from `0x001F8168`, `0x002306A8`, `0x00244880`. *[static]*
- **`0x00289BB8`** - Game resume audio: music Resume, SFX resume, cancels queued speech. *[static]*
- **`0x00289C18`** - Returns the tier selecting the music intensity ramp length N (800/1000/1200 frames). *[static]*
- **`0x00289C98`** - Selects the mix (SetMix `0x002883B0`) from the tWPIGD_Mix world painter (type 1) at the primary rider's position. In retail only ABC1 (Happiness) uses Mix 1 and BRA2 (Metro-City) Mix 2, both with 3000 ms fades. *[static]*
- **`0x00289DC0`** - Sound Mode option setter (options word bits 12..13: Stereo/Surround/Mono/DTS). *[static]*

## `src/sound/asyncsys.cpp`

Segment `0x0028A1E8`-`0x0028B588`.

- **`0x0028B180`** - SSXAudioSystem singleton accessor: returns the audio system pointer; every game-side audio call does `jal 0x0028B180` and then a method call. Because of this, contact effects, pickup feedback (`0x0029CED8`, `0x002A3B18`), HUD show/hide sounds (`0x0029B0E0`/`0x0029B3C0`) and the trick identity-change observer path from `0x00132620` appear to route through it. It is not itself an effect dispatcher or trick-naming routine. *[static]*
- **`0x0028B1B0`** - Returns whether the game is in a session (G+0x84 != 0). *[static]*
- **`0x0028B1C8`** - Returns the game session G+0x84. *[static]*
- **`0x0028B1D8`** - Returns the race object (G+0x84 -> +0xC), with riders at race+0x28[i]; e.g. PA_Rider_Intro uses the subject mask of the first human at the result +0x28. *[static]*

## `src/sound/bankmanager.cpp`

Segment `0x0028B588`-`0x0028FD00`.

- **`0x0028BF78`** - SetRadioMode: stores the mode, copies the DJ bit (options word bit 17) and restarts music when needed in a world: 2 -> PlayMusic (ambience) unless playing; 0 -> PickNextSong + PlayMusic when leaving ambience; 1/3 -> the same when the song is not in the custom list or is charsel (hub songs stay). Uses `0x002B4AF0`. *[static]*
- **`0x0028C2D0`** - Sets the custom playlist (audio+0x6098) from the profile mask; called from the Request Line screen exit and world init `0x002867E8`. *[static]*
- **`0x0028C430`** - Part of the game-side loop slice scheduler; dead code. *[static]*
- **`0x0028C8C8`** - Big-air DUCKTOLOOPS update, run every frame in a race/world before the game tick: music duck, loop overlay events 7/8 and the air whoosh, using the airtime predictor *(rider+0x788). T > 2 s: ducks the path volume toward floor = clamp((1 - T*0.8425197*0.5)*127, 20, 127) and starts whoosh `0x002910E0`; loops need T > 3.9995 s, DUCKTOLOOPS == 1, not Big Air/Half Pipe, no MusicTrigger zone. Landing: stop whoosh, event 8, path volume 127. Loops never engage on Snow Jam, Metro-City or Junction. *[PS2]*
- **`0x0028CD48`** - Plays pktrans (peak transition music, id 401) with a destination event: 1 for the plane intro, 2 for Peak 2, else 3. *[PS2]*
- **`0x0028CDF8`** - Podium music, called from `0x00236EE8`: in the final round (GMM state 3) with place < 3, plays chartune with the winner's character event (winner slot = `0x00536708`[0]; event from table `0x00482A10` by the CHARDB base character at G+0xC0+0x18+4*slot); saves the playlist index in audio+0x62AC. *[PS2]*
- **`0x0028CF98`** - PlayMusic / music event dispatcher: picks ambience, hub song or playlist song and starts it with an event. Radio mode 2 -> Peak<n>Amb (ids 101-103 on AMBIENT, sets audio+0x6280); course >= 17 in CTM outside challenges, not forced -> hub song Peak1/2/3 (event 12, intensity 127; e.g. the Peak1 station song in free ride); else the current playlist index (event, or 36 with t0 at a station). Blocked by `0x00288AE0` unless audio+0x6294. *[static]*
- **`0x0028D488`** - PickNextSong, the only song chooser (called e.g. by music codes 21-25): index = rand15 * FEcount / 0x7FFF, then (rand15*10/0x7FFF)+1 NextSong(1, CurrentCategory()) steps; if equal to the previous song (audio+0x62A4) it steps once with category, then once without. Not a shuffle. *[static]*
- **`0x0028D5A0`** - Radio mode 2 ambience playback path (Peak1/2/3Amb on the AMBIENT bus); listed together with `0x0028CF98` and `0x002899F8`. *[static]*
- **`0x0028D630`** - MusicTrigger zone handler (A=1/2): sends event B on enter. *[static]*
- **`0x0028D7D8`** - MusicTrigger zone handler (A=1/2): sends event B+1 on leave. *[static]*
- **`0x0028D898`** - Returns whether no MusicTrigger zone is active (audio+0x623C == 0). *[static]*
- **`0x0028D8A0`** - CurrentCategory(): music category from course index and game mode. Modes 6-8 -> 0 Race; 9-11 -> 1 SlopeStyle; otherwise course 0-4 -> 0, 5-7 -> 1, 8-10 -> 2 BigAir, 11-13 -> 3 HalfPipe, else (backcountry 14-16, stations 17-21) -> 4 BackCountry. *[static]*
- **`0x0028D960`** - Music mode check: returns radio mode != 2. *[static]*
- **`0x0028D988`** - MusicTrigger painter state machine (A=0 course sections; B values 9/11/13/14-17/18/42). B=11 connectors into a hub: latch -> event 11, request kind 0 after 2000 ms, DJ kind 0/1 at 1500 ms; 13 hubs: event 13 + hub chatter; 14-17 DJ event-intro gates; 18 ChangeSong (free ride only; in a challenge it jumps into the B=18 code with latch 11). Ambience mode: 31/32 play Peak1Amb/Peak2Amb, 33 nothing. *[PS2]*
- **`0x0028DF18`** - ChangeSong (painter B = 18, radio): FadeOut(2 s) without DJ, event 18, PickNextSong, forced request kind 1 at 2000 ms, DJ intro (kind 3) at 1500 ms; retries in 100 ms if a DJ line is busy (`0x002A10C0`(10)). *[static]*
- **`0x0028E068`** - Retry song change timer callback. *[static]*
- **`0x0028E088`** - Music request timer callback: latches request audio+0x6274 = 1 and kind audio+0x6278. Accepts when there is no song, when `0x002B2550` reports the song finished (-1), or when force (arg2) = 1; otherwise returns 0 and the queue retries. Kinds are executed by `0x0028E100`. *[static]*
- **`0x0028E100`** - Per-frame executor of the pending music request (kinds 0-4): 0 hub song; 1 PlayMusic(0); 2 backcountry (course 14-16) PickNextSong + PlayMusic(36, a2=1), else hub song; 3 PlayMusic(36); 4 PlayMusic(0). *[static]*
- **`0x0028E548`** - DJ line timer callback (DJ kinds 0-5, 7) that queues DJ speech flags: 0 spoke arrival (Radio BIG intro, First_Spoke, Text_Message), 1/2 hub chatter, 3/4/5 song change / free-ride start first/later (nothing when SEDVALUE is -1), 7 backcountry (BC_Intro); kinds 0-4 and 7 queue DJ_Radio_Big_Intro. Free ride uses kind 2 at a station and kind 4 on a course. *[static]*
- **`0x0028E888`** - Arrival / ride start music: calls `0x0028E8C0`(19, 1). *[static]*
- **`0x0028E8C0`** - Music code handler (code, a2) for NIS codes and travel. Codes 21-25 (fly-over, in music modes): PickNextSong `0x0028D488`, FadeOut(1 s) via `0x002B3D48`(1.0), forced request kind 3 (PlayMusic(36)) after 3000 ms via `0x002ADCA0`. Codes 19/20 need a2 != 0; 19 = arrival/ride start, 20 = travel/course change (from `0x0027A860` as (20, 1)): cancel timers, stop rider loops and ambience, destination request/pktrans/ambience event 30. Other codes are forwarded to the song as a Pathfinder event. *[PS2]*
  - `0x0028EF58`: Path that forwards other NIS music codes to the song as a Pathfinder event. *[static]*
- **`0x0028F000`** - Race music intensity, every frame while in state 6: trunc(min(counter/N, 1) * 127), N = 800/1000/1200 by tier (`0x00289C18`). The counter is reset through `0x0028F108` at PlayMusic, falls (`0x002961F0`) and forced resets (`0x0029A220`). *[PS2]*
- **`0x0028F108`** - Resets the race music intensity counter (used at PlayMusic, falls and forced resets). *[static]*
- **`0x0028F140`** - FE music state: sends a charsel event per front-end screen from table `0x00482A70`, ignored if the state is unchanged: title 0 (9 if an event was already sent), main menu/character setup/rider details/online/lodge 1, equip 2, buy attributes 3, audio options 4, uber-trick button map 5, rewards room 6, trophy room 7, career stats 8; states >= 10 send nothing. *[static]*
- **`0x0028F200`** - Restart/replay/quit menu audio step 1, called from `0x0026F8A0`. *[static]*
- **`0x0028F2C0`** - Restart/replay/quit menu audio, called from `0x0026F980`: restores the playlist index and queues a playlist song (kind 3) after chartune, else event 36. *[static]*
- **`0x0028F328`** - Music listener SendEventForced (vtable `0x00483688` slot +0x18): bypasses the duplicate-event filter and forwards to `0x002B3B88`; used for the big-air loop events 7/8. *[static]*
- **`0x0028F3C8`** - Music listener SendEvent (vtable `0x00483688` slot +0x20), the normal path for game music events. *[static]*
- **`0x0028F478`** - Music listener PlaySong (vtable `0x00483688` slot +0x10); also pops the HUD Now Playing (EA RADIO BIG) popup by calling HUD vfunc +0xC0 with command 5 when the MUSIC channel is audible. *[static]*
- **`0x0028F558`** - Sets the travel destination audio+0x6284. *[static]*
- **`0x0028F5B8`** - Map/Transport open audio, called from `0x00200ADC` (Map overlay vtable `0x004733F8`): pauses SFX, UI sound event 9, FadeOut(1 s) in music modes, loading loop on, event 0. *[static]*
  - `0x0028F60C`: UI sound call for event 9 (snd 3) after pausing SFX. *[static]*
- **`0x0028F678`** - Map/Transport close audio: loading loop off (1 s), restarts music at a station. *[static]*
- **`0x0028F700`** - Loads LoadingScreen.bnk (resident) into bank slot 13 (0xD). *[static]*
- **`0x0028F768`** - Starts the LoadingScreen.bnk loop on the MUSIC bus (also used for the map). *[static]*
- **`0x0028FA98`** - Stops the loading music loop with a fade (seconds; 1.0 used). *[static]*
- **`0x0028FC38`** - Stops FE music. *[static]*
- **`0x0028FC58`** - FE re-entry: plays charsel again at audio+0x6290; called from `0x001B3F78`. *[static]*

## `src/sound/soundsys.cpp`

Segment `0x0028FD00`-`0x002A9350`.

- **`0x002906B8`** - SFX voice start: plays the filled sound request record and returns a voice handle (< 0 = failed); used for every NIS sound and speech request. Request: *(audio+4)[i] bank slot, *(audio+8)[i] sound index, mgr+0x1D8+0x38[i] volume 0..127, mgr+0x214[i] gain pointer, mgr+0x1FC[i] position, mgr+0x238 owner rider, mgr+0x25C player, mgr+0x1D8+0x40+8i update callback. Every layer (0xFE-separated patch) of the bank entry starts together. *[PS2]*
- **`0x00290B58`** - 5-point piecewise linear curve lookup (table, x) with x at [0..4] and y at [5..9]. *[static]*
- **`0x00290C10`** - Curve lookup by index (i, x) into the tables at `0x00445898`: 0 speed 200/400/550/800 -> 33/70/100/127; 1 100/1000/2000/4000 -> 20/70/100/127; 2 500..2000 -> 0/10/20/40; 3 500..2500 -> 60/75/90/100/127. *[static]*
- **`0x00290C40`** - Grunt level computation. *[static]*
- **`0x00290CC0`** - UI sound player (audio, bank 0, snd): bus 5, not positional; reached via vtable audio+0xC slot +0x8. *[static]*
- **`0x00290FD0`** - Crowd anticipation at take-off when predicted air > 2 s, graded < 0.25 / < 0.5 / else by the pending trick value in the last 3 s. *[static]*
- **`0x002910E0`** - Starts the air whoosh (bank 0 snd 0x20, gain pointer audio+0x5830, base volume 127); observed to start 12-13 ticks after take-off once predicted air T > 2 s. *[PS2]*
- **`0x002913D8`** - Stops the air whoosh (250 ms fade). *[static]*
- **`0x00291710`** - Board surface class from rider+0x438 (rails use audio+0x598C) via jump table `0x00482AA0`: snow -1,0,5,6,12,14-17,19 -> 0; 2,3,13 -> 1; 1 -> 2; 4 -> 3; 10 -> 4; 9 -> 5; 7,8,18 -> 7; 11 -> 8. *[static]*
- **`0x002917D0`** - Board loop A (human only): SPUBOARD snd 0 with callback `0x00292CB8`. *[static]*
- **`0x00291C88`** - Board loop B (glide): snd class+4 (human, callback `0x00292DA0`) or class+6 (AI, `0x00292EF8`); SPUBOARD if class <= 3 else BOARD. x = compression * (1 - (brake + turn)), x *= 10*speed below speed 0.1, smoothed per player (audio+0x59B8). *[static]*
- **`0x00292508`** - Board loop C (carve, human): snd class+3 with callback `0x00293018`. *[static]*
- **`0x002929D8`** - Starts the board loops for riders (calls `0x00292A50`); called from world start `0x00286E20`. *[static]*
- **`0x00292A50`** - Starts the three per-rider board loops on BOARD (bus 6); called from `0x002929D8`, stopped by `0x00292B48`. *[static]*
- **`0x00292B48`** - Stops the board loops. *[static]*
- **`0x00292CB8`** - Board loop A callback: ground only; vol = curve `0x00482AF8` of speed, pitch = curve `0x00482B20`. *[static]*
- **`0x00292DA0`** - Board loop B glide callback (human riders). *[static]*
- **`0x00292EF8`** - Board sound loop B glide callback (AI riders). *[static]*
- **`0x00293018`** - Board sound loop C carve callback: y = brake + turn, smoothed in audio+0x5990 (50% when falling, 12.5% when rising). Family 0 volume curve `0x00482C68`, family 1 `0x00482CB8`, family 2 fixed 127; pitch from compression via curves `0x00482C90` / `0x00482CE0` / `0x00482D08`. *[static]*
- **`0x002934D0`** - Maps a surface class to the board sound family: 0 -> 0; 1-2 -> 1; 3 -> 2 on a rail, else 0; 4-8 -> 2. *[static]*
- **`0x00294170`** - Take-off sound: LAND sound class x 8 + 2, volume clamp(speed x 127, 64, 127), then calls the follow-up `0x00294678`. Called from ground `0x0013F178`, air `0x0012E9B8`, ollie `0x001307B8` and rail leave `0x0013BFA8` (near the end of the rail post stage, before the speed clamp); other notes call it the ollie event notification. *[static]*
- **`0x00294678`** - Take-off follow-up: plays Big_Air speech or crowd anticipation when the predicted air time exceeds 2 s. A retry path at `0x002947B0` is used when the air predictor is not in flight yet. *[static]*
- **`0x002947B0`** - Retry path of the take-off follow-up `0x00294678`, used when the air predictor is not in flight yet at take-off (inferred). *[unconfirmed]*
- **`0x002948D0`** - Landing sound (rider, trickValue): crowd cheer first, then LAND sound class x 8 + 1 (human) or + 5 (AI), volume from curve `0x00482D30` of impact speed. Called from `0x0010E910` and the crash get-up `0x0012D848`. *[static]*
- **`0x00294F48`** - Plays UI sound 0 (pause opened). *[static]*
- **`0x00294F78`** - UI sound dispatcher (audio, ev) via table `0x00482D60`: ev 0/9 -> snd 3 accept, 1/10 -> 4 back, 2/11 -> 2 move, 3/12 -> 1 scroll, 4/13 -> 0xD error, 7 -> 0x10, 8 -> 0x11, 14 -> 0x12 results panel, 15 -> 7 FE transition. *[static]*
- **`0x00295028`** - One of the two sound repeat FIFO routines (5 (obj, tag) pairs; check/insert), listed together with `0x00295628`; which one checks and which inserts is not stated. *[static]*
- **`0x00295628`** - One of the two sound repeat FIFO routines (5 (obj, tag) pairs; check/insert), listed together with `0x00295028`; which one checks and which inserts is not stated. *[static]*
- **`0x00296088`** - Instance contact sound dispatcher (audio only, no visuals): plays the watrig.adl record (via `0x002B5F60`) on COLLISION at level `0x00290C10`(0, |v|), range 33..127. Called from instance contact `0x00105398` unless instance flag 0x2000 is set; also covers crashbag hits. *[PS2]*
- **`0x002961F0`** - Crowd fall reaction on a rider crash (reached through the audio manager `0x0028B180`): only 0 or -0.25 reach it, giving Ahh20 or nothing. Also resets the music intensity counter. *[static]*
- **`0x00296310`** - Crash sound: bank 0 snd 0x30 + rand(3) (LAND 9 on surface 2/3), bus 5. Called from the crash entry `0x0010EB30` and the ragdoll `0x0012D4E8` (through the audio manager `0x0028B180`). *[PS2]*
- **`0x00296868`** - Crash slide loop start (snd 0x33, chosen by crash clip class); voice handles at rider+0x774/+0x778; counterpart of `0x00296E80` (0x34). Volume curve `0x00482DA0`; a running loop is not restarted. Stopped with a 0.75 s fade (`0x00296E20`/`0x00297438`) on both exits of crash phase 2 (`0x0012D160`), reset, finish and pause (`0x0029ED18`); loops end 45 ticks after get-up. *[PS2]*
- **`0x00296E20`** - Stops a crash slide loop with a 0.75 s fade; listed together with `0x00297438`. *[PS2]*
- **`0x00296E80`** - Crash slide loop start (snd 0x34); counterpart of `0x00296868` (0x33). *[PS2]*
- **`0x00297438`** - Stops a crash slide loop with a 0.75 s fade; listed together with `0x00296E20`. *[PS2]*
- **`0x002974A0`** - Stage-script one-shot sound on bus 5; id routing: 1-99 Mtn.bnk, 100-149 slot 8, 150-199 slot 9, >= 200 TRANSPORT. *[static]*
- **`0x00297950`** - Stage-script looped sound, same id routing as `0x002974A0` (1-99 Mtn.bnk, 100-149 slot 8, 150-199 slot 9, >= 200 TRANSPORT). *[static]*
- **`0x00297EB8`** - Stage-script sound stop. *[static]*
- **`0x00298138`** - Rider-pair attack sound (snd 0x5A, bus 5, volume 127, repeat tag 5), used by the soft attack `0x0010E3A8` and the crash attack `0x0010E468`. *[static]*
- **`0x00298488`** - Rider-pair bump sound (snd 0x36, bus 5, level `0x00290C10`(1, |v_a + v_b|), repeat tag 7), used by the soft `0x0010E228` and crash `0x0010E2E8` bump paths. *[static]*
- **`0x002989A8`** - Obstacle bump sound (snd 0x36, bus 5, volume 127, repeat tag 6); called from `0x0013F488`. *[static]*
- **`0x00298D90`** - Boost loop sound: bank 0 snd 0x7A (plus one-shot 0x4A if a2 is set) on ARCADESFX, refcounted at audio+0x59E4. Called from boost control `0x00114130`. *[static]*
- **`0x002992D8`** - Boost release: stops the boost loop. *[static]*
- **`0x00299368`** - Boost empty sound (bank 0 snd 0x6C, ARCADESFX). *[static]*
- **`0x00299638`** - Tricky start sound: bank 0 snd 0x6B after 400 ms plus arcade speech 0x20A8; requested when HUD slot 9 first appears. *[PS2]*
- **`0x002997B8`** - Tricky end sound (bank 0 snd 0x69); requested after HUD slot 9 is removed. *[PS2]*
- **`0x00299B70`** - Uber-denied sound (bank 0 snd 0x6C, ARCADESFX): called by `0x00132620` once per changed rail identity when an Uber request is unavailable. One note reads this call as trick naming; the sound-id reading is more specific. *[static]*
- **`0x00299E28`** - Overtake sound (bank 0 snd 0x6D, ARCADESFX) plus pass speech; called from the ranking update `0x0010F998`. *[PS2]*
- **`0x0029A220`** - Forced reset sound (bank 0 snd 0x7B, bus 5), the reset observer notification sent from `0x00116120`; also resets the music intensity counter via `0x0028F108`. *[static]*
- **`0x0029A530`** - Grab sound (bank 0 snd 0x77, ARCADESFX), the advanced-trick entry notification sent by the grab lifecycle `0x001352A8` in grab state 2 on both tweak and Uber entry, when tweak input starts the authored clip. Not a boost award. *[PS2]*
- **`0x0029A7D8`** - Points tick sound (bank 0 snd 0x4D, ARCADESFX), called from the score HUD `0x00117FE0`. *[PS2]*
- **`0x0029AB08`** - Boost meter change callback (old meter, delta), emitted by `0x0010E098` for eligible changes; also described as notification/event activity together with `0x0029AB40`. *[static]*
- **`0x0029AB40`** - Per-frame boost-meter fill tick sound (bank 0 snd 0x65, pitch +0x100 per step from 0x1000) and Tricky countdown sound 0x68. Runs in the per-frame audio update `0x00285BF8` before the frame's game tick, so it reads the previous tick's state. *[PS2]*
- **`0x0029B0E0`** - Pending Uber sound start (bank 0 snd 0x66, ARCADESFX), requested via the audio manager `0x0028B180` when HUD slot 10 initializes; the live voice is kept at audio+0x5FDC. Stopped by `0x0029B3C0`. *[PS2]*
- **`0x0029B3C0`** - Stops the pending Uber sound; requested via `0x0028B180` before HUD slot 10 is removed, and on an Uber bail. *[PS2]*
- **`0x0029B430`** - Uber commit sound (bank 0 snd 0x67) plus speech 0x2133, called from `0x0011A228`; reads the run's Uber count before the commit (Arcade_Uber 1 fires at the 4th Uber of the run). *[PS2]*
- **`0x0029B738`** - Per-frame Super Uber speech: Arcade_Uber mask 2 when the focus rider's tier becomes 10 (audio+0x581C holds the last tier). Runs in the per-frame audio update `0x00285BF8` (call at `0x00285D40`) before the game tick, so it fires one tick after the landing. *[PS2]*
- **`0x0029B7E0`** - Monster trick speech: Arcade_Uber mask 8, only when `0x0011B1A8` returns > 0; called from `0x0011A168` and `0x0011A228`. *[PS2]*
- **`0x0029B818`** - Loads a named world-trigger sound bank into dynamic slot 3. *[static]*
- **`0x0029C420`** - Countdown step handler (digit), called from `0x00234A30`: beep ch 5 snd 0x4E when the remaining countdown ticks are a multiple of 60 and at 0; on '3' fades out (2 s) the hub/chartune song, on '1' PickNextSong + PlayMusic(event 0) + Pause. Fade/preload happen only when the current song is a hub song (1-3) or chartune and audio+0x627C is set. Fires one tick after the core's race info. *[PS2]*
- **`0x0029C7B0`** - GO handler, called from `0x00234BE8`: music Resume with event 0 or 37, DJ artist intro request, GO sound 0x5E on ARCADESFX plus UI snd 0x62. Writes the GO tick to audio+0x582C; queues PA_Medal_Run_Intro in CTM when GMM+0x98 != 0 (the final). *[PS2]*
  - `0x0029C7FC`: Stores the GO game tick to audio+0x582C, the reference for the pass-speech gate (e.g. GO at tick 180, gate opens at 780). *[PS2]*
- **`0x0029CE28`** - Pauses SFX voices (via `0x002AD2A8` -> `0x002ACAC8`): bend 0 and volume 0 for active non-fading voices except UI sounds. *[static]*
- **`0x0029CED8`** - Pickup sound (audio, kind, rider, value): bank 0 snd 0x74/0x71/0x75/0x76/0x70 by kind on ARCADESFX (another note says kinds 0/1 select 0x70/0x71; exact kind-to-id order unconfirmed). Callers `0x0010E770`, `0x0010E7D0`, `0x0010E8B8`, `0x0030B9A0`; kind 4 also plays when the Big Challenge offer opens. *[PS2]*
- **`0x0029D290`** - Location ambience (bank 9 snd 0), faded over 5.03 s on a location change. *[static]*
- **`0x0029D6E0`** - Freeride challenge start music: event 33/34/38 by the challenge's music type 1/2/3. *[static]*
- **`0x0029D8E0`** - Freeride challenge end music (event 39); listed together with `0x0029DBB0`. *[static]*
- **`0x0029DBB0`** - Freeride challenge end/abort: music event (39), plus UI ev 14 when the argument is 0 (from `0x0030AAB4`); argument 1 (from `0x003091EC`) is silent. *[static]*
  - `0x0029DBD4`: UI sound call (ev 14) for the argument-0 challenge end. *[static]*
- **`0x0029DC48`** - Handplant sound (bank 0 snd 0x61, ARCADESFX), called from `0x001328B0`. Another note labels this call a handplant results-statistic update. *[static]*
- **`0x0029E590`** - Crash recovery meter sound (bank 0 snd 0x5F, ARCADESFX); listed together with `0x0029E970` (0x60). *[static]*
- **`0x0029E970`** - Crash recovery meter sound (bank 0 snd 0x60, ARCADESFX); listed together with `0x0029E590` (0x5F). *[static]*
- **`0x0029ED18`** - On pause, stops the human rider's crash slide loops, the pending-Uber sound and the boost loop. *[static]*
- **`0x0029EEE0`** - Speech callback (speech vtable `0x004836D8` slot +0x10) mapping the bank name to a bus, stored in audio+0x5738: 'DJ_' -> DJ (2) in a world, else the fixed-volume slot audio+0x5730 (FE, never ducked); 'PA_' -> PA (3); 'Arcade' -> ARCADESPEECH (10); otherwise CHARACTER (4) with per-speaker gain audio+0x636C+4*speaker. *[static]*
- **`0x0029F000`** - Speech stream volume request callback (speech vtable `0x004836D8` slot +0x18); returns the volume pointer. When a stream starts on channel 2 (DJ) it calls `0x00287F00`(0, 0.9999 s, 0.65), ducking the mode-0 group to 65% over ~1 s. *[static]*
- **`0x0029F088`** - Returns the current speech bus (audio+0x5738). *[static]*
- **`0x0029F0A0`** - CHARACTER speech gate: bus volume != 0 and not in replay (`0x00288AE0`). *[static]*
- **`0x0029F0D8`** - DJ speech gate: bus volume != 0 and not in replay. *[static]*
- **`0x0029F128`** - PA speech gate: bus volume != 0 and not in replay. *[static]*
- **`0x0029F160`** - ARCADESPEECH gate: bus volume != 0 and not in replay; checked at the start of `0x002A3B18`. *[static]*
- **`0x0029F198`** - Speech language argument mask from options word `0x00535610` bits 22-24 (arg0 of DJ/PA events). *[static]*
- **`0x0029F2B0`** - Speaker character mask by CHARDB id; listed together with `0x0029F330`. *[static]*
- **`0x0029F330`** - Speaker character mask by CHARDB id; listed together with `0x0029F2B0`; shares its table with the speech subject masks. *[static]*
- **`0x0029F3F8`** - Loads the rider grunt banks (slots 0xE/0xF). *[static]*
- **`0x0029F660`** - Rider grunt on the CHARACTER bus at level `0x00290C40`: GRNT bank 0xE, rotating 3..5 / random 0..1; AI riders use a bank by character. Called on rider crashes through the audio manager `0x0028B180`. *[static]*
- **`0x0029FCC8`** - Big_Air_* rider speech request, from the take-off follow-up `0x00294678` when the predicted air time >= 4.0 s, not in backcountry. *[static]*
- **`0x0029FF80`** - Trick_Easy / Trick_Difficult rider speech request from trick scored `0x00115B58`; played with landing reactions of kind 1/2. *[static]*
- **`0x002A02D8`** - Wipeout_* rider speech request, from crash exit `0x0012E690`. *[static]*
- **`0x002A0560`** - Pass / Passed_by rider speech, friend/foe chosen via `0x002A1820`. Called from the overtake sound `0x00299E28` <- `0x0010F998`; requires game tick - audio+0x582C (the GO tick) >= 600 and 670.56 < relative speed < 1788.16 cm/s. *[PS2]*
- **`0x002A0A30`** - Hit_* / Aggression_Response rider speech, from the rider-pair attack/bump paths `0x0010E228`..`0x0010E468`. *[static]*
- **`0x002A0E70`** - Post_Object_Collision rider speech, from soft collision `0x00108388`. *[static]*
- **`0x002A10C0`** - Speech busy check; ChangeSong calls it with 10 to test for a DJ line. *[static]*
- **`0x002A1138`** - BC_Challenge_<char> rider speech (rival backcountry challenge start). *[static]*
- **`0x002A1280`** - Hey_<char> rider speech (stage-script builtins). *[static]*
- **`0x002A1400`** - Finish_Line_<char> rider speech (rival finish). *[static]*
- **`0x002A1560`** - Whooh rider speech, from board press `0x00130DD0`. Another note reads this call as a rumble request driven by board-press depth. *[static]*
- **`0x002A16B0`** - Plays the rider's Post_Selection speech (0x20BC) on FE character select. *[static]*
- **`0x002A1778`** - Plays the rider's Customize speech (0x20BD) on FE character select. *[static]*
- **`0x002A1820`** - Friend-or-foe classification (A, B) for rider pass/hit speech: returns 0/1 (friend levels) or 2 (foe). 2 with two riders or two humans; else 2 if `0x00155B50`(A,B) >= 2 or `0x00155B50`(B,A) >= 2; else `0x00155AB0`(A,B): 0 -> 0, 1 -> 1, other -> 2. Relationship levels are updated (`0x00155BF0`) after the contact hit speech. *[PS2]*
- **`0x002A19D8`** - NIS PA/DJ speech cue dispatcher: maps a kind-7 cutscene cue number to a PA/DJ request; called at `0x00280B3C`. Cues: 0 Sponsor_Intro (+ forced song request when audio+0x530 = 0), 1 Rider_Intro (`0x002A32B0`), 2 Rider_Race_Intro (`0x002A3358`), 3 Medal_Run_Intro, 5 Finish_Line, 7 Medals, 8 DJ_Hub_Weather, 0xA DJ_Hub_Char_Stories, 0xC DJ_Event_Intro, 0xE DJ_First_Spoke, 0xF PA_Venue_Intro (`0x002A39E0`). Not a debug selector, as once thought. *[PS2]*
- **`0x002A1B58`** - Contact speech handler for ids < 100 (2 = Finish_Line of the contacting rider). *[static]*
- **`0x002A1B88`** - Contact speech handler for ids 100/101: BC_Challenge / Hey with a character from `0x00279F18`. *[static]*
- **`0x002A1BD8`** - Speech course event bit: course 0-4 -> bits 0-4, 5-7 -> 6-8, 8-10 -> 9-11, 11-13 -> 12-14, 14-16 -> 15-17. *[static]*
- **`0x002A1D48`** - Speech subject mask by CHARDB id; guest subject 0x1000. Listed together with `0x002A1DA0`. *[static]*
- **`0x002A1DA0`** - Speech subject mask by CHARDB id; listed together with `0x002A1D48`. *[static]*
- **`0x002A1E20`** - Returns the peak (1/2/3) of a course: 0,1,5,8,11,14,17,18 -> 1; 2,3,6,9,12,15,19,20 -> 2; 4,7,10,13,16,21 -> 3. Also used as the speech peak argument (masks 1/2/4) and for tiered rider-speech banks. *[static]*
- **`0x002A1E68`** - Speech place mask: MP race place 0->1, 1->2, 2->4, 3->8, else 0x10/0x200; otherwise from `0x00536730` via table `0x00483070`. *[static]*
- **`0x002A24B0`** - DJ_Event_Intro request variant (event 0x20CC); listed together with `0x002A2568`. *[static]*
- **`0x002A2568`** - DJ_Event_Intro request (event 0x20CC); listed together with the variant `0x002A24B0`. *[static]*
- **`0x002A2638`** - DJ_First_Spoke request (event 0x20BA). *[static]*
- **`0x002A26F0`** - DJ_Radio_Big_Intro request (event 0x20E5). *[static]*
- **`0x002A27D8`** - DJ_Radio_Big_Outro request (event 0x20E6). *[static]*
- **`0x002A2860`** - DJ artist intro by SEDVALUE s (event 0x20CF, starts with DJ_Silence_500): s < 0 or 999 -> generic DJ_Artist_Intro_gen; s < 100 -> lo mask 1 << s (DJ_Artist_Intro tags 0-29, none for 15 and 28); s >= 100 -> hi mask 1 << (s-100) (DJ_Artist_Intro_2 tags 0-2). *[static]*
- **`0x002A2938`** - DJ_Hub_Char_Progress request (event 0x2102). *[static]*
- **`0x002A2AD0`** - DJ_BC_Intro request (event 0x212B). *[static]*
- **`0x002A2B88`** - DJ_Text_Message request (event 0x212C). *[static]*
- **`0x002A2C30`** - DJ_Free_Ride_Intro request (event 0x212D). *[static]*
- **`0x002A2CF0`** - DJ_Aggression request (event 0x212E). *[static]*
- **`0x002A2DA0`** - DJ_High_Trick_Score request (event 0x212F). *[static]*
- **`0x002A2E50`** - DJ hub chatter from a pool of 8 or 5 categories; the used mask audio+0x573C is reset when exhausted. The first call plays Char_Stories (only when audio+0x5790 == 0 and not just arrived, audio+0x6258) and forces Peak_Boss next; otherwise post-event commentary, then a random unused category. *[PS2]*
- **`0x002A3170`** - Single-event / multiplayer GO speech: Radio BIG intro and artist intro. *[static]*
- **`0x002A31C0`** - PA_Sponsor_Intro request (event 0x20C0), posted after the pre-event panel (qualifier round card) appears. *[PS2]*
- **`0x002A32B0`** - PA_Rider_Intro request (event 0x20C1); args (language, subject mask of the first human). *[PS2]*
- **`0x002A3358`** - PA_Rider_Race_Intro request (event 0x20C2). *[PS2]*
- **`0x002A3400`** - PA_Medal_Run_Intro request (event 0x20C3), followed by the `0x002B1758` flush. *[PS2]*
- **`0x002A34D0`** - PA_Rider_Position request (event 0x20C4). *[static]*
- **`0x002A3708`** - PA_Finish_Line request (event 0x20C5). *[static]*
- **`0x002A3860`** - PA_Medals request (event 0x20C7). *[PS2]*
- **`0x002A39E0`** - PA_Venue_Intro request (event 0x20BB). *[PS2]*
- **`0x002A3B18`** - Arcade_Power_Ups speech for pickups: gated request of speech event 0x20A7 through queue `0x002B1458` (manager+0x5560, key (0, 0x20A7), args (0, 12), scalar 0, no refresh). Checks `0x0029F160`, non-null rider, rider+0x470 < 0, current rider `0x00285D98`(-1) and replay suppression `0x00288AE0`; on admission packs 0x010020A7 via `0x003D8008` and calls gp+0x173C (`0x003D76F0`) with 1 and the pickup type. Speech (Events.evt), not HUD or particle feedback. *[PS2]*
- **`0x002A3C00`** - Arcade_Prompts speech: Tricky countdown masks 0x10/0x8/0x4 and time's up 0x2. The time-up line is not played on a Give Up finish (the `0x00125368` path). *[PS2]*
- **`0x002A3CE8`** - Arcade_Bonus speech: mask 1 from the slope-style checkpoint bonus `0x001194C0`; race bonus speech (audio event 29, argument = value). *[PS2]*
- **`0x002A3DE0`** - Arcade_Uber speech category (variant mask). *[PS2]*
- **`0x002A3EB8`** - Arcade_Icons speech category (variant mask). *[PS2]*
- **`0x002A4040`** - Free-ride-only check; gates MusicTrigger B = 18 (ChangeSong). *[static]*
- **`0x002A4078`** - Rival mode finish announcer: kind 5 (Rival Time) -> PA_Finish_Line; kind 6 (Rival Points) in round 1 -> PA_Rider_Position. *[static]*
- **`0x002A4168`** - Is-Big-Air-event check. *[static]*
- **`0x002A41D8`** - Is-Half-Pipe-event check. *[static]*
- **`0x002A42C8`** - Returns whether the game mode is a time/points challenge (modes 6-11); such modes never queue hub chatter, First_Spoke, Text_Message or artist intros. *[static]*
- **`0x002A43B8`** - Speech OnIdle dispatcher (speech vtable slot +0x20): fires one pending DJ/PA/rider request per idle edge in fixed priority order (also the queue order the DJ timer relies on). Order by audio+ flag: Radio_Big_Intro 0x5768, BC_Intro 0x5784, First_Spoke 0x576C, Text_Message 0x577C, Free_Ride_Intro 0x5770, rider BC_Challenge 0x5788, Artist_Intro 0x5774, hub chatter 0x574C/0x5750/0x5754, Event_Intro 0x5758, Radio_Big_Outro 0x5740, falling through to rider Finish_Line 0x5744. *[PS2]*
- **`0x002A45C0`** - Records post-event DJ commentary data at the finish; listed together with `0x002A4660`. *[static]*
- **`0x002A4660`** - Records post-event DJ commentary data at the finish; listed together with `0x002A45C0`. *[static]*
- **`0x002A4770`** - DJ post-event commentary after a CTM event, played at the next hub chatter: progress / aggression / high score, picked at random avoiding the previous one. *[static]*
- **`0x002A4A78`** - World-start DJ scheduling: at a hub, latch 13 and DJ kind 2 after 2 ms; elsewhere DJ kind 4 with the song's SEDVALUE (not after a backcountry intro). *[PS2]*
- **`0x002A4CA0`** - Audio routine that draws from the visual (presentation) RNG during the rider passes (draw return address `0x002A4CC4`); such audio draws are rare but shift all later visual-RNG draws. *[PS2]*
  - `0x002A4CC4`: Return address of the visual-RNG draw. *[PS2]*
- **`0x002A68B0`** - Crowd loop pitch-bend swell (ATTACK/DECAY/MAXBEND on the ambient crowd loops). *[static]*
- **`0x002A6D78`** - Crowd instances (MIDI .eam on bank slot 5, bus 5). *[static]*
- **`0x002A7040`** - CROWD.INF parser. *[static]*
- **`0x002A73A8`** - Crowd reaction: landing cheer by trick value (< 0.25 Cheer10, < 0.65 Cheer20, else Cheer30); race finish always Cheer30 (called with 2). Trick value = pending points / (repeats+1), 1.0 = 10000 pts. *[static]*
- **`0x002A77C8`** - Audio query returning the crowd cheer level (called with gp+0x410), used by the CrowdMan2d timers. *[static]*

## `src/sound/ps2soundman.cpp`

Segment `0x002A9350`-`0x002A99D8`.

- **`0x002A9988`** - Positional range setup: V = 300 m for stage-script sounds, 30 m otherwise. *[static]*

## `src/sound/streamsys.cpp`

Segment `0x002A99D8`-`0x002ACD08`.

- **`0x002AB028`** - Reports whether the speech stream is playing (state audio+0x63E0). *[static]*
- **`0x002AB6B0`** - Voice update: runs the per-voice callback, then the 3D update `0x002AC868`. *[PS2]*
- **`0x002AB958`** - Caller of the per-frame song update `0x002B21E0`. *[static]*
- **`0x002ABB38`** - Stops a voice with a 250 ms linear fade. *[static]*
- **`0x002ABE78`** - Voice pitch bend (voice, bend): 0x1000 = 1.0, max 0x3FFF. *[static]*
- **`0x002AC868`** - Per-frame 3D voice update: distance volume trunc(base x ((V - max(d - 0.5, 0))/V)^2) with V = 30 m (300 m for stage-script sounds), changes <= 4 not sent; a doppler bend (1 + v/8000) overwrites the callback's bend. Board-loop pitch stays within 4066-4112 in races. *[PS2]*
- **`0x002ACAC8`** - Per-voice pause: bend 0, volume 0 (resume restores both). *[static]*

## `src/sound/bankmonitor.cpp`

Segment `0x002ACD08`-`0x002B4B08`.

- **`0x002AD2A8`** - SFX voice pause chain step (`0x0029CE28` -> `0x002AD2A8` -> `0x002ACAC8`). *[static]*
- **`0x002AD5F0`** - Stops a voice with a fade: (queue, handle, fadeSeconds, 1). *[static]*
- **`0x002ADCA0`** - Posts a delayed member-function call / delayed sound play: (queue, delayMs, pmf, a3, arg1, arg2, ...); delayed sound requests allocate their voice when the timer fires. CTM uses it with 3000 ms, kind 3 for a forced PlayMusic 36. *[static]*
- **`0x002ADDE0`** - Cancels queued timer callbacks / stops voices by callback key (queue, callbackKey). *[static]*
- **`0x002ADF60`** - Audio rand15 helper: calls rand `0x003177F0` on the visual (presentation) RNG and masks to 15 bits; used for random audio slot picks. Rare in a race (33 audio draws in 12440 ticks together with `0x002A4CA0`) but each shifts all later visual-RNG draws. *[PS2]*
  - `0x002ADF70`: Return address of the visual-RNG draw (call to `0x003177F0`). *[PS2]*
- **`0x002AE048`** - Registers audio service callbacks (used with `0x003D54C8`, `0x003D54E8`). *[static]*
- **`0x002AEBD0`** - Checks whether the EA stream has room for another segment. *[static]*
- **`0x002AF370`** - Audio clock: returns ms since boot. *[static]*
- **`0x002AF6C0`** - Pathfinder volume write gate: does nothing unless audio+0x6280 is set (ambience mode only). Called by `0x003D62C8` and the ramp `0x003D5A98`. *[static]*
- **`0x002AF838`** - Flushes a track: stops what is queued and playing (jump action flush bit). *[static]*
- **`0x002AF8A8`** - Speech callback entry (-> `0x002B0F48` -> `0x002B04D8`). *[static]*
- **`0x002AF960`** - Creates a SpeechBank from a '%s.hdr' line table. *[static]*
- **`0x002AFC88`** - Speech update body, called from the per-frame speech update `0x002B0C78`. *[static]*
- **`0x002AFD40`** - Loads eventdat Events.evt (speech events). *[static]*
- **`0x002B0088`** - Loads the speech header archives (%sheaders.big / %slanghead.big) and their .hdr tables. *[static]*
- **`0x002B0290`** - Speech voice busy check: rider/position lines are refused while busy unless < 500 ms remain. *[static]*
- **`0x002B04D8`** - Processes the speech script and queued event; builds the speech line stream path 'data/' + language.big + bank.dat (format %s%s%s.dat at `0x004832F8`). Reached via `0x002AF8A8` -> `0x002B0F48`. *[static]*
- **`0x002B07F8`** - Speech manager constructor (object at audio+0x5560); listed together with `0x002B0AE8`. *[static]*
- **`0x002B0AE8`** - Part of the speech manager constructor; listed together with `0x002B07F8`. *[static]*
- **`0x002B0C78`** - Per-frame speech update (-> `0x002AFC88`): busy tracking, OnIdle edge and scheduler resolve. *[static]*
- **`0x002B0E60`** - SpeechInstance (only instance 0 exists: one speech voice). *[static]*
- **`0x002B0F48`** - Speech processing step between the callback entry `0x002AF8A8` and `0x002B04D8`. *[static]*
- **`0x002B11B0`** - Speech stop. *[static]*
- **`0x002B1428`** - Speech request (feedback) queue clear: resets the active flags only. *[static]*
- **`0x002B1458`** - Speech request admission (speech, ch 0, eventId, rider, speaker, f12, callback, refresh) into a table of ten 32-byte slots, first empty wins, 180-frame lifetime. Duplicate keys are rejected unless refresh (which only resets the existing timer); a full queue rejects. *[PS2]*
- **`0x002B1720`** - Speech request queue tick: decrements active timers with 32-bit wrap and clears the active flag when the new signed value <= 0; inactive entries do not tick. *[static]*
- **`0x002B1758`** - Speech start / flush of pending speech requests; called as a flush after PA_Medal_Run_Intro at GO. *[static]*
- **`0x002B1A98`** - cSongConfiguration constructor defaults: BeatsPerMeasure 4, MeasuresPerBar 2, PhrasesPerBank 4, BeatsPerPhrase 8, PhraseAlign 16, DelayCount 0, DelayFeedback 90, DelayTime 100, DelayLevel 50, PathLevel 100, AsyncLevel 100, BPM 120.0, DUCKTOLOOPS 1, SEDVALUE -1, LOWPASS 0xFFFF, PREVIEW -1, SONGBIG 1. *[static]*
- **`0x002B1B98`** - SongInstance constructor (calls `0x002B1C50`). *[static]*
- **`0x002B1C50`** - SongInstance constructor body, called from `0x002B1B98`. *[static]*
- **`0x002B2018`** - Song pause body: pitch 0 and `0x003D1038`(0x11000002, 1). *[static]*
- **`0x002B2070`** - Song resume body. *[static]*
- **`0x002B20C8`** - Sends a Pathfinder event: `0x003D16F0`(-1, e) once the stream runs, else queues it in song+0x30. *[static]*
- **`0x002B2120`** - Sets the song voices' intensity via `0x003D0D70`. *[static]*
- **`0x002B2160`** - Applies the song LOWPASS value via `0x003B80A0` (only on change). *[static]*
- **`0x002B21E0`** - Per-frame song update, called from `0x002B4388`/`0x002AB958`. First call: load via `0x003D2350`, `0x003D25F0`(0x11000001, MUSDATA, latency 500, 2 queue entries) and, if LOOPDATA, `0x003D25F0`(0x11000002, LOOPDATA, latency 10, 1 entry), then sends the pending event song+0x30. Each frame: applies LOWPASS and volume = clamp(pathVol x 0.01 x PathLevel x channelVolume, 0, 127) -> `0x003B7E70`. *[static]*
- **`0x002B2418`** - Song fade-out body: `0x003B7EB0`(stream, sec x 1000, 0) and song+0x48 = 1. *[static]*
- **`0x002B2550`** - Returns the song status; -1 = finished (via `0x003D11B8`). *[static]*
- **`0x002B2850`** - Copies the async delay/echo parameters to the overlay (no effect in retail: DelayCount 0). *[static]*
- **`0x002B28C0`** - MUSIC.INF parser into cSongConfiguration records (0xAC bytes each); keys are case-insensitive (`0x0041AA88`). TITLE/ARTIST/ALBUM go to 64 x 100-byte tables at mgr+0x934/+0x2234/+0x3B34; section names (max 10 chars) to mgr+0x124+11*i; CATEGORY lines set flags mgr+0x420+0x14*song+4*cat; ADDTOFE counts FE songs (mgr+0x3EC = 35). *[static]*
- **`0x002B35A0`** - PlaySong(name or NULL, 0xC, &channelVolume, t0): stops the current song, picks the slot by name (or keeps mgr+0x3F0), builds a SongInstance, starts the loop-bank loader and calls `0x002B43D8`; sets mgr+0x418 = 1 (active, audio+0x530) and mgr+0x41C = -1 (last event). Listed together with `0x002B3838`. *[static]*
- **`0x002B3838`** - PlaySong variant with the same arguments (name or NULL, 0xC, &channelVolume, t0); listed together with `0x002B35A0`. *[static]*
- **`0x002B3A70`** - Song Pause (-> `0x002B2018`): pitch 0 and overlay pause, no fade; used to pause the sound system while a movie plays. *[static]*
- **`0x002B3A98`** - Song Resume (-> `0x002B2070`): pitch 0x1000 and overlay resume. *[static]*
- **`0x002B3AC0`** - Hard stop of the current song. *[static]*
- **`0x002B3B88`** - Forced send of a Pathfinder event to `0x002B20C8` (no duplicate filter); used by the music listener +0x18 for big-air events 7/8. *[static]*
- **`0x002B3BC0`** - SendEvent(e): ignores e if equal to the last event, else forwards it. The first event of PlaySong goes straight to `0x002B20C8`, so the same number sent right after the start (GO event 0) executes again. *[static]*
- **`0x002B3C28`** - Sets the Pathfinder intensity byte of the song voices via `0x003D0D70` (the voice intensity / branch-value setter); called with 0x7F after starting hub songs. *[static]*
- **`0x002B3C60`** - Song control wrapper calling `0x003D15C8` on the stream (meaning unknown). *[unconfirmed]*
- **`0x002B3C98`** - Sets the song path volume song+0x40. *[static]*
- **`0x002B3CD8`** - LOWPASS setter; has no caller (no runtime music filter modulation). *[static]*
- **`0x002B3D10`** - Sets the async loop overlay level: `0x003D5508`(0x11000002, v), only while song+0x54 is set; clamped 0..100 %, only changes voice+4, latched by each slice at its start. *[static]*
- **`0x002B3D48`** - FadeOut(seconds) of the current song (-> `0x002B2418`); used with 2.0 s and 1.0 s (music codes 21-25 use 1.0 s). *[static]*
  - `0x002B3E20`: Song volume ramp tick callback block inside this routine (runs every 40 ms). *[static]*
- **`0x002B3EE8`** - Adds a song to the playlist by name. *[static]*
- **`0x002B4070`** - SetPlaylist(mask): clears the playlist, then adds every FE song whose bit is set. *[static]*
- **`0x002B40F0`** - Returns a song TITLE (music manager +0x934 table). *[static]*
- **`0x002B4120`** - Returns a song ARTIST (music manager +0x2234 table). *[static]*
- **`0x002B4150`** - Returns a song ALBUM (music manager +0x3B34 table). *[static]*
- **`0x002B416C`** - Contains the previous-song stepping code below. *[static]*
  - `0x002B41E8`: Previous-song variant of NextSong inside this routine: steps backwards through the playlist; no caller. *[static]*
- **`0x002B42B8`** - NextSong(useCategory, cat): advances the index mod count until the song is in the playlist mask (and in cat when requested and available). *[static]*
- **`0x002B4388`** - Caller of the per-frame song update `0x002B21E0`. *[static]*
- **`0x002B43D8`** - Loop-bank loader started by PlaySong; the resident loop bank is later attached to Pathfinder track 1 by `0x002B4620`. *[static]*
- **`0x002B4470`** - Entry of the game-side loop slice scheduler, which is dead code: no caller and no pointer to it. *[static]*
- **`0x002B4568`** - Part of the dead game-side loop slice scheduler (its entry `0x002B4470` has no caller). *[static]*
- **`0x002B4620`** - Attaches the resident loop bank to Pathfinder track 1 (via `0x003D2DF8`) at big-air take-off. *[static]*
- **`0x002B46E8`** - Returns whether big-air loops were requested. *[static]*
- **`0x002B4708`** - Clears the big-air loop request (song+0x4C only). *[static]*
- **`0x002B4740`** - Part of the dead game-side loop slice scheduler (entry `0x002B4470`). *[static]*
- **`0x002B4878`** - Returns the current song's DUCKTOLOOPS value. *[static]*
- **`0x002B4978`** - Request Line preview: sends the song's PREVIEW value (11..45) as an event on character select. *[static]*
- **`0x002B49C0`** - Song id accessor for special songs (song+0x58); paired with `0x002B49E0`, which one is the getter or setter is not stated. *[unconfirmed]*
- **`0x002B49E0`** - Song id accessor for special songs (song+0x58); paired with `0x002B49C0`, which one is the getter or setter is not stated. *[unconfirmed]*
- **`0x002B4AF0`** - Checks whether the current song is in the new playlist (used on a radio mode change). *[static]*

## `src/sound/icepick/worldtriggermanager.cpp`

Segment `0x002B4B08`-`0x002B9100`.

- **`0x002B4C38`** - Final step of the world emitter chain: plays the watrig sound (`0x002B7908` -> `0x002B5C68` -> `0x002B5D78` -> here). *[static]*
- **`0x002B5A18`** `cWorldTriggerManager_LoadTriggerInfo` - watrig.adl loader: 92 records, each a bank slot + sound or a named bank loaded into slot 3. *[static]*
- **`0x002B5C68`** - World emitter chain step (`0x002B7908` -> `0x002B5C68` -> `0x002B5D78` -> `0x002B4C38`). *[static]*
- **`0x002B5D78`** - World emitter chain step (`0x002B7908` -> `0x002B5C68` -> `0x002B5D78` -> `0x002B4C38`). *[static]*
- **`0x002B5F60`** - Looks up a watrig.adl record for a contact sound (used by the instance contact sound `0x00296088`). *[static]*
- **`0x002B6550`** - watrig special record handler that can request PA_Rider_Position. *[static]*
- **`0x002B7848`** - Audio emitters update, the post-camera part of the game update. *[static]*
- **`0x002B7908`** - World-instance sound emitter update: shapes and falloffs, volume = falloff x 127, bus 5. Chain `0x002B7908` -> `0x002B5C68` -> `0x002B5D78` -> `0x002B4C38`. *[static]*
