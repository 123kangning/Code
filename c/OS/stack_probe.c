#include "pthread.h"
#include <stdio.h>

__thread char *base,*cur; // thread-local variables
__thread int id;

__attribute__((noinline)) void set_cur(void *ptr){ cur = ptr; }
__attribute__((noinline)) char*get_cur() { return cur; }

void stackoverflow(int n){
    set_cur(&n);
    if(n%1024==0){
        int size=base-get_cur();
        printf("Stack size of T%d is %d KB\n",id,size);
    }
}

void Tprobe(int tid){
    id=tid;
    base=(void*)&tid;
    stackoverflow(0);
}

int main(void){
    setbuf(stdout,NULL);
    for(int i=0;i<4;i++)
        pthread_create(Tprobe);
}