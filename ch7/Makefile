CC = gcc
TLPI_LIB = ../tlpi-dist/lib
CFLAGS = -Wall -I${TLPI_LIB} -ggdb
COMMON_OBJS = ${TLPI_LIB}/error_functions.o ${TLPI_LIB}/get_num.o
COMMON_DEPS = ${COMMON_OBJS} bin
BUILDSTR = ${CC} ${CFLAGS} ${COMMON_OBJS}

all: bin/free_and_sbrk bin/my_malloc_sample_program

bin/free_and_sbrk: free_and_sbrk.o ${COMMON_DEPS}
	${BUILDSTR} free_and_sbrk.o -o bin/free_and_sbrk

my_malloc.o: my_malloc.c my_malloc.h
	${BUILDSTR} -c my_malloc.c

my_malloc_sample_program.o: my_malloc_sample_program.c

bin/my_malloc_sample_program: my_malloc.o my_malloc_sample_program.o ${COMMON_DEPS}
	${BUILDSTR} my_malloc.o my_malloc_sample_program.o -o bin/my_malloc_sample_program

free_and_sbrk.o: free_and_sbrk.c

bin:
	mkdir bin

# Cleanup
# =====================

clean:
	rm -rf bin
	rm -rf tests
	rm -f *.o

# Test
# =====================

test: tests my_malloc_test 

my_malloc_test.o: my_malloc_test.c
	${BUILDSTR} -c my_malloc_test.c

tests/my_malloc_test: my_malloc_test.o my_malloc.o
	${BUILDSTR} my_malloc_test.o my_malloc.o -o tests/my_malloc_test

my_malloc_test: tests/my_malloc_test
	./tests/my_malloc_test

tests:
	mkdir tests
# For some reason, the above 'testdir' gets invoke every time building test, unlike the bin one.


# External dependencies
# =====================
${TLPI_LIB}/error_functions.o:
	cd ${TLPI_LIB} ; make

${TLPI_LIB}/get_num.o:
	cd ${TLPI_LIB} ; make