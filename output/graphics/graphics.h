#ifndef GRAPHICS_GRAPHICS_H
#define GRAPHICS_GRAPHICS_H

#include "output/graphics/color.h"

#include <stdint.h>

//The display length is the number of pixels on the screen 
#define DISPLAY_LENGTH 192

//The row offset value is the the number of pixels in a row. (8)
#define ROW_OFFSET 8

//A pixel is sum combination of red blue and green and is represented
//within 8 bit (0-15) for each color 
typedef struct {
	uint8_t rgb[3];
} Pxl;

//The screen type is a array of bytes. 
typedef struct {
	Pxl screen[DISPLAY_LENGTH];
	uint8_t AuxLEDs;
} Display; 

//Setup the system to be able to handle graphics
void graphics_init();
void clearScreen();

void SetAuxAll(uint8_t all);

void SetAuxLed(int led, int status);

Pxl GetPxl();

void DrawScreen();

#endif
