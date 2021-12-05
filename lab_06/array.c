#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include "array.h"
#include "universal.h"

// CDIO
// Create array
int create_array(void *array_p, int size, size_t size_elem)
{
    int error_code = 1;
    if (size > 0)
    {
        error_code = 0;

        void *new_array = calloc(size, size_elem);

        memmove(array_p, &new_array, sizeof(void*));
        if (!new_array)
        {
            error_code = 2;
        }
    }

    return error_code;
}

// Delete array
void delete_array(void *array_p)
{
    void *null_pointer = NULL;
    free(*(char**)array_p);
    memmove(array_p, &null_pointer, sizeof(void*));
}

// Enter array
int input_array(void *array, int size, size_t elem_size, FILE* source, int (*fscanf_elem)(FILE*, void*))
{
    int error_code = 1;

    if (is_array_correct(array, size))
    {
        error_code = 0;
        int i = 0;
        while (!feof(source) && i < size && (fscanf_elem(source, (char*)array + i * elem_size) == 1))
        {
            i++;
        }

        if (i != size)
        {
            error_code = 2;
        }
    }

    return error_code;
}

// Print array
int print_array(void *array, int size, size_t size_elem, FILE* dest, int (*fprintf_elem)(FILE*, void*))
{
    int error_code = 1;

    if (is_array_correct(array, size))
    {
        error_code = 0;

        error_code = !fprintf_elem(dest, array);
        int i = 1;
        while (i < size && !error_code)
        {
            fprintf(dest, " ");
            error_code = !fprintf_elem(dest, (char*)array + i * size_elem);
            i++;
        }
        fprintf(dest, "\n");
    }

    return error_code;
}

// Copy array
// TODO memmove valgrind error check
int copy_array(void *array_dest, void *array_source, int size, size_t size_elem)
{
    int error_code = 1;
    if (is_array_correct(array_source, size) && is_array_correct(array_dest, size))
    {
        error_code = 0;
        memmove(array_dest, array_source, size * size_elem);
    }

    return error_code;
}

// Move to end
int move_to_end(void *array, int size, size_t size_elem, int index)
{
    int error_code = 1;

    if (is_array_correct(array, size) && is_position_correct_arr(size, index))
    {
        error_code = 0;

        void *cur_element = malloc(size_elem);
        memmove(cur_element, (char*)array + index * size_elem, size_elem);

        while ((index + 1) < size)
        {
            memmove((char*)array + index * size_elem, (char*)array + (index + 1) * size_elem, size_elem);
            index++;
        }
        memmove((char*)array + index * size_elem, cur_element, size_elem);
        free(cur_element);
    }

    return error_code;
}

// Change size
int change_size_array(void *array_p, int new_size, size_t size_elem)
{
    int error_code = 3;

    void *new_array_head = realloc(*(char**)array_p, new_size * size_elem);

    if (new_array_head || new_size == 0)
    {
        error_code = 0;
        memmove(array_p, &new_array_head, sizeof(void*));
    }

    return error_code;
}

// Insert to position
int insert_to_position(void *array, int size, size_t size_elem, void *value, int pos)
{
    int error_code = 1;
    if (is_array_correct(array, size) && is_position_correct_arr(size, pos))
    {
        error_code = 0;

        size--;
        while (size != pos)
        {
            memmove((char*)array + (size - 1) * size_elem, (char*)array + size * size_elem, size_elem);
            size--;
        }
        memmove((char*)array + pos * size_elem, value, sizeof(size_elem));
    }

    return error_code;
}

int max_in_array(void *array, int size, size_t elem_size, int (*compare)(void*, void*))
{
    void *temp_max = array;
    int pos = 0;

    for (int i = 1; i < size; i++)
    {
        if (compare((char*)array + i * elem_size, temp_max) > 0)
        {
            pos = i;
            temp_max = (char*)array + i * elem_size;
        }
    }

    return pos;
}

int sum_elements(void *array, int size, size_t elem_size, void *result, int (*summator)(void*, void*))
{
    int error_code = 1;
    if (is_array_correct(array, size) && result)
    {
        void *temp_result = NULL;
        error_code = create_array(&temp_result, 1, elem_size);
        if (!error_code)
        {
            int pos = 0;
            for (int i = 0; i < size; pos += elem_size)
            {   
                summator(temp_result, (char*)array + pos);
                i++;
            }
            memmove((char*)result, temp_result, elem_size);
        }

        free(temp_result);
    }

    return error_code;
}

// Is array correct
int is_array_correct(void *array, int size)
{
    return (array && (size > 0));
}

// Is possition correct
int is_position_correct_arr(int size, int pos)
{
    return (pos >= 0 && (pos < size));
}
