#include <stdio.h>

int main(void)
{
    FILE*fp=fopen("1.txt","rw");
    char buf;
    int count=0;
    while(1){
        // int size=fread(&buf,1,1,fp);
        // printf("buf=%c ,count=%d ,size=%d\n",buf,count++,size); 
    }
    return 0;
}