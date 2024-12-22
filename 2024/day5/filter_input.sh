#!/bin/zsh

grep -E "\|" raw.txt > rules.txt
grep -E "," raw.txt > data.txt

