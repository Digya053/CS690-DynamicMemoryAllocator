#include <stdio.h>
#include "mymalloc.h"

/*
* Main function for initializing freelist, making malloc and free calls 
*/

int main(){
	initialize_freelist();

	printf("==============================================First malloc call:==============================================\n");
	int *p = (int*)my_malloc(200*sizeof(int));
	//my_free(p);

	printf("==============================================Second malloc call:==============================================\n");
	int *q = (int*)my_malloc(100*sizeof(int));
	//my_free(q);

	printf("==============================================Third malloc call:==============================================\n");
	char *r = (char*)my_malloc(10*sizeof(char));
	my_free(r);
	my_free(q);

	printf("==============================================Fourth malloc call:==============================================\n");
	double *s = (double*)my_malloc(1000*sizeof(double));
	my_free(s);

	printf("==============================================Fifth malloc call:==============================================\n");
        double *w = (double*)my_malloc(1000*sizeof(double));
        //my_free(w);

	printf("==============================================Sixth malloc call:==============================================\n");
        char *x = (char*)my_malloc(10*sizeof(char));
        //my_free(r);

	printf("==============================================Seventh malloc call:==============================================\n");
        int *y = (int*)my_malloc(100*sizeof(int));
        //my_free(q);	

}
