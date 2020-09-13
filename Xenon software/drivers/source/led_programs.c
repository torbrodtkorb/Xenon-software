#include "led_programs.h"
#include "ws2812b.h"

color led_strip[NUMBER_OF_LEDS] = {0};
int i = 0;
uint16_t rainbow_starting_pos = 0;

float hue2rgb(float p, float q, float t) {
	if(t < 0) t += 1;
	if(t > 1) t -= 1;
	if(t < 1/6.0) return p + (q - p) * 6 * t;
	if(t < 1/2.0) return q;
	if(t < 2/3.0) return p + (q - p) * (2/3.0 - t) * 6;
	return p;
}

void hslToRgb(float h, float s, float l, uint8_t rgb[]) {
	float r, g, b;

	if (s == 0) {
		r = g = b = l; // achromatic
		} else {
		float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		float p = 2 * l - q;
		r = hue2rgb(p, q, h + 1/3.0);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1/3.0);
	}

	rgb[0] = r * 255;
	rgb[1] = g * 255;
	rgb[2] = b * 255;
}

void led_strip_on(uint16_t red, uint16_t green, uint16_t blue)
{
	for (uint16_t i = 0; i < NUMBER_OF_LEDS; i++)
	{
		led_strip[i] = (color){red, green, blue};
	}
	update_led_strip(led_strip, NUMBER_OF_LEDS);

}

void layer_on(uint16_t layer, uint16_t r, uint16_t g, uint16_t b) {
	uint16_t start_number = (layer - 1) * 10;
	for (uint16_t i = start_number; i < start_number + 10; i++) {
		led_strip[i] = (color){r, g, b};
	}
}


void led_strip_sparkle(uint16_t density, uint16_t speed)
{

	for (uint16_t i = 0; i < density; i++)
	{
		led_strip[rand() % NUMBER_OF_LEDS] = (color){ 100, 0, 80 };
	}
	
	for (int i = 0; i < NUMBER_OF_LEDS; i ++)
	{
		int16_t tmp = led_strip[i].red;
		tmp -= speed;
		
		if (tmp < 0)
		{
			tmp = 0;
		}
		led_strip[i].red = tmp;
		led_strip[i].blue = tmp;

	}
	update_led_strip(led_strip, NUMBER_OF_LEDS);
	_delay_ms(5);
}

void led_strip_sparkle_two(uint16_t density, uint16_t speed)
{

	for (uint16_t i = 0; i < density; i++)
	{
		led_strip[rand() % NUMBER_OF_LEDS] = (color){ 100, 0, 0 };
		led_strip[rand() % NUMBER_OF_LEDS] = (color){ 0, 0, 100 };
	}
	
	for (int i = 0; i < NUMBER_OF_LEDS; i ++)
	{
		int16_t tmp = led_strip[i].red;
		tmp -= speed;
		
		if (tmp < 0)
		{
			tmp = 0;
		}
		led_strip[i].red = tmp;
		//led_strip[i].blue = tmp;
		//led_strip[i].green = tmp;

	}
	update_led_strip(led_strip, NUMBER_OF_LEDS);
	_delay_ms(5);
}



void mitt_and_out(uint16_t r, uint16_t g, uint16_t b)
{
	i = 145;

	led_strip[145] = (color){100,0,0};
	update_led_strip(led_strip, NUMBER_OF_LEDS);
	
	for (int i = 146; i < NUMBER_OF_LEDS; i++)
	{
		led_strip[i] = (color){r, g, b};
		led_strip[NUMBER_OF_LEDS - i] = (color){r, g, b};
		update_led_strip(led_strip, NUMBER_OF_LEDS);
	}
	
	for (int i = 0; i < 146; i++)
	{
		led_strip[i] = (color){0, 0, 0};
		led_strip[NUMBER_OF_LEDS - i] = (color){0, 0, 0};
		update_led_strip(led_strip, NUMBER_OF_LEDS);
	}
}



void test(){
	char color [3];
	float hue = 0;
	while (1) {
		hue = hue+0.01f;
		hue -= (int)hue;
		
		hslToRgb(hue, 1, 0.5f, color);
		led_strip_on(color[0], color[1], color[2]);
		update_led_strip(led_strip, NUMBER_OF_LEDS);
		_delay_ms(30);
	}
}

void rainbow(){
	rainbow_starting_pos += 10;
	rainbow_starting_pos %= NUMBER_OF_LEDS;
	
	color c = (color){0, 0, 0};
	
	for (uint16_t i = 0; i < NUMBER_OF_LEDS/5; i++)
	{
		uint16_t pos_on_rainbow = (i*5 + NUMBER_OF_LEDS - rainbow_starting_pos) % NUMBER_OF_LEDS;
		float hue = (float)pos_on_rainbow / (float)NUMBER_OF_LEDS;
		hslToRgb(hue, 1, 0.195f, &c);
		for (uint16_t j = 0; j < 5; j++) {
			led_strip[i*5 + j] = c;
		}
	}
	update_led_strip(led_strip, NUMBER_OF_LEDS);
}

void smuth(void)
{
	for (int i = 0; i < 100; i++)
	{
		led_strip_on(i,0,i);
		update_led_strip(led_strip, NUMBER_OF_LEDS);
		_delay_ms(5);
	}
	for (int i = 0; i < 100; i++)
	{
		led_strip_on(100 - i,0,100 -i);
		update_led_strip(led_strip, NUMBER_OF_LEDS);
		_delay_ms(5);
	}
	

}


void eplepsi(void)
{
	led_strip_on(100,0,0);
	update_led_strip(led_strip, NUMBER_OF_LEDS);
	_delay_ms(80);
	
	led_strip_on(0,100,0);
	update_led_strip(led_strip, NUMBER_OF_LEDS);
	_delay_ms(80);
	
	led_strip_on(0,0,100);
	update_led_strip(led_strip, NUMBER_OF_LEDS);
	_delay_ms(80);

}