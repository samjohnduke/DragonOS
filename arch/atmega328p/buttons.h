#ifndef ARCH_BUTTONS_H
#define ARCH_BUTTONS_H

#include <avr/io.h>

void BtnInit() 
{
   PORTC = 255U;   // Set port c as pull ups
   DDRC = 0;       // Set port c as all inputs
}

uint8_t GetBtnState() 
{
	uint8_t btn = PINC;
	
	//return the 0 for inactive and 1 for active version
	return ~btn & 0x3FU;
}

#endif
