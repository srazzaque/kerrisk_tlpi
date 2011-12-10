CC = gcc
TLPI_LIB = ../tlpi-dist/lib
CFLAGS = -Wall -I${TLPI_LIB} -g
COMMON_OBJS = ${TLPI_LIB}/error_functions.o 
OBJS = common_offsets.o
BUILDSTR = ${CC} ${CFLAGS} ${COMMON_OBJS}

all: bin/common_offsets bin/t_readv bin/t_writev bin/large_file

bin/common_offsets: bin ${COMMON_OBJS} common_offsets.o
	${BUILDSTR} common_offsets.o -o bin/common_offsets

bin/t_readv: bin ${COMMON_OBJS} t_readv.o
	${BUILDSTR} t_readv.o -o bin/t_readv

bin/t_writev: bin ${COMMON_OBJS} t_writev.o
	${BUILDSTR} t_writev.o -o bin/t_writev

bin/large_file: bin ${COMMON_OBJS} large_file.o
	${BUILDSTR} -D_FILE_OFFSET_BITS=64 large_file.o -o bin/large_file 


common_offsets.o: common_offsets.c
t_readv.o: t_readv.c
t_writev.o: t_writev.c my_structs.h
large_file.o: large_file.c

bin:
	mkdir bin

clean:
	rm -rf bin
	rm -f *.o

# External dependencies
# =====================
${TLPI_LIB}/error_functions.o:
	cd ${TLPI_LIB} ; make
