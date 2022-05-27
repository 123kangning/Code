#include <stdio.h>
#include <stdlib.h>
struct kkkk
{
    char name[10];
    double basickkkk;
    double floatkkkk;
    double pay;
    double realkkkk;
};

int main(void)
{
    int *a = (int *)malloc(sizeof(int) * 10);
    printf("%ld", sizeof(a));
    return 0;
}
