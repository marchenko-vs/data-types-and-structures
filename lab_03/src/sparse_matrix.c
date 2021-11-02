#include "matrix.h"
#include "sparse_matrix.h"
#include <stdbool.h>
#include <stdlib.h>

#include <stdio.h>

double *sm_allocate(sparse_matrix_t *sparse_matrix, matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->columns; j++)
        {
            if (matrix->elements[i][j] != 0)
                sparse_matrix->non_zero++;
        }

    sparse_matrix->elements = calloc(sparse_matrix->non_zero, sizeof(double));

    if (!sparse_matrix->elements)
        return NULL;

    sparse_matrix->columns = calloc(sparse_matrix->non_zero, sizeof(int));

    if (!sparse_matrix->columns)
    {
        free(sparse_matrix->elements);

        return NULL;
    }

    sparse_matrix->row_pointers = calloc(matrix->rows + 1, sizeof(int));

    if (!sparse_matrix->row_pointers)
    {
        free(sparse_matrix->elements);
        free(sparse_matrix->columns);
        
        return NULL;
    }

    return sparse_matrix->elements;
}

void sm_fill(sparse_matrix_t *sparse_matrix, matrix_t *matrix)
{
    size_t k = 0, l = 0;

    for (size_t i = 0; i < matrix->rows; i++)
    {
        bool flag = false;

        for (size_t j = 0; j < matrix->columns; j++)
        {
            if (matrix->elements[i][j] != 0)
            {
                if (!flag)
                {
                    sparse_matrix->row_pointers[l++] = k + 1;
                    flag = true;
                }

                sparse_matrix->elements[k] = matrix->elements[i][j];
                sparse_matrix->columns[k] = j + 1;
                k++;
            }
        }

        if (!flag)
            sparse_matrix->row_pointers[l++] = k + 1;
    }

    sparse_matrix->row_pointers[l] = sparse_matrix->non_zero + 1;
}

void sm_multiply(sparse_matrix_t *sparse_matrix, matrix_t *vector,
    matrix_t *result, const int rows)
{
    for (size_t i = 0; i < rows; i++)
        {
            double result_element = 0;

            for (size_t j = sparse_matrix->row_pointers[i] - 1;
                j < sparse_matrix->row_pointers[i + 1] - 1; j++)
                result_element += sparse_matrix->elements[j] *
                    vector->elements[sparse_matrix->columns[j] - 1][0];

            result->elements[i][0] = result_element;
        }
}

void sm_free(sparse_matrix_t *sparse_matrix)
{
    free(sparse_matrix->elements);
    free(sparse_matrix->columns);
    free(sparse_matrix->row_pointers);
}

void sm_print(sparse_matrix_t *sparse_matrix, const int rows)
{
    printf("Значения ненулевых элементов: ");

    for (size_t i = 0; i < sparse_matrix->non_zero; i++)
        printf("%.2lf ", sparse_matrix->elements[i]);

    printf("\nЗначения столбцов соответствующих элементов: ");

    for (size_t i = 0; i < sparse_matrix->non_zero; i++)
        printf("%d ", sparse_matrix->columns[i]);

    printf("\nЗначения указателей на строки: ");

    for (size_t i = 0; i < rows + 1; i++)
        printf("%d ", sparse_matrix->row_pointers[i]);

    printf("\n");
}
