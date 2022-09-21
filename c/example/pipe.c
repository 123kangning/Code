#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char **cutcmd(char *input)
{
    char **cmd = (char **)malloc(sizeof(char *) * 100);
    int len = 0, count = 0, pi = 0, i = 0;

    int l = strlen(input);
    while (len < l)
    {

        cmd[count] = (char *)malloc(sizeof(char) * 20);
        while (len < l && (input[len] != ' '))
        {
            len++;
        }
        strncpy(cmd[count++], input + i, len - i);

        i = len;

        while (input[len] == ' ' || input[len] == '|')
        {
            i++;
            len++;
        }
    }
    return cmd;
}


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
            execvp("wc",cutcmd("wc -l"));
            close(fd[0]);
        default:
            close(fd[0]);
            dup2(fd[1],STDOUT_FILENO);
            execvp("ls",cutcmd("ls -l"));
            close(fd[1]);
    }
    return 0;
}