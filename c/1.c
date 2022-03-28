#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    if((fd=open("myls.c",O_RDWR))==-1){
        perror("open");
        exit(1);
    }
    void*p=mmap(NULL,4095,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    printf("------------------------------------\n%s\n--------------------------------------",(char*)p);
    //execl("/bin/bash","bash","-c","ls","-l",NULL);
    return 0;
} 