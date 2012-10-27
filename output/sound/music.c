#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdint.h>

#include "arch/atmega328p/speaker.h"
#include "output/sound/notes.h"
#include "output/sound/music.h"

uint8_t soundOn;
uint8_t state;
Note currentNote;
uint8_t currentRate;

void SoundInitInterrupt()
{

	SpeakerInit();
	
	state = 1;
	soundOn = 1;
	currentNote = C4;
	
	cli();// disable global interrupts
	
	TCCR1A = 0;// set entire TCCR1 register to 0
	TCCR1B = 0;
		
	//set compare match register to desired timer count:
	OCR1A = noteMap[currentNote];
	
	// turn on CTC mode:
	TCCR1B |= (1 << WGM12);
	
	// Set CS10 for no prescalling
	TCCR1B |= (1 << CS10) | (1 << CS11);
	
	// enable timer compare interrupt:
	TIMSK1 |= (1 << OCIE1A);
	
	sei();// enable global interrupts 
}
/*
ISR(TIMER1_COMPA_vect)
{
	if(state && soundOn) {
		SetSpeakerOn();
		state = 0;
	}
	else if(!state && soundOn) {
		SetSpeakerOff();
		state = 1;
	}
}
*/
void SoundInit()
{
	SpeakerInit();
	
	state = 1;
	soundOn = 1;
	currentNote = C4;
}

void PlaySound()
{
	if(state && soundOn) {
		SetSpeakerOn();
		state = 0;
	}
	else if(!state && soundOn) {
		SetSpeakerOff();
		state = 1;
	}
}

void SetSoundOff()
{
	soundOn = 0;
}

void SetSoundOn()
{
	soundOn = 1;
}

void ToggleSound()
{
	soundOn ^= 1;
}

uint8_t isSoundOn()
{
	return soundOn;
}

void SetCurrentNote(Note n)
{
	currentNote = n;
}

Note GetCurrentNote()
{
	return currentNote;
}

void SetCurrentRate(uint8_t r)
{
	currentRate = r;
}

uint8_t GetCurrentRate()
{
	return currentRate;
}
