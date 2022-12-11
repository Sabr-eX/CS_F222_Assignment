#include <stdio.h>

// Team 11
// Team Details
// Manan Gupta - 2021A7PS2091H
// Kumarasamy Chelliah - 2021A7PS0096H

// Our Approach -
// We are creating an array equal

// Swap function 
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


int Adjacency_Matrix_Permute_compare(int *arr, int first, int last, int length, int (*matrix1)[length], int (*matrix2)[length], int *result)
{
    int temp;
    if (first == last)
    {   
        int equality = 1;
        // to compare the two adjacency matrix
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < length; j++)
            {
                if (matrix1[arr[i]][arr[j]] != matrix2[i][j])
                {
                    equality = 0;
                }
            }
        }
        if (equality == 1)
        {
            printf("Isomorphic");
            printf("\n");
    
            for (int i = 0; i < length; i++)
            {
                printf("%d %d\n", arr[i] + 1 ,i+1);
            }
            *result =1;
            return 0;
        }    
    }
    else{
        for(temp=first ; temp< last ;temp++)
        {
            swap((arr + first),(arr+temp));
            if(Adjacency_Matrix_Permute_compare(arr,first+1,last,length,matrix1,matrix2,result)== 0)
            {
                return 0;
            }
            swap((arr+first),(arr+temp));
        }
}
}


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
    

    int result = 0;
    int permuted_array[nodes_1 +1];

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
    // Initialsing permuted array
    for (int i = 0; i < nodes_1; i++)
    {
        permuted_array[i] = i;
    }

    // Calling Recursive function
    Adjacency_Matrix_Permute_compare(permuted_array, 0, nodes_1, nodes_2, adjacency_matrix_1, adjacency_matrix_2, &result);
    if(result == 0)
    {
        printf("Not Isomorphic, no bijection found.");
    }

}