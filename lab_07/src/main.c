#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

int main(void)
{
    setbuf(stdout, NULL);

    int vertices;

    printf("Enter number of vertices of the graph:\n");

    if (scanf("%d", &vertices) != 1)
    {
        printf("Error: incorrect data type.\n");
        return EXIT_FAILURE;
    }

    if (vertices < 1)
    {
        printf("Error: incorrect number of vertices.\n");
        return EXIT_FAILURE;
    }

    matrix_t adjacency_matrix = { NULL, vertices, vertices };
    m_allocate(&adjacency_matrix);

    int temp, begin_index, minindex, min, max_distance;
    int tmp_i, tmp_j;
    int rc = EXIT_SUCCESS;

    m_constant_fill(&adjacency_matrix, 0);

    printf("Enter data in the following format:\nvertex_1 vertex_2 distance\n"
        "If you want to stop entering data, type : 0 0 0\n");

    while (1)
    {
        if (scanf("%d%d%d", &tmp_i, &tmp_j, &temp) != 3)
        {
            printf("Error: incorrect data type.\n");
            rc = EXIT_FAILURE;
            break;
        }

        if (tmp_i == 0 && tmp_j == 0 && temp == 0)
            break;

        if (tmp_i < 1 || tmp_j > vertices || temp < 0)
        {
            printf("Error: input data is incorrect.\n");
            rc = EXIT_FAILURE;
            break;
        }

        adjacency_matrix.elements[tmp_i - 1][tmp_j - 1] = temp;
    }

    if (rc == EXIT_FAILURE)
    {
        m_free(&adjacency_matrix);
        return rc;
    }

    int is_orientated;

    printf("Is your graph orientated?\n0 - No\n1 - Yes\n");

    if (scanf("%d", &is_orientated) != 1)
    {
        printf("Error: incorrect data type.\n");
        rc = EXIT_FAILURE;
    }

    if (rc == EXIT_FAILURE)
    {
        m_free(&adjacency_matrix);
        return rc;
    }

    if (is_orientated < 0 || is_orientated > 1)
    {
        printf("Error: you should choose between 0 and 1.\n");
        rc = EXIT_FAILURE;
    }

    if (rc == EXIT_FAILURE)
    {
        m_free(&adjacency_matrix);
        return rc;
    }

    if (is_orientated == 0)
        m_mirror(&adjacency_matrix);

    // printf("[DBG] Adjacency matrix:\n");

    // for (size_t i = 0; i < vertices; i++)
    // {
    //     for (size_t j = 0; j < vertices; j++)
    //         printf("%5d ", adjacency_matrix.elements[i][j]);

    //     printf("\n");
    // }

    draw_graph("graph.gv", &adjacency_matrix, is_orientated);

    printf("Enter the starting vertex:\n");

    if (scanf("%d", &temp) != 1)
    {
        printf("Error: incorrect data type.\n");
        return EXIT_FAILURE;
    }

    if (temp < 1 || temp > vertices)
    {
        printf("Error: vertex %d does not exist.\n", temp);
        return EXIT_FAILURE;
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

    do
    {
        minindex = INFINITY;
        min = INFINITY;

        for (size_t i = 0; i < vertices; i++)
        {
            if ((visited_peaks[i] == 1) && (minimum_distance[i]<min))
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
        snprintf(filename, 15, "way_to_%llu.gv", i);

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
