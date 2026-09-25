# World, peaks and streaming

SSX 3's mountain is one connected world made of locations: 17 event courses, five stations (hubs), short
connector sections between them, the transport location TRANSP and one sky per mountain area. An event keeps a
fixed set of locations resident, called its residency row. Free ride and the peak runs stream locations in and
out while the rider moves. Trigger volumes in the connectors drive this streaming. This note covers the
location, course and residency tables, the streaming state machine, and what happens when a location finishes
loading or starts unloading (collision, drawing, section activation, path banks, painters, stage scripts). It also
covers the region placement used for arrivals and session points, how the game moves the rider around the
mountain, and the stage builtin that teleports a rider.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a
PS2 emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

Source files are the decomp's current splits, as reported by the address lookup.

- `src/main/game.cpp`: the streaming requests and per-tick pass: `0x0022CEA8` (unload request), `0x0022D088`
  (load request), `0x0022D8D8` (per-tick streamer pass), `0x0022DE58` / `0x0022DE98` (sky activation and dome
  swap), `0x0022DF50` (current-course update), `0x0022D278` (resident check; role inferred from its use),
  `0x0022D6C8` (the RaceRideState gate) and `0x0022E0E0` (track to location id).
- `src/main/sectionman.cpp`: `0x0022E180` (`cSectionMan_setSky`). The notes describe it as the function that sets the
  default rider irradiance bank by course.
- `src/main/gameload.cpp`: `0x00230338` (section rescan request), `0x00230360` (location unload start), `0x002306B8`
  (a wait for location data).
- `src/world/worldview.cpp`: `0x003A9858` (`cWorldView_isSectionLoaded__FP10cWorldViewi`) and `0x003AB498` (the
  eviction path).
- `src/intersect/aifwddiff.cpp`: `0x00328C20` (instances go into the activation octree when a read completes) and
  `0x003284B8` (they are removed at eviction).
- `asm/1218.s` (unsplit): the section activation `0x00101B60` and its location drop `0x00103308`.
- `src/ai/ai.cpp`: path bank delivery `0x0012A340` and drop `0x0012A490`. `src/ai/computer.cpp`: route re-attach
  `0x00112180` and finish eligibility `0x0010E5D8`. `src/path/pathsys.cpp`: region row lookup `0x0026B5E0`.
- `src/ai/rider.cpp`: region placement `0x0011DE60`, placement at a point `0x0011D660`, reset velocity `0x0011DF18`,
  location arrival `0x0011D390`, teleport `0x00123210` and its sibling `0x001234D0`, trigger contact `0x00121818`,
  per-rider location update `0x001218D0`, query scope rebuild `0x00120E50`.
- `src/main/gamestate.cpp`: world states used by stations and transports (`0x00236058`, `0x00236250`,
  `0x00236418`, `0x00236960`, `0x00235080`). `src/main/gamemode.cpp`: the game-mode handlers, chosen by `0x00238160`
  (`cGameModeMan_initGameMode`).
- `asm/1FBE38.s` (unsplit): stage builtins 68 `0x00302210`, 67 `0x00302048`, 34 `0x00300770` and 40 `0x003012F0`.
- `src/wscript/wscriptman.cpp`: slot-2 contact dispatch `0x0030A060`, collectible slot `0x0030B928`.
  `src/wscript/wscriptprocess.cpp`: per-stage mission build `0x00308C60`, stage teardown `0x00308FE0`, mission tick
  `0x00309270`.
- `src/be/beintplayer.cpp`: peak locks `0x00145F90` (`cBENewPlayerInterface_isPeakLocked`). `src/be/beintnewrace.cpp`:
  map id to course `0x00144CE0`, peak rival `0x00145750`.

The notes do not describe the named functions in `src/world/streamman.cpp`, `src/world/worldcache.cpp` or
`src/world/wscriptcache.cpp`.

## The mountain

### Location codes, areas and peaks

- A location code gives the event type and mountain area. Event codes are `?RA` race, `?SS` slope style, `?BA` big
  air, `?HP` super pipe and `?BC` backcountry. The first letter is the area.
- Peak 1 covers areas A and B, Peak 2 covers C and D, and Peak 3 is area E.
- The stations are the bare area letters: A Green Base Station, B Blue Base Station, C Yellow Mid Station, D Red Mid
  Station, E Black Top Station.
- A connector is named after the two locations it joins, uphill one first: `A_ARA1` runs from station A into ARA1,
  and `ARA1_B` runs from ARA1 into B.
- Each area has one sky (ASKY .. ESKY). A location uses the sky of its area letter, and every residency row agrees.

**Connectivity** (top to bottom). The main line is:

```
E -> E_ERA5 -> ERA5 -> ERA5_C -> C -> C_CRA3 -> CRA3 -> CRA3_D -> D -> D_DRA4 -> DRA4 -> DRA4_A -> A
  -> A_ARA1 -> ARA1 -> ARA1_B -> B -> B_BRA2 -> BRA2
```

- **Spurs from the stations.** E has E_ESS3, E_EBA3 and E_EHP3. C has C_CHP2 and C_CBA2. D has D_DSS2. A has A_ASS1
  and A_ABA1. B has B_BHP1.
- **Backcountries.** Each backcountry ends at a station of its peak: EBC3 -> EBC3_E -> E, DBC2 -> DBC2_D -> D and
  ABC1 -> ABC1_A -> A.
- **Links between peaks.** ERA5_C is the only way from Peak 3 down to the rest of the mountain. DRA4_A leads from
  Peak 2 into Peak 1's station A.

### Location table `0x0043E250`

- **Rows.** 24-byte rows `{id, name[16], kind}`.
- **Kinds.** 0 event course, 1 peak hub (station), 2 connector, 3 TRANSP, 4 sky.
- **Ids.** 0..16 are the courses and 17..21 the stations, and for these the location id equals the course index.
  22..42 are connectors (for example EBC3_E 22, ERA5_C 27, DRA4_A 35, A_ARA1 37, B_BHP1 42). TRANSP is 43, then the
  skies (ASKY 44, BSKY 45, ESKY 48).
- **Example rows.** `{0, "ARA1", 0}` and `{43, "TRANSP", 3}`.
- **Course index order.** The indices group courses by event type, in peak order within each group:

| Indices | Event type |
|---|---|
| 0..4 | races ARA1, BRA2, CRA3, DRA4, ERA5 |
| 5..7 | slope style |
| 8..10 | big air |
| 11..13 | super pipe |
| 14..16 | backcountry ABC1, DBC2, EBC3 |
| 17..21 | stations A..E |

### Course table `0x0043D950`

The rows are 0x64 bytes. The fields at `+0x00`..`+0x44` come from the listed field sizes.

| Offset | Field |
|---|---|
| `+0x00` | index |
| `+0x04` | name[32] ("Snow Jam") |
| `+0x24` | short name[16] (row 12, The Junction, has "Disfunk") |
| `+0x34` | code[16] ("ARA1") |
| `+0x44` | world[16] ("BAM" for every course) |
| `+0x54` | career peak: 1 for Peak 2 and 2 for Peak 3, so presumably 0 for Peak 1 |
| `+0x5C` | map id. This is not the course index: ARA1 0, BRA2 1, ASS1 6, ABA1 9, BHP1 12, ABC1 15, A 18, B 19. `0x00144CE0` maps a map id back to a course |
| `+0x60` | map region (2 for every Peak 3 course) |

Course help texts use the keys `kT_HELP<code>`, and `CMNAMER.LOC` holds course descriptions.

### SDB tracks and resource ids

- **Resource ids.** A world resource id is `(rid << 8) | track`. The patch field `+0x150` holds this word, and
  `resource & 0xFF` is the track.
- **Track numbers.** They do not match location ids. Examples: A 1, ARA1 8, BRA2 16, C 18, CRA3 24, DRA4_A 33, E 36,
  ESKY 47, ESS3 48.
- **Numbering pattern (unconfirmed).** The listed values fit a numbering of the location codes in case-insensitive
  alphabetical order starting at 1. This is only an observation from the values.
- **Track to location.** A streaming-table row stores its track at `+4`. `0x0022E0E0` uses that field to turn a track
  back into a location id.

### Residency table `0x00442488`

- **Rows.** 23 rows of 40 bytes, one per course index: `{course, count, sky, TRANSP, up to 6 location ids}`.
- **Example rows.**
  - Row 0 (Snow Jam): 3 locations, ARA1, A_ARA1 and ARA1_B, with ASKY.
  - Row 17 (Green Base Station): 6 locations, A, A_ARA1, A_ASS1, A_ABA1, DRA4_A and ABC1_A, with ASKY.
- **Course rows** hold the course and every connector that touches it. For a race above Metro-City this includes the
  exit connector toward the next station (ARA1_B, CRA3_D, DRA4_A, ERA5_C).
- **Station rows** hold the station and every connector that touches it. For example, row 19 (C) includes ERA5_C.
- **Events (PS2).** An event keeps exactly its row resident, plus TRANSP and the sky, all in state 2 of the streaming
  table. This was checked in the event savestates of all three peaks.

### Streaming table `0x00442168`

- **Rows.** 50 rows of `{id, track, state, class}`. Rows 0..48 are the locations by id.
- **Classes.** 0 location, 1 TRANSP, 2 sky.
- **Streamer object.** The streamer is at `W+0x78`, where `W = *(*(0x004A28A8)+0x84)` (`0x004A28A8` is gp-0x848).
- **Lookup.** `0x0022E0E0` returns 50 when no row holds the track.

### Other tables the world code reads

| Table | Content |
|---|---|
| `0x00445E40` | Entry mode by builtin-68 key2: `{2,3,4,5,1,1,1,0}` |
| `0x0047B4E0` | Jump table of `0x0022E180`: the default irradiance bank by course (APBR1 for 0, 5, 8, 14, 17; BPBR1 for 1, 11, 18; EPBR1 for 4, 7, 10, 13, 16, 21) |
| `0x00440770` | Session points per course (count at `+0x18`, read by `0x001545F8`). Race, slope-style and backcountry courses have 5..8 points, big air and pipe courses 2, stations 1 |
| `0x0043FA70` | Collectible count per course (read through `0x00153350`). Snow Jam 30, Happiness 44, each station 5. The counts equal the stages' builtin-38 lists |
| `0x00478D38` | Free-ride Transport list, in order per peak. Peak 1: Happiness, Green Station, R&B, Snow Jam, Crow's Nest, Blue Station, Metro-City, The Junction |
| `0x0045AAD8` | Career goal lists per peak (the CTM Transport order). This can differ from the Single Event order, which follows the Map LUI rows |
| `0x00440D18` | Peak-run tiers, split times and cash (see "Peak runs") |
| `0x0043EE10` | Big Challenge table (see "Big Challenge missions") |

## The streaming state machine

Row states (streaming table `state`):

| State | Meaning |
|---|---|
| 0 | absent |
| 3 | load wanted |
| 4 | load wanted, activate on arrival |
| 6 | reading |
| 8 | reading, then activate |
| 1 | Resident, inactive. In the octree, but patch runtime flag 0x40 is clear, so the patch is neither collidable (collision wants 0x41) nor drawn |
| 2 | Resident, active. Collidable and drawn (track state 6) |
| 5 | unload wanted |
| 7 | Unloading. No longer drawn, but still collidable until its chunk slot is evicted |

A patch's runtime flag word at `patch+0xA` is its authored flags OR 0x40.

### Requests

- **Unload request `0x0022CEA8(destination, mode)`.** Called from a connector's Unload trigger (builtin 68 action 0)
  and by the in-world transport, which passes 7 as the second argument.
  - Rows of locations outside the destination's residency row: 1, 2 and 6 go to 5, and 3 goes to 0. Rows in 4 or 8
    are kept. Skies and TRANSP are never released.
  - Rows the destination wants: 0 and 7 go to 3, and 5 goes to 1.
- **Load request `0x0022D088(destination, mode)`.** Called from the Load trigger (action 2), the initial load and the
  transport arrival.
  - Wanted rows: 0, 3 and 7 go to 4, and 6 goes to 8. Rows in 1 or 5 go straight to 2 in the same tick.
  - It also calls `0x0022E180`, which sets the default rider irradiance bank (`0x004A43C4`, gp+0x12D4) by course
    through the jump table `0x0047B4E0`.

### Per-tick pass `0x0022D8D8`

The streamer makes one pass at the start of every game tick, in this order:

1. **Unloads.** 5 goes to 7. 7 goes to 0 at the eviction, 7 passes later. While any row is still in 5 or 7, no new
   load starts in that pass.
2. **Wanted rows.** 3 goes to 6 and 4 goes to 8.
3. **Reads.** From the next pass, one disc read runs at a time. Rows are ordered by slot priority (sky 0.92, TRANSP
   0.91, location 0.90), then by the lowest chunk index.
4. **Read completion.** The resolver delivers the location's records: path bank, instances, stage. On the following
   pass the row goes from 6 to 1 or from 8 to 2, and the next read starts.

Two more steps belong to the pass:

- **Skies.** A sky that reaches state 1 is activated at once (`0x0022DE58`). It replaces the dome (`0x0022DE98`) only
  when the switch is allowed. A flag at `+0x1A4` allows it, and builtin 68 action 5 (the `skybox_trigger` volumes)
  sets that flag.
- **Current course.** The current course `0x00535C08` changes on the first pass after a request (`0x0022DF50`).

**Waits.** The in-world transport's loading loop (screen 11 with flag `+0x1C8`) is `0x00236960`, which waits for
`0x0022D278` to report the requested rows resident. `0x002306B8` in gameload is a separate wait (flag `+0x1D0`) for
location data that is not yet present. The notes do not detail it.

### Timing (PS2)

These timings were measured on free-ride crossings of Peak 1.

- The old locations stop drawing on the pass after the Unload trigger. They leave the octree 8 passes after it, and
  the new reads start 9 passes after it.
- **Read times** are for the location's main chunk (its last SDB chunk). They are deterministic for the same history,
  but vary with the texture sub-chunk reads in flight. Examples: hub A 75 ticks, hub B 57, connectors 21..36, BSKY 30,
  ARA1 238..250.
- The time seems to scale with the size of the last chunk. The value used to estimate unmeasured locations, about
  20.5 KB per tick, is not confirmed.
- **Example crossing A -> A_ARA1 -> ARA1**, with the Unload trigger at tick T:
  - At T, A, DRA4_A, ABC1_A, A_ASS1 and A_ABA1 leave state 2 and reach 7 by the next sampled record. ARA1 and ARA1_B go
    from 0 to 3. A_ARA1 is in both rows and stays.
  - The eviction is at T+7 or T+8 (two runs).
  - The ARA1 path bank arrives at about T+244..T+259, and ARA1's row goes from 6 to 1 a few ticks after the bank.
  - The Load trigger follows about 620..665 ticks after the Unload trigger on the measured runs. The reads had
    finished long before, so the ride never waited.

## Read completion and unload

### Section activation and the octree

- **One octree.** The section activation `0x00101B60` keeps one activation octree for every resident location. It
  covers the instances that carry a slot-1 or slot-3 stage program.
- **Read completion.**
  - A location's instances enter the octree when its read completes (resolver kind 3, `0x00328C20`). The row is still
    in 6 or 8 at that point.
  - At the transition from 6 to 1 or 8 to 2, `0x003A9858` (`cWorldView_isSectionLoaded__FP10cWorldViewi`) calls
    `0x00230338`, according to the notes. `0x00230338` sets the activation object's `+0xD0` to -1, so the next pass
    rescans.
- **Unload start.** When the row goes from 5 to 7, the game calls `0x00230360`. It runs `0x00103308`, which drops the
  location's instances from the activation list without running their leave handlers. It also tears down the
  location's stage programs and entities.
- **Eviction.** `0x003AB498` calls `0x003284B8`, which takes the instances out of the octree. A later read brings them
  back without entities and with their authored flags.
- **Section programs.** In free ride, the slot-1 programs are what disable challenge reset planes, mode fences and
  start-mode colliders.
  - Example: `mdl_A_challenge_reset_plane_s_1020` runs builtin 43 with argument 6. The current kind is 4, so the program
    calls builtin 2 and the node becomes a DeadNode.
  - If the plane were left alive, touching it would run builtin 27 effect 5 ("Wrong Way!") and a reset, `0x00116120`
    reason 4.
- **Entities.** The section activation creates entities when their section is entered, and the unload or eviction
  tears them down.

### Path banks

- **Bank replacement.** When a location with id below 22 (a course or a station) finishes its read, `0x0012A340`
  replaces the race/reset path bank at `0x004D33A0`.
- **Station variants.** Stations carry more than one variant: 1 in a time challenge, 2 in a points challenge (1 in
  mode 11). Every other location and mode uses variant 0.

- **Route re-attach.** `0x00112180` then re-attaches the human to the region row's paths through
  `0x0026B5E0(bank, 1, player 0)`, which selects the grid-slot row.
  - The row's `+0x20` is the reset (AI) path and `+0x24` the race path.
  - The rider's `+0x4D0` and `+0x4D4` are both set to remaining-at-origin minus the `0x0026A638` distance, or to
    remaining-at-origin itself when that is smaller.
- **Bank drop.** The old bank is dropped when its location is evicted (`0x0012A490`). Until the next read there is no
  bank, and neither the race progress nor the route moves.
- **Delivery timing (PS2).** The path record (AIP) is delivered before the row leaves state 6 when the chunk still has
  more to read.
- **Bank contents (PS2).** Checked against Snow Jam and Metro-City savestates.
  - The race path bank equals the course's AIP record (world record kind 14, rid 0) byte for byte. The loader renumbers
    event types 0 to 1 (finish) and 18 to 11 (checkpoint).
  - The reset bank is the AIP AI paths, with the types renumbered -1 to 0, 100 to 12, 102 to 14, 103 to 15, 110 to 16,
    111 to 17 and 300 to 20.
  - The AIP region table's kind-0 rows are the start grid, and slot 0 is the human.

### Painters, lighting and sky

- **Painter records.** Each location has one painter record (world record kind 15). Its sections are typed: Fog 5,
  glare 6, ScreenTint 7, Sun 9, Lighting 11, breath/weather 12.
  - Glare appears only on some locations (for example BRA2, BHP1, ABC1, E, ERA5).
  - EBC3 and E_ERA5 have no Mix/Ambience sections. ERA5_C has two Lighting payloads (the C bank and the E bank). ESKY's
    record is empty.
- **Painter region.** The painter region is the track of the rider's last contacted patch. When the region changes,
  every section's tree is swapped and its blend state is kept.
- **Empty Lighting reference.** The painter reset (at `0x002BE1F8`, inside `0x002BE198`) reads the default irradiance
  bank set by `0x0022E180`.
- **Light glows.** Light-glow sources are world record kind 7, stored per location. Peak 1's stations have none.
- **Sky switch.** Only specific volumes switch the sky dome. `mdl_ERA5_C_skybox_trigger_1000` (ESKY to CSKY) is the
  only skybox trigger on Peak 3.

### Stage programs and collectibles

- **Stage programs.** A location's stage (world record kind 16, the LUN programs) is built when its read completes
  and torn down at its unload start.
  - Stage programs start 16-byte aligned after the offset table.
  - The last program may be followed by zero padding.
- **Collectible slot.** Builtins 37, 38 and 39 handle collectibles through one slot, `ctx+0x2C0`, where
  `ctx = *(0x004A3DD8)` (gp+0xCE8).
  - When a location's read completes, its global handler programs rerun and `0x0030B928` opens the slot, but only if it
    is free.
  - The slot is freed at the location's unload start (`0x00230360` calls `0x00308FE0`).
  - At a run start, the first resident stage in load order takes the slot.
- **Career row.** The collectible career row is the location's course: the profile record at
  `(setKey + *0x005305F0) × 12`.
- **CTM flag.** `0x00535C11` is 0 on the Conquer the Mountain path (free ride and peak runs) and 1 in, for example, the
  Metro-City single event. It only affects builtin-38 collectibles.
- **Award per collectible.** `0x00151178(peak)` pays $500, $1,000 and $2,000 on Peaks 1, 2 and 3 (PS2 for Peak 3).

### Big Challenge missions

The WScript mission system is driven by each stage's own mission records. Peak 1 has 40 missions and Peak 3 has 21.

**Data.**

- The stage's `+0x20`/`+0x24` hold 0x54-byte mission records:

| Offset | Field |
|---|---|
| `+0x0` | challenge id |
| `+0x4` / `+0x8` | steps |
| `+0xC` / `+0x10` / `+0x14` | start, tick and stop programs |
| after `+0x14` | ten event programs |
| `+0x40`..`+0x4C` | four callbacks (`+0x44` complete, `+0x48` fail, `+0x4C` status/visual) |
| `+0x50` | misc |

- The stage's `+0x30`/`+0x34` hold 0x38-byte steps (tasks), with start, tick, end and event kinds 0..9.
- A program word is `program << 8 | track`.
- The table `0x0043EE10` has 88 rows of 0x24 bytes. Each row holds the id, the title, objective and description LOC
  hashes, the course, cash, flags (`+0x18`, s16, the peak), the next challenge and the music type at `+0x22`.

**Objects and lifecycle.**

- `WScriptMission` has vtable `0x00489A30` and derives from `WScriptProcess` (`0x00489B70`). Tasks use vtable
  `0x00489AE0`.
- `0x00308C60` builds one mission per record of every loaded stage. It runs at the world start and at each exit from
  world state 10, which is two ticks after a Load trigger.
- `0x00308FE0` drops a stage's missions at its unload start. A stage loaded later, such as after a transport arrival,
  gets its own missions.
- The context keeps two lists, inactive at `+0x2B4` and active at `+0x2B8`. New entries are pushed to the front, and
  the next pointer is at `+0x18`.
- Each run gets a fresh 8-bucket LUN table (`m+0x1C`) as the programs' globals.

**Tick `0x00309270`.** It runs in the entity pass, after the rider pass of the previous tick:

1. The pending operation (`0x00309118`).
2. The HUD words are zeroed.
3. Queued events at `+0x40` are dispatched to the mission's event programs and the current task's. Kind 0 is a
   `0x0030A060` contact.
4. For each active mission: state 1 goes to 2, then the current task ticks, then the mission tick program runs.

**Builtin 40** (`0x003012F0`, which calls `0x0030A868`) takes operations 0..19: 0, 1, 2 and 18 stop, start, next task
and quiet stop; 3 restart; 4 success; 5 fail; 8, 9 and 11 post to the offer queue (`+0x1C4`); 12..16 are status bits (16
means available and nothing running); 19 is last of chain.

Related builtins:

- 64 moves the rider to an instance through `0x001234D0`.
- 107 checks gate order (`0x0030BFC0`). The rider in the gate gives 1. Beyond 1.1 or 1.5 × the gate spacing gives -1,
  a missed gate.
- 50 and 79 read a rider stat (`0x00122EE8`, keyed through `0x004897B0`).

**Status bits.** Each challenge has a status word at character block `+0x118 + 4·index`: bit 0 locked follow-on, bit 1
new, bit 2 failed, bit 3 completed, bit 4 available.

**Completion and failure.**

- Completion `0x00307308`:
  - Sets bit 3.
  - Pays cash through `0x001511B0(peak)`: $2,000, $4,000 or $6,000. This is not the table's `+0x14`.
  - Shows the "MISSION SUCCESS" popup (`0x0010F2D8`) and runs `0x00119EF8` kind 4.
  - If there is a next challenge, it clears its own bit 4, clears the next challenge's bit 0 and sets its bits 1 and 4.
- Failure `0x003074C0` sets bit 2.

**Flow.**

1. Touching an offer volume runs a slot-2 program, which posts operation 8.
2. The next tick's queue read opens overlay 0x1D (Accept challenge?). Yes sets `+0x2A0` and pending operation 1, which
   starts the challenge. No is operation 3.
3. A tick-program failure (operation 9) opens overlay 0x1E (Retry?).
4. The challenge HUD is drawn at `0x001EB350`, inside `0x001EA930`.

(PS2) The offer, run, failure and success of one Snow Jam challenge ("Speed Demon", 12 gates, 60 s) were checked tick
by tick. Completion changed its status from 0x12 to 0x1A and paid $2,000.

## Trigger volumes: stage builtins 68 and 67

**Contact path.** Trigger volumes are collision nodes with flag 2 and slot-2 programs. A rider contact goes through
`0x00121818` to `0x0030A060`.

- `0x0030A060` sets `ctx+0` to the contacting rider's roster slot (rider interface vt+0x3C, which is `rider+0x86C`),
  runs slot 2, then restores the old `ctx+0`.
- It skips everything for a human (vt+0x44) that has finished (`+0x480`), unless `S+0x214` is 4 (free ride).

**Connector volumes.** Every connector has an Unload volume and a Load volume. The Unload volume sits on the hub (upper)
side, so a rider going downhill meets it first. Each program hides its own volume (builtin 29) and unhides its partner
(builtin 58). Two examples:

| Connector | Unload (action 0 -> `0x0022CEA8`) | Load (action 2 -> `0x0022D088`) | Destination, entry mode |
|---|---|---|---|
| A_ARA1 | rid 115 | rid 42 | ARA1, 2 |
| ERA5_C | rid 113 | rid 78 | C (Peak 2), 1 |

**Builtin 68** (`0x00302210`) handles human riders only. It reads three keys:

- **key0**: a map id (course table `+0x5C`), turned into a course through `0x00144CE0`.
- **key1**: the action:

| Action | Effect |
|---|---|
| 0 | Unload request |
| 1 | nothing |
| 2 | Load request |
| 3 | transport booth |
| 4 | lodge door |
| 5 | allow the sky dome switch |

- **key2**: the entry index into `0x00445E40`.

For actions 3 and 4, key0 is ignored and the station is the current course. On Peak 2, C's and D's volumes carry key0
values 19 and 18. The station volumes are `mdl_<X>_NIS_Lodge_0` (action 4) and `mdl_<X>_NIS_Transport_0` (action 3).

**Builtin 67** (`0x00302048`, which calls `0x0022D6C8`) is triggered by the RaceRideState volumes of the race and
freestyle courses. In CTM free ride on world screen 4, outside the backcountry, it turns the ride into that course's
event, and the PS2 opens the race card. The FreeRideState volumes of EBC3 (key0 4, value 1) are rejected.

## Rider location and query scope

**Location id `rider+0x434`.** `0x001218D0` (the per-rider pass from `0x00128AC0`, after motion) calls `0x0022E0E0`
with the track byte of `rider+0x430`. That field is the contacted patch's `+0x150` word (`rid << 8 | track`), and the
result is the location id.

- The rider constructor `0x0011B698` (`cRider_cRider`) writes 0x31 as the default, at `0x0011B718`.
- Readers:
  - For 11..13 (the super pipes), `0x0013C948` scales the auto boost by |normal.z|, and `0x00114298` skips the
    ground-focus launch scale.
  - For 17 and up (stations and connectors), the auto boost is halved.
- (PS2) On The Junction the value starts at 0x31 and becomes 11 at the first ground contact.

**Patch flags `rider+0x2D4`.** This field holds the contacted patch's runtime flags (`patch+0xA`). It is written by the
ground contact `0x0013D1B8` (at `0x0013D604`), and also by `0x00138960` and `0x001242B0`.

| Flag | Reader | Effect |
|---|---|---|
| 0x20 | `0x00114298` at `0x00114A5C` | A takeoff from a near-vertical wall (|`+0x380` z| < 0.05) is scaled by 0.8 unless this flag is set. The Junction's lip patches are authored 0x29 |
| 0x10 | `0x0013C948` at `0x0013C9CC` | forces the heading boost |
| 0x2 | `0x0013F178` at `0x0013F248` | requests the reset `0x00116120(rider, 0, 1)` on the ground |

**Query scope `rider+0x860`.** The rider's world queries (`0x003342D0`, including the landing probe `0x0013A7B0`)
visit only the scope lists.

- **Rebuild.** `0x00120E50` rebuilds the lists with `0x00332DB8`, from the rider query bounds `+0x400`/`+0x410` that
  `0x0011E150` writes.
- **What is kept.** `0x00332DB8` keeps a terrain patch (`node+0x24` list, box at `patch+0x158`/`+0x164`) or an
  inline-box instance (`0x003309D8`, flag 0x20, box at `+0x60`/`+0x6C`) when the boxes overlap, edges included.
  Flag-0x40 entities use their virtual `+0x168` box.
- **Refresh rate (PS2).** The refresh runs once every three game ticks, through `0x0026DBF0` (`cReplay_restoreFrame`
  in the decomp), `0x0012B788` and `0x00120E50`. It runs after each tick whose tick number is a multiple of 3, with that
  tick's bounds. The scope-derived light list (`+0x79C`/`+0x7A0`/`+0x7AC`) changes only on those ticks.

## Placement: regions, arrivals and session points

**Region lookup `0x0026B5E0(bank, kind, index)`.** It returns the bank row with `+4 == kind` and `+0 == index`. When
none matches, it returns the bank's first row.

- (PS2) Runtime kinds are the disc (AIP) kinds + 1. Grid slots are runtime kind 1 (disc kind 0) and session points are
  runtime kind 2 (disc kind 1).

**Region placement `0x0011DE60(rider, index, kind)`.**

1. Looks up the row with `0x0026B5E0(0x004D33A0, kind, index)`.
2. Sets control 0 and motion 0. The motion-0 entry `0x0013C7A8` runs before the placement, so `+0x390` holds the old
   `+0x370`.
3. Places the rider with `0x0011D660` (semantic 5, clearance 0).
4. Calls `0x0011DF18`, which sets the velocity to the placed forward (`+0x1B0`) × 833.333 cm/s with z stored as 0, and
   the animator rate to 0.

A score reset `0x00119368(score, 1)` runs as part of the arrival placement. One account lists it at the start of the
`0x0011DE60` work, and another attributes it to `0x0011D390`. This is unresolved, so it is unclear whether a Session
placement (which uses `0x0011DE60` alone) also resets the score.

**Arrival `0x0011D390`.** Used in game kinds 4..6 (free ride and the peak runs).

1. Calls `0x00117540`.
2. `0x00112180(rider, 1)` re-attaches the route at the grid slot (runtime kind 1 index 0, `0x00115B08` offset 0 for
   player 0).
3. Calls `0x0011DE60` at the entry row:

| Destination | Call | Row |
|---|---|---|
| courses below 14 | `0x0011DE60(rider, 1, 2)` | session point 1 |
| backcountries | `0x0011DE60(rider, 0, 1)` | grid slot 0 |
| stations | `0x0011DE60(rider, 0, 2)` | the first row, which is session point 0 at A |

4. In its tail, clears `+0x2E8`..`+0x2F4`.

The meter (`+0x2F8`), amount (`+0x2FC`) and retained limit (`+0x2E4`) carry over. A transport arrives from the loading
loop's limbo state, with `+0x370` = `+0x380` = (0, 0, 1) and surface 0. (PS2) The Transport arrivals at R&B, Crow's
Nest, Metro-City and The Junction place the rider at session point 1 of each course to the centimetre, with velocity
(forward.x, forward.y, 0) × 833.333.

**Session points.** They are opened from the Start menu (MCOMM, Session, overlay 0x20).

- The course's count comes from `0x00440770`.
- Item k reads "%s %d" (kT_MAPSessionPt, k + 1). The first item is kT_CMNTopOfRun and the last is kT_CMNBottomOfRun,
  unless there are only two. This is `0x00208840`, inside `0x002087F0` (`cOVState_MAP_onGainTransition`).
- The item's value (`+0x18`) is k + 1, and confirming stores it.
- "Session this area?" Yes enters world state 15 (`0x00236058`), which calls `0x0011DE60(rider, k + 1, 2)` at the
  current course, then `0x0011DF18`.
- Every course has exactly its count of disc-kind-1 rows, 1..count. Point 1 is the top entry and the last point is the
  bottom.
- The disc-kind-1 index-0 rows of ARA1 and ABC1 (the bottom exit and the plane drop) are not session points.

## Moving around the mountain

### Game modes and the world

The game mode is at `0x00535C12` and the game kind at `0x00535C10`. `0x00238160` (`cGameModeMan_initGameMode`)
chooses the handler.

| Mode | Event | Kind | Handler (functions) |
|---|---|---|---|
| 0 | race | 0 | 1, vtable `0x0047CF38` (`0x0023A108`, results `0x0023A760`) |
| 1 | slope style | 1 | 0, vtable `0x0047CFA0` (`0x00238E20`, `0x00239230`) |
| 2 | super pipe | 3 | 0 |
| 3 | big air | 2 | 0 |
| 4 | rival time (backcountry) | 5 | 5 (`0x0023B6C0`, `0x0023B8C8`) |
| 5 | rival points (backcountry) | 6 | 6 (`0x0023BB98`, `0x0023BDB8`) |
| 6 / 7 / 8 | Peak 1 / Peak 2 / All Peak Race | 5 (recorded for mode 6) | 4 (init `0x0023B268`, split `0x0023B5F8`, results `0x0023B468`) |
| 9 / 10 / 11 | Peak 1 / Peak 2 / All Peak Jam | 6 (recorded for mode 9) | 7 (init `0x0023C0D0`, split `0x0023C560`, results `0x0023C2D8`) |
| 12 | free ride | 4 | 2, vtable `0x0047CE00` (init `0x0023B170`) |

- **Finish eligibility.** `0x0010E5D8` accepts a finish only on course 1 (Metro-City) or courses 5..13 (the freestyle
  courses). Snow Jam, Ruthless Ridge, Intimidator, Gravitude and the backcountries have no finish in free ride or a
  peak run.
- **Free ride.** No rounds, results or AI. The event counts as complete from the start (`+0x9C` = 1). There is no time
  limit, and `0x00125228` never DNFs a free-ride rider.
- **Free-ride HUD.** Bit 0x80 shows the collectible counter "n/N" for the current course, with N from `0x0043FA70`.
  Bit 0x100 shows the cash. There is no clock, score, place or progress meter.

### World states and stations

- **Career start.** The notes place the CTM start choice at `0x001A0720` (`cFECustom_cFECustom` in the decomp). A new
  career starts at Happiness (14), dropped from the plane. Later starts are at the last lodge (profile `+0x27C`, 17 at
  first).
- **Start menu (MCOMM, overlay 3).** Items: Return, Transport, Session, Messages, Audio, Options, Quit. During a
  location crossing (screen 11) it is overlay 4, without Transport or Session.
- **Lodge door (action 4).** Enters world state 14 with argument 0. The walk-in cut is cinematics 0x16 and 0x17 through
  `0x00278E50`. Then overlay 0x1F asks whether to enter the lodge. Yes goes to the lodge of that peak. No rides in again
  from session point 0.
- **Transport booth (action 3).** Enters world state 14 with argument 2 (cinematic 0xB and a `0x0011D390` park) and
  opens the Map overlay 0x21.
- **Transport inside the world.** Chosen from MCOMM Transport or the booth, then "Transport to this area now?" Yes
  enters world state 14 with argument 1 (`0x00236250` / `0x00236418`).
  - **To the current location** (outside the backcountry): this is state 15 with session point 1.
  - **Otherwise**, in order:
    1. The departure cut (`0x00278DE8`, `0x0027A860`, `0x00279148`). `0x0027A860` also calls `0x0028E8C0(20)`, the
       travel sound.
    2. `0x0022CEA8(destination, 7)`.
    3. The loading loop streams the destination rows (screen 11, `0x00236960` waiting on `0x0022D278`).
    4. The arrival placement (`0x00123F38`, which calls `0x0011D390`).
    5. `0x0022D088(destination, 7)`, with the dome switch allowed.
  - (PS2) A transport to a station ends at the lodge door with the lodge prompt.
- **Another peak (PS2).** Choosing another peak asks "Go to this peak now?". Yes plays the first-arrival cinematic at
  that peak's backcountry. For Peak 3 this is the helicopter interior with "Loading...", the EBC3 movie and the
  helicopter arrival, then free ride at The Throne with EBC3, EBC3_E, TRANSP and ESKY resident.
  - In world state 10 (`0x002351A8`, inside `0x00235080`), only the first CTM arrival at The Throne plays FMV 31, then
    `ebc3_heli_arr` and `heli_arrb_<char>`.
  - Later arrivals with the transport flag play the two lists without the movie.
- **Other cinematics.** The plane drop at the first CTM start is state 10, cinematic 0x1D. State 10 also has location
  intros 0x1E, 0x1F, 0x10 and 0x11 (not seen on the PS2 runs; unconfirmed).
- **Music (PS2).** Station songs and hub chatter come from per-location MusicTrigger zones, not from the crossing
  itself.

### Peak runs

- **Handlers.** The peak runs use handlers 4 (time) and 7 (points). Both are solo, with no AI.
- **Tier.** The tier comes from the stored medal. Time challenge: gold or silver gives 2, bronze 1, otherwise 0.
  Points challenge: platinum, gold or silver gives 2.
- **Table `0x00440D18`.** For each mode it holds three tier rows with the limit, the split columns and the cash.
  Example (Peak 1 Race): 800, 760 and 670 s (gold is 670 s or less, silver 760 s or less), cash $5,000, $10,000 and
  $25,000. The jams run 12:00 on Peaks 1 and 2 and 2100 s for All Peak Jam. A failed run pays nothing.
- **Start.**
  - The run starts at grid slot 0 of the peak's backcountry. For All Peak the game-mode manager's `+0x68` holds 16
    (The Throne).
  - For Peak 1 there is no countdown: the clock starts on the objectives card's Continue. The card is "68rival_pre"
    (`0x001FD190`).
  - The game-mode manager's `+0x6C` holds the peak's race course, but no reader is known, and `0x0010E5D8` does not
    read it.
- **Splits.** The split handlers fire when a Load request (`0x0022D088`) enters a station, that is, when the current
  course is 17..21. For 5 s they show the difference to the tier row's split k:
  - time challenge: `int(ticks × 0.016666668) − split`, shown as ±H:MM:SS;
  - points challenge: `score − split × 100`.
  - Modes 8 and 11 have five splits.
- **Routes.** The Peak 1 routes are as recorded. The Peak 2 routes follow from the finish rule, the objectives text
  and the station path-bank variants: in a time challenge the hub banks send D to D_DRA4, A to A_ARA1 and B to B_BRA2.
  The All Peak route is inferred from the connectors.

| Run | Route | Finish |
|---|---|---|
| Peak 1 Race | ABC1 -> ABC1_A -> A -> A_ARA1 -> ARA1 -> ARA1_B -> B -> B_BRA2 -> BRA2 | Metro-City |
| Peak 1 Jam | ABC1 -> ABC1_A -> A -> A_ASS1 -> ASS1 | R&B |
| Peak 2 Race | DBC2 -> D -> DRA4 -> DRA4_A -> A -> ARA1 -> B -> BRA2 | Metro-City (it cannot end at Intimidator) |
| Peak 2 Jam | DBC2 -> D -> D_DSS2 -> DSS2 | Style Mile |
| All Peak Race / Jam | EBC3 -> E -> ERA5 -> C -> CRA3 -> D -> DRA4 -> A -> ARA1 -> B -> BRA2, crossing five stations E, C, D, A, B (unconfirmed) | Metro-City |

## Peaks: locks, rivals and per-peak values

- **Lock word.**
  - The profile character block is at `0x004A6CA8` + profile × 0x9B50 + character × 0xF88, and the lock word is at
    `+0x278`.
  - The profile index is the race copy `0x00535B20` `+0x10` & 1, and the character index is `+0x11`.
  - Bits: 12 is the Peak 2 pass and 13 the Peak 3 pass. Bits 6+p and 9+p are the rival locks, and bits 14+p and 17+p
    the peak-event locks.
  - `0x00145F90` (`cBENewPlayerInterface_isPeakLocked`) reads it through `0x00146008`
    (`cBENewPlayerInterface_isPeakLocked1`). (PS2) The Select Peak list reads the locks only when the screen is
    entered.
- **Peak rival.** `0x00145750(peak)` picks the peak's rival: Peak 1 Mac (Griff when the player is Mac), Peak 2 Nate
  (Zoe), Peak 3 Psymon (Elise). The backcountry rival events and the career slope-style opponent use it.
- **Per-peak cash.** Collectibles pay $500, $1,000 and $2,000 on Peaks 1, 2 and 3 (`0x00151178`). Big Challenges pay
  $2,000, $4,000 and $6,000 (`0x001511B0`).
- **Medal thresholds.** `0x0045AFE8` holds per-peak thresholds for collectibles and Big Challenges. The Peak 3
  collectible platinum (122) equals the sum of that peak's collectible counts.
- **End of the career.**
  - The Peak 3 goals give cheat characters (`0x00159CD0`, table `0x0045AA40`).
  - `0x001577E0` awards "Mountain conquered!", which unlocks Far East Myth. It requires golds in every standard event,
    any medal in the rival and peak events, the freeride medals, and a stat-medal sum of at least 24 on all three
    peaks.
  - There is no ending movie. The ending is the award messages.

## Stage builtin 34: teleport current player

**Builtin `0x00300770`.** It calls the rider's vt+0x54, which is `0x00123210`.

- **Argument.** One key, key 0, the destination instance resource, of type int (types at `0x004A3C40`, gp+0xB50).
  The default is -1 (`0x004A5688`, lazily set up through `0x004A5690`). A float passed where an int is expected is
  copied raw.
- **Instance.** When key 0 is -1, the instance is `ctx+0x290` (the current instance). Otherwise the resource is looked
  up in the world track table. `0x004A47B8` is gp+0x16C8.

```
W = *(*(0x004A47B8)); track = *(*(W+8) + 4*(res & 0xFF));
e = *(*(track+0x1C) + 4*(res >> 8)); inst = (e >> 8) << 2      // 0 when absent
```

- **Player.** `player = ctx+0`. The call does nothing when player < 0 or inst == 0.
- **Matrix.** If the instance has an entity (`inst+0xC`), the matrix is the entity's vt+0xC4, otherwise `inst+0x10`.
  - The Object entity's vt+0xC4 is `0x00356078`. It returns the primary modifier's vt+0x94 matrix (entity `+0x1C`
    container slot +0), or else `instance+0x10`.
  - UV scroll (builtin 21) sits in container slot +4, so the Metro-City destinations always resolve to
    `instance+0x10`.
  - (PS2) `instance+0x10` of all five Metro-City destinations was read in RAM. It is unscaled (the models' 2.65 scale
    is not in it).
- **Rider.**

```
rider = *(*(*(*(0x004A28A8) + 0x84) + 0xC) + 0x28 + 4*player)    // human 0, computer riders 1..5
```

  Then the builtin calls `rider->vt+0x54(rider, matrix)` and returns nil. The human vtable `0x004583A8` and the
  computer vtable `0x00458660` both hold `0x00123210` at `+0x54`, so computer riders can teleport too.

### `0x00123210(rider, matrix)`, in order

In this section G = `*(0x004A28A8)`, and the notes write S = G+0x84. The matrix rows are r0..r3, row-major, with r3
the translation.

1. **Race-event observer.** `0x00270970(*(S+0x28), rider+0x86C)`, the same checkpoint/gate observer the reset
   `0x00116120` uses. When the event's `+0x61C`, `+0x620` and `+0` are all 0:
   - `slot = 0x00270730(id)`, the human roster index, or -1 for a computer rider.
   - If slot ≥ 0, `0x00270DE0(ev, slot)` runs. When `ev+0` is 0, it calls `0x0026E800(ev+0x494+0xB4*slot)`, which
     releases the human's pending gate link: it clears bit `1 << entry+0` in `(entry+0xB0)+0x1E` and zeroes
     `entry+0xB0`.
   - Then `0x00270628(ev)` clears `ev+0x3D4` when it is set and there is one human.
2. **Destination point.** Computed with VU0 chop rounding:

```
(a, b) = offset by slot i = rider+0x86C:
         0:(2,0) 1:(1,0) 2:(2,-2) 3:(2,2) 4:(1,-2) 5:(2,1), other: (0,0)
P = r3 + 100 * (a*r0 + b*r1)      // full 4-term accumulate; w = 1
```

   The human lands 200 cm along the destination's local +X row.
3. **Direction.** `D = M × (1,0,0,0)`, with the constant vector at `0x004FF140`, which gives r0. Only D.xy is used
   (as the heading).
4. **Score reset.** `0x00119368(rider+0x790, 1)`. It adds the `0x0011A7A8` lost points to `+0x1A4`, then calls
   `0x00117838` (score reset) and `0x001175F8` (combo reset), then increments the reset count at `+0x120`. Its return
   value, the meter × -0.7 (constant at `0x0049B6C8`), is discarded, so there is no boost change. `0x0012F398`
   instead passes that value to `0x0010E098`.
5. **Motion exit.** `0x0011FE78(rider, 0)` calls `0x001112B8(rider+0x77C, 0)`. It always runs the current motion's
   exit, sets `+0xDE0` to 0 and runs the motion-0 entry `0x0013C7A8`.
   - The ground exit `0x0013F410` sets the decay targets at `+0x208`/`+0x2BC`/`+0x2C8` to 0 (rates about 0.05 .. 1.667).
     It sets `lastLeave` to tick - 500 when it was -1, otherwise to the current tick (tick from `0x001298C8`).
   - `0x0013C7A8` resets the board bounce phase and depths, copies the normal, stamps the ground-focus tick, and scales
     the velocity:

```
d = tick - lastLeave
factor = (d <= 40) ? 0.7 : min((d - 40) * 0.01 + 0.7, 1.0)
```

   A grounded rider therefore loses 30 %. An airborne rider keeps more of its speed the longer it has been in the air.
6. **Control exit.** `0x0011FEC8(rider, 0)` calls `0x00111538`. It runs the current control's exit, sets `+0xDE4` to
   0, and runs the control-0 entry `0x00131608`, which zeroes the idle clock (`+0x35C`) and the board-press latch
   (`+0x360`).
7. **Fade stop.** `0x00125038(rider)` stops the reset white fade. It acts when `S+0x84` is set, the device at
   `rider+0x870` is ≥ 0, and that device's viewport (`*(S+0x5C+4*dev)`) has `+0x78` == 1; it then calls
   `0x002E4578(viewport)`. For computer riders (device -1) it does nothing.
8. **Camera notify, before placement.**
   - The camera director is `Z = *(*(*(S+0x84)+4)+0xA0)` (vtable `0x0045B908`). Its vt+0x1C is `0x0015CC70(Z,
     riderId)`, which calls set-target on each node's algorithm. DEFAULT_3's set-target is `0x00176FE0`. It acts only
     when the algorithm's target is this rider: `0x00166C60` (reset, update, finish), the offset direction
     `0x00166550(559.744, 300)`, then the vt+0x28 update. For a computer rider these node set-targets do nothing,
     because the cameras target the human.
   - Then `0x0015E030(Y = Z+0x10)` calls `0x00166F28(Y+0xC0)` (the outer camera's embedded DEFAULT_3, always) and
     `0x002F41A8(Y)`.
   - The input is the rider as it is now: old position, velocity already scaled by step 5, motion 0.
9. **Speed.** `speed = sqrt(vx² + vy² + vz² + vw²)` of `+0x1E0`, with chop rounding. It is taken after step 5 and
   before the placement clears the velocity.
10. **Placement.** `0x0011D660(rider, &P, &D, semantic 5, clearance 0.0)`. This is the same placement the reset control
    uses, but the reset passes semantic 287 (A_CYC air). Semantic 5 is RNORM_FWD_CYC (class 7, clip 8960, blend
    0.23 s).
    - Clearance 0 means one world probe from P-7000 to P+200 cm in world Z, with preferred fraction
      0.9791666865348816, then +0.
    - The heading comes from D.xy, and the physical frame from `0x0011E098` (`cRider_updateOrientationImplicit`).
    - The tail:
      - zeroes the velocity (all four lanes), the contact state, the 19 filter triplets `+0x1F0`..`+0x2D0` and the
        boost amount `+0x2FC`;
      - sets `+0x300` (time scale) and `+0x318` (leg weight) to 1, clears `+0x150` (the detached board), copies
        `+0x324` into `+0x320` and zeroes `+0x350`, `+0x358` and `+0x35C`;
      - clears the animation channels and requests semantic 5 (`0x003128E8` `cRiderAnimBase_play`, `0x00312598`);
      - runs one full-rate step (`0x0011EB60(1)`, `0x0011EB98`, `0x003103F0`), the pose sample `0x0011E150`, the
        bounds `0x00332DB8`, `0x00122088`, `0x002105B0(+0x86C)` and rider vt+0x84.
    - For devices 0 and 1, it makes a second camera cut. The director's vt+0x24 is `0x0015CCF0`, which calls
      set-target on every node with no rider check, then `0x0015E030` and `0x002F41A8`. This time the input is the new
      position with zero velocity.
11. **Exit velocity.** `v = F × speed`, where F = `+0x1B0` is the physical forward. z is not zeroed, because
    `0x0011DF18` is not called. There is no 833.33 cm/s reset speed and no animation freeze.
12. **FX reset.** `0x00111890(rider+0x77C)` resets the trails, sparks and other effect owners (`0x002DCF28`,
    `0x002DAA78`, `0x002E8560`, `0x002E6640`, `0x002EADC0`, `0x002EF6A0`, `0x002D4BE0`, `0x002E3930`, `0x002DF3B0`,
    `0x002F1148`, `0x002F64E8`, `0x002C03E8`), then the viewport object's vt+0x74 for a device ≥ 0.
13. **Bone emitter.** `0x002F1A00(rider+0x88C)` zeroes `+0xA0` of the rider's bone-emitter controller (vtable
    `0x004881D0`). `0x002F1A08` updates that controller each tick from `0x00120E88`.

**Exit tables** used in steps 5 and 6:

| Motion (`+0xDE0`) | Exit (table `0x00456B10`) |
|---|---|
| 0 ground | `0x0013F410` |
| 1 | `0x00139A18` (empty) |
| 2 crash | `0x00136F28` |
| 3 | none |
| 4 rail | `0x0013C5A0` |
| 5 handplant | `0x00139178` |

| Control (`+0xDE4`) | Exit (table `0x00456B90`) |
|---|---|
| 0 | `0x00131C30` |
| 1 | `0x0012FE98` |
| 2 | `0x0012E9B0` |
| 4 | `0x0012FB68` |
| 5 | `0x00134CB0` |
| 7 rail | `0x00132048` |
| 8 crash | `0x0012E690` |
| 11 handplant | `0x00132F98` |
| 3, 6, 9, 10, 12, 13 | none |

**Result.** The rider ends in control 0 and motion 0, on the ground at the destination (plus the slot offset), facing
the destination's +X row. Its speed is the old speed × the ground-entry factor. The animation is RNORM_FWD_CYC, and the
trails and effects are reset. The score combo and pending points are lost and the reset count goes up by 1, with no
boost change. The camera is re-targeted twice, then updated normally at the end of the frame. The air predictor does
not start.

**Sibling `0x001234D0` (vt+0x64).** A different place-at-matrix: no slot offset, motion 3 with control 0xD then 6, and
zero speed. Builtin 34 does not use it. The Big Challenge builtin 64 does.

### Teleporters on Metro-City

All teleporters are in BRA2's own stage (track 16). B_BRA2 has none.

| Trigger (slot 2) | Draw (builtin 77) | Destinations |
|---|---|---|
| resource 0x43510 `mdl_BRA2_watertowerbeam_0001` | < 90 | 90 %: 0xA2C10 (`_0002`), else 0x22410 (`_0003`) |
| resource 0xC9810 `mdl_BRA2_phoneboothbeam_0004` | < 75 | 75 %: 0x99010 (`_0005`), else 0x68F10 (`_0006`) |
| resource 0x55B10 `mdl_BRA2_phoneboothbeam_0007` | < 101 (always) | 0x24210 (`_0008`) |

- **RNG.** Every firing uses one gameplay RNG draw (builtin 77, `0x00317810` `AIrand__Fv`).
- **No gating.** No program hides or debounces these volumes, and `0x00535C11` does not gate them, so they are live in
  the race. The triggers' runtime flags do not include 0x2000, so they take the static body route and are contactable
  in the race.
- **Contact rate.** The water-tower trigger has an Object entity that sets a 30-tick gate (`0x00355770`) after its
  section is entered. The phone-booth triggers have no entity, so `0x0030A060` runs on every contact tick.
- **Placement.** The triggers are rooftop and phone-booth secrets, off the default line. The computer riders' AI lines
  pass 14..40 m away, so computer riders could fire them too (not observed).
- **No PS2 result.** No PS2 run has touched a teleporter, so the teleport behaviour above comes from the code only.
