#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
from collections import Counter
from pathlib import Path


def classify_stem(stem: str) -> str:
    if stem.startswith("ERS_"):
        return "conforming"
    if stem.startswith("GUI_"):
        return "legacy_gui"
    if stem.startswith("PyBind11"):
        return "legacy_pybind"
    return "plain_name"


def nearest_named_parent(path: Path, root: Path) -> str | None:
    for parent in path.parents:
        if parent == root:
            break
        if parent.name.startswith(("ERS_", "GUI_")):
            return parent.name
    return None


def scan_cpp_files(root: Path) -> dict:
    files = sorted(
        path for path in root.rglob("*")
        if path.is_file() and path.suffix.lower() in {".cpp", ".h", ".hpp", ".cxx", ".cc"}
    )

    offenders = []
    top_dirs = Counter()
    families = Counter()
    for file_path in files:
        family = classify_stem(file_path.stem)
        families[family] += 1
        if family == "conforming":
            continue

        relative_path = file_path.relative_to(root.parent)
        top_dirs[str(relative_path.parent)] += 1
        offenders.append(
            {
                "path": str(relative_path),
                "family": family,
                "nearest_named_parent": nearest_named_parent(file_path.parent, root),
            }
        )

    return {
        "root": str(root),
        "total_cpp_files": len(files),
        "conforming_cpp_files": families["conforming"],
        "nonconforming_cpp_files": len(offenders),
        "family_counts": dict(families),
        "top_offender_directories": top_dirs.most_common(25),
        "offenders": offenders,
    }


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Audit BrainGenix-ERS C++ filenames against the CONTRIBUTING.md ERS_* filename rule."
    )
    parser.add_argument(
        "--source-root",
        default=Path(__file__).resolve().parents[1] / "Source",
        type=Path,
        help="Source tree root to scan.",
    )
    parser.add_argument(
        "--write-json",
        type=Path,
        help="Optional path to write the JSON audit report to.",
    )
    parser.add_argument(
        "--show-offenders",
        type=int,
        default=50,
        help="How many offender entries to include in the stdout summary.",
    )
    args = parser.parse_args()

    report = scan_cpp_files(args.source_root.resolve())
    if args.write_json:
        args.write_json.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")

    summary = {
        "root": report["root"],
        "total_cpp_files": report["total_cpp_files"],
        "conforming_cpp_files": report["conforming_cpp_files"],
        "nonconforming_cpp_files": report["nonconforming_cpp_files"],
        "family_counts": report["family_counts"],
        "top_offender_directories": report["top_offender_directories"],
        "sample_offenders": report["offenders"][: args.show_offenders],
    }
    print(json.dumps(summary, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
