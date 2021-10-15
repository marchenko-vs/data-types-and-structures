#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>
#include <inttypes.h>

#define ARGS_ERROR 1
#define FILE_ERROR 2
#define DATA_TYPE_ERROR 3

#define M 100
#define N 100

typedef struct
{
    double *values;
    int *cols;
    int *list;
} sparse_t;

void print_result(double *vector, int size)
{
    printf("Полученный вектор-столбец:\n");
    for (size_t i = 0; i < size; i++)
        printf("%.2lf\n", vector[i]);
}

void print_lf_vector(double *vector, int size)
{
    for (size_t i = 0; i < size; i++)
        printf("%.2lf ", vector[i]);
}

void print_d_vector(int *vector, int size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d ", vector[i]);
}

void print_matrix(double (*matrix)[N], int rows, int cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
            printf("%lf ", matrix[i][j]);
        printf("\n");
    }   
}

void multiply(double (*matrix)[N], int rows, int cols, double *vector, double *res_vector)
{
    for (size_t i = 0; i < rows; i++)
    {
        double res_elem = 0;
        for (size_t j = 0; j < cols; j++)
            res_elem += matrix[i][j] * vector[j];
        res_vector[i] = res_elem;
    }
}

int main(void)
{
    setbuf(stdout, NULL);
    
    int matrix_rows = 0, matrix_cols = 0;
    printf("Введите размер матрицы через пробел (строки, столбцы): ");
    if (fscanf(stdin, "%d%d", &matrix_rows, &matrix_cols) != 2)
    {
        return DATA_TYPE_ERROR;
    }
    if (matrix_rows < 1 || matrix_cols < 1)
    {
        return EXIT_FAILURE;
    }

    int vector_rows = 0;
    printf("Введите количество строк вектора-столбца: ");
    if (fscanf(stdin, "%d", &vector_rows) != 1)
    {
        return DATA_TYPE_ERROR;
    }
    if (vector_rows < 1)
    {
        return EXIT_FAILURE;
    }

    if (matrix_cols != vector_rows)
    {
        printf("Ошибка: число столбцов матрицы должно равняться числу строк"
            " вектора-столбца.\n");
        return EXIT_FAILURE;
    }

    double init_matrix[M][N];
    double *init_vector = calloc(vector_rows, sizeof(double));

    printf("Введите элементы матрицы:\n");
    for (size_t i = 0; i < matrix_rows; i++)
        for (size_t j = 0; j < matrix_cols; j++)
            if (fscanf(stdin, "%lf", &init_matrix[i][j]) != 1)
            {
                free(init_vector);
                return DATA_TYPE_ERROR;
            }

    printf("Введите элементы вектора-столбца:\n");
    for (size_t i = 0; i < vector_rows; i++)
        if (fscanf(stdin, "%lf", &init_vector[i]) != 1)
        {
            free(init_vector);
            return DATA_TYPE_ERROR;
        }

    int choice = 0;
    printf("Введите номер метода умножения матрицы на вектор-столбец: ");
    if (scanf("%d", &choice) != 1)
    {
        return DATA_TYPE_ERROR;
    }
    if (choice < 1 || choice > 3)
    {
        return EXIT_FAILURE;
    }

    if (choice == 1)
    {
        double *res_vector = calloc(matrix_cols, sizeof(double));
        size_t matrix_non_zero = 0;
        for (size_t i = 0; i < matrix_rows; i++)
            for (size_t j = 0; j < matrix_cols; j++)
                if (init_matrix[i][j] != 0)
                    matrix_non_zero++;
        sparse_t sparse_martix;
        sparse_martix.values = calloc(matrix_non_zero, sizeof(double));
        sparse_martix.cols = calloc(matrix_non_zero, sizeof(int));
        sparse_martix.list = calloc(matrix_rows + 1, sizeof(int));
        size_t k = 0, l = 0;
        for (size_t i = 0; i < matrix_rows; i++)
        {
            bool flag = false;
            for (size_t j = 0; j < matrix_cols; j++)
            {
                if (init_matrix[i][j] != 0)
                {
                    if (!flag)
                    {
                        sparse_martix.list[l++] = k + 1;
                        flag = true;
                    }
                    sparse_martix.values[k] = init_matrix[i][j];
                    sparse_martix.cols[k] = j + 1;
                    k++;
                }
            }
            if (!flag)
                sparse_martix.list[l++] = k + 1;
        }
        sparse_martix.list[l] = matrix_non_zero + 1;

        size_t vector_non_zero = 0;
        for (size_t i = 0; i < vector_rows; i++)
            if (init_vector[i] != 0)
                vector_non_zero++;
        sparse_t sparse_vector;
        sparse_vector.values = calloc(vector_non_zero, sizeof(double));
        sparse_vector.cols = calloc(vector_non_zero, sizeof(int));
        sparse_vector.list = calloc(vector_rows + 1, sizeof(int));
        k = 0, l = 0;
        for (size_t i = 0; i < vector_rows; i++)
        {
            if (init_vector[i] != 0)
            {
                sparse_vector.values[k] = init_vector[i];
                sparse_vector.list[l++] = k + 1;
                sparse_vector.cols[k] = 1;
                k++;
            }
            else
                sparse_vector.list[l++] = k + 1;
        }
        sparse_vector.list[l] = vector_non_zero + 1;

        for (size_t i = 0; i < matrix_rows; i++)
        {
            double tmp_elem = 0;
            for (int j = sparse_martix.list[i] - 1; j < sparse_martix.list[i + 1] - 1; j++)
                tmp_elem += sparse_martix.values[j] * sparse_vector.values[j % vector_rows];
            res_vector[i] = tmp_elem;
        }
        print_result(res_vector, matrix_cols);

        free(sparse_martix.values);
        free(sparse_martix.cols);
        free(sparse_martix.list);

        free(sparse_vector.values);
        free(sparse_vector.cols);
        free(sparse_vector.list);

        free(res_vector);
    }
    if (choice == 2)
    {
        double *res_vector = calloc(matrix_cols, sizeof(double));
        struct timeval tv_start, tv_stop;
        int64_t seconds;
        gettimeofday(&tv_start, NULL);
        multiply(init_matrix, matrix_rows, matrix_cols, init_vector, res_vector);
        gettimeofday(&tv_stop, NULL);
        seconds = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
        (tv_stop.tv_usec - tv_start.tv_usec);
        print_result(res_vector, matrix_rows);
        printf("%" PRId64 "\n", seconds);

        free(res_vector);
        free(init_vector);
    }

    return EXIT_SUCCESS;
}
