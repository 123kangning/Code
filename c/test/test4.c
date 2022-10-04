//汉诺塔非递归
#include <stdio.h>
#include <assert.h>

typedef struct {
    int pc,n;
    char from,to,via;
} Frame;

#define call(_n,_from,_to,_via) ({*(++top) = (Frame){.pc=0,.n=(_n),.from=(_from),.to=(_to),.via=(_via)};})
#define ret() ({top--;})
#define goto(loc) ({f->pc=(loc)-1;})

void hanoi(int n,char from ,char to ,char via){
    Frame stk[64],*top=stk-1;
    call(n,from,to,via);
    for (Frame *f;(f=top)>=stk;f->pc++){
        printf("f->pc = %d",f->pc);
        switch(f->pc){
            case 0:printf("case 0\n");if (f->n==1){//移动到只剩下一个盘子
                printf("%c-->%c\n",f->from,f->to);
                goto(4);
            }break;
            case 1:printf("case 1\n");call(f->n-1, f->from, f->via,  f->to); break;     //先借助第三个杆移动n-1个
            case 2:printf("case 2\n");call(     1, f->from,  f->to, f->via); break;     //再将最后一个移动到目标杆上
            case 3:printf("case 3\n");call(f->n-1,  f->via,  f->to,f->from); break;     //将第三个杆上的n-1个移动到目标杆上
            case 4:printf("case 4\n");ret();break;
            default:assert(0);
        }
    }
}

int main(void)
{
    hanoi(3,'a','b','c');
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