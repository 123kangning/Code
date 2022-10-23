/*汉诺塔问题解决过吗？可以用非递归的方式吗？宏函数会使用吗？
来看一个非递归的汉诺塔问题实现，体会一下它们的梦幻联动，尝试理解该函数的执行过程，
体会一下这和递归写法中的函数调用有什么联系。
*/
#include <assert.h>
#include <stdio.h>

typedef struct {
  int pc, n;
  char from, to, via;
} Frame;

#define call(_n, _from, _to, _via)                                             \
  ({                                                                           \
    *(++top) = (Frame){                                                        \
        .pc = 0, .n = (_n), .from = (_from), .to = (_to), .via = (_via)};      \
  })
#define ret() ({ top--; })
#define goto(loc) ({ f->pc = (loc)-1; })
// hanoi 将n个圆盘从from移动到to,中途可经过via
void hanoi(int n, char from, char to, char via) {
  Frame stk[64], *top = stk - 1;
  call(n, from, to, via);
  for (Frame *f; (f = top) >= stk; f->pc++) {
    printf("f->pc = %d", f->pc);
    switch (f->pc) {
    case 0:
      printf("case 0\n");
      if (f->n == 1) {
        printf("%c-->%c\n", f->from, f->to);
        goto(4);
      }
      break;
    case 1:
      printf("case 1\n");
      call(f->n - 1, f->from, f->via, f->to);
      break;
    case 2:
      printf("case 2\n");
      call(1, f->from, f->to, f->via);
      break;
    case 3:
      printf("case 3\n");
      call(f->n - 1, f->via, f->to, f->from);
      break;
    case 4:
      printf("case 4\n");
      ret();
      break;
    default:
      assert(0);
    }
  }
}

int main(void) {
  hanoi(3, 'a', 'b', 'c');
  return 0;
}
/*
考点1：宏函数
考点2：汉诺塔思想
思考点：函数调用与返回时栈帧的变化
提示：可以理解为在一个递归函数中有
case0 case1 case2 case3 case4
这几个步骤，f->pc从0递增到4,函数依次执行这几个步骤，最后在case4步骤时返回
*/