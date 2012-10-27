#include "input/controller.h"
#include "arch/atmega328p/buttons.h"
#include "kernel/event.h"

const uint8_t btnMask[6] = {1,2,4,8,16,32};

uint8_t btnState;
uint8_t btnRelease;

void ControllerInit()
{	
	BtnInit();
	btnState = 0;
	btnRelease = 0;
	
	registerEvent(UP);
	registerEvent(DOWN);
	registerEvent(RIGHT);
	registerEvent(LEFT);
	registerEvent(A);
	registerEvent(B);
}

State GetControllerState(BtnType btn) {
	
	State s;
	
	if(btnState & btnMask[btn]) {
		s = ACTIVE;
	}
	else if(btnRelease & btnMask[btn]) {
		s = RELEASED;
	}
	else {
		s = INACTIVE;
	}
		
	return s;
}

void UpdateBtnState()
{
	uint8_t btns = GetBtnState();
	
	//foreach button 
	uint8_t i;
	for(i = 0; i<6; i++){
		
		//uint8_t last = btnState & btnMask[i]; //last will be 1 if on the last 
											  //update the btn was run otherwise 0.
		//uint8_t now  = btns & btnMask[i];	  //now will 1 if on just now and 0
											  //otherwise
		
		//is the btn on before and off now
		if( (btnState & btnMask[i]) && !(btns & btnMask[i]) )
		{
			
			btnRelease |= btnMask[i]; //set the button as released
			
			triggerEvent(i);		  //call all the functions that are needed 
									  //for this button press
		}	
		
		//is the button on now and previously marked as released
		if( (btns & btnMask[i]) && (btnRelease & btnMask[i]) )
		{
			//set the button as not released
			btnRelease &= ~(btnMask[i]);
		}
	}
	
	btnState = btns;
}

uint8_t GetActive()
{
	return btnState;
}

uint8_t GetReleased()
{
	return btnRelease;
}

