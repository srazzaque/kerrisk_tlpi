#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <error_functions.h>
#include <unistd.h>

/**
 * Exercise 5-5
 */

int
main(int argc, char *argv[])
{
  
  char data[20] = "yo yo wattup?";
  int os, os_d, fd, duped;

  printf("Opening a file\n");
  fd = open( argv[1], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
  if (fd == -1)
    errExit("open");
  duped = dup(fd);

  os = lseek(fd, 0, SEEK_END);
  if (os == -1)
    errExit("lseek");

  os_d = lseek(duped, 0, SEEK_END);
  if (os_d == -1)
    errExit("lseek");

  printf("Current offset in fd: %ld\n", (long) os);
  printf("Current offset in duped: %ld\n", (long) os_d);

  printf("Writing to file: %s\n", data);
  int res = write(fd, data, (size_t)20);
  if (res == -1)
    errExit("write");

  os = lseek(fd, 0, SEEK_END);
  if (os == -1)
    errExit("lseek");

  os_d = lseek(duped, 0, SEEK_END);
  if (os_d == -1)
    errExit("lseek");

  printf("Current offset in fd: %ld\n", (long) os);
  printf("Current offset in duped: %ld\n", (long) os_d);

  printf("Closing file\n");
  if (close(fd) == -1)
    errExit("close");
  if (close(duped) == -1)
    errExit("close");

  exit(EXIT_SUCCESS);
  
}
