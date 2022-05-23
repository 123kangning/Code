#include <pthread.h>
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <string.h>

int globe = 1000000;

void *func(void *arg)
{
    // printf("start safe\n");
    int end = (int)arg;
    int loc, i;
    for (i = 0; i < end; i++)
    {
        // printf("cir i = %d\n", i);
        // loc = globe;
        // loc++;
        // globe = loc;
        globe++;
    }
    // sleep(1);
    // printf("end safe\n");
    return NULL;
}

int main(void)
{
    pthread_t tid1, tid2;
    int ret, end = 1000000;
    printf("start: globe = %d\n", globe);
    ret = pthread_create(&tid1, NULL, func, (void *)end);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_create 1 error:%s\n", strerror(ret));
    }
    ret = pthread_create(&tid2, NULL, func, (void *)end);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_create 2 error:%s\n", strerror(ret));
    }

    ret = pthread_join(tid1, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_join 1 error:%s", strerror(ret));
    }
    ret = pthread_join(tid2, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_join 2 error:%s", strerror(ret));
    }
    printf("end: globe = %d\n", globe);
    // printf("main safe\n");
    // printf("exit \n");
    return 0;
}