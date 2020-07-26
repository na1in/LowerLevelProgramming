// Nalin Gupta, Abhyudaya Gupta
// CSE 373 Homework 6
// 21 May 2020

#ifndef MIMPHEADER
#define MIMPHEADER

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <time.h>

// creating a struct that uses linked list structure to
// define memory
typedef struct FreeList {
    uintptr_t size;
    struct FreeList* next;
} FreeList;

// pointer to the freelist
extern FreeList* front;
// to define how much memory has been assigned.
extern uintptr_t total;

// function to check that the data structure satisfies certain properties
void check_heap();

#endif
