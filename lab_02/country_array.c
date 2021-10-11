#include "country_array.h"
#include "country.h"
#include <stdlib.h>
#include <string.h>

int read_all_data(FILE *stream, country_t *array, key_table_t *key_array, size_t *size)
{
    while (!feof(stream))
    {
        if (MAX_TABLE_SIZE == *size)
            return TOO_MANY_STRUCTURES;

        if (scanf_country(stream, &array[*size]) != EXIT_SUCCESS)
            return INVALID_DATA;

        key_array[*size].index = *size;
        key_array[*size].key = array[*size].population;

        (*size)++;

        if (feof(stream))
            return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}

int find_by_sport(FILE *stream, country_t *country, const int size)
{
    int find_mainland = 0, find_sport = 0, count = 0;

    printf("Расшифровка номеров материков:\n"
        "1 - Африка\n2 - Австралия\n3 - Антарктида\n4 - Евразия\n"
        "5 - Северная Америка\n6 - Южная Америка\n");
    printf("Введите номер материка: ");
    scanf("%d", &find_mainland);
    printf("Расшифровка номеров видов спорта:\n"
        "1 - горные лыжи\n2 - серфинг\n3 - восхождения\n");
    printf("Введите номер вида спорта: ");
    scanf("%d", &find_sport);

    for (size_t i = 0; i < size; i++)
        if (country[i].tourism_type_number == 3)
            if (country[i].mainland == find_mainland &&
                country[i].tourism_type.sport_type.sport_kind == find_sport)
            {
                printf_country(stream, &country[i]);
                count++;
            }
    return count;
}

int array_push(country_t *country, key_table_t *key, size_t *size)
{
    getchar();
    printf("Введите название страны: ");
    char temporary_buffer[NAME_SIZE + 1];

    if (fgets(temporary_buffer, NAME_SIZE + 1, stdin) == NULL)
        return EXIT_FAILURE;

    if (check_string(temporary_buffer) == EXIT_FAILURE)
        return EXIT_FAILURE;

    strcpy(country->country_name, temporary_buffer);
    printf("Введите название столицы: ");

    if (fgets(temporary_buffer, NAME_SIZE + 1, stdin) == NULL)
        return EXIT_FAILURE;

    if (check_string(temporary_buffer) == EXIT_FAILURE)
        return EXIT_FAILURE;

    strcpy(country->capital_name, temporary_buffer);
    printf("Введите население страны: ");

    if (scanf("%lld", &country->population) != 1)
    {
        printf(RED"Ошибка: введены некорректные данные.\n"RESET);
        return EXIT_FAILURE;
    }
    if (country->population < 0)
    {
        printf(RED"Ошибка: население должно быть неотрицательным числом.\n"RESET);
        return EXIT_FAILURE;
    }

    printf("Расшифровка номеров материков:\n"
        "1 - Африка\n2 - Австралия\n3 - Антарктида\n4 - Евразия\n"
        "5 - Северная Америка\n6 - Южная Америка\n");
    printf("Введите номер материка: ");

    if (scanf("%hd", &country->mainland) != 1)
        return EXIT_FAILURE;
    if (country->mainland < 1 || country->mainland > 6)
    {
        printf(RED"Ошибка: номер материка должен быть от 1 до 6.\n"RESET);
        return EXIT_FAILURE;
    }

    printf("Расшифровка номеров COVID-ограничений:\n"
        "0 - отсутствуют\n1 - нужен ПЦР-тест\n2 - нужна вакцина\n");
    printf("Введите номер COVID-ограничений: ");

    if (scanf("%hd", &country->covid_vaccine) != 1)
        return EXIT_FAILURE;
    if (country->covid_vaccine < 0 || country->covid_vaccine > 2)
    {
        printf(RED"Ошибка: номер COVID-ограничений должен быть от 0 до 2.\n"RESET);
        return EXIT_FAILURE;
    }

    printf("Расшифровка номеров видов туризма:\n"
        "1 - экскурсионный\n2 - пляжный\n3 - спортивный\n");
    printf("Введите номер вида туризма: ");

    if (scanf("%hd", &country->tourism_type_number) != 1)
        return EXIT_FAILURE;
    if (country->tourism_type_number < 1 || country->tourism_type_number > 3)
    {
        printf(RED"Ошибка: номер вида туризма должен быть от 1 до 3.\n"RESET);
        return EXIT_FAILURE;
    }

    if (country->tourism_type_number == 1)
    {
        printf("Введите количество объектов: ");

        if (scanf("%d", &country->tourism_type.excursion_type.objects_number) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.excursion_type.objects_number < 0)
        {
            printf(RED"Ошибка: количество объектов должно быть неотрицательным.\n"RESET);
            return EXIT_FAILURE;
        }

        printf("Расшифровка номеров видов экскурсий:\n"
            "1 - природа\n2 - история\n3 - искусство\n");
        printf("Введите номер вида экскурсии: ");

        if (scanf("%hd", &country->tourism_type.excursion_type.main_type) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.excursion_type.main_type < 1 ||
            country->tourism_type.excursion_type.main_type > 3)
        {
            printf(RED"Ошибка: номер вида экскурсии должен быть от 1 до 3.\n"RESET);
            return EXIT_FAILURE;
        }
    }

    if (country->tourism_type_number == 2)
    {
        printf("Введите время полета в часах: ");

        if (scanf("%lf", &country->tourism_type.beach_type.flight_time) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.beach_type.flight_time < 0)
        {
            printf(RED"Ошибка: время полета должно быть неотрицательным.\n"RESET);
            return EXIT_FAILURE;
        }

        printf("Расшифровка номеров сезонов:\n"
            "1 - зима\n2 - весна\n3 - лето\n4 - осень\n");
        printf("Введите основной сезон: ");

        if (scanf("%hd", &country->tourism_type.beach_type.main_season) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.beach_type.main_season < 1 ||
            country->tourism_type.beach_type.main_season > 4)
        {
            printf(RED"Ошибка: номер сезона должен быть от 1 до 4.\n"RESET);
            return EXIT_FAILURE;
        }

        printf("Введите температуру воздуха в градусах: ");

        if (scanf("%lf", &country->tourism_type.beach_type.air_temperature) != 1)
            return EXIT_FAILURE;

        printf("Введите температуру воды в градусах: ");

        if (scanf("%lf", &country->tourism_type.beach_type.water_temperature) != 1)
            return EXIT_FAILURE;
    }

    if (country->tourism_type_number == 3)
    {
        printf("Введите минимальную стоимость в долларах: ");

        if (scanf("%lf", &country->tourism_type.sport_type.minimal_price) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.sport_type.minimal_price < 0)
        {
            printf(RED"Ошибка: минимальная стоимость должга быть неотрицательной.\n"RESET);
            return EXIT_FAILURE;
        }

        printf("Расшифровка номеров видов спорта:\n"
        "1 - горные лыжи\n2 - серфинг\n3 - восхождения\n");
        printf("Введите вид спорта: ");

        if (scanf("%hd", &country->tourism_type.sport_type.sport_kind) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.sport_type.sport_kind < 1 ||
            country->tourism_type.sport_type.sport_kind > 3)
        {
            printf(RED"Ошибка: номер вида спорта должен быть от 1 до 3.\n"RESET);
            return EXIT_FAILURE;
        }
    }
	
	key->index = *size;
    key->key = country->population;
    (*size)++;

    return EXIT_SUCCESS;
}

int array_remove(country_t *country, size_t *size)
{
    getchar();
    char temporary_buffer[NAME_SIZE + 1];
    printf("Введите название страны: ");
    if (fgets(temporary_buffer, NAME_SIZE + 1, stdin) == NULL)
    {   
        printf("Ошибка: неверно введено название страны.\n");
        return EXIT_FAILURE;
    }
    if (check_string(temporary_buffer) == EXIT_FAILURE)
        return EXIT_FAILURE;
    char find_country[NAME_SIZE + 1];
    strcpy(find_country, temporary_buffer);
    for (size_t i = 0; i < *size; i++)
        if (strcmp(country[i].country_name, find_country) == 0)
        {
            if (*size == 1)
            {
                (*size)--;
                return EXIT_SUCCESS;
            }
            for (int j = i; j < *size - 2; j++)
                country[j] = country[j + 1];
            (*size)--;
            return EXIT_SUCCESS;
        }
    return EXIT_FAILURE;        
}

void print_all_data(FILE *stream, country_t *country, const int size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf_country(stream, &country[i]);
        printf("\n");
    }
}

void print_by_keys(FILE *stream, country_t *country, key_table_t *keys, const int size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf_country(stream, &country[keys[i].index]);
        printf("\n");
    }
}

void copy_array(country_t *array_1, country_t *array_2, const int size)
{
    for (size_t i = 0; i < size; i++)
        array_2[i] = array_1[i];
}

void copy_key_array(key_table_t *array_1, key_table_t *array_2, const int size)
{
    for (size_t i = 0; i < size; i++)
        array_2[i] = array_1[i];
}

void print_keys_table(FILE *stream, key_table_t *array, const int size)
{
    printf("----------+----------+------------------\n");
    printf("  Номер   |  Индекс  |      Население     \n");
    printf("----------+----------+------------------\n");
    for (size_t i = 0; i < size; i++)
        printf("%-10zd|%-10zd|%-20lld\n", i, array[i].index, array[i].key);
    printf("----------+----------+--------------------\n");
}
