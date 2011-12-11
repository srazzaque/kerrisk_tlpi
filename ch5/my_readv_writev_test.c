#include "my_readv_writev_functions.c" // Including the '.c' file to get access to the static functions
#include <assert.h>
#include <stdlib.h>

static void
test_count_bytes_to_read()
{
  struct iovec iovs[3];
  size_t a, b, c;
  
  a = 34;
  b = 22;
  c = 234;

  iovs[0].iov_len = (size_t)a;
  iovs[1].iov_len = (size_t)b;
  iovs[2].iov_len = (size_t)c;

  assert(count_bytes_to_read(iovs, 3) == (a + b + c) && "test_count_bytes_to_read()");

}

static void
test_my_readv()
{
  int tmp;
  char template[] = "/tmp/kerriskch5XXXXXX";
  struct iovec inArray[3];
  ssize_t bytes_read;

  char data1[6] = "hello!";
  int data2[2] = {1, 2};
  long data3[3] = {2L, 3892893783L, 2903L};

  // Create a temp file using one of the methods prescribed in 5.12
  tmp = mkstemp(template);
  if (tmp == -1)
    errExit("mkstemp()");

  // Fill it up with the data from above
  if (write(tmp, data1, sizeof(data1)) == -1)
    errExit("write");
  if (write(tmp, data2, sizeof(data2)) == -1)
    errExit("write");
  if (write(tmp, data3, sizeof(data3)) == -1)
    errExit("write");

  // Initialise our iovec array
  inArray[0].iov_base = (void *)malloc(sizeof(data1));
  inArray[0].iov_len = sizeof(data1);

  inArray[1].iov_base = (void *)malloc(sizeof(data2));
  inArray[1].iov_len = sizeof(data2);

  inArray[2].iov_base = (void *)malloc(sizeof(data3));
  inArray[2].iov_len = sizeof(data3);
  
  // lseek() on the temp file to set offset to 0
  if (lseek(tmp, 0, SEEK_SET) == -1)
    errExit("lseek()");

  // Perform my_readv()
  bytes_read = my_readv(tmp, inArray, 3);
  if (bytes_read == -1)
    errExit("my_readv");
  
  // Verify the return val
  assert( bytes_read == (sizeof(data1) + sizeof(data2) + sizeof(data3)) && "number of bytes read was not correct");

  // Verify the contents
  assert( memcmp(data1, inArray[0].iov_base, sizeof(data1)) == 0 && "contents of data1 were not as expected");
  assert( memcmp(data2, inArray[1].iov_base, sizeof(data2)) == 0 && "contents of data2 were not as expected");
  assert( memcmp(data3, inArray[2].iov_base, sizeof(data3)) == 0 && "contents of data3 were not as expected");

  // Close the temp file
  unlink(template);
  if (close(tmp) == -1)
    errExit("close");
}

int
main(int argc, char **argv)
{
  test_count_bytes_to_read();
  test_my_readv();
  return 0;
}
