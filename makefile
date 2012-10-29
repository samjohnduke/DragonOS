###
# Make File for Dragon Operating System
# For the Meggy Jnr 
#
# Copyright Sam John Duke (c) 2012
###

# link headers from the root directory
PFLAGS = -I.

AVR_CFLAGS = -DF_CPU=16000000UL -mmcu=atmega328p
AVR_HFLAGS = -O ihex -R .eeprom

# build the os by linking all the object files together
dragon: graphics.o event.o run.o sound.o game.o controller.o 
	avr-gcc -Wall $(PFLAGS) $(AVR_CFLAGS) -o dragon run.o graphics.o event.o sound.o game.o controller.o
	
run.o: output/graphics/graphics.h kernel/event.h kernel/run.c game/game.h
	avr-gcc -g -c -Wall $(PFLAGS) $(AVR_CFLAGS) -o run.o kernel/run.c

graphics.o: output/graphics/graphics.h output/graphics/graphics.c \
			output/graphics/color.h arch/atmega328p/screen.h
	avr-gcc -g -c -Wall $(PFLAGS) $(AVR_CFLAGS) -o graphics.o output/graphics/graphics.c

controller.o: input/controller.h input/controller.c arch/atmega328p/buttons.h
	avr-gcc -g -c -Wall $(PFLAGS) $(AVR_CFLAGS) -o controller.o input/controller.c
	
event.o: kernel/event.h kernel/event.c
	avr-gcc -g -c -Wall $(PFLAGS) $(AVR_CFLAGS) -o event.o kernel/event.c
	
sound.o: output/sound/music.c output/sound/music.h output/sound/notes.h arch/atmega328p/speaker.h
	avr-gcc -g -c -Wall $(PFLAGS) $(AVR_CFLAGS) -o sound.o output/sound/music.c

game.o: game/game.c game/game.h input/controller.h
	avr-gcc -g -c -Wall $(PFLAGS) $(AVR_CFLAGS) -o game.o game/game.c 


	
# Remove everything but the source code	
.PHONY: clean

clean: 
	rm *.o
	rm dragon
	rm dragon.hex
	
# To send the OS to the meggy jnr first we need to turn the compiled code into
# hex and then push it the meggy. 
# use the cmd:
#
# 	make push 
#
.PHONY: push tohex

tohex: 
	avr-objcopy $(AVR_HFLAGS) dragon dragon.hex
	
push: tohex
	avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:dragon.hex


# We need to perform some tests to make sure that the components work
# individually first before they can be integrated into the operating 
# system and to ensure that they remain working. 
#
# This will be done by running 3 separate test modules. Each module is
# listed below and has a description of what each module does.
#
# 	TEST MODULE ONE :: ROAR
#	
# The roar test module is a stand alone program capable of testing
# every component of the sound architecture of the meggy jnr. The first
# test will be a 1 note per second sweep through all possible sounds
#
#	TEST MODULE TWO :: SCREEN
#
# The screen test module will do a sweep through the screen and display 
# every different color acheiveable on every pixel of the screen
#
#	TEST MODULE THREE :: BUTTONS
#
# The button test module will provide a way to test the button presses
# and display this appropriately. 
# 
# More Test modules will be created as the project becomes more complex

.PHONY: test roar_test screen_test button_test system_test thread_test

test: roar_test screen_test button_test system_test thread_test
	
roar_test:
	@echo 
	@echo 'Sound Test'
	@echo 'Listen for the sounds'
	@echo 
	avr-gcc -g -Wall $(PFLAGS) $(AVR_CFLAGS) -o RoarTest test/sound_test.c output/sound/music.c
	avr-objcopy $(AVR_HFLAGS) RoarTest RoarTest.hex
	avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:RoarTest.hex
	
screen_test:
	@echo 
	@echo 'Screen Test'
	@echo 'All the pretty colors'
	@echo 
	avr-gcc -g -Wall $(PFLAGS) $(AVR_CFLAGS) -o ScreenTest test/screen_test.c output/graphics/graphics.c
	avr-objcopy $(AVR_HFLAGS) ScreenTest ScreenTest.hex
	avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:ScreenTest.hex
	
button_test:
	@echo
	@echo 'Button Test'
	@echo 'Push buttons to test'
	@echo 
	avr-gcc -g -Wall $(PFLAGS) $(AVR_CFLAGS) -o ButtonTest test/buttons_test.c output/graphics/graphics.c input/controller.c kernel/event.c
	avr-objcopy $(AVR_HFLAGS) ButtonTest ButtonTest.hex
	avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:ButtonTest.hex

system_test: 
	@echo
	@echo 'System Test'
	@echo 'Does it all work together'
	@echo 
	avr-gcc -g -Wall $(PFLAGS) $(AVR_CFLAGS) -o SystemTest test/system_test.c output/sound/music.c output/graphics/graphics.c input/controller.c
	avr-objcopy $(AVR_HFLAGS) SystemTest SystemTest.hex
	avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:SystemTest.hex

thread_test:
	@echo
	@echo 'Thread Test'
	@echo 'Towards getting threads working'
	@echo
	avr-gcc -g -Wall $(PFLAGS) $(AVR_CFLAGS) -o ThreadTest test/thread_test.c output/graphics/graphics.c input/controller.c kernel/event.c kernel/schedule.c kernel/thread.c game/game.c
	avr-objcopy $(AVR_HFLAGS) ThreadTest ThreadTest.hex
	avrdude -b57600 -patmega328p -cstk500v1 -P/dev/ttyUSB0 -U flash:w:ThreadTest.hex


