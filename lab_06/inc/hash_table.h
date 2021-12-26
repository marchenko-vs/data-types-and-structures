#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <stdlib.h>

#include "file_array.h"

typedef struct
{
    int *array;
    size_t size;
} hash_table_t;

int ht_init(hash_table_t *table, size_t size);
int hash_2(int data, int size);
int hash_1(int data, int size);
int ht_insert(hash_table_t *table, int data, 
int *comparisons, int (*func)(int, int));
int ht_search(hash_table_t *table, int data, int (*func)(int, int));
int ht_remove(hash_table_t *table, int data, int (*func)(int, int));
void ht_print(hash_table_t *table);
void ht_restructure(hash_table_t *table, array_t *array,
int (*func)(int, int));
void ht_free(hash_table_t *table);

#endif // _HASH_TABLE_H_
