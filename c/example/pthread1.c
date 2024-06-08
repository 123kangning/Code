#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>

void *test(void *arg)
{
    int i = (int)arg;
    sleep(i);
    printf("I'm %dth son ,pid = %d, tid = %lu\n", i + 1, getpid(),
           pthread_self());
    int *m = (int *)malloc(4000);
    m[0] = 1;
    m[999]=2;
     sleep(100000000);
    return NULL;
}
int main(void)
{
    pthread_t tid;
    int ret, i;
    for(i=0;i<5;i++){
        ret=pthread_create(&tid,NULL,test,(void*)i);
        if(ret!=0){
            fprintf(stderr,"pthread_create");
        }
    }
    sleep(i);
    ret = pthread_create(&tid, NULL, test, (void *)1);
    pthread_cancel(tid);
    void *retval;
    sleep(1);
    pthread_join(pthread_self(), (void **)&retval);
    printf("pthread_join %d\n", (int)retval);
    //  printf("I'm father ,pid = %d ,\
    //  tid = %lu\n",getpid(),pthread_self());
    pthread_exit(NULL);
    printf("main: return 0\n");
    return 0;
}
