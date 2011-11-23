#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
  char c;
  int opt, append_mode, fd_out;
  // Even though 'opt' will be representing characters, the getopt() function
  // may return a negative value, and not all implementations of 'char' are signed.

  while ((opt = getopt(argc, argv, "a")) != -1) {
    switch(opt) {
    case 'a':
      append_mode = 1;
      break;
    default:
      fatal("An invalid option was specified.");
    }
  }

  // Currently, the file name can only be the last option.
  if (!(argc == 2 && append_mode == 0) && !(argc == 3 && append_mode == 1))
    usageErr("%s [-a] <filename>\n", argv[0]);


  int write_options = O_WRONLY | O_CREAT;
  if (append_mode == 1) {
    write_options = write_options | O_APPEND;
  } else {
    write_options = write_options | O_TRUNC;
  }

  fd_out = open(argv[argc-1], write_options, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  if (fd_out == -1)
    errExit("open");
  
  int len = 20;
  char buf[len];
  int res;
  while ((res = read(STDIN_FILENO, buf, (size_t)len)) != -1) {
    write(fd_out, buf, (size_t)len);
    write(STDOUT_FILENO, buf, (size_t)len);
  }

  if (res == -1)
    errExit("read");

  if (close(fd_out) == -1)
    errExit("close");
  exit(EXIT_SUCCESS);
  
}
