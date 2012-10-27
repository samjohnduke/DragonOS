#include "output/graphics/graphics.h"
#include "input/controller.h"
#include "kernel/event.h"

void TestUP();
void TestDOWN();
void TestLEFT();
void TestRIGHT();
void TestA();
void TestB();

int
main(void)
{
	event_init();
	graphics_init();
	ControllerInit();
		
	watchEvent(UP, &TestUP);	
	watchEvent(DOWN, &TestDOWN);
	watchEvent(LEFT, &TestLEFT);
	watchEvent(RIGHT, &TestRIGHT);
	watchEvent(A, &TestA);
	watchEvent(B, &TestB);
		
	while(1)
	{
		UpdateBtnState();
		SetAuxAll(GetActive());
		DrawScreen();				
	}
}

void TestUP()
{
	ToggleAuxLed(1);
}
void TestDOWN()
{
	ToggleAuxLed(2);
}
void TestLEFT()
{
	ToggleAuxLed(3);
}
void TestRIGHT()
{
	ToggleAuxLed(4);
}
void TestA()
{
	ToggleAuxLed(5);
}
void TestB()
{
	ToggleAuxLed(6);
}

