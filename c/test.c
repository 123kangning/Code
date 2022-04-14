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

void swap(int fd0,int fd1){
    char*buf0=(char*)malloc(10000);
    char*buf1=(char*)malloc(10000);
    read(fd0,buf0,10000);
    read(fd1,buf1,10000);
    ftruncate(fd0,0);
    ftruncate(fd1,0);
    printf("buf0 = \n%s\n",buf0);
    printf("buf1 = \n%s\n",buf1);
    write(fd1,buf0,10000);
    write(fd0,buf1,10000);

}

int main(void)
{
    char*a=(char*)malloc(100);
    printf("sizeof = %ld",sizeof(a));
    free(a);a=NULL;
    return 0;
}