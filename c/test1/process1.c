#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  int i;
  for (i = 0; i < 2; i++) {
    fork();
    printf("-");
  }
   wait(NULL);
   wait(NULL);
  return 0;
}
// int pid = fork();
// if (pid > 0) {
//   printf("fa=%d,son=%d,i=%d | ", getpid(), pid, i);
// } else {
//   printf("son=%d,i=%d | ", getpid(), i);
// }
// fflush(stdout);