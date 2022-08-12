#include <stdio.h>

int main()
{
    int m,n;
    
    while(scanf("%d %d",&m,&n)!=EOF)
    {
        if(m==n)
            printf("%d=%d\n",m,n);
        if(m>n)
            printf("%d>%d\n",m,n);
        if(m<n)
            printf("%d<%d\n",m,n);
    }
    
    return 0;
}
    // while(a=scanf("%d %d",&m,&n))
    // {
    //     printf("return value = %d\n",a);
    //     if(m==n)
    //         printf("%d=%d\n",m,n);
    //     if(m>n)
    //         printf("%d>%d\n",m,n);
    //     if(m<n)
    //         printf("%d<%d\n",m,n);
    //     if(a==EOF){
    //         printf("EOF = %d",EOF);
    //         break;
    //     }
    // }