///////////////////////////////////////////////////////////////////////////////
//
// Title:            537ps
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
#ifndef PROCESS_PROCESSING_H
#define PROCESS_PROCESSING_H

int get_process_count();
typedef struct process_info{
    int pid;
    char state;
    long unsigned int utime;
    long unsigned int stime;
    long unsigned int virtual_mem;
    char* cmdline;
} process_info;

process_info get_process(char *pid);
process_info * get_process_list();

#endif //PROCESS_PROCESSING_H
