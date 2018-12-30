///////////////////////////////////////////////////////////////////////////////
//
// Title:            prodcomm
// Course:           CS 537
// Semester:         Fall 2018
//
//                   NAME              CS Login     netid
// Authors:          Andy Achenreiner  achenreiner  achenreiner
//                   Keith Ecker       kecker       kjecker
//
// Lecturer's Name:  Barton Miller
//
///////////////////////////////////////////////////////////////////////////////
#ifndef QUEUE_H
#define QUEUE_H
#include <semaphore.h>
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
typedef struct Queue_List{
    Queue *getting;
    Queue *sending;
} Queue_List;

Queue *CreateStringQueue(int size);

void EnqueueString(Queue *q, char *string);

char * DequeueString(Queue *q);

void PrintQueueStats(Queue *q);


#endif
