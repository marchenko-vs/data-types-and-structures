#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "array.h"

#define HASH_STEP 3

typedef struct
{
    int **body;
    int basis;
    int size;
    int fill;
} hash_table_t;

void create_hash_table(hash_table_t *hash, int size, int base);
void delete_hash_table(hash_table_t *hash);

int add_to_hash_table(hash_table_t *hash, int *element, int *comp_times, int max_conflict);
int find_element_in_hash_table(hash_table_t *hash, int *element, int *cmp);
void change_basis(hash_table_t *hash, int basic);

int del_element_in_hash_table(hash_table_t *hash, int *element);

int parse_file_hash_table(hash_table_t *hash, FILE *source);
int print_hash_table(hash_table_t *hash);

#endif // _HASH_TABLE_H_
