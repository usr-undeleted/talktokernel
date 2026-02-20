# Talk to the kernel!
Simple program that takes noise from linux's random-ness to pick words and form phrases with a variety of words.
# Compiling:
In the root directory of this repo, run "make", creating a "bin" folder that contains the binary inside.  
Running make clean (to remove bin directory) is not needed if you want to re-compile, running make alone already cleans up.
# Usage:
<binary command thingimajig> <number>  
Invalid inputs will give an error... hopefully-  
All words are located inside "words.h". If you want to add/change/remove words, edit the file with proper syntax, and run make (fancy or not) if needed.  
"make fancy" makes a symbolic link!
# Contributing
The program can't really get much innovative I'd say, but if you're willingly to add features or add new words, you must follow these guidelines:  
For code.c:  
1. Comment whenever the reason/objective of a function isn't clear or is complex, and make comments small and easy to understand. Also make sure to comment declarations and where they are used.  
2. If you wanna make the code usable in something other than Linux, make sure to either:  
a. make args inside the code for compiling under windows, for example  
b. make a new file inside src for the OS, and rename code.c to linux.c. code for windows, for example, it should be named something like win.c or windows.c  
b2. update the Makefile with an argument for that specific OS, naming the function something like "win" or "windows"  
3. Make commit names clear and useful.  
4. Update the version file with the proper syntax:  
a.b.c  
a is for complete code changes, for example, a total rewrite of the code, or an addition of a feature that completely changes how to approach the code  
b is for significant changes, something like more error messages, a huge amount of new words, etc  
c is for minimal changes, something like correcting typos in words, redoing a small amount of syntax, or correcting a small issue  
5. For adding new words:  
just add cool new words that aren't innapropriate or that actually exist in english, and make sure they don't already exist  
