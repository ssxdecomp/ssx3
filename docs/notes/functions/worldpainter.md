<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/worldpainter/

## `src/worldpainter/worldpainterman.cpp`

Segment `0x002C03E8`-`0x002C0408`.

- **`0x002C03E8`** `cWorldPainterMan_reset__FPv` - Reset call without arguments made at the end of `0x00111890`'s rider FX component list, after the `0x002DCF28`..`0x002F64E8` component constructors/resets. *[static]*

## `src/worldpainter/worldpainterqueryctor.cpp`

Segment `0x002C0408`-`0x002C0A58`.

- **`0x002C0408`** `cWorldPainterQuery_cWorldPainterQuery` - World painter factory: switch on painter type. Case 6 glare (ctor `0x002BC830`), case 7 ScreenTint (`0x002BC890`), case 9 Sun (`0x002BC910`). *[static]*
  - Possible mismatch with the current name: Named as the cWorldPainterQuery constructor, but the records describe a factory that switches on painter type and calls per-type painter constructors.
- **`0x002C0778`** - Stateful painter transition driver (environment property wrapper, vtable `0x00483E00` slot `+0x10`; one record says slot 10): selects the region payload via `0x002C0A10` and blends the painter toward it. Stores last X/Y at wrapper `+0x8`/`+0xC`, adds planar travel to painter `+0x0`. Sentinels -99999.0 at `0x0049EE6C` (init) and `0x0049EE70` (auto weight); compare slot `0x220`, blend slot `0x210`, missing region/payload -> reset slot `0x228`. Auto weight: rate<0 -> -rate; rate>=0 below the travel threshold -> weight 1, distance cleared; else -rate; initial apply -1. A PS2 record ties it to the rider Lighting painter (type 11), storing the area's bright bank (BPBRR/B/G/Y/2) in rider `+0x460`. *[PS2]*
- **`0x002C0A10`** - Painter payload (environment region) selection for the current section, used by the driver `0x002C0778`; calls `0x002BAF90` and shares its leaf/payload-table semantics. *[static]*

## `src/worldpainter/worldpaintermanquery.cpp`

Segment `0x002C0A58`-`0x002C17D0`.

- **`0x002C14F0`** - First of the glare painter value getters (range `0x002C14F0`..`0x002C1520`, vtable slots 13..19). *[static]*
- **`0x002C1560`** - First of the Sun painter value getters (range `0x002C1560`..`0x002C15A0`). *[static]*
- **`0x002C15D0`** - Lighting painter getter returning the gain scalar at painter `+0x48` (vtable slot `0x148`/`0x14C`); reached from `0x002EEFF0`. *[static]*
- **`0x002C15D8`** - Lighting painter getter returning the rim scalar at painter `+0x50`; reached from `0x002EEFA8`. *[static]*
- **`0x002C1608`** - Environment getter returning object `+0x30`. *[static]*

## `src/worldpainter/quadtree.cpp`

Segment `0x002C17D0`-`0x002C6F78`.

- **`0x002C1CD8`** - Stateless painter section point-tree query (EE float): maps an X/Y point to a leaf. Subtracts origin X/Y, multiplies by the stored scale and truncates; accepts 0..32767, otherwise returns the outside leaf at tree `+0x18`. Nodes are 8 bytes; the low bit of the first halfword marks an internal node whose four halfwords hold child index<<1; successive high bits of the doubled 15-bit X/Y choose quadrants. *[static]*
