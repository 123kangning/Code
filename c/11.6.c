#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *file_name1 = (char *)malloc(1000);

    char *file_name2 = (char *)malloc(1000);
    printf("Input the filename :\n");
    scanf("%s %s", file_name1, file_name2);
    int a1, a2;
    FILE *fd1 = NULL, *fd2 = NULL;
    if ((fd1 = fopen(file_name1, "r+")) == NULL)
    {
        printf("file_name1 open error\n");
        return 1;
    }
    if ((fd2 = fopen(file_name1, "r+")) == NULL)
    {
        printf("file_name1 open error\n");
        return 1;
    }

    a1 = fgetc(fd1);
    a2 = fgetc(fd2);

    while ((a1 != EOF) && (a2 != EOF))
    {
        if (a1 != a2)
        {
            printf("not equal\n");
            return 0;
        }
        a1 = fgetc(fd1);
        a2 = fgetc(fd2);
    }
    if (a1 == EOF && a2 == EOF)
    {
        printf("compare ok\n");
    }
    else
    {
        printf("not equal\n");
    }
    fclose(fd1);
    fclose(fd2);
    return 0;
}
