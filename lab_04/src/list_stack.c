#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_stack.h"
#include "info.h"

#define FREE_AREA_SIZE 16

void **free_area;
int n = 0;

void init_free_area(void)
{
    free_area = malloc(FREE_AREA_SIZE * sizeof(void *));
}

struct node *push_list(struct node *last_elem, char value)
{
    struct node *tmp = malloc(sizeof(struct node));

    tmp->value = value;
    tmp->prev_elem = last_elem;

    return tmp;
}

struct node *pop_list(struct node *last_elem, int fl_an)
{
    if (!last_elem)
    {
        printf(RED"Ошибка: стек пуст.\n"RESET);

        return NULL;
    }

    struct node *tmp = last_elem->prev_elem;

    if (fl_an)
        free_area[n++] = (void *)last_elem;

    free(last_elem);

    return tmp;
}

void print_list(struct node *last_elem)
{
    if (!last_elem)
    {
        printf(RED"Ошибка: стек пуст.\n"RESET);

        return;
    }

    printf(GREEN"Текущее состояние стека:\n"RESET);

    while (last_elem)
    {
        printf(GREEN"Элемент: %c; адрес: %p\n"RESET, last_elem->value, 
            (void *)last_elem);

        last_elem = last_elem->prev_elem;
    }

    printf(GREEN"Свободная область:\n"RESET);

    for (size_t j = 0; j < n; j++)
        printf(GREEN"Адрес: %p\n"RESET, free_area[j]);
}

int list_check_brackets(size_t size)
{
    struct node *last_elem = NULL;

    char *input_string = malloc(size * sizeof(char));

    if (!input_string)
    {
        printf(RED"Ошибка: не удалось выделить память под выражение.\n"RESET);

        return ERR_MEMORY_ALLOC;
    }

    printf("Введите выражение:\n");

    if (!fgets(input_string, size, stdin))
        return ERR_INPUT_STRING;

    if (strlen(input_string) == 1)
        return ERR_INPUT_STRING;

    input_string[strlen(input_string) - 1] = '\0';

    for (char *ptr = input_string; *ptr; ptr++)
    {
        if (*ptr == '(' || *ptr == '[' || *ptr == '{')
            last_elem = push_list(last_elem, *ptr);

        if (*ptr == ')' || *ptr == ']' || *ptr == '}')
        {
            if (!last_elem)
            {
                free(input_string);

                return EXIT_FAILURE;
            }
            
            if ((*ptr == ')' && last_elem->value == '(') ||
                (*ptr == ']' && last_elem->value == '[') ||
                (*ptr == '}' && last_elem->value == '{'))
                last_elem = pop_list(last_elem, 0);
            else
            {
                free(input_string);

                return EXIT_FAILURE;
            }
        }
    }

    int rc = EXIT_SUCCESS;

    if (last_elem)
        rc = EXIT_FAILURE;

    free(input_string);

    return rc;
}
