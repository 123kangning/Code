#include<stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool equal(char*s1,char*s2,int len){
    printf("\nequal:\ns1=%s\ns2=%s\n",s1,s2);
    for(int i=0;i<len;i++){
        if(s1[i]!=s2[i])return false;
    }
    return true;
}
bool isFlipedString(char* s1, char* s2){
    int len1=strlen(s1),len2=strlen(s2);
    char*ss2=(char*)malloc(len2*2);
    strcpy(ss2,s2);
    strcat(ss2,s2);
    for(int i=0;i<len2;i++){
        printf("s2[i] = %c , s1[0] = %c \n",s2[i],s1[0]);
        if(ss2[i]==s1[0]&&equal(s1,ss2+i,len1))return true;
    }
    return false;
}
int main(){
    char*s1="waterbottle",*s2="erbottlewat";
    printf("final %d\n",isFlipedString(s1,s2));
    return 0;
}