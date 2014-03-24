#include "tests/lib.h"

int main(){

  int t1,t2;

  t1 = syscall_getclock();

  printf("Time is %d \n",t1);
 
  t2 = syscall_getclock();

  printf("Time 2 is %d\n",t2);


  printf("Difference is %d \n",t2 - t1);

  syscall_halt();
  return 0;
}
