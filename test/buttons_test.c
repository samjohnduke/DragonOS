#include "output/graphics/graphics.h"
#include "input/controller.h"

int
main(void)
{

	graphics_init();
	ControllerInit();
	
	
	while(1)
	{
		SetAuxAll(GetActive());
		DrawScreen();				
	}
}
