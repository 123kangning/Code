#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    int i=0;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigprocmask(SIG_BLOCK,&set,NULL);//屏蔽 Ctrl + c

    while(1){
        sleep(1);
        printf("%d ",i++);
        fflush(stdout);
        
    }
    return 0;
}