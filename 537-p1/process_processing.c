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
#include "stdlib.h"
#include "process_processing.h"
#include "stat_parser.h"
#include "statm_parser.h"
#include "cmdln_parser.h"
#include "dirent.h"
#include "printf.h"
#include <stdio.h>

process_info get_process(char *pid){
    process_info process;

    process.pid = atoi(pid);
    stat_info stat = parse_stat_file(pid);
    process.state = stat.state;
    process.utime = stat.utime;
    process.stime = stat.stime;
    process.virtual_mem = parse_statm_file(pid);
    process.cmdline = parse_cmdln_file(pid);

    return process;
}

int get_process_count(){
    struct dirent *sd;
    int count = 0;
    DIR *dir;
    dir = opendir("/proc");
    
    if(dir == 0){
        printf("Error opening proc directory");
        exit(1);
    }
    
    while((sd = readdir(dir)) !=0){
        //check proc
        char *pid = sd->d_name;
        if(is_valid_pid(pid)){
            count++;
        }
    }
    if(closedir(dir) == -1){
        printf("Error closing proc dir");
        exit(1);
    }
    return count;
}

process_info * get_process_list(){
    struct dirent *sd;
    DIR *dir;

    dir = opendir("/proc");

    if (dir == 0){
        printf("Error opening proc directory");
        exit(1);
    }
    int num_processes = get_process_count();
    process_info *process_list = malloc(sizeof(process_info) * num_processes);
    int cur_index = 0;
    // Loop through directory and get the process for each directory.
    while ((sd = readdir(dir)) != 0 && cur_index < num_processes){
        char *pid = sd->d_name;
        if(is_valid_pid(pid)){
            process_info process = get_process(pid);
            process_list[cur_index++] = process;
        } 
    }
    if(closedir(dir) == -1){
        printf("Error closing proc dir");
        exit(1);
    }
    // return array
    return process_list;
}

