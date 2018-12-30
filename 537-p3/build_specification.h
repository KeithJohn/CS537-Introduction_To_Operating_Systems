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
#ifndef BUILD_SPECIFICATION
#define BUILD_SPECIFICATION

#include "linked_list.h"

typedef struct {

    char* target;
    List* dependencies;
    List* commands;
    List* children;

} BuildSpecification;

BuildSpecification* createBuildSpecification();
void addTarget(BuildSpecification* buildSpec, char* target );
void addDependency(BuildSpecification* buildSpec, char* dependency);
void addCommand(BuildSpecification* buildSpec, char* command);
void addChild(BuildSpecification* buildSpec, BuildSpecification* newChild);
int needToUpdate(BuildSpecification* buildSpec);

#endif
