#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_stack.h"
#include "array_stack.h"
#include "info.h"

#define FREE_AREA_SIZE 1000

void **free_mem_area;
int n = 0;

void init_area(void)
{
    free_mem_area = malloc(FREE_AREA_SIZE * sizeof(char *));
}

void free_area(void)
{
    free(free_mem_area);
}

struct node *push_list(struct node *last_elem, char value)
{
    struct node *tmp = malloc(sizeof(struct node));

    if (!tmp)
    {
        printf(RED"Ошибка: не удалось выделить память под "
            "элемента стека-списка.\n"RESET);

        return NULL;
    }

    tmp->value = value;
    tmp->prev_elem = last_elem;

    return tmp;
}

struct node *pop_list(struct node *last_elem, int option)
{
    if (!last_elem)
    {
        printf(RED"Ошибка: стек-список пуст.\n"RESET);

        return NULL;
    }

    struct node *tmp = last_elem->prev_elem;

    if (option == 1)
        free_mem_area[n++] = last_elem;

    free(last_elem);

    return tmp;
}

void print_list(struct node *last_elem)
{
    if (!last_elem)
        printf(GREEN"Стек-список пуст.\n"RESET);
    else
        printf(GREEN"Текущее состояние стека-списка:\n"RESET);

    while (last_elem)
    {
        printf("Элемент: %c; адрес: %p\n", last_elem->value, 
            (void *)last_elem);

        last_elem = last_elem->prev_elem;
    }

    printf(GREEN"Свободная область:\n"RESET);

    for (size_t j = 0; j < n; j++)
        printf("Адрес: %p\n", free_mem_area[j]);
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
        return ERR_EMPTY_STRING;
    
    if (strlen(input_string) > MAX_ARRAY_SIZE + 1)
        return ERR_BUFFER_OVERFLOW;

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
