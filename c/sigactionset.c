#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void catch(int sigin){
    if(sigin == SIGINT){
        printf("hello world\n");
        sleep(5);
    }
}

int main(void)
{
    struct sigaction act,oldact;
    act.sa_handler=catch;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGINT);
    act.sa_flags=0;

    sigaction(SIGINT,&act,&oldact);
    while(1);
    return 0;
}