#include "input/controller.h"
#include "arch/atmega328p/buttons.h"

extern uint8_t btnstate;

const uint8_t btnMask[6] = {1,2,4,8,16,32};

void ControllerInit()
{
	BtnInit();
	btnstate = 0;
}

State GetBtnState(BtnType btn) {
	
	State s;
	
	if(btn & btnMask[btn]) {
		s = ACTIVE;
	}
	else {
		s = INACTIVE;
	}
		
	return s;
}

void UpdateBtnState()
{
	btnstate = GetBtnState();
}

uint8_t GetActive()
{
	return btnstate;
}
