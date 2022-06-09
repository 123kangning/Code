#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    int i=0;
    alarm(1);
    while(1)printf("%d ",i++);
    return 0;
}