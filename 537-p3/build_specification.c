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
#include "linked_list.h"
#include "build_specification.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

BuildSpecification* createBuildSpecification(){
    BuildSpecification *newBuildSpec = malloc(sizeof(BuildSpecification));

    newBuildSpec->dependencies = Init_list();
    newBuildSpec->commands = Init_list();
    newBuildSpec->children = Init_list();
    return newBuildSpec;

}

void addTarget(BuildSpecification* buildSpec, char* target ){
    //Add target to buildSpec
    buildSpec->target = target;
}

void addDependency(BuildSpecification* buildSpec, char* dependency){
    //Add dependency to linked list of dependencies
    Append(buildSpec->dependencies, dependency);
}

void addCommand(BuildSpecification* buildSpec, char* command){
    //Add command to linked list of commands
    Append(buildSpec->commands, command);
}
void addChild(BuildSpecification* buildSpec, BuildSpecification* newChild){
    //Add child to linked list of children
    Append(buildSpec->children, newChild);
}

int needToUpdate(BuildSpecification* buildSpec){
    //Check dependencies mod time and return if needed to update
    int count = 0;
    struct stat *targetBuffer;
    targetBuffer = malloc(sizeof(struct stat));
    time_t targetModTime;
    if(stat(buildSpec->target, targetBuffer) == -1){
        free(targetBuffer);
        return 1;
    }else{
        targetModTime = targetBuffer->st_mtime;
        free(targetBuffer);
    }

    struct stat *buffer;
    buffer = malloc(sizeof(struct stat));
    int size = buildSpec->dependencies->size;
    time_t modTime;
    while(count < size){
        char* file = (char*) Get(buildSpec->dependencies, count);
        if(stat(file, buffer)!=-1){
            modTime = buffer->st_mtime;
        
            if(modTime > targetModTime){
                free(buffer);
                return 1;
            }
        }
        count++;
    }
    free(buffer);
    return 0;
}
//int main(){
//    BuildSpecification* test = createBuildSpecification();
//}
