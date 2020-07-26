// Nalin Gupta, Abhyudaya Gupta
// CSE 373 Homework 6
// 21 May 2020

#include "mem_impl.h"
#include "mem.h"

/*  Print a formatted listing on file f showing the blocks on the free list.
Each line of output describes 1 free block & begins with 2 hexadecimal numbers
(0xdddddddd, where d is a hexadecimal digit) giving address & length of block.
*/
// 0xADD 0xLEN

void print_heap(FILE * f) {
    if (f == NULL) {
        fprintf(stderr, "The File Provided Can Not Be Opened");
        return;
    }
    FreeList* temp = front;
    if (temp == NULL) {
        fprintf(stderr, "The Free List Is Empty");
        return;
    }
    while (temp->next != NULL) {
        fprintf(f, "%p %lx\n", (void*) temp, temp->size);
        temp = temp->next;
    }
    // last fencepost
    fprintf(f, "%p %lx\n", (void*) temp, temp->size);
}
