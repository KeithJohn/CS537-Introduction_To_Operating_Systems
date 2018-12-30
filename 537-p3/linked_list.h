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
#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct Node{
    void *element;
    struct Node *next;
}Node;

typedef struct List {
    Node *head;
    Node *tail;
    int size;
}List;

List *Init_list();
void Append(List *aList, void *item);
void *Get(List *aList, int index);
int Contains(List *aList, void *item);
int Size(List *aList);
void checkMalloc(void* mem);
void Free_list(List* aList, int clear);
#endif
