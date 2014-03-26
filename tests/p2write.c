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
  char buffer3[32] = "Third message comming your way";
  char buffer4[32] = "Last but not leat, message four";

  fid = syscall_open("[pipe]test");
  //  printf("Fid from read is %d\n", fid);
 
  // write one time
  syscall_seek(fid,0);
  syscall_write(fid,buffer1,len);
  
  // write again
  syscall_seek(fid,0);
  syscall_write(fid,buffer2,len);

  // write again
  syscall_seek(fid,0);
  syscall_write(fid,buffer3,len);

  // write again
  syscall_seek(fid,0);
  syscall_write(fid,buffer4,len);


  return 0;
}
