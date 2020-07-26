// Nalin Gupta, Abhyudaya Gupta
// CSE 373 Homework 6
// 21 May 2020
// Header file containing declarations of the public functions
// This is the interface that clients of your getmem/freemem package would use.

#include "mem_impl.h"

#ifndef MEMHEADERFILE
#define MEMHEADERFILE

// we can add any constants we need here
#define MIN_BYTE 16
#define ADJUST(size) (((size) + (MIN_BYTE -1) ) & (-MIN_BYTE))
#define MIN_BLOCK 32
#define NODESIZE ADJUST(sizeof(FreeList))
#define INITIAL_MEM 4096

// return the pointer to the assigned memory
void* getmem(uintptr_t size);

// frees the memory pointer passed as parameter
void freemem(void* p);

// stores the stats of the memory manager
void get_mem_stats(
  uintptr_t* total_size,
  uintptr_t* total_free,
  uintptr_t* n_free_blocks);

// prints the blocks on the freelist data structure on the file passed
void print_heap(FILE * f);

#endif
