<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/path/

## `src/path/pathsys.cpp`

Segment `0x0026B310`-`0x0026C458`.

- **`0x0026B5E0`** - Region/bank row lookup (bank, kind, index): returns the row whose +4 equals kind and +0 equals index, else the bank's first row. Runtime kinds are the exported (disc) kinds + 1: kind 1 = grid slots, kind 2 = session points. *[PS2]*
