#include "usb.h"

#include <stdarg.h>
#include <stdio.h>

static char serial_print_buffer[256];

static const uint32_t s_value[] = {1000000000u, 100000000u, 10000000u, 1000000u, 100000u, 10000u, 1000u, 100u, 10u, 1u};

void usb_config()
{
	PORTB.DIRSET = (1 << 0);
	PORTB.DIRCLR = (1 << 1);
	
	//receiver and transmitter enable
	USART3.CTRLB |= (1 << USART_TXEN_bp);
	//USART3.CTRLB |= (1 << USART_RXEN_bp);
	
	//enable asynchronous USART 
	USART3.CTRLC = (0x03 << USART_CHSIZE0_bp);
	
	//set baud rate
	USART3.BAUD = BAUD_VALUE;
}

void usb_recive()
{
	
}

void usb_transmit(char data)
{
	//wait for data to be shifted out (data is shifted out when DREIF is set)
	while (!(USART3.STATUS & (1 << USART_DREIF_bp)))
	{
		
	}
	
	//write to data register
	USART3.TXDATAL = data;
}

static int printu_override(char *s, unsigned u)
{
	char tmp_buf[12];
	int  i, n = 0;
	int  m;

	if (u == 0) {
		*s = '0';
		return 1;
	}

	for (i = 0; i < 10; i++) {
		for (m = 0; m < 10; m++) {
			if (u >= s_value[i]) {
				u -= s_value[i];
				} else {
				break;
			}
		}
		tmp_buf[i] = m + '0';
	}
	for (i = 0; i < 10; i++) {
		if (tmp_buf[i] != '0') {
			break;
		}
	}
	for (; i < 10; i++) {
		*s++ = tmp_buf[i];
		n++;
	}
	return n;
}

void usb_print(char* data, ...)
{
	char* start = serial_print_buffer;
	char* s = serial_print_buffer;

	int     n = 0;
	va_list ap;
	va_start(ap, data);
	while (*data) {
		if (*data != '%') {
			*s = *data;
			s++;
			data++;
			n++;
			} else {
			data++;
			switch (*data) {
				case 'c': {
					char valch = va_arg(ap, int);
					*s         = valch;
					s++;
					data++;
					n++;
					break;
				}
				case 'd': {
					int vali = va_arg(ap, int);
					int nc;

					if (vali < 0) {
						*s++ = '-';
						n++;
						nc = printu_override(s, -vali);
						} else {
						nc = printu_override(s, vali);
					}

					s += nc;
					n += nc;
					data++;
					break;
				}
				case 'u': {
					unsigned valu = va_arg(ap, unsigned);
					int      nc   = printu_override(s, valu);
					n += nc;
					s += nc;
					data++;
					break;
				}
				case 's': {
					char *vals = va_arg(ap, char *);
					while (*vals) {
						*s = *vals;
						s++;
						vals++;
						n++;
					}
					data++;
					break;
				}
				default:
				*s = *data;
				s++;
				data++;
				n++;
			}
		}
	}
	va_end(ap);
	*s = 0;

	while (*start != '\0')
	{
		usb_transmit(*start);
		start++;
	}
}