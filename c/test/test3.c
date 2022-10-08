#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* convertAndMerge(char words[][20]);//实现convertAndMerge函数（只翻转字母大小写，并且将其合并为一条字符串返回）

int main(void)
{
     int data[] = {0X636c6577, 0X20656d6f, 0X78206f74, 0X756f7969,0x00};
    int data2[] = {0X6e694c20, 0X67207875, 0X70756f72, 0X32303220, 0X00000a32};
    char words[2][20];
    strcpy(words[0],(char*)data);
    strcpy(words[1],(char*)data2);
    printf("%s\n",(char*)data);
    printf("%s\n",(char*)data2);
    
    char* str=convertAndMerge(words);
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