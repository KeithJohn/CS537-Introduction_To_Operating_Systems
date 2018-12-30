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
#include <stdlib.h>
#include <stdio.h>

void checkMalloc(void *mem){
    if(mem == NULL){
        fprintf(stderr, "Malloc returned NULL\n");
        exit(1);
    }
}

List *Init_list(){
    List *newList = malloc(sizeof(List));
    checkMalloc(newList);

    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

void Free_list(List* aList, int clear){
    Node *start = aList->head;
    while(start != NULL){
        Node *next = start->next;
        if(clear) free(start->element);
        free(start);

        start = next;
    }
    free(aList);
}

void Append(List *aList, void *item){
    Node *newNode = malloc(sizeof(Node));
    checkMalloc(newNode);
    
    newNode->element = item;
    newNode->next = NULL;
if (aList->size == 0){
        aList->head = newNode;
        aList->tail = newNode;
    }
    else{
        aList->tail->next = newNode;
        aList->tail = newNode;
    }
    aList->size++;
}

void *Get(List *aList, int index){
    if (index < 0 || index > (aList->size - 1)){
        return NULL;
    }
    int curIndex = 0;
    Node *curNode = aList->head;
    while (curIndex < index){
        curIndex++;
        curNode = curNode->next;
    }
   return curNode->element;
} 

int Contains(List *aList, void *item){
    Node *curNode = aList->head;
    while (curNode != NULL){
        if (item == curNode->element){
            return 1;
        }
        curNode = curNode->next;
    }
    return 0;
}

int Size(List *aList){
    return aList->size;
}

//int main(){
//    List *testList = Init_list();
//    int RANGE = 10;
//
//    int* t1, *t2, *t3;
//    for (int i=0; i < RANGE; i++){
//        int *num = malloc(sizeof(int));
//        checkMalloc(num);
//        *num = i;
//        Append(testList, num);
//        i//f (i == 0) t1 = num;
//        if (i ==1) t2 = num;
//        if (i==9) t3 = num;
//    }
//    if (Size(testList) != 10){
//        printf("FAILED test 1\n");
//    }
//
//
//    int* val1 = Get(testList, 0);
//    int* val2 = Get(testList, 5);
//    int* val3 = Get(testList, 9);
//    int* val4 = Get(testList, 10);
//    if( !(*val1 == 0 &&
//        *val2 == 5 &&
//        *val3 == 9 &&
//        val4 == NULL)){
//        printf("FAILED test 2\n");
//    }
//
//
//    if (!Contains(testList, (void*)t1) ||
//        !Contains(testList, (void*)t2) ||
//        !Contains(testList, (void*)t3) ||
//        !Contains(testList, (void*)val1) ||
//        Contains(testList, (void*)&t1)){
//        printf("FAILED test 3\n");
//    }
//}
