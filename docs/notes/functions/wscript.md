<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/wscript/

## `src/wscript/wscriptprocess.cpp`

Segment `0x00307598`-`0x003094C8`.

- **`0x00308C60`** - Builds one WScriptMission per mission record of every loaded stage, at world start and at each world state-10 exit (two ticks after a Load trigger, builtin 68 action 2); a stage loaded later (Transport arrival) gets its own. Each run gets a fresh 8-bucket LUN table (m+0x1C) as the programs' globals. *[PS2]*
- **`0x00308DB8`** - Runs each instance's setup stage program with a temporary 8-bucket table. *[static]*
- **`0x00308FE0`** - Drops a stage's WScript missions and frees its collectible slot at location unload start; called from `0x00230360`. *[static]*
- **`0x00309118`** - Applies the pending WScript mission operation at the start of the WScript tick `0x00309270`. *[PS2]*
  - `0x003091EC`: Calls the freeride challenge end `0x0029DBB0` with arg 1 (silent). *[static]*
- **`0x00309270`** - WScript tick / WScriptMan update, run in the entity pass after the previous tick's rider pass. Order: pending op `0x00309118`; zero HUD words C+0x4/+0x10/+0x1C/+0x28/+0x34; dispatch queued events at C+0x40; then for each active mission state 1 -> 2, current task tick, mission tick program. Runs the global scripts, which can reach scripted strikes `0x00390EC8` and seed builtins and `0x00343C60` via `0x00303B38`. *[PS2]*

## `src/wscript/wscriptman.cpp`

Segment `0x003094C8`-`0x0030D8B8`.

- **`0x00309C88`** - Executes an authored LUN handler program: runs function 0 of a course stage program (from `0x003A6D18`(ctx+0x28C)) with globals *(ctx+0x3CC+4*slot). *[static]*
- **`0x00309E50`** - Host callback by name: looks a symbol up in the stage globals (`0x00225248`) and calls the function value found. *[static]*
- **`0x0030A060`** - Stage contact dispatcher: runs an instance's authored slot-2 (contact) program with player/instance/contact context. Sets ctx+0 to the contacting rider's slot (rider interface vt+0x3C() = rider `+0x86C`), applies player/ghost restrictions, skips a finished human (vt+0x44, `+0x480`) unless S+0x214 == 4 (free ride), looks up via `0x003A6B78` and executes via `0x00309C88` with the instance table (ctx+0x2A4, or ctx+0x2A8 -> +0x3C -> +0x1C; else a temporary 8-bucket table), calls an optional entity end callback, then restores/clears the context. Also used for course-script spline launch from `0x00121818`. *[static]*
- **`0x0030A298`** - Runs an instance's slot-1 (section activation) stage program. *[static]*
- **`0x0030A3A0`** - Section-pass helper that runs slot-1 (section activation) stage programs through `0x0030A298`. *[static]*
- **`0x0030A598`** - Runs an instance's slot-4 (completion override) stage program; wraps the authored handler slot lookup `0x003A6B78`. *[static]*
- **`0x0030A5C0`** - Runs an authored handler with a temporary current-instance context through `0x00309C88`, then clears the context. *[static]*
- **`0x0030A688`** - Runs an instance's slot-5 stage program. *[static]*
- **`0x0030A868`** - Mission operation dispatcher (ops 0..19): 0/1/2/18 stop/start/next task/quiet stop, 3 restart, 4 success, 5 fail, 8/9/11 post to the offer queue C+0x1C4, 12..16 status bits (16 = available and nothing running), 19 last of chain. *[static]*
  - `0x0030AAB4`: Calls the freeride challenge end `0x0029DBB0` with arg 0 (sound plays). *[static]*
- **`0x0030AC98`** - Runs an instance's stage program with the instance table (ctx+0x2A4 or the ctx+0x2A8 path), else with a temporary 8-bucket table. *[static]*
- **`0x0030B7F8`** - Ends an active Big Challenge; called by builtin 67 before starting a CTM event. *[static]*
- **`0x0030B928`** - Opens the single collectible slot ctx+0x2C0 for a stage, only when the slot is free. Each location's stage opens it at read completion and it is freed at unload start (`0x00230360` -> `0x00308FE0`); at a run start the first resident stage in load order takes it. *[static]*
- **`0x0030B9A0`** - Collectible award (stage builtin 39): calls `0x00119EF8` with kind 3, amount 500 / 1000 / 2000 by the course table's peak level, and calls the pickup sound dispatcher `0x0029CED8`. *[static]*
- **`0x0030BFC0`** - Builtin 107 gate-order test: resolves up to three authored resources and tests rider instance contact before the position/geometry tests; returns 1 when in the gate and -1 (missed) beyond 1.1 / 1.5 x the gate spacing. *[PS2]*
  - `0x0030C10C`: Calls the rider contact predicate through rider `+0x6C0` slot `0x1C` (through `0x0030C120`). *[static]*
- **`0x0030C4A8`** - Stage collectibles set-up (builtins 37/38/39) using the game type `0x00535C11` and the career collect row. *[static]*

## `src/wscript/wscriptcompile.cpp`

Segment `0x00351030`-`0x00351270`.

- **`0x00351170`** - Instance-clone helper used by the MultiSpline constructor. *[static]*
