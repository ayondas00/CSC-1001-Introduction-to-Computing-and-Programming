
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000
#define LINEAR_RUNS 10
#define BINARY_RUNS 100000

int linear_search(int numbers[], int target, int *checks)
{
    *checks = 0;

    for (int i = 0; i < SIZE; i++)
    {
        (*checks)++;

        if (numbers[i] == target)
        {
            return i;
        }
    }

    return -1;
}

int binary_search(int numbers[], int target, int *checks)
{
    int left = 0;
    int right = SIZE - 1;
    *checks = 0;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;
        (*checks)++;

        if (numbers[middle] == target)
        {
            return middle;
        }
        else if (numbers[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return -1;
}

int main(void)
{
    int *numbers = malloc(SIZE * sizeof(int));

    if (numbers == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Create a sorted array: 0, 1, 2, 3, ...
    for (int i = 0; i < SIZE; i++)
    {
        numbers[i] = i;
    }

    int target = SIZE - 1;
    int checks;
    volatile int result;

    printf("Searching for: %i\n", target);
    printf("Array size: %i\n\n", SIZE);

    // Linear search benchmark
    clock_t start = clock();

    for (int i = 0; i < LINEAR_RUNS; i++)
    {
        result = linear_search(numbers, target, &checks);
    }

    clock_t end = clock();

    double linear_time =
        (double) (end - start) / CLOCKS_PER_SEC / LINEAR_RUNS;

    printf("LINEAR SEARCH\n");
    printf("Result: %s\n", result != -1 ? "Found" : "Not found");
    printf("Comparisons per search: %i\n", checks);
    printf("Average time: %.8f seconds\n\n", linear_time);

    // Binary search benchmark
    start = clock();

    for (int i = 0; i < BINARY_RUNS; i++)
    {
        result = binary_search(numbers, target, &checks);
    }

    end = clock();

    double binary_time = (double) (end - start) / CLOCKS_PER_SEC / BINARY_RUNS;

    printf("BINARY SEARCH\n");
    printf("Result: %s\n", result != -1 ? "Found" : "Not found");
    printf("Comparisons per search: %i\n", checks);
    printf("Average time: %.8f seconds\n\n", binary_time);

    printf("Linear search average: %.8f seconds\n", linear_time);
    printf("Binary search average: %.8f seconds\n", binary_time);

    if (binary_time > 0)
    {
        printf("Binary search is approximately %.2f times faster.\n",
               linear_time / binary_time);
    }

    free(numbers);
}
