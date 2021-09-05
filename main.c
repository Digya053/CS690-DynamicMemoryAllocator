#include <stdio.h>
#include "mymalloc.h"

/*
* Main function for initializing freelist, making malloc and free calls 
*/

int main(){
	initialize_freelist();

	printf("First malloc call:\n");
	int *p = (int*)my_malloc(20*sizeof(int));
	my_free(p);

	printf("Second malloc call:\n");
	char *q = (char*)my_malloc(300*sizeof(char));
	my_free(q);

	printf("Third malloc call:\n");
	int *r = (int*)my_malloc(2000*sizeof(int));
	my_free(r);

	printf("Fourth malloc call:\n");
	double *w = (double*)my_malloc(1000);
	my_free(w);
}
