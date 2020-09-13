#include "pwm_capture.h"

// Configuration for PWM capture
void pulse_width_measurement_config(void)
{
	// Select the clock source
	TCB0.CTRLA &= ~TCB_CLKSEL_gm;
	TCB0.CTRLA = (0x1 << TCB_CLKSEL_gp) | (1 << TCB_ENABLE_bp);
	
	// Set counter mode
	TCB0.CTRLB = (0x4 << TCB_CNTMODE0_bp);
	
	// Enable capture
	TCB0.EVCTRL = (1 << TCB_CAPTEI_bp);
	
	// Enable compare interrupt
	TCB0.INTCTRL = (1 << TCB_CAPT_bp);
	
}


void pwm_capture_event_config(void)
{	
	// EVENT generator config
	EVSYS.CHANNEL0 = EVSYS_GENERATOR_PORT1_PIN3_gc; // Chose pin B3, D3 or F3 on channel 0
	EVSYS.USERTCB0 = EVSYS_CHANNEL_CHANNEL0_gc; // Chose port B
	
}




void pwm_capture_config(void)
{
	pulse_width_measurement_config();
	pwm_capture_event_config();
	
}

int pwm_capture_percentage(void)
{
	uint16_t tmp = TCB0.CCMP;
	if (tmp < 10000)
	{
		tmp = 10000;
	}
	
	int percent = (((tmp/100)-100)*100) / (100);
	
	return percent;
}