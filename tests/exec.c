/*
 * Userland exec test
 * Run with one cpu to see the effect
 */

#include "tests/lib.h"

static const char prog0[] = "[arkimedes]t0"; /* The program to start. */
static const char prog1[] = "[arkimedes]t1"; /* The program to start. */
static const char prog2[] = "[arkimedes]t2"; /* The program to start. */
static const char prog3[] = "[arkimedes]t3"; /* The program to start. */



int main(void)
{
  uint32_t child0, child1,child2,child3;
  int ret1,ret2;

  child0 = syscall_exec(prog0,1000);
  
  child1 = syscall_exec(prog1,2020);


  child2 = syscall_exec(prog2,400);
 
  child3 = syscall_exec(prog3,200);

  ret1 = syscall_join(child0);

  ret2 = syscall_join(child1);
  printf("Child0 joined with status: %d, child1 joined with %d\n", ret1, ret2);

  ret1 = syscall_join(child2);

  ret2 = syscall_join(child3);
  printf("Child2 joined with status: %d, child2 joined with %d\n", ret1,ret2);
 
  syscall_halt();
  return 0;
}
