#ifndef KERNEL_EVENT_H
#define KENREL_EVENT_H

#include <stdint.h>

//What an event is
typedef struct {
	uint8_t num;
	void (*functions)(void);
	uint8_t numfunctions;
} Event;

//A list of events
extern Event* eventList[20]; 
extern uint16_t timer;

void    EventInit();
uint8_t TimerTick(uint16_t fps);
void 	TimerReset();
void 	TimerUpdate();

void 	RegisterEvent (uint8_t eventNum);
void 	TriggerEvent  (uint8_t eventNum);
void	WatchEvent    (uint8_t eventNum, void (*function)(void));

#endif
