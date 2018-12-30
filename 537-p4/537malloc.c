#include "537malloc.h"
#include "AVL.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>


RBT_Node *mem_tree;

//This function checks memory tree to see if given address is within the range(addr - addr+size) of an existing node
//Returns address of node if within range
//Returns NULL if not within range
void *isWithinRange(void *ptr) {
    if (get(mem_tree, ptr)) {
        //node exists with same address
        return ptr;
    }
    Mem_Tuple *mem_tuple = get_max_below(mem_tree, ptr);
    if (mem_tuple) {
        // mem_tuple is not null
        void *addr = mem_tuple->addr;
        void *end_addr = addr + mem_tuple->size;
        if (ptr < end_addr) {
            return addr;
        }
    }
    return NULL;
}

void *malloc537(size_t size) {
    if (mem_tree == NULL) {
        mem_tree = init_tree();
    }
    if (size == 0) {
        fprintf(stderr, "Mallocing size 0\n");
    }
    void *addr = malloc(size);
    if (addr == NULL) {
        fprintf(stderr, "ERROR: Error using malloc\n");
        exit(-1);
    }
    Mem_Tuple *mem_tuple = init_tuple();
    mem_tuple->addr = addr;
    mem_tuple->size = size;

    //Check if address is within another freed address. If yes change size of freed node
    void *node_addr = isWithinRange(addr);
    if (node_addr) {
        Mem_Tuple *node_tuple = get(mem_tree, node_addr);
        if (node_tuple->freed_flag) {
            node_tuple->size = addr - node_addr;
        }
	    if (node_addr == addr) {
            //addr is first byte of freed node
            RBT_Node *tmp = removeNode(mem_tree, node_addr);
            if(tmp != NULL) mem_tree = tmp;
            free(node_tuple);
        }
    }

    // Check end of alloced overruns a freed block
    void *end_addr = addr + size -1;
    node_addr =  isWithinRange(end_addr);
    if (node_addr) {
        Mem_Tuple *node_tuple = get(mem_tree, node_addr);
        if (node_tuple->freed_flag) {
            RBT_Node *tmp = removeNode(mem_tree, node_addr);
            if(tmp != NULL) mem_tree = tmp;

            node_tuple->size = (node_tuple->addr + node_tuple->size) - (addr + size);
            node_tuple->addr = addr + size;
            tmp = add(mem_tree, node_tuple->addr, node_tuple);
            if (tmp != NULL) mem_tree = tmp;
        }
    }

    RBT_Node *tmp = add(mem_tree, addr, mem_tuple);
    if (tmp != NULL) mem_tree = tmp;

    //print_tree(mem_tree, 0);
    return addr;
}

void free537(void *ptr) {
    if (mem_tree == NULL) {
        mem_tree = init_tree();
    }
    Mem_Tuple *mem_tuple = (Mem_Tuple *) get(mem_tree, ptr);
    if (mem_tuple) {
        //there is a node in tree with the same address
        if (mem_tuple->freed_flag) {
            //Already Freed
            fprintf(stderr, "ERROR: Memory is already freed\n");
            exit(-1);
        } else {
            free(ptr);
            mem_tuple->freed_flag = 1;
        }

    } else {
        //no node in tree with address
        void *addr = isWithinRange(ptr);
        if (addr) {
            fprintf(stderr, "ERROR: Address is not first byte of memory\n");
            exit(-1);
        } else {
            //bad address to free
            fprintf(stderr, "ERROR: Address was not malloced by 537malloc\n");
            exit(-1);
        }

    }
}

void *realloc537(void *ptr, size_t size) {
    if (mem_tree == NULL) {
        mem_tree = init_tree();
    }

    void *addr;
    if (ptr == NULL) {
        //malloc
        addr = malloc537(size);
    } else if (size == 0) {
        //free
        fprintf(stderr, "Warning: Freeing using realloc (size 0)\n");
        free537(ptr);
        addr = NULL;
    } else {
        //Realloc
        Mem_Tuple *mem_tuple = get(mem_tree, ptr);
        //first byte
        if (mem_tuple) {
            if (mem_tuple->freed_flag) {
                fprintf(stderr, "Reallocating an addr that is already freed.\n");
                exit(-1);
            }
            void *new_addr = realloc(ptr, size);
            if(new_addr != ptr){
                RBT_Node *tmp = removeNode(mem_tree, ptr);
                if(tmp != NULL) mem_tree = tmp;
                //add new node to tree
                mem_tuple->addr = new_addr;
                mem_tuple->size = size;
                tmp = add(mem_tree, new_addr, mem_tuple);
                if(tmp != NULL) mem_tree = tmp;
            }
            else{
                mem_tuple->size = size;
            }
            addr = new_addr;
        }
        else {
            //not first byte
            fprintf(stderr, "ERROR: Address is not first byte of alloced memory\n");
            exit(-1);
        }
    }
    return addr;
}

void memcheck537(void *ptr, size_t size) {
    if (mem_tree == NULL) {
        mem_tree = init_tree();
    }
    void *node_addr = isWithinRange(ptr);
    if (node_addr) {
        void *end_ptr = ptr + size-1;
        void *end_node_addr = isWithinRange(end_ptr);
        if (end_node_addr == node_addr) {
            Mem_Tuple *mem_tuple = (Mem_Tuple *) get(mem_tree, end_node_addr);
            if (!mem_tuple->freed_flag) {
                //printf("Address range is fully within range allocated by malloc537\n");
            } else {
                fprintf(stderr, "Address range is within freed memory\n");
                exit(-1);
            }
        }
        else{
            fprintf(stderr, "Address range is not fully within range allocated by malloc537\n");
            exit(-1);
        }
    } else {
        fprintf(stderr, "Address range is not fully within range allocated by malloc537\n");
        exit(-1);
    }

}

Mem_Tuple *init_tuple() {
    Mem_Tuple *tuple = malloc(sizeof(Mem_Tuple));
    tuple->addr = NULL;
    tuple->size = -1;
    tuple->freed_flag = 0;
    return tuple;
}
