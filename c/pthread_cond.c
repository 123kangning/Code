/*
have bugs ,the producer thread don't block
*/

#include <pthread.h>
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int globe = 1000000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int array[5], avail;
void *func(void *arg)
{
    // printf("start safe\n");
    int end = 100;
    int loc, i, sign = (int)arg;
    int ret;
    while (1)
    {
        ret = pthread_mutex_lock(&mutex);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_mutex_lock error:%s", strerror(ret));
            exit(1);
        }
        array[avail++] = rand() % 10;
        printf("make array.element %d \n", array[avail - 1]);
        ret = pthread_mutex_unlock(&mutex);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_mutex_unlock error:%s", strerror(ret));
        }
        // sleep(1);
        ret = pthread_cond_signal(&cond);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_cond_signal error:%s", strerror(ret));
        }
    }

    return NULL;
}

int main(void)
{
    pthread_t tid;
    int ret, end = 1000000;
    ret = pthread_create(&tid, NULL, func, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
    }
    while (1)
    {
        ret = pthread_mutex_lock(&mutex);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_mutex_lock error:%s", strerror(ret));
            exit(1);
        }
        while (avail == 0)
        {
            ret = pthread_cond_wait(&cond, &mutex);
            if (ret != 0)
            {
                fprintf(stderr, "pthread_wait error:%s", strerror(ret));
                exit(1);
            }
        }
        while (avail > 0)
        {
            printf("eat array.element %d \n", array[--avail]);
        }
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}