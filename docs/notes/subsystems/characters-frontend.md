# Characters and front end

SSX 3 has ten selectable riders, described by `DATA/BE/CHARDB.DBL`, and twenty cheat characters that are worn as
skins over a chosen base rider. The front end is a set of `FE.LUI` screen states (Select Character, Setup
Character, Rider Details, Equip Gear, Options and their sub-screens) that read and write a per-rider profile
record: attributes, gear inventory, uber-trick choices, cheat unlocks, rider relationships and a message inbox. A
3D preview rider with cinematic head and hands is shown on several screens, and each event load plays one of the
`GL.LUI` loading screens.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

Hex constants that are not addresses (hashes, masks, flags, sizes, strides) are written with an `h` suffix, e.g.
`0CA31FA2h`. Skeleton compile, bone masks and front-end clip timing are in animation.md; the roster random draws
are in random-streams.md; attribute getters, awards, rewards and the career economy are in game-flow.md.

## Where it lives

Translation units per the current decomp split:

- `src/fe/festatecharselect.cpp`: Select Character (`0x00181148` (`cFEStateCharSelect_onCreateScreen`),
  `0x00181620` (`cFEStateCharSelect_onWidgetCreate`), input `0x001817E8`, stats `0x00181BD0`, preview placement
  `0x00181EF0`) and Cheat Characters (`0x00182220`, `0x00182488` (`cFEStateCheatCharSelect_onWidgetCreate`)).
- `src/fe/festatecharsetup.cpp`: Setup Character (`0x00182928` (`cFEStateCharSetup_onCreateScreen`), input
  `0x00182C80`).
- `src/fe/festateriderbio.cpp`: Rider Details (`0x001832A8` (`cFEStateRiderDetail_onCreateScreen`), `0x00183550`,
  input `0x00183710`). `src/fe/festateriderbiodetail.cpp`: Rider Profile (`0x001908C0`
  `cFEStateRiderBio_onCreateScreen` and its `fillDNAInfo`/`fillFavesInfo`/`fillQnAInfo`/`fillBioInfo`).
- `src/fe/festatestore.cpp`: Ubertrick Setup (`0x001849B0`, trick preview `0x00184C60`, `0x00185080`
  `cFEStateUberTrick_onWidgetCreate`).
- `src/fe/festatecharequipdetail.cpp`: Equip Gear (`cFEStateCharEquip_*` from `0x00198DB8`, input `0x00199A38`
  and `0x00199C28`, lists `0x0019AFD0`/`0x0019B180`, bars `0x0019BC90`/`0x0019BD48`, Cross `0x0019BEE8`, preview
  update `0x0019BFE8`).
- `src/fe/feridermanager.cpp`: the front-end preview riders (`0x0019E960` (`cFERider_init`), lighting `0x0019EE88`,
  board placement `0x0019F548`, speech poll `0x001A0358`).
- `src/fe/festatelegal.cpp` (per the current split): the Enter Cheat handler `0x00187D38` and the Options state
  `0x001887A0`. `src/fe/festatecredits.cpp`, `src/fe/festateprofile.cpp` (Load game), `src/fe/festaterewards.cpp`
  (rewards room, movie player), `src/fe/festatebonusmaterial.cpp` (Previews), `src/fe/festatelodge.cpp` (lodge
  Rider Details), `src/fe/festatebigradio.cpp` (the menu-item enable helper `0x00194498`).
- `src/fe/fepopup.cpp`: `cKeyboardPopup` (`0x001CB030`, `0x001CB1A0` (`cKeyboardPopup_onCreateScreen`), key enable
  `0x001CE3C8`). `src/fe/fepopupmisc.cpp`: `cFEPopupScreenPos` (`0x001DEE10`, `0x001DF050`
  `cFEPopupScreenPos_onUpdate`) and the career message posters `0x001E1550`..`0x001E4F80`.
- `src/fe/ovstatehud.cpp`: the in-race mail icon. `src/fe/festateloadhint.cpp`: `0x00245950`
  (`cFELoadHintState_onCreateScreen`). `src/main/loadscreens_prestart.cpp`: load-screen selection `0x00232E20`.
  `src/main/ssxappdtor.cpp` (per the current split): the load-state enter functions `0x00245418`, `0x00245730`.
- `src/be/beintstat.cpp` (CHARDB load, inside `0x00149BB8`), `src/be/belibrary.cpp` (setup-slot getters
  `0x0014A080` (`cBELibrary_getCharacterID__Fi`)/`0x0014A0B0`, equip wrapper, item weights, texture rule, race
  outfit), `src/be/beintecon.cpp` (gear inventory), `src/be/beintbagt.cpp` (uber rows),
  `src/be/beintcharacter.cpp` (model scale `0x0014EFA8`, `0x0014EF30` (`cBECharacterInterface_getWeight__FPvi`)),
  `src/be/beintnetwork.cpp` (name getter `0x0014EEC8`, per the split), `src/be/beintaggression.cpp`
  (relationships), `src/be/beintreward.cpp` (owned cheat count `0x001577A0`), `src/be/beintplayer.cpp` (player
  name, inbox bits), `src/be/beintoption.cpp` (options reset).
- `src/ai/rider.cpp`: race outfit collection and textures (`0x0011BBE8`, `0x0011BE88`, `0x0011C138`,
  `0x0011C298`) and the pad rumble model `0x00125B18`.

## Globals

| Address | Meaning |
|---|---|
| `0x00530970` | CHARDB rows, 10 x `88h` |
| `0x00534FE0` | setup slots, `1Ch` each: `+0x11` base character (`0x0014A080`), `+0x12` cheat id (`0x0014A0B0`) |
| `0x00535538` | attribute bytes: bank x 70 + character x 7 + k (decimal strides; see game-flow.md) |
| `0x00535B20` | race copy of the participants (written through `0x002342B8`) |
| `0x00535B30` | race copy `+0x10`: 1 selects the Pro controller map (see "Options read by the race") |
| `0x00535610` | options word: bit 19 = km/h, bits 30..31 = HUD level (other bits in audio.md and camera.md) |
| `0x00535615` / `0x00535616` | screen position y / x, signed bytes |
| `0x00535C10` / `0x00535C11` | event type / game type (0 = Conquer the Mountain), as in game-flow.md |
| `0x005305F9` | 0 only in Conquer the Mountain (1 in every Single Event state) **(PS2)** |
| `0x004A6CA8` | profile banks, `9B50h` each; a character record is `F88h` (next section) |
| `0x004A6750` | runtime item database loaded from `BOLTPS2.DAT` |
| `0x004A28A8` (gp-0x848) | game object G; the FE preview slots hang off `*(G+0x7C)` |
| `0x004A2C38` (gp-0x4B8) | load-hint counter byte, starts at 0 |
| `0x004A18D8` (gp-0x1818) | outfit item limit, 3392 |
| `0x004A11E0` (gp-0x1F10) | item id of the Boards folder (3) |
| `0x004A19D8` (gp-0x1718) | flag that forces the out-of-lodge loading screen |
| `0x00440F68` | Select Character order, `[4,0,8,5,9,6,7,3,2,1]` |
| `0x0043FA38` | 8-character short names of the cheat characters, id x 8 |
| `0x0045A660` | jump table of `0x0014EFA8` giving cheat-character model scales |
| `0x00530600` | trick score table (begin/hold points by score id) |

## Character roster

### CHARDB.DBL

`DATA/BE/CHARDB.DBL` holds 10 rows of `88h`; the loader at `0x00149C84` (inside `0x00149BB8`) copies them to
`0x00530970`. The row index is the character id used everywhere (0 = Moby ... 9 = Viggo; 3 = Mac, 4 = Zoe).

| Offset | Field |
|---|---|
| +0x00 | long name |
| +0x20 | first name |
| +0x30 | nickname |
| +0x40 | weight (read by `0x0011FF98` (`cRider_getMass`) for rider-pair collisions) |
| +0x44 | stance, 1 = goofy |
| +0x48 | model size; body scale = size x 0.01 |
| +0x4C | blood type |
| +0x5C | female flag |
| +0x60 | age |
| +0x64 | height |
| +0x74 | nationality |

Nate's live body scale (geometry `+0x140`) reads 0.99999994 while cheat characters at 1.0 from `0x0045A660` are
exactly 1.0 **(PS2)**; this fits size 100 x 0.01 computed in single precision (inferred).

Text keys: the display name is `kT_CHAR<Name>` (CMNAMER, getter `0x0014EEC8`), the Select Character card text is
08sel_char widget `69020h` + screen index, the bio is `kT_FULLBIO1<Name>`, the DNA page `kT_DNA1..8<Name>`.
Model files are `MDLPS2.BIG` members named by an internal prefix; four riders use a prefix different from their
display name (e.g. Allegra's files are `arielle_*`). Textures are `DATA/CHAR/<PREFIX>TXP.BIG`. When a live part is
matched against its `MDLPS2.BIG` header, bytes 56..67 of the header are runtime fix-ups **(PS2)**.

The Select Character order table `0x00440F68` starts with Zoe (4) and ends with Kaori (1); Left on the first
entry wraps to the last **(PS2)**.

### Cheat characters

There are twenty cheat characters, ids 10..29 (e.g. 10 = Brodi). They are never Select Character entries: each
is a skin worn by the chosen base rider.

- The setup slot keeps both: `+0x11` the base character, `+0x12` the cheat id. Confirming a rider on Select
  Character clears the cheat.
- Gameplay (stats, stance, weight, uber table, bio) comes from the base rider; the model, texture set, scale and
  skeleton come from the cheat character **(PS2)**. The two stance-dependent start values follow the base: the
  air-entry pivot x changes sign and the grid seed uses the base's reverse stance **(PS2)**.
- Picking one: Setup Character > Rider Details > Cheat Characters (`131cheat_char`, hash `006AA322h`, state
  `cFEStateCheatCharSelect` at `0x00182220`). The list is the base rider's face first, then the owned cheat
  characters in id order, in six face slots with the focused face enlarged and a name bar. The Rider Details item
  is enabled only when `0x001577A0` (owned cheat count of the base rider) is above 0.
- Unlock bits: character record `+0xF57`, bit (id - 10), kept per base rider. All are zero on a fresh profile
  **(PS2)**.
- Unlock sources: three are sold for $20,000 in the Peak 1 lodge and four for $40,000 in the Peak 2 lodge; four
  come from completing a collectible category (cards, toys, posters, art); the rest from awards and Peak 3 goals
  (see game-flow.md, "Rewards, awards").
- Enter Cheat (Options > Enter Cheat, handler `0x00187D38`): the typed text is lowercased and hashed with
  `0x00317670` (`GetHashValue32__FPc`) and compared with constants in the handler. There are 15 codes, each
  unlocking one character for all ten riders of profile 0 (e.g. `zenmaster` = Brodi), plus one more constant
  (`0DD36D88h`, Canhuck) whose text is not recovered. Four characters have no code. There is no all-characters
  code.
- Names come from the `RWRDPS2.DAT` catalog; `0x0043FA38` + id x 8 holds 8-character short names (HUD, records).
- Model scale: `0x0014EFA8` uses the jump table `0x0045A660` (e.g. Brodi 0.98, Stretch 1.2, the largest 2.0) and
  the CHARDB scale for ids below 10 **(PS2)**. In Conquer the Mountain (`0x00535C11` == 0) it returns the base
  rider's CHARDB scale even for a skin (from the code only; not captured).
- Uber overrides: `0x00150198` / `0x001502C8` / `0x001503F8` return a skin's own entry first. Three skins replace
  the Nose Grab uber (semantics 159, 160, 161) and one the Tail Grab uber (162).

The "Tricky" cheat characters used as computer riders are ids 10..16 (see "Computer-rider lineups").

### Per-character live values (PS2)

Read from the human rider of one derived countdown state per character:

- Body scale = CHARDB size x 0.01 for the riders (Zoe 0.85, Griff 0.70, Nate 1.00) and the `0x0045A660` value for
  the cheat characters.
- Channel-1 mask `+0x8C0` is bones 1..15 plus one high bit; Zoe `8000FFFEh`, Moby `20000FFFEh`, Psymon
  `4000FFFEh`. Zoe's three masks are `8000FFFEh` / `8000FFF8h` / `870h` (animation.md).
- Race skeletons have 24 to 29 bones.
- Values that differ between characters: body scale (landing body scale, animation scale), air-entry pivot, uber
  table rows, stance (trick identity, reset stance), bone mask, default mirror and root rotation, variant flags,
  secondary motion (hair) and contact legs.
- The human's countdown ground state is a function of body scale and base stance only: position, normals and the
  forward/lateral offsets follow the scale, reverse stance follows the stance, and the presentation lift fits
  (0.85 - scale) x 90 - 1.5. Riders of equal scale share a spot (Mac, 0.85, sits exactly on Zoe's; Nate at
  0.99999994 is 1.5 mm from the 1.0 riders).

### Select Character stats

`0x00181BD0` fills the seven stat rows from the raw attribute bytes at `0x00535538` + player x 70 + character x 7.
Rows NumAttr0..6 (Acceleration, Edging, Speed, Spin, Stability, Toughness, Tricks) read bytes 1, 3, 0, 4, 6, 5, 2.
Each is shown as raw x 0.2 with `"%.1f"`, bar fill raw / 55. The rider ranking is (sum - sum % 5) / 35, and its
bar is filled from sum / 7. On a fresh profile every raw value is 5 (the limit table `0x005308D8` holds 11), so
every rider shows 1.0 everywhere **(PS2)**.

## Profile records per character

A character record is R = `0x004A6CA8` + bank x `9B50h` + character x `F88h`. Bank 0 is the human's profile;
bank 2 holds the computer riders' values (attributes at raw 20 there, relationships). Single Event and Conquer
the Mountain use the same profile-0 record. Banks 1 and 2 live in RAM from power-on.

| Offset | Content |
|---|---|
| +0x278 | event lock / pass bits (game-flow.md); bit 12 clear = Peak 2 pass |
| +0x288 | gear item -> row lookup |
| +0x28C | gear row count |
| +0x290 | gear rows {s16 item, u16 flags}: `2h` owned, `4h` committed, `10h` equipped, `20h` default |
| +0xBC1 + other x 3 | relationship record about rider `other`: {kind, level, score} |
| +0xE38 | inbox, 25 x {item, variant} |
| +0xF00 | inbox read bits (a new message clears its bit) |
| +0xF04 | inbox count |
| +0xF08 | posted bits, one per message category (test `0x00147980`, set `0x00147A30`) |
| +0xF57 | cheat-character unlock bits, bit (id - 10) |

### Relationships (PS2)

- `0x00155E58` (called by the event setup at `0x00233F20` inside `0x00233CD8` and `0x002348AC` inside
  `0x00234750`) ages every participant's ten records at each load and each restart:
  - score = max(score - 3, 0), level = score / 5;
  - kind 3 at level 0 becomes kind 1, level 3, score 15 (a fresh nemesis record 03 02 00 steps 01 03 0F ->
    01 02 0C -> 01 01 09);
  - kind 1 at level >= 4 becomes kind 3, level 2, score 10; kind 0 at level >= 3 becomes kind 0, level 2,
    score 10;
  - kind 2: level <= 0 becomes level 1; level >= 4 is capped at level 3, score 15;
  - kind 3 at level >= 5 is capped at level 4, score 20.
  - A character raced twice in one bank ages twice.
- `0x00155BF0`, in the race: `0x00107E70` -> `0x0010E228` / `0x0010E2E8` / `0x0010E3A8` / `0x0010E468` add 1, 2,
  4 or 6 (soft bump, crash, soft attack, crash attack) to the other rider's record about the one knocked, with the
  same kind rules (kind 2 or 3 at level <= 0 becomes level 1, score 5). A level change feeds the pair refresh
  `0x0010F560` (rival flag at level >= 2, designated peer at 4) and the computer riders' attacks `0x0010DBF0`
  (level >= 3). `0x00155AB0` returns the kinds and `0x00155B50` the records.
- Both call the relationship notice `0x001E2A08` (see "Career messages").

### Player name and options

- Player Name (Rider Details) stores a non-empty name through `0x00147138`; a fresh profile's name is `PLAYER1`
  **(PS2)**. It is shown on Load game.
- The screen position bytes `0x00535615` / `0x00535616` are zeroed by the options reset at `0x0014F5D0` (inside
  `0x0014F4F8`).

## Front-end screens

### LUI screens

All screens are `FE.LUI` screens driven by the FE state code. What the code relies on:

- Coordinates are a 640x480 frame. Each element has a frame-0 state and timeline events with their own start
  frames; groups and menus carry offsets; there are gouraud shapes, line loops, bars (fill = value / max) and
  FEFONT text boxes (element kind `20h`, wrapping). Option rows are element kind `15h` (label + value widget).
- Menus: each item has a focus state (frames 35 + 5i on most screens; 140audio uses 31/36/41/46/50) that turns
  its text white, moves the orange bar and shows its help text. Up/Down wrap and skip disabled items **(PS2)**.
  A disabled item is drawn at alpha 96 by `0x00194498` (0.37 measured on the frame **(PS2)**).
- Widget events: Cross = 5 (passes the item index to the flow), Triangle = 6 (back), Square = 7. A change of
  screen plays the white fade (whitefade, `TransitionOut` state).
- Arrow flashes are the hll / hlr states; the always-on snowflake screen loops every 600 frames.

### Screen table

| Screen | FE.LUI | Hash | Code | Items |
|---|---|---|---|---|
| Select Character | 08sel_char | | `cFEStateCharSelect` | ten riders; Square Options, Circle Load game |
| Setup Character | 09set_char | `0CA31FA2h` | `0x0018293C` in `cFEStateCharSetup_onCreateScreen` | Continue, Equip Gear, Rider Details, Music |
| Rider Details | 154rider_details | `0B32CE73h` | `0x001832BC` in `cFEStateRiderDetail_onCreateScreen` | Rewards, Cheat Characters, Ubertrick Setup, Player Name, Rider Profile |
| Lodge Rider Details | 155rider_details_conquer | `0FFAD5A2h` | `0x001F4064` in `0x001F4050` (`cFEStateLodgeRiderDetail_onCreateScreen`) | adds Trophies and Career Highlights |
| Rider Profile | 14rid_prof | `0FA0EE56h` | `0x001908D4` in `cFEStateRiderBio_onCreateScreen` | pages Rider DNA / Faves / Q&A / BIO |
| Music | 140audio | `0768BC7Fh` | `cFEStateAudioOptions` | Radio BIG, ambience, custom playlist (DJ / no DJ), Edit Playlist |
| Options | 18options | `067AAFB3h` | `0x001887A0` | Game, Sound, Controller, HUD, Save/Load, Enter Cheat, Credits, DONE |
| Load game | 93profile_load | `06488254h` | `0x0018EDDC` in `cFEStateProfileLoad_onCreateScreen` | rows 1..6: `player%d`, `date%d`, `time%d` |
| Ubertrick Setup | 66ut_btnmap | `05E8EAC0h` | `0x001849C4` in `0x001849B0` | Mute, Indy, Stalefish, Method, Nose Grab, Tail Grab, DONE |
| Keyboard | Fullkeyboard | `05413EA4h` | `cKeyboardPopup` `0x001CB030` | over Player Name and Enter Cheat |
| Game Options | 19game_opt | `083DF9D4h` | `cFEStateOptionsGame` | Speed units, Widescreen, Screen position, Video calibration |
| Controller | 22control | `0A65D25Ch` | `cFEStateOptionsController` | Vibration 1P/2P, Controller 1P/2P (Default / Pro) |
| HUD Options | 21hud_opt | `0FBA4C94h` | `cFEStateOptionsHUD` | Full / Minimal / None |
| Sound | 141advsettings | `0255B2C3h` | `cFEStateOptionsSound` | (audio.md) |
| Credits | 26credits | `0A8BDB33h` | `0x00185AAC` in `cFEStateCredits_onCreateScreen` | credits roll |
| Screen position | 24screen_position | `0746461Eh` | `cFEPopupScreenPos` `0x001DEE10`, vtable `0x0046B230` | popup over Game Options |
| Rewards | 128rewardsroom / 129 rewardgallery / 130rewardposter | `034B045Dh` / `0C495039h` / `046FCA42h` | `cFEStateRewardsRoom` | categories, gallery pages, one reward |
| Main menu | 07main_men | `08065FDEh` | | Single Event, Conquer The Mountain, Previews, Online, Multi Play |
| Previews | 146Bonusmat | `063496A4h` | `cFEStateBonusMaterial`, input `0x00195600` | three trailers |
| Save/Load | 25saveload | `08CE8C54h` | | Save game, Load game, Save options, Load options, Load replay, New game |
| Track selector | Map / femap_template | `00005380h` / `0437FEC5h` | | Select Peak, Select Mode, Select Event |

Other names in the data: `122Autosave`, `86multiplayermode`, `16radio` (Edit Playlist), the FE.LUI Yes/No
`popup` (`007767C0h`).

### Select Character (08sel_char)

- Timeline: the intro (dashes slide in, stats fade in, frames 1..25), the focused rider's state at frame
  40 + 5i (name, orange silhouette, card), the arrow flashes, and a white flash on Cross before Setup Character.
  Layers 0..9 (sky, mountains, snow, white ramp, frame, the big "3") are behind the 3D rider; layers 10+ are in
  front. The 2-player title is hidden.
- The roster row is flat silhouettes (page FE_1-20): a white strip (`00A79FCCh`, layer 9) and one orange
  (194,76,0) highlight per rider (layer 12), drawn at 130% x 110% with group offset (-4,12), feet on one line.
- `cFEStateCharSelect_onWidgetCreate` and `0x00181BD0` fill the names, the seven stats, the ranking and the bars.
- Cross (`0x0018185C` inside `0x001817E8`) sets the preview slot's `+0xC20` flag (rider speech, below).
- The right stick turns the preview rider 3 degrees per frame.

### Setup Character (09set_char)

- Widgets `Option_Continue`, `Option_Equip`, `Option_Rider`, `Option_Radio` = 0..3; `Option_GBA` is hidden. All
  four are enabled (`0x00182AA8`..`0x00182BD8`). Continue goes on to Select Peak; Music opens 140audio.
- Square opens Options on Setup Character (`0x00182D58` inside `0x00182C80`) and on Rider Details (`0x00183A2C`
  inside `0x00183710`).
- The 3D preview is visible behind layers 0..9 as on Select Character. Entering Setup Character or Rider Details
  restarts the cheer clip (animation.md); the model is hidden for a short window (slot `+0xCC8` = 0) on each entry,
  about 26 frames after the Select Character flash and 30 between Setup and Rider Details **(PS2)**.

### Rider Details (154rider_details)

- `Option_1..5` = widgets 5..9. Cheat Characters is disabled by `0x00183550` through `0x00194498` unless the base
  rider owns a cheat character; with it disabled, Down from Rewards skips it and Up from Rewards wraps to Rider
  Profile **(PS2)**.
- The frame group has A = 0 in the screen's own data, yet the PS2 shows it, so code must enable it (where is
  unconfirmed).
- Player Name (`0x00183764` inside `0x00183710`) opens `cKeyboardPopup` with the current name, focus on Done,
  maximum 15 characters, and Tab and the punctuation keys disabled by ten calls to `0x001CE3C8`; Up/Down are
  always dim.
- The lodge variant (155rider_details_conquer) has the same states and help texts and the lodge's item rules.

### Rider Profile (14rid_prof) (PS2)

Opens on Rider DNA; Left/Right cycle DNA -> Faves -> Q&A -> BIO with wrap and flash the pressed arrow; Down, R1 and
L1 do nothing. Texts: `kT_DNA1..8`, `kT_FAVES1..12`, `kT_QNA1..4` and `kT_FULLBIO1`, each suffixed with the first
name. The code shows one page's groups and hides the others. The BIO text box wraps at 440 with a 17.5 px pitch
(measured). There is no 3D rider on this screen, Music, Options or Load game.

### Ubertrick Setup (66ut_btnmap)

- Each category shows "Hold <button> for 1 second while in air": Mute L2, Indy R2, Stalefish R1, Method L1, Nose
  Grab L1+L2, Tail Grab R1+R2 **(PS2)**. Cross opens the category list (check = selected, box = owned, `$` =
  locked, with Cost / You have for the focused row). The list opens on its first row and wraps **(PS2)**. Buying
  is only possible in the lodge. Uber tables and prices are in game-flow.md.
- The in-race grab profile has two uber rows per category: set 0 is the rider's hidden base uber, set 1 the
  selected one. A row is {semantic = trick id A, upper semantic = trick id B, score id = the entry's name index,
  begin/hold points from `0x00530600` by score id}; `0x00150198` / `0x001502C8` / `0x001503F8` read the same list
  entry. This reproduces all 12 of Zoe's rows **(PS2)**.
- Trick preview **(PS2)**: the preview slot shows the rider on the board. Camera eye (0,660,80) looking at
  (0,0,80), 25 degrees (`0x00184A78` inside `0x001849B0`); root (-228,-205,63) cm, turned 62 degrees about Z
  (`0x00184D08` inside `0x00184C60`, half-angle constant 31 degrees at `0x0049D700`, gp-0x59F0); the board is not
  moved away. `0x00184C60` (vtable `0x0046CCC8`) loops semantic 436 `FE_A_CYC`; Square plays the focused uber by
  setting the animator's semantic to its trick id A (animator `+0x8` = `7Bh` for Indian, `9Eh` for Pommel Me).
  The FE variant comes from the runtime table at `*(0x004A3DFC)` (gp+0xD0C): FE clip index = trick id - 93,
  113..148 = `UBER_<GRAB>_<n>_L<k>`, 149..158 = `UBER_TAIL_<PREFIX>` / `UBER_NOSE_<PREFIX>`. It plays once, then
  crossfades back into `FE_A_CYC` over 0.23 s.

### Options (18options) and sub-screens

- All eight items are enabled (the state makes no enable calls). Enter Cheat opens the keyboard empty, focus on
  `q`, with only Tab/Up/Down disabled. Leaving Options asks "Would you like to save your Options?" in the FE.LUI
  popup; No keeps the changes for the session, and the race uses them **(PS2)**.
- Game Options: Language and Auto save are hidden on the US build **(PS2)**; Video calibration opens a popup
  (probably `cFEPopupVideoCalibration`, unconfirmed).
- HUD Options shows a picture per state (FE_1-15/16/17).
- Screen position (`cFEPopupScreenPos`, "Position the screen to fit your TV."): D-pad Right/Up add 1, Left/Down
  subtract 1, clamped to -20..20, pulsing the pressed arrow (states `hl left/right/up/down` at frames 80/85/70/75);
  Cross keeps, Triangle restores. The popup applies the display live through vtable `+0x60` = `0x00393FB8`. The
  NTSC display set-up at `0x00382DC0` (inside `0x00382AF0`) turns x / y into DISPLAY DX = 636 + 5 + 8x VCK (2560
  per line) and DY = 50 - 2y (of 480 lines), so one step is 1/320 of the width right or 1/240 of the height up.
  **(PS2)**: 10 Up presses raise the picture 20 lines, 2 per press.
- Credits: 160 `kT_CREDITS*` strings of CRAMER.LOC, in the order `cFEStateCredits_onGainFocus` references them
  (`0x00185C54`..`0x00185F04`). A doubled backslash breaks a line and a leading `^` marks a heading. The roll is
  centred and scrolls up 1 px per frame inside the TextScroll box (62,95,525,300), followed by the Dolby bitmaps
  (Bitmap0000/0001); the heading/name sizes and gaps were fitted to the PS2 roll **(PS2)**.

### Load game and the keyboard

- Load game dates are formatted by `0x002C7038` as `%02d:%02d:%04d` (month first) and times by `0x002C6F78`
  (`cConsoleConfig_setTimeString`) as `%02d:%02d:%02d` (24-hour). Without a memory card the screen asks for one in
  MEMORY CARD slot 1 **(PS2)**.
- Fullkeyboard uses its frame-45 layout; the key labels are set by code and the focused key is drawn opaque black
  **(PS2)**. L1 is labelled Shift and R1 Caps.

### Rewards room, videos and Previews

- Categories show owned / total for the rider. A gallery page holds 8 x 4 slots ("Page n/m", L1/R1 when there are
  more pages); unowned slots show `questmark` boxes (full brightness on the focused slot, level 151 elsewhere
  **(PS2)**), owned ones their thumbnail (cheat characters their face), with label, name, You have / Cost and the
  help "Buy this item in Conquer the Mountain mode." Cross on an owned item shows it in 130rewardposter.
- An owned video plays full screen through the MoviePlayer state `0x001D23E0` (object named `MoviePlayer`); the
  sound system is paused (`0x002B3A70`) and the state returns to the gallery (`0x001D2638`) at the end or on the
  skip buttons (`0x001D2518`). The two reward videos are `DATA/MOVIES/INTRO.MPC` and `MTNALIVE.MPC`.
- Previews (146Bonusmat) plays `DATA/MOVIES/NFSXSELL.MPC`, `NFLXSELL.MPC` and `ST3XSELL.MPC` from the path table
  `0x00441128`.
- `.MPC` files are EA SCxl chunk streams: `MPCh` chunks hold one MPEG-2 access unit each (512x448, 29.97 fps);
  `SCHl` is a `GSTR` audio header (44000 Hz; INTRO has 6 channels L C R Ls Rs LFE, MTNALIVE is stereo; INTRO_DJ.MPC
  differs from INTRO only in channel 1, the DJ voice); `SCDl` chunks carry one EA-XA R3 block per frame. The GSTR
  header has no revision element.

### Main menu and Single Event track selector

- 07main_men: intro to frame 21, focus states 35/40/50/60/70 (white text, orange `hl` bar, help text in the left
  panel). Square opens Options per the legend. Multi Play leads to 86multiplayermode.
- The track selector draws the `Map` widgets over `femap_template`:
  - Select Peak: `SP_PeakList` (Peak 3 / Peak 2 / Peak 1; All Mountain hidden), `MAPGFX_map_mtn` in `MapPic`, the
    focused peak's `peak<n>outline` (vertex alpha 0 in the data, made visible by the code), the `phl` bar at
    y = 103 + 25i, lock sprites (Locks group). A locked peak keeps black text with the lock and uses the help
    `kT_10HELPUnlockPeakN` **(PS2)**.
  - Select Mode: `SPG_Peak<n>Goals` Race / Freestyle, `MAPGFX_map_peak<A|B|C>`; the focused mode's routes are
    red (227,42,9) and the others orange (224,134,32); the backcountry belongs to Race **(PS2)**.
  - Select Event: `Peak<n>RaceLocations` / `Peak<n>FreestyleLocations`, listed in the goal-list order of
    `0x0045AAD8` (Peak 1 Race starts with Snow Jam; world-streaming.md says the Single Event order can differ
    from that table and follow the Map LUI rows, which is unresolved). The focused route is red, a start
    indicator comes from the course's Map state (frames 200..490), the map tab shows the event type, and the help
    is `kT_HELP<code>`.
    Metro-City uses `kT_HELPBRA2Blah` because `kT_HELPBRA2` has the same hash as `kT_HELPCBA2`. A medal column
    shows the rider's best career medal, and Square toggles the `SE_Info` table (Run / Event / Medal / Top time or
    Top score).

### Rider speech

`0x001A0358` polls two flags of the FE preview slot: `+0xC20` (set by Select Character's Cross) plays
Post_Selection (`20BCh`, `0x002A16B0`) when `0x00535C11` != 0, i.e. not in Conquer the Mountain; `+0xC1C` (set by
the Equip Gear commit at `0x00199EA4` inside `0x00199C28`) plays Customize (`20BDh`, `0x002A1778`) in every mode.
Both use the CHARACTER bus and the slot's character (a skin's base rider). Banks are per rider, e.g.
`Post_Selection_zoe`. See audio.md.

## Front-end preview rider

- Slots are at `*(*(0x004A28A8)+0x7C)` `+0xB0` + `CE0h` x player (G is gp-0x848).

| Slot offset | Field |
|---|---|
| +0x0 | character id |
| +0x8 | geometry |
| +0xC | animator |
| +0xC1C / +0xC20 | speech request flags (Customize / Post_Selection) |
| +0xC30 / +0xC40 | root position / root quaternion |
| +0xC50 / +0xC60 | board position / quaternion (written by `0x0019F548`) |
| +0xCB4 / +0xCB8 | model ready flags |
| +0xCC8 | model shown |
| +0xCD0 | 0 in every observed state; selects an alternative lighting-record branch |
| +0xCD4 | < 0 selects the FE lighting path |
| +0xCD8 | variant mask |

- Geometry: parts at `+0x0C`, count `+0x8`, stride `58h`; per part `+0x0` file id, `+0x4` first bone slot,
  `+0x18` active, `+0x38` bones, `+0x44` bone count; bind bank at `+0x38` and 32-byte world bones at `+0x2C` of
  the geometry. The model header in use is the entry of the part's variant table (`+0x1C`, 16-byte entries
  {header, material names, flags, ...}) selected by `+0x50`, not always entry 0 (Zoe's TopB/BottomB/hands and
  Nate's TopC use variants 1..5) **(PS2)**.
- Assembly **(PS2)**: the equipped outfit as it is, with the cinematic parts instead of the race head and hands:
  `<prefix>_HeadA_NIS` (file 5, 36 morphs), `<prefix>_Eyes_NIS` (file 6, bones `eye_r`/`eye_l`), `_HandsX_NIS`
  (file 8, left hand, 27 morphs) and `_DummyX_NIS` (file 9, right hand, 27 morphs), both board parts, no PDA.
  Every bone slot is active, the binds equal the race binds for shared bones, and the geometry is unscaled
  (`+0x140` = 1.0). Morph data and clip timing are in animation.md.
- Clips (bank `fe.afl`): idle `FE_GEAR_<PREFIX>_CYC` (semantic 434), cheer `FE_CHARSEL_<NAME>` (435) on entering
  Setup Character or Rider Details, `FE_A_CYC` (436) on Ubertrick Setup only.
- Placement **(PS2)**:

| Screen | Camera (cm) | Rider root | Board |
|---|---|---|---|
| Select Character (`0x00181EF0`; also shown on Setup Character and Rider Details) | eye (0,200,0) -> origin | (136,-250,-82), turned 100 degrees | moved out of view by `0x0019F548` |
| Ubertrick Setup (`0x00184C60`) | eye (0,660,80) -> (0,0,80) | (-228,-205,63), 62 degrees about Z | on the rider |
| Equip Gear (`0x0019BFE8`, camera `0x0015E050`) | eye (-110,394,0) -> (-35,0,0) | see "Equip Gear screen" | see "Equip Gear screen" |

  All three cameras use 25 degrees. On Select Character it is the horizontal half-angle of a 4:3 view; with it the
  bone world positions (Kaori's hips at 147.39, -245.70, 23.17 cm) project to the PS2's pixels.
- Lighting (`0x0019EE88`, when slot `+0xCD4` < 0): clear a bank (`0x00389260`); add the character's `IRR.DAT`
  record with weight 1.0 and modulation (1,1,1,1) (`0x00389590`); run `0x00389CB8(bank, world position of the
  hips bone from 0x00310C48, 1.0)` with the FE camera's view matrix (camera block `+0x40`); copy the bank to the
  renderer (vtable `+0x22C` = `0x003954D0`, to renderer `+0x6BB0`); VU1 program 2 scales it by 255. There is no
  environment bank and no local light. Records are per rider for ids 0..9 (ids 6, 7 and 8 all select the `elise`
  record) and `fe_map` for ids >= 10. **(PS2)**: VU1 data qwords 7..16 of Kaori's select state are her record x 255
  plus a rim lane.
- A chosen cheat skin is never drawn in the preview: after Cheat Characters, Setup Character still shows the base
  rider **(PS2)**.

### Rider textures (PS2)

PS2 rider textures (`<PREFIX>TXP.BIG` `.ssh`, 8-bit CLUT) store colour at half intensity (128 = 1.0); GS
HIGHLIGHT2 (tex x light / 128 + light alpha) brings them to full brightness. The GameCube copies are about twice
as bright. A model material binds the loaded texture whose SSH entry name equals the material name (`suit`,
`boot`, `head`, `bord`, `alph`, `eat*`, ...).

## Gear and outfits

### BOLTPS2.DAT

`DATA/CHAR/BOLTPS2.DAT` is loaded into the runtime DB at `0x004A6750`, with 30 character buckets (0..9 riders,
10..29 cheat characters). An item entry is 56 bytes:

| Offset | Field |
|---|---|
| +0x0 | character |
| +0x2 | tier |
| +0x3 | texture group (-1 = none) |
| +0x4 | item id |
| +0x6 | class: the model entry the item belongs to (a top colour belongs to its top model, which belongs to the Tops class) |
| +0x8 | menu parent |
| +0xA | menu order |
| +0xC | item-limit weight |
| +0xE | price / 10 |
| +0x10 | low byte: part slot (geometry file id; `FFh` = no model) |
| +0x14 | name |
| +0x18..+0x24 | LOD models H / M / L / shadow, or one `_NIS` model |
| +0x28 | model path |
| +0x2C | texture name with `$` wildcards |
| +0x30 | icon |
| +0x34 | flags: `1h` equipping unequips the class siblings; `4h` listed leaf; `8h` multi; `10h` fills a required slot; `20h` folder; `100h`..`800h` reward pools; `1000h` re-apply rules |

Three more tables follow: 7327 equip rules of 12 bytes (on/off, item, condition item and state, target,
desired); NIS model -> race model pairs (getters `0x0014DC00`/`0x0014DC10`, e.g. Zoe's HeadA_NIS 84 -> HeadA 86);
and default outfit rows {class A, item B} (`0x0014DC40`/`0x0014DC50`).

### Inventory and equip (PS2)

- `0x00151A88` builds the rows at R `+0x290`; `0x001513B8` applies the default outfit.
- The equip core is `0x00151C90`, with the rules `0x00151EF0` selected by `0x0014DB40`. The UI calls it through
  `0x0014AFB0`:
  1. back up the rows and call `0x00151C90`;
  2. force the item's own flag;
  3. `0x001521F0`: for every default row {A, B}, if no class descendant of A (walker `0x0014D608`, which follows
     `+0x6`, not the menu tree) is equipped with entry flag `10h`, equip B;
  4. `0x001520E8`: equipped entries with flag `1000h` re-apply their rules;
  5. if any step fails, restore the rows.
- Conflicts are resolved by the rules, never by a dialog (e.g. a beanie swaps Zoe's hair for another cut; Bedhead
  removes Mac's hat).
- Equip Gear Cross (`0x0019BEE8`) toggles against the committed bit (on = !(flags & `4h`)) and commits
  (`0x0014AEA8`: the committed bit `4h` is set from the equipped bit `10h`). `0x0014AF10`, called from the
  front-end transition at `0x001A1F1C` (inside `0x001A1EC0` (`cRealFE_load`)), resets equipped from committed.
- Item limit: `0x0014B478` sums the `+0xC` weights of the equipped entries. `0x00199D30` (inside `0x00199C28`)
  refuses an equip when the limit 3392 at `0x004A18D8` is below weight + change; `0x0019B8F0` (inside
  `0x0019B7E0`) precomputes the change by simulating `0x0014AFB0`. Bars 1 and 2 ("Your current outfit" / "Your
  possible outfit") fill (w - 1500) / (3392 - 1500) (`0x0019BC90`, `0x0019BD48`).
- Lists: `0x0019B180` in equip mode lists named owned leaves and folders that hold one (`0x0019AFD0`); children come
  from `0x0014D7E8`, sorted by `+0xA`. A fresh profile's lists are short (Zoe: 2 hairstyles, 1 eyewear, 3 tops,
  3 hands, 2 bottoms, 1 boots, 1 board).
- Five Equip Gear sequences replayed from a fresh profile give exactly the live committed rows, and 17 gear states
  assemble exactly from their rows.

### Race assembly

- `0x0014D068` (through `0x0014BD98`, called at `0x0022ED5C` inside `0x0022EBC8` (`cGame_load`)) sets equipped =
  committed, equips the race model of every committed NIS entry of the pair table, and equips item 4 (the PDA).
- `0x0011BBE8` then collects the equipped entries of the base rider's record; a cheat skin (setup slot `+0x12`)
  collects every entry of its own bucket, which is its fixed outfit. `0x0011C138` adds the four LOD models of each
  entry at its part slot. Hidden slots, skeleton compile, channel-1 masks and secondary-motion enables are in
  animation.md ("Model assembly and skeleton compile").
- Textures (`0x0011BE88` / `0x0014B988`): a `$` in an entry's texture name takes the characters at the same
  positions from another equipped entry's texture of the same group. Example: top `zoe_Suit_C01_$$$` + bottom
  `zoe_Suit_$$$_D01` resolve to `zoe_suit_c01_d01`; boots and hands combine the same way. Cheat skins use the raw
  names.
- Gear icons come from the character's TXP archive (`0x0014B700`); ids >= 10 have none.

### Equip Gear screen (12equ_char, cFEStateCharEquip)

- The preview update `0x0019BFE8` has a view state at `+0xAE0`: 1 rider view, 2 board view, 3 easing to the board
  view, 4 easing back. Entering the Boards folder (id 3, `0x004A11E0`) sets 3 (`0x00199D14`); leaving it sets 4
  (`0x00199E30`). Each eased frame computes p += (target - p) x 0.2 in VU arithmetic until the squared distance
  to the board (3) or rider (4) position is below 0.2 (37 frames in, 34 out by this rule).
- Rider root (-105, -100 + 320z, -80 - 65z), turned about Z by (`+0xAAC` + 80) degrees; (-250,-650,-215) in the
  board view. Right stick X turns 3 degrees per frame (`0x00199AAC` inside `0x00199A38`); stick Y zooms
  z += -0.1 x stick, clamped to [0,1] (`0x00199B64`).
- Board (`0x0019F548`): at (265.75,-1073.5,-232), or (-100,45,15) in the board view; q = rotZ(2 x 2.138029)
  rotY(2 x 2.792527) rotX(spin + 90 degrees), spin +1 degree per frame mod 360. This equals the live `+0xC60` of two
  PS2 states **(PS2)**.
- "Loading..." shows while the preview model loads (`+0xCB4`/`+0xCB8`): the list is up and no rider is drawn,
  about 250 frames of disc load **(PS2)**. The rider updates as soon as an item is equipped; moving the cursor
  only changes the icon and bar 2. A cheat skin's Equip Gear dresses and shows its base rider **(PS2)**.

## Computer-rider lineups

The roster is built at event start by `0x0023A108` (vtable `0x0047CF4C`) through `0x0023A4F0`: two different
"Tricky" cheat riders (ids 10..16), the base riders except the human's character and the peak rival
(`0x00145750`), and a 25-swap shuffle (`0x0023C770`). `0x0023A668` copies the heat's entries into the race copy
`0x00535B20`; an entry of 10 or more is that cheat skin on the **human's** base character, so a cheat computer
rider always has the human's base gameplay **(PS2)**. Seeding, the 52 draws, the heats and the peak rival table
are in random-streams.md; the freestyle opponent pick (`0x00239938`) is in game-flow.md.

Which computer-rider values depend on what **(PS2)**, over 70+ countdown states:

| Depends on | Values |
|---|---|
| grid slot | AI path, route words, score/pacing words, secondary-motion slot |
| skin (base rider or cheat) | body scale, presentation lift, masks `+0x8C0`/`+0x8C8`, bone mask, contact legs, hair |
| gameplay character | stance words, default mirror/root, uber table, ids, variant flags |
| slot x body scale | grid position (about 90 cm x scale along the grid line), ground frame, contact normal, lateral route distances |

Computer riders take their pair collision/attack stats from attribute bank 2 (raw 20), the human from bank 0.

## Career messages

The inbox (R `+0xE38`, table above) holds messages posted by the career; the pause-menu Messages screen and MCOMM
Messages show it (OV.LUI `112messagecenter` / `113ViewMessage`; the pause screen shares the folder, btext, arr_up
and `From%d` strings at `0x004A20D0`). Everything requires Conquer the Mountain (`0x005305F9` == 0). A tutorial
counter at G `+0x84` `+0x28` also blocks posting while it is 1..9 (it is 0 or 10 in every career state seen).

Tables: categories at `0x00441630` (61 x 20 bytes: type, first item, count, kind, folder); message records at
`0x004C6C08` (256 x `18h`: item, category, flag, sender, subject/body key hashes).

- Adding: `0x001E2FE0` adds {item, variant}; a full inbox drops its oldest entry first (`0x001E31B8`, entries and
  read bits shift). `0x001E3100` picks the variant of a flag-1 record: kinds 3/4 r % 10, kind 5 r % 11, kind 8
  r & 3. `0x001E4F80` (inside `0x001E4F70`) formats the subject: kind 3 `kT_MSGSubjectBCFinishWin/Loss<v>` (Win for
  the odd items from `74h`, jump table `0x0046E1E0`), 4 `Foreshadow<v>`, 5 `Aggression<v>`, 8 `BeatThePeak<v>`;
  other kinds use the record's subject. `0x001E2EA0` gives the sender: 0..9 the riders, 10 `kT_CMNGameTitle`
  (FAQs), 11 `kT_CMNDJAtomica` (mountain notices), 12 `kT_FAQFolder`.
- Posted bits (R `+0xF08`): bits 40..51 are pending flags (empty kind-7 categories); bits 7..11 are the open FAQ
  folders, toggled by `0x001E4338` (inside `0x001E4200`), so an open folder stays open in the save. `0x001E3C00`
  opens the Progression/Rewards folder while the Message Center is shown when it was entered with
  `*(0x004A20CC)` (gp-0x1024) != -1; which path sets that is unknown.
- Relationship notice `0x001E2A08(character, score)`: called by `0x00155BF0` only when the human's own record
  rises a level, and by `0x00155E58` for every aged record. Gates: career mode; not the human's own character; no
  message of that character already posted (`0x001E3A30`); score > 15 + (r & 7). The category is 12 + character
  (`0x001E2B38`), the item first + r % count. A score below 5 clears the posted flag (`0x001E3A78`). r is a
  presentation draw (random-streams.md). It also posts HUD event 8 (hash of "hud" under G `+0x48`, virtual
  `+0xC4`; `0x001EC3C4` inside `0x001EC1F0` sets hud `+0x160`).
- Mail icon: `0x001EB6E4` (inside `0x001EA930`) advances a 1 s phase and a 5 s timer; `0x001F0F3C` (inside
  `0x001EF7BC`) draws OV.LUI `mail_icon` (OV_1-4) at (15,384) of 640x480, white (`0x004C8788`) while the phase is
  <= 0.5, else orange (`0x004C87A8` words 1..3 = 0.861, 0.381, 0) **(PS2)**.

Event completion `0x00154EE8` runs once per career event and posts in this order:

1. Backcountry result (`0x001E25D8` -> `0x001E2648` rival race / `0x001E2828` rival jam, course 14 + peak),
   unless result bit 22 + peak / 25 + peak is set: it removes the rival reminders (category 1 + peak / 4 + peak) and
   earlier results (`0x001E32C8`), then posts a loss (item `73h` / `7Fh` + 4 x peak, + 2 for the rival's own
   rider) or, on a win, sets the bit and posts the next item.
2. Without a medal it stops here.
3. Peak-challenge notices (`0x001E1EB8`): pending flags 40..51 post the peak event's "time beaten" message
   (category 34 + jam + 2 x peak), the first text after bronze and the second after silver, which ends the series.
4. Rival reminders (`0x001E1550`, not in rival events): the first unposted of categories 1..3 (rival race) and 4..6
   (rival jam) posts once, if that rival event is open (`+0x278` bit 6 + peak / 9 + peak clear before this event)
   and has no medal (`0x00145EF0`). The item is first + r % 3; the rival's own rider gets the second three.
5. Awards (`0x00159CD0`, notices from Atomika): award 0 all golds (item 251), 1 the whole mountain (255), 2..4 all
   goals of peak 1..3 (252..254; award 3 tests bit 58 but sets 57, so it can repeat), 11/12 the free-ride goals
   (`0x001E38B8`; items 249/250 need the next peak still locked).
6. Peak-challenge flags (`0x001E1DD0`): silver or bronze in a peak event (modes 6..11) sets flag
   40 + 4 x peak + 2 x jam (+1 for silver) unless already posted.
7. Goal-list walk (`0x001591E8`, lists `0x0045AAD8`): while a standard event before the rival has no medal, a
   rival taunt posts (`0x001E1C10`: a random category 28/29 + 2 x peak item not from the human and not already in
   the inbox; subject Foreshadow). When the rival opens, taunts stop (`0x001E2370` sets bits 28..33).

Collectible cash: `0x00119EF8` calls `0x001E3760` before adding the cash; if earned + amount reaches the peak 1
(peak 2) earnings goal while peak 2 (peak 3) is locked, it posts item 247 (248).

Message rows, subjects, senders, bodies and the icon were compared with PS2 frames of states with poked inboxes
**(PS2)**.

## Options read by the race

- Speed units (`0x00535610` bit 19 = km/h): the HUD code at `0x00220260` (inside `0x002200C0`) prints cm/s x 0.036
  for km/h, or x 0.621 of that for mph **(PS2)**.
- HUD level (`0x00535610` bits 30..31: 0 Full, 1 Minimal, 2 None). Minimal masks the HUD owner flags (owner
  `+0x3CC` from table `0x00478078`) with ~`0510C040h`, e.g. `1530C047h` -> `10200007h`: timer, score, place, boost
  gauge, career HUD and trick HUD stay; speed and progress go. None draws only the countdown and banners **(PS2)**.
- Controller 1P = Pro sets the race copy byte `0x00535B30` (race copy `+0x10`) to 1, which selects the
  `INPUT2.MAP` compilation instead of `INPUT.MAP` **(PS2)**; the Pro expressions and the late-spin modes it enables
  are in input.md. world-streaming.md reads race copy `+0x10` & 1 as the profile index; how the two readings fit is
  unresolved.
- Vibration 1P/2P gates the pad motor model `0x00125B18` (gate `0x00127900` inside `0x001278E8`: the option getter
  `0x001474E8` and game state < 10); pause, quit and Off stop the motors (`0x00326CF0`). The model, its constants
  and its impact/slide inputs are in input.md ("Vibration").

## Loading screens

### Files

- `DATA/UI/GL.LUI` + `GL_1.SSH` ("game load"): pages 0 MCOMM art, 1 `Widg` (snowflakes), 2 trees, 3 mountain,
  4 `help` (the DualShock 2 picture and button icons), 5 the orange title swoosh and SSX 3 logo. The GL_1 CLUTs
  use the CSM1 swizzle, including the tree page's short 98-entry CLUT. Screens: 99QPEvent (course card),
  102MPMatch, 110ctrl_load (Basic Controls), 118loadoutlodge and one unnamed screen (`044FAE42h`).
- `DATA/UI/FL.LUI` + `FL_1.SSH` (front-end bound): 101QPMPHints, the stats screens and 117loadinlodge.
- `DATA/FONTS/FLOAD.SSH`, `GLOAD.SSH` and `SPLASH.SSH` each hold only the 512x512 SSX 3 boot logo.

### Selection (`0x00232E20`, the `cGameLoadState` init)

| Condition | State | Screen |
|---|---|---|
| `*(0x004A19D8)` set, or event type `0x00535C10` (`0x00535BC8`+0x48) is 5 or 6 | `cGameLoadStateOutLodge`, vtable `0x0047C878` | 118loadoutlodge |
| else game type `0x00535C11` (`0x00535BC8`+0x49) == 0 (Conquer the Mountain) | `cGameLoadStateConquer`, vtable `0x0047C7A8`, enter `0x00245730` | 110ctrl_load |
| else (Quick Play) | `cGameLoadState`, vtable `0x0047C948`, enter `0x00245418` | 99QPEvent, or 102MPMatch when `0x00535C11` == 2 |

Hints: 101QPMPHints enter `0x00245950` (`cFELoadHintState_onCreateScreen`) shows `kT_FEHINTTitle%d` /
`kT_FEHINTDES%d` (CMNAMER, 15 hints) with n = counter + 1, skips hint 12 (Bragging Rights), then sets counter =
(counter + 1) % 15. The counter is the byte at `0x004A2C38` (gp-0x4B8).

### LUI format (as used by these screens)

- Coordinates are a 640x480 frame.
- An element's frame-0 state is either a `21h` record of property pairs (0 x, 1 y, 3/4 pivot, 5 rotation in
  degrees, 6 w, 7 h, 9/10 scale %, 12 anchor, 13..16 A R G B; for shapes, 4 vertices at 21 + 9k: x, y, then A R G B
  at 26..29 + 9k) or a `20h` record (animation, element, mode) that binds an animation.
- Later states are timeline events at frames 1..500 that start animations (mode 1 holds, mode 9 loops) or set
  properties.
- Animations live in the file's u1 table as `50h` records; each track is a `51h` line (property id, n values, n - 1
  frame counts between them), interpolated linearly.
- Draw layer = definition flags & `3Fh`. Anchor bits: 8 left / 16 centre / 32 right; 1 top / 2 middle / 4 bottom.
- LUI text at 100% is FEFONT at 0.79 of its native size in PS2 pixels (measured **(PS2)**).
- 110ctrl_load contains the sky quad and white ramp, three looping parallax rows of trees, the mountain, twelve
  snowflake flight paths, the controller picture with white leader lines, a "Default" and a "Pro" label set, the
  "NN%" text (element `25h`, set at runtime) and "Loading...".

### Observed behaviour (PS2)

- Single Event, Snow Jam: 99QPEvent is up for about 13.6 s (emulator timing). It fades in from black over about
  20 frames; the percentage reads 2% at frame 20, 17% at 120, 27% at 240, 52% at 400, 97% at 520, holds 98% for
  about 4.4 s, then 100%; the screen is black 20 frames later and the intro cinematic starts ("Press X to skip").
  No input skips the loading screen.
- Conquer the Mountain shows 110ctrl_load ("Basic Controls / Default"): Grab board (L1/L2, R1/R2), Boost/Tweak
  (Square), Jump (Cross), Turn/spin/flip (D-pad), Turn (left stick), Reset (Select). The Pro label set includes
  Board press (right stick), Pause (Start) and a "No function" label pointing at Circle.
- The in-career transport shows a movie with "Loading..." instead of these screens.

## Controller button glyphs

- The FE controller page is one 256x256 page shared as FE_1-14 and OV_1-2. Face icons are 20x20 boxes at
  x = 12 + 22k, y = 123 for Triangle, Square, Cross, Circle (k = 0..3). Shoulder badges are 28x15 boxes at x = 121
  (R) and 151 (L), y = 157 (1) and 174 (2). LUI legends cut slightly different rectangles from the same cells
  (e.g. (56.5, 123.5, 20, 19), which falls on the Cross cell).
- 19game_opt stacks its Cross icon under the Triangle at the same spot.
- The GL.LUI `help` page carries the DualShock 2 picture used by 110ctrl_load; 22control shows the DualShock with
  the Default or Pro labels.
- Prompts that use the glyphs include the title's "Press START button", the cutscene skip "Press X to skip", the
  Ubertrick Setup category hints and the in-race uber trick hint (a shoulder badge plus Square).
