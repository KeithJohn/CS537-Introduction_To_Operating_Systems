#include "queue.h"
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

char *malloc_fail_msg = "malloc returned null\n";
char *sem_fail_msg = "Semaphore returned an error\n";

Queue *CreateStringQueue(int size){
    if (size < 1){
        printf("Queue size must be at least one\n");
        exit(1);
    }
    Queue *newQ = malloc(sizeof(Queue) + size*sizeof(char *)) ;
    if (newQ == NULL){
        printf("%s", malloc_fail_msg);
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
        printf("%s", sem_fail_msg);
        exit(1);
    }
    if(sem_init(&(newQ->empty), 0, 0)){
        printf("%s", sem_fail_msg);
        exit(1);
    }
    if(sem_init(&newQ->mutex, 0, 1)){
        printf("%s", sem_fail_msg);
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
        printf("%s", sem_fail_msg);
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

    q->enqueueCount++;
    q->enqueueBlockCount = q->enqueueBlockCount + blocked;

    q->qArr[q->tail] = string;
    q->tail = (q->tail+1) % q->size;

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

    q->dequeueCount++;
    q->dequeueBlockCount = q->dequeueBlockCount + blocked;

    char *item = q->qArr[q->head];
    q->head = (q->head+1) % q->size;

    check_sem(1, &q->mutex);
    check_sem(1, &q->full);
    return item;
}    

void PrintQueueStats(Queue *q){
    printf("enqueueCount = %d\n", q->enqueueCount);
    printf("dequeueCount = %d\n", q->dequeueCount);
    printf("enqueueBlockCount = %d\n", q->enqueueBlockCount);
    printf("dequeueBlockCount = %d\n", q->dequeueBlockCount);
}

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
//        printf("%s\n", val);
        if(atoi(val) != i){
            printf("%d : %s ERROR\n", i, val);
        }
        free(val);
        val = NULL;
    }
    pthread_exit(NULL);
    return NULL;
}
 
int main(int argc, char *argv[]){
    pthread_t thread1;
    pthread_t thread2;
    Queue *q = CreateStringQueue(10);
    printf("created queue\n");
    if (pthread_create(&thread1, NULL, inc_test, (void *)q)){
        printf("create error\n");
    }
    if (pthread_create(&thread2, NULL, dec_test, (void *)q)){
        printf("create error\n");
    }
    printf("Created thread\n");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    PrintQueueStats(q);
    free(q);
    printf("free\n");
}
