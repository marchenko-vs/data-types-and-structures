#include "country.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>
#include "sort.h"

void print_instruction(void)
{
    printf("==================================================================="
        "=============\n                            Лабораторная работа #2\n"
        "======================================================================"
        "==========\n");
}

void print_menu(void)
{
    printf("\n                                      Меню\n"
        "1 - Считать данные из файла в таблицу.\n"
        "2 - Вывести список стран на выбранном материке, где можно заняться "
        "указанным\nвидом спорта.\n"
        "3 - Упорядочить таблицу по возрастанию населения, "
        "используя исходную таблицу.\n4 - Упорядочить таблицу по "
        "возрастанию населения, "
        "используя\nтаблицу ключей.\n5 - Вывести исходную таблицу.\n"
        "6 - Вывести исходную таблицу, используя таблицу ключей.\n"
        "7 - Вывести таблицу ключей.\n"
        "8 - Добавить запись в конец таблицы.\n9 - Удалить запись"
        " по названию страны.\n10 - Сравнить время сортировки таблиц двумя " 
        "алгоритмами.\n"
        "0 - Выйти из программы.\n"
        "\n");
    printf("Введите номер меню: ");
}

int check_string(char *string)
{
    size_t length = strlen(string);

    if (length > NAME_SIZE && string[length] != '\n')
        return EXIT_FAILURE;

    if (length == 1 && string[0] == '\n')
        return EXIT_FAILURE;

    string[length - 1] = '\0';

    return EXIT_SUCCESS;
}

int scanf_country(FILE *stream, country_t *country)
{
    char temporary_buffer[NAME_SIZE + 1];

    if (fgets(temporary_buffer, NAME_SIZE + 1, stream) == NULL)
        return EXIT_FAILURE;

    if (check_string(temporary_buffer) == EXIT_FAILURE)
        return EXIT_FAILURE;

    strcpy(country->country_name, temporary_buffer);

    if (fgets(temporary_buffer, NAME_SIZE + 1, stream) == NULL)
        return EXIT_FAILURE;

    if (check_string(temporary_buffer) == EXIT_FAILURE)
        return EXIT_FAILURE;

    strcpy(country->capital_name, temporary_buffer);

    if (fscanf(stream, "%lld\n", &country->population) != 1)
        return EXIT_FAILURE;

    if (fscanf(stream, "%hd\n", &country->mainland) != 1)
        return EXIT_FAILURE;

    if (fscanf(stream, "%hd\n", &country->covid_vaccine) != 1)
        return EXIT_FAILURE;

    if (fscanf(stream, "%hd\n", &country->tourism_type_number) != 1)
        return EXIT_FAILURE;

    if (country->tourism_type_number == 1)
    {
        if (fscanf(stream, "%d\n", &country->tourism_type.excursion_type.objects_number) != 1)
            return EXIT_FAILURE;

        if (fscanf(stream, "%hd\n", &country->tourism_type.excursion_type.main_type) != 1)
            return EXIT_FAILURE;
    }

    if (country->tourism_type_number == 2)
    {
        if (fscanf(stream, "%lf\n", &country->tourism_type.beach_type.flight_time) != 1)
            return EXIT_FAILURE;

        if (fscanf(stream, "%hd\n", &country->tourism_type.beach_type.main_season) != 1)
            return EXIT_FAILURE;

        if (fscanf(stream, "%hd\n", &country->tourism_type.beach_type.air_temperature) != 1)
            return EXIT_FAILURE;

        if (fscanf(stream, "%hd\n", &country->tourism_type.beach_type.water_temperature) != 1)
            return EXIT_FAILURE;
    }

    if (country->tourism_type_number == 3)
    {
        if (fscanf(stream, "%d\n", &country->tourism_type.sport_type.minimal_price) != 1)
            return EXIT_FAILURE;

        if (fscanf(stream, "%hd\n", &country->tourism_type.sport_type.sport_kind) != 1)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int read_all_data(FILE *stream, country_t *array, key_t *key_array, size_t *size)
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

char *get_mainland_name(const int number)
{
    if (number == 1)
        return "Africa\0";

    if (number == 2)
        return "Australia\0";

    if (number == 3)
        return "Antarctica\0";

    if (number == 4)
        return "Eurasia\0";

    if (number == 5)
        return "North America\0";

    if (number == 6)
        return "South America\0";

    return NULL;
}

char *get_covid_requirements(const int number)
{
    if (number == 0)
        return "No COVID-measures needed\0";

    if (number == 1)
        return "PCR-test needed\0";

    if (number == 2)
        return "Vaccine needed\0";

    return NULL;
}

char *get_tourism_type(const int number)
{
    if (number == 1)
        return "excursion\0";

    if (number == 2)
        return "beach\0";

    if (number == 3)
        return "sports\0";

    return NULL;
}

char *get_main_type(const int number)
{
    if (number == 1)
        return "nature\0";

    if (number == 2)
        return "history\0";

    if (number == 3)
        return "art\0";

    return NULL;
}

char *get_sports_type(const int number)
{
    if (number == 1)
        return "downhill skiing\0";

    if (number == 2)
        return "surfing\0";

    if (number == 3)
        return "climbing\0";

    return NULL;
}

char *get_season_name(const int number)
{
    if (number == 1)
        return "Winter\0";

    if (number == 2)
        return "Spring\0";

    if (number == 3)
        return "Summer\0";

    if (number == 4)
        return "Autumn\0";

    return NULL;
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

int array_push(country_t *country, size_t *size)
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
            "1 - зима\n2 - весна\n3 - лето\n4 - осень");
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

        if (scanf("%hd", &country->tourism_type.beach_type.air_temperature) != 1)
            return EXIT_FAILURE;

        printf("Введите температуру воды в градусах: ");

        if (scanf("%hd", &country->tourism_type.beach_type.water_temperature) != 1)
            return EXIT_FAILURE;
    }

    if (country->tourism_type_number == 3)
    {
        printf("Введите минимальную стоимость в долларах: ");

        if (scanf("%d", &country->tourism_type.sport_type.minimal_price) != 1)
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

void printf_country(FILE *stream, country_t *country)
{
    fprintf(stream, "Страна: %s\n", country->country_name);
    fprintf(stream, "Столица: %s\n", country->capital_name);
    fprintf(stream, "Население: %llu\n", country->population);
    fprintf(stream, "Материк: %s\n", get_mainland_name(country->mainland));
    fprintf(stream, "%s\n", get_covid_requirements(country->covid_vaccine));
    fprintf(stream, "Вид туризма: %s\n",
        get_tourism_type(country->tourism_type_number));

    if (country->tourism_type_number == 1)
    {
        fprintf(stream, "Количество достопримечательностей: %d\n", country->tourism_type.excursion_type.objects_number);
        fprintf(stream, "Основной вид туризма: %s\n", get_main_type(country->tourism_type.excursion_type.main_type));
    }

    if (country->tourism_type_number == 2)
    {
        fprintf(stream, "Время полета: %.1lf\n", country->tourism_type.beach_type.flight_time);
        fprintf(stream, "Основной сезон: %s\n", get_season_name(country->tourism_type.beach_type.main_season));
        fprintf(stream, "Температура воздуха: %d\n", country->tourism_type.beach_type.air_temperature);
        fprintf(stream, "Температура воды: %d\n", country->tourism_type.beach_type.water_temperature);
    }

    if (country->tourism_type_number == 3)
    {
        fprintf(stream, "Минимальная стоимость отдыха: %d\n", country->tourism_type.sport_type.minimal_price);
        fprintf(stream, "Вид спорта: %s\n", get_sports_type(country->tourism_type.sport_type.sport_kind));
    }
}

void print_all_data(FILE *stream, country_t *country, const int size)
{
    for (size_t i = 0; i < size; i++)
        printf_country(stream, &country[i]);
}

void print_by_keys(FILE *stream, country_t *country, key_t *keys, const int size)
{
    for (size_t i = 0; i < size; i++)
        printf_country(stream, &country[keys[i].index]);
}

void copy_array(country_t *array_1, country_t *array_2, const int size)
{
    for (size_t i = 0; i < size; i++)
        array_2[i] = array_1[i];
}

void copy_key_array(key_t *array_1, key_t *array_2, const int size)
{
    for (size_t i = 0; i < size; i++)
        array_2[i] = array_1[i];
}

void print_keys_table(FILE *stream, key_t *array, const int size)
{
    printf("----------+----------+------------------\n");
    printf("  Номер   |  Индекс  |      Население     \n");
    printf("----------+----------+------------------\n");
    for (size_t i = 0; i < size; i++)
        printf("%-10lld|%-10lld|%-20lld\n", i, array[i].index, array[i].key);
    printf("----------+----------+--------------------\n");
}

void sort_comparison(country_t *table, key_t *key_table, const int size)
{
    country_t array_to_sort_1[MAX_TABLE_SIZE] = {0};
    copy_array(table, array_to_sort_1, size);
    struct timeval tv_start_bubble, tv_end_bubble;
    int64_t overall_time_bubble;
    gettimeofday(&tv_start_bubble, NULL);
    table_bubble_sort(array_to_sort_1, size);
    gettimeofday(&tv_end_bubble, NULL);
    overall_time_bubble =
    (tv_end_bubble.tv_sec - tv_start_bubble.tv_sec) * 1000000LL + 
    (tv_end_bubble.tv_usec - tv_start_bubble.tv_usec);

    country_t array_to_sort_2[MAX_TABLE_SIZE] = {0};
    copy_array(table, array_to_sort_2, size);
    struct timeval tv_start_shell, tv_end_shell;
    int64_t overall_time_shell;
    gettimeofday(&tv_start_shell, NULL);
    table_shell_sort(array_to_sort_2, size);
    gettimeofday(&tv_end_shell, NULL);
    overall_time_shell = (tv_end_shell.tv_sec - tv_start_bubble.tv_sec)
    * 1000000LL + (tv_end_shell.tv_usec - tv_start_bubble.tv_usec);

    key_t keys_to_sort_1[MAX_TABLE_SIZE] = {0};
    copy_key_array(key_table, keys_to_sort_1, size);
    struct timeval tv_start_k_bubble, tv_end_k_bubble;
    int64_t overall_time_k_bubble;
    gettimeofday(&tv_start_k_bubble, NULL);
    key_bubble_sort(keys_to_sort_1, size);
    gettimeofday(&tv_end_k_bubble, NULL);
    overall_time_k_bubble =
    (tv_end_k_bubble.tv_sec - tv_start_k_bubble.tv_sec) * 1000000LL + 
    (tv_end_k_bubble.tv_usec - tv_start_k_bubble.tv_usec);

    key_t keys_to_sort_2[MAX_TABLE_SIZE] = {0};
    copy_key_array(key_table, keys_to_sort_2, size);
    struct timeval tv_start_k_shell, tv_end_k_shell;
    int64_t overall_time_k_shell;
    gettimeofday(&tv_start_k_shell, NULL);
    key_shell_sort(keys_to_sort_2, size);
    gettimeofday(&tv_end_k_shell, NULL);
    overall_time_k_shell =
    (tv_end_k_shell.tv_sec - tv_start_k_shell.tv_sec) * 1000000LL + 
    (tv_end_k_shell.tv_usec - tv_start_k_shell.tv_usec);

    printf("---------------+------------------------+-"
        "----------------\n");
    printf("  Тип таблицы  | Пузырьковая сортировка | "
        "Сортировка Шелла\n");
    printf("---------------+------------------------+-"
        "----------------\n");
    printf("   Исходная    |%-24" PRId64 "|%-17" PRId64 "\n",
        overall_time_bubble, overall_time_shell);
    printf("   Ключей      |%-24" PRId64 "|%-17" PRId64 "\n",
        overall_time_k_bubble, overall_time_k_shell);
    printf("---------------+------------------------+-"
        "----------------\n");
}
