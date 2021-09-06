/************************************************************************

mymalloc.c

This program implements malloc and free functions. The free space has 
been allocated using mmap, and first fit strategy has been used for the 
selection of the block.

************************************************************************/

#include <stdlib.h>
#include <sys/mman.h>
#include "mymalloc.h"

// Allocating space of approximately 20000 using mmap
int memory = 20000;

void initialize_freelist(){
/* This function initializes freelist by allocating the free space using
mmap, initializes the size, free flag and the next item in freelist. */
	printf("Allocating total  memory..\n");
	free_list = mmap(NULL, memory, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	free_list->size = memory - sizeof(struct block);
	printf("Total memory has been allocated. (Memory size: %d bytes)\n", free_list->size);
	//flag to indicate whether the block is free (1) or not (0)
	free_list->free = 1;
	free_list->next = NULL;
}

void split_block(int size){
/* Splits block if block size is greater than the number of bytes to be
allocated. */
	printf("Allocation resulted in splitting of a block (Internal fragmentation, block size > number of bytes). (Block size: %d, Number of bytes: %d) \n", current->size, size);
	struct block *new = (void*)((void*)current + size + sizeof(struct block));
	new->size = (current->size) - size - sizeof(struct block);
	new->free = 1;
	new->next = current->next;
	current->size = size;
	current->free = 0;
	current->next = new;
}

void *my_malloc(int no_of_bytes){
/* Allocates memory in the space created by mmap. To allocate memory, first fit strategy have been used.
*/
	printf("Allocating %d bytes in total memory..\n", no_of_bytes);
	//struct block *current, *previous;
	void *result;
	current = free_list;
	if (current->size < 0){
		printf("Sorry, block size should be greater than 0. (Current block size = %d). Please allocate more memory.\n", current->size);
		exit(0);
	}
	while((((current->size) < no_of_bytes)||((current->free) == 0)) && (current->next != NULL)){
		previous = current;
		current = current->next;
		printf("Skipping a block of %d bytes as number of bytes cannot fit in this block or is already filled with previous allocations..\n", previous->size);
 	}
	if((current->size) == no_of_bytes){
		printf("Allocating a block exactly equal to number of bytes. (Current size: %d, Number of Bytes: %d)\n",current->size, no_of_bytes);
		current->free = 0;
		result = (void*)(++current);
		return result;
	}
	else if((current->size) > (no_of_bytes + sizeof(struct block))){
		split_block(no_of_bytes);
		result = (void*)(++current);
		return result;
	}
	else{
		result = NULL;
		printf("Sorry. There is no sufficient memory to allocate.\n");
		return result;
	}
}

void merge_blocks(){
/* Merge the consecutive blocks if both of them are empty. */
	printf("Merging consecutive free blocks..\n");
	struct block *current, *previous;
	current = free_list;
	while((current->next) != NULL){
		if(current->free == 1 && current->next->free==1 && current->next->next){
			current->size += (current->next->size) + (sizeof(struct block));
			current->next = current->next->next;

		} else if(current->free == 1 && current->next->free==1 && !current->next->next){
			current->size += (current->next->size) + (sizeof(struct block));
		}
	previous = current;
	current = current->next;
	}
}

void my_free(void* ptr){
/* Frees the consecutive blocks and set the flag of the freed space to 1.*/
	struct block* current = ptr;
	-- current;
	//printf("Freeing blocks of size %d\n", current->size);
	current->free = 1;
	printf("Freeing blocks of size approximately %d\n", current->size);
	merge_blocks();
}

