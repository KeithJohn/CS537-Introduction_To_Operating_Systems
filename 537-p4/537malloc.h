#include <stddef.h>

#ifndef MALLOC_537_H
#define MALLOC_537_H

typedef struct Mem_Tuple {
    void *addr;
    int size;
    int freed_flag;
} Mem_Tuple;

Mem_Tuple *init_tuple();

void *malloc537(size_t size);

void free537(void *ptr);

void *realloc537(void *ptr, size_t size);

void memcheck537(void *ptr, size_t size);

#endif
