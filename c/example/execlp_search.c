#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char*argv[])
{
    if(argc!=2||argv[1]=="--help"){
        perror(" pathname\n");
        exit(1);
    }
    execlp(argv[1],argv[1],"myls.c",(char*)NULL);
    perror("execlp\n");
    return 0;
}