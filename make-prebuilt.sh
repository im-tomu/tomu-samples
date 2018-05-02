#!/bin/sh
set -e

# make-prebuilt.sh
# Go through all of the project directories and copy the output binaries
# to the prebuilt/ directory.
# Then, call dfu-suffix to append a Device Firmware Upgrade suffix to the
# end of each file so that dfu-util will know which device to look for.

mkdir -p prebuilt
for proj in $(find . -name '*.bin' | cut -d/ -f2 | grep -v prebuilt)
do
	cp $proj/$proj.bin prebuilt/$proj.bin
	cp $proj/$proj.bin prebuilt/$proj.dfu
	cp $proj/$proj.elf prebuilt/$proj.elf
	dfu-suffix -v 1209 -p 70b1 -a prebuilt/$proj.dfu
done
