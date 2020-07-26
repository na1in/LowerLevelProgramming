// Nalin Gupta, Abhyudaya Gupta
// CSE 373 Homework 6
// 21 May 2020

#include "mem_impl.h"
#include "mem.h"
#define NODESIZE ADJUST(sizeof(FreeList))

void merge(FreeList* block);

/*
return the block of storage at location p to the pool of available free storage
The value p must be obtained as the result of a call to getmem.
If p is NULL, then the call to freemem has no effect and returns immediately.
If p has some value other than one returned by getmem,
or if the block it points to has previously been released by another
call to freemem, then the operation of freemem is undefined.
*/

void freemem(void* p) {
    if (p == NULL) {
        return;
    }
    check_heap();
    FreeList* block = (FreeList*) ((uintptr_t)p - NODESIZE);

    // if we removed everything from FreeList
    if (!front) {
        front = block;
        front->next = NULL;
        return;
    }

    // adding to the middle and front of the freeList
    FreeList* curr = front;
    FreeList* prev = front;
    if ((uintptr_t)block < (uintptr_t)curr) {
        block->next = front;
        front = block;
    } else {
        while (curr && ((uintptr_t)curr < (uintptr_t)block)) {
            prev = curr;
            curr = curr->next;
        }
        if (curr) {
            block->next = curr->next;
        } else {
            block->next = NULL;
        }
        prev->next = block;
    }
    merge(block);
    merge(prev);
    check_heap();
}

// merges to adjacent blocks in freeList to make bigger block
void merge(FreeList* block) {
    while ((uintptr_t)block->next ==
        (uintptr_t)block + block->size + NODESIZE) {
        block->size += NODESIZE + block->next->size;
        block->next = block->next->next;
    }
}


