// Nalin Gupta, Abhyudaya Gupta
// CSE 373 Homework 6
// 21 May 2020

#include "mem_impl.h"
#include "mem.h"

/*
Check for possible problems with the free list data structure.
function should use asserts to verify that free list satisfies certain properties.
If no errors are detected, this function should return silently
If an error is detected, then an assert should fail
and cause the program to terminate at that point.

1. Blocks are ordered with strictly increasing memory addresses
2. Block sizes are positive numbers and no smaller than whatever minimum size
    you are using in your implementation
3. Blocks do not overlap (the start + length of a block is not an address in
    the middle of a later block on the list)
4. Blocks are not touching (the start + length of a block should not be the
    same address as the next block on the list since in that case the two
    blocks should have been combined into a single, larger block.)
*/
void check_heap() {
    FreeList* temp = front;
    while (temp && temp->next) {
        assert((uintptr_t)temp < (uintptr_t)temp->next);    // order check
        assert(temp->size >= MIN_BLOCK);    // size is +ve and > 32 check
        assert(((uintptr_t)temp + NODESIZE + temp->size)
            < (uintptr_t)temp->next);
        assert(((uintptr_t)temp + NODESIZE + temp->size)
            != (uintptr_t)temp->next);
        temp = temp->next;
    }
}
