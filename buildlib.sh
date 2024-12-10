#!/bin/zsh

make clean -C lib

printf "---------------------------------------------------\n"
bear --output lib/compile_commands.json -- make -C lib

