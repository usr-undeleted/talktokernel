compiling:
	rm -rf bin binary
	gcc -I ./ src/*.c
	mkdir bin
	mv a.out bin/binary
clean:
	rm -rf bin
fancy:
	rm -rf bin
	gcc -I ./ src/*.c
	mkdir bin
	mv a.out bin/binary
	ln -s bin/binary binary
