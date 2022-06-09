#include <stdio.h>
#include <string.h>

int main(char **args)
{
    char *file_name1 = args[0];
    char *file_name2 = args[1];
    char ans1 = '\0', ans2 = '\0';
    FILE *fd1 = NULL, *fd2 = NULL;
    if ((fd1 = fopen(file_name1, "r+")) == NULL)
    {
        printf("file_name1 open error\n");
    }
    if ((fd1 = fopen(file_name1, "r+")) == NULL)
    {
        printf("file_name1 open error\n");
    }
    int sign = 1;
    while ((ans1 = fgetc(fd1)) == (ans2 = fgetc(fd2)))
        ;
    if (ans1 == EOF && ans2 == EOF)
    {
        printf("compare ok\n");
    }
    else
    {
        printf("not equal\n");
    }
}
