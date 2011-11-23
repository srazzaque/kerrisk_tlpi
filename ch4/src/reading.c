#include <sys/stat.h>
#include <fcntl.h>
#include <tlpi_hdr.h>
#include <error_functions.h>

#ifndef BUF_SIZ
#define BUF_SIZ 1024
#endif

#define MAX_READ 20

int main(int argc, char *argv[]) {
  
  char buffer[MAX_READ + 1];
  ssize_t numRead;

  char msg[] = "Give me some input: ";
  if (write(STDOUT_FILENO, msg, (size_t)20) == -1)
    errExit("write");
  // In a similar manner to read(), write() will simply write bytes. It cares
  // not about the '\0' that may or may not be in the array somewhere. (hence
  // the precise size given above).

  numRead = read(STDIN_FILENO, buffer, MAX_READ);
  if (numRead == -1)
    errExit("read");

  // Need to add this to the end to avoid garbage being printed out
  buffer[numRead] = '\0';

  printf("The input data was: %s\n", buffer);

  exit(EXIT_SUCCESS);
  
}
