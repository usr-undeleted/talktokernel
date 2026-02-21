compiling:
	rm -rf bin binary
	mkdir bin
	gcc -I ./src -o ./bin/binary ./src/code.c
clean:
	rm -rf bin binary
fancy:
	rm -rf bin binary
	mkdir bin
	gcc -I ./src -o ./bin/binary src/code.c
	ln -s bin/binary binary
