#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    int ret=mkfifo("myfifo1",0664);
    if(ret==-1){
        perror("fifo");
        exit(1);
    }
    return 0;
}