/*
 * Userland exec test
 */

#include "tests/lib.h"

static const char prog0[] = "[arkimedes]exec"; /* The program to start. */
static const char prog1[] = "[arkimedes]exec"; /* The program to start. */


int main(void)
{
  uint32_t child0, child1;
 
  child0 = syscall_exec(prog0,200);
 
  child1 = syscall_exec(prog1,200);

  syscall_join(child1);

  syscall_join(child0);
 
  syscall_halt();
  return 0;
}
