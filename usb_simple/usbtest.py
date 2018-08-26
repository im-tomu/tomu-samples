#!/usr/bin/env python3
import usb.core

MODE = ['off', 'green', 'red', 'green+red']

def main():
    dev = usb.core.find(idVendor=0x1209, idProduct=0x70b1)

    if dev is None:
        raise ValueError('Device not found')
    dev.set_configuration()

    state = 0
    try:
        while True:
            # Send vendor request
            dev.ctrl_transfer(0x40, 0, state, 0, '')
            print('Light is ' + MODE[state])
            print('Press ENTER to toggle, ^C to quit')
            input()
            state += 1
            state %= 4
    except KeyboardInterrupt:
        pass

if __name__ == "__main__":
    main()
