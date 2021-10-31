#include <stdio.h>
#include <stdlib.h>
#include "info.h"
#include "array_stack.h"
#include "list_stack.h"

#define rdtscll(val) __asm__ __volatile__("rdtsc" :"=A"(val))

void print_introduction(void)
{
    printf("==================================================================="
        "=============\n                            Лабораторная работа #4\n"
        "======================================================================"
        "==========\n");
}

void print_menu(void)
{
    printf("\n                                      Меню\n"
        "1. Проверить правильность расстановки скобок в выражении, "
        "используя стек\nна основе динамического массива.\n"
        "2. Добавить элемент в стек на основе динамического массива.\n"
        "3. Удалить элемент из стека на основе динамического массива.\n"
        "4. Просмореть текущее состояние стека на основе "
        "динамического массива.\n"
        "5. Проверить правильность расстановки скобок в выражении, "
        "используя стек\nна основе односвязного линейного списка.\n"
        "6. Добавить элемент в стек на основе односвязного линейного списка.\n"
        "7. Удалить элемент из стека на основе односвязного линейного списка.\n"
        "8. Просмореть текущее состояние стека на основе "
        "односвязного линейного списка.\n"
        "9. Проинициализировать свободную область в стеке на основе "
        "односвязного линейного списка.\n"
        "10. Провести анализ эффективности (по памяти и времени) реализаций "
        "стека\nна основе динамического массива и односвязного линейного "
        "списка.\n"
        "0. Завершить выполнение программы.\n"
        "Введите пункт меню: ");
}

void efficiency_analysis(unsigned long long size)
{
    printf(GREEN"Анализ эффективности при %llu элементах.\n"RESET, size);

    unsigned long long time_start, time_end;

    char *array_stack = malloc(size * sizeof(char));

    if (!array_stack)
    {
        printf(RED"Ошибка: не удалось выделить память под стек.\n"RESET);

        return;
    }

    char *ptr_curr = array_stack - 1;

    printf("------------+---------------+----------------------------+-"
        "-------------------------\n");
    printf(" Реализация | Память, байты | Добавление элемента, такты | "
        "Удаление элемента, такты\n");
    printf("------------+---------------+----------------------------+-"
        "-------------------------\n");

    unsigned long long array_memory = size * sizeof(char) + sizeof(ptr_curr);

    printf("   Массив   |%-15llu|", array_memory);

    rdtscll(time_start);

    for (unsigned long long i = 0; i < size; i++)
        push_array(&ptr_curr, array_stack + size - 1, 'q');

    rdtscll(time_end);

    printf("%-28llu|", (unsigned long long)(time_end - time_start));

    rdtscll(time_start);

    for (unsigned long long i = 0; i < size; i++)
        pop_array(&ptr_curr, array_stack);

    rdtscll(time_end);

    printf("%-25llu\n", (unsigned long long)(time_end - time_start));
    printf("------------+---------------+----------------------------+-"
        "-------------------------\n");

    struct node *last_elem = NULL;
    unsigned long long list_memory = sizeof(last_elem) + 
        sizeof(struct node) * size;

    printf("   Список   |%1lu - %-11llu|", sizeof(last_elem), list_memory);

    rdtscll(time_start);

    for (unsigned long long i = 0; i < size; i++)
        last_elem = push_list(last_elem, 'q');

    rdtscll(time_end);

    printf("%-28llu|", (unsigned long long)(time_end - time_start));

    rdtscll(time_start);

    for (unsigned long long i = 0; i < size; i++)
        last_elem = pop_list(last_elem, 0);

    rdtscll(time_end);

    printf("%-25llu\n", (unsigned long long)(time_end - time_start));
    printf("------------+---------------+----------------------------+-"
        "-------------------------\n");

    free(array_stack);
}
