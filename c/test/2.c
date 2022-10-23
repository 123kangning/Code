#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PGROUNDUP(sz) (((sz) + 4096 - 1) & ~(4096 - 1))
int main(void) {
  char str[100] = "\0";
  char *add = "12345";
  memcpy(str, add, 100);
  printf("len = %d\n", strlen(str));
  strcat(str, "qq");
  printf("%s", str);

  return 0;
}
// 00000fff
// 10=ln1024