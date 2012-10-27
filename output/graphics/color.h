#ifndef OUTPUT_GRAPHICS_COLOR_H
#define OUTPUT_GRAPHICS_COLOR_H

#include <stdint.h>

//Define some different colors;
typedef enum {

	BLACK     = 0,
	RED       = 1,
	GREEN     = 2,
	BLUE      = 3,
	YELLOW    = 4,
	PURPLE    = 5,
	CYAN      = 6,
	WHITE     = 7,

} Color;

//How are the colors defined. why as a const array of course.
const static uint8_t colors[8][3] = {
	
	{  0,  0,  0},
	{  1,  0,  0},
	{  0,  1,  0},
	{  0,  0,  1},
	{  1,  1,  0},
	{  1,  0,  1},
	{  0,  1,  1},
	{  1,  1,  1},

};


#endif
