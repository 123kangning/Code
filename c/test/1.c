#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char*src="hello,world";
    int len=strlen(src);
    char* dest=(char*)malloc(len);
    
    char* d=dest;
    char* s=src+len-1;
    while(len--!=0){
        *d=*s--;
        printf("dest = %-11s,dest->%p d->%p\n",dest,dest,d);
        d++;
    }
    printf("dest = %s\n",dest);
    return 0;
} 