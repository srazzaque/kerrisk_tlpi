CC = gcc
TLPI_LIB = ../tlpi-dist/lib
CFLAGS = -Wall -I${TLPI_LIB} -g
COMMON_OBJS = ${TLPI_LIB}/error_functions.o 
BUILDSTR = ${CC} ${CFLAGS} ${COMMON_OBJS}

all: bin/necho bin/modify_env bin/longjmp bin/setjmp_vars bin/setjmp_vars_o bin/mem_segments bin/longjmp_returned bin/env_functions

# Executable files
# =====================

bin/necho: bin necho.o
	${BUILDSTR} necho.o -o bin/necho

bin/modify_env: bin modify_env.o
	${BUILDSTR} modify_env.o -o bin/modify_env

bin/longjmp: bin longjmp.o
	${BUILDSTR} longjmp.o -o bin/longjmp

bin/setjmp_vars: bin setjmp_vars.o
	${BUILDSTR} setjmp_vars.o -o bin/setjmp_vars

bin/setjmp_vars_o: bin setjmp_vars_o.o
	${BUILDSTR} -O1 setjmp_vars_o.o -o bin/setjmp_vars_o

bin/mem_segments: bin mem_segments.o
	${BUILDSTR} mem_segments.o -o bin/mem_segments

bin/longjmp_returned: bin longjmp_returned.o
	${BUILDSTR} longjmp_returned.o -o bin/longjmp_returned

bin/env_functions: bin env_functions.o
	${BUILDSTR} env_functions.o -o bin/env_functions

necho.o: necho.c

modify_env.o: modify_env.c

longjmp.o: longjmp.c

setjmp_vars.o: setjmp_vars.c
	${CC} ${CFLAGS} -Wextra -c -o setjmp_vars.o setjmp_vars.c

setjmp_vars_o.o: setjmp_vars.c
	${CC} ${CFLAGS} -c -O -o setjmp_vars_o.o setjmp_vars.c

mem_segments.o: mem_segments.c

longjmp_returned.o: longjmp_returned.c

env_functions.o: env_functions.c

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
