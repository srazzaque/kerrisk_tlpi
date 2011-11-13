#include <stdio.h>
#include <stdlib.h>
#include <gnu/libc-version.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "my_header.h"

int main() {
  
  printf("Using gnu_get_lib_version(): The glibc version is: %s\n", gnu_get_libc_version());
  
  char *p;
  size_t max_size = 1024;
  p = (char *)malloc(max_size);
  confstr(_CS_GNU_LIBC_VERSION, p, (size_t)1024 );
  printf("Using confstr(): The glibc version is: %s\n", p);

  printf("Max size of 'p' is %ld", (long)max_size);

  newline();
  printf("OK, now for some error handling....\n");
  error_handling();

  newline();
  printf("Gangsta! Now for some system data type printing!");
  printing_system_data_types();
  

  free(p);
  return 0;

}

void error_handling() {

  char *fileName = (char *)malloc( (size_t)1024 );

  printf("Give me a file name: ");
  scanf("%s", fileName);
  printf("You provided file name: %s\n", fileName);

  printf("I'm going to try and open this file");
  int retval = open( fileName, O_RDONLY );

  if ( retval == -1 ) {
    perror("open");
  } else {
    printf("File opened successfully :)\n");
    printf("I'm now going to try and close this file\n");
    if (close( retval ) == -1) {
      perror("close");
    } else {
      printf("File closed successfully :)\n");
    }
  }
  
  free(fileName);
  return;
}


void printing_system_data_types() {
}
