//
// Created by Thanushanth on 10/7/2024.
//

#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

int sum_of_numbers (int *numbers);
int sum_of_numbers_using_pthreads(int *numbers);

int main(){
    int numbers[20] = {2324,546, 686, 9867, 67865, 566, 78967, 5435,
                       54345, 6529, 4545, 265454, 4545, 4545, 125,
                       45848, 5454, 54718, 572, 7894};

    int sum_of_numbers_without_parallel = sum_of_numbers(numbers);
    printf("%d/n", sum_of_numbers_without_parallel);


    int sum_of_numbers_with_parallel = sum_of_numbers_using_pthreads(numbers);
    printf("%d/n", sum_of_numbers_with_parallel);

    return 0;

}


int sum_of_numbers(int *numbers) {
    int sum = 0;
    for (int i = 0; i < sizeof(numbers); ++i) {
        sum += numbers[i];
    }
    return sum;
}

int sum_of_numbers_using_pthreads(int *numbers) {
    int sum = 0;
    int thread_count = 4;
    long thread;
    pthread_t* thread_handles;
    thread_handles = malloc(thread_count* sizeof(pthread_t));
    int step_size = sizeof(numbers) / thread_count

    for (thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, sum_of_numbers, numbers[thread*step_size : (thread+1)step_size ]);
    }

    int result[thread_count];
    for (thread = 0; thread < thread_count; thread++){
        pthread_join(&thread_handles[thread], &result[thread]);
    }

    for (int i = 0; i < sizeof(result); i++){
        sum+= result[i];
    }

//
//    pthread_t thread1, thread2;
//    pthread_create(&thread1, NULL, sum_of_numbers, numbers);
//    pthread_create(&thread2, NULL, sum_of_numbers, numbers + 10);
//
//    int *result1, *result2;
//    pthread_join(thread1, (void **)&result1);
//    pthread_join(thread2, (void **)&result2);
//
//    sum = *result1 + *result2;
    return sum;
}


