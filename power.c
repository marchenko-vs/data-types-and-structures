#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INCORRECT_INPUT -1
#define POWER_EXISTS 1

int symbol_number(char *string, char symbol)
{
    int number = 0;

    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == symbol)
            number++;

    return number;
}

int check_string(char *string)
{
    int dots_number = 0, e_number = 0, sign_number = 0;

    dots_number += symbol_number(string, '.');
    e_number += symbol_number(string, 'e');
    e_number += symbol_number(string, 'E');
    sign_number += symbol_number(string, '-');
    sign_number += symbol_number(string, '+');

    if (dots_number > 1 || e_number > 1 || sign_number > 2)
        return INCORRECT_INPUT;

    if (e_number == 1)
        return POWER_EXISTS;

    return EXIT_SUCCESS;
}

int get_power(char *string)
{
    char *pointer = NULL;

    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == 'e' || string[i] == 'E')
            pointer = string + i + 1;

    int power = atoi(pointer);

    return power;
}

int main(void)
{
    char str[] = "1232.23e-1234\0";

    if (check_string(str) == POWER_EXISTS)
        printf("%d", get_power(str));

    return EXIT_SUCCESS;
}

