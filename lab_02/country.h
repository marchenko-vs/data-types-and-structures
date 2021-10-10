#ifndef _COUNTRY_H_

#define _COUNTRY_H_

#include <stdio.h>

#define NAME_SIZE 50
#define MAX_TABLE_SIZE 300

#define TOO_MANY_STRUCTURES -1
#define INVALID_DATA -2

#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"

typedef struct
{
    int objects_number;
    short int main_type;
} excursion_t;

typedef struct
{
    double flight_time;
    short int main_season;
    short int air_temperature;
    short int water_temperature;
} beach_t;

typedef struct
{
    int minimal_price;
    short int sport_kind;
} sport_t;

typedef union
{
    excursion_t excursion_type;
    beach_t beach_type;
    sport_t sport_type;
} tourism_t;

typedef struct
{
    char country_name[NAME_SIZE + 1];
    char capital_name[NAME_SIZE + 1];
    long long population;
    short int mainland;
    short int covid_vaccine;
    short int tourism_type_number;
    tourism_t tourism_type;
} country_t;

typedef struct
{
    size_t index;
    long long key;
} key_t;

void print_instruction(void);
void print_menu(void);
int check_string(char *string);
int scanf_country(FILE *stream, country_t *country);
int read_all_data(FILE *stream, country_t *array, key_t *key_array, size_t *size);
char *get_mainland_name(const int number);
char *get_covid_requirements(const int number);
char *get_tourism_type(const int number);
char *get_main_type(const int number);
char *get_sports_type(const int number);
char *get_season_name(const int number);
int find_by_sport(FILE *stream, country_t *country, const int size);
int array_push(country_t *country, size_t *size);
int array_remove(country_t *country, size_t *size);
void printf_country(FILE *stream, country_t *country);
void print_all_data(FILE *stream, country_t *country, const int size);
void print_by_keys(FILE *stream, country_t *country, key_t *keys, const int size);

#endif
