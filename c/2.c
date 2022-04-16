#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

<<<<<<< HEAD
int search(int a){
    int i=0,b[100],count=0,sum=0;
    for(i=a-1;i>1;i--){
        if(a%i==0){
            b[count++]=i;

            sum+=i;
        }
    }
    sum+=1;
    b[count]=1;
    if(sum==a){
        printf("%d = ",a);
        for(int j=count;j>=0;j--){
            printf("%d",b[j]);
            if(j)printf(" + ");
        }
        printf("\n");
        return 1;
    }else{
        return 0;
    }
}

int main(void)
{
    int n,i,m,sign=1;
    scanf("%d %d",&m,&n);

    for(i=m;i<=n;i++){
        if(search(i))
            sign=0;
    }
    if(sign)printf("None");
=======
int main(void)
{
    int i,j,n;
    scanf("%d",&n);
    if(n>30)n=30;
    for(i=1;i<=n;i++){
        for(j=1;j<100-i;j++){
            if(i*5+j*2+100-j-i==150){
                printf("%d %d %d\n",i,j,100-i-j);
                break;
            }
        }
    }
>>>>>>> origin/master
    return 0;
}