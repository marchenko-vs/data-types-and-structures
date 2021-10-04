#ifndef _LONG_REAL_H_

#define _LONG_REAL_H_

#include <stdlib.h>

#define MANTISSA_LEN 30
#define MAX_LEN 39

#define MAX_LEN_ERROR -1
#define INCORRECT_INPUT -2
#define POWER_OVERFLOW -3
#define EMPTY_INPUT_ERROR -4
#define NO_MANTISSA_ERROR -5
#define INCORRECT_SYMBOLS -6
#define POWER_LEN_ERROR -7
#define MANTISSA_LEN_ERROR -8
#define SIGNS_NUMBER_ERROR -9
#define DOTS_NUMBER_ERROR -10
#define NO_POWER_ERROR -11

typedef struct
{
    unsigned char mantissa_sign;
    int mantissa[MANTISSA_LEN];
    unsigned int mantissa_size;
    int power;
} long_real_t;

void print_info(void);
int scan_string(char *string);
void shift(char *string, int n);
void get_power(char *string, long_real_t *number);
int is_zero(char *string);
void get_mantissa_sign(char *string, long_real_t *number);
void simplify_number(char *string, long_real_t *number);
int char_to_int(char symbol);
void str_to_array(char *string, long_real_t *number);
void array_copy(int *array_src, int size_src, long_real_t *number);
void multiply_numbers(long_real_t *l_real_1, long_real_t *l_real_2,
long_real_t *l_real_res);
void simplify_mantissa(long_real_t *number);
int print_result(long_real_t *number);

#endif
