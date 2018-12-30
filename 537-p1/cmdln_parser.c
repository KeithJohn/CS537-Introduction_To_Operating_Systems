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
#include "cmdln_parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Reads all of the characters in the input file into one big string.
// Any null character encountered is replaced with a space.
char *replace_nulls(char* output, int size, FILE *input){
    int index = 0;
    char c;
    // Read until end of file
    while((c = (char)fgetc(input)) != EOF){
        // Need space for null at end. Increase size of string if about to 
        // fill the last spot in the array.
        if (index == size-1){
            char * new_output = realloc(output, size+100);
            if (new_output == NULL){
                printf("Failed to realloc memory");
                exit(1);
            }
            output = new_output;
            size = size + 100;
        }
        // Character read from file is null, so use space instead.
        if (c =='\0'){
            output[index++] = ' ';
        }
        // Otherwise just copy the character into the string.
        else{
            output[index++] = c;
        }
    }

    return output;
}

// Parse the cmdline file, and return the command as a string
// with one space between args. This returned string needs to 
// be freed in the calling function.
char *parse_cmdln_file(char *pid){
    // Create a string of the file path to cmdline file
    unsigned int MAX_LEN_PATH = 30;
    unsigned int PATH_LEN_NO_PID = 15;
    char cmdln_file_name[MAX_LEN_PATH];
    if(strlen(pid) > MAX_LEN_PATH - PATH_LEN_NO_PID ||
       sprintf(cmdln_file_name, "/proc/%s/cmdline", pid) < 0){
        printf("Error creating path to cmdline file");
        exit(1);
    }

    // Open the file
    FILE *cmdln_file = fopen(cmdln_file_name, "r");
    if (cmdln_file == NULL){
        printf("Error opening cmdln file");
        exit(1);
    }

    // Allocate memory for a string of the command.
    int cmd_starting_size = 100;
    char *cmd = malloc(cmd_starting_size);
    if (cmd == NULL){
        printf("Error allocating memory for cmd string");
        exit(1);
    }

    // Copy the characters in file into cmd, and replace nulls with spaces.
    cmd = replace_nulls(cmd, cmd_starting_size, cmdln_file);

    // Close file
    if (fclose(cmdln_file) == EOF){
        printf("Error closing file.");
        exit(1);
    }

    // Return the command string
    return cmd;
}

