<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/input/

## `src/input/inputmap.cpp`

Segment `0x00320CA0`-`0x003217D0`.

- **`0x00320E18`** `cInputMap_compileMap` - Probably an action name registration helper, called by `0x00226B60` (role inferred). *[unconfirmed]*
- **`0x00321108`** - Input map bool getter (value != 0), companion of `0x00320C48`. *[static]*
- **`0x00321298`** - Consumed-sample pad button history update (24 pad channels -> history -> INPUT.MAP): debounce, edges, repeat. The value always updates; after an edge the next three samples suppress new edges while edgeAge advances 0..3 (held unchanged). Repeat fires immediately, then after 24 samples, then every 12. New records start with edgeAge 0; the pad is already settled (edgeAge 3) before any race. The front-end pad read for controller port 0 calls it from `0x00227E98`. *[PS2]*

## `src/input/inputparse.cpp`

Segment `0x003217D0`-`0x00327890`.

- **`0x00325250`** - Zeroes the input-map context default property, so bare-name operands read the value. *[static]*
- **`0x00326CF0`** - Stops the vibration motors (pause, quit, vibration option Off). *[static]*
- **`0x00326EB0`** - Pad read and conversion: calls scePadRead, then converts the pad packet into 24 float channels with an axial stick dead zone (raw stick bytes 79..176 read as centre). *[static]*
  - `0x00327208`: Point just after the scePadRead call. *[static]*
  - `0x00327210`: Pad packet conversion stage (to `0x003276BC`), 24 float channels: active-low button bits; pressure mode scales channels 4..15 by float `0x3B808081` (~1/255); stick byte b -> max(((79-b)*255)/79,0)*k or max(((b-176)*255)/79,0)*k, 79..176 = 0. *[static]*
