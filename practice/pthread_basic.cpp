#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // Required for intptr_t
#include <sys/types.h>
#include <unistd.h>

// Let us create a global variable to change it in threads
int g = 0;

// The function to be executed by all threads
void *increment_fun(void *rank)
{
    // Convert the rank from void* to intptr_t to avoid precision loss
    intptr_t myRank = (intptr_t)rank;

    // Let us create a static variable to observe its changes
    static int s = 0;

    // Let us create a local variable to observe its changes
    int l = 0;

    // Change local, static and global variables
    s++;
    g++;
    l++;

    // Print the argument, static and global variables
    printf("Thread ID: %ld, local: %d, Static: %d, Global: %d\n", myRank, l, s, g);

    return NULL;
}

int main()
{
    printf("Enter the number of threads: ");
    int thread_count = 0;
    scanf("%d", &thread_count);
    pthread_t *thread_handles = (pthread_t *)malloc(thread_count * sizeof(pthread_t));

    // Create the threads
    for (int i = 0; i < thread_count; i++)
    {
        // Pass the thread index as a pointer-compatible type using intptr_t
        pthread_create(&thread_handles[i], NULL, increment_fun, (void *)(intptr_t)i);
    }

    // Wait for all threads to complete
    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(thread_handles[i], NULL);
    }

    printf("Final Global: %d\n", g);

    // Free allocated memory
    free(thread_handles);

    return 0;
}
