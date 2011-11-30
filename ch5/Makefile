
CC = gcc
TLPI_LIB = ../tlpi-dist/lib
CFLAGS = -Wall -I${TLPI_LIB} -g
OBJS = common_offsets.o ${TLPI_LIB}/error_functions.o 

all: bin/common_offsets

bin/common_offsets: bin ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o bin/common_offsets

common_offsets.o: common_offsets.c

bin:
	mkdir bin

clean:
	rm -rf bin
	rm -f *.o

# External dependencies
# =====================
${TLPI_LIB}/error_functions.o:
	cd ${TLPI_LIB} ; make
