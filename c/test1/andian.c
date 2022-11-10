#include <stdio.h>
#include <stdlib.h>
int main(void) {
  int row, col;
  scanf("%d %d", &row, &col);
  int **num = (int **)calloc(sizeof(int *), row);
  for (int i = 0; i < row; i++) {
    num[i] = (int *)calloc(sizeof(int), col);
    for (int j = 0; j < col; j++) {
      scanf("%d", &num[i][j]);
    }
  }
  int NONE = 1;
  for (int i = 0; i < row; i++) {
    int min = 0;
    for (int j = 0; j < col; j++) {
      if (num[i][j] < num[i][min]) {
        min = j; // max是列
      }
    }
    // printf("max = %d , i = %d\n", max, i);
    for (int k = 0; k < col; k++) {
      if (num[i][min] == num[i][k]) {
        // printf("val = %d , k = %d, i = %d\n", num[max][i], k, i);
        int sign = 1;
        for (int j = 0; j < row; j++) {
          // if(j==i)continue;
          if (num[j][k] > num[i][k]) {
            sign = 0;
            break;
          }
        }
        if (sign) {
          NONE = 0;
          printf("(%d,%d,%d)", i + 1, k + 1, num[i][k]);
        }
      }
    }
  }
  if (NONE)
    printf("NONE");
  return 0;
}