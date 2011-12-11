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
  inArray[0].iov_base = malloc(sizeof(data1));
  inArray[0].iov_len = sizeof(data1);

  inArray[1].iov_base = malloc(sizeof(data2));
  inArray[1].iov_len = sizeof(data2);

  inArray[2].iov_base = malloc(sizeof(data3));
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

  // Free stuff up
  free(inArray[0].iov_base);
  free(inArray[1].iov_base);
  free(inArray[2].iov_base);
  
}

static void
test_my_writev()
{
  
  struct iovec arr[3];
  int tmp;
  char template[] = "/tmp/kerriskch5_XXXXXX";
  size_t total_bytes;
  ssize_t bytes_written, bytes_read;
  void *buff;
  
  char data1[12] = "Hello world!";
  int data2[4] = {1, 2, 4, 523};
  long data3[4] = {213L, 2132L, 2131124123L, 2311352322213L};
  
  // Create a bunch of iovec structs with data
  arr[0].iov_base = data1;
  arr[0].iov_len = sizeof(data1);
  arr[1].iov_base = data2;
  arr[1].iov_len = sizeof(data2);
  arr[2].iov_base = data3;
  arr[2].iov_len = sizeof(data3);
  total_bytes = sizeof(data1) + sizeof(data2) + sizeof(data3);

  // Create a temp file
  tmp = mkstemp(template);
  if (tmp == -1)
    errExit("mkstemp");

  // Use my_writev to write the data to the temp file
  bytes_written = my_writev(tmp, arr, 3);
  if (bytes_written == -1)
    errExit("my_writev");
  assert(bytes_written == total_bytes && "all bytes were not written!");

  // Change offset to 0 and read the entire contents of the file into one array
  if (lseek(tmp, 0, SEEK_SET) == -1)
    errExit("lseek");
  buff = malloc(total_bytes);
  bytes_read = read(tmp, buff, total_bytes);
  if (bytes_read == -1)
    errExit("read");
  assert(total_bytes == bytes_read && "all bytes could not be read back");

  // Check the iovec structs and verify the data in the file is as expected
  assert(memcmp(arr[0].iov_base, buff                                , arr[0].iov_len) == 0 && "values weren't written correctly [0]");
  assert(memcmp(arr[1].iov_base, (buff+arr[0].iov_len)               , arr[1].iov_len) == 0 && "values weren't written correctly [1]");
  assert(memcmp(arr[2].iov_base, (buff+arr[1].iov_len+arr[0].iov_len), arr[2].iov_len) == 0 && "values weren't written correctly [2]");

  // Delete/close the temp file and free the buffers and constructs
  free(buff);
  unlink(template);
  if (close(tmp) == -1)
    errExit("close");

}

int
main(int argc, char **argv)
{
  test_count_bytes_to_read();
  test_my_readv();
  test_my_writev();
  return 0;
}



