# Nalin Gupta 
# This is the makefile for all the files in HW5 
#
all: t9

# The executable
t9: t9.o trie.o 
	gcc -Wall -std=c11 -g -o t9 t9.o trie.o

# Individual source files
t9.o: t9.c trie.h
	gcc -Wall -std=c11 -g -c t9.c

trie.o: trie.c trie.h 
	gcc -Wall -std=c11 -g -c trie.c

# A "phony" target to remove built files and backups
clean:
	rm -f *.o t9 *~
