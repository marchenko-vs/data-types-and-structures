#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bs_tree.h"
#include "avl_tree.h"
#include "hash_table.h"
#include "file_array.h"

#define rdtscll(val) __asm__ __volatile__("rdtsc" :"=A"(val))

void print_menu(void)
{
    printf("1. Add an element into all structures.\n"
        "2. Print all structures.\n"
        "3. Efficiency analysis.\n"
        "0. Exit.\n");
}

void print_introduction(void)
{
    printf("==================================================================="
        "=============\n                               Laboratory work #6\n"
        "======================================================================"
        "==========\n");
}

void efficiency_analysis(size_t size)
{
    srand(time(0));

    unsigned long long time_start, time_end;
    size_t memory;
    int comparisons, sum_comparisons = 0;
    int new_element;

    tree_node_t *bs_tree = NULL;
    memory = sizeof(tree_node_t) * size;

    rdtscll(time_start);

    for (size_t i = 0; i < size; i++)
    {
        comparisons = 0;
        new_element = rand() % 500;

        bs_tree = bs_insert(bs_tree, new_element, &comparisons);

        sum_comparisons += comparisons;
    }

    rdtscll(time_end);

    bs_free(bs_tree);

    printf("Data for %llu elements:\n", size);
    printf("----------+---------------+-------------+----------------------\n");
    printf(" Data type| Memory, bytes | Comparisons | Time, ticks\n");
    printf("----------+---------------+-------------+----------------------\n");
    printf(" BS tree  |%-15llu|%-13lf|%-22llu\n", memory, 
        (double)sum_comparisons / size, (time_end - time_start) / size);
    printf("----------+---------------+-------------+----------------------\n");

    avl_node_t *avl_tree = NULL;
    memory = sizeof(avl_node_t) * size;
    sum_comparisons = 0;

    rdtscll(time_start);

    for (size_t i = 0; i < size; i++)
    {
        comparisons = 0;
        new_element = rand() % 500;

        avl_tree = avl_insert(avl_tree, new_element, &comparisons);

        sum_comparisons += comparisons;
    }

    rdtscll(time_end);

    avl_free(avl_tree);

    printf(" AVL tree |%-15llu|%-13lf|%-22llu\n", memory, 
        (double)sum_comparisons / size, (time_end - time_start) / size);
    printf("----------+---------------+-------------+----------------------\n");

    hash_table_t table = { 0 };
    ht_init(&table, size);
    memory = sizeof(table) + table.size * sizeof(int);
    sum_comparisons = 0;

    rdtscll(time_start);

    for (size_t i = 0; i < size; i++)
    {
        comparisons = 0;
        new_element = rand() % 500;

        ht_insert(&table, new_element, &comparisons, hash_1);

        sum_comparisons += comparisons; 
    }

    rdtscll(time_end);

    ht_free(&table);

    printf("Hash table|%-15llu|%-13lf|%-22llu\n", memory, 
        (double)sum_comparisons / size, (time_end - time_start) / size);
    printf("----------+---------------+-------------+----------------------\n");

    array_t array = { NULL, size, 0 };
    array_init(&array);
    memory = sizeof(array_t) + array.size * sizeof(int);
    sum_comparisons = 0;

    rdtscll(time_start);

    for (size_t i = 0; i < size; i++)
    {
        comparisons = 0;
        new_element = rand() % 500;

        array_insert(&array, new_element, &comparisons);

        sum_comparisons += comparisons; 
    }

    rdtscll(time_end);

    array_free(&array);

    printf("   File   |%-15llu|%-13lf|%-22llu\n", memory, 
        (double)sum_comparisons / size, (time_end - time_start) / size);
    printf("----------+---------------+-------------+----------------------\n");
}
