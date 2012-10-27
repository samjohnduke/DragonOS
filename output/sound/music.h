#ifndef OUTPUT_SOUND_MUSIC_H
#define OUTPUT_SOUND_MUSIC_H

#include <stdint.h>

#include "output/sound/notes.h"

//Setup using the speaker without interupts. requires repeatedly calling 
//PlaySound to toggle the speaker on and off.
void SoundInit();

//Setup the speaker using interupts. once it is setup nothing else needs to be
//done except select the notes at the right intervals
void SoundInitInterrupt();

//Turn the sound off. If the sound is off then the interrupt and the active play
//will be silent until the sound is turned back on again
void SetSoundOff();

//Turn the sound on. Allows the buzzer to make noise
void SetSoundOn();

//Calling Toggle sound will change the state of the sound between off and on 
//with every call, useful if you need regular interval toggling
void ToggleSound();

//test whether the sound is on or off
uint8_t isSoundOn();

//Get and set the current note being played by the speaker. This will not work 
//until the interface can be tweaked slightly
void SetCurrentNote(uint8_t n);
uint8_t GetCurrentNote();

//I suspect my concept of rate is too similar to a note so this may be removed
void SetCurrentRate(uint8_t r);
uint8_t GetCurrentRate();

//PlaySound should be actively (as fast as possible) to make the speaker work
void PlaySound();


#endif
