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

#ifndef stat_parser
#define stat_parser

typedef struct stat_info{
    char state;
    long unsigned int utime;
    long unsigned int stime;
} stat_info;

stat_info parse_stat_file(char *pid);

#endif
