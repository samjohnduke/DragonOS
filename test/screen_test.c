#include "graphics/graphics.h"

int
main(void)
{

	graphics_init();
	
	uint16_t toggle = 0;
	
	while(1)
	{
		DrawScreen();
		if(toggle == 100){
			SetAuxLed(0,1);
			toggle = 0;
		}
		else {
			toggle++;
		}
				
	}
}
