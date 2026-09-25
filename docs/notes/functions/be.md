<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/be/

## `src/be/beintnewrace.cpp`

Segment `0x001448D8`-`0x00145930`.

- **`0x00144BC0`** - Returns the location word (0 on Snow Jam); gates stage-script sound id 102. *[static]*
- **`0x00144C78`** - Returns a course index's career peak (+0x54 of the course table). *[static]*
- **`0x00144CE0`** - Map id to course index lookup; used by builtin 68 key0. *[static]*
- **`0x00144D38`** - Reads entries of the location table `0x0043E250`. *[static]*
- **`0x00144D50`** - Reads entries of the location table `0x0043E250`. *[static]*
- **`0x00144D98`** `cBENewRaceInterface_setNumberAI` - Sets the computer rider count = GMM+0x10 - GMM+0x14, stored to `0x00535C04`. *[static]*
- **`0x00144DF0`** `cBENewRaceInterface_setGameMode` - Sets the event type (`0x00535C10`). *[static]*
  - Possible mismatch with the current name: Name says it sets the game mode, but the notes say it writes the event type at `0x00535C10`, while `0x001451E8` (named setGameEvent) is noted as writing the game mode; the two labels may be swapped.
- **`0x001451E8`** `cBENewRaceInterface_setGameEvent` - Sets the game mode (`0x00535C12`). *[static]*
  - Possible mismatch with the current name: Name says it sets the game event, but the notes say it writes the game mode at `0x00535C12`, while `0x00144DF0` (named setGameMode) is noted as writing the event type; the two labels may be swapped.
- **`0x001453D0`** - Posted freestyle score (heat 1, heat 2, solo final) from table `0x00440B38`: column score/100 scaled by level (0.9 at level 0, 1.2 at level 2; leader never scaled), plus trunc(s*(rand%200-100)*0.0005), rounded down to a multiple of 20. *[PS2]*
- **`0x001454F8`** - Returns the time limit in seconds for (course, round) from freestyle table `0x00440B38`; GMM+0x78 = result x 60 when +0x88 is set. Rival Points init calls it as (profile, 1). *[static]*
- **`0x001456A0`** - Career-only platinum upgrade check using table `0x00440E80`: races need time <= T*60 ticks (150/150/160/165/160 s), freestyle needs score >= T*100; peak events have no platinum. *[static]*
- **`0x00145750`** - Returns the peak rival for the current course's peak (via `0x00144C78` on `0x00535C08`): peak 0 Mac (3), or Griff (5) if the player is Mac; peak 1 Nate (7), or Zoe (4) if the player is Nate; peak 2 Psymon (8), or Elise (6) if the player is Psymon. The rival is excluded from the computer-rider roster; used by Rival Time/Points lineups, peak-run cards, the career slope-style opponent and the relationship kind lookup. *[PS2]*

## `src/be/beintplayer.cpp`

Segment `0x00145930`-`0x00148F50`.

- **`0x00145D38`** - First-visit test of a location: returns !(P+0xACC bit loc). *[PS2]*
- **`0x00145EF0`** - Medal query for an event; used to gate rival reminders. *[static]*
- **`0x00145F90`** `cBENewPlayerInterface_isPeakLocked` - Reads a peak/event lock bit from the profile character block lock word +0x278 (set = locked). Bits: 12/13 Peak 2/3 pass, 6+p / 9+p rival, 14+p / 17+p peak events. *[PS2]*
- **`0x00146008`** `cBENewPlayerInterface_isPeakLocked1` - Tests lock word bit 12 (P+0x278, the Peak 2 pass) via `0x00145F90`. Single Event Select reads it when the screen is entered. *[PS2]*
- **`0x00146150`** - Career check: the rival challenge has not yet been shown. *[static]*
- **`0x00146320`** - Career: marks the rival challenge as shown. *[static]*
- **`0x001464D0`** - Career check: the rival challenge is unlocked. *[static]*
- **`0x00146E98`** - Returns the player's lineup slot (called as (profile, 0)). *[static]*
- **`0x00147138`** - Stores the accepted player name into the profile. *[static]*
- **`0x00147398`** `cBENewPlayerInterface_getRiderCharID__FPvi` - Returns the player's character id. *[static]*
- **`0x001474E8`** - Returns the vibration option setting. *[static]*
- **`0x00147908`** - Adds an entry to the profile message inbox (up to 25 entries of item + variant, with read bits). *[static]*
- **`0x00147980`** - Tests an inbox posted-category bit. *[static]*
- **`0x00147A30`** - Sets an inbox posted-category bit. *[static]*
- **`0x00147D20`** - Race adaptive difficulty update (works with `0x00147E18`). *[static]*
- **`0x00147E18`** - Race adaptive difficulty update (works with `0x00147D20`). *[static]*
- **`0x00148950`** - Rider level = max(1, sum(attribute byte / 5) / 7); used by the great-trick test `0x00149778`. *[static]*
- **`0x00148D80`** - Edging stat getter (k=3): progression byte +3 over character max byte +11, same layout as `0x00148E68`. Used by `0x0013CCF0`, `0x0013D028` and `0x0013D818`. *[static]*
- **`0x00148E68`** - Edging stat getter (k=3): progression byte +3 over character max byte +11, same layout as `0x00148D80`. *[static]*

## `src/be/beintstat.cpp`

Segment `0x00148F50`-`0x0014A080`.

- **`0x00148F50`** `cBEStatInterface_getCollisionAttrib` - Toughness stat getter (k=5): progress byte 5 over maximum byte 13, with override and fixed NPC-stat cases; paired with `0x00149038`. Used by collision weight `0x0011FF98` and rider pairs `0x00107888`. *[static]*
- **`0x00149038`** - Toughness stat getter (k=5), paired with `0x00148F50`. *[static]*
- **`0x00149120`** - Stability stat getter (k=6), paired with `0x00149208`; used by landing `0x00139C88` and rails `0x0013AF28`. *[static]*
- **`0x00149208`** - Stability stat getter (k=6), paired with `0x00149120`; its bytes +6/+14 scale rail imbalance as imbalance / (1 + 1.650076*stat), so probably the balance stat. First of the rider stat getters `0x00149208`..`0x001494C0` (ground, landing, air, grab) fed by Buy Attributes; computer riders use attribute bank 2. *[PS2]*
- **`0x001493D8`** - Acceleration stat getter (k=1): integer progression byte +1 / 5, then float division by character max byte +9; a special player flag can return 0.5. Zoe's baseline gives nearest(1/11). Used by `0x0013C948` and `0x0013CCF0`. *[static]*
- **`0x001494C0`** - Top speed stat getter (k=0): progression byte +0 over character max byte +8. Computer riders (race copy +0xC == -1) read attribute bank 2; Peak 2 computer riders are level 4 (raw 20, stat 4/11 = 0.3636) against the human's raw 5. Used by speed limit `0x0011B3F8` and `0x0013CCF0`. *[PS2]*
- **`0x001495A8`** - Spin (air/trick) stat getter (k=4): progression byte +4 / 5 divided by character max byte +12 (scalar DIV, round to nearest), with the same slot/bank/override selection as the other stats; Zoe's baseline gives 1/11 (0x3DBA2E8C). Used by air control `0x00133128`/`0x00133308`. *[PS2]*
- **`0x00149690`** - Tricks stat getter (k=2); used by grab rate `0x00120038`. Meter award `0x0010E098` calls it for positive deltas, before the category eligibility test, without using the value. *[static]*
- **`0x00149778`** - Great-trick test: landing total gain >= table `0x0045A2B0`[clamp(level-1, 0, 10)], with level from `0x00148950`; selects landing reaction kind 1. *[PS2]*
- **`0x00149BB8`** - Contains the CHARDB.DBL character table load below. *[static]*
  - `0x00149C84`: CHARDB load block: loads DATA/BE/CHARDB.DBL and copies its 10 rider rows (0x88 bytes each) into the character table `0x00530970`. *[static]*

## `src/be/belibrary.cpp`

Segment `0x0014A080`-`0x0014DC80`.

- **`0x0014A080`** `cBELibrary_getCharacterID__Fi` - Returns the base character id of a setup slot (slot +0x11). *[static]*
- **`0x0014A0B0`** - Returns the cheat character id of a setup slot (slot +0x12); a cheat skin makes race assembly `0x0011BBE8` collect the skin's whole BOLT bucket. *[static]*
- **`0x0014A0E0`** `cBELibrary_getProfileIndex__Fi` - Returns a rider's relationship record bank: 2 for computer riders, 0 for the human. *[static]*
- **`0x0014AB68`** `cBELibrary_getScoreType` - Maps an event to its record slot via table `0x0045A2F8`. *[static]*
- **`0x0014AEA8`** - Commits the outfit: row committed bit 0x4 := equipped bit 0x10. *[PS2]*
- **`0x0014AF10`** - Restores the outfit: row equipped bit 0x10 := committed bit 0x4; called on a front-end transition. *[static]*
- **`0x0014AFB0`** - UI equip entry: backs up the rows, calls `0x00151C90`, forces the item's own flag, refills required slots (`0x001521F0`) and re-applies rules (`0x001520E8`), restoring the backup on failure. Conflicts resolve through rules, never a dialog (e.g. a beanie swaps Zoe's Mop for SplitHair2; Tiara removes the Peacekeeper and restores Banger; Bedhead removes Mac's hat). *[PS2]*
- **`0x0014B478`** - Sums the item-limit weights (+0xC) of the equipped entries. *[PS2]*
- **`0x0014B560`** - Buys a gear item, including bundled items. *[static]*
- **`0x0014B700`** - Loads gear icons from the character's TXP archive (none for character ids >= 10). *[static]*
- **`0x0014B988`** - Resolves a gear item's '$' texture pattern (which textures it binds): each '$' takes the character at the same position from another equipped entry's texture of the same group, e.g. top zoe_Suit_C01_$$$ + bottom zoe_Suit_$$$_D01 -> zoe_suit_c01_d01. Cheat skins use raw names; a material binds the loaded texture whose SSH name equals the material name. *[PS2]*
- **`0x0014BD98`** - Called from the event load (`0x0022ED5C`); runs race outfit prep `0x0014D068`. *[static]*
- **`0x0014D068`** - Race assembly prep: sets equipped = committed, then equips the race model of every committed NIS entry (table 2) and item 4 (the PDA). *[PS2]*
- **`0x0014D608`** - Walks class descendants via entry +0x6 (not the menu tree). *[static]*
- **`0x0014D7E8`** - Returns the menu children of an item folder. *[static]*
- **`0x0014DB40`** - Selects the BOLT equip rules for an item (used by equip `0x00151C90`). *[static]*
- **`0x0014DC00`** - Getter for BOLT table 2 (NIS model -> race model pairs, e.g. Zoe HeadA_NIS 84 -> HeadA 86). *[static]*
- **`0x0014DC10`** - Getter for BOLT table 2 (NIS -> race model pairs, e.g. HandsB_NIS 128 -> HandsB 130). *[static]*
- **`0x0014DC40`** - Getter for BOLT table 3 (default outfit rows: class A, item B). *[static]*
- **`0x0014DC50`** - Getter for BOLT table 3 (default outfit rows: class A, item B). *[static]*

## `src/be/beintnetwork.cpp`

Segment `0x0014E0E0`-`0x0014EF30`.

- **`0x0014EEC8`** - Character name getter: returns the kT_CHAR<Name> string (CMNAMER) for a character. *[static]*

## `src/be/beintcharacter.cpp`

Segment `0x0014EF30`-`0x0014F250`.

- **`0x0014EFA8`** - Returns a character's model scale: CHARDB model size * 0.01 for riders, via jump table `0x0045A660` for cheat characters. In Conquer the Mountain (`0x00535C11` == 0) the human keeps the base rider's CHARDB scale, dropping the skin's (read from code only). *[PS2]*

## `src/be/beintoption.cpp`

Segment `0x0014F250`-`0x0014F900`.

- **`0x0014F458`** - Profile defaults: music, speech and SFX volume steps set to 10. *[static]*
- **`0x0014F4F8`** - Contains the options reset block below. *[static]*
  - `0x0014F5D0`: Options reset block; sets the screen position bytes to 0 among other options. *[static]*

## `src/be/beintbagt.cpp`

Segment `0x0014F900`-`0x001508D8`.

- **`0x0014FD80`** - Writes the selected Uber entry. *[static]*
- **`0x0014FE08`** - Clears an Uber's lock bit on purchase. *[static]*
- **`0x0014FEA8`** - Reads the Uber selection byte live from `0x00530EC0` + bank*0x13EC + char*0x1FE + slot*6 + (tier >= 5). The grab notes place it, with nearby routines, in the grab/tweak/Uber definition mapping (main semantic, upper semantic, score id, begin/hold points for grabs[15], tweaks[15], ubers[2 tiers][15], with special-character overrides); the exact role split is unconfirmed. *[PS2]*
- **`0x0014FF90`** - Reads the lodge Uber trick lists from table `0x0045AEB8`. *[static]*
- **`0x00150118`** - Resolves an ordinary grab index to its score mapping: 15 mappings from table `0x0045AEB8`, score definitions at `0x00530600` + scoreID*8. *[static]*
- **`0x00150198`** - Uber row lookup: returns a cheat skin's Nose/Tail Grab uber override first, else the list entry (Stretch/Gutless/Canhuck replace the Nose Grab uber with semantics 160/159/161, Snowballs the Tail Grab with 162). The grab profile has two uber rows per category (set 0 hidden base uber, set 1 selected uber); a row is {semantic trick id A, upper semantic trick id B, score id, begin/hold points from `0x00530600`}. One of three Uber selection helpers (with `0x001502C8`, `0x001503F8`) between `0x001352A8` and `0x0014FEA8`. *[PS2]*
- **`0x001502C8`** - Uber row reader; reads the same uber list entry as `0x00150198`, skin overrides included. One of three Uber selection helpers between `0x001352A8` and `0x0014FEA8`. *[PS2]*
- **`0x001503F8`** - Uber row reader; reads the same uber list entry as `0x00150198`, skin overrides included. One of three Uber selection helpers between `0x001352A8` and `0x0014FEA8`. *[PS2]*
- **`0x00150558`** - Per-rider starting Uber ownership/lock state (e.g. Zoe's Mute row: Bar Hop owned; SSXorcist, dnL FlipIt, Katana for sale). *[static]*

## `src/be/beintecon.cpp`

Segment `0x001508D8`-`0x00152398`.

- **`0x00150928`** - Returns the career cash. *[static]*
- **`0x00150C20`** - Buy Attributes: point cost = table `0x00440550`[raw/5 - 1]. *[static]*
- **`0x00151178`** - Collectible cash award by peak level: $500 (peak 0), $1,000 (peak 1), $2,000 (peak 2). *[PS2]*
- **`0x001511B0`** - Big Challenge cash award by peak: $2,000 / $4,000 / $6,000. *[PS2]*
- **`0x001513B8`** - Gear inventory init: applies the default outfit to the inventory rows. *[PS2]*
- **`0x00151600`** - Initialises Big Challenge status for a new character: table flag byte +0x1A -> bit0, +0x1B -> bit4, and sets bit1. *[static]*
- **`0x00151A88`** - Builds a character's inventory rows. *[PS2]*
- **`0x00151C90`** - Equips/unequips a gear item in the inventory, applying the equip rules `0x00151EF0` selected by `0x0014DB40`. *[PS2]*
- **`0x00151EF0`** - Applies the BOLT gear equip rules for an equip change. *[PS2]*
- **`0x001520E8`** - Re-applies the rules of equipped entries with flag 0x1000. *[PS2]*
- **`0x001521F0`** - For every default-outfit row (class A, item B), equips B if no class descendant of A with entry flag 0x10 is equipped. *[PS2]*

## `src/be/beintsavefile.cpp`

Segment `0x00152638`-`0x00153088`.

- **`0x00152BB0`** - Contains the boot-time widescreen apply call below. *[PS2]*
  - `0x00152DBC`: Boot-time call to widescreen apply `0x00228C08`. *[PS2]*

## `src/be/beintmission.cpp`

Segment `0x001532A0`-`0x00154948`.

- **`0x00153350`** - Reads a course's collectible count from table `0x0043FA70`. *[static]*
- **`0x001542A0`** - INFO panel helper for 'Big Challenges n / N' (paired with `0x001542E0`). *[static]*
- **`0x001542E0`** - INFO panel text 'Big Challenges n / N' (paired with `0x001542A0`); N/A when the course has no challenges. *[static]*
- **`0x001545F8`** - Returns a course's session point count from table `0x00440770` (+0x18). *[static]*

## `src/be/beintscore.cpp`

Segment `0x00154948`-`0x00155A50`.

- **`0x00154AB8`** - Conquer the Mountain end-of-run career update reached from `0x00238358`; records run statistics. *[static]*
- **`0x00154EE8`** - Career event result processing (medals, cash, goals, unlocks). Posts result messages once per career event in a fixed order: backcountry result `0x001E25D8`; stop if no medal; peak-challenge notices `0x001E1EB8`; rival reminders `0x001E1550` (not in rival events); awards `0x00159CD0` (in `0x001591E8`); peak-challenge flags `0x001E1DD0`; goal-list walk `0x001591E8` (taunts `0x001E1C10`). *[static]*
- **`0x00155328`** - Medal computation (0 platinum .. 3 bronze, -1 none); rival challenges award gold for a win only. *[static]*
- **`0x00155390`** - Writes stat medals (profile +0xBB8) from the post-event personal bests. *[static]*
- **`0x00155420`** - Records a run's statistics per character as personal bests at the end of a Conquer the Mountain run (human only, not free ride): {best, course} for KO +0x128, Ubers +0x114, super Ubers +0x118, Uber grinds +0x11C, best combo +0x184, handplant +0x158, rail +0x154, air +0x14C (floats stored as (int)(f+0.5)), race time (min) and event score. A value >= the best replaces it and raises the medal. *[static]*

## `src/be/beintaggression.cpp`

Segment `0x00155A50`-`0x00156338`.

- **`0x00155AB0`** - Relationship kind (a, b): byte +0xBC1 of b's record about a (3 / 2 when a is the peak rival from `0x00145750`). *[PS2]*
- **`0x00155B50`** - Relationship level (a, b): byte +0xBC2 of b's record about a; used to read a rider's relationship level about the human (3 for the peak rival). *[PS2]*
- **`0x00155BF0`** - In-race relationship bump on rider-pair contact: adds 1/2/4/6 (from `0x0010E228`/`0x0010E2E8`/`0x0010E3A8`/`0x0010E468` via `0x00107E70`) to the other rider's record about the one knocked, after the contact's hit speech has read the record. Kind 2/3 with level <= 0 -> 1/5, otherwise the ageing kind rules; a level change feeds `0x0010F560` and the AI attacks `0x0010DBF0` (>= 3). Calls `0x001E2A08` when the human's own record rises a level. *[PS2]*
- **`0x00155E58`** - Ages every participant's ten relationship records at each event load and restart: score = max(score-3,0), level = score/5; kind 3 level 0 -> 1/3/15; kind 1 level >= 4 -> 3/2/10; kind 0 level >= 3 -> 0/2/10; kind 2 level <= 0 -> level 1, level >= 4 -> 3/15; kind 3 level >= 5 -> 4/20. A character raced twice in a bank ages twice. Calls `0x001E2A08` for every aged record; the records feed the lineup. *[PS2]*

## `src/be/beintreward.cpp`

Segment `0x001569C0`-`0x0015AD58`.

- **`0x00157080`** - Picks a random unowned item in a category (any price or peak). *[static]*
- **`0x001577A0`** - Counts the cheat characters owned by a base rider; Rider Details enables Cheat Characters only when the count is > 0 (disabled through `0x00183550` -> `0x00194498`). *[static]*
- **`0x001577E0`** - 'Mountain conquered!' check awarding Far East Myth when all three peaks meet the medal conditions: gold in every standard event, any medal in rival and peak events, freeride medals, stat-medal sum >= 24. There is no ending movie; the ending is award messages ('Peak 3 conquered!', 'All Peak Race complete!', 'All Peak Jam complete!'). *[static]*
- **`0x00157BF0`** - Goal evaluation (RACE / FREESTYLE / EXPLORE / EARNINGS); completing any goal of peak N clears the peak N+1 pass bit (+0x278 bits 12/13). *[static]*
- **`0x00158558`** - Buys a song: sets both the owned and playlist bits in the profile; the first 6 use free credits, then $5,000 each (with `0x001988D8`). *[static]*
- **`0x00158750`** - Returns the profile's custom playlist mask. *[static]*
- **`0x001587B8`** - Returns the custom playlist size (rows 2 and 3 need > 0). *[static]*
- **`0x001587F8`** - Saves the radio mode to the profile. *[static]*
- **`0x00158820`** - Saves a song mask (owned or playlist) to the profile; paired with `0x00158848`. *[static]*
- **`0x00158848`** - Saves a song mask (owned or playlist) to the profile; paired with `0x00158820`. *[static]*
- **`0x001591E8`** - Goal-list walk over lists `0x0045AAD8` at event completion: detects the first gold/platinum in a standard event of a peak (awards 17-19), posts rival taunts (`0x001E1C10`) and award notices (`0x00159CD0`). *[static]*
- **`0x00159CD0`** - Grants awards (cheat characters, cards/posters/toys/art, gear, special boards) with Atomika award notices; called inside `0x001591E8`. Award 0 all golds -> item 251; 1 whole mountain -> 255; 2..4 peak 1..3 goals -> 252..254 (award 3 tests bit 58 but sets 57, so it can repeat); 11/12 free-ride goals via `0x001E38B8` (items 249/250, need the next peak locked). Peak-goal cheat characters come from table `0x0045AA40` (Peak 3: race Unknown Rider, freestyle Churchill, explore Canhuck, earnings Cudmore; all Peak 3 goals NW Legend; all goals Gutless). Draws from the visual RNG. *[static]*
- **`0x0015A818`** - Parses the rewards catalog DATA/BE/RWRDPS2.DAT (Art 100, Posters 43, Toys 28, Trading cards 116, Cheat characters 20, Videos 2); items are sold only in their own peak's lodge. *[static]*

## `src/be/bedbreward.cpp`

Segment `0x0015AD58`-`0x0015C988`.

- **`0x0015BEE8`** - Sets the widescreen mode bits 20..21 of profile word `0x00535610`. *[PS2]*
