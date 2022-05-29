#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *output = fopen("/tmp/1.txt", "w+");
    // char *buf = (char *)malloc(sizeof(char) * 1000000);
    int buf;
    // scanf("%s", buf);
    scanf("%lc", &buf);
    // printf("buf = %s   len = %ld\n", buf, strlen(buf));
    printf("buf = %d , buf = %c\n", buf, buf);
    // fputs(buf, output);
    fputc(buf, output);
    fputc(buf, output);
    fputc(buf, output);
    return 0;
}