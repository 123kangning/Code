#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char* t[3] = {
        "ls",
        "-al"
    };
    execvp("ls",t);

    return 0;
}
