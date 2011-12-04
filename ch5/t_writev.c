#include <sys/uio.h>
#include <tlpi_hdr.h>
#include <stdio.h>
#include "my_structs.h"
#include <string.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{

  struct asl *deap;
  struct asl *stela;
  struct iovec elements[2];
  int fd;
  ssize_t writeReturn;

  if (argc != 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s <file to write to>", argv[0]);

  fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC);
  if (fd == -1)
    errExit("open");

  printf("Example usage of writev - which performs 'gather output'\n");

  deap = malloc( sizeof(struct asl) );
  stela = malloc( sizeof(struct asl) );

  printf("Creating the struct asl items...\n");

  deap->age = 25;
  deap->sex = 'M';
  strcpy(deap->location, "Sydney");

  stela->age = 27;
  stela->sex = 'F';
  strcpy(stela->location, "Sydney");

  // Lets write the above two to a file using Gather Output!
  
  printf("Done...\nNow lets write them out to file '%s' using writev()..\n", argv[1]);

  elements[0].iov_base = deap;
  elements[0].iov_len = sizeof(struct asl);
  elements[1].iov_base = stela;
  elements[1].iov_len = sizeof(struct asl);

  writeReturn = writev(fd, elements, 2);
  if (writeReturn == -1)
    errExit("writev");

  printf("Done! Awesome!");
  
  free(deap);
  free(stela);
  if (close(fd) == -1)
    errExit("close");

  exit(0);
}
