#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void* test(void* arg){
    int i=(int)arg;
    if(i==2){
        pthread_exit(NULL);
        //return NULL;
    }
    sleep(i);
    printf("I'm %dth son ,pid = %d, tid = %lu\n",i+1,getpid(),pthread_self());
    return NULL;
}
int main(void)
{
    pthread_t tid;
    int ret,i;
    for(i=0;i<5;i++){
        ret=pthread_create(&tid,NULL,test,(void*)i);
        if(ret!=0){
            fprintf(stderr,"pthread_create");
        }
        //sleep(1);
    }
    // sleep(i);
    //  printf("I'm father ,pid = %d ,\
    //  tid = %lu\n",getpid(),pthread_self());
    pthread_exit(NULL);
    printf("main: return 0\n");
    return 0;
}
