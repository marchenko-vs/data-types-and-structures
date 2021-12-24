#ifndef _IO_FUNCTIONS_
#define _IO_FUNCTIONS_

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int *array;
	size_t size;
	size_t current_size;
} array_t;

int get_array_size(FILE *f);
int array_init(array_t *array);
void array_free(array_t *array);
int array_insert(array_t *array, int number, int *comparisons);
int form_array(FILE *f, array_t *array);
void print_array(array_t *array);
int cmp(const void *a, const void *b);
int get_new_element(void);

#endif // _IO_FUNCTIONS_
