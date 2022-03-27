#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int fd[2],ret;
    pid_t pid;
    if((ret=pipe(fd))==-1){
        perror("pipe error");
        exit(1);
    }
    pid=fork();
    switch(pid)
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            close(fd[1]);
            dup2(fd[0],STDIN_FILENO);
            execlp("wc","wc","-l",NULL);
            close(fd[0]);
        default:
            close(fd[0]);
            dup2(fd[1],STDOUT_FILENO);
            execlp("ls","ls",NULL);
            close(fd[1]);
    }
    return 0;
}