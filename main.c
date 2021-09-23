#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "long_real.h"

int main(void)
{
    setbuf(stdout, NULL);
    print_info();

    char number_1[MAX_LEN + 3];
    int return_code_1;

    printf("Введите первое действительное число: ");

    if ((return_code_1 = scan_string(number_1)) == INCORRECT_INPUT)
    {
        printf("Ошибка: неверная запись действительного числа\n");
        return INCORRECT_INPUT;
    }
        
    if (return_code_1 == MAX_LEN_ERROR)
    {
        printf("Ошибка: неверная длина действительного числа\n");
        return MAX_LEN_ERROR;
    }

    if (return_code_1 == POWER_EXISTS)
    {   
        if (check_power(number_1) == INCORRECT_INPUT)
        {
            printf("Ошибка: неверная запись действительного числа\n");
            return INCORRECT_INPUT;
        }
    }

    char *power_pos_1 = get_power_pos(number_1);

    char number_2[MAX_LEN + 3];
    int return_code_2;

    printf("Введите второе действительное число: ");

    if ((return_code_2 = scan_string(number_2)) == INCORRECT_INPUT)
    {
        printf("Ошибка: неверная запись действительного числа\n");
        return INCORRECT_INPUT;
    }
        
    if (return_code_2 == MAX_LEN_ERROR)
    {
        printf("Ошибка: неверная длина действительного числа\n");
        return MAX_LEN_ERROR;
    }

    if (return_code_2 == POWER_EXISTS)
    {   
        if (check_power(number_2) == INCORRECT_INPUT)
        {
            printf("Ошибка: неверная запись действительного числа\n");
            return INCORRECT_INPUT;
        }
    }

    char *power_pos_2 = get_power_pos(number_2);

    long_real_t l_dbl_1 = { 0 };
    long_real_t l_dbl_2 = { 0 };
    long_real_t l_dbl_result = { 0 };

    if (number_1[0] == '-')
        l_dbl_1.mantissa_sign = 1;

    if (number_2[0] == '-')
        l_dbl_2.mantissa_sign = 1;

    if ((number_1[0] == '-' && number_2[0] != '-') || 
        (number_1[0] != '-' && number_2[0] == '-'))
        l_dbl_result.mantissa_sign = 1;

    if (power_pos_1 != NULL)
        l_dbl_1.power = atoi(power_pos_1);

    if (power_pos_2 != NULL)
        l_dbl_2.power = atoi(power_pos_2);

    l_dbl_result.power = l_dbl_1.power + l_dbl_2.power;
    l_dbl_1.mantissa_size = str_to_array(number_1, l_dbl_1.mantissa);
    l_dbl_2.mantissa_size = str_to_array(number_2, l_dbl_2.mantissa);
    l_dbl_result.mantissa_size = multiply_arrays(l_dbl_1.mantissa, l_dbl_1.mantissa_size, l_dbl_2.mantissa, l_dbl_2.mantissa_size, l_dbl_result.mantissa);
    print_result(l_dbl_result);

    return EXIT_SUCCESS;
}
