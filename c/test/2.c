#include <stdio.h>
#define N 1000
int main(void)
{
    char a[N];
    gets(a);
    int i = 0, j = 0;
    while (1)
    {
        if (a[i] >= 'A' && a[i] <= 'Z')
            break;
        if (a[i] >= 'a' && a[i] <= 'z')
        {
            a[i] -= 32;
            break;
        }
        else
            i++;
    }
    for (; i < N; i++)
    {
        if (a[i] == '!' || a[i] == '.' || a[i] == '?')
        {
            if (a[i + 1] == '\0')
                break;
            j = i + 1;
            while (1)
            {
                if (a[j] >= 'A' && a[j] <= 'Z')
                    break;
                if (a[j] >= 'a' && a[j] <= 'z')
                {
                    a[j] -= 32;
                    break;
                }
                else
                    j++;
            }
        }
    }
    puts(a);
}