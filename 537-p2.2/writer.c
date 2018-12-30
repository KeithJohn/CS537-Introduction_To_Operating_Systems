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
#include "writer.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* write(void * munch2_writer_queue){

    munch2_writer_queue = (Queue*) munch2_writer_queue;

    char *str_original = DequeueString(munch2_writer_queue);
    while(str_original != NULL){
        printf("%s\n", str_original);
        free(str_original);
        str_original = DequeueString(munch2_writer_queue);
    }

    pthread_exit(NULL);
    return NULL;
}
