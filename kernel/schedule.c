#include "kernel/schedule.h"
#include "kernel/thread.h"

#include <stdlib.h>

//A SchedQueue is an array of pointers to threads and 
//both the total number of threads the queue CAN contain
//and a pointer to the last thread pushed onto the queue

//This should be furthur developed into a proper queue interface. 
typedef struct {

	Thread   **ts;
	Thread   *ptr;
	uint8_t  totalnum;
	uint8_t  num;
	
} SchedQueue;

void ShuffleQueue(SchedQueue* q);


//There are 4 states and 3 that are queueable. Ready Blocked and Finished
static SchedQueue Ready;
static SchedQueue Blocked;
static SchedQueue Finished;

//The fourth state is the thread that is currently running. As Meggy Jnr on has
//one 'path of execution' there can only be 1 thread running at a time.
static Thread *Running;


//Brute of the Scheduling Facility. Decides flow of execution of all threads 
//after they have entered the ready queue for the first time
void Schedule()
{
	SwitchOut();
	
	//Check to see if there are any threads waiting to run
	//otherwise just keep running the currently running thread
	if(Ready.num > 0)
	{
		ShuffleQueue(&Ready); 		//This is a dummy call which can be removed later (its really bad)
		
		if(Running != 0)
		{
			Running->status = READY;
			Ready.ts[Ready.num] = Running;
		}
		
		Running = Ready.ts[0];
		Ready.ts[0] = 0;
	}
	
	SwitchIn(Running);
}


//Prepare the scheduler to do its job
void ScheduleInit()
{

	Ready.ts = malloc(sizeof(Thread *)*2);		//Initialise the Ready Queue
	Ready.ptr = Ready.ts[0];
	Ready.num = 0;
	Ready.totalnum = 2;
	
	Blocked.ts = malloc(sizeof(Thread *)*2);	//Initialise the Blocked Queue
	Blocked.ptr = Blocked.ts[0];
	Blocked.num = 2;
	Blocked.totalnum = 2;
	
	Finished.ts = malloc(sizeof(Thread *)*2);	//Initialise the Finished Queue
	Finished.ptr = Finished.ts[0];
	Finished.num = 0;
	Finished.totalnum = 2;
}

//Starting a thread allows the user to push a thread onto the ready queue and
//await scheduling
void StartThread(Thread *t)
{
	if(Ready.num == (Ready.totalnum))
	{
		//allocate more room in the ready queue and
		//increase total num count
		Ready.ts = realloc(Ready.ts, sizeof(Thread*)*(Ready.totalnum+2));
	}
	
	Ready.ts[Ready.num+1] = t;	//push thread onto the ready queue
	Ready.num++; 				//increment the position of the 
}


//This should be run from outside the context of threads and will wait until all 
//the threads have completed execution before continueing.
void JoinThread(Thread **ts, uint8_t num)
{
	uint8_t i,j;
	
	while(1)
	{
		j = 0;
		
		for(i = 0;i<num;i++)
		{
			if(ts[i]->status == FINISHED)
			{
				j++;
			}
		}	
		
		if(j == num)
		{
			return;
		}
	}
}

//Pop all the registers and thread control information onto the stack and
//then reset the original context
void SwitchOut()
{
	SaveContext(Running);
}


//push all the new threads data from the stack to the registers
void SwitchIn(Thread *t)
{
	RestoreContext(t);
}

//switch from the running thread to the new thread without reseting the original
//context. This is the fastest type of context switch but requires a premptive 
//and intellegent Schedualer
void Switch(Thread *t)
{
	SaveContext(Running);
	RestoreContext(t);
}

//if a thread decides that it no longer needs to run it can yield by switching 
//itself from running to ready and calling the scheduler. 
void Yield()
{
	Running->status = READY;
	Schedule();
}

//Take the queue and move all the pointers left one position
void ShuffleQueue(SchedQueue* q)
{
	uint8_t i = 0;
	while(i < q->totalnum)
	{
		q->ts[i] = q->ts[i-1]; 
		
		i++;
	}
}
