/*
 * Long pipes test, try to write 512 bytes
 */

#include "tests/lib.h"
static const char read[] = "[arkimedes]lpread"; /* The program to start. */

int main(void)
{
  int ret, fid;
  int i, child;
  int len = 512;
  int len2 = 0;
  char buffer[512];

  // fill the buffer with a's
  for(i=0; i < 512; i++){
    buffer[i] = 'a';
  }
  // null terminate the string
  //  buffer[512] = '\0';

  ret = syscall_create("[pipe]test",512);
  printf("Created pipe with ret %d\n",ret);

  fid = syscall_open("[pipe]test");
  printf("Fid was %d\n", fid);
  
  child = syscall_exec(read,0);
  
  // to write the string, use a loop
  while(len2<len){
    // write to the buffer, with offset len2, until all was written
    syscall_seek(fid,0);
    len2 += syscall_write(fid,buffer + len2,len);
    //printf("write ret was %d\n", len2);
  }
  ret = syscall_join(child);
  
  return ret;
}
