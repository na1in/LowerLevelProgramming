// Nalin Gupta
// CSE 374 Homework 5
// Implemengting the trie struct


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "trie.h"



// Creates a new TrieNode and initializes all of its values to NULL
Trie* makeNode() {
  Trie* root = (Trie*) malloc(sizeof(Trie));
  if (root != NULL) {
      root->data = NULL;
     for (int i = 0;i < 10; i++) {
        root->children[i] = NULL;
    }
  } else {
    fprintf(stderr, "Memory was not allocated to trie");
    exit(EXIT_FAILURE);
  }
  return root;
}

// Adds the word read from the input file to trie
void add(char* word, char* code, Trie* node) {
    Trie* copy = node;
    // for simple processing
    for (int i  =0;i < strlen(code); i++) {
        int num = code[i] - 48;
        if (copy->children[num] == NULL) {
            copy->children[num] = makeNode();
        }
        copy = copy->children[num];
    }
    // for duplicate code processing
    while (copy->data != NULL) {
        if (copy->children[0] == NULL) {
            copy->children[0] = makeNode();
        }
        copy = copy->children[0];
    }
    // storing the word at the location
    copy->data = (char*) malloc(strlen(word)+1);
    if (copy->data != NULL) {
        strncpy(copy->data, word , strlen(word)+1);
    } else {
        fprintf(stderr, "Memory was not allocated to the word");
        exit(EXIT_FAILURE);
    }
}

// free the memory allocated for the trie and its children
void freeTrie(Trie * root) {
    if (root->data !=  NULL) {
        free(root->data);
    }
    for (int i = 0; i < 10; i++) {
        if (root->children[i] != NULL) {
            freeTrie(root->children[i]);
        }
    }
    free(root);
}





