#ifndef USB_H
#define USB_H

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 20000000
#endif

#define BAUD_RATE 115200
#define BAUD_VALUE (64 * F_CPU / 16 / BAUD_RATE)

void usb_config();

void usb_recive();

void usb_transmit(char data);

void usb_print(char* data, ...);

#endif