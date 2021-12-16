#include <stdlib.h>

#include "graph.h"

int m_allocate(matrix_t *matrix)
{
    int **ptrs = calloc(matrix->rows, sizeof(int *));

    if (!ptrs)
        return EXIT_FAILURE;

    int *data = calloc(matrix->rows * matrix->columns, sizeof(int));

    if (!data)
    {
        free(ptrs);

        return EXIT_FAILURE;
    }

    matrix->elements = ptrs;

    for (size_t i = 0; i < matrix->rows; i++)
        matrix->elements[i] = data + i * matrix->columns;

    return EXIT_SUCCESS;
}

void m_free(matrix_t *matrix)
{
    free(matrix->elements[0]);
    free(matrix->elements);
}

void m_constant_fill(matrix_t *matrix, int constant)
{
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->columns; j++)
            matrix->elements[i][j] = constant;
}

void m_mirror(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; i++)
        for (size_t j = 0; j < matrix->columns; j++)
            if (i > j)
                matrix->elements[i][j] = matrix->elements[j][i];
}
