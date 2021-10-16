#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>
#include "matrix.h"
#include "sparse_matrix.h"

#define FILE_ERROR 1
#define MEMORY_ALLOCATION_ERROR 3

int main(void)
{
    setbuf(stdout, NULL); // Отключение буферизации вывода
    
    matrix_t init_matrix = {.rows = 0, .columns = 0};
    printf("Введите размер матрицы через пробел (строки, столбцы): ");

    if (fscanf(stdin, "%d%d", &init_matrix.rows, &init_matrix.columns) != 2)
    {
        printf("Ошибка: размеры матрицы должны быть положительными целыми "
            "числами.\n");

        return DATA_TYPE_ERROR;
    }

    if (init_matrix.rows < 1 || init_matrix.columns < 1)
    {
        printf("Ошибка: размеры матрицы должны быть положительными целыми.\n");

        return EXIT_FAILURE;
    }

    matrix_t init_vector = {.rows = 0, .columns = 1};
    printf("Введите количество строк вектора-столбца: ");

    if (fscanf(stdin, "%d", &init_vector.rows) != 1)
    {
        printf("Ошибка: количество строк вектора-столбца должно быть "
            "положительным целым числом.\n");

        return DATA_TYPE_ERROR;
    }

    if (init_vector.rows < 1)
    {
        printf("Ошибка: количество строк вектора-столбца должно быть "
            "положительным.\n");

        return EXIT_FAILURE;
    }

    if (init_matrix.columns != init_vector.rows)
    {
        printf("Ошибка: число столбцов матрицы должно равняться числу строк "
            "вектора-столбца.\n");

        return EXIT_FAILURE;
    }

    if (!m_allocate(&init_matrix))
    {
        printf("Ошибка: не удалось выделить память под матрицу.\n");

        return MEMORY_ALLOCATION_ERROR;
    }

    if (!m_allocate(&init_vector))
    {
        printf("Ошибка: не удалось выделить память под вектор-столбец.\n");
        m_free(&init_matrix);

        return MEMORY_ALLOCATION_ERROR;
    }

    printf("Введите элементы матрицы:\n");

    if (m_fill(&init_matrix) == DATA_TYPE_ERROR)
    {
        printf("Ошибка: элементы матрицы должны быть вещественными "
            "числами.\n");

        return DATA_TYPE_ERROR;
    }

    printf("Введите элементы вектора-столбца:\n");

    if (m_fill(&init_vector) == DATA_TYPE_ERROR)
    {
        printf("Ошибка: элементы вектора-столбца должны быть вещественными "
            "числами.\n");
        m_free(&init_matrix);

        return DATA_TYPE_ERROR;
    }

    int choice = 0;
    printf("Введите номер метода умножения матрицы на вектор-столбец: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Ошибка: номер должен быть числом от 1 до 2.\n");
        m_free(&init_matrix);
        m_free(&init_vector);

        return DATA_TYPE_ERROR;
    }

    if (choice < 1 || choice > 3)
    {
        printf("Ошибка: номер должен быть числом от 1 до 2.\n");
        m_free(&init_matrix);
        m_free(&init_vector);

        return EXIT_FAILURE;
    }

    if (choice == 1)
    {
        sparse_matrix_t sparse_matrix = {.non_zero = 0};

        if (!sm_allocate(&sparse_matrix, &init_matrix))
        {
            printf("Ошибка: не удалось выделить память.\n");
            m_free(&init_matrix);
            m_free(&init_vector);

            return MEMORY_ALLOCATION_ERROR;
        }

        matrix_t res_vector = {.rows = init_matrix.rows, .columns = 1};

        if (!m_allocate(&res_vector))
        {
            printf("Ошибка: не удалось выделить память под вектор-столбец.\n");
            m_free(&init_matrix);
            m_free(&init_vector);

            return MEMORY_ALLOCATION_ERROR;
        }
        
        sm_fill(&sparse_matrix, &init_matrix);

        struct timeval tv_start, tv_stop;
        int64_t seconds;

        gettimeofday(&tv_start, NULL);
        sm_multiply(&sparse_matrix, &init_vector, &res_vector);
        gettimeofday(&tv_stop, NULL);

        seconds = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
        (tv_stop.tv_usec - tv_start.tv_usec);

        printf("Получившийся вектор-столбец:\n");
        m_print(&res_vector);
        printf("Время умножения: %" PRId64 " ms.\n", seconds);

        m_free(&res_vector);
    }

    if (choice == 2)
    {
        matrix_t res_vector = {.rows = init_matrix.columns, .columns = 1};

        if (!m_allocate(&res_vector))
        {
            m_free(&init_matrix);
            m_free(&init_vector);
            m_free(&res_vector);

            return MEMORY_ALLOCATION_ERROR;
        }

        struct timeval tv_start, tv_stop;
        int64_t seconds;

        gettimeofday(&tv_start, NULL);
        m_multiply(&init_matrix, &init_vector, &res_vector);
        gettimeofday(&tv_stop, NULL);

        seconds = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
        (tv_stop.tv_usec - tv_start.tv_usec);

        printf("Получившийся вектор-столбец:\n");
        m_print(&res_vector);
        printf("Время умножения: %" PRId64 " ms.\n", seconds);

        m_free(&res_vector);
    }

    m_free(&init_matrix);
    m_free(&init_vector);

    return EXIT_SUCCESS;
}
