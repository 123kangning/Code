/* fwrite.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    long long id;
    char name[20];
    int score;
} st;

int size;
void print(st *num)
{
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            printf("---------------------------------------------\n");
            printf("|  %-8s  | %-18s   | %-3s |\n", "id", "name", "score");
        }
        printf("|  %-10lld|  %-20s| %-5d |\n", num[i].id, num[i].name, num[i].score);
    }
}

int main(void)
{
    FILE *f = fopen("/tmp/2.dat", "w+");
    int n = size = 3;
    printf("Input everystudent id name score\n");
    st *num = (st *)malloc(sizeof(st) * 3);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld%s%d", &num[i].id, num[i].name, &num[i].score);
    }
    int w = fwrite(num, sizeof(st), n, f);
    printf("write = %d\n", w);

    print(num);
    fwrite(num, sizeof(st), n, f);
    return 0;
}