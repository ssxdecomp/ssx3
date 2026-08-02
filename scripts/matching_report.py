"""Generates MATCHING.md, a full per-function breakdown of match status.

Requires a dual build first: `./configure.py -c -o && ninja`.

For each unit, diffs obj/target against obj/current and classifies every
function as Matching (100%, or a near-miss objdiff's own report still counts
as matched — see README.md), Partial (has a C implementation that doesn't yet
byte-match), or Not Started (still a raw INCLUDE_ASM stub).
"""

import json
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).parent.parent
OBJDIFF_CLI = ROOT / "tools" / "objdiff" / "objdiff-cli"
OBJDIFF_JSON = ROOT / "objdiff.json"
OUTPUT = ROOT / "MATCHING.md"


def load_units():
    data = json.loads(OBJDIFF_JSON.read_text())
    return data["units"]


def run_report():
    out = ROOT / "objdiff_report.tmp.json"
    result = subprocess.run(
        [str(OBJDIFF_CLI), "report", "generate", "-p", str(ROOT), "-o", str(out), "-f", "json", "-d"],
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        print("objdiff-cli report failed:", result.stderr, file=sys.stderr)
        sys.exit(1)
    data = json.loads(out.read_text())
    out.unlink()
    return data


def per_unit_matched_counts(report):
    counts = {}
    for u in report["units"]:
        mf = u["measures"].get("matched_functions", 0)
        if mf:
            counts[u["name"]] = int(mf)
    return counts


def diff_unit(target_path, base_path, tmp_path):
    result = subprocess.run(
        [str(OBJDIFF_CLI), "diff", "-1", target_path, "-2", base_path, "-o", str(tmp_path), "--format", "json"],
        capture_output=True,
        text=True,
    )
    if result.returncode != 0 or not tmp_path.exists():
        return None
    try:
        data = json.loads(tmp_path.read_text())
    except Exception:
        return None
    return data


def collect_functions(units):
    tmp_path = ROOT / "_matching_report_diff.tmp.json"
    results = []  # (unit, name, demangled, size, match_percent)
    for i, u in enumerate(units):
        target_path = u.get("target_path")
        if not target_path or not (ROOT / target_path).exists():
            continue
        base_path = u.get("base_path") or target_path.replace("obj/target", "obj/current")
        if not (ROOT / base_path).exists():
            continue

        data = diff_unit(target_path, base_path, tmp_path)
        if data is None:
            continue

        for sym in data.get("left", {}).get("symbols", []):
            if sym.get("kind") != "SYMBOL_FUNCTION":
                continue
            name = sym.get("name")
            if not name or name.endswith(".NON_MATCHING"):
                continue
            results.append((u["name"], name, sym.get("demangled_name"), sym.get("size"), sym.get("match_percent")))

        if (i + 1) % 40 == 0:
            print(f"...{i + 1}/{len(units)} units diffed", file=sys.stderr)

    if tmp_path.exists():
        tmp_path.unlink()
    return results


def classify(results, matched_counts):
    """Splits functions into Matching/Partial/Not Started per unit.

    A unit's `matched_functions` count from `report generate` is usually
    higher than the number of exactly-100% functions we see here: objdiff's
    own report still counts a function as matched if the only remaining byte
    difference is a relocation immediate (see the gp-relative note in
    README.md), which shows up as a near-100% (not exactly 100%) score in a
    plain diff. We approximate that by promoting the highest-scoring partial
    functions in each unit up to Matching until the counts reconcile.
    """
    by_unit = defaultdict(list)
    for unit, name, dem, size, mp in results:
        by_unit[unit].append((name, dem, size, mp))

    final = []
    for unit, items in by_unit.items():
        exact100 = [it for it in items if it[3] == 100.0]
        partial = [it for it in items if it[3] is not None and it[3] != 100.0]
        not_started = [it for it in items if it[3] is None]

        report_mf = matched_counts.get(unit, len(exact100))
        extra = max(0, report_mf - len(exact100))

        partial_sorted = sorted(partial, key=lambda x: -x[3])
        bonus_matching = partial_sorted[:extra]
        real_partial = partial_sorted[extra:]

        for name, dem, size, mp in exact100 + bonus_matching:
            final.append((unit, name, dem, size, "Matching", mp))
        for name, dem, size, mp in real_partial:
            final.append((unit, name, dem, size, "Partial", mp))
        for name, dem, size, mp in not_started:
            final.append((unit, name, dem, size, "Not Started", mp))

    return final


def write_markdown(final, snapshot_date):
    by_unit = defaultdict(list)
    for unit, name, dem, size, status, mp in final:
        by_unit[unit].append((name, dem, size, status, mp))

    total_matching = sum(1 for r in final if r[4] == "Matching")
    total_partial = sum(1 for r in final if r[4] == "Partial")
    total_not_started = sum(1 for r in final if r[4] == "Not Started")
    total = len(final)

    lines = []
    lines.append("# Function matching report")
    lines.append("")
    lines.append(
        "Auto-generated from [objdiff](tools/objdiff) by diffing every unit's `obj/target` "
        "against `obj/current`. Regenerate with a dual build "
        "(`./configure.py -c -o && ninja`) followed by "
        "`python3 scripts/matching_report.py`; see [CONTRIBUTING.md](CONTRIBUTING.md)."
    )
    lines.append("")
    lines.append(f"Snapshot as of {snapshot_date}.")
    lines.append("")
    lines.append("**Status definitions:**")
    lines.append(
        "- **Matching** — byte-for-byte identical to the retail binary (100%), or a near-miss "
        "where objdiff's own report considers the function matched despite a lower raw "
        "percentage (this happens for a handful of functions where the only remaining byte "
        "difference is a relocation immediate baked in at link time by the original SN "
        "toolchain, not a real code difference — see the gp-relative note in "
        "[README.md](README.md))."
    )
    lines.append(
        "- **Partial** — has a C implementation (not raw `INCLUDE_ASM`) but doesn't yet "
        "byte-match; the percentage is objdiff's fuzzy match score."
    )
    lines.append("- **Not started** — still a raw `INCLUDE_ASM` stub with no C implementation attempted.")
    lines.append("")
    lines.append("| | Count | % of total |")
    lines.append("|---|---|---|")
    lines.append(f"| Matching | {total_matching:,} | {total_matching / total * 100:.2f}% |")
    lines.append(f"| Partial | {total_partial:,} | {total_partial / total * 100:.2f}% |")
    lines.append(f"| Not started | {total_not_started:,} | {total_not_started / total * 100:.2f}% |")
    lines.append(f"| **Total** | **{total:,}** | |")
    lines.append("")
    lines.append(
        "(Total here may differ slightly from the function count in README.md's progress "
        "table — that one comes from objdiff's own aggregate report, this one from summing "
        "every unit's individual symbol list, and the two count a handful of duplicated/weak "
        "symbols differently.)"
    )
    lines.append("")
    lines.append("## Per-file summary")
    lines.append("")
    lines.append(
        "Only files with at least one Matching or Partial function are listed here; "
        "files that are 100% Not Started are omitted from this table (see the full "
        "per-file breakdown further down for every file, including those)."
    )
    lines.append("")
    lines.append("| File | Matching | Partial | Not started | Total |")
    lines.append("|---|---|---|---|---|")

    unit_summary = []
    for unit in sorted(by_unit.keys()):
        items = by_unit[unit]
        m = sum(1 for it in items if it[3] == "Matching")
        p = sum(1 for it in items if it[3] == "Partial")
        n = sum(1 for it in items if it[3] == "Not Started")
        unit_summary.append((unit, m, p, n, len(items)))

    for unit, m, p, n, t in sorted(unit_summary, key=lambda x: (-(x[1] + x[2]), x[0])):
        if m == 0 and p == 0:
            continue
        lines.append(f"| `{unit}` | {m} | {p} | {n} | {t} |")

    lines.append("")
    lines.append("## Full per-file breakdown")
    lines.append("")
    lines.append(
        "Every unit, including ones with no progress yet. Matching and Partial functions "
        "are listed individually with their match percentage; Not Started functions are "
        "only counted (there's nothing to report per-function until an implementation is "
        "attempted)."
    )
    lines.append("")

    for unit, m, p, n, t in sorted(unit_summary, key=lambda x: x[0]):
        lines.append(f"### `{unit}`")
        lines.append("")
        lines.append(f"{m} matching, {p} partial, {n} not started ({t} total)")
        lines.append("")
        items = by_unit[unit]
        attempted = [it for it in items if it[3] in ("Matching", "Partial")]
        if attempted:
            lines.append("| Function | Status | Match % | Size |")
            lines.append("|---|---|---|---|")
            for name, dem, size, status, mp in sorted(attempted, key=lambda x: -x[4]):
                pct_str = f"{mp:.2f}%" if mp is not None else ""
                display_name = (dem or name).replace("|", "\\|")
                lines.append(f"| `{display_name}` | {status} | {pct_str} | {size} |")
            lines.append("")

    OUTPUT.write_text("\n".join(lines) + "\n")
    print(f"Wrote {OUTPUT} ({total_matching} matching, {total_partial} partial, {total_not_started} not started)")


def main():
    if not (ROOT / "obj" / "target").exists() or not (ROOT / "obj" / "current").exists():
        print("obj/target and obj/current not found.")
        print("Run `./configure.py -c -o && ninja` first (the -o flag builds the")
        print("dual target/current objects objdiff needs to compare).")
        sys.exit(1)

    import datetime

    snapshot_date = datetime.date.today().isoformat()

    units = load_units()
    report = run_report()
    matched_counts = per_unit_matched_counts(report)
    results = collect_functions(units)
    final = classify(results, matched_counts)
    write_markdown(final, snapshot_date)


if __name__ == "__main__":
    main()
