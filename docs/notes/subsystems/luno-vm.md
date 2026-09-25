# Luno script VM (stage scripts)

SSX 3 drives its scripted world content (trigger volumes, moving set pieces, pickups, collectibles, hub connectors
and Big Challenge missions) with small bytecode programs for EA's "Luno" register VM. Each loaded track's stage
chunk holds a set of `LUN` programs plus a table of per-instance handler rows; the game runs a program when an
instance's course section activates, when a rider touches the instance, when an entity attached to it finishes,
and at a few global moments such as the race GO. Programs call back into the game through a table of 111 builtin
functions that build entities and modifiers, apply effects to riders, and query game state.

Facts are from reading the code unless marked: **(PS2)** means it was checked against the game running on a PS2
emulator (savestates, memory reads at specific frames, or controller replays compared frame by frame), and
**(unconfirmed)** marks inferences.

## Where it lives

- `src/luno/lunovm.cpp`: the interpreter `0x002227D0` (`luno_cLunoVM_execute`) with every opcode handler (all of
  them are case labels inside that function), and the value/table helpers `0x00224D00`..`0x00226768`, including
  `0x00224E50` (`luno_cLunoTable_constructTable`) and `0x00225338` (`luno_cLunoTable_set`).
- `asm/1137E8.s` (not yet split): the frame-setup entries `0x002224B8` (host entry) and `0x00222648` (script call),
  next to two small functions at `0x002224A0` and `0x002224A8` that belong to the same group (roles not described).
- `asm/1FBE38.s` (not yet split): the builtin functions (`0x002FB498`..`0x00306CB0`) and their helpers, e.g.
  `0x002FAE38` (`checkActiveNode`), `0x002FC2C0`, and `0x002FE840` (`cViewer_addParticle`, builtin 25).
- `src/wscript/wscriptman.cpp`: the host runners `0x00309C88`, `0x00309E50`, `0x0030A060`, `0x0030AC98`, the
  handler-slot runners `0x0030A598` / `0x0030A5C0` / `0x0030A688`, mission ops `0x0030A868`, the collectible slot
  `0x0030B928`, and builtin callees `0x0030BFC0` and `0x0030C4A8`.
- `src/wscript/wscriptprocess.cpp`: `0x00308DB8` (setup programs) and the mission objects (`0x00308C60`,
  `0x00308FE0`, `0x00309118`, `0x00309270`).
- `src/world/world.cpp`: `0x003A6D18` (program lookup) and `0x003A6B78` (handler-slot lookup).
- Data: the opcode jump table `0x004797B0` (.rodata, 43 entries), the builtin table `0x00441F38` (.data, 111
  entries, entry = `0x00441F38 + 4*index`), and the allocation-tag strings at `0x00479780`..`0x00479880`
  (`LunoVMRegister`, `LunoVMCallParam`, `cLunoTable`, `LunoTable`, `TableData`, `cLunoTableEntry`).

gp is `0x004A30F0`; gp-relative globals are given below as absolute addresses with the gp form in brackets.

## Terms

- **Track / stage.** A location is loaded as several tracks, and a track can carry a stage chunk (kind 16) with
  its own programs. Stage tracks of the race worlds: Snow Jam (ARA1) 3/8/9, Metro-City (BRA2) 14/16, The Junction
  (BHP1) 13/15, R&B (ASS1) 11 plus hub connector A_ASS1 4, Crow's Nest (ABA1) 5 plus A_ABA1 2. Snow Jam's
  race stage has 238 programs, Metro-City's (track 16) 427.
- **Program / resource reference.** A 32-bit word `id << 8 | track`. Handler rows and mission records name programs
  this way (e.g. `0x1C08` = program 0x1C of track 8), and programs pass instances, splines and rails to builtins in
  the same form (usually pushed with op 0x27).
- **Instance / entity.** Instance +0x8 runtime flags, +0xC entity (0 when none), +0x10 matrix, +0x78 resource id.
  Entity +0xC vtable, +0x10 node type, +0x18 instance, +0x1C modifier container (container +0 = primary modifier).
  Builtins mostly create entities and modifiers on instances; those classes belong to the entity/modifier system.

## Stage chunk (kind 16)

| offset | contents |
|---|---|
| +0x18, +0x1C | handler-row table: six words per row (Snow Jam: 231 rows starting at +0x70; the BHP1 notes give +0x6C) |
| +0x20, +0x24 | mission records, 0x54 bytes each |
| +0x30, +0x34 | mission steps, 0x38 bytes each; the handler rows end exactly at the +0x34 offset |
| +0x38 | program count |
| +0x3C | offset of the program offset table (one word per program, strictly increasing) |
| +0x40 | end of the program area (the following collision data starts here) |

Programs start 16-byte aligned after the offset table (on Snow Jam the first starts exactly at the table's end). Each
program's extent reaches the next program exactly; the last one may be followed by zero padding (BRA2, BHP1).

**Handler rows.** An instance's row index is its collision descriptor word +0x08 shifted right by 8 (its resource
id). The six words are handler slots 0..5; each is a program reference or −1 (`FFFFFFFF`). `0x003A6B78` looks a slot
up and returns −1 when it is empty. What each slot is used for is under "Handler slots" below.

## LUN program format

| offset | contents |
|---|---|
| +0 | magic `4C 55 4E 00` ("LUN\0") |
| +4 | code end, in bytes from the header (at least 0x10) |
| +8, +0xC | extent (stored twice) |
| +0x10 .. code end | code words; pc is a word index counted from +0x10 |
| code end .. extent | trailer: one 16-byte function record per function |

Function record `i` is read at `header + codeEnd + 16*i`:

| field | meaning |
|---|---|
| +0 | byte offset back to the header, `-(codeEnd + 16*i)`; the VM does not use it |
| +4 | start pc |
| +8 | register count. Frame setup only ever reads record 0's count, even when it enters another record. |
| +0xC | argument-stack capacity; `0x002227D0` allocates `capacity*16 + 16` bytes when it is > 0 |

Every course stage program has one record, except program 3 of each course stage (ARA1, BRA2, BHP1), which has
three. Its function 0 stores two function values (op 0x1D, records 1 and 2) into the globals table under the
symbols with hash values `0DFB527E` and `0A3FBCE3` (hex); the host later calls such callbacks by name through
`0x00309E50`. Program 3 is also the stage's "global handler 2", which runs at race GO (see "Lifecycle").

**Instruction encoding.** `word = op | b1<<8 | b2<<16 | b3<<24`. Jump targets are `word >> 16` (a word index).
Opcodes 0x14–0x17, 0x1D and 0x24–0x27 take one inline operand word that follows the instruction; every other opcode
is a single word. There is no bounds check on the operand: an inline word at the code end is read from the trailer.
For op 0x21 (builtin call) b1 is the destination register, b2 the builtin index and b3 the argument count.

## Values

A value is 12 bytes, `{word0, word1, type}`.

| type | meaning |
|---|---|
| 0 | nil. The constant nil is `0x004C9098` = {0,0,0}; builtins may return nil with any word0. |
| 1 | int |
| 2 | float (bits in word0) |
| 3 | symbol: a 32-bit name hash, loaded by op 0x14. Every course table key is a symbol. |
| 4 | table: word0 points at `{+8 refcount, +0xC modulus, +0x10 head-node array}` |
| 5 | function: word0 = program header, word1 = function record index |
| other | copied as word0; always truthy; comparable only with the same type |

Copy and release rules:

- Only a type-5 copy copies word1. Every other copy writes word0 and the type and keeps the destination's old word1.
- Copying a table increments its refcount (`0x00225068`). Releasing it (`0x00224DF0`) decrements the refcount; at
  zero the table is destroyed (`0x00224D00`) and word0 is cleared.
- Every register write first releases the destination (when it holds a table), then sets its type to nil and word0
  to 0, and only then reads the source. So a self-move `mov rX, rX` (ops 0x0B/0x13) leaves nil.
- Builtins never create tables. Op 0x19 creates a table holding two references (the `cLunoTable` handle, which is
  never released, plus the register), so tables created by scripts are never freed.

## Frames, registers and the argument stack

- **`0x002224B8` `(frame, funcref*, globals*, ret*)`** is the host entry. It allocates `record0.registerCount`
  registers of 12 bytes, zeroing word0 and the type of each (word1 is not cleared). `reg0` is a table copy of
  `*globals` (`0x00225068`) with the type forced to 4; `reg1` is nil. It then calls the interpreter.
- **`0x00222648`** is the frame for a script-to-script call (op 0x1B). It is the same as `0x002224B8` except that
  `reg0` is copied from the caller's `reg0` and `reg1` is a copy of the argument register.
- **`0x002227D0` `(frame, funcref*, ret*)`** is the interpreter. Its stack frame holds the program header at +0x70,
  the code base at +0x74, the code word count at +0x78, the argument stack at +0x7C and the argument count at +0x80;
  `s6` is pc and `s7` the return slot. It loops `while (pc < codeWords)` with a signed compare; each iteration
  fetches a word, increments pc and dispatches `word & 0xFF` through `0x004797B0` (the dispatch is at `0x002228C4`
  inside the function). Opcodes 0x2B..0xFF do nothing. On exit it releases every argument-stack entry (all
  `capacity` entries, top first), then every register (`0x00225B90`), and frees both blocks.

The argument stack holds 16-byte entries `{int key, 12-byte value}`. Push opcodes write at the current count and
increment it; a builtin call consumes the top `b3` entries by lowering the count. Consumed entries are not released
at the call; they are released when a later push overwrites them or when the frame exits.

## Opcodes

x = `reg[b2]`, y = `reg[b3]`; the destination is `reg[b1]` unless noted. "Handler" is the case label inside
`0x002227D0`.

| op | handler | semantics |
|---|---|---|
| 00 | `0x00222B44` | pc = word>>16 |
| 01 | `0x00222A60` | if truthy(reg[b1]) pc = word>>16 |
| 02 | `0x00222AD0` | if !truthy(reg[b1]) pc = word>>16 |
| 03 | `0x00222DD4` | int(x == y) |
| 04 | `0x00222EE4` | int(x != y); pairings that cannot be compared give 0 |
| 05 | `0x00222FF4` | int(x >= y) |
| 06 | `0x00223118` | int(x > y) |
| 07 | `0x00223238` | int(x <= y) |
| 08 | `0x0022335C` | int(x < y) |
| 09 | `0x0022347C` | or: `x.type == nil ? 0 : x.w0 ? 1 : (y.type != nil && y.w0 != 0)` |
| 0A | `0x0022353C` | and: `int(y.type && x.type && x.w0 && y.w0)` |
| 0B | `0x002235E0` | reg[b1] = reg[b2] (shares 0x13's code) |
| 0C | `0x00223644` | x + y |
| 0D | `0x002237FC` | x − y |
| 0E | `0x0022398C` | x × y |
| 0F | `0x00223B1C` | x ÷ y (an int divisor of 0 hits BREAK 7) |
| 10 | `0x00223E08` | reg[b1] = nil |
| 11 | `0x00223CD0` | int x % int y when both are ints, else nil (BREAK 7 on 0) |
| 12 | `0x00224030` | table set: reg[b1][reg[b2]] = reg[b3] (`0x00225338`) |
| 13 | `0x002240C0` | move |
| 14 | `0x00224154` | reg[b1] = symbol(inline) |
| 15 | `0x002241B0` | reg[b1] = int(inline) |
| 16 | `0x00222A04` | reg[b1] = int(inline) |
| 17 | `0x002229A0` | reg[b1] = float bits(inline) |
| 18 | `0x00224660` | table get: reg[b1] = reg[b2][reg[b3]] (`0x00225248`) |
| 19 | `0x002246EC` | reg[b1] = new 32-bucket table |
| 1A | `0x00224B2C` | no-op |
| 1B | `0x00223EE0` | if reg[b2] is not nil: call function reg[b2] with argument reg[b3], result into reg[b1] (`0x00222648`) |
| 1C | `0x00224070` | table set as in 0x12, then reg[b2].word0 += 1 |
| 1D | `0x00224214` | reg[b1] = function {this program, record = inline} |
| 1E | `0x00224764` | reg[b1] = nil |
| 1F | `0x002247F8` | *ret = reg[b1]; pc = end |
| 20 | `0x002228F0` | push {key b1, reg[b2]} |
| 21 | `0x00223F58` | builtin call: `table[b2](&temp, b3, &args[count − b3])`; reg[b1] = temp; count −= b3; temp released |
| 22 | `0x00222B4C` | not: int → int(w0 == 0), float → int(f == 0), otherwise nil |
| 23 | `0x00222C98` | negate: int → −w0, float → NEG.S, otherwise nil |
| 24 | `0x0022428C` | for-loop step (below) |
| 25 | `0x00224878` | push {key b1, int(inline)} |
| 26 | `0x002248E0` | push {key b1, float bits(inline)} |
| 27 | `0x00224958` | push {key b1, int(inline)}; course programs use it for `rid<<8 \| track` references |
| 28 | `0x002249D0` | push {key b1, int(b2)} |
| 29 | `0x00224A3C` | push {key b1, float(b2)} |
| 2A | `0x00224AB0` | *ret = nil; pc = end |

### Truthiness (ops 0x01/0x02)

- nil is false.
- An int or symbol is true when `word0 != 0`.
- A float is true when `f != 0.0`, so −0.0 is false.
- Tables, functions and every other type are true.

Ops 0x09 and 0x0A do not use this test: they look at the type and word0 only, so for them a float −0.0 is true.
0x09 is also asymmetric: a nil x gives 0 whatever y is, a non-zero x.word0 gives 1, and only otherwise is y tested.

### Comparisons (ops 0x03–0x08, the table key match, and the loop test)

- **Same type:** compares word0. Ordering uses signed ints, also for floats, so two negative floats compare in
  reverse.
- **x float, y int:** compares x with `CVT.S.W(y)`.
- **x int, y float:** compares x with `CVT.W.S(y)` (truncated and saturated).
- **x symbol, y int:** unsigned compare.
- **Any other pairing:** false for every operator, including `!=`.

### Arithmetic (ops 0x0C–0x0F and the add helper `0x00226628`)

- **Same type:** float uses the EE scalar operation: ADD/SUB keep the guard bit, MUL rounds by chop, DIV rounds to
  nearest, and a divisor with a zero exponent gives a signed maximum-magnitude result (sign | `7F7FFFFF` hex). Int
  uses 32-bit MIPS arithmetic. Symbol + symbol gives a symbol; addition is the only operation that works on symbols.
- **float ∘ int:** `x ∘ CVT.S.W(y)`.
- **int ∘ float:** `x ∘ CVT.W.S(y)`, giving an int.
- **Anything else:** nil.
- Denormal, Inf and NaN operands are flushed the EE FPU's way; the notes do not describe the details.

### For loop (op 0x24)

b1 = i, b2 = limit, b3 = step, inline word = target.

```
negative = step < 0.0f          // comparison rules above: a float step is tested on its sign bit
if (negative ? i >= limit : i <= limit) { i = i + step  /* 0x00226628 */; pc = target; }
// otherwise fall through
```

`nil <= nil` holds (a same-type compare of word0), so a loop whose registers are nil never ends.

## Tables

A table has `n` embedded 32-byte head nodes: key at +0, value at +0xC, next at +0x18, vtable at +0x1C. The bucket is
`key.word0 % (n − 1)` (unsigned), so the last head is never used. Host-created tables have 8 heads, op 0x19 makes 32.

- **get (`0x00225248`):** returns nil when the head's value is nil, without walking the chain. Otherwise it walks
  from the head and returns the value of the first key that compares equal (comparison rules above).
- **set (`0x00225338`, `luno_cLunoTable_set`):**
  - a nil key does nothing;
  - an empty head (value nil) is overwritten with the key and value, even when the value is nil;
  - a matching head key gets the new value; a nil value empties the bucket and so hides its chain from get;
  - a matching chained key gets the new value. A nil value unlinks that node and runs its destructor `0x00226768`,
    which first destroys the rest of the chain even though the previous node still points there. The freed nodes'
    keys and values read as nil afterwards (links and stale words intact) as long as the memory is not reused, so
    later entries of that chain can no longer be found (unconfirmed); with reuse the behaviour depends on the heap;
  - when no key matches, a non-nil value is appended as a new chain node at the tail.
- Hashing a table or function value uses its address, so its bucket depends on the heap. Course programs only use
  symbol keys.

Other helpers in the same group: `0x00224E50` (`luno_cLunoTable_constructTable`), `0x00224DA0` and `0x00224F30`
(table helpers, roles not described), `0x00225B90` (register release), `0x00226600` and `0x00226610` (value
helpers; builtins store results through `0x00226610`).

## Builtins

### Calling convention

`fn(value* result, int count, arg* args)`: `args` points at the top `count` argument-stack entries in push order,
each `{int key, 12-byte value}`. Builtin numbers in this note are decimal indices into `0x00441F38` (for example
builtin 65 = 0x41 has its entry at `0x0044203C`).

### Keyed argument parsing

Builtins read their arguments by key, not position. The shared pattern (seen in builtin 27 at `0x002FF850`, defaults
`0x004FBAE8`, expected types `0x00446530`; builtin 65 at `0x00301D78`, types `0x004A3CB0` [gp+0xBC0]; builtin 34 at
`0x00300770`, types `0x004A3C40` [gp+0xB50], default `0x004A5688` [gp+0x2598] initialised lazily through
`0x004A5690` [gp+0x25A0]):

1. Start from a default word array.
2. For each argument: if `type == expected[key]`, store word0.
3. Otherwise, if the expected type is float, store `CVT.S.W(word0)`, whatever the argument's type.
4. Otherwise store word0 unchanged (so a float given where an int is expected is copied raw).

An argument value of −1 for a player or an instance means "current": the current player or current instance from
the script context.

### Script context

The builtins and hosts share one context object, `ctx = *(0x004A3DD8)` [gp+0xCE8]. Offsets used by the VM hosts
(the mission notes use the same offsets without naming the pointer):

| field | use |
|---|---|
| +0x0 | current player (roster slot); `0x0030A060` sets it to the contacting rider's slot (rider+0x86C) and restores it afterwards |
| +0x40 | queued events for missions (kind 0 = contact from `0x0030A060`) |
| +0x1C4 | mission offer queue |
| +0x28C | passed to `0x003A6D18`, which yields the program `0x00309C88` runs |
| +0x290 | current instance |
| +0x2A4, +0x2A8 | where `0x0030A060` / `0x0030AC98` find the instance's table used as globals: +0x2A4 directly, or +0x2A8 → +0x3C → +0x1C |
| +0x2B4 / +0x2B8 | inactive / active mission lists |
| +0x2C0 | the single collectible slot |
| +0x3CC + 4*slot | per-stage globals tables used by `0x00309C88` |

**Resolving a resource reference to an instance** (shown for builtin 34; builtin 65 resolves through the same world
table at `0x004A47B8` [gp+0x16C8]):

```
W = **0x004A47B8;  track = *(*(W+8) + 4*(res & 0xFF));
e = *(*(track+0x1C) + 4*(res >> 8));  inst = (e >> 8) << 2;   // 0 when absent
```

**Current rider:** `*(*(*(*(0x004A28A8)+0x84)+0xC)+0x28+4*player)` [gp−0x848], the race roster (human 0, computer
riders 1..5).

### Builtin index

Builtins called by the stage programs of Snow Jam, Metro-City and The Junction, plus the ones the hub and mission
programs use. "–" means the notes give no address for the entry. Class addresses are vtables.

| # | address | working label | notes |
|---|---|---|---|
| 0 | `0x002FC0D0` | Object entity (node type 17) | ctor `0x00356DB0`, vtable `0x00490E80`; `0x0034FB00` sets instance+0xC, `0x001032C0` sets flag 0x100 and adds the instance to the renderer's dynamic list; with default arguments turns `flags&3 == 3` into bit 2; its contact method is the 30-tick guard `0x00355770` |
| 1 | `0x002FC7D0` | Debounce | below |
| 2 | `0x002FC420` | set node state | below |
| 3 | `0x002FBCB8` | LiveComp animation player | ctor `0x00341AA0`, vtable `0x00490B10`, keys below (PS2) |
| 6 | `0x002FB498` | AnimTeeter | ctor `0x003421A0`, vtable `0x004908F8` (log teeters); its contact method is also the guard `0x00355770` |
| 7 | `0x002FBEC8` | one-way volume (Boost, node type 8) | `0x00341388` / `0x003415D0` / `0x00341818` / `0x001250A8`; rider list at rider+0x5B8; entity vtable `0x004914E0`, whose contact method `0x003609F0` is empty (PS2) |
| 12 | `0x002FC9C8` | flag cloth | → `0x0034AC88`; flag entity ctor `0x0034ADD8`, vtable `0x0048FC10`, 15-slot flag manager `0x0034C548` (PS2) |
| 13 | `0x002FCFF0` | MeshAnim break pieces | build `0x00351B40` (pose from a LiveComp node or the magnet), draw `0x00352230`, update `0x00352500`; end modes 0/1/2 and handler slot 4 (PS2) |
| 15 | `0x002FD250` | RollerModifier (crash bag) | → `0x00355DB8`, 0x2D0 bytes, ctor `0x0035DA70`, vtable `0x0048F080`, name string `0x0048E908`; takes the rider's contact packet |
| 16 | `0x002FD420` | particle burst / emitter | turns the entity into a type-13 emitter (`0x003578A8` → `0x00355F10`); keys follow the field order of the particle profile (one note labels it MakeParticleData) (PS2) |
| 18 | `0x002FDC60` | ParentModifier | vtable `0x0048F508`, ctor `0x00357038`, eval `0x00357108` (child = parent node matrix, translation + R × offset +0x30) |
| 19 | `0x002FDED0` | SplineModifier | vtable `0x0048F250`; defaults `0x004FB778`; `0x00355AD0` allocates 0xF0 bytes, ctor `0x00359460` (PS2) |
| 20 | `0x002FE0C0` | MultiSplineModifier | vtable `0x0048F168`; `0x00355B30` (`cMoveNode_addSpline`) → ctor `0x00359F88` (PS2) |
| 21 | `0x002FE2C0` | UVScrollModifier | ctor `0x0035F6E8`, tick `0x0035F7D0` (PS2) |
| 22 | – | TexFlip | `0x0035F0B8` is listed with the class (probably its ctor, unconfirmed); unused on Snow Jam |
| 23 | – | PositionModifier | vtable `0x0048F5F0` |
| 25 | `0x002FE840` | particle add (`cViewer_addParticle`) | Particle vtable `0x004912B0` (PS2) |
| 26 | `0x002FEE98` | DynamicParticle trail | vtable `0x00491268` (PS2) |
| 27 | `0x002FF850` | player effect | below |
| 29 / 58 | `0x002FFB50` / `0x002FFD58` | Hide / Unhide | type-16 nodes (vtable `0x00491800`) |
| 30, 31, 73 | `0x002FFF00`, `0x003000A8`, `0x00300260` | sounds | one set-piece note ties a builtin-31 call (argument 181) to the raven's flap animation ("AnimObject"); unresolved |
| 34 | `0x00300770` | teleport current player | below |
| 37, 38, 39 | `0x00300E28`, `0x00300F50`, `0x00301120` | collectibles | below |
| 40 | `0x003012F0` | mission control | → `0x0030A868`, ops 0..19 (below) |
| 43 | `0x00302778` | event-kind test | below |
| 44 / 61 | `0x00302968` / `0x00303430` | set / read current instance | −1 when there is none |
| 47 | – | mission: next task | |
| 48 | `0x002FF1C8` | RailModifier | ctor `0x0035B708`, vtable `0x004911D0`; binds rails to a node (log teeters, falling billboard) |
| 50 / 79 | – | rider stat | `0x00122EE8`, key through table `0x004897B0` |
| 52 | `0x00303130` | has entity | slot-2 trigger programs use it as a "launched once" guard |
| 55 | `0x003019C8` | LiveComp timer gate | true when the player's time crossed key1/30 s during this tick (`0x0034EBE0`); used by slot-5 timeline programs |
| 64 | – | move rider to the instance | `0x001234D0`: placement `0x0011D660` semantic 5, then start-grid control 6 |
| 65 (0x41) | `0x00301D78` | rider in volume / contact predicate | below |
| 67 | – | course event from free ride | the notes associate it with `0x0022D6C8`; triggered by the RaceRideState volumes; in free ride it turns the ride into that course's event and the race card opens (PS2) |
| 68 | – | hub actions | below |
| 69 | `0x00302490` | particles stop / attached-entry state | below |
| 75, 76, 98 | – | mission "Count", timer, "Goal" | |
| 77 | `0x00303598` | random number | one gameplay-RNG draw (`0x00317810`, `AIrand__Fv`); e.g. `builtin77(0, 100) < 90` gates a 90 % branch |
| 81 / 86 | – | height (missions) | |
| 87 | `0x00304E38` | contact guard preset | entity+0x20 = int(60 × s) |
| 88 | `0x00303BA0` | CrowdMan2d | crowd texture animation (16 frames, 3 ticks each) and camera-flash areas; the updater `0x00229530` draws 3 visual-RNG values per flash-timer expiry |
| 90 | `0x00305478` | MagnetModifier | vtable `0x0048F420`; the slot-2 program runs once the pickup has reached the rider (`0x00357660`); a Debounce freezes its matrix (PS2) |
| 95 | – | AvaSpline | vtable `0x0048F338`; unused on Snow Jam |
| 97 | `0x003057C0` | HaloModifier | vtable `0x00491220`. An older class list in the notes gives 92 for Halo; unresolved, 97 is the entry with an address. |
| 99 | `0x003061B0` | option enabled | below |
| 105 / 106 | `0x00306A90` / `0x00306CB0` | MultiParticle add / remove | one static emitter per group (`0x00357BF8`); remove takes the first match (`0x003581F0`) (PS2) |
| 107 | – | gate order | `0x0030BFC0`: in the gate → 1; beyond 1.1 / 1.5 × the gate spacing → −1 (missed) |
| 63, 78, 83, 110 | – | not analysed | 63 is described as a rail id and 83 as called tricks |

In a race, 40, 47, 50, 63..65, 67, 68, 75, 76, 78, 79, 83, 98 and 107 are inert: their programs do not run there or
they return 0.

### Builtin details

**1, Debounce (`0x002FC7D0`).** Keys: 0 target instance (default −1 = current), 1 duration (float, default 1.0),
2 restore mode (default 1), 3 flag mode (default −1); keys 2 and 3 are confirmed by the authored calls, 0 and 1 follow
the order of the default array (unconfirmed). An existing Debounce on the instance is updated through
`0x002FAE38` (`checkActiveNode`); otherwise a component named "Debounce" (string `0x004896E8`) is built by
`0x00342C08`: ticks = int(duration × clock rate), with the clock at `0x004C9428` (through `0x004A5B64` [gp+0x2A74])
and rate 60 at +0x10. Flag mode 0 clears the instance flags' low four bits; the restore mode is kept at +0x30. The
update `0x00342D88` decrements a positive count and calls the completion (vtable +0x114) only when it reaches zero;
a count that starts at zero or below never expires. The completion `0x00342E98` first checks the instance's handler
slot 4 (`0x0034FCC0`): a program there replaces the default completion. Otherwise restore mode 0 makes a permanent
DeadNode and 3 removes the Debounce and builds a RestoreNode (`0x00350F60`, vtable `0x00491680`). A Debounce replaces
whatever entity the instance had (`0x00355F10`: its effects move over, a magnet is frozen).

**2, set node state (`0x002FC420`).** Makes the instance a DeadNode (node type 6, tag `0x004896B8`), restores its
authored flags, or makes a RestoreNode (type 19, tag `0x004896C8`). When the instance's own event-6 handler returns
false it falls back to `0x002FC2C0` (call site `0x002FC590` inside `0x002FC420`):

| mode | behaviour of `0x002FC2C0` |
|---|---|
| 0 | keep an existing type 6; otherwise destroy the node (mode 3) and build a DeadNode |
| 1 | keep an existing type 6; otherwise destroy the node (mode 3), then restore the flags from the authored high half and the retained runtime bits (read after the destruction callback, which may change them) |
| 3 | keep an existing type 6 or 19; otherwise destroy the node (mode 3) and build a RestoreNode |
| other | nothing |

DeadNode and RestoreNode have empty draw and contact callbacks (`0x00360790` / `0x003609F0`).

**3, LiveComp player (`0x002FBCB8`).** Keys: 1 mode (once / loop / ping-pong), 2 reverse, 3/4 time range in 1/30 s,
5 rate, 6 random rate spread, 7 start time, 8 random start from the gameplay RNG (`0x004FF030`), 9 hide the static
draw. The tick `0x00341D48` advances 1/60 s per game tick in the entity pass, then runs the owner's handler slot 5
(`0x0034EBA0` → `0x0030A688`); a finished once-mode player runs slot 4 (`0x0034FCC0` → `0x0030A598`). (PS2)

**19, Spline (`0x002FDED0`).** Speed in km/h × 27.777779 (cm/s), starting at 0, or at the path length for a
negative speed; the constructor makes one `AIrandf__Fff` draw (`0x00317830`) even with zero jitter. At the path end
the entity update `0x00356198` runs handler slot 4 (entity vtable +0x114, `0x0034FD00`). For the stop-mode pieces
(Snow Jam rockets, spin twins, dragons) that slot calls builtin 16, which turns the entity into an emitter, frees the
spline and attaches a PositionModifier (`0x00356F10`) holding the end matrix. (PS2)

**27, player effect (`0x002FF850`).** Keys: player (−1 = current), 1 effect type, 2 amount (float). It calls
`0x0010F1C0`, which dispatches types 0..7 through `0x00456AF0`:

| type | effect |
|---|---|
| 1 | rider interface (rider+0x6C0) slot +0x6C → `0x0010E770`: adds the amount to rider+0x2E8 (boost counter) |
| 2 | slot +0x74 → `0x0010E7D0`: adds the amount to rider+0x2EC |
| 5 | reset with the "Wrong Way!" message (reset reason 4 via `0x00116120`) |
| 6 | point icons (→ `0x0010E8B8` → `0x00119608`; 2000/3000/5000/10000) |

Types 1 and 2 also request feedback: `0x0028B180` → `0x0029CED8` (kind 0/1) and `0x0028B180` → `0x002A3B18`
(kind 1/2).

**34, teleport current player (`0x00300770`).** One key: 0 = destination instance (int, default −1 = ctx+0x290).
No-op when the current player is < 0 or the instance is absent. The destination matrix is the entity's vtable +0xC4
result when the instance has an entity (for an Object entity, `0x00356078` returns the primary modifier's matrix
or `instance+0x10`), else `instance+0x10`; on Metro-City the destinations resolve to `instance+0x10` (PS2). It then
calls the rider's vtable +0x54 = `0x00123210` (human vtable `0x004583A8` and computer vtable `0x00458660` both
point there, so computer riders teleport too) and returns nil. `0x00123210(rider, M)`, in order:

1. the race-event observer `0x00270970` (releases a pending gate link; a no-op at race start);
2. destination `P = r3 + 100 × (a·r0 + b·r1)` with (a, b) by roster slot rider+0x86C: 0:(2,0) 1:(1,0) 2:(2,−2)
   3:(2,2) 4:(1,−2) 5:(2,1), any other slot (0,0); direction `D = r0` (r0..r3 = matrix rows, r3 = translation);
3. score reset `0x00119368(rider+0x790, 1)`, return value discarded;
4. current motion exit, then the ground entry `0x0013C7A8` (velocity × 0.7, or × `min(0.7 + (airTicks − 40)×0.01, 1)`
   after more than 40 ticks in the air);
5. control exit and control 0; stop the reset fade (`0x00125038`); camera set-target; speed = |v|; placement
   `0x0011D660(P, D, semantic 5, clearance 0)` with a camera cut; v = forward × speed (z kept); FX reset
   `0x00111890`.

No PS2 recording reaches a teleport beam, so the rider side is from code reading only.

**37 / 38 / 39, collectibles (`0x00300E28` / `0x00300F50` / `0x00301120`).** Use `0x0030C4A8` and the byte
`0x00535C11` (0 = career path, 1 = single event; it affects builtin 38). In a single event every listed collectible
becomes a DeadNode. In career races the uncollected ones stay (their section builds them: LiveComp + magnet + halo,
one gameplay-RNG draw), and a collect updates the career save row and awards cash. A location's stage opens the one
collectible slot ctx+0x2C0 (`0x0030B928`, only when it is free) when its read completes.

**40, missions (`0x003012F0` → `0x0030A868`).** Ops 0/1/2/18 stop / start / next task / quiet stop, 3 restart,
4 success, 5 fail, 8/9/11 post to the offer queue ctx+0x1C4, 12..16 status bits (16 = available and nothing
running), 19 last of chain.

**43, event-kind test (`0x00302778`).** Returns `int(table_0x004465F8[n] == value at 0x00535C10)`. In the courses'
own events the value is the race kind on Snow Jam and Metro-City and the half-pipe kind on The Junction; it is 1 on
R&B, 2 on Crow's Nest, and 4 in free ride. Mode fences, start-mode colliders and challenge reset planes use it in
their slot-1 programs to kill themselves (builtin 2 → DeadNode) when the kind does not match; e.g. a hub challenge
reset plane runs `builtin43(6)`, the kind is 4, so it becomes a DeadNode, and touching it would otherwise apply
builtin 27 effect 5.

**65 (0x41), rider in volume (`0x00301D78`).** Resolves an instance resource through the world table (the block from
`0x00301E5C` inside the function), gets the current rider through the player manager and the current-player index,
calls the instance-contact predicate, and stores a boolean-like result through `0x00226610` (exact result type not
described). The mission notes describe it as "rider in volume" (the rider's volume list at rider+0x5B8). Snow Jam's
programs contain 17 one-argument calls of it.

**68, hub actions.** Keys: 0 map id (course table +0x5C), 1 action (1 nothing, 2 the Load trigger, 3 transport
booth, 4 lodge door), 2 entry index into `0x00445E40` = {2,3,4,5,1,1,1,0}. Human riders only. The hub connectors'
Unload and Load trigger programs lead to `0x0022CEA8` and `0x0022D088`; each also hides its own volume (29) and
unhides its partner (58).

**69, particles stop (`0x00302490`).** Resolves the current or given instance, checks its entity (instance+0xC,
vtable +0x84) and walks the entity's container (+0x1C). Key 1 = 1 calls `0x00353278`, which requests state 3
(vtable +0xC) on every attached entry of type 3; 0 calls `0x00353228`. The stage notes summarise mode 1 as deleting
halos.

**99, option enabled (`0x003061B0`).** Selectors 0/1/2 test bits 6/8/7 of `0x005308D0` (at `0x00306260` inside the
function) and return "enabled" when the bit is clear; any other selector returns 1. The pickups' slot-1 programs
query selector 1. It looks like an FX/debug option gate (unconfirmed).

## Running programs

### Host entry points

- **`0x00309C88`** runs function 0 of the program that `0x003A6D18` resolves from ctx+0x28C, with the globals
  `*(ctx+0x3CC + 4*slot)` (one table per loaded stage).
- **`0x00309E50`** looks a symbol up in those globals (`0x00225248`) and calls the function value it finds (the
  program-3 callbacks).
- **`0x0030A060`** (contact) and **`0x0030AC98`** run with the instance's table (ctx+0x2A4, or else through ctx+0x2A8
  → +0x3C → +0x1C). When there is none they use a temporary 8-bucket table released afterwards.
- **`0x00308DB8`** runs a setup program per instance with a temporary 8-bucket table.
- **`0x0030A598`** looks up handler slot 4 (`0x003A6B78`); when there is a program, **`0x0030A5C0`** sets ctx+0x290
  to the instance for the duration, runs it through `0x00309C88` and clears the context. **`0x0030A688`** runs
  slot 5.

All of these reach `0x002224B8`.

### Handler slots

| slot | runs when | path |
|---|---|---|
| 1 | the instance's course section is activated (section pass `0x00101B60`) | builds the instance's set pieces (LiveComps, modifiers, particles), kills event-specific objects |
| 2 | a rider's selected contact is this instance | `0x00121818` → entity vtable +0x144 → `0x0034FE00` → `0x002D19B8` → `0x0030A060`, or `0x0030A060` directly when the instance has no entity |
| 4 | an entity attached to the instance finishes (Debounce expiry, spline end, once-mode LiveComp end, MeshAnim end) | `0x0034FCC0` → `0x002D19E8` → `0x0030A598` → `0x0030A5C0` (the spline end enters through entity vtable +0x114 = `0x0034FD00`); an empty slot selects the entity's default completion |
| 5 | every tick of a playing LiveComp | `0x0034EBA0` → `0x0030A688`; the program fires timed events with builtin 55 |
| 0, 3 | not described (slot-3 programs exist on the Peak 1 locations) | |

**Slot 2 in detail.** `0x00121818` runs when rider+0xA30 (the selected instance) is non-null. With an entity it
calls the entity's contact method with rider+0xA60, the contact packet rider+0x9E0 and the interface rider+0x6C0.
For LiveComp and Object entities that is `0x00355770`: it calls the attached component's predicate (methods +0x54 /
+0x4C) when there is one and rejects when it says no, rejects while entity+0x20 > 0, and otherwise sets entity+0x20 =
clock rate / 2 (30 ticks at 60 Hz) and forwards. `0x0030A060` installs the current player (ctx+0, from the rider
interface's vtable +0x3C = rider+0x86C), the current instance and the contact context, skips a human rider that has
finished (rider+0x480) unless the mode word `G+0x84+0x214` (G = `*(0x004A28A8)`) is 4 (free ride), looks up slot 2
(`0x003A6B78`), runs it through
`0x00309C88` (with separate handling for a nested context), then calls the entity's end callback (vtable +0x14C;
`0x00355858` sets entity+0x20 = 30 ticks) and restores the context. The path is the same for computer riders, and
they do fire trigger programs in races (PS2).

### Lifecycle of a location's stage

1. **Read complete.** The stage's programs are built, the global handler programs run again and the collectible
   slot is claimed if free (`0x0030B928`). Mission objects are built by `0x00308C60`, one per mission record of every
   loaded stage, at the world start and at each exit from world state 10 (two ticks after a Load trigger); a stage
   loaded later gets its own.
2. **Section activation.** Slot-1 programs of the section's instances run; activation and unloading follow section
   streaming, so set pieces are created and dropped as the rider moves (PS2).
3. **Race GO.** Global handler 2 (program 3) runs. On all three race courses it starts the start-gate door LiveComps,
   which are built one tick after the race phase begins, before that tick's entity pass (PS2).
4. **During play.** Slot 2 on contacts, slot 4 on completions, slot 5 on LiveComp ticks, and the mission tick.
5. **Unload start.** `0x00230360` → `0x00103308` drops the location's instances without leave handlers and tears
   down its stage programs and entities; `0x00308FE0` drops its missions and frees the collectible slot.

### Order within a game update (PS2)

Inside the race update `0x002306B8`: first the group-1 entity pass (modifier and entity updates, including LiveComp
ticks with their slot-5 programs; the mission tick `0x00309270` also runs in the entity pass), then the rider manager
`0x00128AF0`, which calls `0x00121818` for every rider in slot order (human first) at `0x00128EA4`, so slot-2
programs run there, before any rider FX pass; the section pass `0x00101B60` follows the FX passes. A set piece
created by a slot-2 program in tick T is first updated in tick T+1.

### Missions (WScript)

Mission objects (WScriptMission, vtable `0x00489A30` over WScriptProcess `0x00489B70`; tasks `0x00489AE0`) run programs
named by the stage's mission records and steps (`program << 8 | track`: start / tick / stop programs, event programs,
completion / fail / status callbacks). Each run gets a fresh 8-bucket table (mission +0x1C) as its globals. The tick
`0x00309270` (entity pass) runs the pending op (`0x00309118`), clears the HUD words ctx+0x4/+0x10/+0x1C/+0x28/+0x34,
dispatches the queued events of ctx+0x40 to the mission's event programs and the current task's, then for each active
mission advances state 1 → 2 and runs the current task's tick and the mission tick program.

## Example: boost pickup programs (Snow Jam)

The speed-boost and trick-boost instances have handler rows with slot 1 and slot 2 filled (e.g. slot 2 = `0x1C08`
and `0x1E08`). The slot-2 programs begin with these calls:

```
builtin27(1: 1 or 2, 2: 5)   // effect type 1 = speed boost, 2 = trick boost; amount 5 (int → float by the key type)
builtin69(1: 1)
builtin1(2: 3, 3: 0)         // Debounce: default 1 s, restore mode 3 (RestoreNode), flag mode 0
```

The slot-1 programs query builtin 99 (selector 1) and then conditionally call FX-related builtins. A crash bag's slot-2
program is `builtin0(); builtin15(); return` (an Object entity, then a RollerModifier driven by the contact).

## Observations about the shipped programs

- Snow Jam's 238 race-stage programs decode into 8,522 whole instructions, each program ending exactly at its code
  end, and every builtin index is inside the 111-entry table.
- In the stages of Snow Jam, Metro-City and The Junction (858 programs, 864 function records) the opcodes 0x01, 0x0B,
  0x0F, 0x10, 0x11, 0x13, 0x19, 0x1A, 0x1B, 0x1C, 0x22 and 0x24 are never executed.
- Course programs only use symbol keys, so the address-dependent hashing of table and function keys does not come
  up in them.

## Open points

- Handler slots 0 and 3, and where the stage's global handler list is stored, are not described.
- The Halo builtin index (97 with address vs 92 in an older list) and the exact role of builtin 31 are unresolved.
- Builtins 63, 78, 83 and 110 are not analysed; 22, 23, 47, 50, 64, 67, 68, 75, 76, 79, 81, 86, 95, 98 and 107
  have no table address in the notes.
