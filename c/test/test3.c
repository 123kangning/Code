#include <stdio.h>
#include <stdlib.h>

char* convertAndMerge(char words[][20]);//实现convertAndMerge函数（只翻转字母大小写，并且将其合并为一条字符串返回）

int main(void)
{
    char words[2][20]={"welcome TO ","XIYOU linux"};
    char* str=convertAndMerge(words);
    printf("%s\n",words[0]);
    printf("%s\n",words[1]);
    printf("str = %s\n",str);
    return 0;
}

char* convertAndMerge(char words[2][20]){
    char*ans=(char*)malloc(40);
    int count=0;
    for(int i=0;i<2;i++){
        for(int j=0;j<20;j++){
            //printf("%c",words[i][j]);
            if(words[i][j]<='z'&&words[i][j]>='a'){
                ans[count++]=words[i][j]-32;
            }else if(words[i][j]<='Z'&&words[i][j]>='A'){
                ans[count++]=words[i][j]+32;
            }else if(words[i][j]=='\0'){
                //printf("woo It's \\0\n");
            }else{
                ans[count++]=words[i][j];
            }
        }
    }
    return ans;
}
/*
考点1：二维数组传参
考点2：一条字符串以'\0'为结束标识
考点3：函数返回的字符串需要在堆上手动为其分配内存
*/