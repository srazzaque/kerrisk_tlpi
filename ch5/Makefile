CC = gcc
TLPI_LIB = ../tlpi-dist/lib
CFLAGS = -Wall -I${TLPI_LIB} -g
COMMON_OBJS = ${TLPI_LIB}/error_functions.o 
OBJS = common_offsets.o
BUILDSTR = ${CC} ${CFLAGS} ${COMMON_OBJS}

all: bin/common_offsets bin/t_readv bin/t_writev bin/large_file bin/append_seek_write bin/atomic_append bin/my_dups

# Executable files
# =====================

bin/common_offsets: bin ${COMMON_OBJS} common_offsets.o
	${BUILDSTR} common_offsets.o -o bin/common_offsets

bin/t_readv: bin ${COMMON_OBJS} t_readv.o
	${BUILDSTR} t_readv.o -o bin/t_readv

bin/t_writev: bin ${COMMON_OBJS} t_writev.o
	${BUILDSTR} t_writev.o -o bin/t_writev

bin/large_file: bin ${COMMON_OBJS} large_file.o
	${BUILDSTR} -D_FILE_OFFSET_BITS=64 large_file.o -o bin/large_file 

bin/append_seek_write: bin ${COMMON_OBJS} append_seek_write.o
	${BUILDSTR} append_seek_write.o -o bin/append_seek_write 

bin/atomic_append: bin ${COMMON_OBJS} atomic_append.o
	${BUILDSTR} atomic_append.o -o bin/atomic_append 

bin/my_dups: bin ${COMMON_OBJS} my_dups.o my_dups_functions.o
	${BUILDSTR} my_dups.o my_dups_functions.o -o bin/my_dups 

common_offsets.o: common_offsets.c
t_readv.o: t_readv.c
t_writev.o: t_writev.c my_structs.h
large_file.o: large_file.c
append_seek_write.o: append_seek_write.c
atomic_append.o: atomic_append.c
my_dups.o: my_dups.c
my_dups_functions.o: my_dups_functions.c my_dups_functions.h
my_readv_writev.o: my_readv_writev.c
my_readv_writev_functions.o: my_readv_writev_functions.c my_readv_writev_functions.h

bin:
	mkdir bin


# Tests
# =====================

test_run: test
	tests/my_readv_writev_test

test: tests/my_readv_writev_test

tests/my_readv_writev_test: tests my_readv_writev_test.o
	${BUILDSTR} my_readv_writev_test.o -o tests/my_readv_writev_test

my_readv_writev_test.o: my_readv_writev_test.c my_readv_writev_functions.c my_readv_writev_functions.h

tests:
	mkdir tests


# Cleanup
# =====================

clean:
	rm -rf bin
	rm -rf tests
	rm -f *.o

# External dependencies
# =====================
${TLPI_LIB}/error_functions.o:
	cd ${TLPI_LIB} ; make
