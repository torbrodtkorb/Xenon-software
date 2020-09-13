#include "pwm_generator.h"

#define COUNTER_TOP_VALUE 1000


void pwm_waveform_generation_config(void)
{
	// Set count top value
	TCA0.SINGLE.PER = COUNTER_TOP_VALUE;
	
	// Select the clock frequency
	TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV1_gc;
	
	// Enable
	TCA0.SINGLE.CTRLA |= (1 << TCA_SINGLE_ENABLE_bp);
	
}


void pwm_pulse_with_modulation_config(void)
{	
	// Selecting waveform generation to single slope pulse with modulation
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
	
	// Disables count on event input
	TCA0.SINGLE.EVCTRL &= ~(1 << TCA_SINGLE_CNTEI_bp);
	
	// Configuration of port with portmux
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTB_gc;
	
	// Enable waveform on CMP2
	TCA0.SINGLE.CTRLB |= (1 << TCA_SINGLE_CMP2EN_bp);
	
	// Set compare match
	//TCA0.SINGLE.CMP2 = 500;
	
	pwm_waveform_generation_config();
}