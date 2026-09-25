<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/util/

## `src/util/locale.cpp`

Segment `0x001959A8`-`0x00196540`.

- **`0x00195FF0`** - cFEStateAudioOptions: Music/Audio options screen (140audio in the front end, 142audio_pda in game); sends FE music event 4 and keeps the checkbox index at obj+0x78. In game (G+0x84 != 0) the pause menu creates it with flag 0 at `0x001F8B3C`, and it sends HUD command 3 on enter and 4 on exit. *[static]*
- **`0x001962A8`** - Greys out a disabled audio options row (listed with `0x00196378`). *[static]*
- **`0x00196378`** - Greys out a disabled audio options row (listed with `0x001962A8`). *[static]*

## `src/util/statemachine.cpp`

Segment `0x002C6F78`-`0x002C8348`.

- **`0x002C6F78`** `cConsoleConfig_setTimeString` - Formats a save time as '%02d:%02d:%02d' (24-hour) for the Load game screen. *[static]*
- **`0x002C7038`** - Formats a save date as '%02d:%02d:%04d' (month first) for the Load game screen. *[static]*

## `src/util/menu.cpp`

Segment `0x002CA258`-`0x002D1CE0`.

- **`0x002D18B0`** - Wake noise: periodic 160-cell interpolation over the 161-entry table `0x00445AB0`. *[static]*
- **`0x002D1928`** - Wake noise octave sum (3 octaves for rows; the last weighted sample is added after the loop). *[static]*
- **`0x002D19B8`** - Delegates entity contact handling to `0x0030A060`. It is not itself the slot-0x144 contact target, which is `0x00355770`. *[static]*
- **`0x002D19E8`** - Checks for and runs an authored slot-4 handler: `0x0030A598` -> `0x003A6B78` lookup, then `0x0030A5C0`. *[static]*
- **`0x002D1B30`** - Returns the rider identity used by entity contact `0x00355770`. *[static]*
- **`0x002D1BA0`** - Reads course table row +0x54 and returns the flag wind mode = value + 1. *[static]*
- **`0x002D1BD8`** - Resolves a packed rail id (object+0x30) to its rail descriptor for type-2 object rails. *[static]*
- **`0x002D1BE0`** - Returns the world/collision context passed as the first argument to the sphere-tree query `0x00336850` (inferred from the call `0x00336850`(`0x002D1BE0`(), ...)). *[unconfirmed]*
- **`0x002D1C20`** - Probably a camera-position getter: the sky box draw `0x00353B10` uses it to replace the matrix translation row and centre the sky dome on the camera (signature unknown). *[unconfirmed]*

## `src/util/objectinterface.cpp`

Segment `0x002D1CE0`-`0x002D2510`.

- **`0x002D21B0`** - Group-4 update target called from `0x002449F8`. *[static]*
