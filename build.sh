#!/bin/bash
set -e


export PREFIX="$HOME/opt/cross/bin/"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

if [ -e build ]; then
    rm -rf build;
fi

TB=""

FILES="
boot.s
g.hpp
include
include/multiboot.h
include/serial.h
include/colors.h
include/string.h
include/font.h
logger.hpp
logger.cpp
video.hpp
video.cpp
terminal.hpp
terminal.cpp
errors.hpp
errors.cpp
mem.hpp
mem.cpp
kernel.cpp
"


mkdir build
function recBuild {
    cd build
    echo $FILES
    for i in $FILES; do
        echo Compiling: $i
        if [[ -d ../src/$i ]]; then
            mkdir $i
        else
            cp ../src/$i $i
            O=$( echo -n $i | wc -c )
            N=$(expr $O - 3)
            if [[ ${i:$N:${#i}} == ".go" ]]; then
                $PREFIX$TARGET-gccgo -static -Werror -nostdlib -nostartfiles -nodefaultlibs -c $i -o $i.o
                $PREFIX$TARGET-objcopy -j .go_export $i.o "$i"x
                TB="$TB build/$i.o"

            fi
            N=$(expr $O - 4)
            if [[ ${i:$N:${#i}} == ".cpp" ]]; then
                $PREFIX$TARGET-g++ -L ../src/ -c $i -o $i.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
                TB="$TB build/$i.o"
            fi
            N=$(expr $O - 2)
            if [[ ${i:$N:${#i}} == ".s" ]]; then
                $PREFIX$TARGET-as $i -o $i.o
                TB="$TB build/$i.o"
            fi
        fi
    done
    cd ..
}

recBuild
if [ ! -d out ]; then
    if [ -e out ]; then rm -f out; fi
    mkdir out
fi;
$PREFIX$TARGET-gcc -T src/linker.ld -o out/krnl.bin -ffreestanding -O2 -nostdlib $TB -lgcc
rm -rf build