#include "output/graphics/graphics.h"
#include "output/sound/music.h"
#include "input/controller.h"


#include "kernel/event.h"
#include "kernel/thread.h"
#include "kernel/schedule.h"

#include "game/game.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void gthread(void *arg);
void dthread(void *arg);

int
main(void)
{
	GraphicsInit(); 			//Initialise Graphics
	EventInit();				//Initialise Events
	ControllerInit();			//Initialise The Controller
	ScheduleInit();				//Initialise The Scheduler	

	
	Thread *ts[2];
	
	NewThread(ts[0], &gthread);
	NewThread(ts[1], &dthread);
	
	TCCR1B |= (1 << WGM12);
	TIMSK1  = (1 << OCIE1A);
	
	sei();						//Turn Global Interrupts on
	
	OCR1A   = 200;				// 200*8 cycles between Timer Match
	TCCR1B  |= (1 << CS10); 	// 1/8 prescaler
	
	//initialise the users game code
	setup();
	
	StartThread(ts[0]);
	StartThread(ts[1]); 
	
	JoinThread(ts, 2);

	return 0;
}

void gthread(void *arg)
{
	loop();
	UpdateBtnState();
}

void dthread(void *arg)
{
	DrawScreen();
}

ISR(TIMER1_COMPA_vect, ISR_NAKED)
{
	Schedule();
	reti(); //finished scheduling so finish the interupt
	sei();
}
