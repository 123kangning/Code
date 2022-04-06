#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
    pid_t pid,p;
    int i;
    for(i=0;i<5;i++){
        pid=fork();
        if(pid==-1){
            perror("fork");
        }else if(pid==0){
            break;
        }
        if(i==4){
            p=pid;
        }
    }
    if(i<5){
        sleep(5);
        printf("\ni = %d\n",i);
        printf("I'm child ,my pid is %d ,ppid is %d\n",getpid(),getppid());
        sleep(10);
    }else{
        sleep(10);
        kill(p,SIGKILL);
       
    }
    return 0;
}