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

#ifndef check_proc
#define check_proc

int is_proc_ours(char *pid);
int is_valid_pid(char *pid);
int is_just_int(char *pid);
int is_dir(char *pid);
#endif
