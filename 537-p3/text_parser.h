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
#ifndef TEXT_PARSER
#define TEXT_PARSER

List* makeBuildSpecs(char *fileName);
List* get_words(char* line);
char** parse_command(List* cmd);

// Takes a list of char*
char* contains_dup_str(List* list);
char* contains_dup_target(List* buildSpecs);
#endif
