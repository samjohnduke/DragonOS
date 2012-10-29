#include "kernel/event.h"
#include <stdlib.h>

uint16_t timer;
Event* eventList[20];

void EventInit(void)
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

void RegisterEvent(uint8_t eventNum)
{
	
	if(1) 
	{
		Event* e = malloc(sizeof(Event));
		e->num = eventNum;
		e->functions = malloc(sizeof(Event)*5);
		e->numfunctions = 0;
		
		eventList[eventNum] = e;
	}

}

void TriggerEvent(uint8_t eventNum)
{
	Event* e = eventList[eventNum];
	
	e->functions();
}

void WatchEvent(uint8_t eventNum, void (*function)(void))
{
	Event* e = eventList[eventNum];
	e->functions = function;
	e->numfunctions++;
}

