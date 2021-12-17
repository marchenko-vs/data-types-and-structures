#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define rdtscll(val) __asm__ __volatile__("rdtsc" :"=A"(val))

int main(void)
{
    setbuf(stdout, NULL);

    int vertices;

    if (g_get_vertices(&vertices) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    matrix_t adjacency_matrix = { NULL, vertices, vertices };
    m_allocate(&adjacency_matrix);

    int temp, begin_index, minindex, min, max_distance;
    int rc = EXIT_SUCCESS;

    m_constant_fill(&adjacency_matrix, 0);
    rc = m_scan(&adjacency_matrix, vertices);

    if (rc == EXIT_FAILURE)
    {
        m_free(&adjacency_matrix);
        return rc;
    }

    int is_orientated;

    rc = g_is_orientated(&is_orientated);

    if (rc == EXIT_FAILURE)
    {
        m_free(&adjacency_matrix);
        return rc;
    }

    if (is_orientated == 0)
        m_mirror(&adjacency_matrix);

    draw_graph("out/graph.gv", &adjacency_matrix, is_orientated);

    rc = g_get_vertex(&temp, vertices);

    if (rc != EXIT_SUCCESS)
    {
        m_free(&adjacency_matrix);
        return rc;
    }

    begin_index = temp - 1;

    printf("Enter maximum distance:\n");

    if (scanf("%d", &temp) != 1)
    {
        printf("Error: incorrect data type.\n");
        rc = EXIT_FAILURE;
    }

    if (rc == EXIT_FAILURE)
    {
        m_free(&adjacency_matrix);
        return rc;
    }

    if (temp < 0)
    {
        printf("Error: distance must be non-negative.\n");
        rc = EXIT_FAILURE;
    }

    if (rc == EXIT_FAILURE)
    {
        m_free(&adjacency_matrix);
        return rc;
    }

    max_distance = temp;

    int *minimum_distance = calloc(vertices, sizeof(int));
    int *visited_peaks = calloc(vertices, sizeof(int));

    for (size_t i = 0; i < vertices; i++)
    {
        minimum_distance[i] = INFINITY;
        visited_peaks[i] = 1;
    }

    minimum_distance[begin_index] = 0;
    unsigned long long time_start, time_end;
    size_t memory;

    memory = sizeof(matrix_t) + sizeof(minimum_distance) + 
        sizeof(visited_peaks) + vertices * vertices * sizeof(int) +
        vertices * sizeof(int *);

    rdtscll(time_start);

    do
    {
        minindex = INFINITY;
        min = INFINITY;

        for (size_t i = 0; i < vertices; i++)
        {
            if ((visited_peaks[i] == 1) && (minimum_distance[i] < min))
            {
                min = minimum_distance[i];
                minindex = i;
            }
        }

        if (minindex != INFINITY)
        {
            for (size_t i = 0; i < vertices; i++)
            {
                if (adjacency_matrix.elements[minindex][i] > 0)
                {
                    temp = min + adjacency_matrix.elements[minindex][i];
                    if (temp < minimum_distance[i])
                    {
                        minimum_distance[i] = temp;
                    }
                }   
            }

            visited_peaks[minindex] = 0;
        }
    }
    while (minindex < INFINITY);

    rdtscll(time_end);
    printf("Algorithm was working for %llu ticks.\n",
        time_end - time_start);
    printf("Algorithm used %llu bytes of memory.\n", memory);

    size_t counter = 0;

    for (size_t i = 1; i <= vertices; i++)
        if (i - 1 != begin_index && minimum_distance[i - 1] <= max_distance)
            counter++;

    if (counter == 0)
    {
        printf("There are no reachable vertices.\n");

        m_free(&adjacency_matrix);
        free(minimum_distance);
        free(visited_peaks);

        system("bash draw_graph.sh");

        return rc;
    }

    printf("Next vertices are reachable from vertex %d shorter distance %d:\n",
        begin_index + 1, max_distance);

    for (size_t i = 1; i <= vertices; i++)
        if (i - 1 != begin_index && minimum_distance[i - 1] <= max_distance)
            printf("%llu ", i);

    int *ver = calloc(vertices, sizeof(int));

    for (size_t i = 1; i <= vertices; i++)
    {
        if (i - 1 == begin_index || minimum_distance[i - 1] > max_distance)
            continue;

        int end = i - 1;
        ver[0] = end + 1;
        int k = 1;
        int weight = minimum_distance[end];

        while (end != begin_index)
        {
            for (size_t i = 0; i < vertices; i++)
                if (adjacency_matrix.elements[i][end] != 0)
                {
                    int temp = weight - adjacency_matrix.elements[i][end];

                    if (temp == minimum_distance[i])
                    {
                        weight = temp;
                        end = i;
                        ver[k] = i + 1;
                        k++;
                    }
                }
        }

        printf("\nThe shortest way to vertex %llu:\n", i);
        char filename[15];
        snprintf(filename, 15, "out/way_%llu.gv", i);

        FILE *f = fopen(filename, "w");

        if (f == NULL)
            return EXIT_FAILURE;

        if (is_orientated == 0)
        {
            fprintf(f, "graph way_to_%llu {\n", i);

            for (size_t i = 0; i < k - 1; i++)
                fprintf(f, "  %d -- %d [color=red, label=%d];\n", 
                    ver[k - i - 1], ver[k - i - 2], 
                    adjacency_matrix.elements[ver[k - i - 1] - 1][ver[k - i - 2] - 1]);

            for (size_t i = 0; i < adjacency_matrix.rows; i++)
                for (size_t j = 0; j < adjacency_matrix.columns; j++)
                    if (adjacency_matrix.elements[i][j] != 0 && j >= i)
                    {
                        int flag = 0;

                        for (size_t m = 0; m < k - 1; m++)
                        {
                            flag = 0;

                            if ((ver[k - m - 1] == i + 1 && ver[k - m - 2] == j + 1) ||
                                (ver[k - m - 1] == j + 1 && ver[k - m - 2] == i + 1))
                            {
                                flag = 1;
                                break;
                            }
                        }

                        if (flag == 0) 
                            fprintf(f, "  %llu -- %llu [label=%d];\n", 
                                i + 1, j + 1, adjacency_matrix.elements[i][j]);
                    }      
        }
        else
        {
            fprintf(f, "digraph way_to_%llu {\n", i);

            for (size_t i = 0; i < k - 1; i++)
                fprintf(f, "  %d -> %d [color=red, label=%d];\n", 
                    ver[k - i - 1], ver[k - i - 2], 
                    adjacency_matrix.elements[ver[k - i - 1] - 1][ver[k - i - 2] - 1]);

            for (size_t i = 0; i < adjacency_matrix.rows; i++)
                for (size_t j = 0; j < adjacency_matrix.columns; j++)
                    if (adjacency_matrix.elements[i][j] != 0)
                    {
                        int flag = 0;

                        for (size_t m = 0; m < k - 1; m++)
                        {
                            flag = 0;

                            if ((ver[k - m - 1] == i + 1 && ver[k - m - 2] == j + 1) ||
                                (ver[k - m - 1] == j + 1 && ver[k - m - 2] == i + 1))
                            {
                                flag = 1;
                                break;
                            }
                        }

                        if (flag == 0) 
                            fprintf(f, "  %llu -> %llu [label=%d];\n", 
                                i + 1, j + 1, adjacency_matrix.elements[i][j]);
                    }      
        }
        
        fprintf(f, "}");

        fclose(f);

        for (size_t i = 0; i < k; i++)
        {
            printf("%d", ver[k - i - 1]);

            if (i < k - 1)
                printf(" -> ");
        }
    }

    system("bash draw_graph.sh");

    m_free(&adjacency_matrix);
    free(minimum_distance);
    free(visited_peaks);
    free(ver);

    return rc;
}
