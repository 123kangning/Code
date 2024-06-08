#include "consumer.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  pthread_t id1, id3, id5;
  pthread_t id2, id4, id6;
  int i;
  int ret;

  sem_mutex_init();

  /*create the producer thread*/
  ret = pthread_create(&id1, NULL, producer, NULL);
  ret = pthread_create(&id3, NULL, producer, NULL);
  ret = pthread_create(&id5, NULL, producer, NULL);
  if (ret != 0) {
    printf("producer creation failed \n");
    exit(1);
  }

  /*create the consumer thread*/
  ret = pthread_create(&id2, NULL, consumer, NULL);
  ret = pthread_create(&id4, NULL, consumer, NULL);
  ret = pthread_create(&id6, NULL, consumer, NULL);
  if (ret != 0) {
    printf("consumer creation failed \n");
    exit(1);
  }

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);
  pthread_join(id3, NULL);
  pthread_join(id4, NULL);
  pthread_join(id5, NULL);
  pthread_join(id6, NULL);

  exit(0);
}