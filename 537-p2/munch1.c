#include "munch1.h"
#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


void* munch1(void) *munch1_args[]){
    Queue *reader_munch1_queue = (Queue*) munch1_args[0] ;
    Queue *munch1_munch2_queue = (Queue*) munch1_args[1];
    char *str_original = malloc(MAX_LINE_LEN);
    char *str_munched = malloc(MAX_LINE_LEN);
    while(str_original = DequeueString(reader_munch1_queue)){
        str_munched = replace_spaces(str_original);
        EnqueueString(munch1_munch2_queue, str_munched);
    }

    free(str_original);
    free(str_munched);
    pthread_exit();
};

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