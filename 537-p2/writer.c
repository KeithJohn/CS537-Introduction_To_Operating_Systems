#include "writer.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* write(void * munch2_writer_queue){

    munch2_writer_queue = (Queue*) munch2_writer_queue;
    char *str = NULL;
    while(str = DequeueString(munch2_writer_queue)){
        printf("%s\n",str);
    }
    free(str);
    pthread_exit();
}