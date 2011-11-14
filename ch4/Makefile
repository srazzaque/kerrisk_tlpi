include Makefile.inc

all: bin/simple_copy

bin/simple_copy: src/simple_copy.o ${TLPI_LIB}/error_functions.o bin
	${CC} src/simple_copy.o ${TLPI_LIB}/error_functions.o -o bin/simple_copy

src/simple_copy.o: src/simple_copy.c
	cd src ; make

bin:
	mkdir bin

clean:
	rm -rf bin
	rm src/*.o