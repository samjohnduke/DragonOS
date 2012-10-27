#include "output/graphics/graphics.h"

int
main(void)
{

	graphics_init();
	
	uint16_t toggle = 0;
	
	SetPxl(0,0,RED);
	SetPxl(1,0,BLUE);
	SetPxl(2,0,GREEN);
	SetPxl(3,0,RED);
	SetPxl(4,0,BLUE);
	SetPxl(5,0,GREEN);
	SetPxl(6,0,RED);
	SetPxl(7,0,BLUE);
	
	SetPxl(0,1,GREEN);
	
	while(1)
	{
		DrawScreen();
		if(toggle == 100){
			ToggleAuxLed(0);
			toggle = 0;
		}
		else {
			toggle++;
		}
				
	}
}
