#!/bin/bash

# Enter Artifact/Binary Dir
echo "[ERS BUILD SYSTEM] - Entering Build Directory"
cd ..
cd Build


# Depending On Platform, Run
echo "[ERS BUILD SYSTEM] - Running Tests"
ctest