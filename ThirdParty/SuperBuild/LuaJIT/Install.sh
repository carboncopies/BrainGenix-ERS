#!/usr/bin/env bash

echo "Installing LuaJIT Library To $1"
make DESTDIR=$1 install
echo "Done Installing LuaJIT Library"
