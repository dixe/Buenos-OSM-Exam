/*
 * simple pipe test, create a pipe, wirte to it and
 * then read from it a new buffer, and echo what was read
 */

#include "tests/lib.h"

int main(void)
{
  int fid;
  int len = 32;  
  char buffer1[32] = "Hello this is first message";
  char buffer2[32] = "Hello second message is up";

  fid = syscall_open("[pipe]test");
  //  printf("Fid from read is %d\n", fid);
 
  // write one time
  syscall_write(fid,buffer1,len);
  //  printf("W1\n");
  
  // write again
  syscall_write(fid,buffer2,len);
  //  printf("W2\n");

  return 0;
}
