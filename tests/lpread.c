/*
 * Long pipes test, try to write 512 bytes
 */

#include "tests/lib.h"

int main(void)
{
  int fid;
  int len = 512;
  int len2 = 0;
  char buffer[512];

  fid = syscall_open("[pipe]test");
  printf("Fid was %d\n", fid);
  
  
  // to read from buffer, until we read 0 bytes the string, use a loop
  while(len2 < len){
    // write to the buffer, with offset len2, until all was written
    syscall_seek(fid,0);
    len2 += syscall_read(fid,buffer + len2,len);

    printf("read ret was %d\n", len2);
  }

  // print the length of the string in buffer
  printf("Length of string is %d\n", strlen(buffer));
  return 0;
}
