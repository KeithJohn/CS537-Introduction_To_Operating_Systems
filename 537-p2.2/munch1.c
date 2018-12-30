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
#include "munch1.h"
#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

char* replace_spaces(char* str){
    int c =0;
    while(*(str+c)){
        if(*(str+c)== ' '){
            *(str+c) = '*';
        }
        c++;
    }
    return str;
}

void* munch1(void* queue_list_ptr){
    Queue_List *queue_list = (Queue_List*) queue_list_ptr;
    Queue *reader_munch1_queue = queue_list->getting;
    Queue *munch1_munch2_queue = queue_list->sending;
    char *str_original = DequeueString(reader_munch1_queue);
    while(str_original != NULL){
        str_original = replace_spaces(str_original);
        EnqueueString(munch1_munch2_queue, str_original);
        str_original = DequeueString(reader_munch1_queue);
    }
    EnqueueString(munch1_munch2_queue, NULL);
    pthread_exit(NULL);
    return NULL;
};


