#include "output/sound/music.h"
#include "output/sound/notes.h"

void delay(uint16_t ms) {
   uint16_t i,j;
   uint16_t loop = F_CPU / 17000;  
   for (i=0;i<ms;i++) {
      for (j=0;j<loop;j++);
   }
}

int
main(void)
{

	SoundInit();	
	
	while(1)
	{
		PlaySound();
		delay(2);		
	}
}


