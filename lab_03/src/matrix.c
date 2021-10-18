#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void m_free(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
        free(matrix->elements[i]);

    free(matrix->elements);
}

double **m_allocate(matrix_t *matrix)
{
    matrix->elements = calloc(matrix->rows, sizeof(double *));

    if (!matrix->elements)
        return NULL;

    for (size_t i = 0; i < matrix->rows; i++)
    {
        matrix->elements[i] = calloc(matrix->columns, sizeof(double));

        if (!matrix->elements[i])
        {
            m_free(matrix);

            return NULL;
        }
    }

    return matrix->elements;
}

int m_fill(FILE *stream, matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->columns; j++)
            if (fscanf(stream, "%lf", &matrix->elements[i][j]) != 1)
            {
                m_free(matrix);

                return DATA_TYPE_ERROR;
            }

    return EXIT_SUCCESS;
}

void m_multiply(matrix_t *matrix, matrix_t *vector, matrix_t *result)
{
    for (size_t i = 0; i < matrix->rows; i++)
    {
        double result_element = 0;

        for (size_t j = 0; j < matrix->columns; j++)
            result_element += matrix->elements[i][j] * vector->elements[j][0];

        result->elements[i][0] = result_element;
    }
}

void m_print(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
    {
        for (size_t j = 0; j < matrix->columns; j++)
            printf("%.1lf ", matrix->elements[i][j]);

        printf("\n");
    }   
}
