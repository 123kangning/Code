#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void *test(void *arg)
{
    int i = (int)arg;
    sleep(i);
    printf("I'm %dth son ,pid = %d, tid = %lu\n", i + 1, getpid(), pthread_self());
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
            fprintf(stderr, "pthread_create");
        }
        // sleep(1);
    }
    // sleep(i);
    for (i = 0; i < 5; i++)
    {
        ret = pthread_join(tid[i], (void *)&retval);
        if (ret != 0)
        {
            fprintf(stderr, "pthread_join error  ");
        }
        printf("The %dth pthread %ld\n", i + 1, (long)retval);
    }
    //  printf("I'm father ,pid = %d ,\
    //  tid = %lu\n",getpid(),pthread_self());

    pthread_exit(NULL);
    printf("main: return 0\n");
    return 0;
}
