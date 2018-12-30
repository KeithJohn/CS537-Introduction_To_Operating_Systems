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
#ifndef BUILD_SPECIFICATION_GRAPH
#define BUILD_SPECIFICATION_GRAPH

#include "linked_list.h"
#include "build_specification.h"

typedef struct {

    List* nodeList;

}BuildSpecificationGraph;

void* AddNode(BuildSpecificationGraph* graph, BuildSpecification* buildSpec);

BuildSpecificationGraph* createGraph(char* fileName);

void beginTraversal(BuildSpecificationGraph* graph, char* targetName);
char* isCyclic(BuildSpecificationGraph* graph);
#endif
