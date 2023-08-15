#!/bin/bash

clean () {
(
	cd src
	make clean
)
}

# Pre-Clean
#clean

# Build
./cross-compile.sh

[ -f src/kernel.bin ] || {
	echo "Build Failed!"
	exit 1
}

# Publish kernel bin
cp src/kernel.bin iso/kernel/kernel.bin

# Clean
clean
./clean.sh

# Make iso
rm -f os.iso
mkisofs -R -input-charset utf8 -b boot/grub/stage2_eltorito -boot-info-table -no-emul-boot -boot-load-size 4 -o os.iso iso

[ -f os.iso ] && {
	echo "Build complete"
}
