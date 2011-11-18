#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error_functions.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  if (argc != 2)
    usageErr("%s file-to-open-in-excl\n", argv[0]);

  int fd = open( argv[0], O_EXCL | O_CREAT );

  if (fd == -1)
    errExit("open");

  printf("File was opened successfully in exclusive mode!\nClosing....\n");
  
  if (close(fd) == -1)
    errExit("close");

  exit(EXIT_SUCCESS);
  
}
