# SSX 3 (2003)

This is a work-in-progress decompilation of SSX 3 (2003) for the PlayStation 2. This project builds the NTSC-U version of the game (`SLUS_207.72`, sha1 `77114dfd1205eaccf1ccc18c5f9650097fa78bd8`). Other regions and versions may be considered once NTSC-U has been completed and matched.

The main goal of this project is to decompile the game code to matching source code. This project doesn't contain any game assets or original code from the game's executable. It requires your own copy of the game to build and run this project.

## Setup

You will need:

- a Linux system that can run 32 bit applications. WSL2 should work as well.
- a copy of binutils for the `mips-linux-gnu` target
- A NTSC-U disc image (obtained legally)

### Debian/Ubuntu

`# apt install -y binutils-mips-linux-gnu ninja-build wine`  

Download required tools:  

```bash  
# ./scripts/setup.sh
```

Make a `disc` directory in the root of this repository, and copy the files from the NTSC-U game disc.

Setup a venv for splat:

```bash
$ python -m venv venv  
$ . venv/bin/activate  
(venv) $ pip install -r requirements.txt  
```

`./configure.py` ultimately does the setup.

## Building

`ninja` should do the trick.

## Progress

Non-matching functions live under `asm/nonmatchings/`; anything not in that
directory has already been decompiled and matches the original binary
byte-for-byte. Progress is tracked with [objdiff](tools/objdiff), which
compares the real game bytes (`obj/target`) against what our source
currently compiles to (`obj/current`) function-by-function — this is the
same tool used interactively while matching (see
[CONTRIBUTING.md](CONTRIBUTING.md)).

To check current progress locally:

```bash
$ ./configure.py -c -o && ninja   # -o builds obj/target and obj/current
$ python3 scripts/progress.py
```

The first step is a full dual build (everything compiles twice, once as
reference bytes and once from our current source) so it's slower than a
normal `ninja` build; only rerun it when you want a fresh number.

Snapshot as of 2026-08-02:

| | matching | partial | total | % matching |
|---|---|---|---|---|
| Functions | 1,159 | 105 | 12,930 | 8.96% |
| Code bytes | 18,876 | — | 3,195,184 | 0.59% |
| Data bytes | 1,368 | — | 500,792 | 0.27% |

"Partial" functions have a real C implementation (not a raw `INCLUDE_ASM`
stub) that compiles but doesn't yet byte-match — see the `//XX%` comment
above each one for its objdiff score. A full per-function breakdown,
including every partial and matching function by file, is in
[MATCHING.md](MATCHING.md).

The function/code counts include every function that's been split into its
own file, named or not (via `config/gap_symbol_addrs.txt` — see that file's
header for why some splits don't have a recovered name yet). It does not
include code still sitting in the large, not-yet-split `asm/` catch-all
files, so the true total will grow as more of those get split out and
identified.

## Contributing

Contributions are welcome. See [CONTRIBUTING.md](CONTRIBUTING.md) for how to
pick a function to match, the matching workflow, and PR expectations.

## AI use

Use of AI tools (Claude, ChatGPT, Copilot, decomp.me's assistants, etc.) to
help write or reverse-engineer matches is welcome, including for whole PRs.
This project's correctness standard doesn't depend on who or what wrote a
match: [objdiff](tools/objdiff) either reports a byte-perfect match against
the real game binary or it doesn't. AI-assisted PRs are held to the same bar
as any other — a green objdiff diff, not a claim of one — and normal review
still applies (does the struct layout make sense, is naming reasonable,
etc.). There's no need to disclose AI involvement, but please don't submit
unverified output you haven't actually built and diffed yourself.

## License

Original code, build scripts, and tooling in this repository are released
under [CC0](LICENSE) (public domain). This does not extend to the decompiled
game code being reconstructed, or to any game assets, which remain the
property of Electronic Arts and are never included in this repository.
