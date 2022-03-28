#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int mysystem(char*command);

int main(void)
{
    mysystem("top");
    return 0;
}
int mysystem(char*command)
{
    int status;
    pid_t pid;
    switch(pid=fork())
    {
        case -1:
            perror("fork");
            return -1;
        case 0:
            execl("/bin/bash","bash","-c",command,NULL);
            _exit(127);
        default:
            if(waitpid(pid,&status,0)==-1)return -1;
            else return status;
    }
}