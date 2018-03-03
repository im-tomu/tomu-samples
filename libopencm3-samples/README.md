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

These examples are built for the vanilla (non-DFU, AN0042) bootloader present
on board revision 0.3.

For different bootloaders, modify the linker script and SCB\_VTOR assignment
as required.

Use:
    arm-none-eabi-objcopy -O binary <infile>.elf <outfile>.bin

To create a raw binary that is transferable to the Tomu board using XMODEM.

# License

The libopencm3 code & examples are released under the terms of the GNU Lesser
General Public License (LGPL), version 3 or later.

See COPYING.GPL3 and COPYING.LGPL3 for details.
