import usb.core

if __name__ == "__main__":
    dev = usb.core.find(idVendor=0x1209, idProduct=0x70b1)

    if dev is None:
    	raise ValueError('Device not found')
    dev.set_configuration()

    from gi.repository import Gtk as gtk
    w = gtk.Window()
    w.connect("destroy", gtk.main_quit)
    toggle = gtk.ToggleButton("Toggle LED")
    def toggled(button):
    	dev.ctrl_transfer(0x40, 0, button.get_active(), 0, 'Hello World!')
    toggle.connect("toggled", toggled)
    w.add(toggle)
    w.show_all()
    gtk.main()

