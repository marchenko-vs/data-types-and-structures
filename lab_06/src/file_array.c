#include <stdio.h>
#include <stdlib.h>

#include "file_array.h"

int get_array_size(FILE *f)
{
    if (!f)
        return -1;

    int temp, size = 0;

    while (fscanf(f, "%d", &temp) == 1)
    {
        size++;

        if (feof(f))
            return size;
    }

    if (!feof(f))
        return -2;

    return size;
}

int array_init(array_t *array)
{
    array->array = malloc(array->size * sizeof(int));

    if (!array->array)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int array_insert(array_t *array, int number, int *comparisons)
{
    if (number < 0)
        return -1;

    if (!array->array)
        return -2;

    *comparisons = 1;

    if (array->current_size == array->size)
    {
        int *temp = realloc(array->array, array->size * 2 * sizeof(int));

        if (!temp)
            return -3;

        array->array = temp;
        array->size *= 2;
    }

    int index;

    for (index = array->current_size - 1; index >= 0; index--)
    {
        (*comparisons)++;

        if (number > array->array[index])
        {
            index++;
            break;
        }
    }
        
    if (index < 0)
        index = 0;
        
    for (int i = array->current_size; i > index; i--)
        array->array[i] = array->array[i - 1];

    array->array[index] = number;
    array->current_size++;

    return EXIT_SUCCESS;
}

void array_free(array_t *array)
{
    if (array->array != NULL)
        free(array->array);
}

int form_array(FILE *f, array_t *array)
{
    if (!f)
        return -1;

    for (size_t i = 0; i < array->current_size; i++)
    {
        if (fscanf(f, "%d", &array->array[i]) != 1)
            return -2;

        if (array->array[i] < 0)
            return -3;
    }

    return EXIT_SUCCESS;
}

void print_array(array_t *array)
{
    printf("Numbers in file:\n");
    
    for (size_t i = 0; i < array->current_size; i++)
        printf("%d ", array->array[i]);

    printf("\n");
}

int cmp(const void *a, const void *b)
{
    if (*(int *)a > *(int *)b)
        return 1;

    if (*(int *)a < *(int *)b)
        return -1;

    return 0;
}

int get_new_element(void)
{
    int number;

    printf("Enter new number: ");

    if (scanf("%d", &number) != 1)
    {
        printf("Error: incorrect data type.\n");
        return -1;
    }

    if (number < 0)
    {
        printf("Error: new number must be non-negative.\n");
        return -2;
    }

    return number;
}
