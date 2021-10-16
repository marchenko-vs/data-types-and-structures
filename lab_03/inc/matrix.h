#ifndef _MATRIX_H_
#define _MATRIX_H_

#define DATA_TYPE_ERROR 2

typedef struct
{
    double **elements;
    int rows;
    int columns;
} matrix_t;

void m_free(matrix_t *matrix);
double **m_allocate(matrix_t *matrix);
int m_fill(matrix_t *matrix);
void m_multiply(matrix_t *matrix, matrix_t *vector, matrix_t *result);
void m_print(matrix_t *matrix);

#endif // _MATRIX_H_
