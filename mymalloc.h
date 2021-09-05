#include <stdio.h>

/************************************************************************

mymalloc.h

This header file adds all function declarations to be defined in mymalloc.c. Also, initializes struct.
 
*************************************************************************/

/* Struct to keep track of size of each block, next block and whether it's free or not */
struct block{
 size_t size;
 int free;
 struct block *next;
}block;

/* Global structures free_list and current */
struct block *free_list;
struct block *current;

/* Function declarations */
void initialize_freelist();
void split_block(size_t size);
void *my_malloc(size_t no_of_bytes);
void merge_blocks();
void my_free(void* ptr);
