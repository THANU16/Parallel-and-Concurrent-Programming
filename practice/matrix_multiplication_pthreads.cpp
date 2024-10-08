#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Define the global variables
int **matrix_a = NULL;
int *matrix_b = NULL;
long *result = NULL;
int num_of_calculations = 0;
int num_of_threads = 0;

void matrix_multiply_pthreads();

void *matrix_multiply(void *rank);

int main()
{
    printf("Starting the 2D array program\n");
    printf("Enter the number of threads: ");
    scanf("%d", &num_of_threads);

    // Define the 2D array
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

    // Define the 1D array
    int b[8] = {7893, 2568, 9874, 1548, 4598, 7895, 1236, 7895};

    // Assign the 2D array and 1D array to the global variables
    matrix_a = a;
    matrix_b = b;

    // Call the function to multiply the 2D array with the 1D array
    // matrix_multiply_pthreads();
    printf("Number of threads: %d\n", num_of_threads);
    // Create the threads
    pthread_t *thread_handles = (pthread_t *)malloc(num_of_threads * sizeof(pthread_t));

    for (int i = 0; i < num_of_threads; i++)
    {
        // Pass the thread index as a pointer-compatible type using intptr_t
        pthread_create(&thread_handles[i], NULL, matrix_multiply, (void *)(intptr_t)i);
    }

    // Wait for all threads to complete
    for (int i = 0; i < num_of_threads; i++)
    {
        pthread_join(thread_handles[i], NULL);
    }

    for (int i = 0; i < sizeof(result); i++)
    {
        printf("Result: %d\n", result[i]);
    }

    printf("Number of calculations: %d\n", num_of_calculations);

    // Free allocated memory
    free(a);

    return 0;
}

void matrix_multiply_pthreads()
{
    printf("Number of threads: %d\n", num_of_threads);
    // Create the threads
    pthread_t *thread_handles = (pthread_t *)malloc(num_of_threads * sizeof(pthread_t));

    for (int i = 0; i < num_of_threads; i++)
    {
        // Pass the thread index as a pointer-compatible type using intptr_t
        pthread_create(&thread_handles[i], NULL, matrix_multiply, (void *)(intptr_t)i);
    }

    // Wait for all threads to complete
    for (int i = 0; i < num_of_threads; i++)
    {
        pthread_join(thread_handles[i], NULL);
    }
}

void *matrix_multiply(void *rank)
{
    // Get the thread index
    int number_of_calculations_by_thread = 0;
    int my_rank = (intptr_t)rank;
    int rows_per_thread = sizeof(matrix_a) / num_of_threads;
    int first_row = my_rank * rows_per_thread;
    int last_row = (my_rank + 1) * rows_per_thread - 1;

    // Multiply the 2D array with the 1D array
    for (int i = first_row; i <= last_row; i++)
    {
        for (int j = 0; j < sizeof(matrix_b); j++)
        {
            result[i] += matrix_a[i][j] * matrix_b[j];
            // num_of_calculations += 2;
            number_of_calculations_by_thread += 2;
        }
    }

    printf("Thread %d: Number of calculations: %d\n", my_rank, number_of_calculations_by_thread);
}
