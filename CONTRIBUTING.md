# Contributing

Thanks for your interest in helping decompile SSX 3. This document covers how
to find work, match a function, name symbols, and submit a pull request.

Before anything else, follow the [Setup](README.md#setup) steps in the
README and confirm `ninja` builds successfully against your own NTSC-U disc
image.

## Ground rules

- **Never commit game assets, disc contents, or the EE GCC toolchain.**
  `disc/`, `assets/`, and `tools/cc/eegcc-2.95.3-V1.36` are gitignored for a
  reason — this project must only ever contain original code that
  contributors have written, not copyrighted material extracted from the
  game.
- **Match, don't rewrite.** The goal is byte-for-byte identical compiled
  output. Prefer restructuring your C/C++ to match the original compiler
  output over changing behavior. Style should follow whatever convention
  the surrounding file already uses, even if it looks dated — this is a
  reconstruction of 2003-era code, not a modernization.
- **Small, focused PRs.** One file or one small group of related functions
  per PR is much easier to review than a large batch.

## Finding a function to match

Non-matching functions live under `asm/nonmatchings/<file>/<symbol>.s`.
Functions named `func_00XXXXXX` are matched but not yet identified/renamed;
functions with a readable name are identified but still asm-only. Either is
fair game — pick whichever you're more interested in.

Loose, unassigned code (not yet attributed to any source file at all) lives
as top-level files directly under `asm/` (e.g. `asm/218AE8.s`). Splitting one
of these into the correct file in `config/ssx3_us.yaml` is also useful work
even before it's fully matched.

## Matching workflow

1. Open the corresponding `.s` file under `asm/nonmatchings/` to see the
   target MIPS assembly.
2. Write or edit the matching C/C++ in `src/`, following the file layout in
   `src/readme.md` (a list of known source file names recovered from
   prototype builds — some files in that list won't exist in the final
   retail build, and some retail files are missing from it).
3. Build with `ninja` and compare your output against the target using
   [objdiff](tools/objdiff) (`tools/objdiff/objdiff-cli`, or the GUI build for
   your platform) to check for a byte-perfect match.
4. If you're stuck, paste the target asm and a first-pass decompilation into
   [decomp.me](https://decomp.me) or run it through the
   [permuter](https://github.com/simonlindholm/decomp-permuter) locally
   (`permuter_settings.toml` at the repo root configures it — this file is
   gitignored since settings are per-machine).
5. Functions that don't split cleanly into a single file, or that you
   haven't sorted into the right file yet, can go in `src/uncollated/` in the
   meantime (see `src/uncollated/readme.md`).

## Naming symbols

Known function and symbol names live in `config/symbol_addrs.txt`. The file
has two parts: hand-maintained entries above the `// Spreadsheet Auto
Generation` marker, and a larger auto-generated block below it, produced by
`scripts/spreadsheet.py` from a shared spreadsheet of recovered names.

If you identify a function's real name (from debug strings, RTTI, prototype
symbols, etc.) and don't have access to the shared spreadsheet, just add or
correct the entry directly in `config/symbol_addrs.txt` and explain the
source of the name in your PR description — a manual edit there is just as
valid as a spreadsheet sync.

## Submitting a PR

- Make sure `ninja` still builds cleanly.
- Run objdiff on any function you touched and mention the match result
  (matched / still non-matching but closer / etc.) in the PR description.
- Keep unrelated formatting or reordering out of the diff — it makes the
  actual change harder to review.
- If you're renaming or re-identifying symbols, note where the name came
  from.

## Questions

If something here is unclear or you're unsure where a piece of code
belongs, open an issue or start a discussion before sinking a lot of time
into it — it's much easier to redirect early.
