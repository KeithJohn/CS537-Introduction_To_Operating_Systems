#include "munch2.h"
#include <stdlib.h>
#include <pthread.h>

void* munch2(void *munch2_args[]){
    Queue *munch1_munch2_queue = (Queue*) munch2_args[0];
    Queue* munch2_writer_queue = (Queue*) munch2_args[1];

    char *str_original = malloc(MAX_LINE_LEN);
        char *str_munched = malloc(MAX_LINE_LEN);
        while(str_original = DequeueString(munch1_munch2_queue)){
            str_munched = replace_lowercase(str_original);
            EnqueueString(munch2_writer_queue, str_munched);
        }
        free(str_original);
        free(str_munched);
        pthread_exit();
};


char* replace_lowercase(char* str){
    int c =0;
    while(*(str+c)){
        if(*(str+c)>= 'a' && *(str+c)<= 'z'){
            *(str+c) = *(str+c) - 32;

        }
        c++
    }
    return str;
}