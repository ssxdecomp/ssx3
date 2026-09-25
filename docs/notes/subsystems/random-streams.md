# Random number streams

SSX 3 keeps two global six-word random generators side by side in `.bss`: the presentation stream at `0x004FF018`,
drawn through `0x003177F0` (`BXrand__Fv`), and the gameplay stream at `0x004FF030`, drawn through `0x00317810`
(`AIrand__Fv`). A third instance of the same generator at `0x004C9548` is used only to build the computer-rider
roster. Separate from these, board and snow effects use a one-word LCG at `0x004A3AFC`, and particle sprites use the
VU's own random unit. Every in-race draw happens inside the game update, once per game tick, in a fixed order.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

Hex constants that are not addresses are written with an `h` suffix (for example `E9507Ch`), so they are not
mistaken for EE addresses.

## Where it lives

- `src/bx/bxrandom.cpp`: the generator (`0x00317958` `cBxPseudoRng_Seed`, `0x00317A08` `cBxPseudoRng_NextInt`)
  and all the wrappers from `0x003177C8` (`BXsrand__FUi`) to `0x00317930`.
- `src/bx/ps2main.cpp`: the boot seed, inside `0x0031ADB0` (`systemInit`).
- `src/main/gameload.cpp`: `0x0022EBC8` (`cGame_load`), which draws the roster seed, and the race game update
  `0x002306B8`, which fixes the per-tick order.
- `src/main/gamestate.cpp`: the roster-generator wrappers `0x00237CB0` (seed) and `0x00237CD8` (draw).
- `src/main/gamemode.cpp`: event start `0x0023A108`, roster build `0x0023A4F0`, shuffle `0x0023C770`, copy to the
  race slots `0x0023A668`.
- Presentation-stream consumers: `src/render/particle.cpp`, `src/render/graphicsman.cpp`,
  `src/object/instanceman.cpp`, `src/object/flagset.cpp`, `src/render/lightman.cpp`, `src/main/ssxapp.cpp`,
  `src/camera/camera.cpp`, `src/sound/bankmonitor.cpp`, `src/sound/soundsys.cpp`, and the camera splash in the
  unsplit segment `asm/1F1548.s`.
- Gameplay-stream consumers: `asm/1218.s` (rider pairs, crash and related rider code), `src/ai/computer.cpp`,
  `src/ai/ai.cpp`, `asm/14B10.s`, `src/ai/control/handplantcontrol.cpp`, plus the `AIrandf__Fff` callers listed
  below.
- State save and restore: `src/replay/replay.cpp`, `src/replay/playbackman.cpp`, `asm/156860.s`
  (`cGameComm_syncGame`).

## Streams at a glance

| Stream | State | Draw | Seeded | Working names in older notes |
|---|---|---|---|---|
| Presentation | `0x004FF018`, 6 words | `0x003177F0` `BXrand__Fv` | once at boot, by `0x003177C8` (`BXsrand__FUi`) | visual RNG, particle RNG, presentation generator |
| Gameplay | `0x004FF030`, 6 words | `0x00317810` `AIrand__Fv`, `0x00317830` `AIrandf__Fff`, `0x00317890` | reset to the seed-0 state at the event load | gameplay RNG, shared game RNG, world RNG |
| Roster | `0x004C9548`, 6 words | `0x00237CD8` | `0x00237CB0`, from one presentation draw in `cGame_load` | roster generator |
| Visual LCG | `0x004A3AFC` (gp+0xA0C), 1 word | inline in each consumer | not covered here | visual LCG, trail LCG |
| VU random | VU `RINIT`/`RNEXT` | VU microcode | per emitter (see below) | sprite LFSR |

`0x004FF018` and `0x004FF030` are adjacent 24-byte objects. There is no separate per-rider generator. Every rider,
human or computer, draws from the one gameplay state in the order the tick runs them.

## The six-word generator (cBxPseudoRng)

### State layout

| Offset | Word | Role |
|---|---|---|
| `+0x00` | w0 | output word; it holds the last value returned |
| `+0x04` .. `+0x10` | w1..w4 | a chain of add-with-carry accumulators |
| `+0x14` | w5 | draw counter: it goes up by exactly one per draw |

Because w5 counts draws, the difference in w5 between two snapshots of the same state is the exact number of draws
between them. **(PS2)**: stepping the generator by the change in w5 between consecutive savestates of a Snow Jam race
lands exactly on the next savestate's six words, for all 44 pairs tested.

### `0x00317A08` `cBxPseudoRng_NextInt(state)`

It takes a pointer to the six words and returns a full 32-bit value:

```
s = w5 + w4;  c = (s < w5) || (s < w4);  w4 = s
for i in 3, 2, 1:  s = s + w[i] + c;  c = (s < old w[i]);  w[i] = s
s = s + w0 + c;  w0 = s
w5 += 1
if w5 == 0:  w4 += 1; if that wrapped, w3 += 1; and so on up to w1
             if w1 also wrapped:  s += 1;  w0 = s
return s
```

- The first carry test compares the sum against both addends. The later tests compare only against the word being
  added, so a carry is lost in the corner case where the incoming sum plus carry wraps exactly. The game's code
  behaves this way.
- The step can be undone, so a state can be walked back to where it was seeded. This is how the roster seeds were
  checked (see below).
- The only direct callers are `BXrand__Fv`, `AIrand__Fv` and the roster wrapper `0x00237CD8`.

### `0x00317958` `cBxPseudoRng_Seed(state, seed)`

Each word is the seed plus a running sum of six fixed constants (mod 2^32): `w[i] = seed + K0 + ... + Ki`.

| i | Ki (hex) | w[i] for seed 0 |
|---|---|---|
| 0 | `F22D0E56h` | `F22D0E56h` |
| 1 | `96041893h` | `883126E9h` |
| 2 | `3DF3B646h` | `C624DD2Fh` |
| 3 | `40DDE76Dh` | `0702C49Ch` |
| 4 | `97327AE1h` | `9E353F7Dh` |
| 5 | `D1A9FBE7h` | `6FDF3B64h` |

- After seeding, w5 = seed + `6FDF3B64h`. The number of draws made since seeding is therefore
  w5 − seed − `6FDF3B64h` (mod 2^32).
- The seed-0 state is stored as a constant block in `.rodata` at `0x0048DCB0`.
- The only callers are `BXsrand__FUi` and the roster seed wrapper `0x00237CB0`.
- **Test vector (PS2):** boot seed `182200h` gives `B57109A9h` as the 130th draw. That is the roster seed of the
  reference sessions.

### Wrappers in `src/bx/bxrandom.cpp`

| Address | Name | Behaviour |
|---|---|---|
| `0x003177C8` | `BXsrand__FUi` | `cBxPseudoRng_Seed(0x004FF018, seed)`. Its one caller is the boot. |
| `0x003177F0` | `BXrand__Fv` | `cBxPseudoRng_NextInt(0x004FF018)`. It has 99 call sites in 34 functions. |
| `0x00317810` | `AIrand__Fv` | `cBxPseudoRng_NextInt(0x004FF030)`. It has 36 call sites in 21 functions, one of them `AIrandf__Fff`. |
| `0x00317830` | `AIrandf__Fff(a, b)` | One `AIrand` draw r. It computes u = float_bits((r & `7FFFFFh`) \| `3F800000h`) − 1.0, which is in [0, 1), and returns a + (b − a)·u. |
| `0x00317890` | – | a + b·`AIrandf(-1, 1)`: a value centred on a. Its only caller is the LiveComp constructor `0x00341AA0`. |
| `0x003178E0` | – | Copies the 24 gameplay-stream bytes out to a buffer, through the block copy `0x003E6574` (probably memcpy; unconfirmed). |
| `0x00317908` | – | Copies 24 bytes from a buffer into the gameplay stream. |
| `0x00317930` | – | Copies the seed-0 block `0x0048DCB0` into the six words its argument points to. |

`BXrand` has no float variant. The presentation consumers use the same mantissa trick inline:
`((r & 7FFFFFh) | 3F800000h) − 1` gives u in [0, 1), and 2u − 1 gives [−1, 1).

Callers of the copy helpers:

- `0x003178E0` (save): `0x002585B0` in `0x00258448` (`cGameComm_syncGame`), and `0x0026D83C` in `0x0026D818`
  (`src/replay/playbackman.cpp`).
- `0x00317908` (restore): `0x0025861C` in `cGameComm_syncGame`, `0x0026CCBC` in `0x0026CC48` (playbackman.cpp),
  and `0x0026DC60` in `0x0026DBF0` (`cReplay_restoreFrame`).
- `0x00317930` (reset to seed 0):
  - `0x0032059C` and `0x003205A8` in `0x00320550`, for `0x004FF018` and `0x004FF030` in turn. Just before, the same
    function calls `0x00316A00` on `0x004FF000`. Its entry test (second argument 0xFFFF and first argument non-zero)
    has the shape of a compiler-generated static initialiser (unconfirmed). If so, both streams hold the seed-0
    state before the boot seed.
  - `0x002437BC` in `0x00242EB8` (`src/main/streampause.cpp`), for the roster generator `0x004C9548`.
  - `0x00393B1C` in `0x00393048` (`src/render/font.cpp`). Its target was not traced.

## Seeding and lifetime

### Presentation stream `0x004FF018`

- **Boot seed.** `systemInit` calls `BXsrand` at `0x0031AE94`. The seed comes from `sceCdReadClock` (`0x00402520`):
  seed = c0 ^ (c1 << 3), where c0 and c1 are the two words of the clock result. c0 holds the status, second, minute
  and hour bytes and c1 holds the pad, day, month and year bytes, all BCD. Nothing reseeds this stream afterwards
  (`BXsrand` has one caller), so it carries on across events for the whole session.
- **Draws from boot to the first race (PS2):**
  - The boot makes one draw before the menus. The consumer is not identified.
  - The title, main menu, select and setup screens, the pause menu and the quit dialog make no draws.
  - Each event load makes 128 draws, then the roster seed. The 128 matches the 128 crowd timers that `0x002292E0`
    arms at the load.
  - So the first race after boot takes presentation draw 130 as its roster seed, whatever the menu timing, the
    character or the cheat path. The lineup of the first race is a function of the boot clock and the human's
    character.
- **Later events (PS2).** After the seed, the load, the overlay, the countdown and the race draw every frame:
  - from the seed to countdown tick 18: 1051 to 1261 draws, depending on the state;
  - from the countdown to the glide: about 5.2 to 5.6 per tick.

  The next event's roster seed is 129 draws after wherever the previous race left the stream. A restart does not
  rebuild the roster, so it does not draw a new seed.
- The per-frame count depends on the values drawn, not only on time. The crowd re-arms with `300 + r % 300`, the
  lightning makes a second draw only under a chance, and the emitters run for every rider. So the seed of a later
  event cannot be predicted from tick counts alone.

### Gameplay stream `0x004FF030`

- **Reset at the event load (PS2).** It is seeded with 0, so it holds the same six words as `0x0048DCB0`. The code
  that performs this reset is not identified here.
- **Load draws (PS2).** The load then draws N times. N depends only on the course and the human's character:
  - Snow Jam 10, Metro City 13;
  - one less when the human is Zoe, one more when the human is Moby;
  - 4 more when the human uses a cheat skin.
- **Countdown draws (PS2).** At the first countdown pass, each computer rider's start command draws twice: first the
  rider's `+0xDF0` steering amount, then its sign. For the k-th computer rider (k = 0..4) these are draws N + 2k and
  N + 2k + 1.
- This rule was fitted on 30 character states and holds for all 80 countdown states checked.
- **Replay and sync.** The replay and sync code saves and restores this state with `0x003178E0` and `0x00317908`;
  `cReplay_restoreFrame` is one of the restorers.

### Roster generator `0x004C9548`

- `0x00237CB0(seed)` is `cBxPseudoRng_Seed(0x004C9548, seed)`. `0x00237CD8()` is
  `cBxPseudoRng_NextInt(0x004C9548)`.
- **Normal path.** `cGame_load` draws `BXrand` at `0x0022EFE8` (return address `0x0022EFF0`) and passes the value to
  `0x00237CB0`.
- **Sync path.** `cGameComm_syncGame` first restores the gameplay stream (`0x0025861C`), then draws `AIrand` at
  `0x00258624`. The older notes call this the replay path and say it seeds the roster from a draw of the restored
  gameplay stream.
- `0x00242EB8` resets it to the seed-0 state (`0x002437BC`).

## Roster build `0x0023A4F0` (52 draws)

**When it runs.** The race rules object's event start `0x0023A108` (vtable `0x0047CF4C`) builds the roster:

- A Single Event (`0x00535C11` != 0) builds it whenever an event is chosen. `0x00238C80` resets the rules object,
  which sets roster `+0x84` = 1 and the round to 0.
- A restart keeps the roster.
- Conquer the Mountain builds it in round 1 and reuses it in the semi-final and the final.

**Build.** All the draws come from `0x00237CD8`. It makes ten entries:

1. Two different "Tricky" cheat riders (ids 10..16). The first is `10 + r % 7`. The second is `10 + r % 6`, plus 1
   when that is at or above the first.
2. The base riders 0..9 in id order, except the human's character and the peak rival.
3. The shuffle `0x0023C770`: 25 swaps, each of entries `r % 10` and `r % 10`.

That makes 2 + 50 = 52 draws per build.

**Peak rival.** `0x00145750` returns the peak rival. The peak index is read from the course table at
`0x0043D950` + event·100 + 0x54.

| Peak index | Rival | Rival when the human is that rider |
|---|---|---|
| 0 | Mac | Griff |
| 1 | Nate | Zoe |
| 2 | Psymon | Elise |

**Heats (`0x0023A108`).**

- Single Event and career round 1: entries 0..4 go to slots 1..5.
- Semi-final: the qualifier's top three, not counting the human (finish order at `0x00536708`), then entries 5..7.
- Final: the rival, the semi-final's top three not counting the human, then entries 8 and 9.

**Copy (`0x0023A668`).** It writes the words at `*(0x004A2C70)` `+0x18[]` / `+0x40[]` (gp−0x480). The code at
`0x002342B8` (inside `0x002341D0`) then fills the race copy at `0x00535B20`. An entry below 10 races as that base
rider. An entry of 10 or more is that cheat skin on the **human's** base character.

**Check (PS2).**

- Walking each countdown savestate's `0x004C9548` words back gives a freshly seeded state after exactly 52 draws.
  With that seed, the build reproduces the savestate's lineup in all 70 countdown states tested.
- Poking the `0x004FF018` words in a character-select savestate made the game produce exactly the predicted lineup.

## Presentation-stream consumers

### Callers of `BXrand`

Grouped by the function that holds the call. "Race" means the consumer draws during a normal race.

| Function | Sites | What it is | Race |
|---|---|---|---|
| `0x003710D0` (`src/render/particle.cpp`) | 1 | particle emitter update: one draw per active emitter per update | yes |
| `0x0036CCB8` (`src/render/graphicsman.cpp`) | 9 | set-piece emitter seeds: 9 per static emitter | when sections activate |
| `0x00370DC8` (`src/render/particle.cpp`) | 1 | script builtin 26 emitter: 9 + 1 seeds | when sections activate |
| `0x00352230` (`src/object/instanceman.cpp`) | 9 | MeshAnim (script builtin 13): 9 draws per node | on contact triggers |
| `0x0034B228` (`cFlagSet_CreateMesh`) | 1 | flag grid build: 4 draws (in a loop) per new flag slot | when sections activate |
| `0x0034C668` (`src/object/flagset.cpp`) | 1 | flag wind: one draw when the one-second timer wraps | yes |
| `0x002F39E0` (`asm/1F1548.s`) | 2 | camera splash update | yes, 1 per tick |
| `0x002F3810` (`asm/1F1548.s`) | 1 | camera splash spawn: crystal group size | heavy snowfall only |
| `0x00390C60` (`src/render/lightman.cpp`) | 2 | ScreenTint lightning | yes, 1 per tick |
| `0x00229530` (`src/main/ssxapp.cpp`) | 3 | 2D crowd flash timers | yes |
| `0x002292E0` (`src/main/ssxapp.cpp`) | 1 | arms the 128 crowd timers at the load | load |
| `0x001656B0`, `0x00165938` (`src/camera/camera.cpp`) | 12 + 12 | camera shake start and per-tick shake | when a shake runs |
| `0x002ADF60` (`src/sound/bankmonitor.cpp`) | 1 | returns one draw ("rand15" in the older notes) | rare |
| `0x002A4CA0` (`src/sound/soundsys.cpp`) | 1 | random element of a counted list: `count ? list[1 + r % count] : 0` | rare |
| `0x001E9AD0` (`cOVStateHUD1P_onCreateScreen`) | 1 | uber-trick hint: owner `+0x55C` = r & 1 | HUD creation |
| `0x0022EBC8` (`cGame_load`) | 1 | roster seed | load |
| `0x002E4D88` (`src/visualfx/boardwakefx.cpp`) | 3 | snowfall set-up | load |
| `0x0027B0C0` (`cSSXScriptEngine_GetScriptFromCategory`), `0x00279A70` | 1, 2 | script engine | load |
| `0x00160028`, `0x00160130` (`src/camera/camera.cpp`) | 2, 1 | camera-director nodes | no |
| `0x00156C70`, `0x00156EE0`, `0x00157080` (`src/be/beintreward.cpp`) | 1 each | awards | no |
| `0x001E1550`, `0x001E1AD0`, `0x001E2A08`, `0x001E3100` (`src/fe/fepopupmisc.cpp`) | 12, 1, 2, 3 | career messages | no |
| `0x002D66A0` (`tAvalancheNode_calculate`), `0x002EBE20` (`src/visualfx/boardtrailfx.cpp`) | 5, 2 | not described | no |
| `0x0035F0B8`, `0x0035F410` (`src/object/railmodifier.cpp`) | 1 each | `0x0035F410` is the TexFlip effect, not used on the courses studied | no |
| `0x00343C60` (`src/object/debouncenode.cpp`) | 1 | reachable from global scripts through `0x00303B38` | none seen |

No render function draws from this stream. The group render pass `0x00355028`, the ScreenTint render `0x00390F20`,
the splash render `0x002F3E28` and the environment render `0x002F0CD0` make no calls.

### Camera splash (snow drops and ice crystals on the lens), update `0x002F39E0`

**Class.** The vtable is at `0x00488230`:

| Slot | Function |
|---|---|
| `+0x0C` | `0x002F3618` |
| `+0x14` | update `0x002F39E0` |
| `+0x24` | render `0x002F3E28` |

`0x002F39C8` is its reset. There is one object per possible camera, and all of them sit in entity group 2.

**Group 2 on Snow Jam (PS2).** The objects run in this order: the snowfall object (update `0x002E5DA0`), the flag
manager (`0x0034C668`), the splash for camera 1, then the splash for camera 0.

**Tweakables.** The menu constructor is `0x0024BF60` (`cSplashTogglesMenu_cSplashTogglesMenu`, "Camera Splash Menu").
These are the values in the race:

| Global | Name | Value |
|---|---|---|
| `0x004A424C` (gp+0x115C) | Enable | 1 |
| `0x004A4250` (gp+0x1160) | Render | 1 |
| `0x004A4254` / `0x004A4258` | Max Drops / Max Crystals | 30 / 24 |
| `0x004A425C` | Percentage Ice Crystals | 0.6 |
| `0x004A4260` | Percentage Ice Crystal Spawn | 0.01 |
| `0x004A4264` / `0x004A4268` | Ice Crystal Min / Max in Group | 1 / 3 |
| `0x004A426C` | Max Spawn Per Crystal | 2 |
| `0x004A4270` | Farthest Impact Distance | 450 |
| `0x004A4274` | Lowest Impact Intensity | 105 |
| `0x004A4278` | Lowest Snowfall For Impacts | 1.0 |
| `0x004A427C` | Impact Multiplier | 1.1 |
| `0x004A4280` | Lowest Snowfall Amount | 1.5 |
| `0x004A4284` | Snowfall Multiplier | 0.015 |
| `0x004A4294` (gp+0x11A4) | (unnamed; the size threshold in step 6) | 4 |

**Update, in order (s1 = the object):**

1. **Gate.** It returns if Enable is 0, or if the camera index `+0x10` is not below the camera count (read through
   G+0x84; G is probably the game object, unconfirmed). In single player the camera-1 object returns here and makes no draw.
2. **Speed.** p is the camera's `+0x20`.
   - If `+0x100C` is set, speed `+0x1020` = |p − prev `+0x1010`| · 59.999996 (`0x0049F7EC`) · 0.036 (`0x0049F7F0`),
     which is km/h. Otherwise speed = 0 and `+0x100C` is set to 1.
   - A speed above 1000 calls vtable `+0x70` (reset) and sets the speed to 0.
   - Then prev = p.
3. **Spawn (`0x002F3810`).**
   - n = trunc(pending `+0x1024`), and pending −= n.
   - Each unit makes three draws u1, u2, u3 in [0, 1) of the visual LCG `0x004A3AFC`: x = 640·u1, y = 480·u2 and
     t = u3.
   - If t < 0.6, one `BXrand` draw (return address `0x002F3920`) gives the group size k = 1 + r % (3 − 1), and
     `0x002F3640` spawns a crystal group. Otherwise `0x002F37A8` spawns a drop.
4. **Drops.** `0x002F2810` updates the drops (count `+0x14`, 0x3C bytes each at `+0x1C`). A dead drop is replaced by
   the last one.
5. **Crystal pick.**
   - One unconditional draw (return address `0x002F3BE8`) gives u, then f = u · crystals `+0x18` / 24.
   - If f < 0.01 and there is at least one crystal, a second draw (return address `0x002F3C4C`) gives
     chosen = r % crystals. Otherwise chosen = −1.
6. **Crystals** (0x4C bytes each at `+0x724`).
   - `0x002F3030` updates each crystal.
   - If the crystal is alive, its index is `chosen` and its spawn count is below 2, the count goes up by one. It also
     spawns a drop (`0x002F37A8`) if both of its sizes · 0.6 are above 4.
   - A dead crystal is replaced by the last one.

**Pending sources.**

- **Snowfall.** `0x002F4330` is called once per camera from the snowfall object (`0x002E5920` / `0x002E5DA0`). It
  sets `+0x1028` = snowfall. If snowfall > 1.5, pending += snowfall · (speed + 10) · 0.015 · 0.0076923
  (`0x0049F7FC`).
- **Impacts.** `0x002F4260` is called from `0x002F4118`. It adds only when snowfall > 1.0 and the distance d < 450:
  pending += (1 − d/450) · clamp((I·0.036 − 105)/(120 − 105), 0, 1) · 1.1.

**Result (PS2).**

- Every sampled savestate on three courses has snowfall at or below 0.1, so nothing spawns. The splash makes
  **exactly one draw per game tick**, the unconditional one.
- A 12440-tick trace has no draws at `0x002F3920` or `0x002F3C4C`. Spawn and pick draws should appear only in heavy
  (blizzard) snowfall (unconfirmed).
- The splash also runs in the load and overlay updates.

### ScreenTint lightning, update `0x00390C60`

**Owner.** The environment object is built by `0x002F0548` (`cPSPVisualEffectsMan_cPSPVisualEffectsMan`), vtable
`0x00487D28`. It holds 17 components. Each is a 4-byte object that holds only a vtable, so their state is global.
In order:

0 RenderToggles, 1 VisualEffectsTest, 2 LightGlow, 3 Plants, 4 DepthFog, 5 HeightFog, 6 DetailSystem,
**7 ScreenTint**, 8 Shadow, 9 SnowSurface, 10 BoardTrail, 11 Flags, 12 PowerUpFXToggles, 13 SnowfallToggles,
14 SplashToggles, 15 Tube, 16 PathArrow.

ScreenTint's vtable is `0x00492FA0`: update `+0x14` = `0x00390C60`, render `+0x1C` = `0x00390F20`.

**Environment update `0x002F0A98` (vtable `+0x14`).**

- It calls slot `+0x14` of components 0..16 in order, then `0x002F00A0` (region environment refresh) for each camera.
- It runs from entity group 3. The group-3 entity's update `0x00244478` calls slot 0x14 of the vtable at `+0x44` of
  `*(obj+0x10)`.

**Tweakables** (menu constructor `0x0024A228`, `cScreenTintMenu_cScreenTintMenu`). All are globals:

| Global | Meaning |
|---|---|
| `0x004A45F0`..`0x004A4608` (gp+0x1500..0x1518) | fill / XN tint colours, XN lerp |
| `0x004A460C` (gp+0x151C) | Enable Lightning |
| `0x004A4610` (gp+0x1520) | Frame Id (−1 normally) |
| `0x004A4614` (gp+0x1524) | Lightning Chance |
| `0x004A4618`..`0x004A4624` | phase lengths 2, 2, 2, 7 ticks |
| `0x004A4628` / `0x004A462C` / `0x004A4630` | phase intensities 0.4 / 1.0 / 0.5 |
| `0x004A4634`, `0x004A4640`, `0x004A464C` | flash colours 1..3 (1.584, 1.905, 1.998), (0.333, 0.43, 1.99), (0.75, 0.75, 2.0) |
| `0x004A4698` (gp+0x15A8) | phase counter (−1 = idle) |
| `0x004A469C` (gp+0x15AC) | intensity |
| `0x004A46A0`..`0x004A46A8` | current colour |
| `0x004A46AC` (gp+0x15BC) | mode (5 in every phase) |
| `0x004A46B0` (gp+0x15C0) | strike distance |
| `0x004A46B4` (gp+0x15C4) | thunder delay (ticks) |

**The refresh `0x002F00A0`** recomputes two values every update, after the component updates, so the lightning reads
the value set in the previous update:

- Chance = the region getter `0x002EE738` (vtable `+0x1AC` of the region payload). **(PS2)** It is 0 in every sampled
  state on Snow Jam, Metro City, Happiness, Crow's Nest, R&B and The Junction.
- Enable = (S == 0) || (S == 1). S = `*(*(G+0x84)+0x28)` is the game-flow word, and `0x002F7BE0` tests S == 0.
  **(PS2)** S is 0 during the countdown and the race, 10 or 11 on the ready screen, and 13 after the finish.

**`0x00390C60` each update:**

```
if !Enable: return                          (no draw, no countdown)
if thunderDelay > 0: thunderDelay--
if counter < 0:                             (idle)
    u = unit(draw)                          (return address 0x00390CA0)
    if u < chance*chance:
        dist = (unit(draw)*1.98 + 0.02) * 100000     (return address 0x00390CE0; constants 0x004A0A4C..0x004A0A54)
        strike(dist)                        (0x00390EC8)
    return
counter++  (or counter = Frame Id when 0 <= Frame Id <= the sum of the phase lengths); no draw
```

`0x00390EC8(dist)` sets the counter to 0, the intensity to 0 and the distance to dist, and the thunder delay to
(int)(dist · 0.0018072289) ticks. That is 553.3 cm per tick, or 332 m/s at 60 Hz. While the flash runs:

| Counter c | Intensity | Colour |
|---|---|---|
| c ≤ 2 | c/2 · 0.4 | colour 1 |
| c ≤ 4 | 0.4 | colour 1 |
| c ≤ 6 | 1.0 | colour 2 |
| c ≤ 13 | (1 − (c − 6)/7) · 0.5 | colour 3 |
| c > 13 | 0, and the counter goes back to −1 | base colour `0x004A45E4`..`0x004A45EC` |

**Other entry points.**

- A script builtin can also call `0x00390EC8`, for a scripted strike with no draw. The call is at `0x00305778`,
  inside `0x00305660`. The older notes tie it to `0x00303E60` and the script interpreter `0x002FC2C0`.
- The audio function `0x00285BF8` polls `0x00390EF8`. It returns 1 once, when the delay reaches 0, and that plays
  the thunder (bank 8, sound 16).
- The render `0x00390F20` draws the tint while the intensity is not 0. It makes no draws.

**Result (PS2).** With chance 0, the lightning costs exactly one draw per game update while S is 0 or 1. The draws
stop about two updates after the finish update (the exact offset is unconfirmed).

### 2D crowd flashes: `0x002294C8` → `0x00229530`

- **Each update.** For each registered slot (0..127, stride 0x40, slot word ≠ −1), the countdown at `+0x240` goes
  down by 10·|cheer| + 4. The cheer comes from the audio function `0x002A77C8`, called with the global at
  `0x004A3500` (gp+0x410).
- **Expiry.** When the countdown reaches 0 or below:
  - draws c1 (return address `0x0022961C`) and c2 (`0x00229638`), each in [−1, 1);
  - a camera flash spawns at centre + axis1·c1 + axis2·c2;
  - a third draw (return address `0x002296D0`) re-arms the timer with `300 + r % 300`.

  That is three draws per expiry.
- **Load.** `0x002292E0` arms all 128 timers, one draw each (return address `0x00229340`).

### Flags

- **Wind.** The flag manager's update `0x0034C668` (group 2) moves a wind value toward a random target (±0.15 on Snow
  Jam). It picks a new target, with one draw (return address `0x0034C71C`), each time its one-second timer wraps.
  **(PS2)** 207 draws in 12440 ticks.
- **Grid build.** New flags are built during the section pass:
  - The flag entity is built by script builtin 12 (`0x002FC9C8` → `0x0034AC88`, constructor `0x0034ADD8`).
  - It registers with the 15-slot flag manager `0x0034C548` → `0x0034B038`.
  - When that allocates a new cloth slot, `0x0034B228` (`cFlagSet_CreateMesh`) draws 4 random start phases (return
    address `0x0034B288`).

### Particle emitters and emitter seeds

- **Emitter update.** `0x003710D0` makes one draw per active emitter per update (return address `0x003711D0`). It is
  reached from:
  - DynamicParticle effects in the world-entity pass: the effect list `0x00352D20` → `0x00345F90`. The plain Particle
    effect `0x00345B40` makes no draw.
  - The board-sparks grind-chunk emitter, in the rider FX pass `0x002E8938` (rider FX `+0x520`).
  - The snow FX pass `0x002DF920` (rider FX `+0xB40`), one draw per enabled emitter.
- **Emitter seeds.** `0x0036CCB8` makes 9 draws per static emitter (return addresses `0x0036CCE4`..`0x0036CDCC`). It
  is reached from script builtin 16 (`0x002FD420` → `0x003705E0`) and builtin 26 (`0x00370DC8`, 9 + 1 draws, the
  extra one at return address `0x00370E1C`). These values probably seed the emitter's VU random generator
  (unconfirmed).
- **MultiParticle.** The static MultiParticle emitters (`0x00357BF8`) make no draws. They use the VU generator.

### MeshAnim

Script builtin 13, `0x00352230`, makes 9 draws per node:

- a first loop over the N nodes with 4 draws each (return addresses `0x003522B8`, `0x003522E0`, `0x00352300`,
  `0x0035231C`);
- then a second loop with 5 draws each (`0x003523C0`..`0x00352444`).

### Camera shake

- For each camera, `0x0022E840` (`cGameViewMan_updateAll`) calls slot `+0x1C` of the vtable at `cam+0x90`, which is
  `0x0015DF98` → `0x0015E668` → `0x0015E460`.
  - `0x001656B0` makes 12 draws when a shake starts (return addresses `0x00165708`..`0x001658C0`).
  - `0x00165938` makes 6 draws on each tick of the shake (return addresses `0x00165A54`..`0x00165BAC`).
- Shakes are requested through `0x0015E360`. For example, the crash-recovery code `0x0012D160` requests one at
  `0x0012D218`:
  - shake index 4, fade 0;
  - scale = clamp(speed_cm_per_s · 0.036 / 100, 0, 1);
  - only when rider `+0x870` ≥ 0 and rider `+0x87C` ≠ 0.

### Audio

- `0x002ADF60` returns one draw. The song chooser `0x0028D488` uses 15 bits of it, so the mask is applied by the
  caller:
  - start index = rand15 · count / 0x7FFF;
  - then (rand15 · 10 / 0x7FFF) + 1 steps of next-song.
- `0x002A4CA0` picks a random entry from a counted list.
- In the race both are called from the rider-manager passes. They are rare (33 draws in 12440 ticks, PS2), but each
  one shifts every later draw.

### Caller histogram (PS2)

Draws per caller, counted by a hook on a character-select savestate. The counts are cumulative from character select.
The hook totals equal the change in w5.

| Caller (return address, function) | Load, 1200 frames | Countdown tick 19 | Race tick 919 |
|---|---|---|---|
| `0x00229340` (`0x002292E0`), timers armed at the load | 128 | 128 | 128 |
| `0x0022EFF0` (`cGame_load`), roster seed | 1 | 1 | 1 |
| crowd expiries (`0x00229530`), 3 draws each | 25×3 | 36×3 | 209×3 |
| `0x002F3BE8` (splash) | 312 | 439 | 1339 |
| `0x003711D0` (emitters, all six riders and set pieces) | 213 | 271 | 2746 |
| `0x00390CA0` (lightning) | 1 | 18 | 918 |
| emitter seeds (`0x0036CCB8`, `0x00370DC8`) | 240 | 240 | 294 |
| camera shake (`0x001656B0`, `0x00165938`) | 0 | 0 | 128 |
| flags (`0x0034B228`, `0x0034C668`) | 21 | 23 | 38 |
| audio `0x002ADF70` | 3 | 3 | 11 |
| load-time set-up (`0x002E4D88`, `0x0027B214`, `0x001EA800`) | 21 | 21 | 21 |

## Gameplay-stream consumers

### Callers of `AIrand`

| Function | Sites | What it is |
|---|---|---|
| `0x00105D98` | 6 | crash handling (it also restarts the air predictor); what the draws are for is not described |
| `0x00107E70` | 3 | rider-pair contact: velocity set |
| `0x00108388` | 3 | soft contact reaction |
| `0x0010B250`, `0x0010B590`, `0x0010B790`, `0x0010BFA8`, `0x0010C1D0`, `0x0010C258`, `0x0010C320`, `0x0010C3B8` (`asm/1218.s`) | 1 or 2 each | not described |
| `0x0010CBE0`, `0x0010D410`, `0x0010DA10` (`src/ai/computer.cpp`) | 1 each | not described |
| `0x00115D48` | 2 | controller pass |
| `0x00131620` | 1 | controller pass |
| `0x0012B420` | 1 | not described |
| `0x00139C88` (`src/ai/control/handplantcontrol.cpp`) | 2 | not described |
| `0x00258448` (`cGameComm_syncGame`) | 1 | roster seed on the sync path |
| `0x00311710` | 1 | not described |

### Callers of `AIrandf__Fff`

| Function | Sites | What it is |
|---|---|---|
| `0x00137138` | 3 | not described |
| `0x00303598` | 1 | not described (in the script-builtin segment `asm/1FBE38.s`) |
| `0x00341AA0` | 1, plus 1 through `0x00317890` | LiveComp constructor (script builtin 3, `0x002FBCB8`). Key 6 is a random rate spread and key 8 a random start, taken from the gameplay stream. Which call serves which key is unconfirmed. |
| `0x00359460` | 1 | SplineModifier constructor (script builtin 19, `0x002FDED0` → `0x00355AD0`). It always makes one draw, even when the jitter is zero. |

### Other consumers in the notes

- Script builtin 77 returns a random value in a range and uses one gameplay draw per call. The Metro City beam
  teleports use it as builtin77(0, 100) < 90 (90 %) and < 75 (75 %). Its address is not given.
- A career collectible whose section builds it (LiveComp + magnet + halo) costs one gameplay draw. This is probably
  the LiveComp constructor's draw (unconfirmed).

### Shared order

- All riders draw from the one state in the order the tick runs them. So the values a contact reaction gets depend
  on everything drawn before it in that tick, by every rider, and a contact shifts every later draw in that tick.
- Within the rider manager `0x00128AF0`, every pass runs over all riders in slot order (human in slot 0, then the
  computer riders):
  1. `0x0010F560` (manager refresh, every sixth tick);
  2. `0x00120F20`;
  3. `0x00121068`, the providers and controllers. The controller draws continue one sequence in slot order.
  4. `0x001210B0`, `0x001211F8`, `0x001216E0` (motion);
  5. `0x00121700` / `0x00121728` (pose);
  6. `0x00121750`, the second motion phase. It includes the rider-pair dispatch `0x00107888`. Its velocity set
     `0x00107E70` and soft reaction `0x00108388` call `AIrand` directly (the crash reaction is `0x0010EB30`).
  7. `0x001217F8` / `0x00121818` (course progress, route and triggers). Contact-triggered script programs run here,
     including builtin 19 spline launches and builtin 77.
  8. After all riders, the section pass `0x00101B60` runs the section-load programs (LiveComp and spline
     constructors).
- As a result:
  - every rider's controller draws come before any rider's later draws in that tick;
  - the rare draws in the later pre-pose passes come after all controller draws;
  - the draws in `0x00121750` and `0x00121818` follow in slot order.

  The exact position of the script-constructor draws is inferred from where those programs run (unconfirmed).

## Per-tick order in the race game update `0x002306B8`

The race game is vtable `0x0047D130`, and slot `+0x14` (`0x0047D144`) is its update, `0x002306B8`. The presentation
draws happen in this order (PS2: a draw trace of a whole Snow Jam race with five computer riders, 172188 draws with
none missing, checked against 45 savestates):

1. **Group 1, at `0x00230C64`.** This is `0x00354F98(mgr, 1)`, with the bucket manager held at `0x004A5988`
   (gp+0x2898). It runs all
   world entities, newest first (`0x00356198`, type-13 `0x00357950`, `0x003608E8`, ...).
   - Script programs run inside it: a LiveComp's slot-5 handler through `0x00341D48`, and builtin 16 `0x002FD420` →
     `0x003705E0` → `0x0036CCB8`, which makes 9 seeds per static emitter.
   - Each entity's effect list runs: DynamicParticle → `0x003710D0`, one draw per active emitter.
   - Steps 1 to 3 are skipped when bit 2 of the debug word `0x004A2A50` (gp−0x6A0) is set.
2. **Groups 5 and 6** (`0x00230C70`, `0x00230C7C`, through `0x00244948`). No draws.
3. **`0x00355028(mgr, 1)`** at `0x00230C98`, the group-1 slot `+0x1C`. No draws.
4. **The rider manager `0x00128AF0`** at `0x00230CB0`. Every pass runs over all riders in slot order, which the trace
   confirms for every tick. In order:
   - `0x0012BB20`, `0x00113C20` (race clock), `0x0010F560`, then the controller and physics passes
     (`0x00120E30`..`0x001217F8`). The audio draws happen here.
   - At `0x00128EA4`, `0x00121818` runs for each rider. The selected contact runs slot-2 stage programs through
     `0x0030A060`: MeshAnim (9 per node), builtin 26 (9 + 1 seeds), builtin 16 (9 seeds).
   - `0x001218D0`, `0x00121950`.
   - The FX passes, each over all riders:
     - `0x002DD0B8` (`+0x3B0`), `0x002DABC8` (`+0x470`);
     - **`0x002E8938` (`+0x520`): the grind-chunk emitter, one draw;**
     - `0x002E66B8`, `0x002EADD0`, `0x002EF6D0`, `0x002D4C08`, `0x002E39D8`;
     - **`0x002DF920` (`+0xB40`): snow FX, one draw per enabled emitter**, the human's emitters first and then each
       computer rider's;
     - `0x002F1150` (fist sparkle), `0x002F6518`, `0x00120E88`.
   - The section pass `0x00101B60` (called at `0x00129124`) → `0x0030A3A0` → `0x0030A298` runs slot-1 programs in
     section order: flag construction (4 draws per new flag slot), then emitter seeds `0x0036CCB8` / `0x00370DC8`.
   - `0x001013A8`, then the total-tick counter goes up.
5. **Group 2, at `0x00230CCC`** (skipped when bit 0x10 of `0x004A2A50` is set):
   - snowfall, no draw;
   - flag wind, one draw when its timer wraps;
   - the camera splash objects, one draw from the camera-0 object.
6. **Group 3, at `0x00230CE8`** (skipped when bit 4 is set):
   - the environment → ScreenTint lightning, one draw (plus one on a strike);
   - then the region refresh for each camera;
   - the other group-3 entities make no draws.
7. **WScriptMan `0x00309270`** at `0x00230CF0`, for the global scripts. They can reach a scripted strike (no draw),
   builtins that seed emitters, and `0x00343C60` through `0x00303B38`. None drew in the traced race.
8. **CrowdMan2d** at `0x00230CF8`: `0x002294C8` → `0x00229530`, three draws per expiry.
9. **CrowdMan3d `0x003440C8`, MultiParticleMan `0x00357BF8` and the flush `0x00354C98`** (`0x00230D00`..`0x00230D14`).
   No draws.
10. **Group 4** at `0x00230D50` (`0x002449F8` → `0x002D21B0`). No draws.
11. **Cameras** at `0x00230D7C`: `cGameViewMan_updateAll`, which does the shake draws. It is skipped when S == 3.
12. **From `0x00230DC0` on:** audio emitters `0x002B7848`, each rider's `+0x98`, `0x00237948`, `0x003F42A0`, and the
    HUD (`0x001A39F0`, `0x001E1458`, `0x001F3188`). None of them draws during a race.

**The `0x00230D24` branch.** It is taken when `0x00270280(state)` is true and either `0x002379C8` returns 0 or
`0x0026CE50` is non-zero.

- It runs group 5, group 3 (so the lightning still draws), group 4 and the cameras.
- It skips groups 1, 2 and 6, the riders, WScript and the crowd.
- The older notes guess it is the frozen or pause path (not verified). The functions it tests live in
  `src/replay/replaycache.cpp` and `src/replay/playbackman.cpp`, so it may belong to replay playback (unconfirmed).

**Tick labels.** The rider-manager object `*(G+0x84)+0x0C` doubles as the race clock: `+0` phase, `+8` total ticks,
`+0xC` race ticks.

- `+8` goes up at the end of the rider-manager work (`0x00129134`..`0x00129144`). With the current boundaries, that
  code and the section-pass call at `0x00129124` fall inside `0x00129100`.
- So a trace labelled with this counter shows steps 1-4 of an update under tick T and steps 5-11 under T + 1.
- **(PS2)** A savestate taken between updates sits after the cameras of one update and before group 1 of the next. In
  all 41 states checked, the last draw before the state is the lightning or the crowd, and the first draw after it
  is an emitter.

**All in-race draws are in the game update.** The generator advances per game tick, never per displayed frame.

### Measured rates (PS2)

Snow Jam, five computer riders, 12002 ticks:

| Consumer | Draws | Per tick |
|---|---|---|
| Emitters (`0x003710D0`), all | 45033 | 3.75 |
| – human (snow and grind) | | 1.66 |
| – computer riders | | 1.96 |
| – DynamicParticle | | 0.13 |
| Camera splash | 12002 | 1.00 |
| Lightning | 11881 | 1.00, until the finish |
| Crowd | 4512 | 0.38 |
| Emitter seeds | 918 | 0.08 |
| MeshAnim | 405 | 0.03 |
| Camera shake | 356 + 36 | |
| Flag wind | 200 | 1 per 60 ticks |
| Flag grid | 24 | |
| Audio | 33 | |
| **All** | | about 6.3 (4.7 to 9.5 per 400-tick window) |

- In every interval between two savestates, the splash draws equal the number of ticks exactly. So do the lightning
  draws, until the finish.
- Example: a 400-tick window has 1878 draws: emitters 954, splash 400, lightning 400, crowd 117, flag wind 7.
- Windows with set pieces add seeds (9 per emitter), MeshAnim (9 per node) and flag grids (4 per slot).

## Other generators

- **Visual LCG, `0x004A3AFC` (gp+0xA0C).** One word, stepped inline:

  ```
  w = ((w · 18FCDh + E9507Ch) & 7FFFFFh) | 3F800000h
  ```

  The float with bits w, minus 1, is the value. The board trail, the board sparks (chunk and glint draws), the fist
  sparkle, snow emission and the camera-splash spawn positions use it. The trail steps it before the spray within a
  tick. The board sparks use this LCG and the presentation stream (chunk births), never the gameplay stream.
- **VU random (`RINIT`/`RNEXT`).** The particle sprite microcode and the static MultiParticle emitters use it. It is
  a different generator from the six-word one.

## Corrections to earlier working names

- **`0x002306A8` is a getter, not the game update.** It is four instructions that return `*(a0 + 0x68 + 4·a1)`, the
  camera-splash object of camera a1. The race game update is `0x002306B8`.
- **`0x00111890` is not the main loop.** It builds one rider's FX components. It calls the set-up functions
  `0x002DCF28`..`0x002F64E8` and `0x002C03E8` (`cWorldPainterMan_reset__FPv`), then `0x002306A8` to get that camera's
  splash object.
- **`0x00244880` is not one function.** An older function list merged several functions there. The alternate update
  body starts at `0x00244E60`, and its pass order matches `0x002306B8`. The decomp's current boundaries put its group
  passes (`0x00244F94`..`0x00245074`) and camera call (`0x002450A0`) inside `0x00244A18`, so that boundary is
  unresolved.
- **Stream names.** "Visual RNG", "particle RNG" and "presentation generator" are all `0x004FF018` / `BXrand`.
  "Gameplay RNG", "shared game RNG" and "world RNG" are all `0x004FF030` / `AIrand`. Despite the `AI` prefix, the
  gameplay stream serves the human rider too, as well as contact reactions, set-piece constructors and script
  builtins.
- **The sprite "LFSR" is the VU generator**, not the six-word one.
- **"Crystal draw `0x002F3BE0`"** in older notes is the `BXrand` call site (return address `0x002F3BE8`) inside the
  splash update, not a separate function. The decomp's current boundaries place it inside `0x002F39C8`.
- **The call at `0x0012D218` is a camera-shake request** (`0x0015E360`, index 4), not a controller rumble.
- **"rand15" `0x002ADF60`** returns the raw 32-bit draw. The 15-bit mask is applied by its callers.
- **Caller functions:**
  - The notes list `0x00159CD0` (awards) as a `BXrand` caller. The direct calls in `src/be/beintreward.cpp` are in
    `0x00156C70`, `0x00156EE0` and `0x00157080` (`0x00159CD0` may reach them indirectly; unconfirmed).
  - The notes list `0x002797A0` as a script-engine caller. The direct calls (`0x00279BD0`, `0x00279C54`) are inside
    `0x00279A70`.
