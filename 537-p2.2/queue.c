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
#include "queue.h"
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

char *malloc_fail_msg = "malloc returned null\n";
char *sem_fail_msg = "Semaphore returned an error\n";

Queue *CreateStringQueue(int size){
    if (size < 1){
        fprintf(stderr, "Queue size must be at least one\n");
        exit(1);
    }
    Queue *newQ = malloc(sizeof(Queue) + size*sizeof(char *)) ;
    if (newQ == NULL){
        fprintf(stderr, "%s", malloc_fail_msg);
        exit(1);
    }
    newQ->size = size;
    newQ->head = 0;
    newQ->tail = 0;
    newQ->enqueueCount = 0;
    newQ->dequeueCount = 0;
    newQ->enqueueBlockCount = 0;
    newQ->dequeueBlockCount = 0;

    if(sem_init(&newQ->full, 0, size)){
        fprintf(stderr, "%s", sem_fail_msg);
        exit(1);
    }
    if(sem_init(&(newQ->empty), 0, 0)){
        fprintf(stderr, "%s", sem_fail_msg);
        exit(1);
    }
    if(sem_init(&newQ->mutex, 0, 1)){
        fprintf(stderr, "%s", sem_fail_msg);
        exit(1);
    }
    return newQ;
}

// Waits or posts on the semaphore if op = 0 or not respectively.
// Then checks the return value.
void check_sem(int op, sem_t *sem){
    int err;
    if (op == 0){
        err = sem_wait(sem);
    }
    else{
        err = sem_post(sem);
    }
    if (err){
        fprintf(stderr, "%s", sem_fail_msg);
        exit(1);
    } 
}

void EnqueueString(Queue *q, char *string){
    int blocked = 0;
    if (sem_trywait(&q->full) == -1){
        blocked = 1;
        check_sem(0, &q->full);
    }
    check_sem(0, &q->mutex);

    q->qArr[q->tail] = string;
    q->tail = (q->tail+1) % q->size;

    if (string != NULL){
        q->enqueueCount++;
        q->enqueueBlockCount = q->enqueueBlockCount + blocked;
    }

    check_sem(1, &q->mutex);
    check_sem(1, &q->empty);
    return;
}

char *DequeueString(Queue *q){
    int blocked = 0;
    if (sem_trywait(&q->empty) == -1){
        blocked = 1;
        check_sem(0, &q->empty);
    }
    check_sem(0, &q->mutex);

    char *item = q->qArr[q->head];
    q->head = (q->head+1) % q->size;

    if (item != NULL){
        q->dequeueCount++;
        q->dequeueBlockCount = q->dequeueBlockCount + blocked;
    }

    check_sem(1, &q->mutex);
    check_sem(1, &q->full);
    return item;
}    

void PrintQueueStats(Queue *q){
    check_sem(0, &q->mutex);
    fprintf(stderr, "enqueueCount = %d\n", q->enqueueCount);
    fprintf(stderr, "dequeueCount = %d\n", q->dequeueCount);
    fprintf(stderr, "enqueueBlockCount = %d\n", q->enqueueBlockCount);
    fprintf(stderr, "dequeueBlockCount = %d\n", q->dequeueBlockCount);
    check_sem(1, &q->mutex);
}

// Below are some functions that we were using to test the queue.
// These functions were used in the commented main at the bottom of this file.

int TRIALS = 10000000;
void *inc_test(void *q){
    q = (Queue *)q;
    for (int i = 0; i < TRIALS; i++){
        char *count = malloc(10);
        sprintf(count, "%d\n", i);
        EnqueueString(q, count);
    }
    pthread_exit(NULL);
    return NULL;
}

void *dec_test(void *q){
    q = (Queue *)q;
    for (int i = 0; i < TRIALS; i++){
        char* val = DequeueString(q);
        if(atoi(val) != i){
            fprintf(stderr, "%d : %s ERROR\n", i, val);
        }
        free(val);
        val = NULL;
    }
    pthread_exit(NULL);
    return NULL;
}
 
//int main(int argc, char *argv[]){
//    pthread_t thread1;
//    pthread_t thread2;
//    Queue *q = CreateStringQueue(10);
//    printf("created queue\n");
//    if (pthread_create(&thread1, NULL, inc_test, (void *)q)){
//        printf("create error\n");
//    }
//    if (pthread_create(&thread2, NULL, dec_test, (void *)q)){
//        printf("create error\n");
//    }
//    printf("Created thread\n");
//    pthread_join(thread1, NULL);
//    pthread_join(thread2, NULL);
//    PrintQueueStats(q);
//    free(q);
//    printf("free\n");
//}
