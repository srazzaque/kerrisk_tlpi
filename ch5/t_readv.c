#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <tlpi_hdr.h>

#define STR_SIZE 100


/*
Just for reference:

struct iovec {
  void *iov_base; // Start address of buffer
  size_t iov_len; // Number of bytes to transfer to/from this buffer
};
*/

int
main(int argc, char *argv[])
{
  int fd;
  struct iovec iov[3];
  struct stat myStruct; /* First Buffer - expecting serialized data... */
  int x; /* Second Buffer */
  char str[STR_SIZE]; /* Third buffer */
  ssize_t numRead, totRequired;
  
  if (argc != 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s file\n", argv[0]);

  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    errExit("open");

  /* Working out the required value for totRequired and setting up
     the structure for the scatter input */

  totRequired = 0;
  
  iov[0].iov_base = &myStruct;
  iov[0].iov_len = sizeof(struct stat);
  totRequired += iov[0].iov_len;

  iov[1].iov_base = &x;
  iov[1].iov_len = sizeof(x);
  totRequired += iov[1].iov_len;

  iov[2].iov_base = str;
  iov[2].iov_len = STR_SIZE;
  totRequired += iov[2].iov_len;

  numRead = readv(fd, iov, 3);
  if (numRead == -1)
    errExit("readv");
  
  if (numRead < totRequired)
    printf("Read fewer bytes than requested");

  printf("Total bytes requested: %ld; bytes read: %ld\n",
         (long) totRequired,
         (long) numRead);
  
  exit(EXIT_SUCCESS);
  
  
}
