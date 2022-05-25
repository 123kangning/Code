#include <stdio.h>
struct kkkk
{
    char name[10];
    double basickkkk;
    double floatkkkk;
    double pay;
    double realkkkk;
};

int main(void)
{
    int n;
    scanf("%d", &n);
    struct kkkk kkkks[n];
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%s", &kkkks[i].name);
        scanf("%lf", &kkkks[i].basickkkk);
        scanf("%lf", &kkkks[i].floatkkkk);
        scanf("%lf", &kkkks[i].pay);
        kkkks[i].realkkkk = kkkks[i].basickkkk + kkkks[i].floatkkkk - kkkks[i].pay;
    }

    for (i = 0; i < n; i++)
    {
        printf("%s %.2f\n", kkkks[i].name, kkkks[i].realkkkk);
    }
    return 0;
}
