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
    return 0;
}