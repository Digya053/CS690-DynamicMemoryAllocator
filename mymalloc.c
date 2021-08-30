#include<stdlib.h>
#include<sys/mman.h>
#include "mymalloc.h"

int memory = 20000;

struct block *free_list;
struct block *current;

void initialize_freelist(){
 printf("Allocating total  memory..\n");
 free_list = mmap(NULL, memory, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
 printf("Total memory has been allocated. (Memory size: approximately %d bytes)\n", memory);
 free_list->size = memory-sizeof(struct block);
 free_list->free = 1;
 free_list->next = NULL;
}

void split_block(size_t size){
 printf("Allocation resulted in splitting of a block (Internal fragmentation, block size > number of bytes). (Block size: %d, Number of bytes: %d) \n", current->size, size);
 struct block *new = (void*)((void*)current + size + sizeof(struct block));
 new->size = (current->size) - size - sizeof(struct block);
 new->free = 1;
 new->next = NULL;
 current->size = size;
 current->free = 0;
 current->next = new;
}

void *my_malloc(size_t no_of_bytes){
 printf("Allocating %d bytes in total memory..\n", no_of_bytes);
 struct block *previous;
 void *result;
 current = free_list;
 if (current->size < 0){
   printf("Sorry, block size should be greater than 0. (Current block size = %d). Please allocate more memory.\n", current->size);
   exit(0);
}
 while((((current->size) < no_of_bytes)||((current->free) == 0)) && (current->next!=NULL)){
  previous = current;
  current = current->next;
  printf("Skipping a block of %d bytes as number of bytes cannot fit in this block or is already filled with previous allocations..\n", previous->size);
 }
  if((current->size) == no_of_bytes){
  current->free=0;
  result = (void*)(++current);
  printf("Allocating a block exactly equal to number of bytes. (Current size: %d, Number of Bytes: %d)\n",current->size, no_of_bytes);
  printf("Pointer pointing to address: %d after allocation.\n", result);
  return result;
 }
 else if((current->size) > (no_of_bytes + sizeof(struct block))){
  split_block(no_of_bytes);
  result = (void*)(++current);
  printf("Pointer pointing to address: %d after allocation.\n", result);
  return result;
 }
  else{
  result = NULL;
  printf("Sorry. There is no sufficient memory to allocate.\n");
  return result;
 }
}

void merge_blocks(){
 printf("Merging consecutive free blocks..\n");
 struct block *current,*previous;
 current = free_list;
 while((current->next)!=NULL){
  if((current->free) && (current->next->free)){
   current->size += (current->next->size) + sizeof(struct block);
   current->next = current->next->next;
  }
  previous = current;
  current = current->next;
 }
 printf("Total coalesed memory after merging free blocks: %d\n", current->size);
}

void my_free(void* ptr){
  printf("Freeing allocated blocks..\n");
  struct block* current = &ptr;
  --current;
  current->free = 1;
  printf("After freeing memory, pointer pointing to address: %d\n",current->size);
  merge_blocks();
}

