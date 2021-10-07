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

    country_t country_array[10] = { 0 };
    size_t size = -1;

    while (!feof(input_file))
    {
        size++;
        scanf_country(input_file, &country_array[size]);   
    }

    fclose(input_file);
    print_info();

    int choice = 0;

    while (1)
    {
        print_menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            print_all_data(stdout, country_array, size);
            break;
        case 2:
            find_by_sport(stdout, country_array, size);
            break;
        case 0:
            return EXIT_SUCCESS;
        }
    }

    return EXIT_SUCCESS;
}
