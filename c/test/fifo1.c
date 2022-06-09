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
    if(read(fd0,buf,9)==-1){
        perror("read");
        exit(1);
    }
    printf("read success here\n");
    printf("-----\n%s\n-----",buf);
    close(fd0);
    unlink("myfifo");
    return 0;
}