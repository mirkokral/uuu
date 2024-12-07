x86_64-elf-as test1.asm -64 -o bl.o
ld -Ttext 200000 --oformat binary -o bl.iso bl.o