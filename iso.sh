set -e
./build.sh

if [ ! -d out ]; then
    if [ -e out ]; then rm -f out; fi
    mkdir out
fi;
mkdir -p isodir/boot/grub
cp out/krnl.bin isodir/boot/krnl.bin
echo -e "menuentry \"testos\" {\nmultiboot /boot/krnl.bin hi\n}" >> isodir/boot/grub/grub.cfg
grub-mkrescue -o out/testos.iso isodir
rm -rf isodir