// Nalin Gupta
// CSE 374 HW5
// 11th May 2020
// Implementing a structure to store words in the T9 numpad format


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "trie.h"

// preprocessor command for maximum characters in the words of dictionary
#define MAX_WORD 100
// Helper method to add word from the dictionary to the tree.
char* parse_word(char* word, char* letters);
// Helper method that gives us the appropriate number for each character.
char* make_array();
// Populates the trie using the words in the dictionary.
void makeTrie(char* file_arg, Trie* trie);
// Searches and prints the word
void search(Trie* trie);

// method checks for arguments, builds tree and prints the word.
int main(int argc, char** argv) {
    // checking if the file argument is passed
    if (argc < 2) {
        fprintf(stderr, "File argument not passed \n");
        return EXIT_FAILURE;
    }
    // gets the basic structure of the trie.
    Trie* trie = makeNode();
    // populates the tree using the words in the dictionary
    makeTrie(argv[1], trie);
    // searches and prints the word from the dictionary
    search(trie);
    // free the allocated memory of a tree.
    freeTrie(trie);
    return EXIT_SUCCESS;
}

// Open the file passed and populates the trie
void makeTrie(char* file_arg, Trie* trie) {
    //  contains the file passed
    FILE * file = fopen(file_arg, "r");
    // checks if the file was able to open or not.
    if (file == NULL) {
        fprintf(stderr, "%s File does not exist", file_arg);
        return;
    }
    // array of letters, helps us to figure out code for each word.
    char* letters = make_array();
    // character array to read in words from the file
    char buffer[MAX_WORD];
    // adds the words to the trie
    while (fgets(buffer, MAX_WORD, file)) {
        int size = strlen(buffer);
        if (buffer[size -1] == '\n') {
            buffer[size -1] = '\0';
        }
        // Would add call add on every word
        char * code = parse_word(buffer, letters);
        add(buffer, code, trie);
        // free the memory allocated to code
        free(code);
    }
    // closes the file
    fclose(file);
    // free the memory allocated to the letter array
    free(letters);
}

// searches and prints the word
void search(Trie* trie) {
    // input provided by the user
    char input[MAX_WORD];
    // copy of the trie to traverse
    Trie* copy = trie;
    // start the interactive session
    printf("Enter \"exit\" to quit.\n");
    // Indicates whether the last interaction contained a hash
    int hash = 0;
    // prints the required output
    while (1) {
        printf("Enter Key Sequence (or \"#\" for next word):\n");
        printf("> ");
        // takes the input from the user
        scanf("%s", input);
        if (strcmp("exit", input) == 0) {
            break;
        } else if (input[0] == '#') {
            // reaches the trie child as directed by the user input
            for (int i = 0; i < strlen(input); i++) {
                if (copy != NULL && input[i] == '#') {
                    copy = copy->children[0];
                }
            }
            // checks if the word exists or not
            if (copy != NULL) {
                printf("\'%s\'\n", copy->data);
            } else {
                printf("There are no more T9onyms\n");
            }
        } else {
            // searching using the copy
            copy = trie;
            // moves along the trie as required
            for (int i = 0; i < strlen(input) ;i++) {
                int hcode = (int)input[i];
                if (copy == NULL || (hcode != 35 && hcode < 50 && hcode > 57)) {
                    break;
                }
                // checking if the input recieved is # character
                if (hcode == 35) {
                    hash = 1;
                    hcode = 0;
                } else {
                    hash = 0;
                    hcode = hcode - 48;
                }
                copy = copy->children[hcode];
            }

            // prints the word if found.
            if (copy != NULL && copy->data != NULL) {
                printf("\'%s\'\n", copy->data);
            } else {
                if (hash == 1) {
                    printf("There are no more T9onyms\n");
                } else {
                    printf("Not found in current dictionary.\n");
                }
            }
        }
    }
}

// helper method to convert words into code
char* parse_word(char* word, char* letters) {
    // stores the code generated
    char* wordInt = (char*) malloc(strlen(word) + 1);
    if (wordInt == NULL) {
        printf("Memory was not allocated as desired");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < strlen(word); i++) {
        char num = letters[word[i] -'a'];
        wordInt[i] = num;
    }
    wordInt[strlen(word)] = '\0';
    return wordInt;
}

// stores the appropriate number for each character as per numpad
char* make_array() {
    // allocation of memory to store the array
    char* letters =(char*) malloc(sizeof(char) * 26);
    if (letters == NULL) {
        printf("Memory was not allocated as desired");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 26; i++) {
        if (i < 3) {
            letters[i] = '2';
        } else if (i >= 3 && i < 6) {
            letters[i] = '3';
        } else if (i >= 6 && i < 9) {
            letters[i] = '4';
        } else if (i >= 9 && i < 12) {
            letters[i] = '5';
        } else if (i >= 12 && i < 15) {
            letters[i] = '6';
        } else if (i >= 15 && i < 19) {
            letters[i] = '7';
        } else if (i >= 19 && i < 22) {
            letters[i] = '8';
        } else {
            letters[i] = '9';
        }
    }
    return letters;
}

