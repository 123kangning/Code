#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char args[100];
    scanf("%s",args);
    int index1=-1,length=strlen(args),index2=length,i=length-1,cc=0;
    while(i>0){
        if(args[i]==')'){
            index2=i;
            break;
        }i--;
    }
    i=0;
    while(i<index2){
        if(args[i]=='('){
            
            int ans=0,count=0;
            for(int j=i+1;j<length;j++,i++){
                if(args[j]<='9'&&args[j]>='0'){
                    ans=10*ans+args[j]-'0';
                }else{
                    break;
                }
            }
            if(ans>0){
                printf("%d",ans);
                cc++;
            }else{ 
                break;
            }
        }else{
            i++;
        }
    }
    if(cc==0)
    printf("not find");
    return 0;
}