#include "long_real.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    setbuf(stdout, NULL); // Отключение буферизации вывода
    print_info();

    char str_number_1[MAX_LEN + 3];
    int return_code = EXIT_SUCCESS;
    printf("Введите первое действительное число: ");

    // Ввод и проверка первого числа
    if ((return_code = scan_string(str_number_1)) == INCORRECT_INPUT) 
    {
        printf("Ошибка: некорректный ввод действительного числа.\n");
        return INCORRECT_INPUT;
    }
    if (return_code == EMPTY_INPUT_ERROR)
    {
        printf("Ошибка: введена пустая строка.\n");
        return EMPTY_INPUT_ERROR;
    }
    if (return_code == NO_MANTISSA_ERROR)
    {
        printf("Ошибка: не введена мантисса при наличии порядка.\n");
        return NO_MANTISSA_ERROR;
    }
    if (return_code == INCORRECT_SYMBOLS)
    {
        printf("Ошибка: введены некорректные символы.\n");
        return INCORRECT_SYMBOLS;
    }
    if (return_code == POWER_LEN_ERROR)
    {
        printf("Ошибка: длина порядка превышает 5 символов.\n");
        return POWER_LEN_ERROR;
    }
    if (return_code == MANTISSA_LEN_ERROR)
    {
        printf("Ошибка: длина мантиссы превышает 30 символов.\n");
        return MANTISSA_LEN_ERROR;
    }
    if (return_code == SIGNS_NUMBER_ERROR)
    {
        printf("Ошибка: неправильное количество знаков в числе.\n");
        return SIGNS_NUMBER_ERROR;
    }
    if (return_code == DOTS_NUMBER_ERROR)
    {
        printf("Ошибка: неправильное количество точек в числе.\n");
        return DOTS_NUMBER_ERROR;
    }
    if (return_code == NO_POWER_ERROR)
    {
        printf("Ошибка: не введен порядок при наличии символа 'E'.\n");
        return NO_POWER_ERROR;
    }

    char str_number_2[MAX_LEN + 3];
    return_code = EXIT_SUCCESS;
    printf("Введите второе действительное число: ");

    // Ввод и проверка второго числа
    if ((return_code = scan_string(str_number_2)) == INCORRECT_INPUT) 
    {
        printf("Ошибка: некорректный ввод действительного числа.\n");
        return INCORRECT_INPUT;
    }
    if (return_code == EMPTY_INPUT_ERROR)
    {
        printf("Ошибка: введена пустая строка.\n");
        return EMPTY_INPUT_ERROR;
    }
    if (return_code == NO_MANTISSA_ERROR)
    {
        printf("Ошибка: не введена мантисса при наличии порядка.\n");
        return NO_MANTISSA_ERROR;
    }
    if (return_code == INCORRECT_SYMBOLS)
    {
        printf("Ошибка: введены некорректные символы.\n");
        return INCORRECT_SYMBOLS;
    }
    if (return_code == POWER_LEN_ERROR)
    {
        printf("Ошибка: длина порядка превышает 5 символов.\n");
        return POWER_LEN_ERROR;
    }
    if (return_code == MANTISSA_LEN_ERROR)
    {
        printf("Ошибка: длина мантиссы превышает 30 символов.\n");
        return MANTISSA_LEN_ERROR;
    }
    if (return_code == SIGNS_NUMBER_ERROR)
    {
        printf("Ошибка: неправильное количество знаков в числе.\n");
        return SIGNS_NUMBER_ERROR;
    }
    if (return_code == DOTS_NUMBER_ERROR)
    {
        printf("Ошибка: неправильное количество точек в числе.\n");
        return DOTS_NUMBER_ERROR;
    }
    if (return_code == NO_POWER_ERROR)
    {
        printf("Ошибка: не введен порядок при наличии символа 'E'.\n");
        return NO_POWER_ERROR;
    }

    if (is_zero(str_number_1) || is_zero(str_number_2))
    {
        printf("Результат умножения:                  0.0");
        return EXIT_SUCCESS;
    }

    long_real_t number_1 = { 0 }; // Инициализация структур
    long_real_t number_2 = { 0 };
    long_real_t number_res = { 0 };

    simplify_number(str_number_1, &number_1); // Упрощение чисел
    simplify_number(str_number_2, &number_2);

    str_to_array(str_number_1, &number_1); // Перевод из строки в массив
    str_to_array(str_number_2, &number_2); // целых чисел

    multiply_numbers(&number_1, &number_2, &number_res); // Умножение

    if (print_result(&number_res) == POWER_OVERFLOW) // Вывод результата
    {
        printf("Ошибка: переполнение порядка.\n");
        return POWER_OVERFLOW;
    } 

    return EXIT_SUCCESS;
}
