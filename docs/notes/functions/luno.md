<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/luno/

## `src/luno/lunovm.cpp`

Segment `0x002227D0`-`0x00226830`.

- **`0x002227D0`** `luno_cLunoVM_execute` - LUN stage-script VM interpreter (frame, funcref*, ret*): loops while pc < code word count (signed compare); each word does pc++ then dispatches word & 0xFF through the 43-entry jump table `0x004797B0` (opcodes >= 0x2B do nothing). Allocates capacity*16+16 bytes of argument stack when the record's capacity > 0; on exit releases argument-stack entries top first, then every register (`0x00225B90`), and frees both blocks. s6 holds pc, s7 the return slot. *[static]*
  - `0x002228C4`: Dispatch block: masks the instruction's low byte and jumps through the 43-entry table `0x004797B0`. *[static]*
  - `0x002228F0`: Opcode 0x20 case (jump table `0x004797B0`): push register argument. *[static]*
  - `0x002229A0`: Opcode 0x17 case (jump table `0x004797B0`): load float bits from inline word. *[static]*
  - `0x00222A04`: Opcode 0x16 case (jump table `0x004797B0`): load int from inline word. *[static]*
  - `0x00222A60`: Opcode 0x01 case (jump table `0x004797B0`): jump if truthy. *[static]*
  - `0x00222AD0`: Opcode 0x02 case (jump table `0x004797B0`): jump if not truthy. *[static]*
  - `0x00222B44`: Opcode 0x00 case (jump table `0x004797B0`): unconditional jump. *[static]*
  - `0x00222B4C`: Opcode 0x22 case (jump table `0x004797B0`): logical not. *[static]*
  - `0x00222C98`: Opcode 0x23 case (jump table `0x004797B0`): negate. *[static]*
  - `0x00222DD4`: Opcode 0x03 case (jump table `0x004797B0`): equal. *[static]*
  - `0x00222EE4`: Opcode 0x04 case (jump table `0x004797B0`): not equal. *[static]*
  - `0x00222FF4`: Opcode 0x05 case (jump table `0x004797B0`): greater or equal. *[static]*
  - `0x00223118`: Opcode 0x06 case (jump table `0x004797B0`): greater than. *[static]*
  - `0x00223238`: Opcode 0x07 case (jump table `0x004797B0`): less or equal. *[static]*
  - `0x0022335C`: Opcode 0x08 case (jump table `0x004797B0`): less than. *[static]*
  - `0x0022347C`: Opcode 0x09 case (jump table `0x004797B0`): asymmetric logical or. *[static]*
  - `0x0022353C`: Opcode 0x0A case (jump table `0x004797B0`): logical and. *[static]*
  - `0x002235E0`: Opcode 0x0B case (jump table `0x004797B0`): move (falls into code shared with opcode 0x13). *[static]*
  - `0x00223644`: Opcode 0x0C case (jump table `0x004797B0`): add. *[static]*
  - `0x002237FC`: Opcode 0x0D case (jump table `0x004797B0`): subtract. *[static]*
  - `0x0022398C`: Opcode 0x0E case (jump table `0x004797B0`): multiply. *[static]*
  - `0x00223B1C`: Opcode 0x0F case (jump table `0x004797B0`): divide. *[static]*
  - `0x00223CD0`: Opcode 0x11 case (jump table `0x004797B0`): integer modulo. *[static]*
  - `0x00223E08`: Opcode 0x10 case (jump table `0x004797B0`): set nil. *[static]*
  - `0x00223EE0`: Opcode 0x1B case (jump table `0x004797B0`): call function value. *[static]*
  - `0x00223F58`: Opcode 0x21 case (jump table `0x004797B0`): builtin call; builtin index in bits 16..23, argument count in bits 24..31, destination in bits 8..15, dispatched via table `0x00441F38`. *[static]*
  - `0x00224030`: Opcode 0x12 case (jump table `0x004797B0`): table set. *[static]*
  - `0x00224070`: Opcode 0x1C case (jump table `0x004797B0`): table set, then increment reg[b2].word0. *[static]*
  - `0x002240C0`: Opcode 0x13 case (jump table `0x004797B0`): move (code also used by opcode 0x0B). *[static]*
  - `0x00224154`: Opcode 0x14 case (jump table `0x004797B0`): load symbol from inline word. *[static]*
  - `0x002241B0`: Opcode 0x15 case (jump table `0x004797B0`): load int from inline word. *[static]*
  - `0x00224214`: Opcode 0x1D case (jump table `0x004797B0`): load function value. *[static]*
  - `0x0022428C`: Opcode 0x24 case (jump table `0x004797B0`): for loop. *[static]*
  - `0x00224660`: Opcode 0x18 case (jump table `0x004797B0`): table get. *[static]*
  - `0x002246EC`: Opcode 0x19 case (jump table `0x004797B0`): new 32-bucket table. *[static]*
  - `0x00224764`: Opcode 0x1E case (jump table `0x004797B0`): set nil. *[static]*
  - `0x002247F8`: Opcode 0x1F case (jump table `0x004797B0`): return register value. *[static]*
  - `0x00224878`: Opcode 0x25 case (jump table `0x004797B0`): push inline int argument. *[static]*
  - `0x002248E0`: Opcode 0x26 case (jump table `0x004797B0`): push inline float argument. *[static]*
  - `0x00224958`: Opcode 0x27 case (jump table `0x004797B0`): push inline int argument (instance handle). *[static]*
  - `0x002249D0`: Opcode 0x28 case (jump table `0x004797B0`): push int(b2) argument. *[static]*
  - `0x00224A3C`: Opcode 0x29 case (jump table `0x004797B0`): push float(b2) argument. *[static]*
  - `0x00224AB0`: Opcode 0x2A case (jump table `0x004797B0`): return nil. *[static]*
  - `0x00224B2C`: Opcode 0x1A case (jump table `0x004797B0`): no-op. *[static]*
- **`0x00224D00`** - LUN VM table destroy; called by the table release `0x00224DF0` when the refcount reaches zero. *[static]*
- **`0x00224DA0`** - LUN VM table helper in the interpreter's table code; role not described. *[static]*
- **`0x00224DF0`** - LUN VM table release: decrements the refcount and, at zero, destroys the table (`0x00224D00`) and clears word0. *[static]*
- **`0x00224E50`** `luno_cLunoTable_constructTable` - LUN VM table helper in the interpreter's table code; role not described. *[static]*
- **`0x00224F30`** - LUN VM table helper in the interpreter's table code; role not described. *[static]*
- **`0x00225068`** - LUN VM table value copy: increments the table refcount. *[static]*
- **`0x00225248`** - LUN VM table get: returns nil without walking when the head's value is nil; otherwise uses the first key in the chain that compares equal. *[static]*
- **`0x00225338`** `luno_cLunoTable_set` - LUN VM table set: a nil key is ignored; an empty head is overwritten; a matching key is updated, or removed when the value is nil; a new non-nil key is appended at the chain tail. Unlinking a chained node runs the node destructor `0x00226768`, which first destroys the rest of the chain while the previous node still points there (a use-after-free the original tolerates). *[static]*
- **`0x00225B90`** - LUN VM register release; run for every register at interpreter (`0x002227D0`) exit. *[static]*
- **`0x00226600`** - First of the small LUN VM value helper functions (range `0x00226600`..`0x00226628`); role not described. *[static]*
- **`0x00226610`** - Script value write helper used to store builtin results (probably; exact type semantics not traced). Lies in the LUN VM value helper range `0x00226600`..`0x00226628`. *[unconfirmed]*
- **`0x00226628`** - LUN VM value add helper, used by the for-loop opcode for i = i + step; last of the `0x00226600`..`0x00226628` value helpers. *[static]*
- **`0x00226768`** - LUN VM table chain node destructor; destroys the rest of the chain first. *[static]*
