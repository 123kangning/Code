#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *output = fopen("/tmp/1.txt", "w+");
    char *buf = (char *)malloc(sizeof(char) * 1000000);
    scanf("%s", buf);

    fputs(buf, output);

    return 0;
}