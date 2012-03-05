#include "my_malloc.h" // NOTE: this is NOT xxx.h on purpose.
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#define CUR_BRK sbrk((intptr_t)0)

static int numFailed = 0;

static void
pass()
{
  printf("[PASS]\n");
}

static void
fail(const char *msg)
{
  printf("[FAIL] %s\n", msg);
  numFailed++;
}

static void
testing(char *item)
{
  printf("Testing %s\n", item);
}

void
test_basic_allocation()
{
  
  void *ptr, *ptr2;
  int *i, *t;

  testing("Basic allocation");

  // Check sbrk()
  ptr = CUR_BRK;

  // Allocate an int on the heap
  i = (int *)malloc(sizeof(int));

  // Ensure that sbrk(0) has risen by sizeof(size_t) + sizeof(int)
  ptr2 = CUR_BRK;
  assert((ptr2 - ptr) >= (sizeof(size_t) + sizeof(int)) && "Test heap has been allocated");
  
  // Test basic pointer storage
  *i = 24;
  t = i;
  assert((*t == 24) && "Test values can be retrieved");
  
  // Finally, pass if everything is OK
  pass();

}

void
test_basic_deallocation()
{
  void *ptr1, *ptr2;
  int *tmp;

  testing("Basic deallocation");

  ptr1 = CUR_BRK;
  tmp = (int *)malloc(sizeof(int));
  ptr2 = CUR_BRK;
  assert( (ptr2 > ptr1) && "System break has risen" );
  
  ptr1 = CUR_BRK;
  free(tmp);
  tmp = (int *)malloc(sizeof(int));
  ptr2 = CUR_BRK;
  assert( (ptr2 == ptr1) && "System remains the same" );
  
  pass();
}

void
test_allocation_after_deallocation()
{

  void *ptr1, *ptr2;
  int *tmp[5], *tmp2;
  long long *lng;
  int i;

  testing("Allocation after free()");
  
  // Allocate 5 ints on the heap using separate calls to malloc
  for (i=0; i < 5; i++) {
    tmp[i] = (int *)malloc(sizeof(int));
  }
  
  // Deallocate the second and the fourth
  free(tmp[1]);
  free(tmp[3]);
  free(tmp[4]);
  
  // Allocate another int and ensure system break doesn't rise
  ptr1 = CUR_BRK;
  tmp2 = (int *)malloc(sizeof(int));
  ptr2 = CUR_BRK;
  assert((ptr1 == ptr2) && "System break doesn't change after malloc that follows free");

  // Ensure that the memory address of tmp2 is after tmp[0] and before tmp[2]
  assert((tmp2 > tmp[0]) && (tmp2 < tmp[2]) && "Memory block 2 was re-used");

  // Allocate a long - sbrk should rise
  assert((sizeof(long long) > sizeof(int)) && "Ensure 'long long' is longer than int on this system");
  ptr1 = CUR_BRK;
  lng = (long long *)malloc(sizeof(long long));
  ptr2 = CUR_BRK;
  assert((ptr1 < ptr2) && "System should change because there are no free slots big enough for long long");
  
  // Allocate another, sbrk should not rise
  ptr1 = CUR_BRK;
  tmp2 = (int *)malloc(sizeof(int));
  ptr2 = CUR_BRK;
  assert((ptr1 == ptr2) && "System break should not change");

  // Assert that tmp2 > tmp[2]
  assert((tmp2 > tmp[2]) && "Memory block 4 was re-used");
  
  // Free the long and allocate another int, sbrk not rise and free block should be taken from middle
  free(lng);
  ptr1 = CUR_BRK;
  tmp2 = (int *)malloc(sizeof(int));
  ptr2 = CUR_BRK;
  assert((ptr1 == ptr2) && "System break should change");

  // tmp2 should be > tmp[3]
  assert((tmp2 > tmp[3]) && "Memory block was newly allocated");

  pass();

}

int
main(int argc, char *argv[])
{
  printf("Testing my_malloc.c ...\n");
  printf("------------------------------------------------------\n");

  test_basic_allocation();
  test_basic_deallocation();
  test_allocation_after_deallocation();

  return numFailed;
}
