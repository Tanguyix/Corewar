#!/bin/zsh
make
./asm champs/our_champs/Forking.s -o output
./corewar -v output/Forking.cor output/Forking.cor output/Forking.cor output/Forking.cor output/Forking.cor output/Forking.cor
