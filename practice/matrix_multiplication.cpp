#include <stdio.h>
#include <stdlib.h>

// Define the global variables
int **matrix_a = NULL;
int *matrix_b = NULL;
int num_of_calculations = 0;

long *matrix_multiply();

int main()
{
    printf("Starting the 2D array program\n");
    int rows = 8;
    int **a = (int **)malloc(rows * sizeof(int *));

    // Define the rows values of the 2D array
    int a_0[8] = {156, 287, 589, 899, 914, 478, 989, 489};
    int a_1[8] = {894, 252, 898, 524, 369, 154, 456, 789};
    int a_2[8] = {123, 456, 789, 987, 654, 321, 741, 852};
    int a_3[8] = {741, 852, 963, 147, 258, 369, 456, 789};
    int a_4[8] = {841, 422, 563, 247, 358, 769, 455, 785};
    int a_5[8] = {499, 222, 333, 444, 555, 666, 777, 888};
    int a_6[8] = {756, 287, 589, 899, 914, 478, 989, 489};
    int a_7[8] = {276, 287, 589, 899, 914, 478, 989, 489};

    // Assign the rows to the 2D array
    a[0] = a_0;
    a[1] = a_1;
    a[2] = a_2;
    a[3] = a_3;
    a[4] = a_4;
    a[5] = a_5;
    a[6] = a_6;
    a[7] = a_7;

    int b[8] = {7893, 2568, 9874, 1548, 4598, 7895, 1236, 7895};

    // Assign the 2D array and 1D array to the global variables
    matrix_a = a;
    matrix_b = b;

    // Call the function to multiply the 2D array with the 1D array
    long *result = matrix_multiply();

    for (int i = 0; i < sizeof(result); i++)
    {
        printf("Result: %d\n", result[i]);
    }

    printf("Number of calculations: %d\n", num_of_calculations);

    // Free allocated memory
    free(a);

    return 0;
}

// Define the function to multiply the 2D array with the 1D array
long *matrix_multiply()
{
    long *result = (long *)malloc(sizeof(matrix_b) * sizeof(long));

    for (int i = 0; i < sizeof(matrix_a); i++)
    {
        for (int j = 0; j < sizeof(matrix_b); j++)
        {
            int temp = matrix_a[i][j] * matrix_b[j];
            printf("%d * %d\n", matrix_a[i][j], matrix_b[j]);
            printf("%d + %d\n", result[i], temp);
            result[i] += temp;
            num_of_calculations += 2;
        }
    }
    return result;
}
