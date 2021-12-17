#ifndef _GRAPH_T_
#define _GRAPH_T_

#define INFINITY 10000

#define ERR_MEMORY_ALLOCATION 1

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
int m_scan(matrix_t *matrix, size_t vertices);

int draw_graph(char *filename, matrix_t *matrix, int option);
int g_get_vertices(int *vertices);
int g_is_orientated(int *is_orientated);
int g_get_vertex(int *vertex, size_t vertices);

#endif // _GRAPH_T_
