#include <stdio.h>
#include <stdlib.h>

void permute(int *numbers, int start, int end, int *permutations)
{
    if (start == end)
    {
        // print the permutation
        for (int i = 0; i <= end; i++)
        {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            // swap the current element with the first element
            int temp = numbers[start];
            numbers[start] = numbers[i];
            numbers[i] = temp;

            // recurse on the sublist with the current element at the front
            permute(numbers, start + 1, end);

            // restore the original order
            temp = numbers[start];
            numbers[start] = numbers[i];
            numbers[i] = temp;
        }
    }
}

int main()
{
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // read the numbers
    int *numbers = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        numbers[i] = i + 1;
    }

    // compute and print all permutations
    permute(numbers, 0, n - 1);

    free(numbers);
    return 0;
}
