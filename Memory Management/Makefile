# Nalin Gupta, Abhyudaya Gupta 
# CSE 373 Homework 6 
# 21 May 2020

all: bench
#target
bench:  bench.o getmem.o freemem.o  get_mem_status.o mem_utils.o print_heap.o 
	gcc -Wall -std=c11 -g -o bench bench.o getmem.o freemem.o  get_mem_status.o mem_utils.o print_heap.o 

# Individual source files
bench.o: bench.c mem.h
	gcc -Wall -std=c11 -g -c bench.c

getmem.o: getmem.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c getmem.c

freemem.o: freemem.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c freemem.c

get_mem_status.o: get_mem_status.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c get_mem_status.c

mem_utils.o: mem_utils.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c mem_utils.c

print_heap.o: print_heap.c mem.h mem_impl.h
	gcc -Wall -std=c11 -g -c print_heap.c


#Not sure if this is the way to run test files.
test: bench #complies all files
	./bench #execute file
# A "phony" target to remove built files and backups
clean:
	rm -f *.o bench *~
