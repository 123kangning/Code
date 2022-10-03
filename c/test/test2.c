#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int flag=1;
int judge(int check){
    if(check||!judge(flag)){
        printf("check success\n");
    }else{
        printf("check failure\n");
    }
    return check;
}
int main(void)
{
    int flag=0;
    judge(flag);
}
//需要第一次调用输出失败第二次调用输出成功
//printf("\012\146\154\141\147\075\060\073");