#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *f = fopen("/tmp/1.txt", "r");
    char *buf = (char *)malloc(sizeof(char) * 100);
    while (fgets(buf, 100, f) != NULL)
    {
        // buf[strlen(buf) - 1] = '\0';
        printf("%s", buf);
    }
    return 0;
}
