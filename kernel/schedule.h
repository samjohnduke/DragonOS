#ifndef KERNEL_SCHEDUAL_H
#define KERNEL_SCHEDUAL_H

#include "kernel/thread.h"

#include <stdint.h>

//Add thread to the ready queue and the start of the schedule system
void StartThread(Thread *t);

//Primary execution will wait until all the threads specified 
void JoinThread(Thread **ts, uint8_t num);

//should any thread need to be switched with another, schedule will do this
void Schedule();

//setup all schedule systems
void ScheduleInit();

//switch functions call all relevant commands for context switch
void SwitchOut();
void SwitchIn(Thread *t);
void Switch(Thread *t);

#endif
