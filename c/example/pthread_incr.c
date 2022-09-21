#include <pthread.h>
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int globe = 1000000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *func(void *arg)
{
    // printf("start safe\n");
    int end = 100;
    int loc, i, sign = (int)arg;
    for (i = 0; i < end; i++)
    {
        if (sign % 2)
        {
            int ret = pthread_mutex_lock(&mutex);
            if (ret != 0)
            {
                fprintf(stderr, "pthread_mutex_lock error:%s", strerror(ret));
                exit(1);
            }

            ret = pthread_mutex_lock(&mutex1);
            if (ret != 0)
            {
                pthread_mutex_unlock(&mutex1);
                continue;
                // fprintf(stderr, "pthread_mutex_lock1 error:%s", strerror(ret));
                // exit(1);
            }
            globe++;
            globe++;
            globe--;
            pthread_mutex_unlock(&mutex1);
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            int ret = pthread_mutex_lock(&mutex);
            if (ret != 0)
            {
                fprintf(stderr, "pthread_mutex_lock error:%s", strerror(ret));
                exit(1);
            }

            ret = pthread_mutex_lock(&mutex1);
            if (ret != 0)
            {
                pthread_mutex_unlock(&mutex1);
                // fprintf(stderr, "pthread_mutex_lock1 error:%s", strerror(ret));
                // exit(1);
            }
            globe++;
            globe++;
            globe--;
            pthread_mutex_unlock(&mutex1);
            pthread_mutex_unlock(&mutex);
        }
    }
    // sleep(1);
    // printf("end safe\n");
    return NULL;
}

int main(void)
{
    pthread_t tid[100];
    int ret, end = 1000000;
    printf("start: globe = %d\n", globe);
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
    printf("end: globe = %d\n", globe);
    // printf("main safe\n");
    // printf("exit \n");
    return 0;
}