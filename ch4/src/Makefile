include ../Makefile.inc

TLPI_LIB = ../../tlpi-dist/lib

all: simple_copy.o oexcl.o seek_io.o reading.o tee.o

simple_copy.o: simple_copy.c
oexcl.o: oexcl.c
seek_io.o: seek_io.c
reading.o: reading.c
tee.o: tee.c

clean:
	rm *.o