/*
 * Userland helloworld
 */

#include "tests/lib.h"


int main(void)
{

  int t0, t1;
  int i, a=0;
  t0 = syscall_getclock();
  //create a big loop, so there will be a some thread switch
  for(i =0; i< 100000; i++){
    a = a + 2;
  }
  a = 0;
  for(i =0; i< 100000; i++){
    a = a + 2;
  }
  puts("Done t0\n");

  t1 = syscall_getclock();
 
  syscall_exit(t1-t0);
  return t1-t0;
}
