# SSX 3 (2003)

This is a work-in-progress decompilation of SSX 3 (2003) for the PlayStation 2. This project builds the NTSC-U version of the game (`SLUS_207.72`, sha1 `77114dfd1205eaccf1ccc18c5f9650097fa78bd8`). Other regions and versions may be considered once NTSC-U has been completed and matched.

The main goal of this project is to decompile the game code to matching source code. This project doesn't contain any game assets or original code from the game's executable. It requires your own copy of the game to build and run this project.

## Setup

You will need:

- a Linux system that can run 32 bit applications. WSL2 should work as well.
- a copy of binutils for the `mips-linux-gnu` target
- A NTSC-U disc image (obtained legally)

### Setup on Windows from Scratch (Ubuntu WSL2)

1. Install Ubuntu WSL2.
2. Open a Ubuntu WSL terminal and `cd` into a path inside the Linux filesystem (not `/mnt/c/...`), e.g. `cd ~`.
3. Clone the repo:
   ```bash
   git clone https://github.com/ssxdecomp/ssx3
   cd ssx3
   ```
4. Install dependencies:
   ```bash
   sudo dpkg --add-architecture i386
   sudo apt-get update
   sudo apt install -y binutils-mips-linux-gnu ninja-build wine python3.12-venv cpp
   ```
5. Run the setup script:
   ```bash
   chmod +x ./scripts/setup.sh
   ./scripts/setup.sh
   ```
6. Place the game files into the newly made `disc` directory.
7. Set up the Python virtual environment:
   ```bash
   python3 -m venv venv
   . venv/bin/activate
   pip install -r requirements.txt
   ```
8. Run the first build:
   ```bash
   python3 configure.py -o -c
   ninja
   ```

#### Rebuilding after closing and reopening WSL

Once set up, you don't need to repeat the steps above. Just:

```bash
cd ssx3
. venv/bin/activate
python3 configure.py -o -c
ninja
```

### Debian/Ubuntu

Install required packages:

```bash
sudo apt install -y binutils-mips-linux-gnu ninja-build wine
```

Download required tools:

```bash
./scripts/setup.sh
```

Make a `disc` directory in the root of this repository, and copy the files from the NTSC-U game disc into it.

Set up a venv for splat:

```bash
python -m venv venv
. venv/bin/activate
pip install -r requirements.txt
```

`./configure.py` ultimately does the setup.

#### Building

```bash
ninja
```
