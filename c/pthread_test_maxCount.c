#include <pthread.h>
#include <stdio.h>
#include <error.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void *func(void *arg)
{
    while (1)
    {
        sleep(1);
    }

    return NULL;
}

int main(void)
{
    pthread_t tid;
    int count = 0;
    while (1)
    {
        int ret = pthread_create(&tid, NULL, func, NULL);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_create %d error:%s\n", count, strerror(ret));
            exit(1);
        }
        count++;
    }
    return 0;
}