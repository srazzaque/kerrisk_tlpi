#include "my_readv_writev_functions.h"

static size_t count_bytes_to_read(const struct iovec *iov, int iovcnt);

ssize_t
my_readv(int fd, const struct iovec *iov, int iovcnt)
{
  size_t bytes_to_read, total_copied, bytes_to_copy;
  ssize_t bytes_read;
  int i, quitloop;
  void *buff;

  // How many bytes do we need to read in total?
  bytes_to_read = count_bytes_to_read(iov, iovcnt);

  // Create a buffer large enough to hold the above
  buff = malloc(bytes_to_read);

  // Perform the read() - return prematurely if == -1
  bytes_read = read(fd, buff, bytes_to_read);
  if (bytes_read == -1)
    return bytes_read;

  // Copy from the buffers to the memory addresses pointed to in the iovec's
  for (i = 0, quitloop = 0, total_copied = 0; i < iovcnt && quitloop == 0; i++) {

    bytes_to_copy = (iov+i)->iov_len;
    if ((bytes_to_copy + total_copied) > bytes_read) {
      bytes_to_copy = bytes_read - total_copied;
      quitloop = 1; // Exit the loop after this copy.
    }

    memcpy((iov+i)->iov_base, (buff+total_copied), bytes_to_copy);
    total_copied += (iov+i)->iov_len;
  }

  // free the buffer
  free(buff);

  // Return total bytes read.
  return total_copied;

}


ssize_t
my_writev(int fd, const struct iovec *iov, int iovcnt)
{
  
  size_t total_bytes_to_write, j;
  ssize_t bytes_written;
  void *buff;
  int i;
  
  // Work out how many bytes we need and create a buffer to store everything from all the struct iov
  // objects
  total_bytes_to_write = count_bytes_to_read(iov, iovcnt);
  buff = malloc(total_bytes_to_write);

  // Copy everything from the structs into the above buffer
  for (i=0, j=0; i < iovcnt; i++) {
    if (memcpy((buff+j), (iov+i)->iov_base, (iov+i)->iov_len) == NULL)
      errExit("memcpy");
    j += (iov+i)->iov_len;
  }

  // Perform the write()
  bytes_written = write(fd, buff, total_bytes_to_write);
  if (bytes_written == -1 || bytes_written != total_bytes_to_write)
    errExit("write");
  
  // free() the buffer
  free(buff);

  // Return total bytes 
  return bytes_written;
}


size_t
count_bytes_to_read(const struct iovec *iov, int iovcnt)
{
  int i = 0;
  size_t total = 0;
  while (i < iovcnt) {
    total = total + (iov+i)->iov_len;
    i++;
  }
  return total;
}
