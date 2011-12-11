#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>
#include <tlpi_hdr.h>
#include <string.h>

#ifndef MY_READV_WRITEV_FUNCTIONS
#define MY_READV_WRITEV_FUNCTIONS
ssize_t my_readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t my_writev(int fd, const struct iovec *iov, int iovcnt);
#endif
