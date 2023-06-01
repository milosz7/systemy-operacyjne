#define _REENTRANT
#include <stdlib.h>

#include "source/utils.h"

#define REQUIRED_ARGS_AMOUNT 3
#define RIGHT_X 0
#define LEFT_X 60
#define Y_MIDDLE 10
#define MAX_SLEEP_IN_SECS 3

int counter = 0;

void *thread_fun(void *args);

int main(int argc, char *argv[])
{
    if (argc != REQUIRED_ARGS_AMOUNT)
    {
        fprintf(stderr, "Wrong number of arguments provided!\n");
        exit(EXIT_FAILURE);
    }

    int threads_amount = input_to_int(argv[1]);
    int sections_amount = input_to_int(argv[2]);
    pthread_t threads[threads_amount];
    struct thread_args *args_arr[threads_amount];
    pthread_mutex_t mutex;
    init_default_mutex(&mutex);
    struct thread_args *args = (struct thread_args *)malloc(sizeof(struct thread_args));

    for (int i = 0; i < threads_amount; i++)
    {
        struct thread_args args1 = {
            .mutex_ptr = &mutex,
            .thread_id = i + 1,
            .sections_amount = sections_amount};
        pthread_t threadID;
        args_arr[i] = (struct thread_args *)malloc(sizeof(struct thread_args));

        args_arr[i]->mutex_ptr = &mutex;
        args_arr[i]->thread_id = i + 1;
        args_arr[i]->sections_amount = sections_amount;
        my_create_thread(&threadID, NULL, &thread_fun, (void *)args_arr[i]);
        threads[i] = threadID;
    }
    for (int i = 0; i < threads_amount; i++)
    {
        my_thread_join(threads[i], NULL);
        free(args_arr[i]);
    }

    destroy_mutex(&mutex);

    int expected_counter_amt = threads_amount * sections_amount;
    printf(COLOR_WHITE);
    printf("Final counter value: %d\n", counter);
    printf("Expected value: %d\n", expected_counter_amt);
    printf("%s\n", (counter == expected_counter_amt) ? "Counter value is correct!" : "Something went wrong.");
}

void *thread_fun(void *args)
{
    int thread_ID = ((struct thread_args *)args)->thread_id;
    pthread_mutex_t *mutex = ((struct thread_args *)args)->mutex_ptr;
    int sections_amount = ((struct thread_args *)args)->sections_amount;
    for (int i = 0; i < sections_amount; i++)
    {
        printf(COLOR_GREEN);
        gotoxy(LEFT_X, Y_MIDDLE + thread_ID);
        printf("Private section of thread with ID: %d Counter: %d\n", thread_ID, counter);
        lock_mutex(mutex);
        random_sleep(MAX_SLEEP_IN_SECS);
        printf(COLOR_RED);
        gotoxy(RIGHT_X, Y_MIDDLE + thread_ID);
        int private_counter = counter;
        private_counter++;
        printf("Critical section of thread with ID: %d Counter: %d\n", thread_ID, private_counter);
        random_sleep(MAX_SLEEP_IN_SECS);
        counter = private_counter;
        unlock_mutex(mutex);
        printf(COLOR_GREEN);
        gotoxy(LEFT_X, Y_MIDDLE + thread_ID);
        printf("Private section of thread with ID: %d Counter: %d\n", thread_ID, counter);
    }
    pthread_exit(NULL);
}
