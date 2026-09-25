<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/world/

## `src/world/world.cpp`

Segment `0x003A6688`-`0x003A6D50`.

- **`0x003A6B78`** - Looks up an instance's authored handler slot program; returns -1 when absent. Slot 2 = contact handler (`0x0030A060`); slot 4 = completion override (via `0x0030A598`). *[static]*
- **`0x003A6CC8`** - Replaces the collision descriptor `+0x0C` mesh-resource field with a runtime cache pointer (confirms that descriptor `+0x0C` becomes a cache pointer at runtime). *[static]*
- **`0x003A6D18`** - Returns the stage program for a script context (called with ctx+0x28C). *[static]*

## `src/world/worldview.cpp`

Segment `0x003A9800`-`0x003AC800`.

- **`0x003A9858`** `cWorldView_isSectionLoaded__FP10cWorldViewi` - Streaming row completion: advances row state 6 -> 1 and 8 -> 2, and calls `0x00230338` to force a section rescan. *[static]*
  - Possible mismatch with the current name: Named as an is-section-loaded query, but the records describe it as streaming row completion that changes row states and forces a section rescan.
- **`0x003AB498`** - Location eviction step; calls `0x003284B8` to take the location's instances out of the activation octree. *[static]*
