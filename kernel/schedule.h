#ifndef KERNEL_SCHEDUAL_H
#define KERNEL_SCHEDUAL_H

#include "kernel/thread.h"

#include <stdint.h>

void StartThread(Thread *t);
void JoinThread(Thread **ts, uint8_t num);

void Schedule();
void ScheduleInit();

void SwitchOut();
void SwitchIn(Thread *t);
void Switch(Thread *t);

#endif
