#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 30

int char_to_int(char symbol)
{
    return symbol - 48;
}

int str_to_array(char *string, int *array)
{
    int size = 0;

    for (size_t i = 0; string[i] != '\0' && string[i] != 'e'; i++)
    {
        if (string[i] == '.')
            continue;

        array[i] = char_to_int(string[i]);
        size++;
    }

    return size;
}

void print_array(int *array, int size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d", array[i]);

    printf("\n");
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

    return size;
}

int main(void)
{
    char str1[MAX + 1] = "999999999\0";
    char str2[MAX + 1] = "8888888888\0";
    
    int arr1[MAX] = {0};
    int arr2[MAX] = {0};
    int arr3[MAX] = {0};

    int len1 = str_to_array(str1, arr1);
    int len2 = str_to_array(str2, arr2);

    print_array(arr1, len1);
    print_array(arr2, len2);
    int len3 = multiply_arrays(arr1, len1, arr2, len2, arr3);
    print_array(arr3, len3);
    printf("%d\n", len3);

    return EXIT_SUCCESS;
}

