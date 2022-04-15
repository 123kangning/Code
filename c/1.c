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

int judje(long long num){
    if(num==1)return 0;
    if(num==2)return 1;
    for(int j=2;j<sqrt(num);j++){
        if(num%j==0)return 0;
    }
    return 1;
}

int main(void)
{
    long long m;
    long long i=0;
    scanf("%lld",&m);
    for(i=1;i<10000;i+=2){
        if(judje(i)&&judje(m-i)){
            printf("%lld = %lld + %lld",m,i,m-i);
            return 0;
        }
    }

    return 0;
}