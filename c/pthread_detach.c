#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>

void *test(void *arg)
{
    int i = (int)arg;
    // if(i==4){
    //     return (void*)i;
    // }
    sleep(i);
    // printf("I'm %dth son ,pid = %d, tid = %lu\n", i + 1, getpid(), pthread_self());
    while (1)
    {
        printf("I'm %dth son ,pid = %d, tid = %lu\n", i + 1, getpid(), pthread_self());
        sleep(1);
        pthread_testcancel();
    }
    return (void *)i;
}
int main(void)
{
    pthread_t tid[5];
    int ret, i;
    void *retval;
    for (i = 0; i < 5; i++)
    {
        ret = pthread_create(&tid[i], NULL, test, (void *)i);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_create %s", strerror(ret));
            exit(1);
        }
        // sleep(1);
    }
    sleep(3);

    for (i = 0; i < 5; i++)
    {
        // if(i==4)continue;
        sleep(1);
        ret = pthread_cancel(tid[i]);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_cancel error %s\n", strerror(ret));
            exit(1);
        }
        else
        {
            printf("\n---pthread_cancel success ---\n");
        }
    }
    sleep(1);
    for (i = 2; i < 5; i++)
    {
        ret = pthread_detach(tid[i]);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_detach error %s\n", strerror(ret));
        }
        else
        {
            printf("\n---pthread_detach success ---\n");
        }
    }
    // for (i = 0; i < 5; i++)
    // {
    //     // printf("***join***\n");
    //     ret = pthread_join(tid[i], (void **)&retval);
    //     if (ret != 0)
    //     {
    //         fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
    //     }
    //     printf("The %dth pthread %ld\n", i + 1, (long)retval);
    // }
    //  printf("I'm father ,pid = %d ,\
    //  tid = %lu\n",getpid(),pthread_self());
    printf("main: return 0\n");
    pthread_exit(NULL);

    return 0;
}