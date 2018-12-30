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
#include <pthread.h>
#include "queue.h"
#include "reader.h"
#include "munch1.h"
#include "munch2.h"
#include "writer.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    const int queue_size = 10;

    Queue *reader_munch1 = CreateStringQueue(queue_size);
    Queue *munch1_munch2 = CreateStringQueue(queue_size);
    Queue *munch2_writer = CreateStringQueue(queue_size);

    pthread_t reader_t;
    pthread_t munch1_t;
    pthread_t munch2_t;
    pthread_t writer_t;
    
    // Use to pass multiple args into the threads.
    Queue_List munch1_args = {reader_munch1, munch1_munch2};
    Queue_List munch2_args = {munch1_munch2, munch2_writer};

    // Create the four threads. Exit if any of them are not successful.
    if (pthread_create(&reader_t, NULL, read, (void *)reader_munch1) ||
        pthread_create(&munch1_t, NULL, munch1, (void *)&munch1_args)||
        pthread_create(&munch2_t, NULL, munch2, (void *)&munch2_args)||
        pthread_create(&writer_t, NULL, write, (void *)munch2_writer)){
        
        fprintf(stderr, "Error creating the four threads\n");
        exit(1);
    } 

    // Join on all the threads. Exit if any of them are not successful.
    if (pthread_join(reader_t, NULL)||
        pthread_join(munch1_t, NULL)||
        pthread_join(munch2_t, NULL)||
        pthread_join(writer_t, NULL)){
        
        fprintf(stderr, "pthread_join error\n");
        exit(1);
    }

    // Print the stats
    PrintQueueStats(reader_munch1);
    PrintQueueStats(munch1_munch2);
    PrintQueueStats(munch2_writer);
}
