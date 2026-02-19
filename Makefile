compiling:
	rm -rf bin
	gcc -n binary src/*.c
	mkdir bin
	mv binary bin
clean:
	rm -rf bin
