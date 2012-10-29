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
	uint8_t Updated;
} Display; 

//Setup the system to be able to handle graphics
void GraphicsInit();

//Set the screen to display all black values
void ClearScreen();

//Set all the Aux LEDs at the same time via a bit pattern. 
// eg if all = 01001000 then the 2nd and 5 LEDS turn on
void SetAuxAll(uint8_t all);

//Set the specific led on or off. This will need to be formalised in
//some way probably as an enum but for now int represent the LED number.
//Does not care about the current LED state
void SetAuxLedOn(uint8_t led);

//Same as SetAuxLedOn but turns off the led. does not about the current LED 
//state
void SetAuxLedOff(uint8_t led);

//Changes the state of the specific LED.
void ToggleAuxLed(uint8_t led);

//Returns a pointer to a Pxl object (struct) at specific coordinates x and y
Pxl* GetPxl(int8_t x, int8_t y);

//Sets the color of the pixel at x and y coordinates
void SetPxl(int8_t x, int8_t y, Color c);

//takes the display object and draws it on the screen
void DrawScreen();

//SIMPLE GRAPHICS LIBRARY
void line       (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color c);
void square     (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, Color c);
void squarefill (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, Color c); 


#endif
