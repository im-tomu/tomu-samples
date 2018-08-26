# README

This is small USB controlled LED example program using libopencm3.

The `usbtest.py` script in this directory may be used to control the LED.

When connected, the device will appear as:

```
Manufacturer: "Tomu"
Product Name: "USB Simple LED"
Serial Number: "e018bf6d-0e3b-4f20-bf9f-c25ee5e0f769"
```

One may send a USB Control Transfers of a Vendor request type (0x40) in order to change the LED state:

 * 0: Off
 * 1: Green
 * 2: Red
 * 3: Green and Red

## Flashing to a device with autorun

To build and flash `usb_simple` with autorun enabled, so you don't need to flash on power-on:

```
make usb_simple.bin CFLAGS=-DTOBOOT_FORCE_AUTORUN
dfu-util -d 1209:70b1 -D usb_simple.bin
```

If you want to be able to reflash this, you need to [short the two outer pads on power-on](https://github.com/im-tomu/tomu-bootloader#entering-toboot).
