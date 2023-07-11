#!/bin/bash

echo "Entering Diagrams Directory"
cd ../../Docs/Diagrams

echo "Generating Images From Diagrams"
for i in *.drawio; do
    [ -f "$i" ] || break
    echo "    - Generating Images For File $i"
    echo "        - Generating png" 
    drawio -x -f png --scale 2.5 -o $i.png $i
    echo "        - Generating svg"
    drawio -x -f png --scale 2.5 -o $i.svg $i
done
