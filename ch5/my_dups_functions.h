#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#ifndef MY_DUPS
#define MY_DUPS
int my_dup(int oldfd);
int my_dup2(int oldfd, int newfd);
#endif
