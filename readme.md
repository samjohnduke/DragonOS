Read all about it
=================

About DragonOS
--------------

DragonOS is an embeded operating system designed specifically for the 
Meggy Jnr RGB from EvilMadScientists. This project is for my university 
course Operating Systems - Comp3300 as a practical assignment in OS
design. 


How To Build
------------

Like most software everything works right out of the make file. 
There are a number of steps that are required however to build and then 
transfer on to the Meggy Jnr. First we need to compile the code

```Bash	
$	make
```
	
Now that the code has been compiled we push it onto the meggy. Before
this can be done the code must be put into hex form to be programable onto
the CPU. This step is contained within the push command but it is important 
to remember that it is occuring. Make sure that the meggy is plugged into 
the computer via the USB-TTL cable and run the command

```Bash
$	make push
```

Now the operating system is on the Meggy it is time to get programming. 
I recommend reading the programming guide to get a good handle on using
DragonOS to make your game.
	
License
-------
	
All code contained within the DragonOS source is licensed under the 
BEER-WARE license. Found within the LICENSE file in the root directory,
the BEER-WARE license is as permissive as possible, rewritten to help 
remind the users and developers that life is here to be enjoyed and not
squabled over ie. Political Climate of 2012 Patent Law.
	The license requires that the license always be reproducable by the 
source and the that all users and developers should drink a beer to the 
freedom given to us by permissive, open source licenses.

