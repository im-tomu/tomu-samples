# README

This example implements a USB CDC-ACM device (aka Virtual Serial Port)
to demonstrate the use of the USB device stack.

When data is recieved, it will toggle the green LED and echo the data.
The red LED is toggled constantly and a string is sent over USB every
time the LED changes state as a heartbeat.
