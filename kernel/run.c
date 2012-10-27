/**
 * Run.c
 *
 * Entry Point into the OS
 * Contains the loop for engaging and dispatching events
 *
 * Dragon is an evented operating system for embedded gaming
 * devices. Applications can emit events and listen for events
 * allowing the games to be easily programmed.
 *
 * Sam John Duke
 * mail@samjohnduke.com
 *
 * copyright (c) 2012
 */

#include "output/graphics/graphics.h"
#include "output/sound/music.h"
#include "kernel/event.h"
#include "game/game.h"
#include "input/controller.h"

#include <avr/io.h>
#include <avr/interrupt.h>

int
main(void)
{
	
	//initialise the graphics
	graphics_init();
	
	//initialise eventedness
	event_init();
	
	//controller initialisation
	ControllerInit();	
	
	TCCR1B |= (1 << WGM12);

	TIMSK1 = (1 << OCIE1A);
	sei();
	
	OCR1A   = 200;
	
	TCCR1B |= (1 << CS10);
	
	//initialise the users game code
	setup();
	
	//This is the event loop. It should be always spinning. 
	while(1) {	
		loop();
		UpdateBtnState();
		//SetAuxAll(GetActive());
		//ToggleAuxLed(7);
	}
	
}

ISR(TIMER1_COMPA_vect)
{
	TimerUpdate();
	DrawScreen();
	
}

