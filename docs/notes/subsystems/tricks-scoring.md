# Tricks, scoring and boost

Every rider owns a score object that accumulates trick points while a trick is in progress, commits them at
landings and other boundaries, runs the combo clock, and keeps run statistics. Committed points also refill the
boost meter; a full meter starts "Tricky", during which grab combinations become Uber tricks, and nine Ubers
reach Super Uber. The human rider's score object also owns a bank of HUD message slots that the single-player
HUD draws: trick names, point popups, the combo counter and the boost gauge with its SUPER/UBER letters.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

- `src/ai/ridermetrix.cpp`: the score object. Per-tick update `0x00117C28`, HUD-side update `0x00117FE0`
  (including the boost widget blocks), commit `0x0011A228`, trick identity `0x0011A8C8`, repeat history
  `0x001190F0`, monster tricks `0x0011B1A8`, grab begin/end `0x00119708` / `0x001197D8`, and the event entry
  points listed below. The existing names in this file, `0x001172E0` (`cRiderMetrix_linkToRider`) and
  `0x0011A088` (`cRiderMetrix_evAutoResetSurface__FPv`), suggest the score object is the decomp's
  `cRiderMetrix` (unconfirmed).
- `asm/14B10.s` (not yet split): HUD slot primitives `0x00116FB8`, `0x00117008`, `0x00117048`, `0x001170A8`,
  `0x001171A8`; score object construction `0x00117248`; boost controller `0x00114130`; takeoff `0x00114298`;
  landing reaction player `0x00115B58`; reset path `0x00116120`.
- `src/ai/computer.cpp`: rider-side wrappers. Meter award `0x0010E098`, landing `0x0010E910`, reaction request
  `0x0010E028`, crash entry `0x0010EB30`, crash attack `0x0010E468`, pickups `0x0010E8B8` / `0x0010F1C0`, quick
  recovery `0x0010F280`, and the race bonus crossing test inside `0x00112FB0`.
- `src/ai/rider.cpp`: boost timers `0x001200D0`, leg IK weight `0x00120D90`, rider tick phases `0x001210B0` /
  `0x00121818` / `0x00121750`, human input provider `0x00127998`, finish `0x00125108`.
- `src/ai/ai.cpp`: grab/tweak/Uber lifecycle `0x001352A8`, air control `0x00133308`.
- `src/be/beintbagt.cpp`: grab, tweak and Uber mapping lookups `0x0014FEA8`, `0x00150118`, `0x00150198`,
  `0x001502C8`, `0x001503F8`.
- `src/be/beintstat.cpp` (`0x00149690`, great-trick test `0x00149778`), `src/be/beintplayer.cpp` (rider level
  `0x00148950`), `src/be/beintscore.cpp` (career personal bests `0x00154AB8`, `0x00155390`, `0x00155420`).
- `src/fe/ovstatehud.cpp`: the single-player HUD. `0x001E9AD0` (`cOVStateHUD1P_onCreateScreen`), HUD update
  `0x001EA930`, `0x001EC3F8` (`cOVStateHUD1P_onRender2D`), Uber hint layout/draw `0x001E92A8` / `0x001E95A0`,
  text helpers `0x001F1B30` / `0x001F1E28` / `0x001F2AA0`, sprite submission `0x001F1190`.
- `asm/1137E8.s` (not yet split): HUD drawing helpers. Gauge `0x0021D1A0`, recover bar `0x0021D9A0`, align
  `0x0021E750`, `0x0021E7A8`, glow `0x0021E7E0` / `0x0021EA00`, letter `0x0021ED48`, stars `0x0021F338`.
- `src/fe/festatebuyattrib.cpp`: Career Highlights `0x001F5DA0` (`cFEStateCareerStats_setupHighlightsList`),
  page switch `0x001F5A38`.
- `src/sound/soundsys.cpp`: trick, Uber, Tricky and arcade speech calls (see "Audio calls").
- `src/render/font.cpp` (`0x00391CB0`, `0x00391FB0`, `0x003921F0`) and `src/render/particle.cpp` (`0x00379860`,
  `0x0037D938`) for the HUD's text and sprite submission.

## Rider fields used by tricks and boost

| Rider offset | Meaning |
|---|---|
| `+0x234` / `+0x238` | grab lifecycle phase (0..5) and grab index (-1 = none), on the lifecycle's owner (presumably the rider) |
| `+0x2E8` | not the stored meter |
| `+0x2EC` | boost modifier; cleared by a positive landing award |
| `+0x2F0` | Tricky / Super Uber timer, seconds |
| `+0x2F4` | Uber tier, 0..10 (0 = no Tricky, 10 = Super Uber) |
| `+0x2F8` | boost meter, 0..1 |
| `+0x2FC` | active boost amount (1, 0.625 or 0.25; 0 = not boosting) |
| `+0x304` | meter policy: 0 forces full, 1 normal decay, 2 fast decay, 3 ignores awards; other values keep the meter |
| `+0x318` | leg IK weight written by `0x00120D90` (same owner as `+0x234`) |
| `+0x790` | pointer to the score object |
| `+0xB28` | award category mask tested by `0x0010E098` |
| `+0xB2C` | bit 0: Tricky/Uber capability |
| `+0xB34` | stat level; 11 = maxed stats (PS2) |
| `+0xD20` / `+0xD27` | feedback object and byte: `0x002F6AC8(owner+0xD20, 0)` sets bit 0x10 of the byte at `+0xD27` on a boost press |

## Score object (`*(rider+0x790)`, 0x1CC bytes)

Timers use -1 for "inactive"; the per-tick update advances only nonnegative ones. **(PS2)** for the whole layout:
the object and the bank matched PS2 memory word for word, every tick, across air, combo, repeat, grab, rail and
Uber runs.

| Offset | Field |
|---|---|
| `+0x00` | stance |
| `+0x04` | alternate flag (takeoff: the ramp branch; landing: surface normal z < 0.7) |
| `+0x08` | multi-trick flag (set when a new air trick starts while points are pending) |
| `+0x0C` / `+0x10` | style / flag arguments of the last boundary |
| `+0x14` | pending trick accumulator. Meter units: 1.0 = 10000 unmultiplied points |
| `+0x18` | pickup multiplier (reset to 1 per trick) |
| `+0x1C` | inverted/stall accumulator, paid at the landing |
| `+0x20` / `+0x28` | style / flag copies; nonzero means a special record (also skips the repeat history) |
| `+0x24` | rail distance |
| `+0x2C` | press timer (pairs with the LONG PRESS popup) |
| `+0x30` | air time |
| `+0x34` / `+0x38` | spin / flip, radians |
| `+0x3C` | hold increment added to `+0x14` each tick |
| `+0x40` | current hold seconds |
| `+0x44` / `+0x48` | total hold seconds / longest hold |
| `+0x4C` / `+0x50` / `+0x54` / `+0x58` | normal / tweak / Uber / super-Uber counts for the current trick |
| `+0x5C` | active Uber flag |
| `+0x60` | grabs[3] (grab score IDs) |
| `+0x6C` | timer accruing 0.05 per second into `+0x14` |
| `+0x70` / `+0x7C` | special-record fields (nonzero skips the repeat history) |
| `+0x74` / `+0x80` | counters summed into run statistics `+0x11C` / `+0x108` |
| `+0x78` | handplant timer (pairs with LONG PLANT) |
| `+0x84` | bonus points from duration thresholds |
| `+0x88` / `+0x8C` / `+0x90` / `+0x94` / `+0x98` | threshold indices: air, hold, press, handplant, rail |
| `+0x9C` / `+0xA0` / `+0xA4` | combo count, combo points, combo clock (-1 = suspended) |
| `+0xA8`..`+0xF7` | repeat history, 10 entries of 8-byte trick identities |
| `+0xF8` | history cursor (mod 10) |
| `+0xFC`..`+0x1A7` | run statistics, see below |
| `+0x1A8` | smoothed speed (0.9 old + 0.1 new, per tick) |
| `+0x1AC` | owning rider |
| `+0x1B0` | HUD message bank pointer; null for riders without a HUD |
| `+0x1B4` | slot count (44) |
| `+0x1B8` / `+0x1BC` / `+0x1C0` | renderer bits; the tick clears the first two and sets `+0x1C0` = 1 |
| `+0x1C4` | score multiplier, 1 after construction; never reset per trick |
| `+0x1C8` | starting total, copied to `+0x198` by the run reset |

Run statistics (zeroed by the run reset `0x00117540`):

| Offset | Statistic |
|---|---|
| `+0xFC` / `+0x100` | spin / flip degrees (each commit adds the rotation rounded to 180 degrees) |
| `+0x104` / `+0x108` | sums of `+0x4C` / `+0x80` |
| `+0x110` / `+0x114` / `+0x118` / `+0x11C` | committed tricks, Ubers, super Ubers, Uber grinds |
| `+0x120` / `+0x124` / `+0x128` / `+0x12C` | resets, crashes, knockdowns dealt (KO), crashes with the attack flag set |
| `+0x130` | multiplier pickups |
| `+0x134` | tricks in paid combos |
| `+0x144` | hold seconds |
| `+0x14C` / `+0x150` / `+0x154` / `+0x158` | best air, longest hold, longest rail, longest handplant |
| `+0x15C` / `+0x160` / `+0x164` / `+0x168` | top speed, top smoothed speed, speed sum, tick count |
| `+0x16C`..`+0x180` | count per grade 0..5 |
| `+0x184` / `+0x188` | best combo count / best combo points |
| `+0x18C`, `+0x190` / `+0x194` | best trick points (-1 after reset) and its identity |
| `+0x198` | total score |
| `+0x19C` | total inverted/stall points |
| `+0x1A0` / `+0x1A4` | points lost to bails / to resets |

## HUD message bank (`*(score+0x1B0)`)

44 slots of 0x9C bytes. Only the single human rider's score object has a bank.

| Slot offset | Field |
|---|---|
| `+0x00` | type; 0x34 = free |
| `+0x04` | maximum: duration in seconds, or -1 for a persistent value slot |
| `+0x08` | value: elapsed seconds, or `-input` for a value slot (so value/maximum = input) |
| `+0x0C` | arg (grade, count, tier, message id...) |
| `+0x10` | field10 (the combo slot keeps a stopwatch step here: 4 while the clock is suspended) |
| `+0x14` | points |
| `+0x18` | text, NUL-terminated: a trick name, or `"%d"` of the points |

A type below 0x22 owns slot `[type]`. Types 0x23 and above are placed in slots 0x23..0x2B by the allocator
`0x00117A58`. Timed slots are aged by `0x00116FB8`, which adds 1/60 to the value and frees the slot when
value >= maximum; value slots (maximum -1) are skipped.

| Routine | Role |
|---|---|
| `0x00116FB8` | age one slot (1/60 per tick) |
| `0x00117008` | copy text into a slot |
| `0x00117048` | set a timed text slot |
| `0x001170A8` | set a timed points slot (`"%d"`) |
| `0x001171A8` | set a value slot: type, points, arg, maximum -1, value = -input |
| `0x001173B8` | free every slot |
| `0x001179E0` | free a type: slot `[type]` below 0x22, otherwise every allocated slot of that type |
| `0x00117A58` | allocate a slot for a type |
| `0x00117AE8` / `0x00117B88` | post a text / points message of a type with a duration |

Slot types, with who writes them and how the HUD draws them:

| Type | Written by | Drawn as |
|---|---|---|
| 0 | trick name (`0x00118FF8`, 3 s; arg 1 = repeat) | trick name, FEFONT, wrapped |
| 1 | pending points (value slot, arg = grade) | score with grade stars |
| 2 | bonus `+0x84` + inverted points (arg = inverted) | bonus and its box |
| 3 | combo (points, arg = count) | "NX" at 2 x 2.4 scale, stopwatch and quarter hand, "+points", "Combo" |
| 4 | multiplier (`0x00119448`) | multiplier |
| 5 / 6 | boost preview / stored meter | boost gauge fills |
| 7 | total `+0x198` | total; pulses while slot 0x18 flashes |
| 8 | earned Uber letters | active SUPER/UBER letters |
| 9 | Tricky timer | gauge flash (through the HUD pre-pass) |
| 0xA | pending Uber letters | flipping letters after the earned ones |
| 0xB | recover state (control state 8) | recover bar `0x0021D9A0` |
| 0xC / 0xD | spin dial; 0xD holds the dial angle as a fraction of a turn | |
| 0xE / 0xF | landing message text (arg 1..5) / its bonus weight | landing messages |
| 0x10..0x17 | rotation direction slots | |
| 0x18 | flash trigger for the total (0.7 s) | |
| 0x19 | a points value (source not described) | nothing under the race flags |
| 0x1C..0x20 | BIG AIR, LONG RAIL, LONG PRESS, LONG PLANT, LONG GRAB (1.5 s, arg = threshold) | labels |
| 0x21 | RECOVERED! (1.5 s) | recover state |
| 0x23 / 0x24 | trick points (2.5 s, arg = grade) / the same for a repeat | popups flying to the total; green pulse, red for a repeat, grade stars |
| 0x25 / 0x27 / 0x28 | lost pending / combo / bonus points (1.5 s) | lost points, digits scattered by `0x001F14B0` |
| 0x26 | combo payout (arg = count) | "NX Combo" |
| 0x29..0x2B | race bonus (0x29, 2.5 s) and race checkpoint/time popups | |
| 0x2C / 0x2D | knockdown dealt / bail with the attack flag set (1.5 s) | |
| 0x2E / 0x2F / 0x30 / 0x31 | career award popups (award kinds 1 / 0 / 2 / 3) | |
| 0x32 | monster trick bonus (1.5 s) | only when the HUD flags lack bit 2 |
| 0x33 | "Wrong Way!" (posted from `0x0011A088`) | |

## Score arithmetic helpers

| Routine | Result |
|---|---|
| `0x00117948` | pending points: `t = trunc(+0x1C4 * +0x14 * 10000 + 5)`, then `t - t % 10` (signed remainder) |
| `0x00117990` | multiplied points: the same with `+0x1C4 * +0x18 * +0x14` |
| `0x00117908` | inverted points: the same with `+0x1C * 10000` |
| `0x00119310` | grade: < 1000 -> 0, < 2500 -> 1, < 4000 -> 2, < 7500 -> 3, < 11500 -> 4, else 5 |
| `0x00117838` | per-trick reset: zero the trick fields, timers to -1, `+0x18` = 1; leaves `+0xA4` and `+0x1C4` alone |
| `0x001175F8` | combo reset: free slot 3, count 0, points 0, clock -1 |
| `0x00117540` | run reset: zero `+0xFC..+0x1A7`, `+0x18C` = -1, `+0x198` = `+0x1C8`, free all slots, clear the history, then both resets |
| `0x001176F8` | set the combo clock `+0xA4` to -1 (suspend) |
| `0x00117708` | at the end of a commit, keep the combo open: `+0xA4 = max(+0xA4, 1.5)` |
| `0x00119EF8` | career award: when points go to the career instead of the HUD, posts slot 0x18 and a kind-specific popup (jump table `0x00457870`) with `min(points / 500, 20)`. Kinds: 0 trick commit, 1 pickup, 2 combo payout, 3 (caller not described) |

All arithmetic follows EE float semantics (multiply and int conversion truncate; add/sub keep the guard bit;
divide rounds to nearest). The object is constructed at `0x00117248`.

## Per-tick update `0x00117C28` (PS2)

Runs during `0x00121818`, after the AI route progress `0x001125C0`. `dt = timeScale * 1/60`.

1. Combo clock: when `+0xA4 >= 0`, the rider is on the ground (motion mode 0) and not in control state 1,
   subtract `dt`; at `<= 0` call the combo expiry `0x00117718`.
2. Accrue the active timers (below). Each timer with a threshold table then calls `0x00119210`.
3. Speed statistics (`+0x15C..+0x168`, `+0x1A8`).
4. The HUD-side update `0x00117FE0`, then `0x00116FB8` on every slot, then the renderer bits.

| Timer | Per tick | Added to `+0x14` | Threshold index, popup type |
|---|---|---|---|
| air `+0x30` | `+= dt` | none | `+0x88`, 0x1C BIG AIR |
| hold `+0x40` | `+= dt` | `+0x3C` once per tick, not time-scaled | `+0x8C`, 0x20 LONG GRAB |
| rail `+0x24` | `+= speed * dt` | distance * 0.00005 | `+0x98`, 0x1D LONG RAIL |
| press `+0x2C` | `+= dt` | dt * 0.01 | `+0x90`, 0x1E LONG PRESS |
| `+0x6C` | `+= dt` | dt * 0.05 | none |
| handplant `+0x78` | `+= dt` | dt * 0.05 | `+0x94`, 0x1F LONG PLANT |

The rail branch also adds `distance * 0.0002` to `+0x1C` while an up-vector component is negative (read as the
rider being inverted on the rail; unconfirmed).
With a zero time scale, the hold timer stops but the hold increment is still added.

`0x00119210` checks only the current entry of an authored `{seconds or distance, points}` table, not every
crossed entry. On a crossing it advances the index once, computes `trunc(points * +0x1C4 + 0.5)`, frees the
types 0x1C..0x20, posts the given type for 1.5 s with the points and the integer threshold, and returns the
points, which the caller adds to `+0x84`. An entry of -1 is the sentinel. Tables (points before the multiplier):

| Table | Entries |
|---|---|
| air (s) | 6: 5000, 8: 5000, 10: 10000 |
| hold (s) | 3: 4000, 6: 2000, 9: 1000 |
| press (s) | 5: 1000, 10: 2000, then every 5 s from 15 to 120: 4000 |
| handplant (s) | every second from 2 to 12: 2000 |
| rail (distance) | 10000: 1000, 12000: 3000, 14000: 5000, 16000: 7000, 18000: 9000, 20000: 12000, 22000: 16000, 24000: 20000, 26000: 30000, 28000: 40000, 30000: 50000 |

## HUD-side update `0x00117FE0`

Called from the per-tick update; does nothing without a bank. In order:

- Slot 1 = pending points (value slot, arg = grade) while pending > 0.
- Slot 0xB while in control state 8 with sub-state `+0x2C0` != 3, otherwise freed. Slots 0x10..0x17 are freed each
  tick.
- In control states 2 and 5: the spin dial 0xD approaches `angle / 2pi` plus a small cosine wobble of the global
  tick, and slot 0xC is posted. In air control 5 only, the direction of the rotation already performed
  (signs of the air controller's spin and flip) selects the direction slots 0x10..0x17 and is compared with the
  stick/D-pad direction to produce a landing message (block `0x001185F0`..`0x001188CC`; messages from
  `0x00457820`):

| Angle between rotation and stick | Message (slot 0xE arg) | Bonus weight b |
|---|---|---|
| > 157.5 degrees | STALLED! (1) | 1 on the spin axis, 5 on the flip axis, 2 on diagonals |
| 67.5..157.5 degrees | OFF-AXIS! (2) or INVERTED! (3), chosen by the geometry | 3 / 2 |
| 22.5..67.5 degrees | LATE SPIN! (4) if the input angle is within 45 degrees of 0 or 180 degrees, else LATE FLIP! (5) | 1 / 2 |

While a message shows, slot 0xF carries b and `+0x1C` gains `b / 1200` per tick; `0x00117908` pays it at the
landing (PS2: a back flip stalled 60 ticks scored 4130, 30 ticks 2740). When the message changes, slot 2 is
rewritten with the bonus total. The update then continues:

- The boost widgets `0x001188F8`..`0x00118D4C` (see "Boost gauge HUD").
- Slot 7 = total `+0x198`.
- Slot 3 (combo): the shown points move toward `+0xA0` by at most 70 per tick; field10 holds a stopwatch
  value from the combo clock.
- Slots 2, 0x19 and 4 are refreshed.

## Grab scoring

The ordinary grab path of the lifecycle `0x001352A8` resolves a grab index through `0x00150118`. The 15 grab
mappings come from `0x0045AEB8 + index*20 + 4`; score definitions are 8 bytes at `0x00530600 + scoreID*8`,
two signed words: begin points and hold points. Score IDs below 19 are ordinary grabs, 19..34 tweaks, 35 and above
Ubers.

**Begin, `0x00119708`.** `+0x14 += beginPoints * 0.0001`; `+0x3C = holdPoints * 0.0001 / 60` (float bits
`38D1B717` and `35DFB23B`). A negative `+0x40` is started at 0; a running one is kept. IDs 35+ set `+0x5C`.
Then `0x001176F8` suspends the combo clock. The threshold index and completed durations are not cleared.

**End, `0x001197D8`.** First `0x00119068` inserts the ID into `grabs[3]`: into the first empty entry unless the
previous entry already holds it; a full list is kept. Then counts: ID < 19 -> `+0x4C`, 19..34 -> `+0x50`,
35+ -> `+0x54`, and for 35+ also `+0x58` when the rider's tier `+0x2F4` >= 6. Then `+0x44 += +0x40`, `+0x48`
takes the maximum, `+0x5C` = 0, `+0x40` = -1. The increment `+0x3C` and the combo clock are kept.

Both return exactly +0.0, so the `0x0010E098` calls that follow them never change the meter. Boost comes from
the commit at the landing, not from grabbing.

The Super Uber description says Ubers count in `+0x58` / `+0x118` at tier 10; the condition in `0x001197D8` is
tier >= 6, so by the code Ubers at tiers 6..9 count there too. Whether the PS2 runs covered that case is not
recorded.

## Trick identity, repeat history and monster tricks

**Identity `0x0011A8C8`.** Builds an 8-byte trick identity from the score object, returns a validity flag and
may flip the signs of `+0x34` / `+0x38` in place. It normalises rotations into signed 180-degree buckets, maps
recognised spin/flip/cork combinations through the 319-byte rotation tables at `0x0043D388` and `0x0043D4C8`,
and uses an explicit fallback record for rotations outside the tables. The identity also covers the special
records (`+0x70`, `+0x28` / `+0x20`), stance flags, up to three grabs and `+0x7C`. Rotation inputs come from
the air controller's scored rotation fields through `0x00119898` / `0x001198D8`.

**Repeat history `0x001190F0`.** Returns how many of the 10 history entries equal the identity, then writes the
identity at the cursor `+0xF8` and advances it mod 10. Nonzero `+0x08`, `+0x20`, `+0x70`, `+0x7C` or `+0x28`
skips both matching and insertion. An identity whose word-1 bits 11..17 equal 1, or whose word-0 bits 22..27
equal 1, skips matching but is still inserted. There is no occupancy bit; comparison is byte for byte.

**Monster tricks `0x0011B1A8` (PS2).** Compares seven bit fields of the identity (direction, spin, flip kind,
flip count, flip spin, grab, late grab) with the 24 rows of 16 bytes at `0x0043D608`, takes the first match,
replaces the identity with `{0, id << 27}` (so the trick name becomes the monster name) and returns the row's
bonus (10000, 20000 or 30000; for example id 1, Da Housecat = FS 540 G-Money, 10000). The callers
(`0x0011A228` at the landing and `0x0011A168` at each new air trick) then add `bonus * 0.0001` to `+0x14`,
post slot 0x32 with the bonus for 1.5 s and call `0x0029B7E0` (Arcade_Uber variant 8, "Monster Trick"). The
popup and speech happen only for a match (bonus > 0).

- Nothing checks unlocks in gameplay: every monster trick scores whenever performed.
- The history then holds the monster identity, so the same monster again is a repeat: points halved (7020
  against 14040), popup 0x24; the bonus popup and speech still fire.
- A late flip added after the Uber does not split the trick; it joins the same identity (for example
  FS Rodeo G-Money), so there is neither a monster nor a repeat.
- Slot 0x32 is drawn only when the HUD flags lack bit 2 (free ride, backcountry); the race and freestyle flag
  words have it, so events show no monster popup.
- Eleven monster tricks were performed on the PS2 with matching score, popup, name and speech.

## Commit `0x0011A228` and combos (PS2)

`0x0011A228` receives stance, alternate, style, flag and a takeoff flag:

1. Free slots 1, 2, 4 and 0x1C..0x20.
2. Build the identity (`0x0011A8C8`).
3. If pending points (`0x00117948`) > 0:
   - if the identity is valid: the monster check (block at `0x0011A334`), the repeat count (`0x001190F0`), and
     the trick name into slot 0 through `0x00118FF8` (arg 1 for a repeat);
   - `divisor = repeats + 1`; grade from the pending points; combo add `0x00117638(pending / divisor)`;
   - meter delta = `+0x14 / divisor` (the division at `0x0011A440`), returned to the caller;
   - multiplied points (`0x00117990`) divided by the divisor and rounded down to 10;
   - statistics: `+0x110` += 1, grade counter, best trick, degree totals, sums of the per-trick counts
     (`+0x114 += +0x54`, `+0x118 += +0x58`, `+0x11C += +0x74`, ...), maxima of air/hold/rail/handplant;
   - total = multiplied + bonus `+0x84` + inverted, added to `+0x198`; popup 0x23 (0x24 for a repeat) with the
     grade for 2.5 s and slot 0x18 for 0.7 s, or the career award kind 0.
4. If (at a takeoff) `+0x20` and `+0x28` are 0, or (otherwise) the style and flag arguments are 0, and either
   `+0x14` > 0 or the combo clock is suspended, `0x00117708` sets the clock to at least 1.5 s.

The returned meter delta ignores `+0x18`, `+0x1C4`, the bonus and the display rounding, so dividing displayed
points by 10000 is not equivalent.

**Combo add `0x00117638`** (points > 0): count `+0x9C` += 1, then
`scale = clamp((count + 10) * 0.05, 0.5, 2)`, `+0xA0 += trunc(points * scale)`, clock -1, slot 3 updated.

**Combo expiry `0x00117718`.** When the clock runs out on the ground: if count >= 2 and points > 0, add the
points to `+0x198`, the count to `+0x134`, update the best combo `+0x184` / `+0x188`, and post 0x26 (arg =
count) plus 0x18, or the career award kind 2. Then the combo reset. The finish `0x001193E0` (called from
`0x00125108`) pays an open combo the same way, so it reaches `+0x198` (not checked on the PS2).

## Score events at rider boundaries

Each rider-side wrapper calls a score routine and passes its return value to the meter award `0x0010E098`.

| Event | Caller -> score routine | Behaviour |
|---|---|---|
| landing | `0x0010E910` -> `0x00119D40` | the caller passes stance = (rider `+0x320` xor `+0x324`) != 0, alternate = surface normal z < 0.7, and flag = rider `+0x330`. If the new style is nonzero and points are pending, `+0x14 += 0.13`; then commit, per-trick reset, and seed the new mode (stance, alternate, style/flag and their copies and timers) |
| takeoff | `0x00114298` -> `0x00119E38` | commits with the takeoff flag and resets; while `+0x70` is set (an active rail Uber) it keeps the pending trick instead. Seeds stance, alternate (set by the ramp branch at `0x00114660`), style/flag from the old copies, and air time 0 |
| new air trick | air control phase 3 (`0x00133734` inside `0x00133308`) -> `0x00119C98` -> `0x0011A168` | records the finished rotation (identity, monster check, history, name slot) without awarding points; then restarts the rotation fields, sets `+0x08` and suspends the combo clock; returns 0 |
| bail | crash entry `0x0010EB30` -> `0x00119B08` | crash counter (`+0x124`, or `+0x12C` and popup 0x2D when an attack flag is set); lost points `0x0011A7A8` into `+0x1A0`; returns -0.25 if points were pending; both resets |
| quick recovery | `0x0010F280` -> `0x00119BB0` | popup 0x21 RECOVERED!, returns +0.1 |
| reset placement | `0x00119368` | lost points into `+0x1A4`, both resets, `+0x120` += 1; returns `meter * -0.7` or `meter * -0.1`, chosen by an argument |
| point pickup | stage script -> `0x0010F1C0` -> `0x0010E8B8` -> `0x00119608` | `trunc(points * +0x1C4 + 0.5)` into `+0x198`, popups 0x23 and 0x18 (or career award kind 1); returns 0 |
| multiplier pickup | `0x0010F1C0` -> `0x0010E830` (in the air or on a rail) -> `0x00119448` | `+0x130` += 1; if the value exceeds `+0x18`, slot 4 = the value and `+0x18` = value; returns 0 |
| knockdown dealt | `0x0010E468` -> `0x00119400` | `+0x128` += 1, popup 0x2C for 1.5 s, then `0x0010E098(attacker, 1.0, category 2)` (PS2) |
| auto reset | `0x0011A088` (`cRiderMetrix_evAutoResetSurface__FPv`) | reason 1 of the reset path `0x00116120` posts "Wrong Way!" (0x33) (PS2) |

The lost-points routine `0x0011A7A8` posts 0x25 for pending points, 0x27 for combo points and 0x28 for bonus plus
inverted points (freeing their live slots first), and returns the pending points.

**Finish-line trick bonus `0x001194C0` (PS2).** The race progress step (block `0x00113014`..`0x001130A8` inside
`0x00112FB0`) walks the checkpoint list at `0x004D33B8`: up to six `{int value, float distance}` entries ended by
a 0 value. A checkpoint is crossed when the rider's best remaining distance (`+0x4D4`) passes its distance.
Each crossing pays the value through `0x001194C0`: popup 0x29 for 2.5 s and the Arcade_Bonus speech
(`0x002A3CE8`) with the value. Rules:

- Bit 9 of the global flags at `0x005308D0` disables the bonus, as does any game mode (`0x00535C12`) other
  than 1.
- Event handlers 1, 2, 5 and 6 (handler id at `*(G+0xC0)+4`, G the game object) pay it. Handler 0 (freestyle)
  pays it too; with freestyle kind 1 it also adds `value * 60` ticks to the time limit, and pays only while
  the run is inside the limit. Other handlers were not seen on the PS2.

## Landing wrapper `0x0010E910`

1. `0x00119D40` (commit + reset) returns the meter delta.
2. Uber tier progression (block `0x0010E9B4`..`0x0010E9F4`), before the award: if the run Uber count `+0x114`
   grew and the tier is below 10, `tier += min(growth, 10 - tier)`; reaching 10 sets the timer `+0x2F0` to
   60 s.
3. `0x0010E098(delta, category 1)`; a positive award clears `+0x2EC`.
4. For human riders, a landing reaction (block `0x0010EA28`..`0x0010EAA4`): combo paid at this landing ->
   `0x0010E028(3)`; else Ubers committed -> `0x0010E028(2)`; else a "great trick" -> `0x0010E028(1)`.
   `0x00149778` decides a great trick: the landing's total gain >= `0x0045A2B0[clamp(level - 1, 0, 10)]`, with
   level from `0x00148950` = `max(1, sum(attribute byte / 5) / 7)`. The table:

| Level index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| Points | 3000 | 5000 | 7000 | 9000 | 12000 | 15000 | 20000 | 25000 | 30000 | 40000 | 50000 |

`0x00115B58` plays the requested reaction: kinds 1..3 play clip semantic 315 (kinds 1 and 2 also call the trick
speech `0x0029FF80`); kinds 5 and 6 play 318, only in control state 0, with the animator's current (all-bone)
mask. `0x001200D0` runs after `0x00115B58` in the tick, so a reaction it requests plays on the next tick (PS2).

## Grab, tweak and Uber lifecycle `0x001352A8`

The lifecycle keeps only the phase (owner `+0x234`) and grab index (`+0x238`); everything else comes from the
current animation classes and markers and the live boost state. Animation channel 1 is the upper body, channel 2
the main body.

| Phase | Behaviour |
|---|---|
| 0 | request the ordinary main clip, or cancel it when the identity releases |
| 1 | wait for marker bit 1; begin ordinary scoring, pause the main clip, optionally start the upper-body clip |
| 2 | hold the grab. Release: end ordinary scoring, fade upper channel 1, resume main 2. Tweak input (Square): fade channels 1/2 by 0.1, choose the authored tweak or Uber main clip, call `0x0029A530`, apply the stat-derived rate, enter 3 |
| 3 | on matching identity + tweak + marker bit 1: pause main 2, begin the mapped advanced score, start the authored upper clip, enter 4. Otherwise marker bits 1/2/3 can begin and end the score in the same tick and enter 5, even with the input still held |
| 4 | hold the advanced trick. Release: end its mapped score, fade upper 1 by 0.33, resume main 2, enter 5 |
| 5 | wait for class 2 or marker bit 3. Either chain into another authored Uber with a forced main request, or reset to phase 0 / index -1 |

- Upgrading from phase 2 does not end the ordinary score. The advanced score begins later and shares the hold
  timer until its own end call.
- Initial Uber selection needs a nonzero timer `+0x2F0`, capability `+0xB2C` bit 0, and a non-sentinel
  mapping; otherwise the tweak is chosen. The tier variant (tier >= 5) is sampled once per call. Phase-5
  chaining needs main class 20, tweak input, a requested index and an available mapping, but does not recheck
  the timer or capability.
- The returned grab-active flag uses the main class cached before the phase-5 reset/restart: classes 18..20
  return true even if the phase has just reset to 0. It gates the air controller's angular limits.
- `0x0029A530` is a sound/feedback call on both tweak and Uber entry, not a boost award.

**Mappings.** Grab profiles hold `grabs[15]`, `tweak[15]` and `uber[2][15]` (two tier variants). Each definition
has a main semantic, an upper semantic, a score ID and authored begin/hold points. The Uber of grab slot c is
looked up live, `0x001352A8` -> `0x00150198` / `0x001502C8` / `0x001503F8` -> `0x0014FEA8`, from the row given by
the byte at `0x00530EC0 + bank*0x13EC + char*0x1FE + c*6 + (tier >= 5)` into the table at `0x0045AEB8`. Byte +0
is the hidden base Uber used below tier 5; byte +1 is the lodge "Ubertrick Setup" selection used from tier 5
(PS2). Special characters have their own overrides (five special-character types).

**Leg IK weight `0x00120D90`.** Separate from the lifecycle. The rider timer phase `0x001210B0` calls it after all
`0x00121068` controller updates and before the `0x001211F8` smoothing, so it sees the newly requested main
class. Classes 20..26 approach 0, others approach 1, with step 0.05 (float bits `3D4CCCCE`) and authored
snapping thresholds. It runs once per tick.

## Boost meter

**Award `0x0010E098(rider, delta, category)`.**

- Policy 3 (`+0x304`) or a zero delta: return without effects.
- A positive delta first calls `0x00149690`, then requires `category & +0xB28`; negative deltas skip the mask.
- `0x0029AB08(old meter, delta)` is notified, then `meter = clamp(meter + delta, 0, 1)`.
- A positive award that fills the meter with `+0xB2C` bit 0 set: if `+0x2F0` is 0, request notification 5
  (presumably `0x0010E028(5)`, as reaction kind 5; unconfirmed); a tier <= 0 becomes 1 (positive tiers are kept); at
  tiers 1..9, `+0x2F0 = max(+0x2F0, 20)`. This starts Tricky (PS2).
- A negative change clears `+0x2F0` unless the tier is 10.

Categories seen: 1 for landing commits, 2 for knockdowns. Penalties: -0.25 on a bail with pending points, +0.1 on
a quick recovery, `meter * -0.7` / `meter * -0.1` on reset placement.

**Controller `0x00114130(held, pressed)`.** A press ORs the feedback flag (`0x002F6AC8`). While held with a
nonzero meter: when boost starts, the amount `+0x2FC` is 1 if meter > 2/3, 0.625 if meter > 1/3, else 0.25, and
the start callback runs; the meter drains by the constant at `0x0049B4FC` (gp-0x7BF4) per tick while the drain
window is 0, the policy is nonzero and the tier is below 10. Otherwise the amount returns to 0, with the
denied callback when held and pressed, and the stop callback when an amount was active. Callers: control state
0 passes held and pressed (its jump-entry frame returns before the call); control 2 passes held and no press
(release returns first); control 5 passes false, false (its encoded bit 14 means tweak there, not boost).

**Timers `0x001200D0`**, after controller dispatch and before the common smoothing:

- the drain window and the modifier `+0x2EC` decay (the modifier only above a threshold or when not airborne);
- `+0x2F0` counts down, but while airborne or in control state 12 (handplant) it stops at a floor value instead
  of running out;
- when the timer runs out, `0x0010E028` requests reaction 6; at tier 10 the meter stays 1, and when the timer
  reaches 0 the tier drops to 5 with 20 s of Tricky (PS2);
- below tier 10, policy 0 forces the meter to 1 and policies 1/2 apply normal/fast decay.

The virtual `0x00140BC8` it calls is a getter whose result is unused.

## Tricky, Uber tiers and Super Uber (PS2)

- A full meter starts Tricky: `+0x2F0 = max(+0x2F0, 20 s)`, tier 0 -> 1. During Tricky, holding a grab
  combination and adding Square performs the Uber of that slot.
- Each committed Uber adds one tier, capped at 10. The nine letters of SUPER UBER show the progress.
- Tier 10 is Super Uber: `+0x2F0` = 60 s and the meter is locked at 1. When the 60 s run out the tier drops to
  5 with 20 s of Tricky and reaction 318 plays.
- Several Ubers in one air all commit at the landing (`+0x54` = count) and advance the tier by the count (two
  per air: 1 -> 3 -> 5). A Square tap between them is allowed.
- An Uber crash applies the bail penalty, ends Tricky (sound 0x69) and stops the pending-Uber sound.

## Monster unlocks and Career Highlights

- The front-end list (`0x001F5DA0`, order table `0x00441B40`) shows list position p as unlocked when
  `p % 3 < medal[p / 3]`. `medal[s]` is the profile byte `R+0xBB8+s`, written only by `0x00155390` from the
  post-event personal bests (`0x00155420`): the number of thresholds of `0x00440ED0` reached. Gameplay never
  checks these medals.
- `0x00155420` records the run statistics of the score object per character at the end of every Conquer the
  Mountain run (finish block `0x001251B8` inside `0x00125108` -> `0x00238358` -> `0x00154AB8`; restart / quit
  `0x001297C8` / `0x0012B090` record with no score or time). Not in free ride; human only. It keeps `{best,
  course}` for KO `+0x128`, Ubers `+0x114`, super Ubers `+0x118`, Uber grinds `+0x11C`, best combo `+0x184`,
  handplant `+0x158`, rail `+0x154`, air `+0x14C` (floats as `(int)(f + 0.5)`), race time (minutes) and event
  score (slope style, big air, pipe, rival points). A value >= the best replaces it and raises the medal to the
  thresholds reached; medals never go down.

| Medal s | Statistic | Thresholds |
|---|---|---|
| 0 | StayOnRail | 2500 / 12000 / 30000 |
| 1 | HoldHandplant | 3 / 5 / 8 |
| 2 | StayInAir | 5 / 8 / 9 |
| 3 | KOPeopleRace | 3 / 6 / 10 |
| 4 | DoUberGrind | 5 / 8 / 10 |
| 5 | DoSupUber | 5 / 8 / 10 |
| 6 | GetPoints (score / 100) | 1500 / 5000 / 10000 |
| 7 | DoXCombo | 10 / 20 / 100 |

- Rider Details -> Career Highlights is the FE.LUI screen `35car_stat`. Per row r, `0x001F5DA0` fills `hl<r>` with
  the locale `"%s%d"` of the stat label from `0x00441BA0`, `checkmark<r>` / `checkbox<r>` by tier < medal,
  `hlsec<r>` with `"%s Monster Trick"` and the name, `hlsec<r>a` with the trick or the locked text, and the up/down
  arrows by scroll position. The page switch `0x001F5A38` hides the other pages' groups (`race_platinum`,
  `freestyle_platinum`, `ridersbest`) and the dashes (PS2: the screen filled this way matches a PS2 frame).
- There is no post-event unlock message: nothing queues one when a medal rises. The stats screen shows the medal
  sum as `"%d / 24"`.

## Boost gauge HUD

### Score-side widget updates (inside `0x00117FE0`)

All use the shared "approach" step: move the old value/maximum toward the target by at most the step, with
strict comparisons, EE nearest division for the ratio and guard-bit add/sub. No elapsed-time multiplier.

| Block | Slot (bank offset) | Behaviour |
|---|---|---|
| `0x001188F8`..`0x00118A24` | 5 (`+0x30C`) preview, 6 (`+0x3A8`) stored | preview target `min(meter + +0x14, 1)` (policy 3: meter only); stored target the raw meter; step 1/60 (`0x0049B680`, `0x0049B684`, gp-0x7A70 / -0x7A6C). A free slot starts at the raw meter |
| `0x00118A28`..`0x00118AF4` | 8 (`+0x4E0`) earned letters | tier 0 frees it. Otherwise init 0, `count = min(tier, 10) - 1` into arg, target `min(count / 9, 1)`, step 0.0066666673 (`0x0049B68C`, gp-0x7A64) |
| `0x00118AF8`..`0x00118C28` | 10 (`+0x618`) pending letters | `remaining = 10 - min(tier, 10)`. No Uber in the current trick (`+0x54` and `+0x5C` both 0) or remaining <= 0: an initialized slot calls hide `0x0029B3C0` through `0x0028B180`, then is freed. Otherwise `count = min(+0x54 + (+0x5C ? 1 : 0), remaining)`; init writes 0 and calls show `0x0029B0E0`; target `min(count / 9, 1)`, step 1/60 |
| `0x00118C2C`..`0x00118D4C` | 9 (`+0x57C`) Tricky timer | absent: appears only if `+0x2F0` > 0, initialized to 0 with `0x00299638`, no update that tick. Present: freed only when its old ratio == 1 and the timer == 0, then `0x002997B8`. Otherwise target `1 - timer * 0.05` (`0x0049B698`, gp-0x7A58; not clamped), step 1/60 (`0x0049B69C`, gp-0x7A54), arg = `min(tier, 11)` |

The tier-0 branch of slot 8 (`0x00118A44`) jumps straight to `0x00118AFC`, loading in the delay slot, and the
pending-letter update ends by branching to `0x00118C30`: block boundaries are not simple fall-throughs.

### HUD update pre-pass (inside `0x001EA930`)

The single-player per-player HUD state is at owner `+0x48` (read at `0x001EC9F0`..`0x001EC9F8`); its phases are
written in `0x001EBC94`..`0x001EBF2C`.

- Flash phase `+0x64` (`0x001EBDF4`..`0x001EBE60`), from slot 9: absent -> -1; ratio exactly 1 -> -1 (and additional
  text is toggled through `0x001E94E0`, probably the Uber hint's `+0x55C` flip below; unconfirmed); negative -> 1;
  otherwise `phase += (1/30) / ((1 - ratio) * 0.9104144 + 0.0299726)`, wrapping while > 2. The flashing speeds up as
  Tricky runs out.
- Pending-letter phase `+0x68` (`0x001EBED4`..`0x001EBF2C`), from slot 10: absent -> -1; negative -> 0.5;
  otherwise `+= 0.0879163444`, wrapping while > 1.
- Palette `+0x54` from slot 9's arg: `0x004C8428` gold below 5, `0x004C8448` orange below 10, `0x004C8468` red
  at 10, `0x004C8488` purple otherwise.
- Uber hint gating `+0x84` (see the trick HUD).

### Gauge, orb and glow draws (inside `0x001EC3F8`)

- `0x0021D1A0` draws gauge widgets 4/5/6/7 (backgrounds and the stored/preview fills), submitting through
  `0x00379860`. Layout descriptors at `0x004768B0`: bottom 392, height 242, centre x 582, coil width 50, stem
  background 8, preview 4; the single-player owner scales by 1.01680672 and has eight middle sections. Sprites
  come from `OV_1.SSH` image 4 (`hude`: silver coil, orb and other HUD sprites; OV.LUI atlas page 4, texture
  handle 0x656). The ordinary colour ramp is at `0x001ECD60`, with palettes `0x004C84C8`, `0x004C84E8`,
  `0x004C8508`; material order fields 11..14.
- Orb (`0x001EFC58`..`0x001EFDB0`): sprite at owner `+0x538`, descriptor 3, centre (582, 127), 32 x 32, UV
  (0.5723, 0.1973)..(0.6934, 0.3184). With phase >= 0 it uses the palette `+0x54` and multiplies the width by
  `phase` (phase < 1) or `2 - phase`; otherwise the descriptor colour at full width.
- Glow (`0x001EFDB4` onward, `0x0021E7E0` -> `0x0021EA00`, only while phase >= 0): the orb glow pads the orb by
  17.00098 per side, alpha 0.2603549 at phase 0 rising to 0.4999854 at phase 1 and back (triangular), material
  order 10, texture handle 0x5F5. Active flash submits five glows: orb, three coil sections (left and right
  halves plus a constant-U centre strip) and the stem.
- `0x001EFE94`..`0x001F0040`: during the flash, the gray coil (group 0) is tinted with the palette and widget 5
  swaps the gray stem (group 1) for the white stem (group 3), also tinted; the fills stay white.

The slot-type switch uses the jump table `0x0046EC70` (52 entries, types 0..0x33, default case `0x001EFAC0`). Its
targets lie between `0x001ECCB8` and `0x001EFAC0`. The lookup splits a function at `0x001EF7BC`, but that start
comes only from a data pointer and the switch has cases on both sides of it, so these blocks are probably all part
of `cOVStateHUD1P_onRender2D` (unconfirmed). Types 9, 0xC, 0xD, 0xF, 0x10..0x18, 0x1A, 0x1B, 0x22 and 0x2D go to
the default case. The notes also name `0x001E9A30` as the slot-case routine; how it relates to this switch is
unresolved.

### SUPER/UBER letters

- `0x0021ED48` draws one letter; placement helpers `0x001E91F8`, `0x001E9220`, `0x001F10F8`, `0x0021E750`,
  `0x0021E7A8`; font submission `0x00391CB0`, outline sprite `0x001F1190` (through `0x001E91A8`). Glyphs use
  HUDFONT (not FEFONT).
- The nine letters spell UBERSUPER in index order: UBER at x 552/568/584/600, y 81; SUPER at x
  544/560/576/592/608, y 59. Descriptors `30 + 2*letter` in single player. Scale (0.6667, 1).
- Modes: 0 = dim glyph, ARGB (0.4, 1, 1, 1); 1 = the same plus a white outline sprite; 2 = the descriptor's
  blue-green glyph ARGB (1, 0, 0.4, 0.651) plus the white outline, and a glow when phase `+0x64` >= 0. The
  first U's outline is at (551, 80), 14 x 20, texture 0x656. Glyphs are submitted first but with material order
  12 against 11 for outlines, so outlines end up underneath.
- Inactive letters: the loop at `0x001F0110`..`0x001F01D0` starts at the first inactive index (a stack local)
  and draws through index 8, changing the font shadow offsets around the loop.
- Earned letters: type 8's case at `0x001ED790`..`0x001ED8F4` reads the count from slot `+0x0C` (at
  `0x001ECC74` / `0x001ECC84`) and draws active glyphs in index order. Letter boundaries advance by 1/9 of the
  smoothed fraction, so the fraction decides which letters have appeared, with a scale pop of coefficient
  1.80013132 (`0x0049DA38`, gp-0x56B8).
- Pending letters: type 10's case `0x001EF6AC`..`0x001EF7A0` draws mode-1 letters after the earned prefix; the
  outline's horizontal scale is `(phase - 0.5) * 2`, which goes negative and mirrors the sprite.

### Glow texture

Handle 0x5F5 is owned by the renderer, not the OV atlas. `cOVStateHUD1P_onCreateScreen` stores
`renderer+0xF50` at owner `+0x474` (`0x001EA1CC`..`0x001EA1E0`), with owner UV `+0x480..+0x48C` = 0, 0, 1, 1.
The setter at `0x003948B0` inside `0x003946E8` writes `renderer+0xF50+index*4`; no direct call to it was
found. The renderer's virtual at slot `+0x1CC` is `0x0037D938`: descriptor = `*(renderer+0x18F4 table +
handle*4 + 8)`. Handle 0x5F5 resolves to the texture `part`: 64 x 64, 8-bit indexed (PSMT8H) with a palette.
The same bytes are entry `part` of `DATA/TEXTURES/PARTICLE.SSH` (record format 2, texels at +16, palette at the
recorded block size + 16, palette in the CSM1 order that swaps index bits 3 and 4).

## Trick HUD draw

Helpers: align `0x0021E750`, measure `0x00391FB0`, text and lerped text `0x001F1B30` / `0x001F1E28`, wrapped
text `0x001F2AA0`, stars `0x0021F338`, and the sine-table pulse at `0x00504FB8`. Layout descriptors are at
`0x004768B0`. Within a layer, glyphs go above sprites: popup digits cover the grade star (PS2). The type 1
score uses a per-player pulse at owner `+0x70` whose writer was not found. Combo text, popups, the total and the
trick names drawn by these cases were compared with PS2 screenshots (PS2).

**Uber hint (PS2).** The pre-pass at `0x001EBCA4` (inside `0x001EA930`), the layout `0x001E92A8` and the draw
`0x001E95A0`.

- Owner `+0x560` holds `"UBER TRICK = @l1 + @square"` or the `@r1` variant, from the table at `0x004A21D0`
  (gp-0xF20) indexed by owner `+0x55C`. `+0x55C` starts as `0x003177F0` (`BXrand__Fv`) `& 1` on the visual RNG
  (`0x004FF018`) at HUD creation, and flips on each pre-pass that sees slot 9 at ratio 1.
- Layout: FEFONT (owner `+0x428`) at 0.7. Text runs split at `@` and are measured by `0x003921F0`; icons come
  from the table at `0x004C8980` (`bsl1` / `bsr1` 28 x 16, square 21 x 20; unscaled). Height =
  `max(29 * 0.7, tallest icon)`.
- Drawn after the slot loop (`0x001F0228`) at descriptor 73 (320, 460), centred, bottom-aligned, white with a
  (2, 2) shadow, when the per-player flags have bits 21 and 24 and the pre-pass granted bit 25: slot 9 live, its
  ratio != 1, and no live slot of type 0, 0x21 or 0xB. After the finish (`0x001EB9FC`) nothing is drawn.

**Frame order (PS2).** Every frame runs the HUD draw (`cOVStateHUD1P_onRender2D`, vtable slot at `0x004741DC`),
then the HUD update (`0x001EA930`, vtable slot at `0x004741C4`), the human input provider `0x00127998`, the
rider post `0x00121750` (landing commits), `0x00117C28`, and then the tick counter advances. So frame N draws the
bank after tick N-1, while the pre-pass state it uses (palette `+0x54`, flash phase `+0x64`, hint gating `+0x84`)
came from frame N-1's update of the bank after tick N-2.

## Audio calls (PS2)

| Address | Role |
|---|---|
| `0x002906B8` | every SFX voice start (bank slot, sound index) |
| `0x002B1458` | speech requests |
| `0x002A3DE0`, `0x002A3C00`, `0x002A3CE8`, `0x002A3EB8`, `0x002A3B18` | arcade speech categories (variant masks); `0x002A3CE8` is Arcade_Bonus |
| `0x0029B0E0` / `0x0029B3C0` | pending-Uber sound start / stop; the live voice is kept at audio system `+0x5FDC` |
| `0x00299638` / `0x002997B8` | Tricky start / end |
| `0x0029B430` | Uber commit. Receives the run Uber count before this commit's increment; Arcade_Uber 1 plays when that count reaches 4 (the 4th Uber) |
| `0x0029B738` | Super Uber speech (Arcade_Uber 2), one tick after the landing that reaches tier 10 |
| `0x0029B7E0` | monster trick speech (Arcade_Uber 8) |
| `0x0029AB08` | meter change notification from `0x0010E098` |
| `0x0029A530` | tweak/Uber entry feedback from the grab lifecycle |
| `0x0029FF80` | trick speech with landing reactions 1 and 2 |
| `0x00296310` | crash sound; the airborne crash-loop path `0x0012D4E8` also plays it |
| `0x0028B180` | audio system accessor used by the pending-letter widget |

- Sound 0x65 is the meter fill tick (driven from value slot 6), 0x68 the Tricky countdown tick, 0x69 the Tricky
  end. The points tick is evaluated only while points are pending.
- `0x0029AB40`, `0x0029B738` and `0x0028C8C8` run in the per-frame audio update before the frame's game tick,
  so they read the previous tick's state (fill ticks, Tricky countdown, whoosh).

## Related gameplay facts (PS2)

- The animator's pending next rate `+0x1C` (setter `0x003158E0`) is given to every new sequence by `0x00311F00`;
  placement `0x00311A50` and the air selector reset it after their own play; `0x0012C678` sets 0.75 only around
  the finish reaction (`0x00115B58`) and then back to 1. This affects spin timing, prewinds and finish reactions.
- The prewind branches of `0x0012E9B8` use class 10 and semantic 21, and `0x00114CC0` makes a reverse turn when
  rider `+0x328` == 0 and `+0x2DC` == 0.
- Air spin rates come from `0x0012F620`. The speed-limit table is indexed thick snow [0..7], groomed [8..15],
  ice [16..23], +24 with the maxed stat; switch stance is 2% slower.
- The landing classifier has a crash rule for main classes 18..21 (grab, tweak and Uber classes).
- The Select warp (ResetPath 0x1000) goes through the reset path `0x00116120`; a warp from a rail runs
  `0x00132048` / `0x0013C5A0`.
- Countdown beeps: `0x0029C420` plays when the countdown's remaining ticks are a multiple of 60, and at 0 on
  the GO tick.
