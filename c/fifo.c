#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    int ret=mkfifo("myfifo",0664);
    int fd0;
    char*buf="fifo_fifo";
    if(ret==-1){
        perror("fifo");
        exit(1);
    }
    if((fd0=open("myfifo",O_WRONLY))==-1){
        perror("open");
        exit(1);
    }
    // sleep(10);
    if(write(fd0,buf,9)==-1){
        perror("write");
        exit(1);
    }
    printf("write success");
    close(fd0);
    return 0;
}