#include "my_malloc.h" // NOTE: this is NOT xxx.h on purpose.
#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#define CUR_BRK sbrk((intptr_t)0)

static void
pass()
{
  printf("[PASS]\n");
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
  assert((ptr2 - ptr) == (sizeof(size_t) + sizeof(int)) && "Test heap has been allocated");
  
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
  testing("Basic deallocation");

  // Check sbrk()
  
  // Allocate 4 ints on the heap in separate calls to malloc

  // Deallocate the second and the fourth

  // Check the free list

  pass();
}

void
test_allocation_after_deallocation()
{
  testing("Allocation after deallocation");

  // Allocate 10 ints using separate calls to malloc

  // Free two of them in the middle

  // Allocate another int using malloc

  // Ensure system break does not rise

  // Ensure the new memory location is as expected

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
  return 0;
}
