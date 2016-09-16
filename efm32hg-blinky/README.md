# Overview
This code produces a program with which to test the LEDs and capacitive on the
[tomu](http://tomu.im) board.  It will endlessly blink the green LED once, and
the red LED twice. It will also respond to capacitive touch; when you touch
either side of the board, it will make that side's LED blink ten times.

# How to Compile
Head over to http://launchpad.net/gcc-arm-embedded/+download to download the ARM
toolchain for your platform.

You will then need to edit the `Makefile` and point it to where you've extracted
the toolchain.

The `Makefile` can handle things from here. It will fetch the necessary
dependencies, check that they're set up correctly, and compile them.

```
make deps
make check  # resolve any issues with the linker script that have been identified
make
```

# How to Flash
Open up `minicom` (or whatever your favourite serial I/O utility is). Be sure to
configure it to talk `115200 8n1` with no flow control. Confirm the bootloader
on your tomu is responsive by pressing `i` and making sure you receive the
identification prompt from the bootloader.

Press `u` and the bootloader should report that it's `Ready`. Upload the
`blinky.bin` file using XMODEM to your tomu, and then press `b` to boot into it.
Remember that after striking `b`, the bootloader will no-op for 5-7 seconds to
give you time to close your serial I/O utility, so there will be a delay before
the LEDs start blinking.

