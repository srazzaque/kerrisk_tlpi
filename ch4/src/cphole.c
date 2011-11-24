#include "tlpi_hdr.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUF_SIZ
#define BUF_SIZ 1024
#endif

int
main(int argc, char *argv[])
{

  int fdSrc, fdDst, readRes;
  char buf[BUF_SIZ];

  if (argc != 3 || strcmp(argv[0], "--help") == 0)
    usageErr("%s <file1> <file2>", argv[0]);

  // ---------------------------------------
  // Opening files
  // ---------------------------------------
  fdSrc = open(argv[1], O_RDONLY);
  if (fdSrc == -1)
    errExit("Opening source file");

  fdDst = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if (fdDst == -1)
    errExit("Opening destination file");

  // ---------------------------------------
  // MAIN PROGRAM
  // ---------------------------------------

  while ((readRes = read(fdSrc, buf, (size_t)BUF_SIZ)) != -1) {
    if (write(fdDst, buf, readRes) == -1)
      errExit("write to dstfile");
    if (readRes < BUF_SIZ)
      break;
  }

  // ---------------------------------------
  // Closing files and exit
  // ---------------------------------------
  if (close(fdSrc) == -1)
    errExit("Closing source file");

  if (close(fdDst) == -1)
    errExit("Closing destination file");

  exit(EXIT_SUCCESS);


}
