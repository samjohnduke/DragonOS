#include "kernel/event.h"
#include <stdlib.h>

uint16_t timer;
Event* eventList[20];

void event_init(void)
{
	timer = 0;
}

uint8_t TimerTick(uint16_t fps) 
{
	if(timer > fps) 
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void TimerUpdate()
{
	timer++;
}

void TimerReset()
{
	timer = 0;
}

void registerEvent(uint8_t eventNum)
{
	
	if(1) 
	{
		Event* e = malloc(sizeof(Event));
		e->num = eventNum;
		e->functions = malloc(sizeof(Event)*5);
		e->numfunctions = 0;
		
		eventList[eventNum] = e;
	}
	else
	{
		//event number already registered
	}

}

void triggerEvent(uint8_t eventNum)
{
	Event* e = eventList[eventNum];
	
	e->functions();
}

void watchEvent(uint8_t eventNum, void (*function)(void))
{
	Event* e = eventList[eventNum];
	e->functions = function;
	e->numfunctions++;
}

