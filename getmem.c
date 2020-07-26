// Nalin Gupta, Abhyudaya Gupta
// CSE 373 Homework 6
// 21 May 2020

#include "mem_impl.h"
#include "mem.h"


FreeList* search(uintptr_t size);
void removeFromFreeList(FreeList* block);
void addToFreeList(uintptr_t size);
void split(FreeList* bigBlock, uintptr_t size);

FreeList *front = NULL;
uintptr_t total = 0;


/*
Return a pointer to a new block of storage with at least size bytes of memory.
The pointer to the returned block is aligned on an 16-byte boundary 
The block may be somewhat larger than the size requested,
if that is convenient for the memory allocation routines,
but should not be significantly larger, which would waste space.
The value size must be greater than 0. If size is not positive,
or if for some reason getmem cannot satisfy the request, it should return NULL.
*/
void* getmem(uintptr_t size) {
    check_heap();
    // if the size passed is not positive we return null
    if (size <= 0) {
        return NULL;
    }
    uintptr_t newSize = ADJUST(size);
    if (newSize < MIN_BLOCK) {
        newSize = MIN_BLOCK;
    }
    FreeList* block = search(newSize);

    if (block == NULL) {
        // Add block & take care of larger than 4096 case
        addToFreeList(newSize);
        block = search(newSize);
    }

    // when malloc gives an error while allocating memory
    if (!block) {
        return NULL;
    }

    if (block->size > (newSize + MIN_BLOCK)) {
        split(block, newSize);
    }
    removeFromFreeList(block);
    // check if the freelist has been initialized or not

    void* result = (void *) ((uintptr_t)block + sizeof(FreeList));
    check_heap();
    return result;  // will allocate memory and return the pointer to it
}

// searches a block of relevant size
FreeList* search(uintptr_t size) {
    FreeList* curr = front;
    while (curr != NULL && curr->size < size) {
        curr = curr->next;
    }
    return curr;
}

void removeFromFreeList(FreeList* block) {
    // We are not expecting this
    if (block == NULL) {
        return;
    }

    // removing according to the position of the block
    if (block == front) {
        front = front->next;
        block->next = NULL;
    } else {
        FreeList* curr = front;
        FreeList* prev = front;

        while (curr != block) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        curr->next = NULL;
    }
}

// adds the new memory block to the freeList
void addToFreeList(uintptr_t size) {
    int toMalloc = 0;
    // sets the size accordingly to be added to total size
    if (size > INITIAL_MEM) {
        toMalloc = size;
    } else {
        toMalloc = INITIAL_MEM;
    }
    // requests a memory block from malloc
    FreeList* block = (FreeList*)malloc(toMalloc + NODESIZE);
    if (!block) {
        return;
    }
    total += toMalloc + NODESIZE;
    block->size = toMalloc;
    block->next = NULL;

    // Now adding the block to the freeList
    // using with proper sorting
    if (!front) {
        front = block;
    } else {
        FreeList* curr = front;

        if (block < front) {
            block->next = front;
            front = block;
        } else {
            while (curr && curr->next && (uintptr_t)curr->next
                < (uintptr_t)block) {
                curr = curr->next;
            }
            block->next = curr->next;
            curr->next = block;
        }
    }
}

// splits the bigger block into smaller blocks
void split(FreeList* bigBlock, uintptr_t size) {
    FreeList* newBlock = (FreeList*) ((uintptr_t)bigBlock + size + NODESIZE);
    newBlock->size = (bigBlock->size) - size - NODESIZE;
    newBlock->next = bigBlock->next;
    bigBlock->size = size;
    bigBlock->next = newBlock;
}


