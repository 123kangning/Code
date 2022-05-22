#include <stdio.h>
#define pi 3.1415926
void sum(int (*a)[5]){
    // int sum=0;
    // for(int i=0;i<2;i++){
    //     for(int j=0;j<3;j++){
    //         printf("%c ",a[i][j]);
    //     }
    //     printf("\n");
    // }
    for(int i=0;i<5;i++)printf("%d ",(*a)[i]);
}
int main(void)
{
    int a[2][3]={1,2,3,4,5,6};
    // sum(&a);
    int(*p)[3]=a;
    int i=0;
    while(i<6){
        printf("%d ",(*(p+i/3))[i%3]);
        i++;
    }
    return 0;
}