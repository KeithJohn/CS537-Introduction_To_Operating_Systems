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
#include "statm_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parse the statm file, and return an int of virtual mem in use in pages. 
int parse_statm_file(char *pid){
    // Create a string of the file path to statm file
    unsigned int MAX_LEN_PATH = 30;
    unsigned int PATH_LEN_NO_PID = 13;
    char statm_file_name[MAX_LEN_PATH];
    if(strlen(pid) > MAX_LEN_PATH - PATH_LEN_NO_PID ||
       sprintf(statm_file_name, "/proc/%s/statm", pid) < 0){
        printf("Error creating path to statm file");
        exit(1);
    }

    // Open the file
    FILE *statm_file = fopen(statm_file_name, "r");
    if (statm_file == NULL){
        printf("Error opening statm file");
        exit(1);
    }

    // Parse the first field of statm file into v_mem variable
    int v_mem;
    if (fscanf(
        statm_file, 
        "%d"  // Field 1
        " %*s", // Everything else
        &v_mem) != 1){
        printf("Error scanning statm file.");
        exit(1);
    }

    // Close file
    if (fclose(statm_file) == EOF){
        printf("Error closing statm file");
        exit(1);
    }

    // Return virtual mem quantity
    return v_mem;
}

