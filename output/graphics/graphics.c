#include "output/graphics/graphics.h"
#include "output/graphics/color.h"
#include "arch/atmega328p/screen.h"

//Need to do some IO stuff. 
#include <avr/io.h>

Display frame;

void graphics_init(void)
{
	screen_setup();
	clearScreen();
}

Pxl GetPxl()
{
	Pxl p;
	p.rgb[0] = 0;
	p.rgb[1] = 8;
	p.rgb[2] = 0;
	
	return p;
}

void SetAuxLed(int led, int status)
{
	frame.AuxLEDs ^= 1 << led;
}

void SetAuxAll(uint8_t all)
{
	frame.AuxLEDs = all;
}

void DrawScreen()
{
	screen_draw(frame);
}

void clearScreen()
{
	
	int i;
	for( i=0; i<=64; i++ )
	{
		frame.screen[i].rgb[0] = 0;
		frame.screen[i].rgb[1] = 0;
		frame.screen[i].rgb[2] = 0;
	}
}
