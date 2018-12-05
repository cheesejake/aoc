#!/bin/sh

sed -E -e 's/^\[(.*)-(.*)-(.*) (.*):(.*)\] (.*)$/\1 \2 \3 \4 \5 \6/' <input.txt >input2.txt
sed -E -e 's/^(.*) Guard \#([0123456789]*) begins shift$/\1 \2 1 2/' <input2.txt >input3.txt
sed -E -e 's/^(.*) wakes up$/\1 1 1/' <input3.txt >input4.txt
sed -E -e 's/^(.*) falls asleep$/\1 0 1/' <input4.txt >justnumbers-input.txt

# I decided to leave the file unsorted
