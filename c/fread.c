#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    int id;
    char name[20];
    int score;
} st;
int size = 3;
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
int main(void)
{
    int n = size;
    FILE *f = fopen("/tmp/2.dat", "r+");
    // st *input = (st *)malloc(sizeof(st) * n);
    // int r = fread(input, sizeof(st), n, f);
    // printf("read = %d\n", r);
    // printf("\n-------------------------------------\n");
    // print((st *)input);
    char a = 0;
    fread(&a, sizeof(char), 1, f);
    printf("a = %d\n", a);
    return 0;
}