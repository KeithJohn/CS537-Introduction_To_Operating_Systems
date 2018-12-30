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
#include "build_specification.h"
#include "build_specification_graph.h"
#include "linked_list.h"
#include "text_parser.h"
#include "string.h"
#include "process_execution.h"
#include <stdlib.h>
#include <stdio.h>
//This function is for testing purposes
void printGraph(BuildSpecificationGraph* graph){
    List* nodes = graph->nodeList;
    for(int i=0; i<Size(nodes); i++){
        BuildSpecification *curSpec = Get(nodes, i);
        printf("Target : %s\n", curSpec->target);
        printf("Dependencies : ");
        for (int j=0; j<Size(curSpec->dependencies); j++){
            printf("%s, ", (char*)Get(curSpec->dependencies, j));
        }
        printf("\nCommands :\n");
        for (int k=0; k<Size(curSpec->commands); k++){
            printf("%s\n", (char*)Get(curSpec->commands, k));
        }
        printf("\nChildren :\n");
        for (int l = 0; l<Size(curSpec->children); l++){
            BuildSpecification* currChild = Get(curSpec->children, l);
            printf("%s\n", currChild->target);
        }
        printf("\n\n");
    }
}

int contains(List* aList, char* str){
    for (int i=0; i<Size(aList); i++){
        char *cur = Get(aList, i);
        if(strcmp(cur, str) == 0){
            return 1;
        }
    }
    return 0;
}

int isCyclicUtil(char* lookFor, BuildSpecification* current,  List* visited){
    //If visited return true
    if(strcmp(current->target, lookFor) == 0){
         return 1;
    }
   // for(int i = 0; i < visited->size; i++) {
   //     char *currVisitedNode = (char *) Get(visited, i);
   //     if (strcmp(target, currVisitedNode) == 0) {
   //         return target;
   //     }
   // }
    //Else add to list
    Append(visited, current->target);
    List* children = current->children;
    for(int i = 0; i < children->size; i++){
        BuildSpecification* child = (BuildSpecification*) Get(children, i);
        if (!contains(visited, child->target) && 
            isCyclicUtil(lookFor, child, visited)){
            return 1;
        }
    }
    return 0;
}

char* isCyclic(BuildSpecificationGraph* graph){
    List* nodes = graph->nodeList;

    for(int i = 0; i < nodes->size;i++){
        List* visited = Init_list();
        BuildSpecification* currNode = (BuildSpecification*) Get(nodes, i);
        List *children = currNode->children;

        for(int j=0; j<Size(children); j++){
            BuildSpecification* curChild = Get(children, j);
            
            if (!contains(visited, curChild->target) &&
                isCyclicUtil(currNode->target, curChild, visited)){
                Free_list(visited, 0);
                return currNode->target;
            }
        }
        Free_list(visited, 0);
    }
    return NULL;
}

int hasDependency(BuildSpecification* buildSpecToCheck, char* nameToCheck){

    List* dependencies = buildSpecToCheck->dependencies;
    for (int i=0; i<Size(dependencies); i++){
        char* dependencyName = (char*) Get(dependencies, i);
        //Compare Strings
        if(strcmp(nameToCheck, dependencyName) == 0){
            return 1;
        }
    }

    return 0;
}

void addNode(BuildSpecificationGraph* graph, BuildSpecification* buildSpecToAdd){
    //Check past nodes if buildSpecToAdd is a dependency.
    //If yes add buildSpecToAdd to the children list of buildSpec that has it as dependency
    char* targetName = buildSpecToAdd->target;
    BuildSpecification* buildSpecToCheck;
    for(int i=0; i<Size(graph->nodeList); i++){
        buildSpecToCheck = (BuildSpecification*) Get(graph->nodeList, i);
        if(hasDependency(buildSpecToCheck, targetName) == 1){
           addChild(buildSpecToCheck, buildSpecToAdd);
        }
    }

}

BuildSpecificationGraph* createGraph(char* fileName){
    //init a new build spec graph
    BuildSpecificationGraph *newBuildSpecGraph = (BuildSpecificationGraph*) malloc(sizeof(BuildSpecificationGraph));

    //Use text parser to get list of build specs from file
    newBuildSpecGraph->nodeList = makeBuildSpecs(fileName);
    int numNodes = Size(newBuildSpecGraph->nodeList);
    BuildSpecification* buildSpecToAdd;
    for (int i=0; i<numNodes; i++){
        buildSpecToAdd = (BuildSpecification*) Get(newBuildSpecGraph->nodeList, i);
        addNode(newBuildSpecGraph, buildSpecToAdd);
    }

    return newBuildSpecGraph;
}

void traverse(BuildSpecification* buildSpec){
    //Traverse graph postorderly and check if needed to update. If yes execute commands
    List* children = buildSpec->children;
    for(int i=0; i<Size(children); i++){
        BuildSpecification* curChild = Get(children, i);
        traverse(curChild);
    }

    //loop through children and check if need to update
    if(needToUpdate(buildSpec)){
        List* cmds = buildSpec->commands;
        for(int i=0; i<Size(cmds); i++){
            char *curCmd = Get(cmds, i);
            //int ret = executeCommand(curCmd); 
            //printf("Exec: '%s' Status: %i\n", curCmd, ret);
            if(executeCommand(curCmd)){
                fprintf(stderr, "Build Failed\n");
                exit(1);
            }
            printf("%s\n", curCmd+1); // remove tab
        }
    }
}

void beginTraversal(BuildSpecificationGraph* graph, char* targetName){
    //begins traversal based on target name
    if(targetName == NULL){
        BuildSpecification* rootBuildSpec = Get(graph->nodeList, 0);
        traverse(rootBuildSpec);
    }
    else{
        //find build spec with target name
        int found = 0;
        List* buildSpecs = graph->nodeList;
        for(int i=0; i<Size(buildSpecs); i++){
            BuildSpecification* buildSpecToCheck = Get(buildSpecs, i);
            if(strcmp(targetName, buildSpecToCheck->target) == 0){
                found++;
                traverse(buildSpecToCheck);
                break;
            }
        }
        if(!found){
            fprintf(stderr, "ERROR: No build specification with target name %s\n", targetName);
            exit(1);
        }
    }
}


