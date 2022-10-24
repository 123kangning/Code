#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  unsigned char a = 4 | 7;//a=111
  a <<= 3;//a=111000
  unsigned char b = 5 & 7;//b=101
  b >>= 3;//b=0
  unsigned char c = 6 ^ 7;//c=1
  c = ~c;//c=1111 1110
  short d = (a ^ c) << 3;//d=110 0011 0000
  int e = d & 0x51;//e=1 0000
  printf("%d %d %d %d %d\n", a, b, c, d, e);
  return 0;
}
