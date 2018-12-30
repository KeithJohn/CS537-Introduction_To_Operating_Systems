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
#include <stdio.h>
#include <stdlib.h>
#include "options_processing.h"
#include "process_processing.h"
#include "check_proc.h"
void print_process(process_info *proc, options_info *options){
    printf("%d", proc->pid);
    if (options->state_flag == 1){
        printf(" %c", proc->state);
    }
    if (options->usertime_flag == 1){
        printf(" utime=%ld", proc->utime);
    }
    if (options->systemtime_flag == 1){
        printf(" stime=%ld", proc->stime);
    }
    if (options->virtualmem_flag == 1){
        printf(" vmemory=%ld", proc->virtual_mem);
    }
    if (options->cmdline_flag == 1){
        printf(" [%s]", proc->cmdline);
    }
    printf("\n");
}

int main(int argc, char *argv[]){

    options_info options = set_flags(argc, argv);
    
    if(options.process_flag == 1){
        char* pid = options.process_id;
        if(!is_just_int(pid) || !is_dir(pid)){
            printf("%s is not a valid pid.\n", pid);
            exit(1);
        }
        process_info process_ptr = get_process(pid);
        print_process(&process_ptr, &options);
        
    }else{
        process_info *process_list = get_process_list();
        int total = get_process_count();
        int cur_index = 0;
        while (cur_index < total){
            process_info cur_proc = process_list[cur_index++];
            print_process(&cur_proc, &options);
        }
    }
}
