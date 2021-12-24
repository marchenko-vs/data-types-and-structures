#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "avl_tree.h"
#include "bs_tree.h"
#include "hash_table.h"
#include "io_functions.h"

#define ERR_ARGS_NUMBER -1
#define ERR_FILE_OPEN -2
#define ERR_INCORRECT_DATA -3

#define BUFFER_SIZE 64

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);

    if (argc < 2)
    {
        printf("Error: enter file name.\n");
        return ERR_ARGS_NUMBER;
    }

    FILE *input_file = fopen(argv[1], "r");

    if (!input_file)
    {
        printf("Error: file can not be opened.\n");
        return ERR_FILE_OPEN;
    }

    array_t file_array = { 0 }; // Массив чисел из файла
    file_array.current_size = get_array_size(input_file);

    if (file_array.current_size <= 0)
    {
        printf("Error: incorrect input data.\n");
        fclose(input_file);
        return ERR_INCORRECT_DATA;
    }

    file_array.size = file_array.current_size * 2;
    array_init(&file_array);
    rewind(input_file);
    
    if (form_array(input_file, &file_array) < 0)
    {
        printf("Error: incorrect input data.\n");
        fclose(input_file);
        array_free(&file_array);
        return ERR_INCORRECT_DATA;
    }    

    tree_node_t *bs_head = NULL; // Двочиное дерево поиска
    avl_node_t *avl_head = NULL; // АВЛ дерево
    hash_table_t table = { 0 }; // Хэш-таблица

    int tmp = 0;

    for (size_t i = 0; i < file_array.current_size; i++)
        bs_head = bs_insert(bs_head, file_array.array[i], &tmp);

    FILE *f2 = fopen("bs_tree.gv", "w");
    bs_export_to_dot(f2, "BS_tree", bs_head);
    system("dot -Tpng bs_tree.gv -o bs_tree.png");
    fclose(f2);

    qsort(file_array.array, file_array.current_size, sizeof(int), cmp);

    for (size_t i = 0; i < file_array.current_size; i++)
        avl_head = avl_insert(avl_head, file_array.array[i], &tmp);

    FILE *f3 = fopen("avl_tree.gv", "w");
    avl_export_to_dot(f3, "AVL_tree", avl_head);
    fclose(f3);
    system("dot -Tpng avl_tree.gv -o avl_tree.png");

    ht_init(&table, file_array.current_size);

    for (size_t i = 0; i < file_array.current_size; i++)
        ht_insert(&table, file_array.array[i], &tmp, hash_1);

    system("bash draw_graphs.sh");
    ht_print(&table);

    int choice = 1, new_element = -1;
    int bs_comparisons = 0, avl_comparisons = 0, ht_comparisons = 0,
    file_comparisons = 0, max_comparisons = 0;
    char buffer[BUFFER_SIZE];
    bool flag = false;

    while (choice)
    {
        printf("1. Add element into all structures.\n"
            "2. Print all structures.\n"
            "3. Efficiency analysis.\n"
            "0. Exit.\n");

        if (scanf("%d", &choice) != 1)
        {
            printf("Error:\n");
            fgets(buffer, BUFFER_SIZE, stdin);
            continue;
        }

        if (choice < 0 || choice > 3)
            continue;

        if (choice == 1)
        {
            while (new_element < 0)
            {
                new_element = get_new_element();
                fgets(buffer, BUFFER_SIZE, stdin);
            }

            printf("Enter number of comparisons to restructure hash table: ");

            if (scanf("%d", &max_comparisons) != 1)
            {
                fgets(buffer, BUFFER_SIZE, stdin);
                continue;
            }

            if (max_comparisons < 1)
                continue;

            bs_head = bs_insert(bs_head, new_element, &bs_comparisons);
            avl_head = avl_insert(avl_head, new_element, &avl_comparisons);
            array_insert(&file_array, new_element, &file_comparisons);

            if (!flag)
                ht_insert(&table, new_element, &ht_comparisons, hash_1);
            else
                ht_insert(&table, new_element, &ht_comparisons, hash_2);

            if (ht_comparisons > max_comparisons)
            {
                ht_restructure(&table, &file_array, hash_2);
                flag = true;
            }

            new_element = -1;
        }

        if (choice == 2)
        {
            f2 = fopen("bs_tree.gv", "w");
            bs_export_to_dot(f2, "BS_tree", bs_head);
            fclose(f2);
            system("dot -Tpng bs_tree.gv -o bs_tree.png");

            f3 = fopen("avl_tree.gv", "w");
            avl_export_to_dot(f3, "AVL_tree", avl_head);
            fclose(f3);
            system("dot -Tpng avl_tree.gv -o avl_tree.png");

            ht_print(&table);

            print_array(&file_array);

            system("bash draw_graphs.sh");
        }

        if (choice == 3)
        {
            srand(time(0));

            for (size_t i = 0; i < 100; i++)
            {
                new_element = rand() % 100;

                bs_head = bs_insert(bs_head, new_element, &bs_comparisons);
                avl_head = avl_insert(avl_head, new_element, &avl_comparisons);
                array_insert(&file_array, new_element, &file_comparisons);

                if (!flag)
                    ht_insert(&table, new_element, &ht_comparisons, hash_1);
                else
                    ht_insert(&table, new_element, &ht_comparisons, hash_2);

                            printf("Efficiency: %d %d %d %d\n", bs_comparisons,
                            avl_comparisons, ht_comparisons, file_comparisons);
            }
        }
    }
    
    ht_free(&table);
    array_free(&file_array);

    return EXIT_SUCCESS;
}
