#ifndef _COUNTRY_H_

#define _COUNTRY_H_

#include <stdio.h>

#define NAME_SIZE 50

typedef struct
{
    unsigned short int sport_kind;
    unsigned int minimal_price;
} sport_t;

typedef struct
{
    unsigned short int main_season;
    short int air_temperature;
    short int water_temperature;
    double flight_time;
} beach_t;

typedef struct
{
    unsigned int objects_number;
    unsigned short int main_type;
} excursion_t;

typedef union
{
    excursion_t excursion_type;
    beach_t beach_type;
    sport_t sport_type;
} tourism_t;

typedef struct
{
    char country_name[NAME_SIZE + 1];
    unsigned long long population;
    char capital_name[NAME_SIZE + 1];
    unsigned short int mainland;
    unsigned short int covid_vaccine;
    unsigned short int tourism_type_number;
    tourism_t tourism_type;
} country_t;

void print_info(void);
void print_menu(void);
int scanf_country(FILE *stream, country_t *country);
char *get_mainland_name(const int number);
char *get_covid_requirements(const int number);
char *get_tourism_type(const int number);
char *get_main_type(const int number);
char *get_sports_type(const int number);
char *get_season_name(const int number);
void print_all_data(FILE *stream, country_t *country, const int size);
void find_by_sport(FILE *stream, country_t *country, const int size);
void printf_country(FILE *stream, country_t *country);

#endif
