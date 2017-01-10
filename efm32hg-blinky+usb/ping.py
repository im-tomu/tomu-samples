#!/usr/bin/python3

import sys
import usb.core
import usb.util

data = 'ping'
if len(sys.argv) > 1:
	data = ' '.join(sys.argv[1:])

dev = usb.core.find(idVendor=0x10c4, idProduct=0x4711)
if dev is None:
    raise ValueError('Tomu not found')

bytes = dev.write(0x01, data, 0)
data = dev.read(0x81, bytes, 0)
print("Tomu returned '" + data.tostring().decode("utf-8") + "'")

