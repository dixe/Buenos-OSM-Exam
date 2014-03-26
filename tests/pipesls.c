/*
 * Create two pipies and list them, using filecount and file syscall
 */

#include "tests/lib.h"

int main(void)
{
  int ret, fcount;
  int i, len = 32;
  char file[len]; // buffer to hold filenames

  ret = syscall_create("[pipe]test",512);
  printf("Created pipe with ret %d\n",ret);

  ret = syscall_create("[pipe]test2",512);
  printf("Created pipe 2 with ret %d\n",ret);
  
  fcount = syscall_filecount("[pipe]");
  printf("Number of pipes %d\n",fcount);
  
  for(i=0; i< fcount; i++){
    syscall_file("[pipe]",i , file);
    printf("File %d on pipes is %s\n",i, file);
  }
  
  return 0;
}
