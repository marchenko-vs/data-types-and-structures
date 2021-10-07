#include "country.h"
#include <stdio.h>
#include <stdlib.h>

void print_info(void)
{
    printf("Расшифорвка номеров материков:\n"
        "1 - Африка\n2 - Австралия\n3 - Антарктида\n4 - Евразия\n"
        "5 - Северная Америка\n6 - Южная Америка\n\n");
    printf("Расшифорвка номеров видов спорта:\n"
        "1 - горные лыжи\n2 - серфинг\n3 - восхождения\n\n");
}

void print_menu(void)
{
    printf("Меню\n"
        "1 - Вывести информацию обо всех странах\n"
        "2 - Вывести список стран на выбранном материке, где можно заняться\n"
        "указанным видом спорта.\n"
        "3 - Упорядочить таблицу по возрастанию населения, используя исходную\n"
        "таблицу\n0 - Выйти из программы\n\n");
    printf("Введите номер меню: ");
}

int scanf_country(FILE *stream, country_t *country)
{
    fscanf(stream, "%s", country->country_name);
    fscanf(stream, "%llu", &country->population);
    fscanf(stream, "%s", country->capital_name);
    fscanf(stream, "%hud", &country->mainland);
    fscanf(stream, "%hud", &country->covid_vaccine);
    fscanf(stream, "%hud", &country->tourism_type_number);

    if (country->tourism_type_number == 1)
    {
        fscanf(stream, "%ud", &country->tourism_type.excursion_type.objects_number);
        fscanf(stream, "%hud", &country->tourism_type.excursion_type.main_type);
    }

    if (country->tourism_type_number == 2)
    {
        fscanf(stream, "%hud", &country->tourism_type.beach_type.main_season);
        fscanf(stream, "%hd", &country->tourism_type.beach_type.air_temperature);
        fscanf(stream, "%hd", &country->tourism_type.beach_type.water_temperature);
        fscanf(stream, "%lf", &country->tourism_type.beach_type.flight_time);
    }

    if (country->tourism_type_number == 3)
    {
        fscanf(stream, "%hud", &country->tourism_type.sport_type.sport_kind);
        fscanf(stream, "%ud", &country->tourism_type.sport_type.minimal_price);
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

void print_all_data(FILE *stream, country_t *country, const int size)
{
    for (size_t i = 0; i < size; i++)
        printf_country(stream, &country[i]);
}

void find_by_sport(FILE *stream, country_t *country, const int size)
{
    int find_mainland = 0, find_sport = 0;

    printf("Введите номер материка: ");
    scanf("%d", &find_mainland);
    printf("Введите номер вида спорта: ");
    scanf("%d", &find_sport);

    for (size_t i = 0; i < size; i++)
        if (country[i].tourism_type_number == 3)
            if (country[i].mainland == find_mainland &&
                country[i].tourism_type.sport_type.sport_kind == find_sport)
                printf_country(stream, &country[i]);
}

void bubble_sort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)    
     
    // Last i elements are already in place
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

void printf_country(FILE *stream, country_t *country)
{
    fprintf(stream, "Страна: %s\n", country->country_name);
    fprintf(stream, "Население: %llu\n", country->population);
    fprintf(stream, "Столица: %s\n", country->capital_name);
    fprintf(stream, "Материк: %s\n", get_mainland_name(country->mainland));
    fprintf(stream, "%s\n", get_covid_requirements(country->covid_vaccine));
    fprintf(stream, "Вид туризма: %s\n", get_tourism_type(country->tourism_type_number));

    if (country->tourism_type_number == 1)
    {
        fprintf(stream, "Количество достопримечательностей: %d\n", country->tourism_type.excursion_type.objects_number);
        fprintf(stream, "Основной вид туризма: %s\n", get_main_type(country->tourism_type.excursion_type.main_type));
    }

    if (country->tourism_type_number == 2)
    {
        fprintf(stream, "Основной сезон: %s\n", get_season_name(country->tourism_type.beach_type.main_season));
        fprintf(stream, "Температура воздуха: %d\n", country->tourism_type.beach_type.air_temperature);
        fprintf(stream, "Температура воды: %d\n", country->tourism_type.beach_type.water_temperature);
        fprintf(stream, "Время полета: %.1lf\n", country->tourism_type.beach_type.flight_time);
    }

    if (country->tourism_type_number == 3)
    {
        fprintf(stream, "Вид спорта: %s\n", get_sports_type(country->tourism_type.sport_type.sport_kind));
        fprintf(stream, "Минимальная стоимость отдыха: %d\n", country->tourism_type.sport_type.minimal_price);
    }

    fprintf(stream, "\n");
}
