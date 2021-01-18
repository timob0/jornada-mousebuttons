#include "uinput.h"
#include <stddef.h>

struct libevdev_uinput *uinput_initialize(struct libevdev **tsdevs) {
    // Create a evdev first to describe the features
    struct libevdev *evdev = libevdev_new();
    libevdev_set_name(evdev, "Touchscreen with button emulation");

    libevdev_enable_event_type(evdev, EV_KEY);
    libevdev_enable_event_code(evdev, EV_KEY, BTN_TOUCH, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, BTN_RIGHT, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, BTN_MIDDLE, NULL);
    libevdev_enable_event_code(evdev, EV_KEY, BTN_LEFT, NULL);

    libevdev_enable_event_type(evdev, EV_ABS);
    libevdev_enable_event_code(evdev, EV_ABS, ABS_X, libevdev_get_abs_info(tsdevs[0], ABS_X));
    libevdev_enable_event_code(evdev, EV_ABS, ABS_Y, libevdev_get_abs_info(tsdevs[0], ABS_Y));

    // Initialize uinput device from the evdev descriptor
    struct libevdev_uinput *uinput = NULL;
    if (libevdev_uinput_create_from_device(evdev, LIBEVDEV_UINPUT_OPEN_MANAGED, &uinput) != 0) {
        uinput = NULL;
    }

    // We don't need the fake evdev anymore.
    libevdev_free(evdev);
    return uinput;
}

void uinput_send_right_click(struct libevdev_uinput *uinput) {
    libevdev_uinput_write_event(uinput, EV_KEY, BTN_RIGHT, 1);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
    libevdev_uinput_write_event(uinput, EV_KEY, BTN_RIGHT, 0);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
}

void uinput_send_right_btn(struct libevdev_uinput *uinput, int value) {
    libevdev_uinput_write_event(uinput, EV_KEY, BTN_RIGHT, value);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
}

void uinput_send_middle_btn(struct libevdev_uinput *uinput, int value) {
    libevdev_uinput_write_event(uinput, EV_KEY, BTN_MIDDLE, value);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
}

void uinput_send_left_btn(struct libevdev_uinput *uinput, int value) {
    libevdev_uinput_write_event(uinput, EV_KEY, BTN_LEFT, value);
    libevdev_uinput_write_event(uinput, EV_SYN, SYN_REPORT, 0);
}

void uinput_passthrough_event(const struct libevdev_uinput *uinput_dev, unsigned int type, unsigned int code, int value) {
	libevdev_uinput_write_event(uinput_dev, type, code, value);
}
