#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <stdint.h>

typedef enum { ACTIVE, RELEASED, INACTIVE } State;

typedef enum { 	
				UP    = 0, 
				DOWN  = 1, 
				LEFT  = 2, 
				RIGHT = 3, 
				A     = 4,
				B     = 5 
			 } BtnType;

State GetBtnState(State s, BtnType btn);
uint8_t GetActive();
void ControllerInit();

#endif
