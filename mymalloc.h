#include <stdio.h>

struct block{
 size_t size;
 int free;
 struct block *next;
}block;

struct block *free_list;
struct block *current;

void initialize_freelist();
void split_block(size_t size);
void *my_malloc(size_t no_of_bytes);
void merge_blocks();
void my_free(void* ptr);
