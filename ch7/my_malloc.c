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

      if (tmp->len >= size) {
      
	// Previous 'next' must be changed to 'tmp.next'
	if (tmp != head) {

	  // i.e. if tmp is in the middle of the list somewhere, we
	  // need to change the linkages on the previous and next
	  // elements

	  (tmp->prev)->next = tmp->next;

	  // Next 'prev' (if not null) must be changed to 'tmp.prev'
	  // if it isn't null
	  if (tmp->next != NULL) {
	    (tmp->next)->prev = tmp->prev;
	  }

	} else {

	  // We're at the head of the list
	  head = tmp->next;
	  tmp->prev = NULL;
	}

	// Return the address of tmp->prev
	return &(tmp->prev);
      }

      last = tmp;
    }
  }

  // Increase the system break by the amount specified,
  intptr_t size_requested = (size + sizeof(size_t));
  intptr_t size_required = size_requested > sizeof(struct mblock) ? size_requested : sizeof(struct mblock);
  tmp = (struct mblock *)sbrk(size_required);
  tmp->len = size;
  if (last != NULL) {
    last->next = tmp;
  }

  // Return the memory just past the len (i.e. address of tmp->prev)
  tmp = &(tmp->prev);
  return (void *)tmp;

}

void
free(void *ptr)
{
  struct mblock *tmp, *tmp2;

  // Get a pointer to the mblock that this ptr falls within, and set the 'next' member
  tmp = ptr - sizeof(size_t);
  tmp->next = NULL;
  
  // Add to the end of the free list if the free list already exists, else
  // create the free list
  if (head != NULL) {
    tmp2 = head;
    while (tmp2->next != NULL) {
      tmp2 = tmp2->next;
    }
    tmp2->next = tmp;
    tmp->prev = tmp2;
  } else {
    head = tmp;
  }

}
                                                      
