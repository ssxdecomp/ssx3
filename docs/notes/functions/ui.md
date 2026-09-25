<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/ui/

## `src/ui/uiengine.cpp`

Segment `0x00397AD8`-`0x0039A3F8`.

- **`0x00399820`** - Contains the UI list box setup block below. *[static]*
  - `0x00399904`: List box setup block that sets the wrap bit (+0x14 bit 7). *[static]*
- **`0x00399970`** - UIListBox input (vtable `0x00494798`): index -1/+1 with wrap, notify 9, query +0xB0 (0/3 dec, 1/2 inc; 4 Triangle) -> sound kind 1 / kind[0]. *[static]*

## `src/ui/uilistbox.cpp`

Segment `0x0039A3F8`-`0x0039AD38`.

- **`0x0039A8D8`** - UIMenu init (uses button set 0). *[static]*
- **`0x0039AB00`** - UIMenu button set selection: set 0 (+0x91..+0x94 = UIUp, UIDown, UILeft, UIRight), set 1 = right stick. *[static]*
- **`0x0039AB50`** - UIMenu next item: skips items with flag bit 5 (or rejected by the virtual-list query); wraps only with +0x14 bit 7. *[static]*
- **`0x0039AC48`** - UIMenu previous item (same skip/wrap rules as `0x0039AB50`). *[static]*

## `src/ui/uimenu.cpp`

Segment `0x0039AD38`-`0x0039C518`.

- **`0x0039AE98`** - Scrolls the visible menu window (plays no sound). *[static]*
- **`0x0039B000`** - UIMenu HandleInput (vtable `0x00494928` slot +0x78): focused item first, then Up/Down cursor with skip/wrap and button notify/query sounds. Cursor moved -> UI sound kind 1; not moved -> the focused item's kind[0]; +0x90 bit 3 -> kind 0. *[static]*
  - `0x0039B17C`: Cursor moved: plays UI sound kind 1 (move). *[static]*
  - `0x0039B274`: Cursor moved: plays UI sound kind 1 (move). *[static]*
  - `0x0039B5E4`: Cursor did not move: plays the focused item's kind[0] (default 4 error; 0 on the title 'Press START'). *[static]*
- **`0x0039B760`** - UIMenu virtual-list selectability query. *[static]*
- **`0x0039BED8`** - UIPair input (vtable `0x00494868`): label plus embedded control (+0x7C); Cross/Triangle query +0xA8(pair, 0/1), other input is passed to the child. *[static]*

## `src/ui/uiscreen.cpp`

Segment `0x0039C518`-`0x0039E8B8`.

- **`0x0039DFE8`** - cUISlider input (vtable `0x00494348`): Left/Right changes the value by 1 -> notify 9 -> UI sound kind 1 (snd 2); silent at the ends (no query). *[static]*
- **`0x0039E130`** - Slider knob position: track.x + value x (trackW - knobW) / 11. *[static]*

## `src/ui/uistatestack.cpp`

Segment `0x0039F238`-`0x0039FF78`.

- **`0x0039F400`** - UI transition triggered by notify 5 on the title screen. *[static]*
- **`0x0039FB30`** - LUI widget base constructor: item sound kind table kind[0] = 4 (error), kind[1] = 6 (accept); flags +0x14 bits 1,3,6 set, 0,2,4,5,7 cleared. *[static]*
- **`0x0039FF50`** - Returns the UI context (listener chain screen+0x5C -> +0xD0 -> +0x10 -> +0x14). *[static]*

## `src/ui/uithing.cpp`

Segment `0x0039FF78`-`0x003A05E8`.

- **`0x003A0330`** - Sets a widget item's sound kind table entry (the only game-code writer of the kind table). *[static]*

## `src/ui/uivector.cpp`

Segment `0x003A34C0`-`0x003A6688`.

- **`0x003A3F48`** - Contains the null UI sound listener static initialisation below. *[static]*
  - `0x003A426C`: Static initialiser that builds the null UI sound listener (not a listener call). *[static]*
- **`0x003A4AA8`** - Widget wrap setter (flag bit 7); never called by game code. *[static]*
- **`0x003A4AD8`** - Widget orientation setter (flag bit 0); never called by game code. *[static]*
- **`0x003A5390`** - UIMenu silent-flag setter (+0x90 bit 3); unreferenced. *[static]*
