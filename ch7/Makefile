CC = gcc
TLPI_LIB = ../tlpi-dist/lib
CFLAGS = -Wall -I${TLPI_LIB} -g
COMMON_OBJS = ${TLPI_LIB}/error_functions.o ${TLPI_LIB}/get_num.o
COMMON_DEPS = ${COMMON_OBJS} bin
BUILDSTR = ${CC} ${CFLAGS} ${COMMON_OBJS}

all: bin/free_and_sbrk

bin/free_and_sbrk: free_and_sbrk.o ${COMMON_DEPS}
	${BUILDSTR} free_and_sbrk.o -o bin/free_and_sbrk

free_and_sbrk.o: free_and_sbrk.c

bin:
	mkdir bin

# Cleanup
# =====================

clean:
	rm -rf bin
	rm -f *.o

# External dependencies
# =====================
${TLPI_LIB}/error_functions.o:
	cd ${TLPI_LIB} ; make

${TLPI_LIB}/get_num.o:
	cd ${TLPI_LIB} ; make