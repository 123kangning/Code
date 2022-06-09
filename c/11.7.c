#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char ans[100000];
    printf("Input the chars ");
    scanf("%s", ans);
    for (int i = 0; i < strlen(ans); i++)
    {
        if (ans[i] <= 'Z' && ans[i] >= 'A')
        {
            ans[i] -= 'A' - 'a';
        }
    }
    FILE *fd = NULL;
    if ((fd = fopen("1.txt", "r+")) == NULL)
    {
        printf("file open error\n");
        return 1;
    }
    fputs(ans, fd);
    fclose(fd);
    return 0;
}