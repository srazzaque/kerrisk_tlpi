//#include "my_malloc.h"
#include <malloc.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
  printf("Copyright (C) Sandipan Razzaque 2012\n");
  int *num1, *num2;
  num1 = (int *)malloc(sizeof(int));
  *num1 = 23;
  num2 = num1;
  printf("The number is: %d\n", *num2);
  return 0;
}
