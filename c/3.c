#include <stdio.h>
#include <string.h>

int main(void)
{
    char *file_name1 = "1.c";
    char *file_name2 = "2.c";
    char ans1[1000], ans2[1000];
    int a;
    FILE *fd1 = NULL, *fd2 = NULL;
    if ((fd1 = fopen(file_name1, "r+")) == NULL)
    {
        printf("file_name1 open error\n");
    }
    if ((fd1 = fopen(file_name1, "r+")) == NULL)
    {
        printf("file_name1 open error\n");
    }
    while ((a = fgetc(fd1)) != EOF)
    {
        a = fgetc(fd1);
        printf("%c", a);
    }
    return 0;
}