#include <stdio.h>

int main(void)
{
    int c=0;
    int sign[1000]={0};
    int prime[1000]={0};
    while(c<1000){
        printf("1");
        if(sign[c]){
            c++;
            continue;
        }
        for(int i=2;i<c;i++){
            if(c%i==0){
                sign[c]=1;
            }
        }
        if(sign[c]==0){
            for(int i=c;i<1000;i+=c){
                sign[i]=1;
            }
            sign[c]=0;
        }
        c++;
    }
    for(int i=0;i<1000;i++){
        if(sign[i]==0)printf("%d ",i);
    }
    return 0;
}
