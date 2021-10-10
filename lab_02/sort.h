#ifndef _SORT_H_

#define _SORT_H_

#include "country.h"

int compare(long long *population_1, long long *population_2);
void table_swap(country_t *country_1, country_t *country_2);
void key_swap(key_t *key_1, key_t *key_2);
void table_bubble_sort(country_t *array, const int size);
void key_bubble_sort(key_t *array, const int size);
void table_shell_sort(country_t *array, const int size);
void key_shell_sort(key_t *array, const int size);
void sort_comparison(country_t *table, key_t *key_table, const int size);

#endif
