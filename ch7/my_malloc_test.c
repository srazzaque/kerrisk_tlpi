#include "my_malloc.c" // NOTE: this is NOT xxx.h on purpose.
#include <assert.h>
#include <stdio.h>

static void
pass()
{
  printf("[PASS]\n");
}

static void
testing(char *item)
{
  printf("Testing %s: ", item);
}

void
test_basic_allocation()
{
  testing("Basic allocation");

  // Check sbrk()

  // Allocate an int on the heap

  // Ensure that sbrk(0) has risen by sizeof(size_t) + sizeof(int)

  // Test some basic pointer arithmetic

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
