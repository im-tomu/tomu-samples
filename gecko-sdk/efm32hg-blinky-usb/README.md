# Overview
This code produces a program with which to test the LEDs, capacitive and USB on the
[tomu](http://tomu.im) board.  It will endlessly blink the green LED once, and
the red LED twice. It will also respond to capacitive touch; when you touch
either side of the board, it will make that side's LED blink ten times. If data
is send to its OUT buld endpoint (EP 0x01) then it will echo it back to the IN
bulk endpoint (EP 0x81) - unless 'ping' is sent: then it returns 'pong'. The
provided python script 'ping.py' can be used for testing (might require sudo for
privileges - YMMV).


# How to Compile
Edit the `Makefile` in the parent directory and possible define where you've installed the toolchain, then :

```
make
```

# How to Flash
Follow the steps in the general README.md, using `blinky-usb.bin`
