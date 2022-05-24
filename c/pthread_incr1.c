#include <pthread.h>
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int globe = 1000000;
pthread_mutex_t mutex;

void *func(void *arg)
{

    int end = 10000;
    int loc, ret, i, sign = (int)arg;
    for (i = 0; i < end; i++)
    {
        ret = pthread_mutex_lock(&mutex);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_mutex_lock error:%s", strerror(ret));
            exit(1);
        }

        globe++;

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid[10000];
    int ret, end = 10000000;
    printf("start: globe = %d\n", globe);
    ret = pthread_mutex_init(&mutex, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_mutex_init error:%s", strerror(ret));
        exit(1);
    }
    for (int i = 0; i < 100; i++)
    {
        ret = pthread_create(&tid[i], NULL, func, (void *)i);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_create %d error:%s\n", i, strerror(ret));
        }
    }
    for (int i = 0; i < 100; i++)
    {
        ret = pthread_join(tid[i], NULL);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_join 1 error:%s", strerror(ret));
        }
    }
    pthread_mutex_destroy(&mutex);

    printf("end: globe = %d\n", globe);
    // printf("main safe\n");
    // printf("exit \n");
    return 0;
}