compiling:
	rm -rf bin
	gcc src/*.c
	mkdir bin
	mv a.out bin/binary
clean:
	rm -rf bin
