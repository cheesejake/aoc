#!/bin/sh

sed -e 's/^\(.*\)$/s" \1"/' <.input.txt >.string-input.txt

# I decided to leave the file unsorted
