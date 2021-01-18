jornada-mousebuttons (was: evdev-right-click-emulation)
---

This is based on PeterCxy's work to implement "long-tap to right click" for evdev touchscreens. This variant includes a couple of modifications to target Jornada 7xx devices by:
- Adding the ability to use front audio buttons as L/M/R buttons
- Adding the ability to disable touchscreen tap so that only front buttons work
- Adding the ability to switch to relative movements to emulating a real mouse even closer

It will connect to the event0 and event1 devices to read keyboard and touchscreen events. It will then add a new event2 device which will be the emulated pointing device that can be used as a touchscreen / mouse device in other applications.

Layering tslib on top of this is particlarily useful to get proper calibration.

Dependencies
---

- libevdev
- libevdev headers (for development)

And of course `glibc` and your Linux kernel.

Building
---
Manually:
Edit Makefile and uncomment CXFLAGS and Include directives, then

```bash
make all
```
The compiled program lies in `out/evdev-rce`.

For use with buildroot, download the folder subfolder "jornada-mousebuttons" and place it into the "packages" folder in buildroot. Then edit Config.in in the packages folder to point to jornada-mousebuttonsr/Config.in
Use make menuconfig to activate the package and then make.

Usage
---

Simply run

```bash
out/evdev-rce
```

Or you may put this executable anywhere on your file system.

Note: this program needs to read from and write to `/dev/input`. Make sure the current user has the permission to do so, or you may use `root`.

There are some tunable options accessible through the following environment variables:

```bash
# Required interval in ms for a touch event to be considered a long press
# default = 1000ms
LONG_CLICK_INTERVAL=1000
# Allowed margin of error (in px) for a long press event
# i.e. the finger is considered still if its movement is within this range
# Note: the px here is not physical pixels on the screen. It's the physical
# pixels of the touch devices, which may have a different resolution.
# default = 100px
LONG_CLICK_FUZZ=100
# Uncomment to set a blacklist of devices that `evdev-rce` will not
# listen on for touch events. The names can be retrived by using `xinput`
# or simply by reading the output of `evdev-rce`
# (it will print out the names of all touch devices when starting,
#  e.g. "Found touch screen at <some_path>: <device_name>)
#TOUCH_DEVICE_BLACKLIST="device1 name|device2 name|..."
# Uncomment to set a whitelist of devices that `evdev-rce` will ONLY
# listen on. This overrides the blacklist - when whitelist is present,
# any device not in this list will be ignored.
#TOUCH_DEVICE_WHITELIST="device1 name|device2 name|..."
```

So you can run the program like

```
LONG_CLICK_INTERVAL=500 LONG_CLICK_FUZZ=50 evdev-rce
```

To customize those options.
