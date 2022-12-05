#include <stdio.h>

// Team 11
// Team Details
// Manan Gupta - 2021A7PS2091H
// Kumarasamy Chelliah - 2021A7PS0096H

int main(int arg1, char *fileName[])
{
  if (arg1 != 2)
  {
    printf("Please enter correct file name");
    return 0;
  }

  FILE *file_name = fopen(fileName[1], "r");

  FILE *output_fptr = fopen("out.txt", "w");

  if (output_fptr == NULL)
  {
    printf("Error!");
    fclose(file_name);
    fclose(output_fptr);
    return 1;
  }

  if (file_name == NULL)
  {
    printf("Error!");
    fclose(file_name);
    fclose(output_fptr);
    return 1;
  }

  int nodes;
  int edges;
  fscanf(file_name, "%d\n", &nodes);
  fscanf(file_name, "%d\n", &edges);

  if (nodes == 0)
  {
    printf("Graph doesn't exist");
    fprintf(output_fptr, "%s", "Graph doesn't exist!");
    return 0;
  }
  if (edges == 0)
  {
    printf("All vertices are isolated: ");
  }

  // Making a 2-D Array for Adjaceny Matrix
  int adjacency_matrix[nodes][nodes];
  for (int i = 0; i < nodes; i++)
  {
    for (int j = 0; j < nodes; j++)
    {
      adjacency_matrix[i][j] = 0;
    }
  }

  // Initialising the matrix from the input file
  for (int i = 0; i < edges; i++)
  {
    int a, b;
    fscanf(file_name, "%d", &a);
    fscanf(file_name, "%d\n", &b);
    adjacency_matrix[a - 1][b - 1] = 1;
    adjacency_matrix[b - 1][a - 1] = 1;
  }

  // Initialising the output array
  int degree[nodes];
  for (int i = 0; i < nodes; i++)
  {
    degree[i] = 0;
  }

  // Calculating the degree of each vertex
  for (int i = 0; i < nodes; i++)
  {
    for (int j = 0; j < nodes; j++)
    {
      if (adjacency_matrix[i][j] == 1)
      {
        degree[i]++;
      }
      else
      {
        continue;
      }
    }
  }

  // Making the array in non-increasing order
  for (int i = 0; i < nodes; i++)
  {
    for (int j = i + 1; j < nodes; j++)
    {

      if (degree[i] < degree[j])
      {
        int temp = degree[i];
        degree[i] = degree[j];
        degree[j] = temp;
      }
    }
  }

  fprintf(output_fptr, "%s", "Degree of the vertices in non-increasing order: ");

  for (int i = 0; i < nodes; i++)
  {
    printf("%d ", degree[i]);
    fprintf(output_fptr, "%d ", degree[i]);
  }

  fclose(file_name);
  fclose(output_fptr);

  return 0;
}
