include Makefile.inc

all: bin/simple_copy bin/oexcl bin/reading

bin/simple_copy: src/simple_copy.o ${TLPI_LIB}/error_functions.o bin
	${CC} src/simple_copy.o ${TLPI_LIB}/error_functions.o -o bin/simple_copy

bin/oexcl: src/oexcl.o ${TLPI_LIB}/error_functions.o bin
	${CC} src/oexcl.o ${TLPI_LIB}/error_functions.o -o bin/oexcl

bin/reading: src/reading.o ${TLPI_LIB}/error_functions.o bin
	${CC} src/reading.o ${TLPI_LIB}/error_functions.o -o bin/reading

src/simple_copy.o: src/simple_copy.c
	cd src ; make

src/reading.o: src/reading.c
	cd src ; make

src/oexcl.o: src/oexcl.c
	cd src ; make

bin:
	mkdir bin

${TLPI_LIB}/error_functions.o:
	cd ${TLPI_LIB} ; make

clean:
	rm -rf bin
	rm src/*.o