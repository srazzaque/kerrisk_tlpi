#include <unistd.h>
#include <stdio.h>
#include <tlpi_hdr.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
  
  int fd, options;
  off_t num_bytes;
  int i = 0;
  
  if ((argc != 3 && argc != 4) || strcmp(argv[1], "--help") == 0)
    usageErr("%s filename num-bytes [x]\n", argv[0]);

  // Default 'open' options
  options = O_CREAT | O_APPEND | O_WRONLY;

  // Remove 'O_APPEND' if 'x' is specified
  if (argc == 4 && strcmp(argv[3], "x") == 0)
    options = options ^ O_APPEND;

  // Write data according to the number of bytes specified
  num_bytes = (off_t)atoll(argv[2]);
  
  
  fd = open(argv[1], options, S_IRUSR | S_IWUSR);
  if (fd == -1)
    errExit("open");

  while (i++ < num_bytes) {

    if ((options & O_APPEND) == O_APPEND)
      lseek(fd, 0, SEEK_END);

    if (write(fd, "a", 1) == -1)
      errExit("write");

  }

  if (close(fd) == -1)
    errExit("close");

  exit(EXIT_SUCCESS);
}
