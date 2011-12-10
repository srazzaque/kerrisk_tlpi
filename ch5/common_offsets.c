#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <error_functions.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
  
  char data[20] = "yo yo wattup?";

  printf("Opening a file\n");
  int fd = open( argv[1], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
  if (fd == -1)
    errExit("open");

  printf("Writing: %s\n", data);
  int res = write(fd, data, (size_t)20);
  if (res == -1)
    errExit("write");

  int os = lseek(fd, 0, SEEK_END);
  if (os == -1)
    errExit("lseek");

  printf("Current offset: %ld\n", (long) os);

  printf("Waiting 5 seconds\n");
  sleep(5);

  os = lseek(fd, 0, SEEK_END);
  if (os == -1)
    errExit("lseek");

  printf("Current offset: %ld\n", (long) os);

  printf("Closing file\n");
  if (close(fd) == -1)
    errExit("close");

  exit(EXIT_SUCCESS);
  
}
