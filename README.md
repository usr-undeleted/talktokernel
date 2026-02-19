# Talk to the kernel!
Simple program that takes noise from linux's random-ness to pick words and form phrases with a variety of words.
# Compiling:
In the root directory of this repo, run "make", creating a "bin" folder that contains the binary inside.  
Running make clean (to remove bin directory) is not needed if you want to re-compile, running make alone already cleans up.
# Usage:
<binary command thingimajig> <number>  
Invalid inputs will give an error... hopefully-  
I'm looking fowards to making words be located in a lib or something, to make adding more easier, but for now, if you want to add your own words, edit the "code.c" file located inside "src", and on the array declaration, simply add more words with proper syntax.
