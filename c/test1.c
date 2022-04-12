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
    char*buf1=(char*)malloc(1024*1024);
    char*buf2=(char*)malloc(1024*1024);
    read(fd0,buf1,1024*1024);
    read(fd1,buf2,1024*1024);
    ftruncate(fd0,0);
    ftruncate(fd0,1);
    write(fd0,buf2,1024*1024);
    write(fd1,buf1,1024*1024);
    printf("%s\n",buf1);
    printf("%s\n",buf2);

}

int main(void)
{
    int fd[2];
    if ((fd[0] = open("1.txt", O_RDWR|O_CREAT, S_IWUSR | S_IRUSR)) == -1)
    {
        fprintf(stderr,"error open\n");
        exit(1);
    }
    if ((fd[1] = open("2.txt", O_RDWR|O_CREAT, S_IWUSR | S_IRUSR)) == -1)
    {
        fprintf(stderr,"error open\n");
        exit(1);
    }
    swap(fd[0],fd[1]);
    return 0;
}