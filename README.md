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
