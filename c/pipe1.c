#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2],ret,status;
    pid_t pid;
    pid_t*p=&pid;
    if((ret=pipe(fd))==-1){
        perror("pipe error");
        exit(1);
    }
    if((*p=fork())==-1){
        perror("fork");
        exit(1);
    }
    switch(pid)
    {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            close(fd[0]);
            dup2(fd[1],STDOUT_FILENO);
            execlp("ls","ls",NULL);
            close(fd[1]);
            break;
        default:
            pid_t pid1;
            pid_t*p1=&pid1;
            if((*p1=fork())==-1){
                perror("fork");
                exit(1);
            }
            switch(pid)
            {
                case 0:
                    close(fd[1]);
                    dup2(fd[0],STDIN_FILENO);
                    execlp("wc","wc","-l",NULL);
                    close(fd[0]);
                    break;
                case -1:
                    perror("fork");
                    exit(1);
                default:
                    waitpid(*p1,&status,0);
                    if(WIFEXITED(status)){
                        printf("\nexit with %d\n",WEXITSTATUS(status));
                    }
                    if(WIFSIGNALED(status)){
                        printf("\nkill with %d\n",WTERMSIG(status));
                    }
            }
            waitpid(*p,&status,0);
            if(WIFEXITED(status)){
                printf("\nexit with %d\n",WEXITSTATUS(status));
            }
            if(WIFSIGNALED(status)){
                printf("\nkill with %d\n",WTERMSIG(status));
            }
    }
    return 0;
}