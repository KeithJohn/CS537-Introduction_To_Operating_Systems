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
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "text_parser.h"
#include "build_specification.h"

const int MAX_LINE_LEN = 1024;
char readLine(FILE *file, char *buffer){
    int count = 0;
    char c = fgetc(file);
    while(c != EOF && c != '\n' && c != '\0' && count < MAX_LINE_LEN-1){
        buffer[count] = c;
        c = fgetc(file);
        count++;
    }
    buffer[count] = '\0';

    return c;
}

char print_until_end(FILE *file){
    char c = fgetc(file);
    while (c != EOF && c != '\n'){
        fprintf(stderr, "%c", c);
        c = fgetc(file);
    }
    return c;
}

int count(char* str, char c){
    int num = 0;
    int i = 0;
    char curChar = str[i];
    while(curChar != '\0'){
        if (curChar == c){
            num++;
        }
        curChar = str[++i];
    }
    return num;
}

int indexOf(char* str, char c){
    int i = 0;
    char curChar = str[i];
    while(curChar != '\0'){
        if (curChar == c){
            return i;
        }
        curChar = str[++i];
    }
    return -1;
}

char** split(char* str, char c){
    char* h1 = malloc(MAX_LINE_LEN);
    checkMalloc(h1);
    char **halves = malloc(sizeof(char*)*2);
    checkMalloc(halves);

    strcpy(h1, str);

    int middle = indexOf(str, c);
    h1[middle] = '\0';
    char *h2 = h1 + middle + 1;
    halves[0] = h1;
    halves[1] = h2;
    return halves;
}
 
List* get_words(char* line){
    List* words = Init_list();
    int i = 0;
    char c = line[i];
    while (c != '\0'){
        while (c == ' ' || c == '\t'){
            c = line[++i];
        }
        
        char *newWord = malloc(MAX_LINE_LEN);
        checkMalloc(newWord);
        int j = 0;
        int reached_word_end = (c == ' ' || c == '\t' || c == '\0' || c == '\n');
        while(!reached_word_end && j < MAX_LINE_LEN-1){
            newWord[j++] = c;
            c = line[++i];
            
            reached_word_end = (c == ' ' || c == '\t' || c == '\0' || c == '\n');
        }
        newWord[j] = '\0';
        
        if (!reached_word_end){
            fprintf(stderr, "Word did not fit into buffer\n");
            exit(1);
        }
        if(newWord[0] != '\0'){
            Append(words, newWord);
        }
        else{
            free(newWord);
        }
    }
    return words;
}

int Endof(char *word){
    char c = word[0];
    int i = 0;
    while(c != '\0'){
        c = word[++i];
    }
    return word[i-1];
}

int is_valid_rule(char* line){
    int colonCount = count(line, ':');
    if (colonCount != 1) return 0;

    char **halves = split(line, ':');
    List* targets = get_words(halves[0]);
    int ans = Size(targets) == 1 &&
              line[0] != '\t' &&
              line[0] != ' ';

    Free_list(targets, 1);
    free(halves[0]);
    free(halves);

    return ans;
}

int invalid(char* str){
    // Return 1 if str is invalid for some reason
    // 0 otherwise
    List *words = get_words(str);

    // Valid blank line
    if ((Size(words) == 0 && str[0] != '\t') || // Valid blank
        (Size(words) != 0 && str[0] == '\t') || // Valid cmd
        is_valid_rule(str)){ // Valid rule

        Free_list(words, 1);
        return 0;
    }
    // Invalid
    else{
        Free_list(words, 1);
        return 1;
    }
}

int is_cmd(char *line){
    return line[0]=='\t';
}

List* read(char* fileName){
    FILE *file = fopen(fileName, "r");
    if (file == NULL){
        fprintf(stderr, "Cannot open file %s", fileName);
        exit(1);
    }

    char c;
    int done = 0;
    int lineNum = 1;
    int seen_rule = 0;
    int seen_command = 0;
    List *line_list = Init_list();
    while (!done){
        char *str = (char*) malloc(MAX_LINE_LEN);
        checkMalloc(str);

        // This returned character is not included in the str
        c = readLine(file, str);
        List *words = get_words(str);
        int line_finished = c == EOF || c == '\n';
        if (Size(words) > 0 && !is_cmd(str)) seen_rule = 1;
        if (Size(words) > 0 && is_cmd(str)) seen_command = 1;

        if (!line_finished || invalid(str) || (seen_command && !seen_rule)){
            // ERROR - INVALID LINE
            fprintf(stderr, "%d: Invalid line : \"%s", lineNum, str);
            if (!line_finished){ 
                if(c != '\0') fprintf(stderr, "%c", c);
                print_until_end(file);
            }
            fprintf(stderr, "\"\n");
            exit(1);
        }

        if(Size(words) > 0){
            Append(line_list, str);
        }else{
            free(str);
            str = NULL;
        } 
        Free_list(words, 1);
        lineNum++;
        done = (c == EOF);
    }
    
    if(fclose(file)){
        fprintf(stderr, "Error closing file %s\n", fileName);
        exit(1);
    }

    return line_list;
}

  

BuildSpecification* parse_rule(char* rule){
    char** halves = split(rule, ':');
    List *targets = get_words(halves[0]);
    List *words = get_words(halves[1]);
    char *target = Get(targets, 0);
    
    free(halves[0]);
    free(halves);

    BuildSpecification *newBuildSpec = createBuildSpecification();
    addTarget(newBuildSpec, target);
    Free_list(targets, 0);
 
    //loop to add dependencies
    for (int i = 0; i < Size(words); i++){
        char *dependency = Get(words, i);
        addDependency(newBuildSpec, dependency);
    }
    Free_list(words, 0);

    return newBuildSpec;
}

List* makeBuildSpecs(char *fileName){
    List *lines = read(fileName);
    BuildSpecification *curBuildSpec;
    List * allBuildSpecs = Init_list();
    
    for (int i = 0; i < Size(lines); i++){
        char *curLine = Get(lines, i);
        if(is_cmd(curLine)){
            addCommand(curBuildSpec, curLine);
        }
        else{
            curBuildSpec = parse_rule(curLine);
            free(curLine);
            Append(allBuildSpecs, curBuildSpec);
        }
        
    }
    Free_list(lines, 0);
    return allBuildSpecs;
}

char** parse_command(List *args){
    int argc = Size(args);
    char **argv = malloc(sizeof(char*) *(argc+1));
    checkMalloc(argv);
    
    for(int i=0; i < argc; i++){
        argv[i] = (char*) Get(args, i);
    }
    argv[argc] = NULL;

    return argv;
}

char* contains_dup_str(List* list){
    for(int i=0; i<Size(list); i++){
        char *str1 = Get(list, i);
        for(int j=i+1; j<Size(list); j++){
            char *str2 = Get(list, j);
            if(strcmp(str1, str2) == 0){
                return str1;
            }
        }
    }
    return NULL;
}

char* contains_dup_target(List *buildSpecs){
    List* targets = Init_list();
    for (int i=0; i<Size(buildSpecs); i++){
        BuildSpecification *curSpec = Get(buildSpecs, i);
        char *curTarget = curSpec->target;
        Append(targets, curTarget);
    }
    char *ans = contains_dup_str(targets);
    Free_list(targets, 0);
    return ans;
}
//int main(int argc, char* argv[]){
//    printf("%i\n", argc);
//    
//    // Get words test
//    char *test = "asdkjfhsd askjdhfskdjf     skdjfhasj\td\t\t\tsdf0";
//    List *words = get_words(test);
//    printf("\nGET WORDS TEST for : %s\n\n", test);
//    for(int i=0; i<Size(words); i++){
//        char* word = Get(words, i);
//        printf("%d) %s\n",i,  word);
//    }
//
//    // Read all valid lines test
//    printf("\nREAD VALID LINES TEST\n\n");
//    List *lines = read(argv[1]);
//    for(int i=0; i<Size(lines); i++){
//        char *line = Get(lines, i);
//        printf("%d) %s\n",i,  line);
//    }
//   
//    // Make build specs test 
//    printf("\nMAKE BUILD SPECS TEST\n\n");
//    List* specs = makeBuildSpecs(argv[1]);
//    for(int i=0; i<Size(specs); i++){
//        BuildSpecification *curSpec = Get(specs, i);
//        printf("Target : %s\n", curSpec->target);
//        printf("Dependencies : ");
//        for (int j=0; j<Size(curSpec->dependencies); j++){
//            printf("%s, ", (char*)Get(curSpec->dependencies, j));
//        }
//        printf("\nCommands :\n");
//        for (int k=0; k<Size(curSpec->commands); k++){
//            printf("%s\n", (char*)Get(curSpec->commands, k));
//        }
//        printf("\n\n");
//    }
//
//    return 1;
//}


