#ifndef ARCH_SCREEN_H
#define ARCH_SCREEN_H

#include <avr/io.h>
#include "output/graphics/graphics.h"

void delay(uint16_t ms) {
   uint16_t i,j;
   uint16_t loop = F_CPU / 17000;  // this is approximate and needs calabration.
   for (i=0;i<ms;i++) {
      for (j=0;j<loop;j++);
   }
}

void screen_setup(void) {

	DDRB  |= (1<<PB2) | (1<<PB3); // make the serial pins output   
	PORTB |= (1<<PB2);  // set the led drivers to recieve input
 
	DDRD  |= (1<<PD2); // make the pin for row 0 output
	PORTD |= (1<<PD2); // turn that row off.

	DDRD  |= (1<<PD3); // row 2
	PORTD |= (1<<PD3); 

	DDRD  |= (1<<PD4); // row 3
	PORTD |= (1<<PD4); 

	DDRD  |= (1<<PD5); // row 4
	PORTD |= (1<<PD5); 

	DDRD  |= (1<<PD6); // row 5
	PORTD |= (1<<PD6); 

	DDRD  |= (1<<PD7); // row 6
	PORTD |= (1<<PD7); 

	DDRB  |= (1<<PB0); // row 7
	PORTB |= (1<<PB0); 

	DDRB  |= (1<<PB4); // row 8
	PORTB |= (1<<PB4); 
	
}

void screen_draw(Display frame) {
	
	uint8_t i;

    for (i=0;i<8;i++) {
        
    	SPCR = (1 << SPE) | ( 1 << MSTR );    // enable SPI, master, and set clock rate

        SPDR = frame.AuxLEDs; // set the shift out register
        while(!(SPSR & (1<<SPIF))); // wait until complete

		uint8_t rows = 0;
		if(frame.screen[8*i+7].rgb[0])
			rows |= 1 << 7;
		if(frame.screen[8*i+6].rgb[0])
			rows |= 1 << 6;
		if(frame.screen[8*i+5].rgb[0])
			rows |= 1 << 5;
		if(frame.screen[8*i+4].rgb[0])
			rows |= 1 << 4;
		if(frame.screen[8*i+3].rgb[0])
			rows |= 1 << 3;
		if(frame.screen[8*i+2].rgb[0])
			rows |= 1 << 2;
		if(frame.screen[8*i+1].rgb[0])
			rows |= 1 << 1;
		if(frame.screen[8*i].rgb[0])
			rows |= 1 << 0;
			
        SPDR = rows;
        while(!(SPSR & (1<<SPIF))); 
	
		rows = 0;
		if(frame.screen[8*i+7].rgb[1])
			rows |= 1 << 7;
		if(frame.screen[8*i+6].rgb[1])
			rows |= 1 << 6;
		if(frame.screen[8*i+5].rgb[1])
			rows |= 1 << 5;
		if(frame.screen[8*i+4].rgb[1])
			rows |= 1 << 4;
		if(frame.screen[8*i+3].rgb[1])
			rows |= 1 << 3;
		if(frame.screen[8*i+2].rgb[1])
			rows |= 1 << 2;
		if(frame.screen[8*i+1].rgb[1])
			rows |= 1 << 1;
		if(frame.screen[8*i].rgb[1])
			rows |= 1 << 0;
			
        SPDR = rows;
        while(!(SPSR & (1<<SPIF))); 

		rows = 0;

		if(frame.screen[8*i+7].rgb[2])
			rows |= 1 << 7;
		if(frame.screen[8*i+6].rgb[2])
			rows |= 1 << 6;
		if(frame.screen[8*i+5].rgb[2])
			rows |= 1 << 5;
		if(frame.screen[8*i+4].rgb[2])
			rows |= 1 << 4;
		if(frame.screen[8*i+3].rgb[2])
			rows |= 1 << 3;
		if(frame.screen[8*i+2].rgb[2])
			rows |= 1 << 2;
		if(frame.screen[8*i+1].rgb[2])
			rows |= 1 << 1;
		if(frame.screen[8*i].rgb[2])
			rows |= 1 << 0;

        SPDR = rows;
        while(!(SPSR & (1<<SPIF))); 
        
        SPCR = 0; //turn off spi 

		PORTB |=4;

		//Turn the column of lights on
        if (i==0) {
            PORTD &= ~(1<<PD2);
        } else if (i==1) {
            PORTD &= ~(1<<PD3);
        } else if (i==2) {
            PORTD &= ~(1<<PD4);
        } else if (i==3) {
            PORTD &= ~(1<<PD5);
        } else if (i==4) {
            PORTD &= ~(1<<PD6);
        } else if (i==5) {
            PORTD &= ~(1<<PD7);
        } else if (i==6) {
            PORTB &= ~(1<<PB0);
        } else if (i==7) {
            PORTB &= ~(1<<PB4);
        }
		
		//wait just a little bit
        delay(1);
		
		//turn the row of lights off again
        if (i==0) {
            PORTD |= (1<<PD2);
        } else if (i==1) {
            PORTD |= (1<<PD3);
        } else if (i==2) {
            PORTD |= (1<<PD4);
        } else if (i==3) {
            PORTD |= (1<<PD5);
        } else if (i==4) {
            PORTD |= (1<<PD6);
        } else if (i==5) {
            PORTD |= (1<<PD7);
        } else if (i==6) {
            PORTB |= (1<<PB0);
        } else if (i==7) {
            PORTB |= (1<<PB4);
        }
        
        PORTB &= 251; 
    }
}

#endif
