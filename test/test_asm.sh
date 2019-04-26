#!/bin/zsh
make asm
setopt shwordsplit
sources=$(echo champs/**/*.s)
for i in $sources; do
    ./test/asm $i
done;
./asm -r -o output champs/**/*.s
echo "\n--------------------------------------------[ Diff ]--------------------------------------------"
bin=$(echo $sources | sed -e "s/\.s/\.cor/g")
for i in $bin; do
    if [ -f "$i" ]; then
        cmp $i $(echo $i | sed -e "s/champs/output/")
    fi
done
echo "-----------------------------------------------------------------------------------------------"
