#ifndef OUTPUT_SOUND_MUSIC_H
#define OUTPUT_SOUND_MUSIC_H

#include <stdint.h>

//The note map sets up the frequencies of the 4th octave 
//Starting at C. This should be internal only
const uint16_t noteMap[14] = {
	
	262,
	277,
	294,
	311,
	330,
	349,
	370,
	392,
	415,
	440,
	466,
	494,
	0,
	1,
	
};

//Each note is the 4th octive from the bottom (lowest possible frequency)
//and starts from C. This C should be middle C on the piano.
typedef enum {

	C4   = 0,
	CS4  = 1,
	D4   = 2,
	DS4  = 3,
	E4   = 4,
	F4   = 5,
	FS4  = 6,
	G4   = 7,
	GS4  = 8,
	A4   = 9,
	AS4  = 10,
	B4   = 11,
	REST = 12,
	HOLD = 13,
	
} Note;


#endif
