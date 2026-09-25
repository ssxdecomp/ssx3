# Notes from the SSX 3 port

These notes describe what functions, globals and objects in `SLUS_207.72` do. They were written while building
a browser/native port of SSX 3. The port runs parts of the original code alongside hand-written
reimplementations of game subsystems: rider physics and terrain contact, rails, camera, animation, computer
riders, audio, race flow, world streaming and others. Writing those reimplementations meant working out what the
original functions do. These files collect that knowledge so it can help with naming and matching here.

They are working notes, not decompiled code. Treat them as leads. When a note and the assembly disagree, trust
the assembly.

## Target and addresses

- The executable is the same one this project targets: NTSC-U `SLUS_207.72`, SHA-1
  `77114dfd1205eaccf1ccc18c5f9650097fa78bd8`.
- Every address is an EE virtual address. That is the value splat uses as vram (file offset + `0xFF000`).
  Addresses are written as eight hex digits, for example `0x002227D0`.
- `gp` is `0x004A30F0`. Globals the code reaches through `gp` are given at their absolute address. The `gp`
  form is added where it helps.
- Struct offsets are written as `+0x1A4`. Hex constants that are not addresses are sometimes written with an
  `h` suffix (`3F800000h`) so they cannot be mistaken for addresses.

## What is here

| Path | Contents |
|---|---|
| [`functions/`](functions/) | Function-by-function notes: 2,163 functions and 588 notable addresses inside them. There is one file per `src/` directory, grouped by translation unit. |
| [`data.md`](data.md) | 499 globals, tables, vtables, strings and constants, grouped by ELF section. |
| [`structs/`](structs/) | Partial layouts of the main objects: the rider, its components, cameras and render objects, game-flow, front-end and audio objects. |
| [`subsystems/`](subsystems/) | 19 longer notes, one per subsystem, listed below. |

Subsystem notes:

- [Rider motion and physics](subsystems/rider-motion.md): motion modes, ground and air motion, terrain contact,
  jumping, landing and EE float behaviour.
- [Rider controllers](subsystems/rider-controllers.md): the controller table, attacks and board press,
  handplants, crashes and resets.
- [Rails and grinding](subsystems/rails.md)
- [Rider animation](subsystems/animation.md)
- [Tricks, scoring and boost](subsystems/tricks-scoring.md)
- [Collision, pickups and instance events](subsystems/collision.md)
- [Computer riders](subsystems/ai-racers.md)
- [Cameras](subsystems/camera.md)
- [Controller input](subsystems/input.md)
- [Random number streams](subsystems/random-streams.md): the `BXrand`/`AIrand` streams and the order in which
  they are drawn each tick.
- [Luno script VM](subsystems/luno-vm.md): the stage-script bytecode, its opcodes and its builtins.
- [Game modes, race flow and career](subsystems/game-flow.md)
- [World, peaks and streaming](subsystems/world-streaming.md)
- [Rendering and lighting](subsystems/rendering.md)
- [Rider visual effects](subsystems/rider-effects.md)
- [Set pieces and cutscenes](subsystems/set-pieces-cutscenes.md)
- [Characters and front end](subsystems/characters-frontend.md)
- [Audio, music and DJ](subsystems/audio.md)
- [Asset formats and their loaders](subsystems/asset-formats.md)

### How the function notes are organised

Inside each file in `functions/`, entries are grouped under the translation unit that contains their address.
The grouping follows the splits in `config/ssx3_us.yaml` on the `AI-Split-ID` branch at `da959b7`. Addresses
that are still inside an `asm` catch-all segment are in [`functions/unsplit.md`](functions/unsplit.md), under the
segment's splat name. If the splits change, some entries will belong under a different heading, but the
addresses stay valid.

An entry looks like this:

```
- **`0x00317810`** `AIrand__Fv` - what it does, what calls it, notable constants. *[PS2]*
  - `0x0031xxxx`: a note about a specific call site or block inside the function. *[static]*
```

- **Name.** If `config/symbol_addrs.txt` already names the address, the name follows the address. Otherwise
  the function is still `func_XXXXXXXX` here, and no name is shown. The descriptive phrases in the notes, such
  as "race game update" or "camera splash update", are working labels, not recovered names. None of them were
  added to `symbol_addrs.txt`.
- **Possible mismatches.** For 18 named functions, the notes describe a role that does not obviously fit the
  current name. Each of these entries carries a "Possible mismatch with the current name" line. These are
  offered as questions, not corrections.
- **Evidence tag.**
  - *[PS2]*: checked against the original game running in PCSX2 or ARMSX2 (an arm64 PCSX2 fork), using
    savestates, EE memory read at chosen frames, and controller replays compared frame by frame with our
    reimplementation.
  - *[static]*: read from the disassembly or data only. This includes behaviour confirmed by running the
    original instructions in isolation.
  - *[unconfirmed]*: an inference that has not been confirmed. The note says what is uncertain.
  The subsystem and struct notes use **(PS2)** and **(unconfirmed)** marks in the text in the same way.
- **Function boundaries.** An address counts as a function start here if splat's current split, a
  heuristic function scanner, a `jal` target, a code pointer in `.data`, or a standard prologue marks it. If
  the source material called an address a routine but none of these did, the entry lists it as a location
  inside the containing function.

## What is not here

- No changes to `config/`, `src/`, `include/` or the build. No names were added to `symbol_addrs.txt`.
- No code, no disassembly listings and no game data. The notes paraphrase what functions do. Short constants
  and small facts are quoted where they are the point, such as a table stride or a tweakable's default. Long
  tables such as name lists, song lists and string tables are summarised with a count and an example.
- Nothing is derived from the port's generated code. The port also runs statically recompiled code, but that
  is a mechanical translation and was not used as a source for any of this.

## Credits

- Function names shown next to addresses come from this project's `config/symbol_addrs.txt`.
- Our understanding of the SSX 3 asset formats that some of the loaders here read comes from GlitcherOG's
  [SSX-Library](https://github.com/GlitcherOG/SSX-Library) (GPL-3.0). This covers world, model, texture,
  archive and audio formats. These notes describe the formats only through what the game's loaders do. No
  SSX-Library code is included.
