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
#include "reader.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

const int MAX_LINE_LEN = 1024;
void* read(void *reader_munch1_queue){
    reader_munch1_queue = (Queue*) reader_munch1_queue;
    char c;
    int done = 0;
    while (!done){
        char *str = (char*) malloc(MAX_LINE_LEN);
        if (str == NULL){
            fprintf(stderr, "Malloc returned NULL\n");
            exit(1);
        }

        int count = 0;
        c = getc(stdin);
        while(c != EOF && c != '\n'){
            if (count < MAX_LINE_LEN-1){
                str[count] = c;
            }
            c = getc(stdin);
            count++;
        }

        if (count >= MAX_LINE_LEN) {
            fprintf(stderr, "ERROR: String is longer than max line length\n");
            free(str);
            str = NULL;
        }
 
        else if (c == '\n' || count > 0){
            str[count] = '\0';
            EnqueueString(reader_munch1_queue, str);
        }
       done = (c == EOF);
    }
    EnqueueString(reader_munch1_queue, NULL);
    pthread_exit(NULL);
    return NULL;
}
