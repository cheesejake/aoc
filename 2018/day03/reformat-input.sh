#!/bin/sh

sed -e 's/^#\(.*\) @ \(.*\),\(.*\): \(.*\)x\(.*\)$/\1 \2 \3 \4 \5/' <.input.txt >.justnumbers-input.txt
