Group Members: 
     
     1) Abhyudaya Gupta
     2) Nalin Gupta

Group Identifier: **agna**

Code files assigned to each group member: 
The work was equally divided. We had brainstormed together on how we want to go about doing the freemem & getmem functions.
    
     Abhyudaya Gupta -
           1) mem.h
           2) bench.c
           3) print_heap.c
           4) mem_utils.c
     
     Nalin Gupta -
           1) mem_impl.h
           2) freemem.c
           3) get_mem_stats.c 
           4) Makefile
           5) getmem.c

Heap Data Structure and Algorithm Description:
  We resemeble the memory heap data structure using a linked list (FreeList) of freeNode structures.
Each freeNode contains two properties 
1. size : size of the allocated memory block 
2. next : reference to the next block (basically a freenode)
 The field "size" does not account for the size of the header, it just shows us the space available for allocation 
 after enough space has been used for headers(NODESIZE). All free, allocated memory blocks in the free list have a minimum 
size (MIN_BLOCK) which we have taken to be 32bytes. The freelist data structure is initialized on the first call to getmem.
We use check_heap to make sure that: 
1. The blocks are ordered in strictly increasing memory addresses. 
2. All the blocks have non-zero positive size and are at least of minumum set bytes.
3. None of the memory blocks are overlapping. 
4. Touching blocks of free memory are combined into a bigger block 

When a getmem call is made for some size of memory and we are not able to find a block of relevant space in the freeList
we request a bigger block (INITIAL_MEM) 4096 or larger than that to accomodate the request from the malloc system and added to 
the freeList at appropriate position after sorting according to the pointers. 
If we find a block in freeList that can complete the request we return that and subsequnetly 
remove that from the freeList after splitting the block if required. 

  When a freemem call is made with a block location, then it computes the location of the 
block with respect to the free list and inserts this block to a location sorting according to the postion of the block to
maintain the increasing order of the memory addresses. 
If the adjacent blocks in the Freelist are free we combine them to form bigger blocks of free memory.

Summary of Results Observed in Testing:
  We conducted several tests by giving different parameter values to the bench program. 

  Total CPU time used by the benchmark: 8913.000000
  Total Amount Of Storage In Bytes Aquired By The Memory: 3877184
  Total Number Of Blocks of Free Storage: 33
  Average Number Of Bytes In The Free Storage Blocks: 944

  Total CPU time used by the benchmark: 9355.000000
  Total Amount Of Storage In Bytes Aquired By The Memory: 4514464
  Total Number Of Blocks of Free Storage: 37
  Average Number Of Bytes In The Free Storage Blocks: 854

  Total CPU time used by the benchmark: 9844.000000
  Total Amount Of Storage In Bytes Aquired By The Memory: 5184864
  Total Number Of Blocks of Free Storage: 42
  Average Number Of Bytes In The Free Storage Blocks: 766

  Total CPU time used by the benchmark: 10356.000000
  Total Amount Of Storage In Bytes Aquired By The Memory: 5832784
  Total Number Of Blocks of Free Storage: 48
  Average Number Of Bytes In The Free Storage Blocks: 764

  Total CPU time used by the benchmark: 10906.000000
  Total Amount Of Storage In Bytes Aquired By The Memory: 6488464
  Total Number Of Blocks of Free Storage: 51
  Average Number Of Bytes In The Free Storage Blocks: 726

  We had faced many segmentation faults and floating point errors. We debugged our code using fprintf statements and by 
  changing different parameters of our code whcih narrowed down the cases. E.g by setting pctget as 100 we expected to 
  call only getmem functions however we had a case where we went into freemem - meaning we weren't setting the probabilities correctly.


Resources: Stack Overflow, C documentation