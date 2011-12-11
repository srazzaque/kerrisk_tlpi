#include "my_dups_functions.h"

int
my_dup(int oldfd)
{
  return fcntl(oldfd, F_DUPFD);
}

int
my_dup2(int oldfd, int newfd)
{

  // If they are both the same, check validity of oldfd and return it straight
  // away.
  if (oldfd == newfd && fcntl(oldfd, F_GETFL) != -1)
    return oldfd;
  else {
    errno = EBADF;
    return -1;
  }
  
  // close the newfd and duplicate it straight away.
  close(newfd); // Silently ignoring any error here
  return fcntl(oldfd, F_DUPFD);
}

