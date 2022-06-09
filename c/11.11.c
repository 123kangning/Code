#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char name[20];
    double s1, s2, s3;
    double aver;
} stu;

void insert(stu *num)
{

    int index;
    double s1, s2, s3;
    char name[20] = "\0";

    printf("Input index between 0 ~ %d\n", 5);
    scanf("%d", &index);
    printf("Input the id name score\n");
    scanf("%s %lf %lf %lf", name, &s1, &s2, &s3);
    for (int i = 0; i < 5; i++)
    {
        if (strcmp(num[i].name, name) == 0)
        {
            printf("this id exist already\n");
            return;
        }
    }
    for (int i = 4; i >= index; i--)
    {
        num[i + 1] = num[i];
    }
    strcpy(num[index].name, name);
    num[index].s1 = s1;
    num[index].s2 = s2;
    num[index].s3 = s3;
}

void swap(stu *num, int i, int j)
{
    char temp[20];
    double temp1;

    temp1 = num[i].s1;
    num[i].s1 = num[j].s1;
    num[j].s1 = temp1;
    temp1 = num[i].s2;
    num[i].s2 = num[j].s2;
    num[j].s2 = temp1;
    temp1 = num[i].s3;
    num[i].s3 = num[j].s3;
    num[j].s3 = temp1;
    strcpy(temp, num[i].name);
    strcpy(num[i].name, num[j].name);
    strcpy(num[j].name, temp);
}

void sort(stu *num, int start, int end)
{
    if (start >= end)
        return;
    int zhou = start, zhi = start + 1;
    for (int i = start + 1; i <= end; i++)
    {
        if (num[i].aver < num[zhou].aver)
        {
            swap(num, i, zhi);
            zhi++;
        }
    }
    swap(num, zhi - 1, zhou);

    sort(num, start, zhi - 2);
    sort(num, zhi, end);
}

int main(void)
{
    stu stud[10];
    FILE *fd = NULL;
    fd = fopen("stu_list", "r+");
    fread(stud, sizeof(stu), 5, fd);
    pclose(fd);
    insert(stud);
    sort(stud, 0, 5);
    for (int i = 0; i < 6; i++)
    {
        printf("name = %s aver = %lf\n", stud[i].name, stud[i].aver);
    }
    fd = fopen("new_stu", "w+");
    fwrite(stud, sizeof(stu), 6, fd);
    fclose(fd);
    return 0;
}