#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    char*a[3]={
        "cat",
        "1.txt"
    };
    execlp("cat","cat","cat",NULL);
    return 0;
} 

