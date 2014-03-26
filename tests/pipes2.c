/*
 * simple pipe test, create a pipe, wirte to it and
 * then read from it a new buffer, and echo what was read
 */

#include "tests/lib.h"

static const char read[] = "[arkimedes]p2read"; /* The program to start. */
static const char write[] = "[arkimedes]p2write"; /* The program to start. */

int main(void)
{
  int ret1,ret2, childR, childW;
    
  // create the test pipe
  ret1 = syscall_create("[pipe]test",512);
  printf("Created pipe with ret %d\n",ret1);
  if(ret1){ // error
    printf("Cound not created pipe, returned %d\nclosing program \n",ret1);
    return 1;
  }
  
  // start read and write processes
  childW = syscall_exec(read,0);

  childR = syscall_exec(write,0);

  // join then
  ret1 = syscall_join(childR);
  ret2 = syscall_join(childW);
  printf("ChildR joined with status: %d, childW joined with %d\n", ret1, ret2);

  return 0;
}
