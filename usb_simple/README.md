# README

This is small USB controlled LED example program using libopencm3.

## Flashing to a Tomu with autorun

To build and flash `usb_simple` with autorun enabled, so you don't need to flash on power-on:

```
make usb_simple.bin CFLAGS=-DTOBOOT_FORCE_AUTORUN
dfu-util -d 1209:70b1 -D usb_simple.bin
```

If you want to be able to reflash this, you need to [short the two outer pads on power-on](https://github.com/im-tomu/tomu-bootloader#entering-toboot).

## Controlling the LED

The `usbtest.py` script in this directory may be used to control the LED with [`pyusb`][pyusb] and
`libusb`.

If you're running Windows, you'll _also_ need to install `libusb-package` with `pip` and
[assign the `WinUsb` driver](#windows-driver) to the Tomu Simple USB to make it work.

Linux and macOS do not require any drivers.

When connected, the device will appear as:

```
Manufacturer: "Tomu"
Product Name: "USB Simple LED"
Serial Number: "e018bf6d-0e3b-4f20-bf9f-c25ee5e0f769"
```

You can send a USB Control Transfers of a Vendor request type (0x40) in order to change the LED state:

* 0: Off
* 1: Green
* 2: Red
* 3: Green and Red

## Windows driver

You'll need to assign the `WinUsb` driver to the Tomu in order to control it:

1. Open `Device Manager`
1. Expand `Other devices`
1. Right-click `USB Simple LED` and select `Update driver`
1. Click `Browse my computer for drivers`
1. Click `Let me pick from a list of available drivers on my computer`
1. Under `Manufacturer`, click `WinUsb Device`
1. Under `Model`, click `WinUsb Device`
1. Click `Next`
1. Windows will warn that installing the driver is not recommended because it cannot verify that it is compatible. Click `Yes` to continue installing the driver.

The `USB Simple LED` device should now move to the `Universal Serial Bus devices` section, and you
should be able to control the LED with the `usbtest.py` script above.

[pyusb]: https://pypi.org/project/pyusb/

