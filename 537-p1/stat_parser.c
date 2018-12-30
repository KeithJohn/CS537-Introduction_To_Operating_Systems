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
#include "stat_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parse the stat file, and return a struct
// containing the state, utime, and stime.
stat_info parse_stat_file(char *pid){
    // Create a string of the file path to stat file
    unsigned int MAX_LEN_PATH = 30;
    char stat_file_name[MAX_LEN_PATH];
    if(strlen(pid) > MAX_LEN_PATH - 12 || // Check that path will fit in array
       sprintf(stat_file_name, "/proc/%s/stat", pid) < 0){
        printf("Error creating path to stat file");
        exit(1);
    }

    // Open the file
    FILE *stat_file = fopen(stat_file_name, "r");
    if (stat_file == NULL){
        printf("Error opening stat file");
        exit(1);
    }

    // Declare struct to contain the parsed data
    stat_info parsed_info;

    // Parse the data into the struct.
    // The * after the % sign suppresses the function from assigning that
    // value to a variable. Just field 3, 14, and 15 are extracted.
    if (fscanf(
        stat_file, 
        "%*d"  // Field 1
        " %*s" // Field 2
        " %c"  // Field 3 (state)
        " %*s" // ...
        " %*s"
        " %*s"
        " %*s"
        " %*s"
        " %*s"
        " %*s"
        " %*s"
        " %*s"
        " %*s"
        " %lu" // Field 14 (utime)
        " %lu" // Field 15 (stime)
        " %*s",// Everything else in string
        &parsed_info.state,
        &parsed_info.utime,
        &parsed_info.stime
        ) != 3){
        printf("Error scanning stat file.");
        exit(1);
    }
    if (fclose(stat_file) == EOF){
        printf("Error closing stat file");
        exit(1);
    }

    // return the stuct
    return parsed_info;
}

