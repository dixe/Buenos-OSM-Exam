/*
 * simple pipe test, create pipe wirte and then read into
 * a new buffer
 */

#include "tests/lib.h"

int main(void)
{
  int ret, fid = 0;
  int len = 32;
  char buffer[32] = "Hello w";
  char buffer2[32];
  syscall_create("[pipe]test",512);

  fid = syscall_open("[pipe]test");
  printf("Fid was %d\n", fid);
  
  ret = syscall_write(fid,buffer,len);
  printf("write ret was %d\n", ret);
  
  ret = syscall_read(fid,buffer2,len);
  printf("Buffer2 says %s \n",buffer2);

  printf("Ret: %d\n",ret);
  return ret;
}
