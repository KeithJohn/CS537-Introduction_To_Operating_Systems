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
#include "munch2.h"
#include <stdlib.h>
#include <pthread.h>
#include "queue.h"
#include "stdio.h"

char* replace_lowercase(char* str){
    int c =0;
    while(*(str+c)){
        if(*(str+c)>= 'a' && *(str+c)<= 'z'){
            *(str+c) = *(str+c) - 32;

        }
        c++;
    }
    return str;
}

void* munch2(void* queue_list_ptr){
    Queue_List *queue_list = (Queue_List*) queue_list_ptr;
    Queue *munch1_munch2_queue = queue_list->getting;
    Queue* munch2_writer_queue = queue_list->sending;

    char *str_original = DequeueString(munch1_munch2_queue);
    while(str_original != NULL){
        str_original = replace_lowercase(str_original);
        EnqueueString(munch2_writer_queue, str_original);
        str_original = DequeueString(munch1_munch2_queue);
    }
    
    EnqueueString(munch2_writer_queue, NULL);
    pthread_exit(NULL);
    return NULL;
};



