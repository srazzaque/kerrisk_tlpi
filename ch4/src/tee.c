#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZ
#define BUF_SIZ 20
#endif

void close_and_exit() {
  
}

/*
 * Returns 0 if EOF is detected. 1 otherwise
 */
int
check_for_eof( const char *buf, int size ) {

  if (size == 0)
    return 1;
  else {
    int i=0;
    for (i=0; i < size; i++) {
      if (buf[i] == EOF)
        return 0;
    }
    return 1;
  }

}

int
main(int argc, char *argv[])
{

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
  
  char buf[BUF_SIZ];
  int res;
  while ((res = read(STDIN_FILENO, buf, (size_t)BUF_SIZ)) != -1) {
    if (write(fd_out, buf, (size_t)res) == -1)
      errExit("write to outfile");

    if (write(STDOUT_FILENO, buf, (size_t)res) == -1)
      errExit("write to stdout");

    if (!check_for_eof(buf, res))
      break;
  }

  if (res == -1)
    errExit("read");

  if (close(fd_out) == -1)
    errExit("close");
  exit(EXIT_SUCCESS);
  
}
