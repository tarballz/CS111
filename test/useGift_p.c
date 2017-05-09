#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    exit(-1);
  }
  int forkRes = fork();
  int res;
  if (forkRes == 0) {
    // Child
    printf("i errno %d\n", errno);
    res = syscall(548, argv[1], argv[2]);
    printf("c res %d\n", res);
    printf("c errno %d\n", errno);
  } else {
    // Parent
    int status = -1;
    printf("waiting\n");
    waitpid(forkRes, &status, WEXITED);
    printf("done waiting\n");
    //res = syscall(548, 0, 0);
    //printf("p res %d\n", res);
    //printf("p errno %d\n", errno);    
  }
  printf("returning\n");
  return 0;
}
