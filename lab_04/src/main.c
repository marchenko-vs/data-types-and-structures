#include <stdio.h>
#include <stdlib.h>
#include "array_stack.h"
#include "list_stack.h"
#include "info.h"

#define MAX_SIZE 1000

#define ERR_OPTION -1

int main(void)
{
    setbuf(stdout, NULL);
    print_introduction();

    int option = 1;
    char *array_stack = malloc(MAX_SIZE * sizeof(char));

    if (!array_stack)
    {
        printf(RED"Ошибка: не удалось выделить память под стек.\n"RESET);

        return ERR_MEMORY_ALLOC;
    }

    char *end_elem = array_stack + MAX_SIZE;
    char *last_array = array_stack - 1;

    struct node *last_elem = NULL;

    while (option != 0)
    {
        print_menu();

        if (scanf("%d", &option) != 1)
        {
            printf(RED"Ошибка: неверно введен номер меню.\n"RESET);
            free(array_stack);

            return ERR_OPTION;
        }

        getchar();

        if (option < 0 || option > 10)
        {
            printf(RED"Ошибка: пункт меню должен быть от 0 до 10.\n"RESET);
        }

        if (option == 1)
        {
            int rc = array_check_brackets(MAX_SIZE);
            
            if (rc == EXIT_SUCCESS)
                printf(GREEN"Выражение корректно.\n"RESET);
            else if (rc == ERR_INPUT_STRING)
                printf(RED"Ошибка: пустая входная строка.\n"RESET);
            else
                printf(RED"Выражение некорректно.\n"RESET);
        }

        if (option == 2)
        {
            char elem;

            printf("Введите новый элемент стека (символ): ");
            scanf("%c", &elem);

            if (push_array(&last_array, end_elem, elem) == EXIT_SUCCESS)
                printf(GREEN"Элемент успешно добавлен.\n"RESET);
        }

        if (option == 3)
        {
            if (pop_array(&last_array, array_stack) == EXIT_SUCCESS)
                printf(GREEN"Элемент успешно удален.\n"RESET);
        }

        if (option == 4)
        {
            print_array(array_stack, last_array);
        }

        if (option == 5)
        {
            if (list_check_brackets(MAX_SIZE) == EXIT_SUCCESS)
                printf(GREEN"Выражение корректно.\n"RESET);
            else
                printf(RED"Выражение некорректно.\n"RESET);
        }

        if (option == 6)
        {
            char elem;

            printf("Введите новый элемент стека (символ): ");
            scanf("%c", &elem);
            last_elem = push_list(last_elem, elem);
            printf(GREEN"Элемент успешно добавлен.\n"RESET);
        }

        if (option == 7)
        {
            if ((last_elem = pop_list(last_elem, 0)))
                printf(GREEN"Элемент успешно удален.\n"RESET);
        }

        if (option == 8)
        {
            print_list(last_elem);
        }

        if (option == 10)
        {
            efficiency_analysis(100);
            efficiency_analysis(1000);
            efficiency_analysis(10000);
            efficiency_analysis(100000);
        }

        if (option == 0)
        {
            printf(GREEN"Выполнение программы завершено.\n"RESET);
            free(array_stack);

            return EXIT_SUCCESS;
        }
    }

    free(array_stack);
    
    return EXIT_FAILURE;
}
