// Nalin Gupta
// CSE 374 Homework 5
// This part of the code implements the trie struct


#ifndef TH
#define TH

// A single list node that stores an integer as data.
typedef struct Trie {
  char* data;
  struct Trie* children[10];
} Trie;


// Allocates a new node on the heap.
Trie* makeNode();

// Builds a heap-allocated linked list with the values in the array.
void add(char* word, char* code, Trie* node);

// Frees all nodes in the linked list.
void freeTrie(Trie* trie);

#endif
