// Nalin Gupta, Abhyudaya Gupta
// CSE 373 Homework 6
// 21 May 2020


#include "mem_impl.h"
#include "mem.h"


/*
Store statistics about the current state of the memory manager in integer
variables whose addresses are given as arguments.
total_size: total amount of storage in bytes acquired by the memory manager
so far to use in satisfying allocation requests.
total_free: total amount of storage in bytes that is stored on the free list,
including any space occupied by header information or links in the free blocks.
n_free_blocks: total number of individual blocks  stored on the free list.
*/


void get_mem_stats(uintptr_t* total_size,
                   uintptr_t* total_free,
                   uintptr_t* n_free_blocks) {
    FreeList* temp = front;
    while (temp != NULL) {
        *total_free = *total_free + temp->size + NODESIZE;
        (*n_free_blocks)++;
        temp = temp->next;
    }
    *total_size = total;
}
