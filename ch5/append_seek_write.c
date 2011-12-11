#include <stdio.h>
#include <fcntl.h>
#include <tlpi_hdr.h>
#include <unistd.h>

/**
 * Exercise 5-2
 */

int
main(int argc, char **argv)
{

  int fd;
  off_t sk;

  if (argc != 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s <filename>\n", argv[0]);

  fd = open(argv[1], O_APPEND | O_WRONLY);
  if (fd == -1)
    errExit("open");

  sk = lseek(fd, 0, SEEK_SET);
  if (sk == -1)
    errExit("seek");

  if (write(fd, "gangsta", 7) == -1)
    errExit("write");

  if (close(fd) == -1)
    errExit("close");

  exit(EXIT_SUCCESS);
}
