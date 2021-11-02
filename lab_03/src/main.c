#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>
#include "matrix.h"
#include "sparse_matrix.h"
#include "info.h"

#define FILE_ERROR 1
#define CHOICE_ERROR 2
#define MEMORY_ALLOCATION_ERROR 3

#define NAME_SIZE 50

int main(void)
{
    setbuf(stdout, NULL); // Отключение буферизации вывода
    print_instruction();
    
    short int choice = 0;
    print_input_format();
    if (scanf("%hd", &choice) != 1)
    {
        printf("Ошибка: некорректно введен номер способа ввода данных.\n");
        return DATA_TYPE_ERROR;
    }

    FILE *input_file;
    char input_stream[NAME_SIZE + 1];

    if (choice == 1)
        input_file = stdin;
    else if (choice == 2)
    {
        printf("Введите название файла: ");
        getchar();

        if (fgets(input_stream, NAME_SIZE + 1, stdin) == NULL)
        {
            printf("Ошибка: не удалось считать название файла.\n");
            return EXIT_FAILURE;
        }

        input_stream[strlen(input_stream) - 1] = '\0';
        input_file = fopen(input_stream, "r");

        if (!input_file)
        {
            printf("Ошибка: не удалось открыть файл.\n");
            return FILE_ERROR;
        }
    }
    else
    {
        printf("Ошибка: номер способа ввода данных может быть 1 или 2.\n");
        return CHOICE_ERROR;
    }

    matrix_t init_matrix = {.rows = 0, .columns = 0};
    matrix_t init_vector = {.rows = 0, .columns = 1};

    printf("Введите размер матрицы через пробел (строки, столбцы): ");
    if (fscanf(input_file, "%d%d", &init_matrix.rows, &init_matrix.columns) 
        != 2)
    {
        printf("Ошибка: некорректно введены размеры матрицы.\n");
        fclose(input_file);
        return DATA_TYPE_ERROR;
    }
    if (init_matrix.rows < 1 || init_matrix.columns < 1)
    {
        printf("Ошибка: размеры матрицы должны быть положительными целыми.\n");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    printf("Введите количество строк вектора-столбца: ");
    if (fscanf(input_file, "%d", &init_vector.rows) != 1)
    {
        printf("Ошибка: некорректно введено количество строк "
            "вектора-столбца.\n");
        fclose(input_file);
        return DATA_TYPE_ERROR;
    }
    if (init_vector.rows < 1)
    {
        printf("Ошибка: количество строк вектора-столбца должно быть "
            "положительным.\n");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    if (init_matrix.columns != init_vector.rows)
    {
        printf("Ошибка: число столбцов матрицы должно равняться числу строк "
            "вектора-столбца.\n");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    if (!m_allocate(&init_matrix))
    {
        printf("Ошибка: не удалось выделить память под матрицу.\n");
        fclose(input_file);
        return MEMORY_ALLOCATION_ERROR;
    }
    if (!m_allocate(&init_vector))
    {
        printf("Ошибка: не удалось выделить память под вектор-столбец.\n");
        m_free(&init_matrix);
        fclose(input_file);
        return MEMORY_ALLOCATION_ERROR;
    }

    printf("Введите элементы матрицы:\n");
    if (m_fill(input_file, &init_matrix) == DATA_TYPE_ERROR)
    {
        printf("Ошибка: элементы матрицы должны быть вещественными "
            "числами.\n");
        m_free(&init_matrix);
        m_free(&init_vector);
        fclose(input_file);
        return DATA_TYPE_ERROR;
    }

    printf("Введите элементы вектора-столбца:\n");
    if (m_fill(input_file, &init_vector) == DATA_TYPE_ERROR)
    {
        printf("Ошибка: элементы вектора-столбца должны быть вещественными "
            "числами.\n");
        m_free(&init_matrix);
        m_free(&init_vector);
        fclose(input_file);
        return DATA_TYPE_ERROR;
    }

    short int method = 0;
    print_menu();

    if (fscanf(input_file, "%hd", &method) != 1)
    {
        printf("Ошибка: номер должен быть числом от 1 до 2.\n");
        m_free(&init_matrix);
        m_free(&init_vector);
        fclose(input_file);
        return DATA_TYPE_ERROR;
    }

    matrix_t res_vector = {.rows = init_matrix.rows, .columns = 1};
    struct timeval tv_start, tv_stop;
    int64_t seconds;
    short int output_format = 0;

    if (!m_allocate(&res_vector))
    {
        printf("Ошибка: не удалось выделить память под вектор-столбец.\n");
        m_free(&init_matrix);
        m_free(&init_vector);
        fclose(input_file);
        return MEMORY_ALLOCATION_ERROR;
    }

    if (method == 1)
    {
        sparse_matrix_t sparse_matrix = {.non_zero = 0};

        if (!sm_allocate(&sparse_matrix, &init_matrix))
        {
            printf("Ошибка: не удалось выделить память.\n");
            m_free(&init_matrix);
            m_free(&init_vector);
            m_free(&res_vector);
            fclose(input_file);
            return MEMORY_ALLOCATION_ERROR;
        }
        
        sm_fill(&sparse_matrix, &init_matrix);
        gettimeofday(&tv_start, NULL);
        sm_multiply(&sparse_matrix, &init_vector, &res_vector,
            init_matrix.rows);
        gettimeofday(&tv_stop, NULL);

        seconds = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
        (tv_stop.tv_usec - tv_start.tv_usec);

        print_output_format(init_matrix.rows);
        if (fscanf(input_file, "%hd", &output_format) != 1)
        {
            printf("Ошибка: некорректно введен номер формы вывода "
                "результата.\n");
            m_free(&init_matrix);
            m_free(&init_vector);
            m_free(&res_vector);
            sm_free(&sparse_matrix);
            fclose(input_file);
            return EXIT_FAILURE;
        }

        printf("Результат:\n");
        if (output_format == 1)
            m_print(&res_vector);
        else if (output_format == 2)
        {
            sparse_matrix_t sparse_res = {.non_zero = 0};

            sm_allocate(&sparse_res, &res_vector);
            sm_fill(&sparse_res, &res_vector);
            sm_print(&sparse_res, res_vector.rows);
            sm_free(&sparse_res);
        }
        else
        {
            printf("Ошибка: формат вывода должен быть числом от 1 до 2.\n");
            m_free(&init_matrix);
            m_free(&init_vector);
            m_free(&res_vector);
            sm_free(&sparse_matrix);
            fclose(input_file);
            return EXIT_FAILURE;
        }

        printf("Время умножения: %" PRId64 " мкс.\n", seconds);
        sm_free(&sparse_matrix);
    }
    else if (method == 2)
    {
        gettimeofday(&tv_start, NULL);
        m_multiply(&init_matrix, &init_vector, &res_vector);
        gettimeofday(&tv_stop, NULL);

        seconds = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
        (tv_stop.tv_usec - tv_start.tv_usec);

        printf("В результате умножения вектор-столбец имеет размер %d x 1.\n",
            init_matrix.rows);
        printf("В какой форме вывести результат?\n1. В обычной.\n2. В "
            "разреженном строчном формате.\nВведите номер: ");

        if (fscanf(input_file, "%hd", &output_format) != 1)
        {
            printf("Ошибка: некорректно введен номер формы вывода "
                "результата.\n");
            m_free(&init_matrix);
            m_free(&init_vector);
            m_free(&res_vector);
            fclose(input_file);
            return EXIT_FAILURE;
        }

        printf("Результат:\n");
        if (output_format == 1)
            m_print(&res_vector);
        else if (output_format == 2)
        {
            sparse_matrix_t sparse_res = {.non_zero = 0};

            sm_allocate(&sparse_res, &res_vector);
            sm_fill(&sparse_res, &res_vector);
            sm_print(&sparse_res, res_vector.rows);
            sm_free(&sparse_res);
        }
        else
        {
            printf("Ошибка: формат вывода должен быть числом от 1 до 2.\n");
            m_free(&init_matrix);
            m_free(&init_vector);
            m_free(&res_vector);
            fclose(input_file);
            return EXIT_FAILURE;
        }

        printf("Время умножения: %" PRId64 " мкс.\n", seconds);
    }
    else
    {
        printf("Ошибка: алгоритм умножения должен быть числом от 1 до 2.\n");
        m_free(&init_matrix);
        m_free(&init_vector);
        m_free(&res_vector);
        fclose(input_file);
        return EXIT_FAILURE;
    }

    m_free(&init_matrix);
    m_free(&init_vector);
    m_free(&res_vector);
    fclose(input_file);

    return EXIT_SUCCESS;
}
