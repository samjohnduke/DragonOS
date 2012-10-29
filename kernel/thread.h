#ifndef KERNEL_PROCESS_H
#define KERNEL_PROCESS_H

#include <stdint.h>

//Define what a thread is
typedef struct thread {

	uint16_t* stack_ptr;	//where the top of the stack is 
	uint8_t*  stack;		//thread specific stack
	uint8_t   status;
	void	  (* finit)(void* arg);
	
	
} Thread;

//Define the states of a thread
typedef enum {

	FINISHED = 0,
	READY 	 = 1,
	BLOCKED  = 2,
	RUNNING  = 3,
	CREATED  = 4
	
} ThreadState;

//Create a new thread
void NewThread(Thread *t, void (*tinit)(void* arg));

//delete a thread
void DeleteThread(Thread *t);

//save all the registers on the stack
void SaveContext();

//restore all context variables from the stack into registers
void RestoreContext();

#endif
