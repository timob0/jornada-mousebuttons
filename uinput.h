#ifndef UINPUT_H
#define UINPUT_H
#include <libevdev/libevdev-uinput.h>

struct libevdev_uinput *uinput_initialize(struct libevdev **tsdevs);

void uinput_send_right_click(struct libevdev_uinput *uinput);

void uinput_send_right_btn(struct libevdev_uinput *uinput, int value);
void uinput_send_middle_btn(struct libevdev_uinput *uinput, int value);
void uinput_send_left_btn(struct libevdev_uinput *uinput, int value);

void uinput_passthrough_event(const struct libevdev_uinput *uinput_dev,
				unsigned int type,
				unsigned int code,
				int value);
#endif
