#ifndef _LONG_REAL_H_

#define _LONG_REAL_H_

#define MANTISSA_LEN 30
#define MAX_LEN 39

#define INCORRECT_INPUT -2
#define MAX_LEN_ERROR -1
#define POWER_EXISTS 1

typedef struct
{
    unsigned char mantissa_sign;
    int mantissa[MANTISSA_LEN + 1];
    unsigned int mantissa_size;
    int power;
} long_real_t;

void print_info(void);
int symbol_number(char *string, char symbol);
int scan_string(char *string);
int char_to_int(char symbol);
int str_to_array(char *string, int *array);
int multiply_arrays(int *arr1, int sz1, int *arr2, int sz2, int *arr3);
int check_power(char *string);
char *get_power_pos(char *string);
void print_result(long_real_t l_real);

#endif
