#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char name[20];
    double s1, s2, s3;
    double aver;
} stu;

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
    stu stud[5];
    FILE *fd = NULL;
    fd = fopen("stu_list", "r+");
    fread(stud, sizeof(stu), 5, fd);
    sort(stud, 0, 4);
    pclose(fd);
    for (int i = 0; i < 5; i++)
    {
        printf("name = %s aver = %lf\n", stud[i].name, stud[i].aver);
    }
    fd = fopen("stu_sort", "w+");
    fwrite(stud, sizeof(stu), 5, fd);
    fclose(fd);
    return 0;
}