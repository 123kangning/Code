#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <error.h>

void catch_child(int pid){
    int status;
    pid_t wpid;
    while((wpid=waitpid(-1,&status,0))!=-1){
        printf("----catch child %d\n",wpid);
    }
    if(wpid==-1){
        fprintf(stderr,"waitpid");
    }
    return;

}

int main(void)
{
    int i;
    pid_t pid;
    for(i=0;i<10;i++){
        if((pid=fork())==-1){
            fprintf(stderr,"fork");
        }else if(pid==0)
            break;
    }
    if(i==10){
        struct sigaction act;
        act.sa_handler=catch_child;
        act.sa_flags=0;
        sigemptyset(&act.sa_mask);
        sigaction(SIGCHLD,&act,NULL);
        printf("I'm parents %d\n",pid);
    }else{
        printf("I'm child %d\n",getpid());
    }
    return 0;
}