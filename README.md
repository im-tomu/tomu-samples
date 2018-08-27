# Tomu Samples

These projects are simple programs for the [Tomu](http://tomu.im). They do
various things, and are intended to offer code examples and simple testing to
ease your introduction to the Tomu platform.

These are based on the libopencm3 library.  To build projects using the `Gecko_SDK` provided by Silicon Labs, see the [gecko-sdk](./gecko-sdk) directory.

## libopencm3

[libopencm3](http://libopencm3.org/) is an Open-Source lowlevel hardware
library for ARM Cortex-M3 microcontrollers (but also M0, M4 are supported and
more to come).

Upstream libopencm3 now supports the EFM32HG. The examples located here
were modified to support the EFM32HG and tested on the Tomu with a Linux host:

* A USB-Serial CDCACM device example (`usb_cdcacm`)
* A USB HID mouse emulation example (`usb_hid`)
* A USB Mass Storage Device example (`usb_msc`)
* A USB MIDI example (`usb_midi`)
* A raw endpoint example with a sample python program that controls an LED

## Building

1. To compile these, you'll need a cross-compiling toolchain to arm-none-eabi.
* Debian/Ubuntu/... : `sudo apt-get install gcc-arm-none-eabi`
* Fedora : `sudo yum install arm-none-eabi-gcc-cs arm-none-eabi-newlib`
* OpenSUSE: sudo zypper ar obs://home:mnhauke home_mnhauke && sudo zypper in cross-arm-none-gcc8 cross-arm-none-newlib-devel dfu-util
* Arch : `sudo pacman -S arm-none-eabi-gcc arm-none-eabi-newlib`
* Other Linux : check your package manager, or
* Anything else (Windows, OSX, Linux): [https://developer.arm.com/open-source/gnu-toolchain/gnu-rm](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm)

2. Fetch the required git submodules:

```
git submodule init
git submodule update
```

3. Run `make` to build all examples

## Debugging build issues

It can be helpful to run the build with:

```
CFLAGS='-v' make
```

This will show you include paths, commands and more, and may help you to diagnose the issue.

## Bootloader assumptions

These examples are compatible with the non-DFU serial AN0042 bootloader.  They will run in legacy mode with a DFU-enabled bootloader, such as the one shipped on v0.4 boards.  They run from flash offset 0x4000, and do not auto-boot.  To get back into the bootloader, reset the board (e.g. by unplugging it and plugging it back in).

If you have a DFU-enabled bootloader, upload programs using `dfu-util`.  For example, to upload miniblink, run:

````
dfu-util -d 1209:70b1 -D ./usb_hid/usb_hid.bin
````

If you're using the serial bootloader, upload the binary using XMODEM.

## License

The libopencm3 code & examples are released under the terms of the GNU Lesser
General Public License (LGPL), version 3 or later.

See COPYING.GPL3 and COPYING.LGPL3 for details.

