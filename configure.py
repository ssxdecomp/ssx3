#!/usr/bin/env python3
import argparse
import os
import shutil
import sys
from pathlib import Path
from typing import Dict, List, Set, Union

import ninja_syntax
import splat
import splat.scripts.split as split
from splat.segtypes.linker_entry import LinkerEntry

ROOT = Path(__file__).parent.resolve()
TOOLS_DIR = ROOT / "tools"
OUTDIR = "out"

YAML_FILE = ROOT / "config" / "ssx3_us.yaml"
BASENAME = "SLUS_207.72"
LD_PATH = f"{BASENAME}.ld"
ELF_PATH = f"{OUTDIR}/{BASENAME}"
MAP_PATH = f"{OUTDIR}/{BASENAME}.map"
PRE_ELF_PATH = f"{OUTDIR}/{BASENAME}.elf"

COMMON_INCLUDES = "-Iinclude -isystem include/sdk/ee -isystem include/gcc"


CC_DIR = f"{TOOLS_DIR}/cc/ee-991111-01"
DRIVER_PATH_FLAG = f"-B{CC_DIR}/lib/gcc-lib/ee/2.9-ee-991111-01/"

# See tools/cc/README.md for how these were gathered
COMMON_CFLAGS = "-O2 -fno-edge-lcm -fomit-frame-pointer"
COMMON_CXXFLAGS = ""


COMPILE_C_RULE = f"{CC_DIR}/bin/ee-gcc -c {COMMON_INCLUDES} {DRIVER_PATH_FLAG} {COMMON_CFLAGS} $in"
COMPILE_CXX_RULE = f"{CC_DIR}/bin/ee-gcc -xc++ -c {COMMON_INCLUDES} {DRIVER_PATH_FLAG} {COMMON_CFLAGS} {COMMON_CXXFLAGS} $in"

def clean():
    files_to_clean = [
        ".splache",
        ".ninja_log",
        "build.ninja",
        "permuter_settings.toml",
        LD_PATH
    ]
    for filename in files_to_clean:
        if os.path.exists(filename):
            os.remove(filename)

    shutil.rmtree("asm", ignore_errors=True)
    shutil.rmtree("assets", ignore_errors=True)
    shutil.rmtree("obj", ignore_errors=True)
    shutil.rmtree("out", ignore_errors=True)


def write_permuter_settings():
    with open("permuter_settings.toml", "w", encoding="utf-8") as f:
        f.write(f"""compiler_command = "{COMPILE_CXX_RULE} -D__GNUC__"
assembler_command = "mips-linux-gnu-as -march=r5900 -mabi=eabi -Iinclude"
compiler_type = "gcc"

[preserve_macros]

[decompme.compilers]
"tools/cc/ee-990721/bin/gcc" = "ee-gcc2.9-990721"
"tools/cc/ee-990721/bin/g++" = "ee-gcc2.9-990721"
""")

def build_stuff(linker_entries: List[LinkerEntry], skip_checksum=False):
    built_objects: Set[Path] = set()

    def build(
        object_paths: Union[Path, List[Path]],
        src_paths: List[Path],
        task: str,
        variables: Dict[str, str] = None,
        implicit_outputs: List[str] = None,
    ):
        if variables is None:
            variables = {}

        if implicit_outputs is None:
            implicit_outputs = []

        if not isinstance(object_paths, list):
            object_paths = [object_paths]

        object_strs = [str(obj) for obj in object_paths]

        # Add object paths to built_objects
        for object_path in object_paths:
            if object_path.suffix == ".o":
                built_objects.add(object_path)
            ninja.build(
                outputs=object_strs,
                rule=task,
                inputs=[str(s) for s in src_paths],
                variables=variables,
                implicit_outputs=implicit_outputs,
            )

    ninja = ninja_syntax.Writer(open(str(ROOT / "build.ninja"), "w", encoding="utf-8"), width=9999)

    cross = "mips-linux-gnu-"

    ld_args = "-EL -T config/undefined_syms_auto.txt -T config/undefined_funcs_auto.txt -Map $mapfile -T $in -o $out"

    ninja.rule(
        "as",
        description="as $in",
        command=f"cpp {COMMON_INCLUDES} $in -o  - | {cross}as -no-pad-sections -EL -march=5900 -mabi=eabi -Iinclude -o $out",
    )

    ninja.rule(
        "cc",
        description="cc $in",
        command=f"{COMPILE_C_RULE} -o $out && {cross}strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "cxx",
        description="cxx $in",
        command=f"{COMPILE_CXX_RULE} -o $out && {cross}strip $out -N dummy-symbol-name",
    )

    ninja.rule(
        "ld",
        description="link $out",
        command=f"{cross}ld {ld_args}",
    )

    ninja.rule(
        "sha1sum",
        description="sha1sum $in",
        command="sha1sum -c $in && touch $out",
    )

    ninja.rule(
        "elf",
        description="elf $out",
        command=f"{cross}objcopy $in $out -O binary",
    )

    # Add recipes for everything
    for entry in linker_entries:
        seg = entry.segment

        if seg.type[0] == ".":
            continue

        if entry.object_path is None:
            continue

        if isinstance(seg, splat.segtypes.common.asm.CommonSegAsm) or isinstance(
            seg, splat.segtypes.common.data.CommonSegData
        ):
            build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.c.CommonSegC):
            build(entry.object_path, entry.src_paths, "cc")
        elif isinstance(seg, splat.segtypes.common.cpp.CommonSegCpp):
            build(entry.object_path, entry.src_paths, "cxx")
        elif isinstance(seg, splat.segtypes.common.databin.CommonSegDatabin):
            build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.rodatabin.CommonSegRodatabin):
            build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.textbin.CommonSegTextbin):
            build(entry.object_path, entry.src_paths, "as")
        elif isinstance(seg, splat.segtypes.common.bin.CommonSegBin):
            build(entry.object_path, entry.src_paths, "as")
        else:
            print(f"ERROR: Unsupported build segment type {seg.type}")
            sys.exit(1)

    ninja.build(
        PRE_ELF_PATH,
        "ld",
        LD_PATH,
        implicit=[str(obj) for obj in built_objects],
        variables={"mapfile": MAP_PATH},
    )

    ninja.build(
        ELF_PATH,
        "elf",
        PRE_ELF_PATH,
    )

    # FIXME: Do this in a more elegant way;
    # probably a python script which reads the splat yaml to get the SHA1,
    # rather than needing a seperate sha1 file.
    # My obession with DRY will never stop >:3
    if not skip_checksum:
        ninja.build(
            ELF_PATH + ".ok",
            "sha1sum",
            "config/checksum.sha1",
            implicit=[ELF_PATH],
        )
    else:
        print("Not adding sha1 rule")

def main():
    parser = argparse.ArgumentParser(description="Configure the project")
    parser.add_argument(
        "-c",
        "--clean",
        help="Clean artifacts and build",
        action="store_true",
    )
    parser.add_argument(
        "-C",
        "--only-clean",
        help="Only clean artifacts",
        action="store_true",
    )
    parser.add_argument(
        "-s",
        "--skip-checksum",
        help="Skip the checksum step",
        action="store_true",
    )
    args = parser.parse_args()

    do_clean = (args.clean or args.only_clean) or False

    # FIXME: Set skip_checksum to False once builds are able
    # to match; it has been temporairly enabled here.
    do_skip_checksum = args.skip_checksum or True

    if do_clean:
        clean()
        if args.only_clean:
            return

    split.main([YAML_FILE], modes="all", verbose=False)

    linker_entries = split.linker_writer.entries

    build_stuff(linker_entries, do_skip_checksum)

    write_permuter_settings()

if __name__ == "__main__":
    main()