/*
 * simple pipe test, create a pipe, wirte to it and
 * then read from it a new buffer, and echo what was read
 */

#include "tests/lib.h"

int main(void)
{
  int fid;
  int len = 32;
  char buffer[len];

  fid = syscall_open("[pipe]test");

  // read one time
  syscall_seek(fid,0);
  syscall_read(fid,buffer,len);
  printf("R1 %s \n",buffer);
  
  //read again
  syscall_seek(fid,0);
  syscall_read(fid,buffer,len);
  printf("R2 %s \n",buffer);

  //read again
  syscall_seek(fid,0);
  syscall_read(fid,buffer,len);
  printf("R3 %s \n",buffer);

  //read again
  syscall_seek(fid,0);
  syscall_read(fid,buffer,len);
  printf("R4 %s \n",buffer);

  return 0;
}
