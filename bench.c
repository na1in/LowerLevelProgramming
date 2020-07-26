// Nalin Gupta, Abhyudaya Gupta
// CSE 373 Homework 6
// 21 May 2020

#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

void provide_stats(clock_t start_time);

// When this program is run, it should execute a large number of calls to
// getmem & freemem to allocate & free blocks of random sizes & in random order
// This program should allow the user to specify
// parameters that control the test

// Prints the following Stats
/*
1. Total CPU time used by the benchmark test so far in seconds
2. Total amount of storage acquired from the underlying system
by the memory manager during the test so far 
3. Total number of blocks on the free storage list at this point in the test.
4. Average number of bytes in the free storage blocks at this point in the test
*/
// bench [ntrials] [pctget] [pctlarge] [small_limit] [large_limit][random_seed]
uintptr_t total_size = 0;
uintptr_t total_free = 0;
uintptr_t n_free_blocks = 0;

// int rand_r(int *seedp);

int main(int argc, char* argv[]) {
    // if more than 7 arguments are passed
    if (argc >= 8) {
        return EXIT_FAILURE;
    }

    int ntrials = 10000;
    int pctget = 50;
    int pctlarge = 10;
    int small_limit = 200;
    int large_limit = 20000;
    unsigned int random = time(NULL);

    if (argc > 1) {
        ntrials = atoi(argv[1]);
    }

    if (argc > 2) {
        pctget = atoi(argv[2]);
    }

    if (argc > 3) {
        pctlarge = atoi(argv[3]);
    }

    if (argc > 4) {
        small_limit = atoi(argv[4]);
    }

    if (argc > 5) {
        large_limit = atoi(argv[5]);
    }

    if (argc > 6) {
        random = atoi(argv[6]);
    }

    int ten = ntrials / 10;
    clock_t time_start = clock();
    void** pointer_array = (void**) malloc(sizeof(void*) * ntrials);
    int array_size = 0;

    for (int i = 0; i < ntrials; i++) {
        int random_flip = (rand_r(&random) % 100);
        if (random_flip < pctget) {
            // now we need to do getmem
            int size_flip = rand_r(&random) % 100;
            uintptr_t size = 0;
            if (size_flip < pctlarge) {
                // need to allocate large block
                size = (uintptr_t) rand_r(&random) % (large_limit - small_limit)
                + small_limit;
            } else {
                // allocate small block
                size = (uintptr_t) rand_r(&random) %  small_limit + 1;
            }
            // now doing getmem
            void* alloc = getmem(size);

            if (alloc != NULL) {
                char* current = (char*) alloc;
                for (int i = 0; i < 16; i++) {
                    (*current) = 0xFE;
                    current++;
                }
            }
            pointer_array[array_size] = alloc;
            array_size++;
        } else if (array_size > 0) {
            // freemem
            int to_free = rand_r(&random) % array_size;
            freemem(pointer_array[to_free]);
            pointer_array[to_free] = NULL;
            if (to_free != array_size-1) {
                pointer_array[to_free] = pointer_array[array_size-1];
                pointer_array[array_size-1] = NULL;
            }
            array_size--;
        }
        if ((i != 0) && (((i + 1) % ten == 0))) {
            provide_stats(time_start);
        }
    }
}
    // Operations
    // 1. perform n trials. random decision of getmem or freemem based on
    // pctget getmem probab
    // 2. if freemem -(choose one of previous allocated blocks) - (update
    // pointer array) -continue to next trial
    // 3. if getmem - not null (mostly)- should store 0xFE in each of of
    // first 16 bytes
    // 4. new block allocated = large with prob of pctlarge
    // 5. If smallblock = request block size between 1 & small_limit randomly
    // 6. If largeblock = request block size between small_limit & large_limit
    // randomly
    // Provide Stats to stdout (10 times during exec - 10% of calls, 20% of
    // calls etc and finally a quick overall summary)
    void provide_stats(clock_t time_start) {
        get_mem_stats(&total_size, &total_free, &n_free_blocks);
        clock_t time_end = clock();
        double compute_time = (double) time_end - time_start / CLOCKS_PER_SEC;
        printf("Total CPU time used by the benchmark: %f\n", compute_time);
        printf("Total Amount Of Storage In Bytes Aquired By The Memory: %lu\n",
            total);
        printf("Total Number Of Blocks of Free Storage: %lu\n", n_free_blocks);
        printf("Average Number Of Bytes In The Free Storage Blocks: %lu\n",
            (uintptr_t)(n_free_blocks == 0 ? 0.0 :
                (total_free / n_free_blocks)));
    }
    // 1. total CPU time (DONE)
    // 2. Total amount of storate aquired - get total from get_mem_stats (DONE)
    // 3. Total number of blocks of free storage at a
    // given point during the test (DONE)
    // 4. AVG no of bytes in the free storage blocks at a given point.(DONE)
