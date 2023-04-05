#!/bin/bash

# Enumerate subdirs, run build script
for Dir in */ ; do
    echo "Building Image '$d'"
    cd "$d"
    bash Run.sh
    cd ..
done
