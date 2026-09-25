<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/ (top level)

## `src/hashvalue.cpp`

Segment `0x00317618`-`0x003177C8`.

- **`0x00317618`** `tHashName32_getHashValue__FPUiPc` - Computes a 32-bit hash of a NUL-terminated name string; the hash uses sign-extended (signed) byte values and stops at the first terminator. *[static]*
- **`0x00317670`** `GetHashValue32__FPc` - String hash function; the Enter Cheat screen hashes the lowercased cheat code with it. *[static]*
