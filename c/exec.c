#include <stdio.h>
#include <unistd.h>

int main(void)
{
    execl("/bin/ls","ls","-l",NULL);
    
    return 0;
}