/*
 *Create a pipe open it, wirte to it, delete it and try to read from it
 */

#include "tests/lib.h"

int main(void)
{
  int ret, fid;
  int len = 32;
  char buffer[32] = "Hello pipes";
  char buffer2[32];
  ret = syscall_create("[pipe]test",512);
  printf("Created pipe with ret %d\n",ret);

  fid = syscall_open("[pipe]test");
  printf("Fid was %d\n", fid);
  
  ret = syscall_write(fid,buffer,len);
  printf("write ret was %d\n", ret);
  
  syscall_delete("[pipe]test");  

  ret = syscall_read(fid,buffer2,len);
  printf("Buffer2 says %s \n",buffer2);
  
  printf("Ret: %d\n",ret);
  return ret;
}
