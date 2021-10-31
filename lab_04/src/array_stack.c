#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array_stack.h"
#include "info.h"

int push_array(char **ptr_curr, char *ptr_end, char value)
{
    if (*ptr_curr >= ptr_end)
    {
        printf(RED"Ошибка: стек переполнен.\n"RESET);

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
        printf(RED"Ошибка: стек пуст.\n"RESET);

        return ERR_EMPTY_STACK;
    }

    (*ptr_curr)--;

    return EXIT_SUCCESS;
}

void print_array(char *ptr_beg, char *ptr_curr)
{
    if (ptr_beg > ptr_curr)
    {
        printf(RED"Стек пуст.\n"RESET);

        return;
    }

    printf(GREEN"Текущее состояние стека:\n"RESET);

    while (ptr_beg <= ptr_curr)
    {
        printf(GREEN"Элемент: %c; адрес: %p\n"RESET, *ptr_beg, ptr_beg);

        ptr_beg++;
    }
}

int array_check_brackets(size_t size)
{
    char *array_stack = malloc(size * sizeof(char));

    if (!array_stack)
    {
        printf("Ошибка: не удалось выделить память под стек.\n");

        return ERR_MEMORY_ALLOC;
    }

    char *input_string = malloc(size * sizeof(char));

    if (!input_string)
    {
        printf("Ошибка: не удалось выделить память под выражение.\n");
        free(array_stack);

        return ERR_MEMORY_ALLOC;
    }

    printf("Введите выражение:\n");

    if (!fgets(input_string, size, stdin))
        return ERR_INPUT_STRING;

    if (strlen(input_string) == 1)
        return ERR_INPUT_STRING;

    input_string[strlen(input_string) - 1] = '\0';

    char *end_elem = array_stack + size;
    char *last_elem = array_stack - 1;

    for (char *ptr = input_string; *ptr; ptr++)
    {
        if (*ptr == '(' || *ptr == '[' || *ptr == '{')
            push_array(&last_elem, end_elem, *ptr);

        if (*ptr == ')' || *ptr == ']' || *ptr == '}')
        {
            if (!last_elem)
            {
                free(array_stack);
                free(input_string);

                return EXIT_FAILURE;
            }
            
            if ((*ptr == ')' && *last_elem == '(') ||
                (*ptr == ']' && *last_elem == '[') ||
                (*ptr == '}' && *last_elem == '{'))
                pop_array(&last_elem, array_stack);
            else
            {
                free(array_stack);
                free(input_string);

                return EXIT_FAILURE;
            }
        }
    }

    int rc = EXIT_SUCCESS;

    if (last_elem != array_stack - 1)
        rc = EXIT_FAILURE;

    free(array_stack);
    free(input_string);

    return rc;
}
