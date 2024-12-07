set -e
./iso.sh
qemu-system-i386 -drive file=out/testos.iso,format=raw,index=0,media=disk -serial stdio -m 1G
# qemu-system-i386 -kernel out/krnl.bin -serial stdio