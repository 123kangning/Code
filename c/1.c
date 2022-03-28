#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    execl("/bin/bash","bash","-c","ls","-l",NULL);
    return 0;
}