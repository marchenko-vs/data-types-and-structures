#include "sort.h"
#include "country.h"
#include "country_array.h"
#include <sys/time.h>
#include <inttypes.h>

int compare(long long *population_1, long long *population_2)
{
    if (*population_1 > *population_2)
        return 1;

    if (*population_1 < *population_2)
        return -1;

    return 0;
}

void table_swap(country_t *country_1, country_t *country_2)
{
    country_t temporary = { 0 };

    temporary = *country_1;
    *country_1 = *country_2;
    *country_2 = temporary;
}

void key_swap(key_table_t *key_1, key_table_t *key_2)
{
    key_table_t temporary = { 0 };

    temporary = *key_1;
    *key_1 = *key_2;
    *key_2 = temporary;
}

void table_bubble_sort(country_t *array, const int size)
{
    for (size_t i = 0; i < size - 1; i++)    
        for (size_t j = 0; j < size - i - 1; j++)
            if (compare(&array[j].population, &array[j + 1].population) > 0)
                table_swap(&array[j], &array[j + 1]);
}

void key_bubble_sort(key_table_t *array, const int size)
{
    for (size_t i = 0; i < size - 1; i++)    
        for (size_t j = 0; j < size - i - 1; j++)
            if (compare(&array[j].key, &array[j + 1].key) > 0)
                key_swap(&array[j], &array[j + 1]);
}

void table_shell_sort(country_t *array, const int size)
{    
    int i, j, step;
    country_t tmp;
    for (step = size / 2; step > 0; step /= 2)
        for (i = step; i < size; i++)
        {
            tmp = array[i];
            for (j = i; j >= step; j -= step)
            {
                if (compare(&tmp.population, &array[j - step].population) < 0)
                    array[j] = array[j - step];
                else
                    break;
            }
            array[j] = tmp;
        }
}

void key_shell_sort(key_table_t *array, const int size)
{ 
    int i, j, step;
    key_table_t tmp;
    for (step = size / 2; step > 0; step /= 2)
        for (i = step; i < size; i++)
        {
            tmp = array[i];
            for (j = i; j >= step; j -= step)
            {
                if (compare(&tmp.key, &array[j - step].key) < 0)
                    array[j] = array[j - step];
                else
                    break;
            }
            array[j] = tmp;
        }
}

void sort_comparison(country_t *table, key_table_t *key_table, const int size)
{
    country_t array_to_sort_1[MAX_TABLE_SIZE] = {0};
    copy_array(table, array_to_sort_1, size);
    struct timeval tv_start_bubble, tv_end_bubble;
    int64_t overall_time_bubble;
    gettimeofday(&tv_start_bubble, NULL);
    table_bubble_sort(array_to_sort_1, size);
    gettimeofday(&tv_end_bubble, NULL);
    overall_time_bubble =
    (tv_end_bubble.tv_sec - tv_start_bubble.tv_sec) * 1000000LL + 
    (tv_end_bubble.tv_usec - tv_start_bubble.tv_usec);

    country_t array_to_sort_2[MAX_TABLE_SIZE] = {0};
    copy_array(table, array_to_sort_2, size);
    struct timeval tv_start_shell, tv_end_shell;
    int64_t overall_time_shell;
    gettimeofday(&tv_start_shell, NULL);
    table_shell_sort(array_to_sort_2, size);
    gettimeofday(&tv_end_shell, NULL);
    overall_time_shell = (tv_end_shell.tv_sec - tv_start_bubble.tv_sec)
    * 1000000LL + (tv_end_shell.tv_usec - tv_start_bubble.tv_usec);

    key_table_t keys_to_sort_1[MAX_TABLE_SIZE] = {0};
    copy_key_array(key_table, keys_to_sort_1, size);
    struct timeval tv_start_k_bubble, tv_end_k_bubble;
    int64_t overall_time_k_bubble;
    gettimeofday(&tv_start_k_bubble, NULL);
    key_bubble_sort(keys_to_sort_1, size);
    gettimeofday(&tv_end_k_bubble, NULL);
    overall_time_k_bubble =
    (tv_end_k_bubble.tv_sec - tv_start_k_bubble.tv_sec) * 1000000LL + 
    (tv_end_k_bubble.tv_usec - tv_start_k_bubble.tv_usec);

    key_table_t keys_to_sort_2[MAX_TABLE_SIZE] = {0};
    copy_key_array(key_table, keys_to_sort_2, size);
    struct timeval tv_start_k_shell, tv_end_k_shell;
    int64_t overall_time_k_shell;
    gettimeofday(&tv_start_k_shell, NULL);
    key_shell_sort(keys_to_sort_2, size);
    gettimeofday(&tv_end_k_shell, NULL);
    overall_time_k_shell =
    (tv_end_k_shell.tv_sec - tv_start_k_shell.tv_sec) * 1000000LL + 
    (tv_end_k_shell.tv_usec - tv_start_k_shell.tv_usec);

    printf("---------------+------------------------+-"
        "----------------\n");
    printf("  Тип таблицы  | Пузырьковая сортировка | "
        "Сортировка Шелла\n");
    printf("---------------+------------------------+-"
        "----------------\n");
    printf("   Исходная    |%-24" PRId64 "|%-17" PRId64 "\n",
        overall_time_bubble, overall_time_shell);
    printf("   Ключей      |%-24" PRId64 "|%-17" PRId64 "\n",
        overall_time_k_bubble, overall_time_k_shell);
    printf("---------------+------------------------+-"
        "----------------\n");
}
