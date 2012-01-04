/*
 * Exercise 6-3
 * Implementing setenv() and unsetenv() using only getenv() and putenv()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
my_unsetenv(const char *name)
{
  int ret=0;

  ret = putenv((char *)name);
  if (ret != 0)
    return ret;
 
  if (getenv(name) == NULL)
    return ret;
  else
    my_unsetenv((const char *)name);

  // We should never get here...
  return -99;
}

int
my_setenv(const char *name, const char *value, int overwrite)
{
  char *str, *p1;
  const char *p2;
  int ret=0;

  str = (char *)malloc( (size_t)(strlen(name) + strlen(value) + 2) ); // Add 1 for '=' and 1 for '\0'

  // Create the 'name=value' string
  p1 = str; p2 = name;
  while ((*p1++ = *p2++) != '\0') { } // Copy first string
  *--p1 = '='; // Decrement to change that last '\0' to an '='
  p1++; // Re-increment
  p2 = value;
  while ((*p1++ = *p2++) != '\0') { } // Copy second string
  //  printf("New string: %s\n", str);

  if (getenv(name) != NULL) {
    if (overwrite != 0) {
      my_unsetenv(name);
      ret = putenv(str);
    }
  } else {
    ret = putenv(str);
  }
  
  return ret;
}


int
main(int argc, char *argv[])
{
  
  //  const char *x = "hello";
  //  printf("sizeof(x) = %ld, strlen(x) = %ld\n", (long)sizeof(x), (long)strlen(x));
  
  printf("Setting 'bob' to 'builder'\n");

  if (my_setenv("bob", "builder", 0) != 0) {
    printf("Error setting 'bob' to 'builder'!\n");
    exit(1);
  }
  
  printf("Retrieving value - bob: %s\n", getenv("bob"));

  printf("Now unsetting 'bob'\n");
  
  if (my_unsetenv("bob") != 0) {
    printf("Error unsetting 'bob'!\n");
    exit(1);
  }

  printf("Retrieving value - bob: %s\n", getenv("bob"));

  exit(EXIT_SUCCESS);
    
}
