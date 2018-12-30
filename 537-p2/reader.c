#include "reader.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


void* read(void *reader_munch1_queue){

    reader_munch1_queue = (Queue*) reader_munch1_queue;
    char *buffer = (char*) malloc(MAX_LINE_LEN);
    char c = NULL;
    int count = 0;
    if(buffer) {
        c = getc(stdin);
        while(c !=EOF){
            if(c == '\n'){
                if(count !=0) {
                    //malloc a string with size count the enqueue.
                    char *str = (char *) malloc(count);
                    for (int i = 0; i < count; ++i) {
                        str[i] = buffer[i];
                    }
                    EnqueueString(reader_munch1_queue, str);
                    count = 0;
                }
            }else{
                //add char to buffer increase count
                if(count == MAX_LINE_LEN){
                    //MAX line length reached print error
                    fprint("ERROR: String is longer than max line length\n");
                    // loop through rest of line
                    while(getc(stdin)!=EOF||getc(stdin)!='\n'){
                    }
                    count = 0;
                }else{
                    buffer[count] = c;
                    count++;
                }
            }
            c = getc(stdin);
        }
    }else{
       printf("Error allocating memory for buffer in read method.\n");
       exit(1);
    }
    free(buffer);
    EnqueueString(reader_munch1_queue, NULL);
    pthread_exit();
}