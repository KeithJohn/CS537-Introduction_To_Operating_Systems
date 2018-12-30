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
#include "check_proc.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int is_just_int(char *pid){
    char *end = NULL;
    int base = 10;
    strtol(pid, &end, base);
    if(*end == '\0'){
        return 1;
    }
    else{
        return 0;
    }
}

int is_dir(char *pid){
    unsigned int MAX_LEN = 25;
    unsigned int LEN_NO_PID = 7;
    char path[MAX_LEN];
    if(strlen(pid) > MAX_LEN - LEN_NO_PID){
        printf("PID too long.\n");
        exit(1);
    }
    if(sprintf(path, "/proc/%s", pid) < 0){
        printf("Error making path to pid: %s\n", pid);
        exit(1);
    }
    DIR *dir = opendir(path);
    if(dir == NULL){
        return 0;
    }
    if(closedir(dir) == -1){
        printf("Failed to close %s\n", path);
        exit(1);
    }
    return 1;
}    

// Get the uid of a given process
int get_uid_of_pid(char *pid){
    // Create a string of the file path
    unsigned int MAX_LEN_PATH = 30;
    unsigned int LEN_PATH_NO_PID = 14;
    char file_name[MAX_LEN_PATH];
    if(strlen(pid) > MAX_LEN_PATH - LEN_PATH_NO_PID || // Check that path fits
       sprintf(file_name, "/proc/%s/status", pid) < 0){
        printf("Error creating path to status file");
        exit(1);
    }

    // Open the file
    FILE *status_file = fopen(file_name, "r");
    if (status_file == NULL){
        printf("Error opening status file\n");
        exit(1);
    }

    int BUF_SIZE = 100;
    char buf[BUF_SIZE];
    int line_count = 1;
    int needed_line = 9;
    int uid;
    while(fgets(buf, BUF_SIZE, status_file) != NULL){
        int length = strlen(buf);
        // Check if we finished the line.
        if (buf[length - 1] != '\n' && length == BUF_SIZE -1){
            printf("Error: full line did not fit in buffer\n");
            exit(1);
        }
        if (line_count++ != needed_line){
            continue;
        }
        if (sscanf(buf, "%*s %d %*s", &uid) != 1){
            printf("Error getting uid");
            exit(1);
        }
        break;
    }
    if (line_count <= needed_line){
        printf("Error getting uid");
        exit(1);
    }
    if (fclose(status_file) == EOF){
        printf("Error closing file");
        exit(1);
    }

    // return the uid
    return uid;
}

int is_proc_ours(char *pid){
    int pid_uid = get_uid_of_pid(pid);
    int my_uid = getuid();
    if(pid_uid == my_uid){
        return 1;
    }
    return 0;
}

int is_valid_pid(char *pid){
    return is_just_int(pid) && is_dir(pid) && is_proc_ours(pid);
}

//int main(int argc, char *argv[]){
//    char *pid = argv[1];
 //   printf("%d\n", is_just_int(pid));
 //   printf("%d\n", is_dir(pid));
 //   printf("Proc is ours: %d\n", is_proc_ours(pid));
 //   printf("%d\n", is_valid_pid(pid));
//}    
