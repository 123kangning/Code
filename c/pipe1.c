#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2],ret,status,i;
    pid_t pid;
    if((ret=pipe(fd))==-1){
        perror("pipe");
        exit(1);
    }
    for(i=0;i<2;i++){
        pid=fork();
        if(pid==-1){
            perror("fork");
            exit(1);
        }
        if(pid==0)break;
    }
    if(i==0){
        close(fd[0]);
        printf("\nI'm first son\n");
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
        close(fd[1]);
        exit(1);
    }
    if(i==1){
        close(fd[1]);
        printf("\nI'm second son\n");
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        close(fd[0]);
        exit(1);
    }
    if(i==2){
        //sleep(10);
        printf("\nI'm father\n");
        close(fd[0]);
        close(fd[1]);
        while((pid=wait(NULL))!=-1);
    }
    return 0;
}
