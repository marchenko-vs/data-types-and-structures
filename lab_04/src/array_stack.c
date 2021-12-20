#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_stack.h"
#include "info.h"

int push_array(char **ptr_curr, char *ptr_end, char value)
{
    if (*ptr_curr >= ptr_end - 1)
    {
        printf(RED"Ошибка: стек-массив переполнен.\n"RESET);

        return ERR_STACK_OVERFLOW;
    }

    (*ptr_curr)++;
    **ptr_curr = value;

    return EXIT_SUCCESS;
}

int pop_array(char **ptr_curr, char *ptr_beg)
{
    if (*ptr_curr < ptr_beg)
    {
        printf(RED"Ошибка: стек-массив пуст.\n"RESET);

        return ERR_EMPTY_STACK;
    }

    (*ptr_curr)--;

    return EXIT_SUCCESS;
}

void print_array(char *ptr_beg, char *ptr_curr)
{
    if (ptr_beg > ptr_curr)
    {
        printf(GREEN"Стек-массив пуст.\n"RESET);

        return;
    }

    printf(GREEN"Текущее состояние стека-массива:\n"RESET);

    while (ptr_beg <= ptr_curr)
    {
        printf("Элемент: %c; адрес: %p\n", *ptr_beg, ptr_beg);

        ptr_beg++;
    }
}

int array_check_brackets(size_t size)
{
    array_stack_t array_stack = { NULL, NULL, NULL};

    array_stack.stack = malloc(MAX_ARRAY_SIZE * sizeof(char));

    if (!array_stack.stack)
    {
        printf(RED"Ошибка: не удалось выделить память под стек.\n"RESET);

        return ERR_MEMORY_ALLOC;
    }

    array_stack.last_elem = array_stack.stack + MAX_ARRAY_SIZE;
    array_stack.curr_elem = array_stack.stack - 1;

    char *input_string = malloc(size * sizeof(char));

    if (!input_string)
    {
        printf("Ошибка: не удалось выделить память под выражение.\n");
        free(array_stack.stack);

        return ERR_MEMORY_ALLOC;
    }

    printf("Введите выражение:\n");

    if (!fgets(input_string, size, stdin))
    {
        free(array_stack.stack);

        return ERR_INPUT_STRING;
    }

    if (strlen(input_string) == 1)
    {
        free(array_stack.stack);

        return ERR_EMPTY_STRING;
    }
    
    if (strlen(input_string) > MAX_ARRAY_SIZE + 1)
    {
        free(array_stack.stack);

        return ERR_BUFFER_OVERFLOW;
    }

    input_string[strlen(input_string) - 1] = '\0';

    for (char *ptr = input_string; *ptr; ptr++)
    {
        if (*ptr == '(' || *ptr == '[' || *ptr == '{')
            push_array(&array_stack.curr_elem, array_stack.last_elem, *ptr);

        if (*ptr == ')' || *ptr == ']' || *ptr == '}')
        {
            if (!array_stack.curr_elem)
            {
                free(array_stack.stack);
                free(input_string);

                return EXIT_FAILURE;
            }
            
            if ((*ptr == ')' && *array_stack.curr_elem == '(') ||
                (*ptr == ']' && *array_stack.curr_elem == '[') ||
                (*ptr == '}' && *array_stack.curr_elem == '{'))
                pop_array(&array_stack.curr_elem, array_stack.stack);
            else
            {
                free(array_stack.stack);
                free(input_string);

                return EXIT_FAILURE;
            }
        }
    }

    int rc = EXIT_SUCCESS;

    if (array_stack.curr_elem != array_stack.stack - 1)
        rc = EXIT_FAILURE;

    free(array_stack.stack);
    free(input_string);

    return rc;
}
