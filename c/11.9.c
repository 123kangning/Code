#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char name[20];
    double s1, s2, s3;
    double aver;
} stu;

int main(void)
{
    stu stud[5];
    printf("Input 5 student\n");
    for (int i = 0; i < 5; i++)
    {
        scanf("%s %lf %lf %lf", stud[i].name, &stud[i].s1, &stud[i].s2, &stud[i].s3);
        stud[i].aver = (stud[i].s1 + stud[i].s2 + stud[i].s3) / 3;
    }
    FILE *fd = NULL;
    fd = fopen("stu_list", "w+");
    fwrite(stud, sizeof(stu), 5, fd);
    fclose(fd);
    return 0;
}