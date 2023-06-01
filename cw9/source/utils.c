#include "utils.h"

#define SUCCESS_CODE 0

void print_error(int status_code)
{
    fprintf(stderr, "Error : %s", strerror(status_code));
    exit(EXIT_FAILURE);
}

int input_to_int(char *user_input)
{
    int output = (int)strtod(user_input, NULL);
    if (errno == ERANGE || errno == EINVAL)
    {
        perror("Strtod function call error");
        exit(EXIT_FAILURE);
    }
    return output;
}

void init_default_mutex(pthread_mutex_t *mutex)
{
    int return_code = pthread_mutex_init(mutex, NULL);
    if (return_code != SUCCESS_CODE)
    {
        print_error(return_code);
    }
}

void my_create_thread(pthread_t *threadID, const pthread_attr_t *attr, void *(*function)(void *), void *arg)
{
    int return_code = pthread_create(threadID, attr, function, arg);
    if (return_code != SUCCESS_CODE)
        print_error(return_code);
}

void my_thread_join(pthread_t threadID, void **status)
{
    int return_code = pthread_join(threadID, status);
    if (return_code != SUCCESS_CODE)
        print_error(return_code);
}

void lock_mutex(pthread_mutex_t *mutex)
{
    int return_code = pthread_mutex_lock(mutex);
    if (return_code != SUCCESS_CODE)
        print_error(return_code);
}

void unlock_mutex(pthread_mutex_t *mutex)
{
    int return_code = pthread_mutex_unlock(mutex);
    if (return_code != SUCCESS_CODE)
        print_error(return_code);
}

void destroy_mutex(pthread_mutex_t *mutex)
{
    int return_code = pthread_mutex_destroy(mutex);
    if (return_code != SUCCESS_CODE)
        print_error(return_code);
}

void gotoxy(unsigned int x, unsigned int y)
{
    printf("\033[%d;%dH\033[2K", y, x);
}

void random_sleep(unsigned int max_sleep_in_secs)
{
    srand(time(NULL));
    sleep((int)(((double)rand() / (double)RAND_MAX) * max_sleep_in_secs) + 1);
}
