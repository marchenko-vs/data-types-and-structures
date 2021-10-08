#include "country.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);

    if (argc < 2)
        return EXIT_FAILURE;

    FILE *input_file = fopen(argv[1], "r");

    if (input_file == NULL)
        return EXIT_FAILURE;

    country_t initial_table[MAX_TABLE_SIZE] = { 0 };
    key_t key_table[MAX_TABLE_SIZE] = { 0 };
    size_t table_size = 0;

    if (read_all_data(input_file, initial_table, key_table, &table_size))
    {
        fclose(input_file);

        return EXIT_FAILURE;
    }

    fclose(input_file);
    print_instruction();
    
    int choice = 0;

    while (choice < 9)
    {
        print_menu();
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("\n");
            print_all_data(stdout, initial_table, table_size);
        }
        else if (choice == 2)
        {
            printf("\n");
            find_by_sport(stdout, initial_table, table_size);
        }
        else if (choice == 3)
        {
            table_bubble_sort(initial_table, table_size);
            printf("\n");
            print_all_data(stdout, initial_table, table_size);
        }
        else if (choice == 4)
        {
            key_bubble_sort(key_table, table_size);
            printf("\n");
            print_by_keys(stdout, initial_table, key_table, table_size);
        }
        else if (choice == 5)
        {
            print_info();

            if (insert_array(&initial_table[table_size], &table_size))
                printf("Ошибка: введены некорректные данные.\n");
        }
        else
            return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
