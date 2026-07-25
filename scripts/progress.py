import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
OBJDIFF_CLI = ROOT / "tools" / "objdiff" / "objdiff-cli"


def generate_report():
    if not (ROOT / "obj" / "target").exists() or not (ROOT / "obj" / "current").exists():
        print("obj/target and obj/current not found.")
        print("Run `./configure.py -c -o && ninja` first (the -o flag builds the")
        print("dual target/current objects objdiff needs to compare).")
        sys.exit(1)

    report_path = ROOT / "objdiff_report.tmp.json"
    result = subprocess.run(
        [str(OBJDIFF_CLI), "report", "generate", "-p", str(ROOT), "-o", str(report_path), "-f", "json"],
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        print("objdiff-cli failed:")
        print(result.stdout)
        print(result.stderr)
        sys.exit(1)

    data = json.loads(report_path.read_text())
    report_path.unlink()
    return data


def main():
    data = generate_report()
    m = data["measures"]

    total_functions = int(m.get("total_functions", 0))
    matched_functions = int(m.get("matched_functions", 0))
    total_code = int(m.get("total_code", 0))
    matched_code = int(m.get("matched_code", 0))
    total_data = int(m.get("total_data", 0))
    matched_data = int(m.get("matched_data", 0))

    func_pct = m.get("matched_functions_percent", 0.0)
    code_pct = m.get("matched_code_percent", 0.0)
    data_pct = m.get("matched_data_percent", 0.0)

    print(f"Functions matching:  {matched_functions} / {total_functions}  ({func_pct:.2f}%)")
    print(f"Code bytes matching: {matched_code} / {total_code}  ({code_pct:.2f}%)")
    print(f"Data bytes matching: {matched_data} / {total_data}  ({data_pct:.2f}%)")

    return {
        "total_functions": total_functions,
        "matched_functions": matched_functions,
        "func_pct": func_pct,
        "total_code": total_code,
        "matched_code": matched_code,
        "code_pct": code_pct,
        "total_data": total_data,
        "matched_data": matched_data,
        "data_pct": data_pct,
    }


if __name__ == "__main__":
    main()
