compiling:
	rm -rf bin binary
<<<<<<< HEAD
	gcc -I ./src src/*.c
=======
>>>>>>> f969a823228eff891fc84d17af254cc64d156e74
	mkdir bin
	gcc src/*.c -o bin/binary
clean:
	rm -rf bin binary
fancy:
	rm -rf bin binary
<<<<<<< HEAD
	gcc -I ./src src/*.c
=======
>>>>>>> f969a823228eff891fc84d17af254cc64d156e74
	mkdir bin
	gcc src/*.c -o bin/binary
	ln -s bin/binary binary
