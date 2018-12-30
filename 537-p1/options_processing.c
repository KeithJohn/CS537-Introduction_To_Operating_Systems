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
#include <stdlib.h>
#include "options_processing.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int check_arg(char *optarg){
    if(optarg == NULL){
        return 1;
    }
    else if(strcmp(optarg, "-") == 0){
        return 0;
    }
    printf("Error invalid argument\n");
    printf("Arguments must start with '-' and be space separated.\n");
    exit(1);
}

options_info set_flags(int argc, char *argv[]){
    options_info options;
    options.state_flag = 0;
    options.process_flag = 0;
    options.usertime_flag = 1;
    options.systemtime_flag = 0;
    options.virtualmem_flag = 0;
    options.cmdline_flag = 1;
    int opt ;

    while((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1 ){
        switch(opt){
            case 'p':
                options.process_flag = 1;
                options.process_id = optarg;
                if(atoi(options.process_id)==0){
                    printf("%s is not a valid pid", options.process_id);
                    exit(1);
                }
                break;

            case 's':
                options.state_flag = check_arg(optarg);
                break;

            case 'U':
                options.usertime_flag = check_arg(optarg);
                break;

            case 'S':
                options.systemtime_flag = check_arg(optarg);
                break;

            case 'v':
                options.virtualmem_flag = check_arg(optarg);
                break;

            case 'c':
                options.cmdline_flag = check_arg(optarg);
                break;
            case '?':
                printf("Error invalid argument\n");
                exit(1);
        }
    }
    return options;
}

