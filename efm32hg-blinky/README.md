# Overview
This code produces a program with which to test the LEDs and capacitive on the
[tomu](http://tomu.im) board.  It will endlessly blink the green LED once, and
the red LED twice. It will also respond to capacitive touch; when you touch
either side of the board, it will make that side's LED blink ten times.

# How to Compile
Edit the `Makefile` and point it to where you've installed the toolchain, then :

```
make deps
make check  # resolve any issues with the linker script that have been identified
make
```

# How to Flash

Follow the steps in the general README.md, using `blinky.bin`
