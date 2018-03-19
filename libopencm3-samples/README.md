# libopencm3

[libopencm3](http://libopencm3.org/) is an Open-Source lowlevel hardware
library for ARM Cortex-M3 microcontrollers (but also M0, M4 are supported and
more to come).

Upstream libopencm3 now supports the EFM32HG. The examples located here
were modified to support the EFM32HG and tested on the Tomu with a linux host:

 * A USB-Serial CDCACM device example (`usb_cdcacm`)
 * A USB HID mouse emulation example (`usb_hid`)
 * A USB Mass Storage Device example (`usb_msc`)
 * A USB MIDI example (`usb_midi`)
 * A raw endpoint example with a sample python program that controls an LED

# Building

Typing `make` will compile these examples for you.

# Bootloader assumptions

These examples are compatible with the non-DFU serial AN0042 bootloader.  They will run in legacy mode with a DFU-enabled bootloader, such as the one shipped on v0.4 boards.  They run from flash offset 0x4000, and do not auto-boot.  To get back into the bootloader, reset the board (e.g. by unplugging it and plugging it back in).

If you have a DFU-enabled bootloader, upload programs using `dfu-util`.  For example, to upload miniblink, run:

````dfu-util -d 1209:70b1 -D ./usb_hid/usb_hid.bin````

If you're using the serial bootloader, upload the binary using XMODEM.

# License

The libopencm3 code & examples are released under the terms of the GNU Lesser
General Public License (LGPL), version 3 or later.

See COPYING.GPL3 and COPYING.LGPL3 for details.