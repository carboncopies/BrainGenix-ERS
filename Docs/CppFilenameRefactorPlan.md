<!-- markdownlint-disable MD013 MD043 -->

# C++ Filename Refactor Plan

This note turns issue `BrainGenix-ERS#464` into a reviewable first pass.

## Rule In The Current Contribution Guide

`CONTRIBUTING.md` currently says C++ filenames should use an `ERS_[CLASS/STRUCT/FUNCTION]_` prefix to indicate what the file contains.

## Current Snapshot

Static scan snapshot from 2026-04-22 over `Source/`:

- total C++ files scanned: `321`
- files already starting with `ERS_`: `2`
- files not matching the literal `ERS_` filename rule: `319`

Largest offender directories from that scan:

1. `Source/Core/Renderer/ERS_CLASS_VisualRenderer`: `38`
2. `Source/Core/Editor/Windows/GUI_Window_SceneTree`: `34`
3. `Source/Core/Loader/ERS_ModelLoader`: `18`
4. `Source/Core/Loader/ERS_SceneLoader`: `18`
5. `Source/Core/Script/ERS_CLASS_PythonInterpreterIntegration`: `14`

The drift is not one single pattern. The current tree mixes several naming families:

- `GUI_*` filenames in editor code
- plain domain names inside already-prefixed directories, for example `ERS_STRUCT_Scene/Scene.cpp`
- `PyBind11*` filenames in the Python integration area

## Why This Needs To Be Phased

A blind repo-wide rename would touch:

- `#include` lines
- per-directory `CMakeLists.txt` file lists
- IDE/bookmark expectations
- downstream scripts and documentation

That makes a single all-at-once rename too risky for a first reviewable patch.

## First-Pass Work Added In This Patch

- `Tools/AuditCppFileNames.py` scans `Source/`, classifies nonconforming files, and reports the largest offender directories
- the script can also write a full JSON report for later mechanical rename work

Example usage:

```bash
python3 Tools/AuditCppFileNames.py
python3 Tools/AuditCppFileNames.py --write-json Docs/cpp_filename_audit.json --show-offenders 200
```

## Proposed Migration Order

1. Rename files in directories that already encode the target name in the directory itself.
   Example: `Source/Core/Structures/ERS_STRUCT_Scene/Scene.cpp` -> `ERS_STRUCT_Scene.cpp`
2. Rename low-fanout internal helpers next.
   Example: small `Source/Internal/*` libraries with limited include surfaces.
3. Decide how legacy editor `GUI_*` families should map to the contribution rule before touching them.
   The repo needs a clear answer on whether these stay `GUI_*` or become `ERS_*`.
4. Rename high-fanout renderer and scene-tree helper files after the convention decision is settled.

## Explicit Non-Goals For This Patch

- no mass rename yet
- no include-path churn yet
- no CMake file-list rewrite yet

This patch is only meant to make the filename refactor mechanical and reviewable.
