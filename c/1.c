#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
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
    
    // printf("hello world\n");
    // printf("hello world\n");
    // printf("hello world\n");
    char*p="ls -al";
    char**tmp=cutcmd(p);
    

    return 0;
} 
