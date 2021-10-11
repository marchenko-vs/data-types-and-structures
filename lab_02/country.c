#include "country.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

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
    if (country->population < 0)
        return EXIT_FAILURE;

    if (fscanf(stream, "%hd\n", &country->mainland) != 1)
        return EXIT_FAILURE;
    if (country->mainland < 1 || country->mainland > 6)
        return EXIT_FAILURE;

    if (fscanf(stream, "%hd\n", &country->covid_vaccine) != 1)
        return EXIT_FAILURE;
    if (country->covid_vaccine < 0 || country->covid_vaccine > 2)
        return EXIT_FAILURE;

    if (fscanf(stream, "%hd\n", &country->tourism_type_number) != 1)
        return EXIT_FAILURE;
    if (country->tourism_type_number < 1 ||
        country->tourism_type_number > 3)
        return EXIT_FAILURE;

    if (country->tourism_type_number == 1)
    {
        if (fscanf(stream, "%d\n", &country->tourism_type.excursion_type.objects_number) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.excursion_type.objects_number < 0)
            return EXIT_FAILURE;

        if (fscanf(stream, "%hd\n", &country->tourism_type.excursion_type.main_type) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.excursion_type.main_type < 1 ||
            country->tourism_type.excursion_type.main_type > 3)
            return EXIT_FAILURE;
    }

    if (country->tourism_type_number == 2)
    {
        if (fscanf(stream, "%lf\n", &country->tourism_type.beach_type.flight_time) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.beach_type.flight_time < 0)
            return EXIT_FAILURE;

        if (fscanf(stream, "%hd\n", &country->tourism_type.beach_type.main_season) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.beach_type.main_season < 1 ||
            country->tourism_type.beach_type.main_season > 4)
            return EXIT_FAILURE;

        if (fscanf(stream, "%lf\n", &country->tourism_type.beach_type.air_temperature) != 1)
            return EXIT_FAILURE;

        if (fscanf(stream, "%lf\n", &country->tourism_type.beach_type.water_temperature) != 1)
            return EXIT_FAILURE;
    }

    if (country->tourism_type_number == 3)
    {
        if (fscanf(stream, "%lf\n", &country->tourism_type.sport_type.minimal_price) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.sport_type.minimal_price < 0)
            return EXIT_FAILURE;

        if (fscanf(stream, "%hd\n", &country->tourism_type.sport_type.sport_kind) != 1)
            return EXIT_FAILURE;
        if (country->tourism_type.sport_type.sport_kind < 1 ||
            country->tourism_type.sport_type.sport_kind > 3)
            return EXIT_FAILURE;
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
        fprintf(stream, "Температура воздуха: %.1lf\n", country->tourism_type.beach_type.air_temperature);
        fprintf(stream, "Температура воды: %.1lf\n", country->tourism_type.beach_type.water_temperature);
    }

    if (country->tourism_type_number == 3)
    {
        fprintf(stream, "Минимальная стоимость отдыха: %.1lf\n", country->tourism_type.sport_type.minimal_price);
        fprintf(stream, "Вид спорта: %s\n", get_sports_type(country->tourism_type.sport_type.sport_kind));
    }
}
