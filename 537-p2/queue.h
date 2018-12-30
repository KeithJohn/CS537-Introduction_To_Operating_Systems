#ifndef QUEUE_H
#define QUEUE_H
#define QUEUE_SIZE 10
#include <semaphore.h>
int MAX_LINE_LEN = 100;
typedef struct Queue{
    int size;
    int head;
    int tail;
    int enqueueCount;
    int dequeueCount;
    int enqueueBlockCount;
    int dequeueBlockCount;
    sem_t full;
    sem_t empty;
    sem_t mutex;
    char *qArr[];
} Queue;

Queue *CreateStringQueue(int size);

void EnqueueString(Queue *q, char *string);

char * DequeueString(Queue *q);

void PrintQueueStats(Queue *q);


#endif
