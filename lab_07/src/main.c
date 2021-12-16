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

    int *minimum_distance = calloc(vertices, sizeof(int));
    int *visited_peaks = calloc(vertices, sizeof(int));

    int temp, begin_index, minindex, min, max_distance;
    int tmp_i, tmp_j;

    m_constant_fill(&adjacency_matrix, 0);

    printf("Enter data in the following format:\nvertex_1 vertex_2 distance\n"
        "if you want to stop entering data, type : 0 0 0\n");

    while (1)
    {
        if (scanf("%d%d%d", &tmp_i, &tmp_j, &temp) != 3)
        {
            return EXIT_FAILURE;
        }

        if (tmp_i == 0 && tmp_j == 0 && temp == 0)
            break;

        if (tmp_i < 1 || tmp_j > vertices || temp < 0)
        {
            return EXIT_FAILURE;
        }

        adjacency_matrix.elements[tmp_i - 1][tmp_j - 1] = temp;
    }

    printf("Is your graph orientated?\n0 - No\n1 - Yes\n");

    if (scanf("%d", &temp) != 1)
    {
        return EXIT_FAILURE;
    }

    if (temp < 0 || temp > 1)
    {
        return EXIT_FAILURE;
    }

    if (temp == 0)
        m_mirror(&adjacency_matrix);

    printf("[DBG] Adjacency matrix:\n");

    for (size_t i = 0; i < vertices; i++)
    {
        for (size_t j = 0; j < vertices; j++)
            printf("%5d ", adjacency_matrix.elements[i][j]);

        printf("\n");
    }

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
        return EXIT_FAILURE;
    }

    if (temp < 0)
    {
        printf("Error: distance must be non-negative.\n");
        return EXIT_FAILURE;
    }

    max_distance = temp;

    for (size_t i = 0; i < vertices; i++)
    {
        minimum_distance[i] = 10000;
        visited_peaks[i] = 1;
    }

    minimum_distance[begin_index] = 0;

    do
    {
        minindex = 10000;
        min = 10000;

        for (size_t i = 0; i < vertices; i++)
        {
            if ((visited_peaks[i] == 1) && (minimum_distance[i]<min))
            {
                min = minimum_distance[i];
                minindex = i;
            }
        }

        if (minindex != 10000)
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
    while (minindex < 10000);


    printf("\n[DBG] The shortest distances to verteces:\n");

    for (size_t i = 0; i < vertices; i++)
        printf("Peak %llu: %d\n", i + 1, minimum_distance[i]);

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

        for (size_t i = 0; i < k; i++)
        {
            printf("%d", ver[k - i - 1]);

            if (i < k - 1)
                printf(" -> ");
        }
    }

    m_free(&adjacency_matrix);
    free(minimum_distance);
    free(visited_peaks);
    free(ver);

    return EXIT_SUCCESS;
}
