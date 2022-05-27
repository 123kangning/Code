#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    int id;
    char name[20];
    int score;
} st;
int size = 0; // the size of st Arrays

void sort(st *num, int start, int end);
void swap(st *num, int i, int j);
void print(st *num);
void search(st *num);
int del(st *num); // 0 return is false,1 return is true
void insert(st *num);
void statistics(st *num);

int main(void)
{
    int n;
    printf("Input the students number\n");
    scanf("%d", &n);
    printf("Input everystudent id name score\n");
    st *num = (st *)malloc(sizeof(st) * n);
    size = n;
    for (int i = 0; i < n; i++)
    {
        scanf("%d%s%d", &num[i].id, num[i].name, &num[i].score);
    }
    char c;
    while (1)
    {
        printf("\nInput your operation [p]rint, [s]earch, s[o]rt, [d]el, [i]nsert, s[t]atistics ,[e]xit\n");
        scanf(" %c", &c);
        switch (c)
        {
        case 'p':
            print(num);
            break;
        case 's':
            search(num);
            break;
        case 'o':
            sort(num, 0, size - 1);
            printf("---sort--complete---\n");
            break;
        case 'd':
            del(num);
            break;
        case 'i':
            insert(num);
            break;
        case 't':
            statistics(num);
            break;
        case 'e':
            break;
        }
        // printf("\n size = %d\n", size);
        if (c == 'e')
            break;
    }

    return 0;
}

void sort(st *num, int start, int end)
{
    if (start >= end)
        return;
    int zhou = start, zhi = start + 1;
    for (int i = start + 1; i <= end; i++)
    {
        if (num[i].score < num[zhou].score)
        {
            swap(num, i, zhi);
            zhi++;
        }
    }
    swap(num, zhi - 1, zhou);

    sort(num, start, zhi - 2);
    sort(num, zhi, end);
}
void swap(st *num, int i, int j)
{
    char temp[20];
    int temp1;
    temp1 = num[i].id;
    num[i].id = num[j].id;
    num[j].id = temp1;
    temp1 = num[i].score;
    num[i].score = num[j].score;
    num[j].score = temp1;
    strcpy(temp, num[i].name);
    strcpy(num[i].name, num[j].name);
    strcpy(num[j].name, temp);
}
void print(st *num)
{
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            printf("---------------------------------------------\n");
            printf("|  %-8s  | %-18s   | %-3s |\n", "id", "name", "score");
        }
        printf("|  %-10d|  %-20s| %-5d |\n", num[i].id, num[i].name, num[i].score);
    }
}
void search(st *num)
{
    int id, sign = 1;
    printf("Input the id \n");
    scanf("%d", &id);
    for (int i = 0; i < size; i++)
    {
        if (id == num[i].id)
        {
            sign = 0;
            printf("---------------------------------------------\n");
            printf("|  %-8s  | %-18s   | %-3s |\n", "id", "name", "score");
            printf("|  %-10d| %-20s | %-5d |\n", num[i].id, num[i].name, num[i].score);
            break;
        }
    }
    if (sign)
    {
        printf("The student %d don't exist\n", id);
    }
}
int del(st *num)
{
    int i, id;
    printf("Input the id \n");
    scanf("%d", &id);
    for (i = 0; i < size; i++)
    {
        if (id == num[i].id)
        {
            break;
        }
    }
    if (i == size)
    {
        return 0;
    }
    for (int j = i; j < size - 1; j++)
    {
        num[j] = num[j + 1];
    }
    size--;
    return 1;
}
void insert(st *num)
{

    int index, id, score;
    char name[20] = "\0";
    printf("Input index between 0 ~ %d\n", size);
    scanf("%d", &index);
    printf("Input the id name score\n");
    scanf("%d %s %d", &id, name, &score);
    for (int i = 0; i < size; i++)
    {
        if (num[i].id == id)
        {
            printf("this id exist already\n");
            return;
        }
    }
    num = (st *)realloc(num, sizeof(st) * (++size));
    for (int i = size - 2; i >= index; i--)
    {
        num[i + 1] = num[i];
    }
    num[index].id = id;
    strcpy(num[index].name, name);
    num[index].score = score;
}
void statistics(st *num)
{
    sort(num, 0, size - 1);
    printf("---------------------------------------------\n");
    printf("|  %-8s  | %-18s   | %-3s |\n", "id", "name", "score");
    printf("---------------------------------------------\n");
    int i = size - 1, count = 0;
    printf("90 ~ 100\n");
    while (i >= 0 && num[i].score / 10 >= 9)
    {
        count++;

        printf("|  %-10d|  %-20s| %-5d |\n", num[i].id, num[i].name, num[i].score);
        i--;
    }
    if (count == 0)
        printf("none\n");
    count = 0;
    printf("80 ~ 89\n");
    while (i >= 0 && num[i].score / 10 >= 8)
    {
        count++;

        printf("|  %-10d|  %-20s| %-5d |\n", num[i].id, num[i].name, num[i].score);
        i--;
    }
    if (count == 0)
        printf("none\n");
    count = 0;
    printf("60 ~ 79\n");
    while (i >= 0 && num[i].score / 10 >= 6)
    {
        count++;

        printf("|  %-10d|  %-20s| %-5d |\n", num[i].id, num[i].name, num[i].score);
        i--;
    }
    if (count == 0)
        printf("none\n");
    count = 0;
    printf("40 ~ 59\n");
    while (i >= 0 && num[i].score / 10 >= 4)
    {
        count++;

        printf("|  %-10d|  %-20s| %-5d |\n", num[i].id, num[i].name, num[i].score);
        i--;
    }
    if (count == 0)
        printf("none\n");

    count = 0;
    printf("20 ~ 39\n");
    while (i >= 0 && num[i].score / 10 >= 2)
    {
        count++;

        printf("|  %-10d|  %-20s| %-5d |\n", num[i].id, num[i].name, num[i].score);
        i--;
    }
    if (count == 0)
        printf("none\n");
    count = 0;
    printf("0 ~ 19\n");
    while (i >= 0 && num[i].score / 10 >= 0)
    {
        count++;

        printf("|  %-10d|  %-20s| %-5d |\n", num[i].id, num[i].name, num[i].score);
        i--;
    }
    if (count == 0)
        printf("none\n");
}
