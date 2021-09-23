#include "long_real.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASCII 48

void print_info(void)
{
    printf("Данная программа умножает два вещественных числа.\n");
    printf("Числа можно вводить и в обычном виде, и в экспоненциальном.\n\n");
    printf("Однако, есть определенные ограничения.\n");
    printf("1. Если запись в экспоненциальном виде, нужно обязательно"
        "\nуказать хотя бы одну цифру мантиссы.\n");
    printf("2. Если запись в экспоненциальном виде, нужно обязательно"
        "\nуказать хотя бы одну цифру порядка.\n"); 
    printf("3. Порядок может быть только целым числом.\n");
    printf("4. Длина мантиссы не более 30-и цифр,"
        "\nдлина порядка не более 5-и цифр.\n\n");
    printf("                                     "
        "±|-----------------------------|e±|---|\n");
}

int symbol_number(char *string, char symbol)
{
    int number = 0;

    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == symbol)
            number++;

    return number;
}

int scan_string(char *string)
{
    fgets(string, MAX_LEN + 3, stdin);

    if (strlen(string) > MAX_LEN && string[MAX_LEN] != '\n')
        return MAX_LEN_ERROR;

    string[strlen(string) - 1] = '\0';

    if (strlen(string) == 0)
        return INCORRECT_INPUT;

    if (string[0] == 'e' || string[0] == 'E')
        return INCORRECT_INPUT;

    if (strlen(string) == 1 && string[0] == '.')
        return INCORRECT_INPUT;

    for (size_t i = 0; string[i] != '\0'; i++)
        if (strchr("0123456789+-eE.", string[i]) == NULL)
            return INCORRECT_INPUT;

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

int char_to_int(char symbol)
{
    return symbol - ASCII;
}

int str_to_array(char *string, int *array)
{
    int size = 0, k = 0;

    for (size_t i = 0; strchr("eE\0", string[i]) == NULL; i++)
    {
        if (strchr(".-+", string[i]) != NULL)
            continue;
            
        array[k] = char_to_int(string[i]);
        size++;
        k++;
    }

    return size;
}

int multiply_arrays(int *arr1, int sz1, int *arr2, int sz2, int *arr3)
{
    int mod = 0, k = 0, add = 0, number = 0;

    for (int i = sz2 - 1; i >= 0; i--)
    {
        for (int j = sz1 - 1; j >= 0; j--)
        {
            number = arr1[j] * arr2[i] + mod;
            arr3[k] += number % 10;
            mod = number / 10;
            k++;
        }

        if (mod != 0)
            arr3[k] += mod;

        if (i == 0)
            break;
            
        k = add + 1;
        add++;
        mod = 0;
    }

    int size = 0; 

    if (mod != 0)
        size = k + 1;
    else
        size = k;

    for (size_t i = 0; i < size; i++)
        if (arr3[i] > 9)
        {
            arr3[i + 1] += arr3[i] / 10;
            arr3[i] %= 10;
        }

    for (size_t i = 0; i < size / 2; i++)
    {
        int tmp = arr3[i];
        arr3[i] = arr3[size - i - 1];
        arr3[size - i - 1] = tmp;
    }

    return size;
}

int check_power(char *string)
{
    char *pointer = NULL;

    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == 'e' || string[i] == 'E')
            pointer = string + i + 1;

    if (pointer[0] == '-' || pointer[0] == '+')
    {
        if (pointer[1] == '\0')
            return INCORRECT_INPUT;

        for (size_t i = 1; pointer[i] != '\0'; i++)
            if (strchr("0123456789", pointer[i]) == NULL)
                return INCORRECT_INPUT;
    }
    else
    {
        if (pointer[0] == '\0')
        return INCORRECT_INPUT;

        for (size_t i = 0; pointer[i] != '\0'; i++)
            if (strchr("0123456789", pointer[i]) == NULL)
                return INCORRECT_INPUT;
    }

    return EXIT_SUCCESS;
}

char *get_power_pos(char *string)
{
    char *pointer = NULL;

    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == 'e' || string[i] == 'E')
            pointer = string + i + 1;

    return pointer;
}

void print_result(long_real_t l_real)
{
    printf("Результат умножения: ");

    if (l_real.mantissa_sign == 1)
        printf("-");
    else
        printf("+");

    for (size_t i = 0; i < l_real.mantissa_size; i++)
        printf("%d", l_real.mantissa[i]);

    if (l_real.power < 0)
        printf("e-%d", l_real.power);
    else if (l_real.power > 0)
        printf("e+%d", l_real.power);

    printf("\n");
}
