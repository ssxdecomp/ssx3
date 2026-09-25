<!-- Generated from the SSX 3 port notes; see docs/notes/README.md. -->

# Function notes: src/replay/

## `src/replay/playbackman.cpp`

Segment `0x0026C458`-`0x0026DBF0`.

- **`0x0026CC48`** - World job wrapper with stateful job gating, on the rider light-refresh scheduling path (probably owns its timing, with `0x0026CD20`). Possibly also restart-point handling paired with `0x0026CDF8` (unconfirmed). *[static]*
- **`0x0026CD20`** - World job wrapper with stateful job gating, on the rider light-refresh scheduling path (probably owns its timing, with `0x0026CC48`). *[static]*
- **`0x0026CDF8`** - Probably restart-point handling used around the builtin 64 teleport (paired with `0x0026CC48`; unconfirmed). *[unconfirmed]*
- **`0x0026CE50`** - Condition used for the branch at `0x00230D24` (taken when non-zero together with `0x00270280` true); role otherwise unknown. *[unconfirmed]*
- **`0x0026D178`** - Accepted-command recorder dispatch, called by the (human) input provider after it produces its command; the recorder object is at motion owner +0xDF8, and in ordinary gameplay it dispatches to the RLE recorder `0x0026D2B0`. Not called by the NPC provider. *[PS2]*
- **`0x0026D2B0`** - Run-length-encoded accepted-command recorder for human riders (not called by the NPC provider): recorder+0 = record count, recorder+0x0C = buffer; each record is two little-endian u32, run length = word0 & 0xFFF, command = word0 & 0xFFFFF000. *[PS2]*

## `src/replay/replay.cpp`

Segment `0x0026DBF0`-`0x0026E908`.

- **`0x0026DBF0`** `cReplay_restoreFrame` - Saved-component loading path (calls `0x00354C98` on group 1); an earlier reading as the gameplay frame tick was corrected. After its other phases it calls the rider light / query-scope refresh loop `0x0012B788` at `0x0026DD90` (chain `0x0026DBF0` -> `0x0012B788` -> `0x00120E50`, observed every three ticks). *[PS2]*
  - `0x0026DD90`: Call to the rider light-refresh loop `0x0012B788` after the other world phases. *[static]*
  - Possible mismatch with the current name: Besides the saved-component loading role, sources describe it as the world job that refreshes the rider light/query scope every three ticks, which a replay frame restore name does not suggest.
- **`0x0026DDC0`** `cReplay_restoreBucket` - Saved-component loading path: after its `0x0026DED8` loop it drains group 1. Not a gameplay frame tick. *[static]*
- **`0x0026DE58`** - Walks active group nodes through vtable+0x1C; part of the saved-component loading cluster (exact role unconfirmed). *[unconfirmed]*
- **`0x0026DED8`** `cReplay_restoreObject` - Reads component record types and invokes deserializing constructors; used as the SSB course/world loader, dispatching record kinds 0..22 through the constructor table at `0x004816C0` (kind 8 -> `0x00341548` rail splines, 14 -> `0x0034ED88` AIP paths, 16 -> `0x00350F08` collision bindings, 17 -> `0x00356E60` course-progress objects, 21 -> `0x00349DB0` course spine). Not a gameplay tick loop. *[static]*
  - Possible mismatch with the current name: The name suggests a replay object restore, but records describe the generic component deserializer used to load SSB course/world records.
- **`0x0026E800`** - Releases a gate link: if entry+0xB0 is set, clears bit 1 << entry+0 in (entry+0xB0)+0x1E and zeroes entry+0xB0. *[static]*

## `src/replay/frameptr.cpp`

Segment `0x0026E908`-`0x00270070`.

- **`0x0026EFB8`** - Replay object constructor (object stored at session+0x28). *[static]*
- **`0x0026F850`** - Deferred world job routine with stateful gating, on the rider light-refresh scheduling path. *[static]*
- **`0x0026F8A0`** - Caller of `0x0028F200`, used by the restart/replay/quit menus. *[static]*
- **`0x0026F980`** - Caller of `0x0028F2C0`, used by the restart/replay/quit menus. *[static]*
- **`0x0026FB88`** - Replay transport input handler with UI sounds: FForward/FBackward when allowed -> sound kind 2, at the end/start -> kind 4; CycleCamera -> kind 2. *[static]*
  - `0x0026FBA0`: Replay transport UI sound listener call. *[static]*

## `src/replay/replaycache.cpp`

Segment `0x00270070`-`0x002753B8`.

- **`0x00270280`** - Pause/NIS gate: used by board loop sound callbacks (forces volume 0) and probably to select the frozen/pause branch at `0x00230D24` of the game update (with `0x0026CE50`). *[static]*
- **`0x00270628`** - Clears event+0x3D4 when it is set and the human count is 1. *[static]*
- **`0x00270730`** - Returns the human roster index of a rider id (rider vt+0x3C), or -1 for computer riders. *[static]*
- **`0x00270970`** - Race-event (checkpoint/gate) observer notified on teleport/reset; releases the human's pending gate link. If event+0x61C, +0x620 and +0 are all 0: slot = `0x00270730`(id); if slot >= 0, `0x00270DE0`(ev, slot); then `0x00270628`(ev). Also used by `0x00116120`. *[static]*
- **`0x00270AB0`** - Checkpoint handler: resolves the human roster index, checks inhibition, sets the human +0x5FC bit once and the manager notification bit (byte *(manager+0x3B4)+0x1F). *[static]*
- **`0x00270DE0`** - Race-event observer per-slot release step: when event mode (ev+0) is 0, calls `0x0026E800` on ev+0x494+0xB4*slot. *[static]*
- **`0x00274A30`** - NIS clock: advances script time one tick per game update (60 Hz); world tick equals script time. *[PS2]*
