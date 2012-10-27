#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <stdint.h>

typedef enum { ACTIVE, RELEASED, INACTIVE } State;

typedef enum { 	
				UP    = 2, 
				DOWN  = 3, 
				LEFT  = 4, 
				RIGHT = 5, 
				A     = 0,
				B     = 1 
			 } BtnType;

extern uint8_t btnState;
extern uint8_t btnRelease;

State GetControllerState(BtnType btn);
uint8_t GetActive();
uint8_t GetReleased();
void UpdateBtnState();
void ControllerInit();

#endif
