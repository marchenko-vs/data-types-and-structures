#include "country.h"
#include "country_array.h"
#include "sort.h"
#include "info.h"
#include <stdio.h>
#include <stdlib.h>

#define MENU_OPTION_ERROR -1
#define FILE_READ_ERROR -2

#define FILE_NAME 30

int main(void)
{
    setbuf(stdout, NULL); // Отключение буферизации

    country_t initial_table[MAX_TABLE_SIZE] = {0}; // Инициализация двух таблиц
    key_table_t key_table[MAX_TABLE_SIZE] = {0};
    size_t table_size = 0;

    print_instruction();
    
    int choice = 0;
    while (1)
    {
        print_menu();

        if (scanf("%d", &choice) != 1)
        {
            printf(RED"Ошибка: пункт меню должен быть целым числом от 0 до 10."
                "\n"RESET);
            return MENU_OPTION_ERROR;
        }

        if (choice == 0)
        {
            printf(GREEN"Работа программы успешно завершена.\n"RESET);
            break;
        }
        else if (choice == 1)
        {
            char file_name[FILE_NAME] = "";
            printf("Введите название файла: ");
            scanf("%s", file_name);
            FILE *input_file = fopen(file_name, "r");
            if (input_file == NULL)
            {
                printf(RED"Ошибка: файл не существует.\n"RESET);
                continue;
            }
            if (read_all_data(input_file, initial_table, key_table,
                &table_size))
            {
                printf(RED"Ошибка: не удалось считать данные из файла.\n"RESET);
                fclose(input_file);
                return FILE_READ_ERROR;
            }
            printf(GREEN"Данные из файла считаны успешно.\n"RESET);
        }
        else if (choice == 2)
        {
            if (table_size == 0)
            {
                printf(RED"Ошибка: в таблице нет записей.\n"RESET);
                continue;
            }
            if (find_by_sport(stdout, initial_table, table_size) < 1)
                printf(RED"Ошибка: не найдены записи, удовлетворяющие Вашим "
                    "требованиям."RESET"\n");
        }
        else if (choice == 3)
        {
            if (table_size == 0)
            {
                printf(RED"Ошибка: в таблице нет записей.\n"RESET);
                continue;
            }
            table_shell_sort(initial_table, table_size);
            printf(GREEN"Таблица успешно отсортирована.\n"RESET);
        }
        else if (choice == 4)
        {
            if (table_size == 0)
            {
                printf(RED"Ошибка: в таблице нет записей.\n"RESET);
                continue;
            }
            key_shell_sort(key_table, table_size);
            printf(GREEN"Таблица ключей успешно отсортирована.\n"RESET);
        }
        else if (choice == 5)
        {
            if (table_size == 0)
            {
                printf(RED"Ошибка: в таблице нет записей.\n"RESET);
                continue;
            }
            print_all_data(stdout, initial_table, table_size);
        }
        else if (choice == 6)
        {
            if (table_size == 0)
            {
                printf(RED"Ошибка: в таблице нет записей.\n"RESET);
                continue;
            }
            printf("\n");
            print_by_keys(stdout, initial_table, key_table, table_size);
        }
        else if (choice == 7)
        {
            if (table_size == 0)
            {
                printf(RED"Ошибка: в таблице нет записей.\n"RESET);
                continue;
            }
            print_keys_table(stdout, key_table, table_size);
        }
        else if (choice == 8)
        {
            if (MAX_TABLE_SIZE == table_size)
            {
                printf(RED"Ошибка: таблица переполнена.\n"RESET);
                continue;
            }
            if (array_push(&initial_table[table_size], &key_table[table_size], &table_size))
            {
                getchar();
                continue;
            }
            printf(GREEN"Запись успешно добавлена.\n"RESET);
        }
        else if (choice == 9)
        {
            if (table_size == 0)
            {
                printf(RED"Ошибка: в таблице нет записей.\n"RESET);
                continue;
            }
            if (array_remove(initial_table, &table_size) != EXIT_SUCCESS)
            {
                printf(RED"Ошибка: страна с данным названием не "
                    "найдена.\n"RESET);
                continue;
            }
            printf(GREEN"Запись успешно удалена.\n"RESET);
        }
        else if (choice == 10)
        {
            if (table_size == 0)
            {
                printf(RED"Ошибка: в таблице нет записей.\n"RESET);
                continue;
            }
            sort_comparison(initial_table, key_table, table_size);
            
        }
        else
            printf(RED"Ошибка: такого пункта меню не существует.\n"RESET);
    }

    return EXIT_SUCCESS;
}
