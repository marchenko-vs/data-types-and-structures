#include "long_real.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PLUS 0
#define MINUS 1
#define ASCII 48

/**
 * Функция печатает необходимую информация для начала работы с программой
 */
void print_info(void)
{
    printf("==============================================================="
        "============\n");
    printf("                          Лабораторная работа #1               "
        "  \n");
    printf("==============================================================="
        "============\n");
    printf("Данная программа умножает два вещественных числа.\n");
    printf("Числа можно вводить и в обычном виде, и в экспоненциальном.\n\n");
    printf("Есть некоторые ограничения.\n");
    printf("==============================================================="
        "============\n");
    printf("1. Если запись в экспоненциальном виде, нужно обязательно"
        "\nуказать хотя бы одну цифру мантиссы.\n");
    printf("2. Если запись в экспоненциальном виде, нужно обязательно"
        "\nуказать хотя бы одну цифру порядка.\n"); 
    printf("3. Порядок может быть только целым числом.\n");
    printf("4. Длина мантиссы не более 30-и цифр,"
        "\nдлина порядка не более 5-и цифр.\n");
    printf("5. Знаки можно не указывать.\n");
    printf("6. В записи числа могут присутствовать только цифры,\nзнаки"
        "'+', '-', '.', а также латинские 'e' и 'E'.\n");
    printf("7. Строка не может быть пустой или содержать пробельные"
        " символы.\n");
    printf("==============================================================="
        "============\n");
    printf("Отметка '31' поставлена из-за того,\nчто зарезервировано одно"
        " место для точки.\n\n");
    printf("                                     "
        "0         10        20         31      \n");
    printf("                                     "
        "±|--------|---------|----------|e±-----\n");
}

/**
 * Функция считывает строку и сразу же проверяет ее на корректность
 */
int scan_string(char *string)
{
    fgets(string, MAX_LEN + 3, stdin);

    if (strlen(string) > MAX_LEN && string[MAX_LEN] != '\n')
        return MAX_LEN_ERROR;

    string[strlen(string) - 1] = '\0';

    if (strlen(string) == 0)
        return EMPTY_INPUT_ERROR;

    if (string[0] == 'e' || string[0] == 'E')
        return NO_MANTISSA_ERROR;

    if (strlen(string) == 1 && strchr("+-.", string[0]) != NULL)
        return INCORRECT_INPUT;

    for (size_t i = 0; string[i] != '\0'; i++)
        if (strchr("0123456789+-eE.", string[i]) == NULL)
            return INCORRECT_SYMBOLS;

    int exp_pos = -1;

    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == 'e' || string[i] == 'E')
        {
            exp_pos = i;
            break;
        }

    if (exp_pos != -1)
    {
        for (size_t i = 1; i < exp_pos; i++)
            if (string[i] == '-' || string[i] == '+')
                return SIGNS_NUMBER_ERROR;

        int num_of_dots = 0;

        for (size_t i = 0; i < exp_pos; i++)
            if (string[i] == '.')
                num_of_dots++;

        if (num_of_dots > 1)
            return DOTS_NUMBER_ERROR;

        for (size_t i = exp_pos + 2; string[i] != '\0'; i++)
            if (strchr("+-eE", string[i]) != NULL)
                return SIGNS_NUMBER_ERROR;

        if (strchr("+-", string[exp_pos + 1]) != NULL &&
            string[exp_pos + 2] == '\0')
            return NO_POWER_ERROR;

        num_of_dots = 0;

        for (size_t i = exp_pos + 1; string[i] != '\0'; i++)
            if (string[i] == '.')
                num_of_dots++;

        if (num_of_dots != 0)
            return DOTS_NUMBER_ERROR;

        if (string[exp_pos + 1] == '\0')
            return NO_POWER_ERROR;

        int mantissa_len = 0;

        for (size_t i = 0; i < exp_pos; i++)
            if (string[i] != '+' && string[i] != '-' && string[i] != '.')
                mantissa_len++;

        if (mantissa_len > 30)
            return MANTISSA_LEN_ERROR;

        int power_len = 0;

        for (size_t i = exp_pos + 1; string[i] != '\0'; i++)
            if (string[i] != '+' && string[i] != '-')
                power_len++;

        if (power_len > 5)
            return POWER_LEN_ERROR;
    }
    else
    {
        for (size_t i = 1; string[i] != '\0'; i++)
            if (string[i] == '-' || string[i] == '+')
                return SIGNS_NUMBER_ERROR;

        int num_of_dots = 0;

        for (size_t i = 0; string[i] != '\0'; i++)
            if (string[i] == '.')
                num_of_dots++;

        if (num_of_dots > 1)
            return DOTS_NUMBER_ERROR;

        int mantissa_len = 0;

        for (size_t i = 0; string[i] != '\0'; i++)
            if (string[i] != '+' && string[i] != '-' && string[i] != '.')
                mantissa_len++;

        if (mantissa_len > 30)
            return MANTISSA_LEN_ERROR;
    }

    return EXIT_SUCCESS;
}

/**
 * Вспомогательная функция для сдвига элементов в строке на n позиций
 * @string - строка
 * @n - количество позиций сдвига
 */
void shift(char *string, int n)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < strlen(string); j++)
            string[j] = string[j + 1];
}

/**
 * Функция находит порядок в экспоненциальной записи числа и переводит его из
 * строки в целое число, записывая в поле power структуры типа long_real_t
 * @string - строка
 * @number - структура типа long_real_t
 */
void get_power(char *string, long_real_t *number)
{
    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == 'e' || string[i] == 'E')
            number->power += atoi(string + i + 1);
}

/**
 * Логическая функция, определяющая, является ли число, записанное в строке,
 * нулем
 * @string - строка
 */
int is_zero(char *string)
{
    for (size_t i = 0; strchr("eE\0", string[i]) == NULL; i++)
        if (strchr("+-.0", string[i]) == NULL)
            return 0;

    return 1;
}

/**
 * Функция, определяющая знак мантиссы
 * @string - строка
 * @number - структура типа long_real_t
 */
void get_mantissa_sign(char *string, long_real_t *number)
{
    if (string[0] == '-')
        number->mantissa_sign = MINUS;
}

/**
 * Функция, которая упрощает запись действительного числа в строке (удаляет
 * незначащие нули, перемещает точку, удаляет знак мантиссы)
 * @string - строка
 * @number - структура типа long_real_t
 */
void simplify_number(char *string, long_real_t *number)
{
    get_mantissa_sign(string, number);

    if (string[0] == '+' || string[0] == '-')
        shift(string, 1);

    int first_digit = 0, dot_pos = -1, e_pos = strlen(string);

    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == 'e' || string[i] == 'E')
        {
            e_pos = i;
            break;
        }

    for (size_t i = 0; strchr("eE\0", string[i]) == NULL; i++)
        if (string[i] != '0' && string[i] != '.')
        {
            first_digit = i;
            break;
        }

    for (size_t i = 0; strchr("eE\0", string[i]) == NULL; i++)
        if (string[i] == '.')
        {
            dot_pos = i;
            break;
        }

    if (dot_pos < first_digit && dot_pos != -1)
    {
        number->power -= (e_pos - dot_pos - 1);
        shift(string, first_digit);
    }
    else if (dot_pos > first_digit && dot_pos != -1)
    {
        number->power -= (e_pos - dot_pos - 1);
        shift(string + dot_pos, 1);

        if (first_digit != 0)
            shift(string, first_digit);
    }

    e_pos = strlen(string);

    for (size_t i = 0; string[i] != '\0'; i++)
        if (string[i] == 'e' || string[i] == 'E' || string[i] == '\0')
        {
            e_pos = i;
            break;
        }

    if (string[e_pos - 1] == '0')
        {
            for (int i = e_pos - 2; i >= 0; i--)
                if (string[i] != '0')
                {
                    first_digit = i;
                    break;
                }

            if (e_pos - first_digit > 1)
            {
                shift(string + first_digit + 1, e_pos - first_digit - 1);
                number->power += (e_pos - first_digit - 1);
            }
        }

    get_power(string, number);
}

/**
 * Вспомогательная функция, которая переводит цифру, записанную в переменную
 * типа char, в int
 * @symbol - цифра, записанная в переменной типа char
 */
int char_to_int(char symbol)
{
    return symbol - ASCII;
}

/**
 * Функция, переводящая мантиссу числа, записанного в строке, в массив целых
 * чисел - заполняет поле mantissa структуры типа long_real_t
 * @string - строка, в которой записано действительное число
 * @number - структура типа long_real_t
 */
void str_to_array(char *string, long_real_t *number)
{
    for (int i = 0; strchr("eE\0", string[i]) == NULL; i++)
    {       
        number->mantissa[i] = char_to_int(string[i]);
        number->mantissa_size++;
    }
}

/**
 * Наиболее важная функция, реализующая умножение действительных чисел и, если
 * нужно, их округление
 * @params - три структуры типа long_real_t
 */
void multiply_numbers(long_real_t *l_real_1, long_real_t *l_real_2,
long_real_t *l_real_res)
{
    l_real_res->mantissa_sign = l_real_1->mantissa_sign + 
    l_real_2->mantissa_sign;
    l_real_res->power += l_real_1->power + l_real_2->power;

    int mod = 0, k = 0, begin = 0, number = 0;
    unsigned char flag = 0;

    for (int i = l_real_2->mantissa_size - 1; i >= 0; i--)
    {
        for (int j = l_real_1->mantissa_size - 1; j >= 0; j--)
        {
            number = l_real_1->mantissa[j] * l_real_2->mantissa[i] + mod;
            l_real_res->mantissa[k] += number % 10;
            mod = number / 10;
            k++;
        }

        if (mod != 0)
            l_real_res->mantissa[k] += mod;

        

        for (size_t i = 0; i < k - 1; i++)
            if (l_real_res->mantissa[i] > 9)
            {
                l_real_res->mantissa[i + 1] += l_real_res->mantissa[i] / 10;
                l_real_res->mantissa[i] %= 10;
            }

        if (i == 0)
            break;

        if (k > MANTISSA_LEN)
        {
            flag = 1;

            if (l_real_res->mantissa[0] >= 5)
                l_real_res->mantissa[1]++;

            for (size_t i = 0; i < MANTISSA_LEN - 1; i++)
                if (l_real_res->mantissa[i] > 9)
                {
                    l_real_res->mantissa[i + 1] += l_real_res->mantissa[i] / 10;
                    l_real_res->mantissa[i] %= 10;
                }

            for (size_t i = 0; i < MANTISSA_LEN - 1; i++)
                l_real_res->mantissa[i] = l_real_res->mantissa[i + 1];

            l_real_res->mantissa[MANTISSA_LEN - 1] = 0;
        }

        if (!flag)
        {
            k = begin + 1;
            begin++;
        }
        else
            k = begin;

        mod = 0;
    }

    if (flag)
    {
        l_real_res->mantissa_size = 1;

        if (l_real_res->mantissa[MANTISSA_LEN + 1] >= 5)
            l_real_res->mantissa[0]++;
        else
            l_real_res->mantissa[0] = 0;

        l_real_res->power += l_real_1->mantissa_size + l_real_2->mantissa_size;

        return;
    }
    else if (mod != 0 && k <= MANTISSA_LEN)
        l_real_res->mantissa_size = k + 1;
    else
        l_real_res->mantissa_size = k;

    for (size_t i = 0; i < l_real_res->mantissa_size - 1; i++)
        if (l_real_res->mantissa[i] > 9)
        {
            l_real_res->mantissa[i + 1] += l_real_res->mantissa[i] / 10;
            l_real_res->mantissa[i] %= 10;
        }

    for (size_t i = 0; i < l_real_res->mantissa_size / 2; i++)
    {
        int tmp = l_real_res->mantissa[i];
        l_real_res->mantissa[i] = 
        l_real_res->mantissa[l_real_res->mantissa_size - i - 1];
        l_real_res->mantissa[l_real_res->mantissa_size - i - 1] = tmp;
    }
}

/**
 * Функция, производящая форматированный вывод структуры типа long_real_t
 * @number - структура типа long_real_t
 */
int print_result(long_real_t *number)
{
    int new_power = number->power + number->mantissa_size;

    if (abs(new_power) > 99999)
        return POWER_OVERFLOW;
    
    printf("Результат умножения:                 ");

    if (number->mantissa_sign == MINUS)
        printf("-0.");
    else
        printf("+0.");

    if (number->mantissa_size > MANTISSA_LEN - 1)
        number->mantissa_size = MANTISSA_LEN - 2;

    for (size_t i = 0; i < number->mantissa_size; i++)
        printf("%d", number->mantissa[i]);

    if (new_power <= 0)
        printf("e%d", new_power);
    else if (new_power > 0)
        printf("e+%d\n", new_power);

    return EXIT_SUCCESS;
}
