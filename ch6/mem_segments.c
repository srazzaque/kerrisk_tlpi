#include <stdio.h>
#include <stdlib.h>

char globBuf[65536]; // Uninitialised data segment
int primes[] = { 2, 3, 5, 7 }; // Initialised data segment

static int
square(int x) // Frame for square()
{
  int result; // Frame

  result = x * x;
  return result; // Return value passed via register
}

static void
doCalc(int val) // Frame
{
  printf("The square of %d is %d\n", val, square(val));
  if (val < 1000) {
    int t; // Frame
    t = val * val * val;
    printf("The cube of %d is %d\n", val, t);
  }
}

int
main(int arvc, char *argv[]) // Frame
{
  static int key = 9973; // Initialised data segment
  static char mbuf[10240000]; // Uninitialised data segment
  char *p; // Frame

  p = malloc(1024);// Heap

  doCalc(key);

  exit(EXIT_SUCCESS);
}
