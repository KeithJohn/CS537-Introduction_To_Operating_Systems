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
#ifndef OPTIONS_PROCESSING_H
#define OPTIONS_PROCESSING_H

typedef struct options_info{
    int process_flag;
    int state_flag;
    int usertime_flag;
    int systemtime_flag;
    int virtualmem_flag;
    int cmdline_flag;
    char* process_id;
}options_info;

options_info set_flags(int argc, char *argv[]);
#endif //PA1_OPTIONS_PROCESSING_H
