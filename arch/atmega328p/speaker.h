#ifndef ARCH_SPEAKER_H
#define ARCH_SPEAKER_H

#include <avr/io.h>

void SpeakerInit() 
{
   DDRB |= 1<<PB1;
}

void SetSpeakerOn()
{
	PORTB |= 1<<PB1;
}

void SetSpeakerOff()
{
	PORTB &= ~(1<<PB1);
}

#endif
