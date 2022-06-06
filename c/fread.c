/* fread.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    long long id;
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
        printf("|  %-10lld|  %-20s| %-5d |\n", num[i].id, num[i].name, num[i].score);
    }
}
int main(void)
{
    int n = size;
    FILE *f = fopen("/tmp/2.dat", "r+");
    st *input = (st *)malloc(sizeof(st) * n);
    // int r = fread(input, sizeof(st), n, f);
    // printf("read = %d\n", r);

    int oldid = 1;
    st newdata = {13121, "kangning", 100};
    while (1)
    {
        if (fread(input, sizeof(st), 1, f) < 1)
            break;
        if (oldid == input->id)
        {
            // fpos_t pos;
            // fgetpos(f, &pos);
            fseek(f, -sizeof(st), SEEK_CUR);
            fwrite(&newdata, sizeof(st), 1, f);
            // fsetpos(f, &pos);
        }
    }
    // print(input);
    fclose(f);
    return 0;
}