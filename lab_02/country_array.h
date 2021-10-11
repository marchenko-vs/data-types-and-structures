#ifndef _COUNTRY_ARRAY_H_

#define _COUNTRY_ARRAY_H_

#include <stdio.h>
#include "country.h"

int read_all_data(FILE *stream, country_t *array, key_table_t *key_array, size_t *size);
int find_by_sport(FILE *stream, country_t *country, const int size);
int array_push(country_t *country, key_table_t *key, size_t *size);
int array_remove(country_t *country, size_t *size);
void print_all_data(FILE *stream, country_t *country, const int size);
void print_by_keys(FILE *stream, country_t *country, key_table_t *keys, const int size);
void copy_array(country_t *array_1, country_t *array_2, const int size);
void copy_key_array(key_table_t *array_1, key_table_t *array_2, const int size);
void print_keys_table(FILE *stream, key_table_t *array, const int size);

#endif
