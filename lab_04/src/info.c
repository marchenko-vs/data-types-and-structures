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
        "==========\n\nВ данной программе реализован стек двумя способами: "
        "на основе динамического\nмассива и односвязного линейного списка. "
        "Доступны следующие операции:\nдобавление элемента в стек, удаление "
        "элемента, просмотр текущего состояния\nстека, проверка правильности "
        "расстановки скобок трех типов в выражении.\nТребования к входным "
        "данным:\n1. Строка не должна быть пустой.\n2. Длина строки не должна "
        "превышать 1000 символов.\n3. Элементы стека - символы.\n\n");
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
        "9. Провести анализ эффективности (по памяти и времени) реализаций "
        "стека\nна основе динамического массива и односвязного линейного "
        "списка.\n"
        "0. Завершить выполнение программы.\n"
        "Введите пункт меню: ");
}

void efficiency_analysis(unsigned long size)
{
    printf(GREEN"Анализ эффективности при %lu элементах.\n"RESET, size);

    unsigned long long time_start, time_end;
    array_stack_t array_stack = { NULL, NULL, NULL };

    array_stack.stack = malloc(size * sizeof(char));

    if (!array_stack.stack)
    {
        printf(RED"Ошибка: не удалось выделить память под стек.\n"RESET);

        return;
    }

    array_stack.last_elem = array_stack.stack + size;
    array_stack.curr_elem = array_stack.stack - 1;

    printf("------------+---------------+----------------------------+-"
        "-------------------------\n");
    printf(" Реализация | Память, байты | Добавление элемента, такты | "
        "Удаление элемента, такты\n");
    printf("------------+---------------+----------------------------+-"
        "-------------------------\n");

    unsigned long long array_memory = size * sizeof(char) + 
        sizeof(array_stack.curr_elem) + sizeof(array_stack.last_elem);

    printf("   Массив   |%-15llu|", array_memory);

    rdtscll(time_start);

    for (unsigned long long i = 0; i < size - 1; i++)
        push_array(&array_stack.curr_elem, array_stack.stack + size - 1, 'q');

    rdtscll(time_end);

    printf("%-28llu|", (unsigned long long)(time_end - time_start));

    rdtscll(time_start);

    for (unsigned long long i = 0; i < size - 1; i++)
        pop_array(&array_stack.curr_elem, array_stack.stack);

    rdtscll(time_end);

    printf("%-25llu\n", (unsigned long long)(time_end - time_start));
    printf("------------+---------------+----------------------------+-"
        "-------------------------\n");

    free(array_stack.stack);

    struct node *last_elem = NULL;
    unsigned long long list_memory = sizeof(struct node) + 
        sizeof(struct node) * size;

    printf("   Список   |%2llu - %-10llu|", sizeof(struct node), list_memory);

    rdtscll(time_start);

    for (unsigned long long i = 0; i < size - 1; i++)
        last_elem = push_list(last_elem, 'q');

    rdtscll(time_end);

    printf("%-28llu|", (unsigned long long)(time_end - time_start));

    rdtscll(time_start);

    for (unsigned long long i = 0; i < size - 1; i++)
        last_elem = pop_list(last_elem, 0);

    rdtscll(time_end);

    printf("%-25llu\n", (unsigned long long)(time_end - time_start));
    printf("------------+---------------+----------------------------+-"
        "-------------------------\n");
}
