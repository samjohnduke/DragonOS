#include "output/graphics/graphics.h"
#include "output/sound/music.h"
#include "input/controller.h"


int
main(void)
{

	graphics_init();
	ControllerInit();
	SoundInit();
			
	uint16_t toggle = 0;
	
	SetPxl(0,0,RED);
	SetPxl(1,0,BLUE);
	SetPxl(2,0,GREEN);
	SetPxl(3,0,RED);
	SetPxl(4,0,BLUE);
	SetPxl(5,0,GREEN);
	SetPxl(6,0,RED);
	SetPxl(7,0,BLUE);
	
	SetPxl(0,1,RED);
	SetPxl(1,1,BLUE);
	SetPxl(2,1,GREEN);
	SetPxl(3,1,RED);
	SetPxl(4,1,BLUE);
	SetPxl(5,1,GREEN);
	SetPxl(6,1,RED);
	SetPxl(7,1,BLUE);
	
	SetPxl(0,2,RED);
	SetPxl(1,2,BLUE);
	SetPxl(2,2,GREEN);
	SetPxl(3,2,RED);
	SetPxl(4,2,BLUE);
	SetPxl(5,2,GREEN);
	SetPxl(6,2,RED);
	SetPxl(7,2,BLUE);
	
	SetPxl(0,3,RED);
	SetPxl(1,3,BLUE);
	SetPxl(2,3,GREEN);
	SetPxl(3,3,RED);
	SetPxl(4,3,BLUE);
	SetPxl(5,3,GREEN);
	SetPxl(6,3,RED);
	SetPxl(7,3,BLUE);
	
	SetPxl(0,4,RED);
	SetPxl(1,4,BLUE);
	SetPxl(2,4,GREEN);
	SetPxl(3,4,RED);
	SetPxl(4,4,BLUE);
	SetPxl(5,4,GREEN);
	SetPxl(6,4,RED);
	SetPxl(7,4,BLUE);
	
	SetPxl(0,5,RED);
	SetPxl(1,5,BLUE);
	SetPxl(2,5,GREEN);
	SetPxl(3,5,RED);
	SetPxl(4,5,BLUE);
	SetPxl(5,5,GREEN);
	SetPxl(6,5,RED);
	SetPxl(7,5,BLUE);
	
	SetPxl(0,6,RED);
	SetPxl(1,6,BLUE);
	SetPxl(2,6,GREEN);
	SetPxl(3,6,RED);
	SetPxl(4,6,BLUE);
	SetPxl(5,6,GREEN);
	SetPxl(6,6,RED);
	SetPxl(7,6,BLUE);

	SetPxl(0,7,RED);
	SetPxl(1,7,BLUE);
	SetPxl(2,7,GREEN);
	SetPxl(3,7,RED);
	SetPxl(4,7,BLUE);
	SetPxl(5,7,GREEN);
	SetPxl(6,7,RED);
	SetPxl(7,7,BLUE);

	while(1)
	{
		DrawScreen();
		
		UpdateBtnState();
		//SetAuxAll(GetActive());
		
		if(toggle == 15000){
			ToggleAuxLed(7);
			toggle = 0;
			ToggleSound();
		}
		else {
			toggle++;
		}
				
	}
}
