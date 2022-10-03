#include<stdio.h>
#include <string.h>
#include <stdlib.h>

//编写一个宏函数，求两个数中的最大值
#define MAX(x,y) x>y?x:y //解决test1
//#define MAX(x,y) (x)>(y)?(x):(y) //解决test2
//#define MAX(x,y) ((x)>(y)?(x):(y)) //解决test3
// #define MAX(x,y)({      \
// int x1=x;               \
// int y1=y;               \
// ((x1)>(y1)?(x1):(y1));  \
// }) //解决test4

int main(void)
{
    int i=1,j=5;
    //test1
    printf("max = %d\n",MAX(1,2));
    //test2
    printf("max = %d\n",MAX(1!=1,1!=2));
    //test3
    printf("max = %d\n",100+MAX(1!=1,1!=2));
    //test4
    printf("max = %d\n",MAX(i++,j++));
    return 0;
}

/*
4个示例宏分别对应且仅对应到4个test
test1 -> 1>2?1:2 -> 2
test2 -> 1!=1>1!=2?1!=1:1!=2 -> 1
test3 -> 101
test4 -> 5
*/