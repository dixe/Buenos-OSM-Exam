/*
 * Userland exec test
 * Run with one cpu to see the effect
 */

#include "tests/lib.h"

static const char prog0[] = "[arkimedes]t0"; /* The program to start. */
static const char prog1[] = "[arkimedes]t1"; /* The program to start. */


int main(void)
{
  uint32_t child0, child1;
  int ret1,ret2;

  child0 = syscall_exec(prog0,100);
  
  child1 = syscall_exec(prog1,200);

  ret1 = syscall_join(child1);

  ret2 = syscall_join(child0);
  printf("Child0 joined with status: %d, child1 joined with %d\n", ret2,ret1);

  child0 = syscall_exec(prog0,400);
 
  child1 = syscall_exec(prog1,200);

  ret1 = syscall_join(child1);

  ret2 = syscall_join(child0);
  printf("Child0 joined with status: %d, child1 joined with %d\n", ret2,ret1);
 
  syscall_halt();
  return 0;
}
