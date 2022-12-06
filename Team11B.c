#include <stdio.h>

// Team 11
// Team Details
// Manan Gupta - 2021A7PS2091H
// Kumarasamy Chelliah - 2021A7PS0096H

int main(int arg1, char *fileName[])
{
    if (arg1 != 3)
    {
        printf("Please enter two file names");
        return 0;
    }

    FILE *file_name_1 = fopen(fileName[1], "r");
    FILE *file_name_2 = fopen(fileName[2], "r");

    if (file_name_1 == NULL || file_name_2 == NULL)
    {
        printf("Error!");
        fclose(file_name_1);
        fclose(file_name_2);
        return 1;
    }

    int nodes_1;
    int edges_1;

    fscanf(file_name_1, "%d\n", &nodes_1);
    fscanf(file_name_1, "%d\n", &edges_1);

    if (nodes_1 == 0)
    {
        printf("Graph-1 doesn't exist");

        return 0;
    }
    if (edges_1 == 0)
    {
        printf("All vertices in graph-1 are isolated: ");
    }

    int nodes_2;
    int edges_2;

    fscanf(file_name_2, "%d\n", &nodes_2);
    fscanf(file_name_2, "%d\n", &edges_2);

    if (nodes_2 == 0)
    {
        printf("Graph-2 doesn't exist");

        return 0;
    }
    if (edges_2 == 0)
    {
        printf("All vertices in graph-2 are isolated: ");
    }

    // Checking the equality of the nodes and edges of both graphs
    if ((nodes_1 != nodes_2) || (edges_1 != edges_2))
    {
        printf("Not Isomorphic, no bijection found.");
        fclose(file_name_1);
        fclose(file_name_2);
        return 0;
    }

    // Making a 2-D Array for Adjaceny Matrix for graph-1
    int adjacency_matrix_1[nodes_1][nodes_1];
    for (int i = 0; i < nodes_1; i++)
    {
        for (int j = 0; j < nodes_1; j++)
        {
            adjacency_matrix_1[i][j] = 0;
        }
    }

    // Making a 2-D Array for Adjaceny Matrix for graph-2
    int adjacency_matrix_2[nodes_2][nodes_2];
    for (int i = 0; i < nodes_2; i++)
    {
        for (int j = 0; j < nodes_2; j++)
        {
            adjacency_matrix_2[i][j] = 0;
        }
    }

    // Initialising the adjacency matrix from input file 1
    for (int i = 0; i < edges_1; i++)
    {
        int a, b;
        fscanf(file_name_1, "%d", &a);
        fscanf(file_name_1, "%d\n", &b);
        adjacency_matrix_1[a - 1][b - 1] = 1;
        adjacency_matrix_1[b - 1][a - 1] = 1;
    }

    // Initialising the adjacency matrix from input file 2
    for (int i = 0; i < edges_2; i++)
    {
        int a, b;
        fscanf(file_name_2, "%d", &a);
        fscanf(file_name_2, "%d\n", &b);
        adjacency_matrix_2[a - 1][b - 1] = 1;
        adjacency_matrix_2[b - 1][a - 1] = 1;
    }

    // Initialising the output array and unsorted array for the both the graphs
    int degree_1[nodes_1];
    int degree_2[nodes_2];
    int unsorted_degree_1[nodes_1];
    int unsorted_degree_2[nodes_2];
    for (int i = 0; i < nodes_1; i++)
    {
        degree_1[i] = 0;
        degree_2[i] = 0;
        unsorted_degree_1[i] = 0;
        unsorted_degree_2[i] = 0;
    }

    // Calculating the degree of each vertex in the first graph
    for (int i = 0; i < nodes_1; i++)
    {
        for (int j = 0; j < nodes_1; j++)
        {
            if (adjacency_matrix_1[i][j] == 1)
            {
                degree_1[i]++;
                unsorted_degree_1[i]++;
            }
            else
            {
                continue;
            }
        }
    }

    // Calculating the degree of each vertex in the second graph
    for (int i = 0; i < nodes_2; i++)
    {
        for (int j = 0; j < nodes_2; j++)
        {
            if (adjacency_matrix_2[i][j] == 1)
            {
                degree_2[i]++;
                unsorted_degree_2[i]++;
            }
            else
            {
                continue;
            }
        }
    }

    // Making the degree_1 in non-increasing order
    for (int i = 0; i < nodes_1 - 1; i++)
    {
        for (int j = i + 1; j < nodes_1; j++)
        {

            if (degree_1[i] < degree_1[j])
            {
                int temp = degree_1[i];
                degree_1[i] = degree_1[j];
                degree_1[j] = temp;
            }
        }
    }

    // Making the degree_2 in non-increasing order
    for (int i = 0; i < nodes_2 - 1; i++)
    {
        for (int j = i + 1; j < nodes_2; j++)
        {

            if (degree_2[i] < degree_2[j])
            {
                int temp = degree_2[i];
                degree_2[i] = degree_2[j];
                degree_2[j] = temp;
            }
        }
    }

    // Printing the degree sequence of graph-1 in standard output
    for (int i = 0; i < nodes_1; i++)
    {
        printf("%d ", degree_1[i]);
    }
    printf("\n");

    // Printing the degree sequence of graph-2 in standard output
    for (int i = 0; i < nodes_2; i++)
    {
        printf("%d ", degree_2[i]);
    }
    printf("\n");

    // Comparing the degree sequence of the graphs
    for (int i = 0; i < nodes_1; i++)
    {
        if (degree_1[i] == degree_2[i])
        {
            continue;
        }
        else
        {
            printf("Not Isomorphic, no bijection found.");
            
            fclose(file_name_1);
            fclose(file_name_2);
            return 0;
        }
    }

    int n = -1;
    for (int i = 0; i < nodes_1; i++)
    {
        int k = 0;
        for (int j = 0; j < nodes_2; j++)
        {
            if (j + i < nodes_2)
            {
                if (unsorted_degree_1[j] == unsorted_degree_2[j + i])
                {
                    k++;
                    continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if (unsorted_degree_1[j] == unsorted_degree_2[j + i - nodes_2 + 1])
                {
                    k++;
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
        
        if (k == nodes_1)
        {
            printf("Isomorphic");
            n = i;
            break;
        }
        else
        {
            continue;
        }
    }

    if (n == -1)
    {
        printf("Not Isomorphic, no bijection found.");
        
        fclose(file_name_1);
        fclose(file_name_2);
        return 0;
    }
    else
    {
        for (int i = 0; i < nodes_1; i++)
        {
            if (i + n < nodes_1)
            {
                printf("\n%d %d", i, i + n);
            }
            else
            {
                printf("\n%d %d", i, i + n - nodes_1 + 1);
            }
        }

        fclose(file_name_1);
        fclose(file_name_2);
    }

    return 0;
}
