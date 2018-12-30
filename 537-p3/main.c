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
#include <stdio.h>
#include <unistd.h>
#include "build_specification_graph.h"
#include "linked_list.h"
#include <stdlib.h>
#include "text_parser.h"

char *find_make_file(){
	if( access("makefile", F_OK) != -1){
		return "makefile";
	}
	else if( access("Makefile", F_OK) != -1){
		return "Makefile";
	}
	fprintf(stderr, "Error: No makefile found");
	exit(1);
	return NULL;
}

int main(int argc, char *argv[]){
	if(argc > 2){
		fprintf(stderr, "Error: Too many arguments\n");
		exit(1);
	}

	char *make_file = find_make_file();
	BuildSpecificationGraph *graph = createGraph(make_file);
	char* dup = contains_dup_target(graph->nodeList);
	if(dup){
		fprintf(stderr, "Error: Duplicate target name(%s)\n", dup);
		Free_list(graph->nodeList,1);
		free(graph);
		exit(1);
	} 
	char* target = isCyclic(graph);
	if(target){
		fprintf(stderr, "Error: Cycle detected involving %s\n", target);
		exit(1);
	}

	if (argc == 2){
		beginTraversal(graph, argv[1]);
	}
	else if(argc == 1){
		beginTraversal(graph, NULL);
	}
}
