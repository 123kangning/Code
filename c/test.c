#include <stdio.h>
int main(void)
{
    char buf[4096];
    char*s=fgets(buf,sizeof(buf),stdin);
    printf("s:%s\n",s);
    printf("%s\n",buf);
    return 0;
}