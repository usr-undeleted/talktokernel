compiling:
	rm -rf bin binary
	mkdir bin
	gcc src/*.c -o bin/binary
clean:
	rm -rf bin binary
fancy:
	rm -rf bin binary
	mkdir bin
	gcc src/*.c -o bin/binary
	mv a.out bin/binary
	ln -s bin/binary binary
