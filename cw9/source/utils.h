#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifndef UTILS_H
#define UTILS_H
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_WHITE "\033[0;37m"

// Function to print an error if mutex return value is nonzero.
void print_error(int status_code);
// Function to convert a string to int with error handling.
int input_to_int(char *input);
// Function do create a mutex with default values with error handling.
void init_default_mutex(pthread_mutex_t *mutex);
// Function to create a thread with error handling.
void my_create_thread(pthread_t *threadID, const pthread_attr_t *attr, void *(*function)(void *), void *arg);
// Function to join threads with error handling.
void my_thread_join(pthread_t threadID, void **status);
// Function to lock a mutex with error handling.
void lock_mutex(pthread_mutex_t *mutex);
// Function to trylock a mutex with error handling.
// void trylock_mutex(pthread_mutex_t *mutex);
// Function to unlock a mutex with error handling.
void unlock_mutex(pthread_mutex_t *mutex);
// Function to destroy a mutex with error handling.
void destroy_mutex(pthread_mutex_t *mutex);
// Structure for passing aruments to thread function calls.
struct thread_args
{
    int thread_id;
    int sections_amount;
    pthread_mutex_t *mutex_ptr;
};
// Function to move the cursor to x and y coordinates;
void gotoxy(unsigned int x, unsigned int y);
// Function to make process sleep for random amount of time (max sleep time defined)
void random_sleep(unsigned int max_sleep_in_s);
#endif