#include <stdio.h>

int main(void)
{
    int m,n,k,i,j=0;
    long long y[30000],a,b;
    scanf("%d %d %d",&k,&m,&n);
    for(i=0;i<m;i++){
        scanf("%lld %lld",&a,&b);
        if((k/a)*b>=n)y[j++]=i+1;
    }
    if(j){
        for(i=0;i<j-1;i++)printf("%lld ",y[i]);
        printf("%lld",y[j-1]);
    }else printf("-1");
    return 0;
}