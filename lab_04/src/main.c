#include <stdio.h>
#include <stdlib.h>
#include "array_stack.h"
#include "list_stack.h"
#include "info.h"

#define ERR_OPTION 7

int main(void)
{
    setbuf(stdout, NULL); // Отключение буферизации
    print_introduction();

    int option = 1;
    array_stack_t array_stack = { NULL, NULL, NULL};

    array_stack.stack = malloc(MAX_ARRAY_SIZE * sizeof(char));

    if (!array_stack.stack)
    {
        printf(RED"Ошибка: не удалось выделить память под стек.\n"RESET);

        return ERR_MEMORY_ALLOC;
    }

    array_stack.last_elem = array_stack.stack + MAX_ARRAY_SIZE;
    array_stack.curr_elem = array_stack.stack - 1;

    struct node *last_elem = NULL;
    size_t list_size = 0;

    init_area(); // Массив свободных областей стека-списка

    while (option != 0)
    {
        print_menu();

        if (scanf("%d", &option) != 1)
        {
            printf(RED"Ошибка: неверно введен номер меню.\n"RESET);
            free(array_stack.stack);
            free_area();

            return ERR_OPTION;
        }

        getchar();

        if (option < 0 || option > 9)
            printf(RED"Ошибка: пункт меню должен быть от 0 до 9.\n"RESET);

        if (option == 1)
        {
            int rc = array_check_brackets(MAX_ARRAY_SIZE + 3);
            
            if (rc == EXIT_SUCCESS)
                printf(GREEN"Выражение корректно.\n"RESET);
            else if (rc == ERR_EMPTY_STRING)
                printf(RED"Ошибка: пустая входная строка.\n"RESET);
            else if (rc == ERR_BUFFER_OVERFLOW)
                printf(RED"Ошибка: слишком большое выражение.\n"RESET);
            else
                printf(RED"Выражение некорректно.\n"RESET);
        }

        if (option == 2)
        {
            char elem;

            printf("Введите новый элемент стека (символ): ");
            scanf("%c", &elem);

            if (push_array(&array_stack.curr_elem, array_stack.last_elem, elem) 
                == EXIT_SUCCESS)
                printf(GREEN"Элемент успешно добавлен.\n"RESET);
        }

        if (option == 3)
            if (pop_array(&array_stack.curr_elem, array_stack.stack)
                == EXIT_SUCCESS)
                printf(GREEN"Элемент успешно удален.\n"RESET);

        if (option == 4)
            print_array(array_stack.stack, array_stack.curr_elem);

        if (option == 5)
        {
            int rc = list_check_brackets(MAX_ARRAY_SIZE + 3);

            if (rc == EXIT_SUCCESS)
                printf(GREEN"Выражение корректно.\n"RESET);
            else if (rc == ERR_EMPTY_STRING)
                printf(RED"Ошибка: пустая входная строка.\n"RESET);
            else if (rc == ERR_BUFFER_OVERFLOW)
                printf(RED"Ошибка: слишком большое выражение.\n"RESET);
            else
                printf(RED"Выражение некорректно.\n"RESET);
        }

        if (option == 6)
        {
            char elem;

            printf("Введите новый элемент стека (символ): ");
            scanf("%c", &elem);

            if (list_size == MAX_LIST_SIZE)
                printf(RED"Ошибка: стек-список переполнен.\n"RESET);
            else
            {
                last_elem = push_list(last_elem, elem);
                printf(GREEN"Элемент успешно добавлен.\n"RESET);
                list_size++;
            }  
        }

        if (option == 7)
            if ((last_elem = pop_list(last_elem, 1)) != NULL)
            {
                list_size--;
                printf(GREEN"Элемент успешно удален.\n"RESET);
            }

        if (option == 8)
            print_list(last_elem);

        if (option == 9)
        {
            efficiency_analysis(10);
            efficiency_analysis(100);
            efficiency_analysis(1000);
            efficiency_analysis(10000);
            efficiency_analysis(100000);
        }

        if (option == 0)
        {
            printf(GREEN"Выполнение программы завершено.\n"RESET);
            free(array_stack.stack);
            free_area();

            return EXIT_SUCCESS;
        }
    }

    free(array_stack.stack);
    free_area();
    
    return EXIT_FAILURE;
}
