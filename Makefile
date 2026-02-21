compiling:
	rm -rf bin binary
	gcc -I ./src src/*.c
	mkdir bin
	gcc src/*.c -o bin/binary
clean:
	rm -rf bin binary
fancy:
	rm -rf bin binary
	gcc -I ./src src/*.c
	mkdir bin
	gcc src/*.c -o bin/binary
	ln -s bin/binary binary
