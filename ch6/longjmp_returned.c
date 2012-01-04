/**
 * Exericse 6-2
 * This is code to forcibly longjmp() into a returned function
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf buff;

void
actually_do_setjmp()
{
  printf("actually_do_setjmp()\n");
  setjmp(buff); // The call needs to be two functions deep
  printf("exiting actually_do_setjmp()\n");
}

void
do_setjmp()
{
  printf("do_setjmp()\n");
  actually_do_setjmp();
  printf("exiting do_setjmp()\n");
}

void
do_longjmp()
{
  printf("do_longjmp()\n");
  longjmp(buff, 1);
  printf("exiting do_longjmp()\n");
}

void
another_function()
{
  printf("another_function()\n");
  printf("exiting another_function()\n");
}

int
main(int argc, char *argv[])
{
  printf("main()\n");
  do_setjmp();
  another_function();
  do_longjmp();
  printf("exiting main()\n");
  exit(EXIT_SUCCESS);
}
