#!/bin/zsh

grep -Eo "mul\(( *[0-9]*[0-9]*[0-9] *, *[0-9]*[0-9]*[0-9])\)" input.txt > temp
grep -Eo " *[0-9]*[0-9]*[0-9] *, *[0-9]*[0-9]*[0-9]" temp > part1.input

grep -Eo "mul\(( *[0-9]*[0-9]*[0-9] *, *[0-9]*[0-9]*[0-9])\)|do\(\)|don't\(\)" input.txt > temp
grep -Eo " *[0-9]*[0-9]*[0-9] *, *[0-9]*[0-9]*[0-9]|do\(\)|don't\(\)" temp > part2.input

rm temp
