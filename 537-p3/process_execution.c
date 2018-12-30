///////////////////////////////////////////////////////////////////////////////
//
// Title:            537make
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
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "text_parser.h"
#include <sys/wait.h>

// Return 0 on success
int executeCommand(char* command){
    List *parts = get_words(command);
    char** argv = parse_command(parts);
    pid_t child_pid;
    int child_status;

    child_pid = fork();
    if(child_pid == 0){
        //child
        int return_code;
        return_code = execvp(argv[0], argv);
        //if execvp returns it failed
        if(return_code){
            fprintf(stderr, "ERROR %d\n", return_code);
            return return_code;
        }
    }else if (child_pid > 0){
        //parent
        while(wait(&child_status) != child_pid);
        Free_list(parts, 1);
        free(argv);

    }else{
        fprintf(stderr, "Fork error\n");
        exit(1);
    }
    return child_status;
}

//int main(){
//    executeCommand("gcc -Wall -Wextra -o test process_execution.c");
//}
