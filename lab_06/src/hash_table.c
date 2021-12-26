#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

#include "hash_table.h"
#include "file_array.h"

#define GOLDEN_RATIO 0.6180339

static bool is_prime(size_t number)
{
    if (number < 2)
        return false;

    for (size_t i = 2; i <= sqrt(number); i++)
    {
        if (number % i == 0)
            return false;
    }
    
    return true;
}

int hash_2(int data, int size)
{  
    return (int)(size * (data * GOLDEN_RATIO - 
        (int)(data * GOLDEN_RATIO / 1.0f) * 1.0f));
}

int hash_1(int data, int size)
{
    return data % size;
}

int ht_init(hash_table_t *table, size_t size)
{
    size *= 2;

    while (!is_prime(size))
        size++;

    table->array = malloc(size * sizeof(int));

    if (!table->array)
        return EXIT_FAILURE;

    table->size = size;

    for (size_t i = 0; i < size; i++)
        table->array[i] = -1;

    return EXIT_SUCCESS;
}

int ht_insert(hash_table_t *table, int data,
int *comparisons, int (*func)(int, int))
{
    if (data < 0)
        return -1;

    int key = func(data, table->size);

    *comparisons = 0;

    if (table->array[key] == -1)
    {
        table->array[key] = data;
        (*comparisons)++;

        return EXIT_SUCCESS;
    }

    if (table->array[key] == data)
    {
        (*comparisons)++;
        
        return -2;
    }

    for (size_t i = 1; i < table->size; i++)
    {
        key = func(data + i, table->size);

        (*comparisons)++;

        if (table->array[key] == -1)
        {
            table->array[key] = data;

            return EXIT_SUCCESS;
        }
    }

    return -3;
}

int ht_search(hash_table_t *table, int data, int (*func)(int, int))
{
    if (data < 0)
        return -1;

    int key = func(data, table->size);

    if (table->array[key] == data)
        return key;

    if (table->array[key] == -1)
        return -2;

    for (size_t i = 1; i < table->size; i++)
    {
        key = func(data + i, table->size);

        if (table->array[key] == data)
            return key;
    }

    return -3;
}

int ht_remove(hash_table_t *table, int data, int (*func)(int, int))
{
    if (data < 0)
        return -1;

    int key = func(data, table->size);

    if (table->array[key] == data)
    {
        table->array[key] = -1;

        return EXIT_SUCCESS;
    }

    if (table->array[key] == -1)
        return -2;

    for (size_t i = 1; i < table->size; i++)
    {
        key = func(data + i, table->size);

        if (table->array[key] == data)
        {
            table->array[key] = -1;

            return EXIT_SUCCESS;
        }
    }

    return -3;
}

void ht_restructure(hash_table_t *table, array_t *array,
int (*func)(int, int))
{
    for (size_t i = 0; i < table->size; i++)
        table->array[i] = -1;

    int comparisons;

    for (size_t i = 0; i < array->current_size; i++)
        ht_insert(table, array->array[i], &comparisons, func);
}

void ht_print(hash_table_t *table)
{
    printf("Hash table\n");

    for (size_t i = 0; i < table->size; i++)
        if (table->array[i] != -1)
            printf("%5llu | %5d\n", i, table->array[i]);
        else
            printf("%5llu |\n", i);

    printf("\n");
}

void ht_free(hash_table_t *table)
{
    if (table->array != NULL)
        free(table->array);
}
