#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    int fd0,fd1;
    char*buf=(char*)malloc(1024);
    if((fd0=open("myfifo",O_RDONLY))==-1){
        perror("open");
        exit(1);
    }
    if((fd1=open("1.c",O_WRONLY))==-1){
        perror("open");
        exit(1);
    }
    if(read(fd0,buf,1024)==-1){
        perror("read");
        exit(1);
    }
    if(write(fd1,buf,1024)==-1){
        perror("write");
        exit(1);
    }
    close(fd0);
    close(fd1);
    //printf("%s",buf);
    return 0;
}