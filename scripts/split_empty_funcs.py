#!/usr/bin/env python3
"""Split empty `jr $ra; nop` functions out of the unnamed asm segments into
src/_Unknown/<func>.cpp, one cpp subsegment per function, and register each
auto-named one in config/symbol_addrs.txt as its C++ name func_X__Fv.

Run from the repo root, then:  python3 configure.py -o -c && ninja
"""
import argparse
import difflib
import os
import re
import sys

YAML = "config/ssx3_us.yaml"
SYMBOLS = "config/symbol_addrs.txt"
VRAM_OFFSET = 0xFF000  # main segment: vram 0x100000 at rom 0x1000
FUNC_AUTO = re.compile(r"^func_[0-9A-F]{8}$")
ASM_DIR = "asm"
SRC_DIR = "src"
UNKNOWN = "_Unknown"
COMMENT = "# needs to be sorted"

SEG_LINE = re.compile(r"^(\s*)- \[(0x[0-9A-Fa-f]+),\s*([A-Za-z0-9_]+)(?:,\s*([^\]]+))?\]")
FUNC_HDR = re.compile(r"^nonmatching\s+(\S+),\s*(0x[0-9A-Fa-f]+)")
INSN = re.compile(r"^\s*/\*\s*([0-9A-F]+)\s+[0-9A-F]{8}\s+[0-9A-F]{8}\s*\*/\s+(\S+)\s*(.*)$")


def read_subsegments(lines):
    """Return [(line_index, indent, offset, type, name)] for the main code segment."""
    out = []
    for i, line in enumerate(lines):
        m = SEG_LINE.match(line)
        if m:
            out.append((i, m.group(1), int(m.group(2), 16), m.group(3), m.group(4)))
    return out


def parse_functions(path):
    """Return [(name, rom_offset, size, insns)] in file order."""
    funcs = []
    cur = None
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = FUNC_HDR.match(line)
            if m:
                cur = [m.group(1), None, int(m.group(2), 16), []]
                funcs.append(cur)
                continue
            m = INSN.match(line)
            if m and cur is not None:
                if cur[1] is None:
                    cur[1] = int(m.group(1), 16)
                cur[3].append((m.group(2), m.group(3).strip()))
    return [tuple(f) for f in funcs if f[1] is not None]


def is_empty(size, insns):
    if size < 8 or len(insns) < 2:
        return False
    if insns[0][0] != "jr" or insns[0][1] not in ("$ra", "$31"):
        return False
    return all(mn == "nop" for mn, _ in insns[1:])


def plan_segment(start, end, funcs, budget):
    """Return (entries, picked) where entries is [(offset, type, name)] covering [start, end)."""
    entries = {start: ("asm", None)}
    picked = []
    for idx, (name, off, size, insns) in enumerate(funcs):
        if budget is not None and len(picked) >= budget:
            break
        if not is_empty(size, insns):
            continue
        entries[off] = ("cpp", f"{UNKNOWN}/{name}")
        picked.append((name, off))
        nxt = funcs[idx + 1][1] if idx + 1 < len(funcs) else end
        if nxt < end and nxt not in entries:
            entries[nxt] = ("asm", None)
    # An asm entry immediately overwritten by a later cpp at the same offset is handled by the dict;
    # a following empty func at `nxt` replaces the asm placeholder when it is processed.
    return sorted((o, t, n) for o, (t, n) in entries.items()), picked


def symbol_for(name):
    """C++ symbol for `void name()`; auto-named funcs get the GCC 2.x mangling `__Fv`."""
    if FUNC_AUTO.match(name):
        return name + "__Fv"
    return name


def add_symbols(picked, dry_run):
    """Append `func_X__Fv = 0xVRAM; //type:func` for each auto-named func not already listed."""
    with open(SYMBOLS, "rb") as fh:
        raw = fh.read().decode("utf-8")
    nl = "\r\n" if "\r\n" in raw else "\n"
    known = {int(m.group(1), 16) for m in re.finditer(r"=\s*(0x[0-9A-Fa-f]+)", raw)}
    new = [f"{symbol_for(n)} = 0x{off + VRAM_OFFSET:08X}; //type:func"
           for n, off in picked if FUNC_AUTO.match(n) and off + VRAM_OFFSET not in known]
    if new and not dry_run:
        sep = "" if raw.endswith(nl) or not raw else nl
        with open(SYMBOLS, "wb") as fh:
            fh.write((raw + sep + nl + f"// {UNKNOWN} empty functions {COMMENT}" + nl + nl.join(new) + nl).encode("utf-8"))
    return new


def write_cpp(name, dry_run):
    path = os.path.join(SRC_DIR, UNKNOWN, f"{name}.cpp")
    if os.path.exists(path):
        return False
    body = (
        '#include "common.h"\n'
        "\n"
        f'INCLUDE_ASM("{UNKNOWN}/{name}", {symbol_for(name)});\n'
        "#ifdef SKIP_ASM\n"
        f"void {name}() {{}}\n"
        "#endif\n"
    )
    if not dry_run:
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "w", encoding="utf-8", newline="\n") as fh:
            fh.write(body)
    return True


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--limit", type=int, help="only split the first N empty functions (by address)")
    ap.add_argument("--dry-run", action="store_true", help="print the yaml diff and file list, write nothing")
    args = ap.parse_args()

    if not os.path.exists(YAML):
        sys.exit(f"{YAML} not found - run this from the repo root")

    with open(YAML, encoding="utf-8") as fh:
        lines = fh.read().split("\n")

    subs = read_subsegments(lines)
    replacements = {}
    all_picked = []
    budget = args.limit

    for k, (li, indent, off, typ, name) in enumerate(subs):
        if typ != "asm" or name is not None:
            continue
        end = subs[k + 1][2] if k + 1 < len(subs) else None
        if end is None:
            continue
        asm_path = os.path.join(ASM_DIR, f"{off:X}.s")
        if not os.path.exists(asm_path):
            sys.exit(f"missing {asm_path} - run configure.py once so splat has split the asm")

        remaining = None if budget is None else budget - len(all_picked)
        if remaining is not None and remaining <= 0:
            break
        entries, picked = plan_segment(off, end, parse_functions(asm_path), remaining)
        if not picked:
            continue
        all_picked += picked

        new = []
        for i, (o, t, n) in enumerate(entries):
            if o == off and t == "asm":
                new.append(lines[li])  # keep the original line exactly as written
            elif t == "cpp":
                new.append(f"{indent}- [0x{o:x}, cpp, {n}]  {COMMENT}")
            else:
                new.append(f"{indent}- [0x{o:x}, asm]")
        replacements[li] = new

    if not all_picked:
        print("No empty functions found in unnamed asm segments.")
        return

    out = []
    for i, line in enumerate(lines):
        out.extend(replacements.get(i, [line]))

    created = [n for n, _ in all_picked if write_cpp(n, args.dry_run)]
    symbols = add_symbols(all_picked, args.dry_run)
    named = [n for n, _ in all_picked if not FUNC_AUTO.match(n)]

    if args.dry_run:
        sys.stdout.writelines(difflib.unified_diff(
            [l + "\n" for l in lines], [l + "\n" for l in out], YAML, YAML + " (new)"))
        print(f"\n[dry run] {SYMBOLS} would get:")
        print("\n".join("  " + s for s in symbols))
    else:
        with open(YAML, "w", encoding="utf-8", newline="\n") as fh:
            fh.write("\n".join(out))

    verb = "[dry run] would split" if args.dry_run else "Split"
    print(f"\n{verb} {len(all_picked)} functions: {len(created)} files in {SRC_DIR}/{UNKNOWN}/, "
          f"{len(symbols)} symbols added to {SYMBOLS}")
    if named:
        print("Already named, so not renamed - give these their mangled names by hand:")
        print("\n".join("  " + n for n in named))
    if not args.dry_run:
        print("Next: python3 configure.py -o -c && ninja")


if __name__ == "__main__":
    main()
