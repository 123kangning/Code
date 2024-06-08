#include <stdio.h>
#include "calc.h"
int main() {
  printf("1+2 %d\n", add(1, 2));
  int a = 2, b = 4;
  swap(&a,&b);
  printf("%d %d\n",a,b);
  return 0;
}