#!/bin/bash

# Enumerate subdirs, run build script
for Dir in */ ; do
    echo "Building Image '$Dir'"
    cd "$Dir"
    bash Run.sh
    cd ..
done
