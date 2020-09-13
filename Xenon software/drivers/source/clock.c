#include "clock.h"

#include <avr/io.h>

void clock_config(void)
{
	CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB = 0;
}
