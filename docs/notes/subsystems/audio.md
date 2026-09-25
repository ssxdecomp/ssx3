# Audio, music and DJ

On the EE, SSX 3's audio is one large `SSXAudioSystem` object. It owns an 11-channel mixer, the sound-bank slots and
the SFX request plumbing, a music manager that plays EA "Pathfinder" interactive songs chosen from MUSIC.INF and
PLAYLIST.INF, and a single speech voice. That voice is shared by DJ Atomika, the PA announcer, rider speech and the
arcade call-outs. Game code reaches the object through an accessor and many small dispatcher functions, one per
sound or speech category. Under it, the EA audio library on the EE parses SND/SCxl data, runs the Pathfinder graphs
and the speech-event engine, decodes MicroTalk, and passes streams to the IOP driver `SNDDRV.IRX`.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

File assignments follow the decomp's current translation-unit split.

- `src/sound/ssxAudio.cpp`: `0x00284BB0` (`SSXAUDIO_Init`), constructor `0x00284C68`, per-frame update
  `0x00285BF8`, loaders `0x00285FB0` / `0x002862A8` (`cSSXAudio_FrontEndLoad`, see the naming note), world load /
  teardown `0x002867E8` / `0x00286A80`, mixer `0x002873D8`..`0x00287F00`, MIX.INF `0x00287FC8` / `0x002883B0`,
  playlist loader `0x00289520`, pause / resume `0x00289B70` / `0x00289BB8`.
- `src/sound/asyncsys.cpp`: accessors `0x0028B180` (returns the audio system), `0x0028B1B0`, `0x0028B1C8`,
  `0x0028B1D8`.
- `src/sound/bankmanager.cpp`: the music director `0x0028BF78`..`0x0028FC58` (radio mode, song choice, PlayMusic,
  deferred requests, DJ timers, travel and cutscene codes, front-end music, listener methods, loading loop).
- `src/sound/soundsys.cpp`: SFX request `0x002906B8`, gameplay SFX dispatchers `0x002910E0`..`0x0029ED18`, speech
  gates and category functions `0x0029EEE0`..`0x002A4A78`, crowd `0x002A6D78`..`0x002A73A8`.
- `src/sound/ps2soundman.cpp` (`0x002A9988`); `src/sound/streamsys.cpp` (voice update, stop, pitch
  `0x002AB028`..`0x002ACAC8`).
- `src/sound/bankmonitor.cpp`: delayed-call queue `0x002ADCA0` / `0x002ADDE0`, Pathfinder clock and glue
  (`0x002AE048`, `0x002AF370`, `0x002AF6C0`), speech manager `0x002AF960`..`0x002B1758`, song configuration,
  song instance and music manager `0x002B1A98`..`0x002B4AF0`.
- `src/sound/icepick/worldtriggermanager.cpp`: `0x002B5A18` (`cWorldTriggerManager_LoadTriggerInfo`, watrig.adl)
  and the emitters `0x002B7908`.
- `asm/2B4578.s` (not split): the EA audio library, with the SND tag parsers, stream setters, voice pools and mixer,
  MicroTalk `0x003CD1F8`..`0x003CE410`, Pathfinder `0x003CFC30`..`0x003D62C8` and the speech-event engine
  `0x003D69F0`..`0x003DB5C0`.
- Menus: `src/fe/festateaudiooptions.cpp` (`0x00196540` `cFEStateAudioOptions_onWidgetCreate`, `0x001966E0`
  `cFEStateAudioOptions_onWidgetEvent`, `0x00196B90`); `src/fe/messagecenter.cpp` (Request Line
  `0x00197500`..`0x00198AE8`, e.g. `0x00198340` `cFEStateRequestLine_updateButtonsText`);
  `src/fe/festateoptions.cpp` (`0x0018A258`, `0x0018B380` `cFEStateOptionsSound_updateWidget`); `src/fe/fereal.cpp`
  (UI-sound listeners); `src/fe/ovstatehud.cpp` (Now Playing). The audio options state `0x00195FF0` currently falls
  in `src/util/locale.cpp`.

**Naming note.** The decomp calls `0x002862A8` `cSSXAudio_FrontEndLoad`. The code reading describes it as the
world-side loader: it loads the WORLD bank set and applies the world channel-scale table (argument 1). In that
reading `0x00285FB0` loads the `[FE]` banks, applies the FE table (argument 0) and starts charsel. Which name is
right is unresolved.

## Globals and game state

| Address | Meaning |
|---|---|
| `0x004A3500` (gp+0x410) | Pointer to the SSXAudioSystem (0x7780 bytes); `0x0028B180` returns it before every audio call. |
| `0x004A28A8` (gp-0x848) | Game object G. `0x0028B1B0` = in game (G+0x84 != 0); `0x0028B1C8` = session G+0x84; `0x0028B1D8` = race (session +0xC, riders at +0x28[i]). |
| `0x00535C08` | Course index (course table `0x0043D950`). |
| `0x00535C10` | Event kind (tables `0x0043E7D0` / `0x0043E978`): 0 race, 1 slope style, 2 big air, 3 half pipe, 4 free ride incl. missions, 5 time challenge (rival time, peak races), 6 points challenge (rival points, peak jams) **(PS2)**. |
| `0x00535C11` | Path: 0 Conquer the Mountain (CTM), 1 single event, 2 multiplayer. |
| `0x00535C12` | Mode: 0 race, 1 slope style, 2 half pipe, 3 big air, 4 rival time, 5 rival points, 6-8 peak races, 9-11 peak jams, 12 free ride, 13 mission. |
| `0x00535610` | Options: bits 0-3 music vol, 8-11 SFX vol, 12-13 sound mode, 17 DJ, 18 EA SPORTS BIG Talk, 22-24 language (turned by `0x0029F198` into the speech mask 1 English, 2 French, 4 German, 8 Spanish). |
| `0x00536708` / `0x00536730` | Place → rider slot / rider slot → place. |

**Replay suppression (`0x00288AE0`).** True while the session's Replay object (session+0x28, constructor
`0x0026EFB8`) is in states 1..9, i.e. during instant-replay playback. State 0 means recording in a live race.
Results screens show 1 because the run replays behind them. It is not set by the demo or by split screen **(PS2)**.
It blocks PlayMusic (unless audio+0x6294 is set), the countdown beeps, the big-air duck and all speech.

## SSXAudioSystem layout

| Offset | Contents |
|---|---|
| +0x4 / +0x8 / +0xC | SFX request arrays (bank slot / sound); UI sound player (vtable +0x8 → `0x00290CC0`). |
| +0x118 | Embedded music manager. `*(audio+0x118)` is also dereferenced as the sound manager (SFX request records and the delayed-call queue at +0x1D8); the relation to the embedded manager is not stated. |
| +0x504 / +0x508 / +0x518 | Manager +0x3EC (front-end song count 35) / +0x3F0 (current index) / u64 "Radio BIG" mask. |
| +0x520 / +0x530 / +0x534 | Manager +0x408 current SongInstance / +0x418 active / +0x41C last event. |
| +0x5558 | **Unresolved; two readings.** Music-manager vtable `0x004838F8` (at manager +0x5440), or the music-listener vtable `0x00483688` (+0x10 `0x0028F478` PlaySong, +0x18 `0x0028F328` forced event, +0x20 `0x0028F3C8` event). |
| +0x5560 | Speech manager. |
| +0x5730 / +0x5738 / +0x573C | Fixed FE DJ volume / current speech bus (`0x0029F088`) / hub-chatter used mask. |
| +0x5740..+0x5788 | Pending speech flags served by OnIdle (+0x5780 = Text_Message variant). |
| +0x578C, +0x5814, +0x6254 | Set by the new-career start `0x00234F40`; +0x5814 / +0x6254 also by travel. Role not described. |
| +0x5790 / +0x579C[loc] | Char_Stories played / first-visit flags (via `0x00145D38`). |
| +0x581C / +0x582C / +0x5830 | Last Super Uber tier / GO tick (written at `0x0029C7FC` inside `0x0029C7B0`) / air-whoosh gain. |
| +0x598C / +0x5990 / +0x59B8 / +0x59E4 | Rail surface class / carve smoothing / glide smoothing / boost refcount. |
| +0x608C / +0x6098 | Radio mode / u64 custom playlist mask. |
| +0x60A0 / +0x60A4 | MUSIC volume copy / PLAYLIST.INF section names (`0x00289470`). |
| +0x623C | In a MusicTrigger zone (`0x0028D898`). |
| +0x6244..+0x624C | Big air: latched flight time, start, duck end. |
| +0x6258 | Just arrived. |
| +0x6274 / +0x6278 | Deferred request / kind. |
| +0x627C | Countdown/GO flag: set → GO sends event 0; clear → GO sends 37 and sets it; cleared at a finish with runs left. |
| +0x6280 | Pathfinder level writes on (ambience only). |
| +0x6284 | Travel destination. |
| +0x6290 | FE music state (10 = none). |
| +0x6294 | PlayMusic allowed in replay. |
| +0x62A4 / +0x62AC | Previous song / playlist index saved for the podium. |
| +0x62B0 / +0x62B4 / +0x62B8 | Mono / arcade audio on / DJ on. |
| +0x62BC + 16*ch | Mixer record {user volume, × scale, × duck, × mix = effective}; voices read +0x62C8 + 16*ch. |
| +0x636C[10] | Per-speaker CHARACTER gains. |
| +0x6394[ch] | Duck factor; duck state at +0x63C0 (active, mask, step, target, current, mode) and +0x63E0 (DJ stream seen playing). |
| +0x6414[ch] / +0x6440[ch] | MIX.INF step / target. |
| +0x646C / +0x6478 / +0x647C | Current mix / count / 25 × 0x28 records. |
| +0x6868, +0x6C50, +0x6C58 | Inputs of an inert gate (`0x00289688`); never written. |

**Music manager** (audio+0x118) fields:

- +0x124 + 11·i section names; +0x3E4 song count; +0x3E8 songs in the list; +0x3EC front-end count; +0x3F0 current
  index; +0x3F8 u64 playlist mask.
- +0x408 current SongInstance; +0x418 active; +0x41C last event.
- +0x420 + 0x14·song + 4·cat category flags; +0x920[5] songs per category.
- +0x934 / +0x2234 / +0x3B34 TITLE / ARTIST / ALBUM, 64 × 100 bytes (getters `0x002B40F0` / `0x002B4120` /
  `0x002B4150`).

**SongInstance** (constructor `0x002B1B98` → `0x002B1C50`) is a Pathfinder stream plus an async overlay. Fields:
+0x30 first event (queued until the stream runs), +0x40 path volume (int8, 127), +0x48 fading, +0x4C loops
requested, +0x54 overlay-level enable (always 1), +0x58 song id (`0x002B49C0` / `0x002B49E0`).

**Delayed calls.** `0x002ADCA0(queue, delayMs, pmf, ...)` posts a delayed member-function call, and `0x002ADDE0`
cancels one by key. The keys are `0x004A3648` → `0x0028E088` (music request), `0x004A3650` → `0x0028E548` (DJ
line), `0x004A3658` → `0x0028E068` (retry song change), and `0x004A3850` → the song-volume ramp tick at
`0x002B3E20` (inside `0x002B3D48`, every 40 ms).

## Lifecycle

| Moment | Function (caller) | Audio work |
|---|---|---|
| Boot | `0x00284BB0` → `0x00284C68` | Creates the object. Sets master ch0 = 10/11 at `0x00285094` (constant `0x0049EA90`, gp-0x4660). Installs speech vtable `0x004836D8`. |
| Front end | `0x00285FB0` (from `0x0018BEF8`, `0x001A1CE8`, `0x001D64C0`) | `[FE]` banks, releases ducks, plays charsel (no event), +0x6290 = 10. |
| FE → game | `0x00286200` | Radio mode 2: stop. Otherwise FadeOut(1 s). Unloads FE banks. |
| Loading screen | `0x0028F768` / `0x0028FA98(1.0)` (from `0x00233048` `cGameLoadScreen_loadTexture`, `0x00233640`) |
`LoadingScreen.bnk` (slot 13, `0x0028F700`) loops on MUSIC, 1 s fade-out. The map reuses it. |
| World load | `0x002867E8` (from `0x0022F6B0` `cGame_loadTrack`) | Radio mode and custom list from the profile. Unless pktrans plays: PickNextSong + PlayMusic, event 0 (CTM) or 36 (single event / MP). Painter queries, triggers reset, ducks released. |
| World audio init | `0x00286E20` | Board loops (`0x002929D8` → `0x00292A50`); PA venue intro (single event / MP). |
| Every frame | `0x00285BF8` | Duck release, MIX.INF step (`0x002887F8`), duck tick (`0x00287C48`), pause auto-resume. Runs `0x0029AB40`, `0x0029B738` (at `0x00285D40`) and `0x0028C8C8` before the frame's game tick **(PS2)**. |
| Finish | `0x00286EA0` (from `0x00125108`) | Crowd Cheer30, rider loops stopped, music event, results speech. |
| Podium | `0x0028CDF8` (from `0x00236EE8`) | chartune. |
| Leave world | `0x00286A80` | Resume if paused, Stop (no fade), loops stopped, painters destroyed, SetMix(0), timers cancelled, speech stopped. |
| FE re-entry | `0x0028FC58` (from `0x001B3F78`); stop `0x0028FC38` | charsel. |

## Mixer

| ch | Bus | Slider | Notes |
|---|---|---|---|
| 0 | master | none | `0x00287700` → `0x003B8160(vol × 127)` |
| 1 | MUSIC | Music | Songs, loading loop, hub, pktrans, charsel, chartune |
| 2 | DJ | Music | Only while DJ is on (+0x62B8) and radio mode != 2, else 0 (`0x00287558`) |
| 3 | PA | Effects | |
| 4 | CHARACTER | Speech | Rider speech, grunts, cutscene sounds |
| 5 | (unnamed) | Effects | Countdown, UI/HUD, crash, emitters; not in MIX.INF |
| 6 / 7 | BOARD / COLLISION | Effects | |
| 8 | AMBIENT | **Music** | Ambience, Peak*Amb |
| 9 / 10 | ARCADESFX / ARCADESPEECH | Effects | Only while arcade audio is on (+0x62B4, `0x002875D0`) |

**Sliders.** The setters are `0x00287410` (music), `0x00287488` (effects) and `0x00287520` (speech). A step 0..11
maps linearly to clamp(step / 11, 0, 1) in `0x002873D8`. The getters `0x00287670` / `0x002876A0` / `0x002876D0`
return round(vol × 11). The profile default (`0x0014F458`) is step 10.

**Effective volume.** `0x00287700` computes effective = slider × base scale × duck × mix. `0x00288D18` sets the base
scales through gp+0x414 (`0x004A3504`). The FE table (argument 0) is all 1.0 except CHARACTER 0.6. The world table
(argument 1) is MUSIC 1.0, DJ 0.55, PA 0.43, CHARACTER 0.8, ch5 0.8, BOARD 0.75, COLLISION 0.8, AMBIENT 0.5 and
both arcade channels 0.75.

**Per-speaker gains.** A CHARACTER voice uses `0x00287968(audio, 4, id)` = ch4 × a per-speaker scalar, copied from
`0x004A352C`..`0x004A3550` (gp+0x43C..+0x460) into +0x636C. In the world: moby, kaori, allegra, mac, elise 0.9;
zoe 0.8; griff 0.85; nate, psymon 1.0; viggo 0.95. In the front end all are 1.0.

**Master and output.** Master stays at 10/11, so the SND master byte `0x0050AA5D` is 115. At default sliders the
effective volumes are 0.909 × the scales **(PS2)**. The volume law is linear: halving a channel drops that group
6.0 dB, and the SPU2 stage is at unity **(PS2)**. SPU voices get byte × 129 per side, IOP-mixed voices byte × 258 in
Q15, and centre pan is 181/255. There is no limiter; about 0.015 % of samples clip **(PS2)**.

**MIX.INF.** The parser `0x00287FC8` takes its path from `0x004A3560` (gp+0x470) and reads up to 25 `[Mix n]`
records (defaults 100, TIME 0). The columns MUSIC, DJ, PA, CHARACTER, BOARD, COLLISION, AMBIENT, ARCADESFX and
ARCADESPEECH map to channels 1-4 and 6-10. TIME is stored in seconds.

`0x002883B0` SetMix(audio, idx) turns idx < 0 into 0 and ignores a repeat of the current mix; a level of -1 keeps
the channel. TIME 0 applies at once. Otherwise `0x002887A8` sets targets and steps of (target − current) / TIME /
60, which `0x002887F8` adds every frame: a linear fade at 60 Hz, with the same duration on every bus.

SetMix has only two callers. `0x00289C98` is driven by the tWPIGD_Mix world painter at the primary rider's position
(`0x002898A8`, called per rider from `0x00121950`); only Happiness (ABC1, mix 1) and Metro-City (BRA2, mix 2) are
nonzero in retail, both with 3000 ms fades. `0x00286A80` sets mix 0 at teardown. Menus, pause, the countdown and
the results never change the mix.

**Duck layer.** `0x00287F00(audio, mode, seconds, level)` fades a channel group through the duck factor, and mode 3
releases. The mask bits (`0x00287A10`) are 0x1 MUSIC, 0x2 ch5, 0x4 CHARACTER, 0x8 DJ, 0x10 AMBIENT, 0x20 BOARD,
0x40 COLLISION, 0x80 PA, 0x100 ARCADESFX and 0x200 ARCADESPEECH. Mode 0 uses mask 0x173 (`0x00284BA0`): MUSIC,
ch5, AMBIENT, BOARD, COLLISION and ARCADESFX.

- **DJ talk-over.** A DJ-channel stream start makes `0x0029F000` call `0x00287F00(0, 0.9999 s, 0.65)`.
- **Release.** Once `0x002AB028` has reported the stream playing, `0x00285BF8` calls `0x00287F00(3, 0.5 s, 1.0)`
  when it stops. `0x00285FB0`, `0x002867E8` and `0x002871B0` also release.
- `0x00289688`, a per-line MUSIC duck, is inert in retail.

## Music

### Song configuration (MUSIC.INF)

The parser is `0x002B28C0` (`cSongConfiguration`, 0xAC bytes, defaults set by `0x002B1A98`). Keys are
case-insensitive (`0x0041AA88`).

| Offset | Key (default) |
|---|---|
| +0x00 / +0x20 / +0x40 / +0x44 | PATHDATA (.mpf) / MUSDATA (.mus) / loop file count / LOOPDATA |
| +0x64..+0x74 | BeatsPerMeasure (4), MeasuresPerBar (2), PhrasesPerBank (4), BeatsPerPhrase (8), PhraseAlign (16) |
| +0x78..+0x84 | DelayCount (0), DelayFeedback (90), DelayTime (100), DelayLevel (50) |
| +0x88 / +0x8C / +0x90 | PathLevel (100) / AsyncLevel (100) / BPM (120.0) |
| +0x94 / +0x98 | DUCKTOLOOPS (1) / SEDVALUE (-1, picks the DJ artist intro) |
| +0x9C / +0xA0 / +0xA4 | LOWPASS (0xFFFF) / PREVIEW (-1, charsel event for the preview) / SONGBIG (1) |

TITLE, ARTIST and ALBUM go to the manager tables, and CATEGORY lines set membership flags (0 Race, 1 SlopeStyle, 2
BigAir, 3 HalfPipe, 4 BackCountry). The first 35 sections are the ADDTOFE (front-end) licensed songs, in PLAYLIST
order. No retail song uses the Whole/Quarter/Eighth/Sixteenth switches or the Delay* keys; DelayCount stays 0, so
the delay values copied by `0x002B2850` do nothing.

The disc has 45 songs: the 35 licensed ones plus these special sections.

| Section | Id | Played by | Bus |
|---|---|---|---|
| charsel | 301 | `0x00285FB0`, `0x0028FC58` | MUSIC |
| chartune | 201 | Podium `0x0028CDF8` | MUSIC |
| Peak1/2/3 (hub songs) | 1/2/3 | `0x0028CF98`, `0x0028E100` | MUSIC |
| Peak1Amb/2Amb/3Amb | 101-103 | Radio mode 2 (`0x0028CF98`, `0x002899F8`, `0x0028D5A0`) | AMBIENT |
| pktrans | 401 | Peak transitions `0x0028CD48`, `0x0028E8C0` | MUSIC |
| mapsel | none | Never (the name is not in the executable) | none |
| Playlist songs | -1 | `0x0028CF98` via the playlist index | MUSIC |

### Playlist, song choice and radio modes

**Building the list:**

- `0x00289520` loads PLAYLIST.INF `[SSX Mix]` (the only section; `0x002B3EE8` adds each SONG). The mask goes to
  audio+0x518.
- The custom playlist is the profile mask (`0x00158750`); `0x0028C2D0` copies it to audio+0x6098.
- `0x002B4070` SetPlaylist(mask) adds the front-end songs whose bit is set.
- `0x002B42B8` NextSong(useCategory, cat) steps (index + 1) mod count until the song is in the mask. When
  `useCategory` is set and the list has songs in `cat`, the song must also be in that category.
- The same walk backwards is at `0x002B41E8` (inside `0x002B416C`); it has no caller.

**PickNextSong (`0x0028D488`)** is the only chooser. It is not a shuffle: a song can come back after one other.

```
index = rand15 * FEcount / 0x7FFF        // 0x002ADF60 -> 0x003177F0 (BXrand__Fv), 15 bits
repeat (rand15 * 10 / 0x7FFF) + 1 times: NextSong(1, CurrentCategory())
if index == previous (audio+0x62A4): step once with the category, then once without
```

**CurrentCategory (`0x0028D8A0`)**: modes 6-8 → Race and 9-11 → SlopeStyle. Otherwise by course: 0-4 Race, 5-7
SlopeStyle, 8-10 BigAir, 11-13 HalfPipe, else (backcountry 14-16, stations 17-21) BackCountry.

**PlayMusic (`0x0028CF98`, first argument = event).** In radio mode 2 it plays the current peak's Peak<n>Amb and
sets audio+0x6280. At a station in CTM (course ≥ 17, not forced, no time/points challenge per `0x002A42C8`) it
plays the peak's hub song with event 12. Otherwise it plays the current playlist index (PlaySong with a NULL name).
`0x002A1E20` maps courses to peaks: 0,1,5,8,11,14,17,18 → 1; 2,3,6,9,12,15,19,20 → 2; 4,7,10,13,16,21 → 3.

**Radio modes** (`0x0028BF78` SetRadioMode, audio+0x608C; `0x0028D960` = mode != 2, `0x002899E8` = mode 2):

| Mode | Meaning | Playlist | DJ |
|---|---|---|---|
| 0 | Radio BIG | audio+0x518 | Options bit 17 (copied here) |
| 1 | Custom, DJ | audio+0x6098 | Options bit 17 |
| 2 | BIG Mountain Ambience | Peak*Amb on AMBIENT | off |
| 3 | Custom, no DJ | audio+0x6098 | off |

The menu rows (Radio BIG, BIG Mountain Ambience, Custom Playlist [DJ], Custom Playlist [No DJ]) are modes 0, 2, 1
and 3 (item values set in `0x00196540`). In a world, a change to mode 2 starts the ambience unless it is playing,
and mode 0 plays a new song when leaving the ambience. Modes 1 and 3 play a new song when the current one is not in
the list (`0x002B4AF0`) or is charsel; hub songs stay.

### Song instance, levels and controls

**PlaySong** (`0x002B35A0` / `0x002B3838`; arguments name or NULL, 0xC, &channelVolume, t0) stops the current song
(`0x002B3AC0`), picks the slot, builds the SongInstance, starts the loop-bank loader `0x002B43D8`, and sets active =
1 and last event = -1. `0x0028F478` also shows the Now Playing popup (HUD vfunc 0xC0, argument 5) while MUSIC is
audible.

**Per frame (`0x002B21E0`, from `0x002B4388` / `0x002AB958`).** The first call loads the Pathfinder data
(`0x003D2350`) and creates the track-0 voice on MUSDATA (`0x003D25F0`, latency 500 ms, 2 queue entries). If
LOOPDATA exists it also creates the track-1 overlay (latency 10 ms, 1 entry, so beat-synced). Then it sends a
queued first event. The tracks are addressed by stream handles with top byte 0x11 and low byte 1 or 2, and
`0x003D2DF8` (from `0x002B4620`) attaches the loop bank to track 1. After that, every frame sends LOWPASS on change
(`0x002B2160` → `0x003B80A0`) and writes the volume clamp(pathVol × 0.01 × PathLevel × channelVolume, 0, 127)
through `0x003B7E70`. The overlay level is `0x002B3D10(v)` → `0x003D5508`, clamped 0..100 %.

| Control | Function | Effect |
|---|---|---|
| FadeOut(s) | `0x002B3D48` → `0x002B2418` | `0x003B7EB0(stream, s × 1000, 0)`, song+0x48 = 1 (used with 2 s and 1 s). |
| Pause / Resume | `0x002B3A70` → `0x002B2018` / `0x002B3A98` → `0x002B2070` | Pitch 0 + overlay pause (`0x003D1038`) / pitch 0x1000 + resume. No fade. |
| Stop / path volume | `0x002B3AC0` / `0x002B3C98` | Hard stop / song+0x40. |
| Intensity | `0x002B3C28` → `0x003D0D70` | Pathfinder branch value (0x7F after hub songs start). |
| (unknown) | `0x002B3C60` → `0x003D15C8` | Not recovered. |
| LOWPASS | `0x002B3CD8` | No caller: no filter sweeps. |

**Stream setters.** `0x003B7E70` volume 0..127; `0x003B7FB8` pitch (4.12); `0x003B80A0` filter; `0x003B7EB0` fade,
linear in 0..127 in 10 ms ticks with a 16.16 step (`0x003B8530`).

**End of song.** Only `0x0028E088` checks it (`0x002B2550` → `0x003D11B8` = -1). A song therefore loops until an
event sends it to an ending part.

**LOWPASS.** `0x003B80A0` → `0x003B8978` → `0x003C3178` normalises the cutoff as value / (mixer rate / 2), with the
mixer rate 36000 (the driver field at `0x0050A8E8` + 0x2A) **(PS2)**. `0x003C8D00` drops the filter when the ratio
is ≥ 1, so all retail values (30000-42000, 0xFFFF) mean no filter. Values under 18000 would enable an EE filter
(`0x003CA8A0`, response not recovered).

### Music events

`0x002B3BC0` SendEvent drops an event equal to the previous one. `0x002B3B88` (forced) → `0x002B20C8` calls
`0x003D16F0(-1, e)` once the stream runs, and until then queues the event in song+0x30. PlaySong's first event
bypasses the filter, so GO's event 0 right after a start runs again. The game only sends numbers: the MPF decides
what they do, and the game never quantises transitions.

| Event | Sent by | Typical MPF meaning |
|---|---|---|
| 0 | PlayMusic, GO `0x0029C7B0`, `0x002872A8`, map open `0x0028F5B8` | Start part, save registers 1-5 |
| 36 | Single-event / MP world load, request kind 3, between heats `0x00286EA0`, `0x0028F2C0` | Save, jump to the endless idle part |
| 37 | GO on a later run | Back to the saved bar |
| 10 | Last finish, Request Line exit | Ending |
| 7 / 8 | Big-air take-off / landing (`0x0028C8C8`, forced) | Track 1 to a random loop head / stop with flush |
| 12 | Hub songs, Peak*Amb, pktrans | Default start |
| 18 | Song change `0x0028DF18` | Outro |
| 1 / 2 / 3 | pktrans (`0x0028CD48` 1; `0x0028E8C0` 2 for Peak 2, else 3) | Destination peak |
| 19 | (MPF data) | Fade 3 s, wait 3.1 s, stop |
| 30 | `0x0028E8C0` code 20, ambience mode | Ambience restart |
| 33 / 34 / 38, 39 | Free-ride challenge start by type (`0x0029D6E0`) / end (`0x0029D8E0`, `0x0029DBB0`) | Save, cut, long loop ending, wait 1200 ms, section-3 part |
| 9, 11, 13, 42 | MusicTrigger A = 0 (`0x0028D988`) | Course sections |
| B / B+1 (1/2, 5/6, 40/41) | MusicTrigger zones A = 1/2 (`0x0028D630`, `0x0028D7D8`), enter / leave | Interlude / return |
| 0..9 | FE screens on charsel (`0x0028F140`, table `0x00482A70`) | Menu sections |
| 11..45 | Request Line preview (`0x002B4978`, PREVIEW) | Previews |
| 1..10 | chartune | Winner's theme |

**Intensity.** `0x003D0D70` (from `0x002B2120` / `0x002B3C28`) sets a voice's branch value. Hub, podium, map and FE
songs use 127, and the loader leaves 0. In races `0x0028F000` writes trunc(min(counter / N, 1) × 127) every frame
in race state 6, with N = 800/1000/1200 frames by the tier from `0x00289C18`. The counter resets at PlayMusic, on
falls (`0x002961F0`) and on forced resets (`0x0029A220`), via `0x0028F108`. A song's three-way parts are therefore
low/mid/high-intensity variants: the music builds over about 13 s and drops back after a crash. After GO the
committed bars followed the byte rising 0, 17, 35 ... 121 **(PS2)**.

### Big air: DUCKTOLOOPS (`0x0028C8C8`, every frame in a world)

**Inputs.** The rider is from `0x00285D98(audio, -1)`. The predictor at rider+0x788 holds +0x98 flight time T,
+0x9C landing, +0xA0 elapsed and +0xAC state. The long-air flag is at `0x004A361C` (gp+0x52C), its previous value
at `0x004A3620` (gp+0x530).

1. **Flight time.** T = 0 unless the motion mode (`0x0011FE98`) is 1. In the air with predictor state 1 or 3, T is
   the latched value while the flag is set; otherwise it is +0x98, which is latched with start = 0.
2. **Loops allowed** when T > 3.9995 (`0x0049EB1C`), DUCKTOLOOPS = 1 (`0x002B4878`), the event is not Big Air or
   Half Pipe (`0x002A4168` / `0x002A41D8`), and the rider is in no MusicTrigger zone. Replay returns early.
3. **T > 2 s: air phase.** Set the flag. e = max(elapsed, start). On the first frame duckEnd = e + max((landing −
   elapsed) × 0.5, 0.5).

   ```
   floor  = clamp((1 - T*0.8425197*0.5) * 127, 20, 127)
   before duckEnd (p = e/duckEnd):
       stream = clamp(127 - (127-floor)*p, floor, 127)
       loops  = (127 - (clamp(127 - 107*p, 20, 127) - 20)) * musicVol/127 * 100
   after duckEnd:
       stream = floor;  loops = musicVol * 100
   ```

   - The whoosh gain audio+0x5830 = (127 − stream) / 127 × ch5. With loops, the path volume (`0x002B3C98`) follows
     stream.
   - First frame: the whoosh `0x002910E0` (bank 0 sound 0x20). With loops, if `0x002B4620` attaches the loop bank
     in music mode, forced event 7.
4. **T ≤ 2 s after a long air: landing.** `0x002913D8` stops the whoosh (250 ms). If loops were requested
   (`0x002B46E8`) in music mode it sends forced event 8, and `0x002B4708` clears the request. Path volume returns
   to 127 and loops = musicVol × 100.

On hardware the whoosh starts 12-13 ticks after take-off and tracks 127 × audio+0x5830. The loops never engage on
Snow Jam, Metro-City or The Junction (longest predicted flights 3.96 s and 3.16 s); with the threshold patched to
2.5 s the stream fell 127 → 20 as above **(PS2)**. The game-side slice scheduler (`0x002B4568`, `0x002B4740`,
`0x0028C430`, entry `0x002B4470`) has no caller; the audible loops are Pathfinder track 1.

Nothing else in gameplay (tricks, rails, boost, crashes) touches the music.

### What plays where

| Situation | Code | Behaviour |
|---|---|---|
| FE screens | `0x0028F140(state)` on enter; repeats ignored | Charsel event: title 0 (9 after an earlier event); main menu / char setup / rider details / online / lodge 1; equip 2; buy attributes 3; audio options 4; Uber map 5; rewards 6; trophy room 7; career stats 8; ≥ 10 nothing. |
| FMV | `0x001D25E8` / `0x001D2638` | Pause / Resume. |
| Map | `0x0028F5B8` / `0x0028F678` | Open: SFX paused, UI ev 9, FadeOut(1 s) in music modes, loading loop, event 0. Close: loop off (1 s), music restarts at a station. |
| Countdown 3 / 1 | `0x0029C420` | If a hub song or chartune plays and +0x627C is set. At 3: FadeOut(2 s). At 1: PickNextSong, PlayMusic(0), Pause (preload). |
| GO | `0x0029C7B0` | Resume. Event 0 if +0x627C, else event 37 and +0x627C = 1. Artist intro queued. |
| Pause | `0x00289B70` / `0x00289BB8` (from `0x001F8168` `cOVTemplate_PauseMenu_onCreateScreen`, `0x002306A8`, `0x00244880`) | SFX paused (`0x0029CE28`), music paused. Resume also cancels queued speech. No mix, fade or filter change. |
| Finish | `0x00286EA0` | Big Air / Pipe with runs left: event 36, +0x627C = 0. Otherwise event 10. |
| Podium | `0x0028CDF8` | Final round, human place < 3. chartune with the **winner's** event from `0x00482A10` by CHARDB character: Moby 10, Kaori 2, Allegra 8, Mac 1, Zoe 5, Griff 9, Elise 3, Nate 7, Psymon 4, Viggo 6 **(PS2)**. |
| Restart / replay / quit | `0x0028F200` (from `0x0026F8A0`), `0x0028F2C0` (from `0x0026F980`) | After chartune: restore the index, request kind 3. Otherwise event 36. |
| Cutscene music codes | `0x00280640` → `0x0028E8C0(code, 0)` | 21-25 (venue fly-overs), music modes: PickNextSong, FadeOut(1 s), forced request kind 3 after 3000 ms, which shows the EA RADIO BIG box **(PS2)**. 19/20 need argument 2 != 0. Other codes are sent as events (`0x0028EF58` inside `0x0028E8C0`). |
| Travel | `0x0028E8C0(20)` from the transition cinematic `0x0027A860` | Timers cancelled, loops and location ambience stopped. Free ride: PickNextSong + request kind 2 after 10 ms for the destination (+0x6284, `0x0028F558`). Unvisited backcountry: pktrans event 2/3 (paused). Ambience: destination Peak*Amb, event 30. |
| Arrival | `0x0028E888` → `0x0028E8C0(19, 1)` | |
| Location crossing | `0x0022DF50` | Only `0x00535C08` changes **(PS2)**. |

### Deferred requests, song changes and MusicTrigger

**Requests.** `0x0028E088` sets request/kind when no song plays, when the song has finished, or when forced;
otherwise it returns 0 and the queue retries. `0x0028E100` executes the request each frame: kind 0 hub song, 1
PlayMusic(0), 2 in the backcountry PickNextSong + PlayMusic(36) (else the hub song), 3 PlayMusic(36), 4
PlayMusic(0).

**ChangeSong (`0x0028DF18`)**, from MusicTrigger 18 in free ride (`0x002A4040`), retries after 100 ms while a DJ
line is busy (`0x002A10C0(10)`). Otherwise it fades out over 2 s when the DJ is off, then sends event 18 and calls
PickNextSong. It queues a forced request of kind 1 at 2000 ms and the DJ callback `0x0028E548` (kind 3, the new
song's SEDVALUE) at 1500 ms.

**MusicTrigger (`0x0028D988`, radio modes 0/1/3)**, by painter value B:

| B | Where | Action |
|---|---|---|
| 11 | Hub connectors | Latch, event 11, request kind 0 after 2000 ms (forced with DJ on), DJ kind 0/1 at 1500 ms on change. In a time/points challenge: ChangeSong instead. |
| 13 | Hubs | Event 13; hub chatter on change (not in challenges). |
| 14-17 | | Event-intro flags. |
| 18 | Courses, free ride only | ChangeSong. |
| 42 | | Forced event. |

In ambience mode the values 31/32 start Peak1Amb/Peak2Amb unless playing, 33 does nothing, and others are sent as
events.

On the PS2, crossing from Snow Jam into a station keeps the song until the connector's trigger 11 brings in the
Peak1 hub song through request kind 0, with the DJ spoke lines pending. At a new-career start on Happiness,
`0x00234F40` sets +0x578C and +0x6254 and clears +0x5790; the plane intro plays pktrans (event 1), then Peak1 and
the spoke lines follow **(PS2)**.

## Pathfinder runtime (EE library)

**Slots.** Four slots at `0x00517610` + 0x928·i, zeroed by the loader `0x003D2350`. Fields: +0xC / +0x10 tick
margins (50 / 10 ms), +0x30 id = (1 << 24) << mpf[0xC] | (1 << 28) << instance, +0x34 the MPF followed by the table
pointers, +0x58[track] voices, +0xBC 16 s16 registers, +0xDC 16 pending event copies (count at +0x91C).

**Voice** (0x110 bytes, `0x003D25F0`). Fields: +1 branch value ("intensity"), +2 previous value, +4 level % (100),
+0x20 bit fields (loop counter bits 0-3, slice 4-8, queue size 14-18, write index 19-23), +0x24 latency ms, +0x2C
loop node, +0x2F sync (latency < 50), +0x30 part head, +0x34 volume scale (127), +0x36 last committed node, +0x48 /
+0x10C next slice / pending start time, +0x54 EA stream, +0xFC queue ring.

**Clock.** Time is ms since boot (`0x002AF370`). `0x003D5128` runs from two callbacks registered by
`0x002AE048(0x003D54C8, 0x003D54E8)`. Reason 0x20 processes events first (`0x003D1E80`), then voices; reason 0x42
services voices only. SendEvent only queues.

**Commit (`0x003D4F10`).** A voice queues its next node when the audio queued for it (`0x003D4950`) is ≤ its latency
and the stream has room (`0x002AEBD0`). The song therefore stays one bar ahead: each bar was committed 420-490 ms
before the previous one ended, and the IOP played the queued files gaplessly **(PS2)**.

**Next node (`0x003D3D20` → `0x003D37A0` → `0x003D3900` → `0x003D41A8`).**

- `0x003D37A0` takes the first branch with lo ≤ v ≤ hi (signed, inclusive), else the nearest bound; 0xFFFF or no
  branch = stop. v is the intensity, not a random number. On the loop node, v is instead the loop counter, loaded
  from flags >> 12 at the first end node: 1-7 count down, while 0xF, 12 and 13 loop until an event.
- `0x003D3900` walks control nodes by sample value: 0 part head, -1 part end, -2 random, -3 post event (the last two
  unused). A part head with word-4 bits 17-19 = 1 draws the branch value (now_ms / 23) & 0x7F, the only random
  source. Routers (`0x003D3C90`) are unused by songs.
- `0x003D41A8` queues a stream offset (value × 0x80) or a bank entry; cross-track targets use a synthetic event
  (`0x003D4050`, unused). A 0xFFFF branch stops the voice, and after the queue drains `0x003D11B8` reports -1.

**Events** (`0x003D16F0`, `0x003D2068`, `0x003D1D28`, `0x003CFC30`; jump table `0x00495A30`). The event number
indexes the table (out of range: ignored), and the record is queued (max 16) with its post time. Each tick every
pending event runs its actions in order; an incomplete action blocks only its own event.

| Opcode | Action |
|---|---|
| 0x02 | Wait u32 ms after the previous action. |
| 0x04 | Jump. s16 node, or -16..-31 = register (−v) & 15. Byte 14: -1 absolute, ≥ 0 n-th part head of that section, -32 current section. Byte 15 bit 0 = flush (`0x002AF838`). Queued after what is queued, so an event more than ~500 ms before the bar end lands after that bar, later ones a bar later. On the sync track it waits for the master's next beat, re-rolling its random pick. |
| 0x06 | Ramp to s8 byte 12 over u16 byte 14 ms (`0x003D5A98`); curve byte 13: 1 linear, 2 quadratic, 3 hyperbolic, 0 none. |
| 0x0A | Save register (byte 14); value -33 = last node, -32 = section. |
| 0x01, 0x03, 0x05, 0x07-0x09, 0x0B-0x10 | Sync waits, pause, set +0x34, post/cancel events, stream params. Unused in retail. |

**Loop overlay.** Event 7 jumps track 1 to a random head, e.g. one of three 8-bar slice chains whose heads use sync
mode 0x100 over sliced nodes. `0x003D3658` computes the slice as (master beat + 1) mod beats-per-measure + 1, and
`0x003D41A8` queues one beat of bank entry value + slice − 1 at the master's next beat. The master is the voice with
the largest latency (track 0, `0x003D4B00`). Nodes under a sync-0 head (the long endings) are queued whole.

**Levels.** The Pathfinder volume writes (`0x002AF6C0`, from `0x003D62C8` / `0x003D5A98`) act only when
audio+0x6280 is set (ambience mode). In the music modes the stream level is `0x002B21E0`'s write, the loop level
sets voice+4 (latched per slice), and 0x06 ramps are inaudible. The EE mixer `0x003C2A50` scales by gain / 127.

## Speech: DJ Atomika, PA and riders

**Speech manager.** audio+0x5560 (constructors `0x002B07F8` / `0x002B0AE8`). Its callback vtable `0x004836D8` has
+0x08 start stream (`0x002854F8`), +0x10 bank → bus (`0x0029EEE0`), +0x18 volume + DJ duck (`0x0029F000`) and
+0x20 OnIdle (`0x002A43B8`). Only SpeechInstance 0 exists (`0x002B0E60`; start `0x002B1758`, stop `0x002B11B0`),
so **one voice** serves all speech.

**Request path.** Every category function (`0x0029FCC8`..`0x002A3EB8`) first checks its bus gate (`0x0029F0A0`
CHARACTER, `0x0029F0D8` DJ, `0x0029F128` PA, `0x0029F160` ARCADESPEECH: nonzero volume, no replay). It then admits
the request with `0x002B1458(speech, 0, eventId, rider, speaker, f12, callback, refresh)` into a 10-slot table
(180-frame lifetime). Finally it posts the event with bitmask arguments via `0x003D8008(1, 0, eventId)` and the
pointer at `0x004A482C` (gp+0x173C = `0x003D76F0` → `0x003D7418`). Speakers are the character index, 0xA DJ, 0xB
PA and 0xC arcade. The bus comes from the bank name (`0x0029EEE0`): "DJ_" → DJ (the fixed +0x5730 in the FE), "PA_"
→ PA, "Arcade" → ARCADESPEECH, anything else → CHARACTER with the per-speaker gain.

**Event engine.** An event is posted only if rand(100) < its chance byte (100 everywhere). Of 16 slots, an expired
one (age > W) is reused; otherwise the event pre-empts an active event of priority ≤ P, or is dropped. Priorities
are DJ 900-1000, arcade 890-892, PA 800-801 and rider 500-601. Rider and position lines also refuse while the voice
is busy, unless < 500 ms remain (`0x002B0290`).

**Per frame (`0x002B0C78` → `0x002AFC88`).** When the voice turns free (idle or < 500 ms left) after being busy,
OnIdle fires one pending flag. The best pending event then wins (highest priority, then newest; older ones are
flushed unless flag 0x04 is set; W counts 60 Hz ticks). Its lines stream back to back while the request is still in
the table.

**Line selection.** SPEECH.BIG (`headers.big`) and ENGLISH.BIG (`langhead.big`) hold one `.hdr` per bank plus
`eventdat\Events.evt` (`0x002B0088`, `0x002AFD40`). Lines stream from "data/" + language .big + bank .dat
(`0x002B04D8`). A line matches when `arg & (1 << tag)`. The pick is uniform (`0x003DB5C0`, RNG `0x003DB4D0`), with a
32-entry no-repeat ring at `0x00450B88`, keyed by bank, that rejects the last min(n/2, 10) picks. `0x003D95B8` also
has a shuffle mode and `0x003D8CB0` a weighted pick.

| Argument | Source | Values |
|---|---|---|
| Language | `0x0029F198` | 1 English, 2 French, 4 German, 8 Spanish; arg0 of every DJ/PA event; the USA disc has English only |
| Speaker / subject | `0x0029F330` / `0x0029F2B0`, `0x002A1D48` / `0x002A1DA0`; CHARDB ids (`0x00123128`) | moby 0x4, kaori 0x10, allegra 0x200, mac 0x2, zoe 0x20, griff 0x100, elise 0x1, nate 0x80, psymon 0x8, viggo 0x40; guest speaker 0 / subject 0x1000 |
| Peak | `0x002A1E20` | 1/2/4 |
| Course bit | `0x002A1BD8` | Courses 0-4 → bits 0-4, 5-7 → 6-8, 8-10 → 9-11, 11-13 → 12-14, 14-16 → 15-17 |
| Place | `0x002A1E68` | MP race 0/1/2/3 → 1/2/4/8, else 0x10/0x200; otherwise `0x00536730` via `0x00483070` |
| Song | `0x002A2860` (SEDVALUE s) | s < 0 or 999 → generic bank; s < 100 → 1 << s in DJ_Artist_Intro (tags 0-29, none for 15/28); s ≥ 100 → 1 << (s − 100) in DJ_Artist_Intro_2 |

Events.evt sends 0x40 to the `*_nat` banks and 0x80 to `*_vig`. In the original game Nate therefore speaks Viggo's
lines and Viggo speaks Nate's; the swap lives in the event file, not the code.

### DJ (radio modes 0/1, DJ option on)

| Bank | Event | Function | Trigger |
|---|---|---|---|
| DJ_Radio_Big_Intro | 0x20E5 | `0x002A26F0` | DJ kinds 0-4 and 7; rival start `0x002872A8`; hub entry; single event / MP GO `0x002A3170` |
| DJ_Artist_Intro / _2 / _gen | 0x20CF | `0x002A2860(SED)` | Flags +0x5774/+0x5778 from `0x002872A8`, GO (career round 1, or round 2 in race/slope), `0x002A3170`, song change (DJ kind 3 at 1500 ms); starts with a 500 ms silence bank |
| DJ_Event_Intro / DJ_Radio_Big_Outro | 0x20CC / 0x20E6 | `0x002A2568`, `0x002A24B0` / `0x002A27D8` | MusicTrigger 14-17; post-event fallback |
| DJ_First_Spoke | 0x20BA | `0x002A2638` | Hub spoke arrival (kind 0) |
| DJ_Text_Message | 0x212C | `0x002A2B88` | Kind 0 on Peak 1 (variant 2 first, then 1) |
| DJ_Free_Ride_Intro | 0x212D | `0x002A2C30` | Kinds 3-5 on Peak 1, first visit of a race/slope location |
| DJ_BC_Intro | 0x212B | `0x002A2AD0` | Backcountry arrival (kind 7) |
| DJ_Hub_* (7 categories, e.g. Char_Stories 0x20CA) | | `0x002A2E50(pool)` | Hub chatter: +0x574C/+0x5750/+0x5754 from DJ kinds 1/2, MusicTrigger 13, return from an event |
| DJ_Hub_Char_Progress 0x2102, DJ_Aggression 0x212E, DJ_High_Trick_Score 0x212F | | `0x002A2938` / `0x002A2CF0` / `0x002A2DA0` | Post-event commentary `0x002A4770` after a CTM event (recorded by `0x002A45C0` / `0x002A4660`): 1st place, hits ≥ 5, score ≥ 27 (24 in big air); random, not the previous one |

**DJ timer.** `0x0028E548` takes kind 0 (spoke), 1/2 (hub), 3/4/5 (song change; free-ride start first/later;
nothing if SEDVALUE is -1) or 7 (backcountry). It consults `0x00146008` (`cBENewPlayerInterface_isPeakLocked1`,
profile +0x278 bit 12); that bit was set in every profile read.

**Free-ride start.** `0x002A4A78` (not after a backcountry intro) queues DJ kind 2 after 2 ms at a hub, and kind 4
with the song's SEDVALUE elsewhere.

**OnIdle order (`0x002A43B8`, one flag per idle edge).** The order is: Radio_Big_Intro (+0x5768) → BC_Intro
(+0x5784) → First_Spoke (+0x576C) → Text_Message (+0x577C) → Free_Ride_Intro (+0x5770) → rider BC_Challenge
(+0x5788) → Artist_Intro (+0x5774) → hub chatter (+0x574C/+0x5750/+0x5754) → Event_Intro (+0x5758) →
Radio_Big_Outro (+0x5740) → rider Finish_Line (+0x5744). Chained lines therefore play back to back. The DJ does not
wait for musical boundaries.

**Hub chatter (`0x002A2E50`).** The first call plays Char_Stories (only if +0x5790 == 0 and not just arrived) and
forces Peak_Boss next. After that, post-event commentary comes first; otherwise a random unused category of the
pool (8 or 5) is picked, and the used mask +0x573C resets when the pool is exhausted. Time/points challenges
(`0x002A42C8`) never queue hub chatter, First_Spoke, Text_Message or artist intros.

### PA announcer (speaker 0xB)

| Bank | Event | Function | Trigger |
|---|---|---|---|
| PA_Venue_Intro | 0x20BB | `0x002A39E0` | `0x00286E20` (single event / MP); cutscene cue 0xF in every venue fly-over (so also in CTM) |
| PA_Sponsor_Intro | 0x20C0 | `0x002A31C0` | Pre-event screen `0x001FB588` (career, round < 2, kind != 4); cue 0 |
| PA_Medal_Run_Intro | 0x20C3 | `0x002A3400` | GO in CTM when game-mode +0x98 != 0 (set for round 3 by the race `0x0023A108` and freestyle `0x00238E20` inits and by one-round handlers; 0 in rival challenges); cue 3. Posted at the GO tick, before the artist intro **(PS2)**. |
| PA_Rider_Postition | 0x20C4 | `0x002A34D0` | Finish (career, round < 3, non-race); rival points finish; `0x002B6550` |
| PA_Finish_Line | 0x20C5 | `0x002A3708` | Finish (race courses or final round); rival time finish `0x002A4078`; cue 5 |
| PA_Rider_Intro / _Race_Intro | 0x20C1 / 0x20C2 | `0x002A32B0` / `0x002A3358` | Cues 1 / 2 at the start of each CTM freestyle / race approach **(PS2)** |
| PA_Medals | 0x20C7 | `0x002A3860` | Cue 7 at the start of each podium scene; place mask (8 outside the career) **(PS2)** |

`0x002A19D8` is the cutscene PA/DJ cue dispatcher (called at `0x00280B3C` inside `0x002808E8`). Cues 8, 0xA, 0xC
and 0xE are DJ_Hub_Weather, DJ_Hub_Char_Stories, DJ_Event_Intro and DJ_First_Spoke. Cue 0 also forces a song
request when +0x530 = 0.

### Rider and arcade speech

**Gate.** Rider speech needs a nonzero CHARACTER volume, no replay, a rider who has not crashed and is the local
human (`0x00285D98`), a free voice, and the listener in range (`0x00288B40`). Tiered banks follow the peak.

**Friend or foe (`0x002A1820(A, B)`).** The result is foe (2) with two riders or two humans, or when a relationship
level (`0x00155B50`) is ≥ 2. Otherwise the kind (`0x00155AB0`) decides: 0 → 0, 1 → 1, else 2.

Records are at `0x004A6CA8` + bank×0x9B50 + char×0xF88 + other×3 + 0xBC1 = {kind, level, score}; the bank is 2 for AI
(`0x0014A0E0` `cBELibrary_getProfileIndex__Fi`). Contacts raise the levels (`0x00155BF0`, +1/+2/+4/+6) after that
contact's hit line **(PS2)**.

| Bank | Event(s) | Function | Trigger |
|---|---|---|---|
| Big_Air_* | 0x2084/0x2083/0x2091 | `0x0029FCC8` | Take-off `0x00294678`, predicted air ≥ 4.0 s, not backcountry |
| Trick_Easy_* / _Difficult_* | 0x2082/0x209A/0x209C, 0x2090/0x209B/0x209D | `0x0029FF80` | Trick scored `0x00115B58` |
| Wipeout_* | 0x2088/0x20A0/0x20A1 | `0x002A02D8` | Crash exit `0x0012E690` |
| Pass / Passed_by (friend/foe) | 0x2080/0x2081/0x207D/0x207F | `0x002A0560` | Overtake `0x00299E28` (from `0x0010F998`); ≥ 600 ticks after GO **(PS2)**; relative speed 670.56-1788.16 cm/s |
| Hit_* / Aggression_Response | 0x208A/0x208E/0x208F/0x2078/0x207E | `0x002A0A30` | Rider-pair attacks `0x0010E228`..`0x0010E468` |
| Post_Object_Collision / Whooh | 0x2077 / 0x20B8 | `0x002A0E70` / `0x002A1560` | Soft collision `0x00108388` / board press `0x00130DD0` |
| Finish_Line_, Hey_, BC_Challenge_<char> | 0x20B9, 0x20D4, 0x20D3 | `0x002A1400`, `0x002A1280`, `0x002A1138` | Rival finish; stage-script builtins (`0x001235F8`); rival BC start. Contact speech ids via `0x00123E30`: id < 100 → `0x002A1B58`, 100/101 → `0x002A1B88` |
| Post_Selection / Customize | 0x20BC / 0x20BD | `0x002A16B0` / `0x002A1778` | FE character select `0x001A0358` |
| Arcade_Power_Ups / _Prompts | 0x20A7 / 0x20A8 | `0x002A3B18` / `0x002A3C00` | Pickups / Tricky countdown masks 0x10/0x8/0x4, time's up 0x2 |
| Arcade_Bonus | 0x20A9 | `0x002A3CE8` | Only the slope-style checkpoint bonus `0x001194C0` (human, mode 1) |
| Arcade_Uber / _Icons | 0x2133 / 0x2145 | `0x002A3DE0` / `0x002A3EB8` | Combo commit; Super Uber (2) from `0x0029B738`; monster trick (8) from `0x0029B7E0` |

The Arcade_* banks play on ARCADESPEECH with speaker 0xC.

## Sound effects

**Requests.** A call site fills a request record (a struct of arrays at +0x1D8 of `*(audio+0x118)`, slot index at
+0x1F4) and calls `0x002906B8(audio)`, which returns a handle (< 0 = failed). Defaults are pitch 100, delay
{0, 90, 50} and volume 127. The fields are: the audio+4 / +8 arrays (bank slot / sound), block +0x38 volume, +0x214
gain pointer (`0x00287968(audio, bus, player)`, the bus's effective volume), +0x1FC position (usually
rider+0x110), +0x238 / +0x25C owner / player, and block +0x40 + 8i the update callback.

**Voice control.** `0x002AD5F0(queue, handle, fadeSeconds, 1)` fades and stops, `0x002ADDE0` stops by callback,
`0x002ABB38` stops with a 250 ms linear fade, and `0x002ABE78(voice, bend)` sets pitch (0x1000 = 1.0, max 0x3FFF).
Callbacks write the volume at voice+0x64. `0x002AB6B0` runs the callback, then the 3D update `0x002AC868`:

- Volume = trunc(base × ((V − max(d − 0.5, 0)) / V)²), with V = 30 m, or 300 m for stage-script sounds
  (`0x002A9988`). The listener sits 1 m ahead and 25 cm off the camera (`0x00285930`), and changes ≤ 4 are not sent.
- A doppler bend of 1 + v/8000 overwrites the pitch. Mono (+0x62B0) drops the azimuth.

**Pause.** `0x0029CE28` → `0x002AD2A8` → `0x002ACAC8` sets bend 0 and volume 0 on every active, non-fading voice
except UI. `0x0029ED18` also stops the human's slide loops, the pending-Uber sound and the boost loop.

**Voice pools (`0x003BA0B0`).** There are 48 SPU voices (PS-ADPCM) and 8 IOP-mixed voices (MicroTalk, EA-XA,
PCM8), one per channel of each layer. Allocation takes a free voice, else steals the lowest priority (tag 0x06) ≤
min(new, 100), oldest first, with a hard stop. A layer that gets no voice fails the whole request, and delayed
requests allocate when they fire.

**Patch layers.** All 0xFE-separated patches of an entry start together (`0x003BB588`). Volume is 0x0E ± rnd(0x0F)
× velocity. Pitch is 0x10 + (note − 0x07) × 100 cents ± rnd(0x11). Pan is 0x0C ± rnd(0x0D) via the sine table
`0x0044C590`. Tag 0x19 is the envelope (100 Hz, start level 0x1C), and 0x1D-0x23 are the LFOs.

**Gates.** Listener within 100 units (`0x00288B40`); a repeat FIFO of 5 (object, tag) pairs (`0x00295028` /
`0x00295628`); local human only; muted after finishing.

**Curves.** `0x00290B58(table, x)` is 5-point piecewise linear. `0x00290C10(i, x)` uses the tables at `0x00445898`:
0 = speed 200/400/550/800 → 33/70/100/127; 1 = 100/1000/2000/4000 → 20/70/100/127; 2 = 500..2000 → 0/10/20/40; 3 =
500..2500 → 60/75/90/100/127.

**Bank slots.** The loaders are `0x00285FB0` FE, `0x002862A8` world, `0x0029F3F8` grunts, `0x0028F700` loading.

| Slot | Bank | Slot | Bank |
|---|---|---|---|
| 0 | MAIN: zbxsfx.bnk (game) / SSX3Menu.bnk (FE) | 7 | TRICKY trickyut.bnk |
| 1 | BOARD zboard.bnk | 8, 9 | Per-location banks (world kind-20 chunk, rid 0/1, `0x00286CA8`) **(PS2)** |
| 2 | MOUNTAIN Mtn.bnk | 0xA | LAND land.bnk |
| 3 | Named world-trigger banks (`0x0029B818`) | 0xC | Dynamic |
| 4 | TRANSPORT | 0xD | LoadingScreen.bnk |
| 5 | CROWD Crowd.bnk | 0xE / 0xF | GRNT_<char> / GRNT_AI |
| 6 | AUX (unused) | 0x10 | SPUBOARD zboardSPU.bnk |
| 17-26 | Cutscene banks (17 main, 18 location, 19-26 per script) | | |

SNOW.INF is not used (its name and keys are in no binary; the board curves are hard-coded), and CROWD.INF's
CROWDPATCH1-6 are never read.

### Board

**Surface.** `0x00291710` reads rider+0x438, or audio+0x598C on rails (written at rail attach `0x00106848`). Jump
table `0x00482AA0` gives classes 0-8. The family (`0x002934D0`): class 0 → 0, 1-2 → 1, 3 → 2 on a rail else 0, 4-8
→ 2.

**Loops.** Three loops per rider on BOARD, started by `0x00292A50` and stopped by `0x00292B48`. Each callback
forces volume 0 in a crash, after the finish and under the pause/cutscene gate `0x00270280`.

| Loop | Function | Sound | Callback and curves |
|---|---|---|---|
| A | `0x002917D0` (human) | SPUBOARD 0 | `0x00292CB8`, ground only; curves `0x00482AF8` (volume) and `0x00482B20` (pitch) of speed. |
| B glide | `0x00291C88` | Class+4 (human, `0x00292DA0`) / class+6 (AI, `0x00292EF8`) | x = compression × (1 − (brake + turn)); curves `0x00482B78`..`0x00482C40`. |
| C carve | `0x00292508` (human) | Class+3 | `0x00293018`, brake + turn smoothed (down 50 %, up 12.5 %); curves `0x00482C68`..`0x00482D08`. |

The inputs come from ground contact `0x0013F178`: rider+0x75C speed = clamp(|v| / 3333.33, 0, 1), +0x750 brake,
+0x754 turn, +0x758 compression. The pitch curves are inaudible: the doppler bend overwrites them, and the pitch
sent stays near 0x1000 **(PS2)**.

**Take-off.** `0x00294170` is called from `0x0013F178`, `0x0012E9B8`, ollie `0x001307B8` and rail leave
`0x0013BFA8`. It plays LAND class×8+2 at volume clamp(speed × 127, 64, 127), for the human only. Then
`0x00294678` plays speech or arms the crowd anticipation (air > 2 s); `0x002947B0` retries until the predictor is in
flight.

**Landing.** `0x002948D0(rider, trickValue)` (from `0x0010E910` and get-up `0x0012D848`) plays the crowd cheer, then
LAND class×8+1 (human) or +5 (AI). Its volume is curve `0x00482D30` of the impact speed rider+0x770 (100..2000 →
10..127).

**Rails.** No grind sounds; the loops simply restart with the rail class.

### One-shots, collisions, crowd

The Uber/Tricky/monster dispatchers match the PS2 per tick **(PS2)**.

| Sound | Dispatcher (caller) | Bus |
|---|---|---|
| Boost loop 0x7A (+ 0x4A) / empty 0x6C / release | `0x00298D90` (`0x00114130`) / `0x00299368` / `0x002992D8` | 9 |
| Grab 0x77; Uber denied 0x6C; handplant 0x61 | `0x0029A530` (`0x001352A8`); `0x00299B70` (`0x00132620`); `0x0029DC48` (`0x001328B0`) | 9 |
| Points tick 0x4D; pending Uber 0x66 (stop `0x0029B3C0`) | `0x0029A7D8`, `0x0029B0E0` (score HUD `0x00117FE0`) | 9 |
| Tricky start 0x6B (after 400 ms) / end 0x69 | `0x00299638` / `0x002997B8` | 9 |
| Combo commit 0x67 (+ Arcade_Uber) | `0x0029B430` (`0x0011A228`) | 9 |
| Boost-meter fill tick 0x65, pitch +0x100 per step | `0x0029AB40` (per frame) | 9 |
| Pickups 0x70/0x71/0x74/0x75/0x76 | `0x0029CED8` (`0x0010E770`, `0x0010E7D0`, `0x0010E8B8`, `0x0030B9A0`) | 9 |
| Overtake 0x6D | `0x00299E28` (`0x0010F998`) | 9 |
| Forced reset 0x7B; animation events 0x50/0x51/0x52 | `0x0029A220` (`0x00116120`); `0x00289B18` (`0x00104CC8`) | 5 |
| Countdown 0x4E / GO 0x5E + UI 0x62 | `0x0029C420` / `0x0029C7B0` (`0x00234A30`, `0x00234BE8`) | 5 / 9 |
| Instance contact (watrig record, curve 0) | `0x00296088` (`0x00105398`) | 7 |
| Crash 0x30 + rand(3); LAND 9 on surfaces 2/3 | `0x00296310` (`0x0010EB30`, ragdoll `0x0012D4E8`) | 5 |
| Slide loops 0x33/0x34 by crash clip (curve `0x00482DA0`) | `0x00296868` / `0x00296E80` (`0x0012CD20`, `0x0012D4E8`) | 5 |
| Grunt (bank 0xE rotating 3..5 / random 0..1, or the AI bank) | `0x0029F660` (crash, pair hits; level `0x00290C40`) |
4 |
| Rider pairs 0x36 / 0x5A, obstacle 0x36 (bump = curve 1 of the summed velocities) | `0x00298488` / `0x00298138` / `0x002989A8` (via `0x00107E70`; `0x0013F488`) | 5 |
| Recovery meter 0x60 / 0x5F | `0x0029E970` / `0x0029E590` (`0x0012CB68`) | 9 |

The slide loops stop over 0.75 s (`0x00296E20` / `0x00297438`) on either exit of slide phase 2 (`0x0012D160`), on
reset, finish and pause. They end 45 ticks after the get-up **(PS2)**.

**Crowd.** Instances come from `0x002A6D78`, CROWD.INF is parsed by `0x002A7040`, and the MIDI `.eam` files play
on slot 5, bus 5. The landing cheer (`0x002A73A8`) goes by trick value (1.0 = 10000 points): < 0.25 Cheer10, <
0.65 Cheer20, else Cheer30; a race finish is always Cheer30. A fall (`0x002961F0`) gives only Ahh20 or nothing.
Anticipation is armed when air > 2 s (`0x00290FD0`). ATTACK/DECAY/MAXBEND bend the ambient crowd loops (watrig ids
41-43, `0x002A68B0`), not the `.eam`.

### World and cutscene sounds

- **watrig.adl** (`0x002B5A18`) has 92 records, each a slot + sound or a named bank for slot 3. Emitters play them
  via `0x002B7908` → `0x002B5C68` → `0x002B5D78` → `0x002B4C38` (bus 5, volume = falloff × 127, 0.25 s fade when
  out of range). Contacts play them via `0x00296088` (bus 7).
- **Stage-script sounds** (builtins 30/31/73) are `0x002974A0` one-shot, `0x00297950` loop and `0x00297EB8` stop,
  on bus 5. Ids 1-99 use Mtn.bnk, 100-149 slot 8, 150-199 slot 9, ≥ 200 TRANSPORT. Id 102 is gated on Snow Jam by
  the location word from `0x00144BC0`.
- **Location ambience** (`0x0029D290`) is bank 9 sound 0, faded over 5.03 s on a location change. The tWPIGD_Speech
  painter data exists, but no query for it is ever created.
- **Cutscene sounds** (channel-3 sounds at `0x00280F3C` inside `0x002808E8`; actor sounds at `0x0012584C` inside
  `0x00125448`) play on CHARACTER at speaker 0's gain (`0x00287968(audio, 4, 0)`), volume 127, from the cutscene
  slots **(PS2)**. The single-event start-hut intro has no CHARACTER sound: only ambience, crowd loops,
  stage-script loops and one ARCADESFX one-shot **(PS2)**.

## Menu audio

### Audio options (state `0x00195FF0`)

The state is `140audio` in the front end and `142audio_pda` in game, where the pause menu creates it (`0x001F8B3C`
inside `0x001F8948` `cOVTemplate_PauseMenu_onWidgetEvent`). The front end opens it from Setup Character → Music
(career flow, `0x001A181C` inside `0x001A16C0`) and from the lodge (`0x001A1360` inside `0x001A0830`
`cFECustom_getNextState`). It sends charsel event 4 on entry.

- `0x00196540` sets the item values: radio big 0, big mountain 2, request line 1, playlist 3, edit 4.
- Cross on a mode (`0x00196770` inside `0x001966E0` `cFEStateAudioOptions_onWidgetEvent`) moves the check sprite
  (+0x5C / +0x60), saves the mode (`0x001587F8`) and calls `0x0028BF78` at once. Triangle saves, applies again and
  leaves.
- The query `0x00196B08` returns 0x10 (error) on disabled rows. Rows 2-3 need a custom playlist (`0x001587B8` >
  0) and row 4 the career flag or a playlist; disabled rows are greyed (`0x001962A8` / `0x00196378`) and skipped.
- Help comes from table `0x00460560`. In game the state sends HUD command 3 on enter and 4 on exit, which hides Now
  Playing.

### Request Line (state `0x00196B90`)

The list `0x00197AD8` shows the 35 songs, owned first, in 8 rows. Boxes `0x00197CA0` are a checkbox for playlist
songs, empty for owned songs and a dollar sign for unowned ones. The text updaters are `0x00198118` (count),
`0x001986D0` (`cFEStateRequestLine_updateHilightedSongInfo`), `0x00197E70` (now playing, in game) and `0x00198340`
(Cross label).

- **Cross on an owned song** toggles it; the last song cannot be removed (0x10).
- **Cross on an unowned song** buys it, with the career flag only: free while fewer than 6 songs are owned, else
  $5,000 (`0x00198AE8`). The popup is `0x00198988`, and Yes → `0x001988D8` → `0x00158558` sets the owned and
  playlist bits.
- **Square** (at `0x00197910` inside `0x001977D0`) previews. In the FE, `0x002B4978` sends PREVIEW to charsel; in
  game, for owned songs, it sets audio+0x508 = song and calls PlayMusic(0, 0, -1, 1).
- **Triangle** (`0x0019768C` inside `0x00197500`) saves both masks (`0x00158848` / `0x00158820`) and calls
  `0x0028C2D0`. With the career flag it also sends charsel event 10 (`0x001976E0`).

### Sound Options (`0x0018A258`, widgets `0x0018B380`)

| Row | Widget | Options bits | Setter |
|---|---|---|---|
| Sound Mode (Stereo/Surround/Mono/DTS) | List | 12-13 | `0x00289DC0` |
| Music/MC, SFX, Character speech | Sliders | 0-3, 8-11, not given | `0x00287410`, `0x00287488`, `0x00287520` |
| DJ Speech / Arcade SFX (Off/On) | Lists | 17 / not given | `0x00287558` / `0x002875D0` |
| EA SPORTS BIG Talk | List | 18 | Online only |

Sliders have 12 steps (+0x78 = 12, values 0..11), with the knob at track.x + value × (trackW − knobW) / 11
(`0x0039E130`). Changes apply at once, and Square opens the reset popup. In game these are rows of the in-game
options screen (`0x001F8DF8`).

### Now Playing popup

The popup is drawn by `0x001E9A30`, `0x002204A0`, `0x001EABB0` (inside `0x001EA930`) and `0x001EC2E0` (inside
`0x001EC1F0`), triggered by HUD command 5 from `0x0028F478` when MUSIC is audible. The header "EA RADIO BIG" is
hard-coded (not localised) in HUDFONT × 0.8; the title is wrapped at 300 px in FEFONT × 0.6, followed by artist and
album, in a three-slice box at (20, 460 − H). The timeline runs in 1/60 s steps and freezes in pause: slide in
0-0.4 s, text fade-in to 0.8 s, hold to 7.2 s, fade-out to 7.6 s, slide out to 8.0 s. The same title is ignored
while showing, and a new title restarts it. Layout and timeline match PS2 snapshots **(PS2)**.

### UI sounds

A widget reports a kind with `listener->vfunc+0x14(kind)`, the listener being screen+0x5C → +0xD0 → +0x10 (UI context,
`0x0039FF50`) → +0x14. A null listener uses the silent object `0x004A5A58` (built by a static initialiser at
`0x003A426C` inside `0x003A3F48`), and kind 0 or > 6 is silent. The FE listener "FEUISound" is `0x001A2E58` (vtable
`0x00469348`). The overlay listener `0x001A2F70` (vtable `0x00469318`, created in `0x0022E968`) serves pause, results,
pre-race, replay, map and lodge. Both call `0x00294F78(audio, ev)` with table `0x00482D60`; `0x00294F48` plays sound
0.

| Kind | FE ev | Overlay ev | Bank-0 sound |
|---|---|---|---|
| 1 move | 2 | 11 | 2 |
| 2 scroll | 3 | 12 | 1 |
| 3 back | 1 | 10 | 4 |
| 4 error | 4 | 13 | 0xD |
| 5, 6 accept | 0 | 9 | 3 |

**Direct events.** Ev 7 / 8 (sounds 0x10 / 0x11) are online notifications (`0x001A8B88`). Ev 14 (0x12) plays when
a results, pre-race or top-times panel appears. Ev 15 (sound 7) is the FE transition page (`0x001946E4` inside
`0x001946A8`), and ev 9 is the map opening (`0x0028F60C` inside `0x0028F5B8`). Opening the pause menu plays sound 0
right after `0x00289B70`, at `0x00230AFC` (inside `0x002306B8`) and `0x00244DF0` (inside `0x00244B48`).

**Engine:**

- The base constructor `0x0039FB30` sets kind[0] (+0x6C) = 4 and kind[1] (+0x70) = 6. The only override is the
  title's "Press START": `0x001949C0` (inside `0x00194988`) calls `0x003A0330` to set kind[0] = 0.
- The default handler (vtable `0x004946C8`) answers queries with 0x101: bit 0x100 = animation, 0x1 = kind[1], 0x10
  = kind[0].
- UIMenu `0x0039B000` (vtable `0x00494928`) plays kind 1 on a move (`0x0039B17C`, `0x0039B274`) and kind[0] on a
  blocked move (`0x0039B5E4`). Cross/Triangle/Circle/Square notify 5/6/8/7, then query 6/7/9/8. By default Cross
  and Triangle both play sound 3, so the engine never plays "back". The silent bit's setter `0x003A5390` is
  unreferenced.
- UIPair is `0x0039BED8` (vtable `0x00494868`). The list box `0x00399970` (vtable `0x00494798`) plays kind 1 and wraps
  when +0x14 bit 7 is set (set at `0x00399904` inside `0x00399820`). The slider `0x0039DFE8` (vtable `0x00494348`)
  plays kind 1 and is silent at the ends.

**State overrides.** Cross is silent in the sound/HUD/controller options (`0x0018A890`, `0x0018C270`, `0x0018CCE0`)
and in the pause query `0x001F8908`; the pause item handler plays ev 9, or ev 13 when greyed (`0x001F8998` inside
`0x001F8948` `cOVTemplate_PauseMenu_onWidgetEvent`). Audio
options `0x00196B08`, Request Line `0x001977D0` and Peak Room `0x001D3E08` return 0x10 for disallowed items, and
replay `0x0020DF10` is silent throughout. State code plays the other kinds directly:

- Kind 3 (back) only in the reward galleries (`0x001CF28C` inside `0x001CF270`), reward preview (`0x001D2028`
  inside `0x001D1FF0`) and mountain-room help (`0x001D2EF0` inside `0x001D2EA0`).
- 4 on cash checks (`0x00185528` inside `0x00185268`; `0x001F4B40` inside `0x001F4A90`); 1/4 in the attribute
  shop (`0x001F4D0C`, `0x001F4E18`, `0x001F4E4C`, all inside `0x001F4C30`); 2/4 when scrolling career stats
  (`0x001F59EC` inside `0x001F56C8` `cFEStateCareerStats_onInputBegin`).
- 6/4 in event select (`0x002018A8`); 1/5/6 in the keyboard popup (`0x001CE254` inside `0x001CDB98`); 2/6 in the
  replay menu (`0x0020DF58` inside `0x0020DF38`); 2/4 in the replay transport (`0x0026FBA0` inside `0x0026FB88`).

Loading screens are silent.

## EE side of the driver and streaming

- **Voice handlers.** The IOP-mixed voice types have open/read/close handlers in `0x003C92F8`..`0x003C9DA0`. The
  MicroTalk stream voice is `0x003C9960` / `0x003C96F0` / `0x003C9938`. The SND bank voice opens at `0x003C9420`
  and restarts loops at `0x003C9520`.
- **Block descriptors.** For each SCDl block `0x003B6EA8` builds a descriptor: the sample count with bit 31 = "not
  the first block of this SCHl", and the channel pointer. The SCHl handler `0x003B6BD0` clears bit 31. The
  ring-buffer fetch `0x003C6DE0` (with `0x003C7010`) hands out pointer, count and bit 31.
- **MicroTalk music.** Only "Screw Up" streams in codec 4 (32000 Hz stereo). The read handler skips the first byte
  of each channel's block. With bit 31 clear, `0x003CE0B8` makes `0x003CD6F0` parse the 15-bit header and reset the
  decoder. With bit 31 set, only the bit reader restarts, so the state carries across one SCHl's blocks (never
  across SCHl streams). Tag 0x80 < 3 selects plain MicroTalk (`0x003CE0D8(ctx, 0)`): no flag bytes, patches or
  re-alignment (`0x003CDF34` inside `0x003CDE68`). Both stream voices run in plain mode, with ctx+0xD5C 0 mid-bar
  and 1 at a first block **(PS2)**.
- **IOP side, in words.** SNDDRV.IRX decodes EA-XA ("decxa16c", coefficient pairs (0,0), (240,0), (460,−208),
  (392,−220)); the EE has no EA-XA table. Its XA filter keeps history across chunks (cleared only at init) and
  addresses frames as base + pos × 15/28, so the EE hands it frames without the 4-byte channel prefix. It unpacks
  PCM8, has no MicroTalk decoder, and plays PS-ADPCM on SPU2 hardware voices.

## Audio file formats read by the EE code

**Containers.** MUSIC.BIG / MUSIC2.BIG hold, per song, an `.mpf`, the stream `.mus` and the loop bank
`*loops0.mus`. ENGLISH.BIG has 29 DJ/PA `.dat` banks plus `langhead.big`, and SPEECH.BIG has 294 character banks
plus `headers.big`. AUDIO.BIG has 131 BNKl banks and 9 crowd `.eam` MIDI files (magic `MIDx`, not decoded).
`GRNT_*.BNK` are the grunts. DATA/CONFIG holds MUSIC, PLAYLIST, MIX (3 presets), BANKS, CROWD and SPEECH `.INF`.
The speech path strings are `%sheaders.big` `0x004832D8` and `%slanghead.big` `0x004832E8` (`0x002B0088`),
`%s%s%s.dat` `0x004832F8` (`0x002B04D8`) and `%s.hdr` `0x004A37C0` (`0x002AF960`, which creates a SpeechBank).

**BIGF.** `'BIGF'`, u32 LE size, u32 BE count, u32 BE header size, then {u32 BE offset, u32 BE size, name\0}
entries, offsets from the archive start.

**PT header.** "PT", u8 platform (5), 0, then tags (iterator `0x003C7388`, BE reader `0x003C72F8`). Control bytes
are 0xFC pad, 0xFF end, 0xFD sample data, 0xFE next patch; anything else is tag, u8 len (0xFF = u32 BE len), BE
value. Tags < 0x80 are patch parameters. The sample tags take their defaults from `0x003BB820` (streams) and
`0x003BAAC0` (banks):

| Tag | Meaning (default) |
|---|---|
| 0x80 | Version: 2 streams/loop banks, 3 SFX banks |
| 0x82 | Channels (1) |
| 0x84 | Rate (22050, set at `0x003BB930` / `0x003BABC0`) |
| 0x85 | Samples per channel |
| 0x86 / 0x87 | Inclusive loop (-1) |
| 0x88 / 0x89 | Bank channel offsets |
| 0xA0 | Codec: 4 MicroTalk, 5 PS-ADPCM (default), 9 PCM8, 10 EA-XA |

`0x003BBDA0` (from `0x003B6300`, `0x003B6788`) defaults to 48000 Hz and codec 10. Speech streams carry no 0x84 and
play at 22050 Hz.

**SCxl.** Little-endian chunks {fourcc, u32 size}: `SCHl` (PT header), `SCCl` (count), `SCDl` (u32 samples,
per-channel offsets from the end of the table, then per channel a 4-byte prefix and 15-byte EA-XA frames of 28
samples; the prefix is close to the previous chunk's last two samples, probably encoder source PCM (unconfirmed), and
the decoder does not use it), `SCEl` (end, `0x003B76E8`). The docs also cite `0x003B7080` for the SCHl dispatch.
`.mus` streams start on 0x80-byte boundaries.

**Codecs.**

- EA-XA (IOP): the frame header's high nibble picks the coefficient pair (c1, c2) and its low nibble lo is the shift
  − 8; s = ((nibble << 28) >> (lo + 8)) + h1·c1 + h2·c2, then s >>= 8, with no rounding and no clamp in the history.
- PS-ADPCM: standard SPU frames.
- PCM8: signed, 16-byte header {00 09 00 00, loop start, loop end, count}.
- MicroTalk (EE, 432-sample frames):
  - `0x003CD1F8` / `0x003CD260` bit reader (LSB first).
  - `0x003CD6F0` header: bandwidth bit, threshold, 64 gains g[i] = g[i−1] × (1.04 + 0.001·read(6)).
  - `0x003CD878` frame: 12 reflection coefficients from `0x0044E8E8`, four 108-sample subframes.
  - `0x003CD2B0` excitation (Huffman `0x0044E9E8`, commands `0x0044EBE8`); `0x003CD518` interpolation;
    `0x003CD590` reflection → LPC; `0x003CE410` 12-tap synthesis.
  - `0x003CDDE8` / `0x003CDE68` EA wrapper for bank voices: a flag byte per frame, where 0xEE means a BE PCM patch
    follows.
  - Pitch gain is v × 1/15. A first-subframe pitch lag above 216 reads 39 floats of context. An overrunning patch is
    written unbounded over the context. Looped sounds store the loop body as a second stream at dataOffset + patch
    param 0x1A (channel 0) or 0x26 (channel 1) (observed in the data, not traced).

**BNKl v5.** `'BNKl'`, u8 version 5, u8 flags, u16 count, u32 header size (= sample data start), u32 SPU size, u32
main-RAM size, then u32 × count offsets of each entry's PT header relative to the slot (0 = empty). An entry holds
0xFE-separated patches (random/velocity layers); `0x003BAAC0` returns at each 0xFE. Patches can share data.

**Speech `.hdr`** (parser `0x003D69F0`). A `.dat` is a plain run of SCxl streams, one per line.

```
+0 u16 id  +2 u16 0xFFFF  +4 u8 key count F (bits 0-3), bit 7 = "played" bitmap follows
+5 u8 lines N  +6 u8 history H  +7 u8 alignment mask M  +8 u32 .dat size / 256
+12 N x {u16 BE offset in units of 256*(M+1), F key bytes}, pad to 4, F x u32 key masks,
    u8 history cursor, H recent line numbers
```

The logic notes read the size and offsets in 512-byte units with a "?"; that matches only for M = 1, so it is
unresolved. The disc has 9806 lines (8399 mono, 1407 stereo DJ), all EA-XA at 22050 Hz.

**Events.evt** holds 59 events (count at +0x10, u16 offsets × 4 at +0x18). An event is u16 id, u16 W (max wait),
u16 P (priority), chance % at +9 and record count at +0xE, then conditions (argument index + mask) and u32 bank ids
(= `.hdr` ids).

**Pathfinder `.mpf` v4.** Magic "PFDx" (`78 44 46 50`) and version 4, checked by the loader `0x003D2350` at
`0x003D240C` / `0x003D2420`; the table pointers are built at `0x003D2474`..`0x003D256C`. Offsets are × 4. The header
has tracks +0x0D, sections +0x0E, events +0x0F, routers +0x10, vars +0x11 (always 0) and u16 nodes +0x12. From
+0x20 follow the node offsets, node data, event offsets and data, routers R[k], tracks T[t] and the 8-byte sample
table.

| Node field | Meaning |
|---|---|
| +0 s16 | 1-based sample (read in `0x003D43B0` / `0x003D4400`); 0 head, -1 end, -2 random, -3 post event |
| +2 u16 | Bits 0-4 track, 5-10 section (`0x003D4B00`), 12-15 end-node loop count |
| +4 u32 | Bits 0-7 router, 12-16 branch count, 17-19 == 1 random value, 20-23 measures, 24-27 beats per measure (`0x003D4460` derives ms per bar and per beat) |
| +8 u32 | Bits 0-7 0x40 on audio nodes, 8-9 head sync mode (0x100 only), 10-14 head event (unused), 20-31 part-head index or part id (`0x003D4388`) |
| +12 u32 | Bit 1 = sliced |
| +16 | Branches {s8 lo, s8 hi, u16 target (0xFFFF = stop)} |

The field reads cited in the table (`0x003D43B0`, `0x003D4400`, `0x003D4460`, `0x003D4388`) are all locations inside
`0x003D41A8`.

- A sample-table entry is {u32 value, u32 duration_ms}. value × 0x80 is a `.mus` byte offset, or the first bank
  entry of four 1-beat slices or of one long ending. duration_ms = floor(samples × 1000 / rate).
- An event is a 16-byte head (+0xC: bits 16-21 action count, 22-27 runtime index, 29 disabled) followed by 16-byte
  actions (bytes 0-2 track mask, +4 timeout, byte 9 opcode, +0xC operand).
- Example: "Go" (135 BPM) has 541 nodes, 479 samples (465 stream bars of 1777 ms, 14 loop phrases), 48 events and 5
  sections. Across songs: 18-651 nodes, 1-48 events, 38 songs with a loop bank.
- Song streams are 32000 Hz stereo EA-XA. charsel and mapsel are mostly 6-channel (probably three stereo stems,
  unconfirmed; how the game mixes them is not known). Peak*Amb streams are 44100 Hz; loop banks are EA-XA at 22050 Hz.

