include ../Makefile.inc

TLPI_LIB = ../../tlpi-dist/lib

all: simple_copy.o oexcl.o

simple_copy.o: simple_copy.c
	${CC} ${CFLAGS} -c simple_copy.c

oexcl.o: oexcl.c
	${CC} ${CFLAGS} -c oexcl.c

clean:
	rm *.o