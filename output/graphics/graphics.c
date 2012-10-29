#include "output/graphics/graphics.h"
#include "output/graphics/color.h"
#include "arch/atmega328p/screen.h"

//Need to do some IO stuff. 
#include <avr/io.h>

Display frame;

void GraphicsInit(void)
{
	screen_setup();
	ClearScreen();
}

Pxl* GetPxl(int8_t x, int8_t y)
{
	Pxl *p;
	uint8_t loc = (8*y + x);
	
	p = &frame.screen[loc];
	
	return p;
}

void SetPxl(int8_t x, int8_t y, Color color)
{
	int8_t loc = 63-(8*x+y);
	frame.screen[loc].rgb[0] = colors[color][0];
	frame.screen[loc].rgb[1] = colors[color][1];
	frame.screen[loc].rgb[2] = colors[color][2];
}

void ToggleAuxLed(uint8_t led)
{
	frame.AuxLEDs ^= 1 << led;
}

void SetAuxLedOn(uint8_t led)
{
	frame.AuxLEDs |= 1 << led;
}

void SetAuxLedOff(uint8_t led)
{
	frame.AuxLEDs &= ~(1 << led);
}

void SetAuxAll(uint8_t all)
{
	frame.AuxLEDs = all;
}

void DrawScreen()
{
	screen_draw(&frame);
}

void ClearScreen()
{
	
	int i;
	for( i=0; i<=64; i++ )
	{
		frame.screen[i].rgb[0] = colors[BLACK][0];
		frame.screen[i].rgb[1] = colors[BLACK][1];
		frame.screen[i].rgb[2] = colors[BLACK][2];
	}
}

/**
  function line(x0, x1, y0, y1)
     int deltax := x1 - x0
     int deltay := y1 - y0
     real error := 0
     real deltaerr := abs (deltay / deltax)    // Assume deltax != 0 (line is not vertical),
           // note that this division needs to be done in a way that preserves the fractional part
     int y := y0
     for x from x0 to x1
         plot(x,y)
         error := error + deltaerr
         if error ≥ 0.5 then
             y := y + 1
             error := error - 1.0
 
 */
void line (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color c)
{
	int8_t deltax = (x2 - x1);
	int8_t deltay = (y2 - y1);
	int8_t error  = 0;
	int8_t cerror = (deltay / deltax);
	int8_t derror = (deltay % deltax);
	int8_t dec    = deltax / 2;
	int8_t x      = x1;
	int8_t y 	   = y1;
	int8_t i;
	
	if(deltax == 0) 
	{
		for(i=y1; i<=y2; i++)
		{
			int8_t loc = 63-(8*x1+i);
			frame.screen[loc].rgb[0] = colors[c][0];
			frame.screen[loc].rgb[1] = colors[c][1];
			frame.screen[loc].rgb[2] = colors[c][2];
		}
	}
	else if(cerror > 1)
	{
		for(i=y1; i<=y2; i++)
		{
			int8_t loc = 63-(8*i+y);
			frame.screen[loc].rgb[0] = colors[c][0];
			frame.screen[loc].rgb[1] = colors[c][1];
			frame.screen[loc].rgb[2] = colors[c][2];
		
			error = error + derror;
			if(dec == 0) {
				x += 1;
			}
			else if(error > dec){
				x += 1;
				error -= deltax;
			}
		}
	}
	else if(cerror == 0)
	{
		for(i=x1; i<=x2; i++)
		{
			int8_t loc = 63-(8*i+y);
			frame.screen[loc].rgb[0] = colors[c][0];
			frame.screen[loc].rgb[1] = colors[c][1];
			frame.screen[loc].rgb[2] = colors[c][2];
		
			error = error + derror;
			if(dec == 0) {
				y += 1;
			}
			else if(error > dec){
				y += 1;
				error -= deltax;
			}
		}
	}
	
	
}

void square (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, Color c)
{
	
	uint8_t i, j;
	for(j = y1; j < (y1+height); j++)
	{
		for(i = x1; i < (x1+width); i++)
		{
			
			if( j == y1 || j == (y1+height-1) ) 
			{
				int8_t loc = 63-(8*i+j);
				frame.screen[loc].rgb[0] = colors[c][0];
				frame.screen[loc].rgb[1] = colors[c][1];
				frame.screen[loc].rgb[2] = colors[c][2];
			}
			else 
			{
				if( i == x1 || i == (x1+width-1) )
				{
					int8_t loc = 63-(8*i+j);
					frame.screen[loc].rgb[0] = colors[c][0];
					frame.screen[loc].rgb[1] = colors[c][1];
					frame.screen[loc].rgb[2] = colors[c][2];
				}
			}
		}
	}

}

void squarefill (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, Color c)
{
	
	uint8_t i, j;
	for(j = y1; j < (y1+height); j++)
	{
		for(i = x1; i < (x1+width); i++)
		{
			int8_t loc = 63-(8*i+j);
			frame.screen[loc].rgb[0] = colors[c][0];
			frame.screen[loc].rgb[1] = colors[c][1];
			frame.screen[loc].rgb[2] = colors[c][2];
		}
	}
	
}






