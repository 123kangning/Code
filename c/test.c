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
#include <errno.h>

int main(void)
{
    char **cmd = (char **)malloc(sizeof(char *) * 100);
    for(int i=0;i<100;i++){
        cmd[i]=(char*)malloc(100);
    }
    printf("\ncmd = %ld ,cmd[0] = %ld , size = %ld\n",sizeof(cmd),sizeof(cmd[0]),(sizeof(cmd)/sizeof(cmd[0])));
    free(cmd[10]);
    free(cmd[11]);
    printf("\ncmd = %ld ,cmd[0] = %ld , size = %ld\n",sizeof(cmd),sizeof(cmd[0]),(sizeof(cmd)/sizeof(cmd[0])));
    return 0;
}