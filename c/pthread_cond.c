/*
have bugs ,the producer thread don't block
*/

#include <pthread.h>
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BQ_SIZE 10

typedef struct BlockingQueue
{
    int start;
    int end;
    int *Queue;
} BQ;

BQ *ps;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

void errExit(int ret, char *ans)
{
    if (ret != 0)
    {
        fprintf(stderr, "%s error:%s", ans, strerror(ret));
    }
}

void *producer(void *arg)
{
    // BQ *ps = (BQ *)arg;

    int ret;
    while (1)
    {
        // printf("start = %d , end = %d \n", ps->start, ps->end);
        //  printf("producer\n");
        ret = pthread_mutex_lock(&mutex);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_mutex_lock error:%s", strerror(ret));
            exit(1);
        }
        while (((ps->end + 1 + BQ_SIZE) % BQ_SIZE == ps->start))
        {
            pthread_cond_wait(&cond1, &mutex);
        }

        ps->Queue[(ps->end + 1 + BQ_SIZE) % BQ_SIZE] = rand() % 100;
        printf("make a number %d \n", ps->Queue[ps->end]);
        ps->end = (ps->end + 1 + BQ_SIZE) % BQ_SIZE;

        ret = pthread_mutex_unlock(&mutex);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_mutex_unlock error:%s", strerror(ret));
        }

        ret = pthread_cond_signal(&cond);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_cond_signal error:%s", strerror(ret));
        }
        // sleep(1);
    }

    return NULL;
}
void *consumer(void *arg)
{

    while (1)
    {
        // printf("consumer\n");
        int ret = pthread_mutex_lock(&mutex);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_mutex_lock error:%s", strerror(ret));
            exit(1);
        }
        while (ps->start == ps->end)
        {
            ret = pthread_cond_wait(&cond, &mutex);
            if (ret != 0)
            {
                fprintf(stderr, "pthread_wait error:%s", strerror(ret));
                exit(1);
            }
        }
        while (ps->start != ps->end)
        {
            printf("eat a number %d \n", ps->Queue[ps->start]);
            ps->start = (ps->start + 1 + BQ_SIZE) % BQ_SIZE;
        }
        pthread_mutex_unlock(&mutex);
        errExit(ret, "pthread_mutex_unlock");
        pthread_cond_signal(&cond1);
        errExit(ret, "pthread_cond_signal");
    }
    return NULL;
}

int main(void)
{
    // printf("start\n");
    pthread_t tid1, tid2;
    int ret;
    ps = (BQ *)malloc(sizeof(BQ));
    ps->start = ps->end = 0;
    ps->Queue = (int *)malloc(sizeof(int) * BQ_SIZE);

    ret = pthread_create(&tid1, NULL, consumer, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
    }
    // printf("-------------\n");
    ret = pthread_create(&tid2, NULL, producer, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
    }
    ret = pthread_join(tid1, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_join error  ");
    }
    ret = pthread_join(tid2, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "pthread_join error  ");
    }
    return 0;
}