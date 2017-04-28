#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
       #include <errno.h>



int main() {
  int res = syscall(548, 1, 2);
  //gift(5, 100);
  printf("res %d\n", res);
  printf("errno %d\n", errno);
  return 0;
}
