#include "sort.h"
#include <sys/time.h>
#include <inttypes.h>

void table_swap(country_t *country_1, country_t *country_2)
{
    country_t temporary = { 0 };

    temporary = *country_1;
    *country_1 = *country_2;
    *country_2 = temporary;
}

void key_swap(key_t *key_1, key_t *key_2)
{
    key_t temporary = { 0 };

    temporary = *key_1;
    *key_1 = *key_2;
    *key_2 = temporary;
}

int compare(long long *population_1, long long *population_2)
{
    if (*population_1 > *population_2)
        return 1;

    if (*population_1 < *population_2)
        return -1;

    return 0;
}

void table_bubble_sort(country_t *array, const int size)
{
    struct timeval tv_start, tv_end;
    int64_t overall_time;
    gettimeofday(&tv_start, NULL);
    
    for (size_t i = 0; i < size - 1; i++)    
        for (size_t j = 0; j < size - i - 1; j++)
            if (compare(&array[j].population, &array[j + 1].population) > 0)
                table_swap(&array[j], &array[j + 1]);

    gettimeofday(&tv_end, NULL);
    overall_time = (tv_end.tv_sec - tv_start.tv_sec) * 1000000LL + 
    (tv_end.tv_usec - tv_start.tv_usec);
    printf("Bubble sort time: %" PRId64 " ms\n", overall_time);
}

void key_bubble_sort(key_t *array, const int size)
{
    for (size_t i = 0; i < size - 1; i++)    
        for (size_t j = 0; j < size - i - 1; j++)
            if (compare(&array[j].key, &array[j + 1].key) > 0)
                key_swap(&array[j], &array[j + 1]);
}

void table_shell_sort(country_t *array, const int size)
{
    struct timeval tv_start, tv_end;
    int64_t overall_time;
    gettimeofday(&tv_start, NULL);
    
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
    gettimeofday(&tv_end, NULL);
    overall_time = (tv_end.tv_sec - tv_start.tv_sec) * 1000000LL + 
    (tv_end.tv_usec - tv_start.tv_usec);
    printf("Shell sort time: %" PRId64 " ms\n", overall_time);
}

void copy_array(country_t *array_1, country_t *array_2, const int size)
{
    for (size_t i = 0; i < size; i++)
        array_2[i] = array_1[i];
}
