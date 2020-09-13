#define F_CPU 20000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "clock.h"
#include "usb.h"
#include "pwm_capture.h"
#include "pwm_generator.h"

#include "led_programs.h"
#include "button_pres.h"
#include "ws2812b.h"

volatile uint16_t pulse_value;
volatile uint8_t capture_ready;

volatile uint16_t compare_match;

void led_config(void)
{
	PORTD.DIRSET = 0b11110; // Set D0 to D4 output
	PORTB.DIRSET = (1 << 2);
}


int main(void)
{
	pwm_capture_config();
	pwm_pulse_with_modulation_config();
	led_config();
	usb_config();
	clock_config();
	
	sei();
	
    while (1)
    {		
		//usb_print("Compare value : %d\n", TCB0.CCMP);
		//_delay_ms(50);
		/*
		int tmp = TCA0.SINGLE.CNT;
		usb_print("Value: %d\n", tmp);
		_delay_ms(10);
		*/

		if (capture_ready)
		{
			usb_print("Value: %d%s%d\n", pulse_value," : ", pwm_capture_percentage());
			_delay_ms(50);
			capture_ready = 0;	
		}
		
    }
}

ISR (TCB0_INT_vect)
{
	// Clear the interrupt flag
	TCB0.INTFLAGS = 0b1;
	
	PORTD.OUTTGL = 0b10; //Led pin toggle
	
	pulse_value = TCB0.CCMP; //holds the compare value
		
	// Set compare match
	TCA0.SINGLE.CMP2 = (uint16_t)((1000/100)*pwm_capture_percentage());
	
	capture_ready = 1;

}