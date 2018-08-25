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
