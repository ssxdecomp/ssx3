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
byte-for-byte. To check current progress locally:

```bash
$ find asm/nonmatchings -name '*.s' | wc -l   # functions still non-matching
$ grep -c ';\s*//type:func' config/symbol_addrs.txt   # functions identified so far
```

## Contributing

Contributions are welcome. See [CONTRIBUTING.md](CONTRIBUTING.md) for how to
pick a function to match, the matching workflow, and PR expectations.

## License

Original code, build scripts, and tooling in this repository are released
under [CC0](LICENSE) (public domain). This does not extend to the decompiled
game code being reconstructed, or to any game assets, which remain the
property of Electronic Arts and are never included in this repository.
