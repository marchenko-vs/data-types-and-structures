#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

int m_allocate(matrix_t *matrix)
{
    int **ptrs = calloc(matrix->rows, sizeof(int *));

    if (!ptrs)
        return ERR_MEMORY_ALLOCATION;

    int *data = calloc(matrix->rows * matrix->columns, sizeof(int));

    if (!data)
    {
        free(ptrs);

        return ERR_MEMORY_ALLOCATION;
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
            if (matrix->elements[i][j] == 0 && matrix->elements[j][i] != 0)
                matrix->elements[i][j] = matrix->elements[j][i];
            else if (matrix->elements[i][j] != 0 && matrix->elements[j][i] == 0)
                matrix->elements[j][i] = matrix->elements[i][j];
}

int m_scan(matrix_t *matrix, size_t vertices)
{
    printf("Enter data in the following format:\nvertex_1 vertex_2 distance\n"
        "If you want to stop entering data, type: 0 0 0\n");

    int tmp_i, tmp_j, temp;

    while (1)
    {
        if (scanf("%d%d%d", &tmp_i, &tmp_j, &temp) != 3)
        {
            printf("Error: incorrect data type.\n");
            return EXIT_FAILURE;
        }

        if (temp < 0)
        {
            printf("Error: distances between vertices must be positive.\n");
            return EXIT_FAILURE;
        }

        if (tmp_i == 0 && tmp_j == 0 && temp == 0)
            break;

        if (tmp_i < 1 || tmp_j > vertices || temp < 0)
        {
            printf("Error: input data is incorrect.\n");
            return EXIT_FAILURE;
        }

        matrix->elements[tmp_i - 1][tmp_j - 1] = temp;
    }

    return EXIT_SUCCESS;
}

int draw_graph(char *filename, matrix_t *matrix, int option)
{
    FILE *f = fopen(filename, "w");

    if (f == NULL)
        return EXIT_FAILURE;

    if (option == 0)
    {
        fprintf(f, "graph test {\n");

        for (size_t i = 0; i < matrix->rows; i++)
            for (size_t j = 0; j < matrix->columns; j++)
                if (matrix->elements[i][j] != 0 && i <= j)
                    fprintf(f, "  %llu -- %llu [label=%d];\n", 
                        i + 1, j + 1, matrix->elements[i][j]);
    } 
    else
    {
        fprintf(f, "digraph test {\n");

        for (size_t i = 0; i < matrix->rows; i++)
            for (size_t j = 0; j < matrix->columns; j++)
                if (matrix->elements[i][j] != 0)
                    fprintf(f, "  %llu -> %llu [label=%d];\n", 
                        i + 1, j + 1, matrix->elements[i][j]);
    }
    
    fprintf(f, "}");

    fclose(f);

    return EXIT_SUCCESS;
}

int g_get_vertices(int *vertices)
{
    printf("Enter number of vertices of the graph:\n");

    if (scanf("%d", vertices) != 1)
    {
        printf("Error: incorrect data type.\n");
        return EXIT_FAILURE;
    }

    if (*vertices < 1)
    {
        printf("Error: incorrect number of vertices.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int g_is_orientated(int *is_orientated)
{
    printf("Is your graph orientated?\n0 - No\n1 - Yes\n");

    if (scanf("%d", is_orientated) != 1)
    {
        printf("Error: incorrect data type.\n");
        return EXIT_FAILURE;
    }

    if (*is_orientated < 0 || *is_orientated > 1)
    {
        printf("Error: you should choose between 0 and 1.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int g_get_vertex(int *vertex, size_t vertices)
{
    printf("Enter the starting vertex:\n");

    if (scanf("%d", vertex) != 1)
    {
        printf("Error: incorrect data type.\n");
        return EXIT_FAILURE;
    }

    if (*vertex < 1 || *vertex > vertices)
    {
        printf("Error: vertex %d does not exist.\n", *vertex);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
