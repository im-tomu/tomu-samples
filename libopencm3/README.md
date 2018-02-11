# libopencm3

[libopencm3](http://libopencm3.org/) is an Open-Source lowlevel hardware
library for ARM Cortex-M3 microcontrollers (but also M0, M4 are supported and
more to come).

[Seb Holzapfel](https://github.com/schnommus) has been working on extending
libopencm3 to support the EFM32HG and currently has currently tested on the
Tomu using a Linux host:

 * A USB-Serial CDCACM device example (`usb_cdcacm`)
 * A USB HID mouse emulation example (`usb_hid`)
 * A USB Mass Storage Device example (`usb_msc`)
 * A USB MIDI example (`usb_midi`)
 * A raw endpoint example with a sample python program that controls an LED

The plan to push these changes upstream (to libopencm3) in the near future but
for now you can find a copy in the
[I'm Tomu GitHub organisation](https://github.com/im-tomu).

 * [libopencm3 with SiLabs EFM32 Happy Gecko + Tomu support.](https://github.com/im-tomu/libopencm3)
 * [libopencm3-examples with SiLabs EFM32 Happy Gecko + Tomu support.](https://github.com/im-tomu/libopencm3-examples)

# Building `libopencm3-examples`

Typing `make` will download and compile these examples for you.

The compiled binaries (and README.md about flashing) can then be found at `libopencm3-examples/examples/efm32/efm32hg/tomu-efm32hg309`
