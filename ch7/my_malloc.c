#include "my_malloc.h"

struct mblock {
  size_t len;
  void *prev; // Pointer to previous free block
  void *nxt; // Pointer to next free block
};

// Pointer to the head of the list
static struct mblock *head;

void *
malloc(size_t size)
{
  return NULL;
  
  // First, check the free list
}

void
free(void *ptr)
{
}
