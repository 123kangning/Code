// calc.h

#ifndef CALC_H_

#define CALC_H_

#ifdef _cplusplus

extern "C"

{

#endif
void sem_mutex_init();
void *consumer();
void *producer();
void print();
void swap(int *, int *);

int add(int, int);

#ifdef _cplusplus
}

#endif

#endif // CALC_H_