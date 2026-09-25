# Game, front-end and audio object layouts

Partial layouts of the game-flow, front-end and audio objects of SSX 3 (PS2, SLUS_207.72), gathered from reading the code and checking the running game. Offsets are byte offsets from the start of the object; a type is given only where it is known, and gaps between rows are simply unmapped. gp-relative globals are written as absolute addresses (gp = 0x004A30F0). **(PS2)** marks fields whose meaning was checked against the game running on a PS2 emulator; **(unconfirmed)** marks inferences. In the tables, the Evidence column reads "PS2" for checked fields, is blank for static reading of the code, and reads "unconfirmed" for inferences.

Game objects come first, audio objects after them. Camera, render, world, collision and animation objects are documented in the companion file "World, camera and render object layouts".

## Game object G

Global game object; pointer at gp-0x848 = 0x004A28A8.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x14 | float | Game clock delta time used by modifier updates | |
| +0x7C | ptr | FE preview block (preview slots at +0xB0, 0xCE0 bytes each) | PS2 |
| +0x84 | ptr | Game world object W (non-zero while in game) | |
| +0xC0 | ptr | GameModeMan / current event handler (handler id at +0x4, round at +0x0, final flag at +0x98) | PS2 |

## Game world object W

W = *(G+0x84), i.e. *(*(0x004A28A8)+0x84); non-zero while in game. The notes also call it game session, race/game object, world object S and race world. It is not the world manager at **(gp+0x16C8).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xC | ptr | Race object / rider manager (race clock, rider array, game info); see "Race object" | PS2 |
| +0x28 | ptr | Unresolved: game-flow word holder (0 race, 10/11 ready screen, 13 after finish); replay object (state 1-9 replay, 0 recording; ctor 0x0026EFB8, read by 0x00288AE0); race-event observer passed to 0x00270970; tutorial counter (career messages gated while 1..9) | PS2 |
| +0x44 | ptr | Surface parameter record array (stride 0xB0) | PS2 |
| +0x5C | ptr[] | Viewport per device | |
| +0x78 | object | Location streamer object, driven by 0x0022D8D8 once per game tick | |
| +0x84 | ptr | Camera manager: its +0x10 is the camera count (read by the camera splash gate); *(+0x4)+0xA0 is the camera director chain; also tested by 0x00125038 | |
| +0x214 | int | World/screen state: 1 intro, 2 card, 3 countdown, 4 free ride (game screen), 5 finish, 7 results, 12 podium, 14 transport; 0x0030A060 lets finished humans trigger only in 4 | PS2 |

## Race object (race game-info object)

*(W+0x0C). The notes also call it rider manager, race roster, race clock and game-info object. The game update calls it through the interface vtable at +0xCC.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Race phase (race clock) | |
| +0x8 | int | Total simulation ticks = global game tick (incremented at the end of 0x00128AF0; read by 0x001298C8) | PS2 |
| +0xC | int | Race ticks (incremented by 0x00113DB0) | PS2 |
| +0x14 | int | Race-enabled flag, cleared on Freeride entry | unconfirmed |
| +0x1C | int | Countdown count: 180 on Countdown entry, decremented, cleared on exit | unconfirmed |
| +0x28 | ptr[] | Rider pointer array (+0x28 + 4*slot; slot 0 human, 1..5 computer riders) | |
| +0x74 | int | Rank mode (2 = rank by score) | PS2 |
| +0x78 | int | Event rider (roster) count; the POST_RACE_1 camera uses wider framing when >= 2 | PS2 |
| +0xB8 | int | Handler-local value cleared on PreRace entry | unconfirmed |
| +0xCC | ptr | Interface vtable 0x00458488; the game update calls slots +0x18/+0x1C through it | PS2 |

## GameModeMan (game mode manager / event handler)

Reached as *(G+0xC0) (G = game object) and through the global at gp-0x480 = 0x004A2C70. career-events.md gives the pointer as *0x004A2C6C instead; which global is right is unresolved. Race handler init 0x0023A108, freestyle handler init 0x00238E20; the handler slot is selected by 0x00238160. The notes also call it the event handler and "the object at gp-0x480".

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Current round (Rival Time init sets 1; Single Event forces round 3, final only) | |
| +0x4 | ptr | Handler slot / handler id (selected by 0x00238160) | |
| +0x8 | | Handler kind = game mode byte (0x00535C12) | PS2 |
| +0x10 | int | Other-rider count: live slots = +0x10 - +0x14 + 1, computer riders spawned = +0x10 - +0x14 (race 5, slope style 1, pipe/big air 0); 1 in rival modes | PS2 |
| +0x14 | int | Posted rider count (0x00238E20 sets 4 for kind 1, else 5); zeroed by rival init | PS2 |
| +0x18 | int[] | Character per rider slot (CHARDB base character; slot 0 = player, -1 empty); written by 0x0023A668 | PS2 |
| +0x1C | int | Slot 1: peak rival / opponent character (0x00145750); Single Event puts the last shuffled character here | PS2 |
| +0x20 | int[] | Remaining slots: other characters, shuffled | PS2 |
| +0x40 | int[] | Per-slot lineup word (-1 empty, 0 for the rival slot); second participant array written by 0x0023A668 | |
| +0x68 | int | Peak-run start course (-1 in rival modes; 16 The Throne for All Peak runs) | |
| +0x6C | int | Peak's race course (3 for mode 7, 4 for All Peak); no reader in 0x0010E5D8 | |
| +0x70 | int | Next round (1 at init, 0 on a rival win); Pause Restart copies +0x74 here (0x00238348) | |
| +0x74 | int | Round just played (1 at init; takes +0x70 on a win). Possibly the 'game+0x74' that is 2 in The Junction event and 1 in races | |
| +0x78 | int | Time limit in ticks = 0x001454F8(course, round) x 60 when +0x88 is set; +0x78..+0x94 all zero = no limit; slope-style checkpoint accept 0x002398E8 adds value x 60 | PS2 |
| +0x84 | int | Unresolved: win flag set by rival results (backcountry notes) vs fresh event flag (career notes) | |
| +0x88 | int | Time limit enabled flag (1 in Rival Points) | PS2 |
| +0x94 | | Field with no reader (differs for big air) | |
| +0x98 | int | Medal-run / final-round flag: 1 for round 3 of race/freestyle handlers and one-round handlers (set by 0x0023A108, 0x00238E20); the final heat queues [4 start hut, 5 idle] (0x00235C58). Unresolved: rival init sets 1, audio notes say 0 in rival challenges | PS2 |
| +0x9C | int | Event complete flag (1 from the start in free ride; set by results) | |

## Profile character record

0xF88 bytes per character: 0x004A6CA8 + bank*0x9B50 + char*0xF88 (profile bank, character 0..9). The notes also use "career profile P", "career profile block" and "profile" for fields at these offsets; they are merged here.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x118 | u32[] | Big Challenge status word per challenge (+0x118 + 4*index): bit 0 locked follow-on, 1 new, 2 failed, 3 completed, 4 available | PS2 |
| +0x278 | u32 | Lock word (set = locked): bits 6+peak / 9+peak rival race / jam, 12 Peak 2 pass, 13 Peak 3 pass, 14+peak / 17+peak peak events. Bit 12 set on a fresh profile (tested by 0x00146008) | PS2 |
| +0x27C | int | Last lodge course index used as the Conquer the Mountain free-ride start (17 = Green station initially) | |
| +0x280 | | Race adaptive difficulty state (+0x280/+0x282), level 0..2, updated by 0x00147D20/0x00147E18; two steps move a level (win margin 601/301/181 ticks in rounds 1/2/3) | |
| +0x284 | | Freestyle adaptive difficulty state (+0x284/+0x286): up on a heat-2 win or final medal, down on a final fail; posted-score scale 0.9 at level 0, 1.2 at level 2 | |
| +0x288 | | Inventory item -> row lookup | PS2 |
| +0x28C | | Inventory row count | PS2 |
| +0x290 | | Inventory rows {s16 item, u16 flags} (see "Inventory row") | PS2 |
| +0xAC4 | int | Current cash | |
| +0xAC8 | int | Lifetime earnings | |
| +0xACC | u32 | Visited-locations mask (bit per location) | |
| +0xBB8 | byte[8] | Stat medal tiers, one byte per personal-best category (StayOnRail, HoldHandplant, StayInAir, KOPeopleRace, DoUberGrind, DoSupUber, GetPoints, DoXCombo); thresholds 0x00440ED0, written only by 0x00155390 | |
| +0xBC1 | | Relationship records toward each other character, 3 bytes each (see "Relationship record") | PS2 |
| +0xE38 | | Career message inbox (see "Career message inbox") | PS2 |
| +0xF28 | | One-shot award bits (awards 17-19 excepted) | |
| +0xF30 | | Reward ownership bits (+0xF30..+0xF57) | |
| +0xF57 | | Cheat character unlock bits of this base rider: bit (id - 10) set = cheat character owned; all zero on a fresh profile | PS2 |

## Inventory row

4 bytes; rows at profile character record +0x290 (count at +0x28C).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | s16 | Item id | PS2 |
| +0x2 | u16 | Row flags (0x2 owned, 0x4 committed, 0x10 equipped, 0x20 default) | PS2 |

## Relationship record

3 bytes at profile character record +0xBC1 + other*3.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | u8 | Relationship kind | PS2 |
| +0x1 | u8 | Relationship level (= score / 5 after ageing) | PS2 |
| +0x2 | u8 | Relationship score | PS2 |

## Career message inbox

At profile character record +0xE38.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | | 25 message entries {item index, variant}; the oldest is dropped first when full (0x001E31B8) | PS2 |
| +0xC8 | | Read bits, one per entry; a new message clears its bit | PS2 |
| +0xCC | | Message count | PS2 |
| +0xD0 | | Posted bits, one per message category (tested 0x00147980, set 0x00147A30): bits 40..51 pending peak-challenge flags, 7..11 open FAQ folders (0x001E4338), 28..33 set by 0x001E2370 | PS2 |

## BOLT item entry

56 bytes; runtime item DB at 0x004A6750, loaded from BOLTPS2.DAT.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | | Character (bucket) | PS2 |
| +0x2 | | Tier | PS2 |
| +0x3 | | Texture group (-1 = no texture) | PS2 |
| +0x4 | | Item id | PS2 |
| +0x6 | | Class: the model entry the item belongs to (e.g. top colour Junker -> Midriff Top model -> Tops class); walked by 0x0014D608 | PS2 |
| +0x8 | | Menu parent | PS2 |
| +0xA | | Menu order (lists are sorted by it) | PS2 |
| +0xC | | Item-limit weight (summed by 0x0014B478) | PS2 |
| +0xE | | Price / 10 | PS2 |
| +0x10 | | Part slot in the low byte (geometry file id; 0xFF = no model) | PS2 |
| +0x14 | | Name | PS2 |
| +0x18 | | LOD model names H/M/L/Shadow (+0x18..+0x24), or one _NIS model | PS2 |
| +0x28 | | Model path | PS2 |
| +0x2C | | Texture name with '$' wildcards (resolved by 0x0014B988) | PS2 |
| +0x30 | | Icon | PS2 |
| +0x34 | | Flags | PS2 |

## Course table entry

Table at 0x0043D950, stride 0x64.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Course index | |
| +0x4 | | Course name | |
| +0x24 | | Short name | |
| +0x34 | | Course code (e.g. ARA1) | |
| +0x44 | | World | |
| +0x54 | int | Unresolved: career peak, 0-based (0 Peak 1, 1 Peak 2, 2 Peak 3; read by every progression function via 0x00144C78; Intimidator DRA4 is a Peak 2 race) vs flag wind mode minus 1 (set-piece notes) | |
| +0x58 | | Station flag | |
| +0x5C | int | Map id (the builtin 68 key0 value for this course) | |
| +0x60 | int | Map region (ABC1 15; every Peak 3 course 2) | |

## Big Challenge table row

Table at 0x0043EE10; 0x24 bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x14 | int | Cash value (the completion payout uses 0x001511B0(peak) instead) | |
| +0x18 | s16 | Flags word: peak of the challenge | |
| +0x1A | u8 | Flag byte copied to status bit 0 (locked follow-on) for a new character (0x00151600) | |
| +0x1B | u8 | Flag byte copied to status bit 4 (available) for a new character (0x00151600) | |
| +0x22 | u8 | Music type of the challenge (0x0029D6E0 events 33/34/38) | |

## Location stage (stage script container)

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x20 | ptr | Mission record array (0x54-byte records) | |
| +0x24 | int | Mission record count | |
| +0x30 | ptr | Mission step (task) array (0x38-byte steps; kinds start, tick, end, events 0..9) | |
| +0x34 | int | Mission step count | |

## Mission record

0x54 bytes; array at location stage +0x20.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Challenge id (index into the Big Challenge table 0x0043EE10) | |
| +0x4 | int | Step range/reference (with +0x8) | |
| +0x8 | int | Step range/reference (with +0x4) | |
| +0xC | int | Start program word (program << 8 \| track); followed by 10 mission event program words | |
| +0x10 | int | Tick program word (program << 8 \| track) | |
| +0x14 | int | Stop program word (program << 8 \| track) | |
| +0x40 | int[] | Callback words +0x40..+0x50: +0x44 complete, +0x48 fail, +0x4C status/visual, +0x50 misc (slot of +0x40 not stated) | unconfirmed |

## WScript mission context

Called C in the notes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | int | Challenge HUD word, zeroed each WScript tick (also +0x10, +0x1C, +0x28, +0x34) | PS2 |
| +0x40 | queue | Queued WScript events (kind 0 = 0x0030A060 contact), dispatched to mission and current-task event programs | PS2 |
| +0x1C4 | queue | Big Challenge offer queue (ops 8/9/11 post here; read next tick to open overlay 0x1D) | PS2 |
| +0x2A0 | int | Accepted challenge (set on Yes in the offer overlay; pending op 1 then starts it) | PS2 |
| +0x2B4 | list | Inactive mission list | |
| +0x2B8 | list | Active mission list (push front; mission next link at +0x18) | |

## WScriptMission object

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x18 | ptr | Next mission in the C+0x2B4/+0x2B8 lists | |
| +0x1C | ptr | Per-run 8-bucket LUN table used as the programs' globals | |

## Stage script context

ctx = *(gp+0xCE8) = *(0x004A3DD8).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Current player/roster slot for builtins (0x0030A060 sets it to the contacting rider's +0x86C) | |
| +0x28C | | Stage program handle passed to 0x003A6D18 | |
| +0x290 | ptr | Current instance (used when a builtin's instance key is -1) | |
| +0x2A4 | ptr | Instance script table used by 0x0030A060 / 0x0030AC98 | |
| +0x2A8 | ptr | Alternative path to the instance table: ctx+0x2A8 -> +0x3C -> +0x1C | |
| +0x2C0 | ptr | Collectible slot/set: a single slot opened by 0x0030B928 only when free and freed by 0x00308FE0; filled by builtins 37/38 | |
| +0x3CC | ptr[] | Per-slot globals table pointers: globals = *(ctx+0x3CC+4*slot) | |

## LUN stage program header

Read by the interpreter 0x002227D0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | u32 | Code end: byte offset of the trailer from the header (>= 0x10); the trailer holds one 16-byte function record per function (header + codeEnd + 16*index) | |
| +0x8 | u32 | Program extent (stored twice, at +0x8 and +0xC) | |
| +0x10 | u32[] | Start of the code words; pc is a word index from +0x10 | |

## LUN interpreter stack frame

Stack frame of 0x002227D0; offsets are sp-relative.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x70 | ptr | Program header pointer | |
| +0x74 | ptr | Code base pointer | |
| +0x78 | int | Code word count (loop bound) | |
| +0x7C | ptr | Argument stack pointer | |
| +0x80 | int | Argument count (pushed entries) | |

## LUN VM value

12 bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | u32 | word0: int / float bits / symbol hash / table pointer / program header | |
| +0x4 | u32 | word1: function record index; only type-5 copies copy it, other copies keep the destination's old word1 | |
| +0x8 | u32 | Value type (0 nil, 1 int, 2 float, 3 symbol, 4 table, 5 function) | |

## cLunoTable (LUN VM table)

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | int | Reference count | |
| +0xC | int | Bucket count n (modulus); bucket = key.word0 % (n - 1) unsigned, so the last head is never used. Host tables have 8 buckets, op 0x19 creates 32 | |
| +0x10 | ptr | Array of n embedded 32-byte head nodes | |

## LUN VM table node

32 bytes; bucket heads are embedded in the table's +0x10 array.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | | Key value (12 bytes) | |
| +0xC | | Stored value (12 bytes); a nil value in a head marks the bucket empty | |
| +0x18 | ptr | Next node in the bucket chain | |
| +0x1C | ptr | Node vtable | |

## LUN VM argument-stack entry

16 bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Argument key (builtins parse arguments by key) | |
| +0x4 | | Argument value (12-byte LUN value) | |

## Race-event observer

*(W+0x28); passed to 0x00270970 for checkpoint/gate events. Other notes read the object at W+0x28 as the replay object (see W +0x28); they may be the same object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Event mode (release path only when 0) | |
| +0x3D4 | int | Flag cleared by 0x00270628 when the human count is 1 | |
| +0x494 | struct[] | Per-human gate entries, stride 0xB4 | |
| +0x61C | int | Gate word checked by 0x00270970 (must be 0) | |
| +0x620 | int | Gate word checked by 0x00270970 (must be 0) | |

## Race-event gate entry

Observer +0x494 + 0xB4*slot.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xB0 | ptr | Pending gate link (bit 1 << entry+0 is cleared in link+0x1E on release) | |

## Race checkpoint manager

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x3B4 | ptr | Notification object; its byte +0x1F carries checkpoint notification bits | |

## Race game object

Vtable 0x0047D130 (race game update 0x002306B8).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x68 | ptr[] | Camera-splash object pointers indexed by camera (getter 0x002306A8) | unconfirmed |

## Race rules object

Vtable 0x0047CF4C. The notes write the field as roster+0x84; it may be the race object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x84 | | Roster (re)build flag; set to 1 by the reset 0x00238C80 | |

## Race place display object

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4C | float | 1st-place glow timer (0..2 while leading, -1 otherwise) | |

## Game mode settings block

Global block at 0x00535BC8.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x48 | u8 | Game mode byte (0x00535C10); 5 and 6 make the event load use the out-of-lodge load state (read by cGameLoadState init 0x00232E20) | |
| +0x49 | u8 | Play type (0x00535C11): 0 Conquer the Mountain (0x00232E20 builds the Conquer load state), 2 multiplayer match (cGameLoadState enter 0x00245418 opens 102MPMatch, not 99QPEvent), else Quick Play single event | |

## Race copy

Global block at 0x00535B20.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | u8 | Profile bank index (& 1) of the player | |
| +0x11 | u8 | Player character index | |

## Setup slot

0x00534FE0 + slot*0x1C.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x11 | u8 | Base character id (0..9) of the player slot; getter 0x0014A080 | PS2 |
| +0x12 | u8 | Cheat character id (10..29) worn on the base rider; getter 0x0014A0B0; confirming a rider on Select Character clears it | PS2 |

## Game clock object

Global object at 0x004C9428.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | int | Clock rate (60 ticks per second); used by Debounce (duration x rate) and the entity contact cooldown (rate/2) | PS2 |

## Game object (owner of the world render owner)

Called "game" in the render notes; it may be the game object G.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1C | ptr | World render owner (sun and light-glow owner) | |

## Path manager

Global object at 0x004D33A0 (the AI path bank).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | ptr | 14 start marker records | PS2 |
| +0x8 | int | AI path count (129); array at +0xC | PS2 |
| +0x10 | int | Course-progress (track) path count (8) | PS2 |
| +0x14 | ptr | Course-progress path array (stride 60) | PS2 |

## AIP region row

Row of the path bank 0x004D33A0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | int | Region row index (matched against the requested index by 0x0026B5E0) | PS2 |
| +0x4 | int | Runtime kind (exported kind + 1: 1 grid slot, 2 session point) | PS2 |
| +0x20 | ptr | Reset (AI) path of the region row (ARA1 kind 0 index 0: reset path 2) | |
| +0x24 | ptr | Race path of the region row (ARA1 kind 0 index 0: race path 3) | |

## Runtime reset path

AIP AI path record; it may be the path referenced by AIP region row +0x20.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x38 | int | AIP AI path field3 | |
| +0x3C | int | AIP AI path field6 | |

## FE preview slot

*(*(gp-0x848)+0x7C) + 0xB0 + player*0xCE0: slots of 0xCE0 bytes starting at FE preview block +0xB0 (block = G+0x7C).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | | Character id | PS2 |
| +0x8 | ptr | Geometry pointer (unscaled preview geometry) | PS2 |
| +0xC | ptr | Animator pointer | PS2 |
| +0xC1C | | Customize speech request flag (set by 0x00199EA4, polled by 0x001A0358) | |
| +0xC20 | | Post_Selection speech request flag (set by 0x0018185C, polled by 0x001A0358) | |
| +0xC30 | vec4 | Root position | PS2 |
| +0xC40 | vec4 | Root quaternion | PS2 |
| +0xC50 | vec4 | Board position (written by 0x0019F548) | PS2 |
| +0xC60 | vec4 | Board quaternion (written by 0x0019F548); equals the computed Equip Gear spin quaternion | PS2 |
| +0xCB4 | | Model ready flag (paired with +0xCB8); Equip Gear shows 'Loading...' until set | PS2 |
| +0xCB8 | | Model ready flag (paired with +0xCB4) | PS2 |
| +0xCC8 | | Model shown flag: 0 while the preview is hidden (e.g. about 26-30 frames after Setup/Rider Details transitions) | PS2 |
| +0xCD0 | | Selector read by the FE lighting (0 in every state seen, so the Moby-to-elise record branch is not taken) | PS2 |
| +0xCD4 | | Lighting path selector: 0x0019EE88 builds the IRR lighting bank when it is < 0 | PS2 |
| +0xCD8 | | Variant mask | PS2 |

## Equip Gear preview state

Updated by 0x0019BFE8; owner object not named in the notes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xAAC | | Rider turn angle in degrees (rider yaw = +0xAAC + 80); stick X adds 3 per frame | PS2 |
| +0xAE0 | | View state: 1 rider view, 2 board view, 3 easing to board view (set on entering Boards, 0x00199D14), 4 easing back (on leaving, 0x00199E30) | PS2 |

## Single-player HUD owner

Update 0x001EA930, draw 0x001EC3F8 (also called the HUD owner object).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x48 | | Single-player HUD per-player state (see below) | |
| +0x70 | | Per-player pulse used by the type 1 score draw; writer unknown | unconfirmed |
| +0x3CC | u32 | HUD element flags, from table 0x00478078 masked by the HUD level: 0x1 place, 0x4 clock, 0x10 standings, 0x40 progress meter, bit 20 finish banner, bit 27 OPPONENT line | PS2 |
| +0x3D0 | | Clock red blink state | |
| +0x428 | ptr | FEFONT font | |
| +0x474 | int | Glow texture handle (from renderer +0xF50; 0x5F5 'part') | |
| +0x480 | float[4] | Glow UV rectangle (+0x480/+0x484/+0x488/+0x48C = 0/0/1/1) | |
| +0x49C | | 'timeup' sprite (TIME'S UP) | PS2 |
| +0x4B4 | | 'fini' sprite (OV_1-3 FINISH!) | PS2 |
| +0x538 | ptr | Boost orb sprite (descriptor 3; UV 0.572265625, 0.197265625, 0.693359375, 0.318359375) | |
| +0x55C | int | Uber hint variant index: starts as 0x003177F0() & 1 (visual RNG 0x004FF018 at HUD init 0x001E9AD0); flips on each pre-pass that sees slot 9 at value/maximum == 1 | PS2 |
| +0x560 | ptr | Uber hint text ('UBER TRICK = @l1 + @square' or the @r1 variant), taken from table gp-0xF20 = 0x004A21D0 by +0x55C | PS2 |

## HUD per-player state

At HUD owner +0x48.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x54 | | Active flash palette colour for the orb/coil (pre-pass state; palette tier = slot 9 argument) | PS2 |
| +0x64 | float | Tricky flash phase (-1 inactive), written in 0x001EBC94..0x001EBF2C: += (1/30)/((1-fraction)*0.9104144 + 0.0299726), wraps while > 2; letter glow and orb active when >= 0 | |
| +0x68 | float | Pending-Uber-letter phase (drives the pending letter x scale) | |
| +0x80 | u32 | Element mask; after the finish it holds all bits except bit 20, hiding all but the bit-20 finish banner | PS2 |
| +0x84 | | Uber-hint gating computed by the pre-pass (bit 25) | PS2 |
| +0x88 | int | Finish banner state: 1 FINISH, 2 TIME'S UP (set by 0x001EB9E8 as rider+0x480 ? 2 : 1) | PS2 |

## Score HUD message bank

*(score+0x1B0); 44 slots of 0x9C bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x30C | | Slot 5: boost preview fill | |
| +0x3A8 | | Slot 6: stored boost meter display | |
| +0x4E0 | | Slot 8: earned SUPER UBER letters | |
| +0x57C | | Slot 9: Tricky timer / flash widget | |
| +0x618 | | Slot 10: pending-Uber letter preview | |

## In-race HUD object

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x160 | | New-message notice flag set by HUD event 8; the mail icon shows while it is set | PS2 |

## Full-screen fade overlay

Vtable 0x0048817C.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x48 | | Alpha fade timing/value parameter (with +0x54/+0x58/+0x5C) | |

## NIS list player / step

Owning structure not named in the notes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xB8 | | Fade-related value after which the script clock starts (out + hold) | unconfirmed |

## LUI widget base

Ctor 0x0039FB30.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x14 | u32 | Widget flags: bit 0 vertical, bit 3 item takes input first, bit 5 hidden/disabled, bit 7 wrap (bits 2 and 4 also cleared by default) | |
| +0x6C | int | kind[0]: UI sound kind for a blocked move / 0x10 query result (default 4 = error) | |
| +0x70 | int | kind[1]: UI sound kind for a 0x1 query result (default 6 = accept) | |

## UIMenu

Vtable 0x00494928.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x90 | u8 | Flags: bit 2 virtual list (selectability via query event 1, 0x0039B760); bit 3 silent (setter 0x003A5390 unreferenced) | |
| +0x91 | u8[4] | Navigation button ids +0x91..+0x94 (default 0..3 = UIUp, UIDown, UILeft, UIRight) | |
| +0xA0 | ptr | Focused item | |

## UIListBox

Vtable 0x00494798.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x318 | u8 | Item count | |
| +0x319 | u8 | Current index | |

## cUISlider

Vtable 0x00494348.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x74 | int | Slider value | |
| +0x78 | int | Slider step count (12 for volume sliders, values 0..11) | |

## LUI menu item widget

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x18 | int | Item value (radio mode values set by 0x00196540) | |

## LUI screen

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x5C | ptr | First link of the UI sound listener chain (-> +0xD0 state/handler -> +0x10 UI context -> +0x14 listener) | |

## cFEStateAudioOptions

Associated address 0x00195FF0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x5C | | Checkbox sprite (put on the new box) | |
| +0x60 | | Empty box sprite (put on the old box) | |
| +0x78 | int | Checkbox index (selected radio mode box) | |

## cFEStateRequestLine

Associated address 0x00196B90.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x16C | | Conquer the Mountain flag: unowned songs are buyable only when set | unconfirmed |

## Pause menu state

Vtables 0x00472C60..0x00473170.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xD8 | array | Per-item enabled flags (state+0xD8[id] != 0 = enabled) | |

## Pad object

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | struct[24] | First of 24 consumed button records (stride 0x1C) | PS2 |

## Pad button record

Stride 0x1C; 24 of them in the pad object from +0x4.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | float | Raw value (read by bare-name expressions) | |
| +0x4 | u32 | Pressed edge flag | |
| +0x8 | u32 | Released edge flag | |
| +0xC | u32 | Held flag | |
| +0x10 | u32 | Repeat flag | |
| +0x14 | u32 | Repeat timer | |
| +0x18 | u32 | Edge age (0..3; 3 = settled) | |

## Pad input ring

*(gp-0x850) = *(0x004A28A0).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x2EE0 | int | Read cursor | PS2 |
| +0x2EE4 | int | Write cursor | PS2 |

## Accepted command packet

Written by the human input writer 0x00127998.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | u32 | word0: bits 24..29 turn, 16..23 signed grab identity (-1 none; all-zero is also a valid airborne grab), 12 recovery, 13 handplant, 14/15 attacks. Rail notes map crouch/jump held/pressed to bits 14/13 instead; bits 13..15 may be controller-specific | unconfirmed |
| +0x4 | u32 | word1: bits 0..5 crouch | |

## Crowd record (stage crowd)

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x18C | float | Crowd cheer level | |

## CrowdMan2d manager

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x240 | int | Flash countdown per registered crowd slot (slots of stride 0x40; whether the countdown sits inside each slot or in a separate array is not stated) | unconfirmed |

## SSXAudioSystem

Pointer at gp+0x410 = 0x004A3500 (*0x004A3500). The notes also call it the audio manager, audio object and speech/feedback manager. Offsets below are relative to the audio system object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | ptr | Sound request array: bank slot per request (*(audio+4)[i]) | |
| +0x8 | ptr | Sound request array: sound index in the bank (*(audio+8)[i]) | |
| +0xC | | UI sound player object (vtable slot +0x8 = 0x00290CC0) | |
| +0x118 | | Embedded music manager (64 song slots, playlist, song tables). The same notes also dereference *(audio+0x118) to reach the sound manager (timer/callback queue, sound requests); embedded vs pointer is unresolved | |
| +0x504 | | The 35 front-end songs used by the Request Line list | |
| +0x508 | int | Current playlist index (= music manager +0x3F0); the in-game Request Line sets it and calls PlayMusic(0,0,-1,1) | |
| +0x518 | u64 | Radio BIG playlist mask (SSX Mix, all 35 songs) | |
| +0x520 | ptr | Current SongInstance (= music manager +0x408) | |
| +0x530 | int | Song active flag (= music manager +0x418) | |
| +0x534 | int | Last Pathfinder event sent (= music manager +0x41C) | PS2 |
| +0x5558 | ptr | Unresolved: music listener vtable pointer (0x00483688) vs music manager vtable 0x004838F8 (given at music manager +0x5440 = audio +0x5558); both in audio-logic.md | |
| +0x5560 | | Embedded speech manager / DJ player (vtable 0x004836D8; ctor 0x002B07F8/0x002B0AE8; SpeechInstance 0x002B0E60, start 0x002B1758, stop 0x002B11B0); one speech voice for DJ, PA, rider and arcade speech. Also described as the feedback event queue (ten 32-byte slots) used by 0x002B1458 | |
| +0x5730 | | Fixed-volume speech gain slot used for DJ lines in the front end (never ducked) | |
| +0x5738 | | Current speech bus, chosen from the bank name by 0x0029EEE0 | |
| +0x573C | | Hub chatter used-category mask (shuffle without repeat) | |
| +0x5740 | | Pending DJ_Radio_Big_Outro | |
| +0x5744 | | Pending rider Finish_Line speech | |
| +0x574C | | Pending DJ hub chatter request 1 | |
| +0x5750 | | Pending DJ hub chatter request 2 (pool 8; set by MusicTrigger 13) | PS2 |
| +0x5754 | | Pending DJ hub chatter request 3 (pool 5) | |
| +0x5758 | | Pending DJ_Event_Intro | |
| +0x5768 | | Pending DJ_Radio_Big_Intro | |
| +0x576C | | Pending DJ_First_Spoke (peak) | |
| +0x5770 | | Pending DJ_Free_Ride_Intro (course bit, 0x002A1BD8) | |
| +0x5774 | | Pending DJ artist intro flag (argument at +0x5778) | |
| +0x5778 | int | Unresolved: pending DJ artist intro argument (SEDVALUE; audio notes, unconfirmed) vs artist intro pending flag set to 1 after the event start speech (backcountry notes) | |
| +0x577C | | Pending DJ_Text_Message (variant from +0x5780, then 1) | PS2 |
| +0x5780 | | DJ_Text_Message variant (2 the first time, then 1) | PS2 |
| +0x5784 | | Pending DJ_BC_Intro (peak) | |
| +0x5788 | int | Pending rider BC_Challenge speech; holds the speaking rider slot of the queued rival speech (rival slot 1) | |
| +0x578C | int | New-career intro flag, set by 0x00234F40 | |
| +0x5790 | | Hub intro flag: 0 until Char_Stories has played (DJ kind 0 vs 1), 0 after the new-career intro | PS2 |
| +0x579C | byte[23] | First-visit flags per location, from the profile visited mask (profile character record +0xACC, 0x00145D38); used for Free_Ride_Intro | PS2 |
| +0x5814 | int | Travel flag set by 0x0028E8C0(20) (stays 0 on a location crossing) | PS2 |
| +0x581C | int | Last boost/Uber tier of the focus rider (Super Uber speech edge detect) | PS2 |
| +0x582C | int | GO game tick (written by GO 0x0029C7B0 at 0x0029C7FC); pass speech is allowed 600 ticks after it | PS2 |
| +0x5830 | float | Air whoosh gain = (127 - stream)/127 x ch5 volume; gain pointer of the whoosh voice (sent whoosh volume tracks 127 x this) | PS2 |
| +0x598C | int | Rail surface type (last rail surface id), written at rail attach 0x00106848 | |
| +0x5990 | | Smoothed carve input (brake + turn) for board loop C | |
| +0x59B8 | | Per-player smoothed glide input for board loop B | |
| +0x59E4 | int | Boost loop refcount | |
| +0x5FDC | | Live pending-Uber voice handle | PS2 |
| +0x608C | int | Radio mode: 0 Radio BIG, 1 custom playlist + DJ, 2 BIG Mountain Ambience, 3 custom playlist without DJ | |
| +0x6098 | u64 | Custom playlist mask (from the profile; radio modes 1 and 3) | |
| +0x60A0 | float | MUSIC effective volume kept by the big-air update | |
| +0x60A4 | | Cached PLAYLIST.INF section names | |
| +0x623C | | Active MusicTrigger zone (0 = none) | |
| +0x6244 | float | Big-air latched predicted flight time T | |
| +0x6248 | float | Big-air duck start time | |
| +0x624C | float | Big-air duck end time = e + max((landing - elapsed) x 0.5, 0.5) | |
| +0x6254 | int | Travel/intro flag set by 0x0028E8C0(20) and by 0x00234F40 (new-career intro, pktrans playing) | PS2 |
| +0x6258 | | Just-arrived flag (suppresses the first Char_Stories) | |
| +0x6274 | int | Pending music request flag (set by 0x0028E088, executed by 0x0028E100) | |
| +0x6278 | int | Pending music request kind (0 hub song, 1 PlayMusic(0), 2 backcountry/hub, 3 PlayMusic(36), 4 PlayMusic(0)) | |
| +0x627C | int | Run-started flag: GO sends event 0 when set, else event 37 and sets it; cleared between Big Air/Pipe runs | |
| +0x6280 | int | Enables Pathfinder volume writes/ramps; set by 0x0028CF98 only for BIG Mountain ambience (radio mode 2) | |
| +0x6284 | int | Travel destination (written by 0x0028F558) | |
| +0x6290 | int | FE music state (current charsel screen event; 10 = none) | |
| +0x6294 | | Flag that lets PlayMusic run despite the replay suppression 0x00288AE0 | |
| +0x62A4 | int | Previous song index (PickNextSong repeat avoidance) | |
| +0x62AC | int | Playlist index saved before the podium chartune | |
| +0x62B0 | | Sound mode mono flag; mono removes the 3D azimuth | |
| +0x62B4 | | Arcade audio enabled flag (gates ARCADESFX and ARCADESPEECH) | |
| +0x62B8 | | DJ enabled flag (DJ Speech option); when set it also forces MusicTrigger 11 to request kind 0 | |
| +0x62BC | struct[11] | Mixer channel records, 16 bytes each (+0x62BC + 16*ch; 0 master .. 10 ARCADESPEECH): {user volume, user x scale, x duck, x mix = effective} | |
| +0x62C8 | float | Effective volume of mixer channel ch at +0x62C8 + 16*ch (= slider x base scale x duck x mix), read by streams and voices; 0x00287968(audio, ch) returns a pointer to it | |
| +0x636C | float[10] | Per-speaker CHARACTER gains indexed by CHARDB id (in game: moby, kaori, allegra, mac, elise 0.9; zoe 0.8; griff 0.85; nate, psymon 1.0; viggo 0.95; FE 1.0) | |
| +0x6394 | float[11] | Per-channel duck factor | |
| +0x63C0 | | Duck state: active flag | |
| +0x63C4 | | Duck state: channel mask | |
| +0x63C8 | | Duck state: step | |
| +0x63CC | | Duck state: target level | |
| +0x63D0 | | Duck state: current level | |
| +0x63D4 | | Duck state: mode | |
| +0x63E0 | | Speech stream playing state tracked by 0x00285BF8 for the duck release | |
| +0x6414 | float[11] | Mix fade step per channel (per 60 Hz frame) | |
| +0x6440 | float[11] | Mix fade target per channel | |
| +0x646C | int | Current mix index | |
| +0x6478 | int | Number of MIX.INF mix records | |
| +0x647C | struct[25] | MIX.INF mix records, 0x28 bytes each (per-channel levels plus TIME) | |
| +0x6868 | | Per-line speech byte envelope read by 0x00289688; never written in retail (nor is the related +0x6C50) | |
| +0x6C58 | | Enable flag of the inert music-duck gate 0x00289688 (never set in retail) | |

## Music manager

Embedded in SSXAudioSystem at +0x118 (music manager +0x3F0 = audio +0x508, +0x408 = audio +0x520, +0x418 = audio +0x530). Its vtable 0x004838F8 is given at music manager +0x5440 (= audio +0x5558; see the unresolved audio +0x5558 row). Offsets are relative to the music manager.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x124 | char[64][11] | MUSIC.INF section names (max 10 chars), 11 bytes each | |
| +0x3E4 | int | Song count | |
| +0x3E8 | int | Number of songs in the current list | |
| +0x3EC | int | Front-end song count (ADDTOFE; 35 licensed songs, in PLAYLIST order) | |
| +0x3F0 | int | Current song index (= audio +0x508 playlist index) | |
| +0x3F8 | u64 | Playlist mask | |
| +0x418 | int | Song active flag (= audio +0x530); set to 1 by PlaySong; PA cue 0 in 0x002A19D8 forces a song request when it is 0 | |
| +0x41C | int | Last Pathfinder event sent (= audio +0x534); -1 after PlaySong | |
| +0x420 | int[64][5] | Song category membership flags at +0x420 + 0x14*song + 4*cat | |
| +0x920 | int[5] | Songs per category in the current list | |
| +0x934 | char[64][100] | Song TITLE table (getter 0x002B40F0) | |
| +0x2234 | char[64][100] | Song ARTIST table (getter 0x002B4120) | |
| +0x3B34 | char[64][100] | Song ALBUM table (getter 0x002B4150) | |

## Sound manager

Reached as *(SSXAudioSystem+0x118) in audio-logic.md, which conflicts with the embedded music manager at audio +0x118 (see the unresolved audio +0x118 row). Offsets are relative to the pointed-to object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1D8 | | Timer/callback queue and struct-of-arrays sound request records: 0x002ADCA0 posts delayed member-function calls, 0x002ADDE0 cancels by key; volume at +0x1D8+0x38[i], update pmf at +0x1D8+0x40+8i; defaults pitch 100, delay {0,90,50}, volume 127 | |
| +0x1F4 | int | Current sound request slot index | |
| +0x1FC | ptr[] | Per-request position pointer (usually rider +0x110) | |
| +0x214 | ptr[] | Per-request gain pointer (bus effective volume from 0x00287968) | |
| +0x238 | ptr | Request owner rider | |
| +0x25C | | Request player (rider +0x870) | |

## SongInstance

*(SSXAudioSystem+0x520); ctor 0x002B1B98 -> 0x002B1C50 (Pathfinder stream plus async loop overlay).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x30 | int | Pending first Pathfinder event, sent once the stream runs | |
| +0x40 | int8 | Path volume / path level (127 normally); lowered by the big-air duck via 0x002B3C98 | |
| +0x48 | int | Fading-out flag, set by 0x002B2418 | |
| +0x4C | int | Big-air loop request flag (cleared by 0x002B4708) | |
| +0x54 | int | Overlay-level enable flag (always 1 in practice) | |
| +0x58 | int | Song id: 301 charsel, 201 chartune, 1-3 Peak hubs, 101-103 Peak*Amb, 401 pktrans, -1 playlist song | |

## cSongConfiguration

One MUSIC.INF song; 0xAC bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | char[0x20] | PATHDATA (.mpf file name) | |
| +0x20 | char[0x20] | MUSDATA (.mus stream file name) | |
| +0x40 | int | Loop file count | |
| +0x44 | char[0x20] | LOOPDATA (loop bank file name) | |
| +0x64 | int | BeatsPerMeasure (default 4) | |
| +0x68 | int | MeasuresPerBar (default 2) | |
| +0x6C | int | PhrasesPerBank (default 4) | |
| +0x70 | int | BeatsPerPhrase (default 8) | |
| +0x74 | int | PhraseAlign (default 16) | |
| +0x78 | int | DelayCount (default 0; 0 in every retail song, so the async delay/echo does nothing) | |
| +0x7C | int | DelayFeedback (default 90) | |
| +0x80 | int | DelayTime (default 100) | |
| +0x84 | int | DelayLevel (default 50) | |
| +0x88 | int | PathLevel % (default 100); scales the main stream volume | |
| +0x8C | int | AsyncLevel % (default 100) | |
| +0x90 | float | BPM (default 120.0) | |
| +0x94 | int | DUCKTOLOOPS (default 1): allows the big-air loop overlay; read via 0x002B4878 | |
| +0x98 | int | SEDVALUE (default -1): DJ artist-intro selector; s < 0 or 999 generic intro, s < 100 DJ_Artist_Intro tag s, s >= 100 DJ_Artist_Intro_2 tag s-100 | |
| +0x9C | int | LOWPASS (default 0xFFFF = open); retail values 30000-42000 all mean no filter | |
| +0xA0 | int | PREVIEW (default -1): charsel event sent for a Request Line preview | |
| +0xA4 | int | SONGBIG (default 1; 1 or 2 = MUSIC.BIG / MUSIC2.BIG) | |

## Pathfinder slot

0x00517610 + 0x928*i.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0xC | int | Service margin for callback reason 0x20: 50 ms (events processed first) | |
| +0x10 | int | Service margin for callback reason 0x42: 10 ms (voices only) | |
| +0x30 | int | Slot/track id = (1 << 24) << mpf[0xC] \| (1 << 28) << instance | |
| +0x34 | ptr | Loaded .mpf data | |
| +0x38 | ptr | Node offset table (u16 per node, x4) | |
| +0x3C | ptr | Node data pointer | |
| +0x40 | ptr | Event offset table (u16 per event, x4) | |
| +0x44 | ptr | Event data pointer | |
| +0x48 | ptr | Router table (u32 x (routers+1); router k = u32 pairs from R[k-1]*4 to R[k]*4) | |
| +0x4C | ptr | Track table (u32 x (tracks+1)); samples of track t = T[t]*4 .. T[t+1]*4 | |
| +0x50 | ptr | Sample table (8 bytes per sample: u32 value, u32 duration_ms) | |
| +0x54 | ptr | End of the .mpf data (T[tracks]*4) | |
| +0x58 | ptr[] | Voice per track (0x110-byte Pathfinder voice objects) | |
| +0xBC | s16[16] | Pathfinder registers (saved bars/sections) | |
| +0xDC | | 16 pending event copies (event queue) | |
| +0x91C | int | Pending event count | |

## Pathfinder voice

Pathfinder slot +0x58[track]; 0x110 bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x1 | u8 | Branch value ('intensity') compared with the branch lo/hi; set by 0x003D0D70 | PS2 |
| +0x2 | u8 | Previous branch value | |
| +0x4 | u8 | Level % (default 100); latched by each slice at its start (% x 0.01 x +0x34) | |
| +0x20 | u32 | Bitfield: bits 0-3 loop counter, 4-8 slice, 14-18 queue size, 19-23 write index | |
| +0x24 | int | Latency ms (500 main stream, 10 loop track) | PS2 |
| +0x2C | | Loop node | |
| +0x2F | u8 | Sync flag (latency < 50) | |
| +0x30 | | Current part head node | |
| +0x34 | s8 | Volume scale (127); target of op 0x06 ramps and op 0x09 | |
| +0x36 | s16 | Last committed node (register save value -33) | |
| +0x48 | int | Next slice time (following master beat) | |
| +0x54 | ptr | EA stream | |
| +0xFC | | Queue ring of committed segments | |
| +0x10C | int | Pending start time of the next slice (master beat, rounded down to 10 ms) | |

## Pathfinder .mpf header

Loaded by 0x003D2350.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | u8 | Version (4); the u16 at +0x6 is 0x08B0 for songs, 0x063C for ambiences | |
| +0xC | u8 | Byte used in the slot id ((1 << 24) << mpf[0xC]) | |
| +0xD | u8 | Track count | |
| +0xE | u8 | Section count | |
| +0xF | u8 | Event count (events >= count are ignored) | |
| +0x10 | u8 | Router count | |
| +0x11 | u8 | Variable count (0 in every song) | |
| +0x12 | u16 | Node count | |
| +0x20 | u16[] | Node offset table (offset/4 per node), followed by node data, event offsets, event data, routers, tracks and samples (all offsets x4) | |

## Pathfinder .mpf node record

16 bytes plus 4 per branch.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | s16 | Sample: 1-based global index into the sample table; 0 = part head, -1 = part end (loop counter), -2 random, -3 post event | |
| +0x2 | u16 | Flags: bits 0-4 track (voice index), 5-10 section, 12-15 loop count of an end node (1-7 count down; 0xF/12/13 endless) | |
| +0x4 | u32 | Bits 0-7 router (1-based), 12-16 branch count, 17-19 == 1 random branch value, 20-23 measures, 24-27 beats per measure | |
| +0x8 | u32 | Bits 0-7: 0x40 on audio nodes; 8-9 sync mode of a part head (0x100 only); 10-14 event posted by a part head (unused); 20-31 part head index (audio nodes) | |
| +0xC | u32 | Bit 1 = sliced (one beat per master beat, bank entry value + slice - 1); bit 0 unused | |
| +0x10 | struct[] | Branches, 4 bytes each {s8 lo, s8 hi, u16 target}; lo/hi compared inclusively with the voice intensity; target 0xFFFF = stop | |

## Pathfinder .mpf event head

16 bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | | Runtime time (with +0x8) | |
| +0x8 | | Runtime time | |
| +0xC | u32 | u16 id; bits 16-21 action count, 22-27 runtime action index, bit 29 = disabled | |

## Pathfinder .mpf event action

16 bytes.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x0 | u8[3] | Track mask (1 = stream, 2 = loops); byte 3 (0xF1/0x1F) is AND-ed with the slot id high byte | |
| +0x4 | u32 | Timeout (0 in retail) | |
| +0x8 | u8 | Runtime flags (bit 26 of the word = done) | |
| +0x9 | u8 | Opcode (0x02 wait, 0x04 jump, 0x06 ramp, 0x0A save register in retail data) | |
| +0xC | s16 + 2 bytes | Operand: s16 value (node / register / ms / target); bytes 14-15 arguments (section, flush, curve, duration) | |

## MicroTalk decoder context

Stream voice decoder context (used by 0x003C9960).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x14 | float[] | Synthesis history (read by a first-subframe pitch lag > 216) | |
| +0x114 | float[] | Reflection coefficients | |
| +0x144 | float[] | Last fixed gains | |
| +0x684 | float[432] | Live decoded frame buffer | PS2 |
| +0xD44 | int | Position in the current frame; reset to 0 when a new block opens (dropping a partly used frame); with +0xD54 selects the current decoded frame | PS2 |
| +0xD54 | int | Voice position; with +0xD44 selects the current decoded frame | PS2 |
| +0xD5C | int | First-block flag (bit 31 of the block count word from 0x003B6EA8): set = first block of the SCHl, parse the header and reset state; clear = decoder state carries across blocks | PS2 |
| +0xD64 | int | EA wrapper / MicroTalk mode: 1 = flag bytes, PCM patches and byte re-alignment; 0 = plain MicroTalk (0 when stream tag 0x80 < 3, as on retail streams) | PS2 |

## Stream voice object

EE sound voice (IOP-mixed stream voice); also called audio stream voice object.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x30 | int | Voice type / MicroTalk mode = stream tag 0x80; 2 on every disc stream = MicroTalk stream voice, plain MicroTalk | PS2 |

## EE audio stream object

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x24 | int | 'Not the first block of this SCHl' flag (source of bit 31 for SCDl blocks) | PS2 |

## SCDl stream chunk

Handled by 0x003B6EA8.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x8 | u32 | Samples in this chunk | |
| +0xC | u32[channels] | Per-channel data offsets, relative to the end of this offset table. EA-XA channel data starts with a 4-byte prefix (ignored); MicroTalk data with one skipped byte (01 in the first block, 00 after) | |

## BNKl v5 bank header

Parsed by 0x003BAAC0.

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x4 | u8 | Version (5) | |
| +0x5 | u8 | Flags | |
| +0x6 | u16 | Entry count | |
| +0x8 | u32 | Header size = start of sample data | |
| +0xC | u32 | SPU (VAG) data size | |
| +0x10 | u32 | Main-RAM (IOP/EE-decoded) data size | |
| +0x14 | u32[count] | Per-entry PT header offset, relative to the slot itself (0 = empty) | |

## Events.evt (speech event file)

Event record: u16 id, +2 u16 W (max wait), +4 u16 P (priority), +9 chance %, +0xE u16 record count, then records (condition = argument index + mask; u32 bank ids = .hdr u16 id).

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x10 | | Event count (59); u16 offsets (x4) follow at +0x18 | |

## SFX voice

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x64 | | Voice volume written by the per-voice update callbacks | |

## UI sound listener

| Offset | Type | Meaning | Evidence |
|---|---|---|---|
| +0x14 | vslot | Listener virtual +0x14(kind) plays a UI sound kind | |
