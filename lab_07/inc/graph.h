#ifndef _GRAPH_T_
#define _GRAPH_T_

#define INFINITY 10000

typedef struct
{
    int **elements;
    int rows;
    int columns;
} matrix_t;

int m_allocate(matrix_t *matrix);
void m_free(matrix_t *matrix);
void m_constant_fill(matrix_t *matrix, int constant);
void m_mirror(matrix_t *matrix);
int draw_graph(char *filename, matrix_t *matrix, int option);

#endif // _GRAPH_T_
