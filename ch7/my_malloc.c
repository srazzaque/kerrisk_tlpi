#include "my_malloc.h"
#include <unistd.h> // For sbrk()

struct mblock {
  size_t len;
  struct mblock *prev; // Pointer to previous free block
  struct mblock *next; // Pointer to next free block
};

// Pointer to the head of the list
static struct mblock *head;

void *
malloc(size_t size)
{
  
  struct mblock *last = NULL;
  struct mblock *tmp = NULL;

  // First, check the free list (if it exists), and if anything with
  // sufficient size is available just return that block.
  if (head != NULL) {
    for( tmp = head; tmp != NULL ; tmp = tmp->next ) {

      if (tmp->len > size) {
      
	// Previous 'next' must be changed to 'tmp.next'
	(tmp->prev)->next = tmp->next;

	// Next 'prev' (if not null) must be changed to 'tmp.prev'
	if (tmp->next != NULL) {
	  (tmp->next)->prev = tmp->prev;
	}

	// Return a pointer to tmp.prev
	return (void *)(tmp->prev);
      }

      last = tmp;
    }
  }

  // Increase the system break by the amount specified,
  tmp = (struct mblock *)sbrk((intptr_t)(size + sizeof(size_t)));
  tmp->len = size;
  if (last != NULL) {
    last->next = tmp;
  }

  // Return the memory just past the len
  tmp = &(tmp->prev);
  return tmp;

}

void
free(void *ptr)
{
}
                                                      
