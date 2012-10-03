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
#include "kernel/event.h"

int
main(void)
{

	//initialise the Operating System
	//dragon_init();
	
	//initialise the graphics
	graphics_init();
	
	//initialise eventedness
	event_init();
	
	//This is the event loop. It should be always spinning. 
	while(1) {
	
	}
	
}
