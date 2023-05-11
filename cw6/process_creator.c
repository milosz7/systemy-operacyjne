#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

#include "source/open_sem.h"
#include "source/wait_sem.h"
#include "source/getval_sem.h"
#include "source/post_sem.h"
#include "source/close_sem.h"

#define SEMAPHORE_NAME "/semaphore"
#define SLEEP_IN_SECS 3
#define READ_CHUNK 3
#define OPEN_MODE 0644

int random_int(int max_sleep_in_s);

ssize_t open_file(char *name, int oflags, mode_t mode);

int main(int argc, char *argv[])
{
    sem_t *sem = open_sem(SEMAPHORE_NAME, O_RDWR);
    int process_sections_amount = (int)strtod(argv[1], NULL) | 2;
    char *counter_filename = argv[2];
    unsigned int pid = getpid();
    char counter_buffer[5];

    for (int i = 0; i < process_sections_amount; i++)
    {
        printf("-----\n");
        printf("Private section of: %d\n", pid);
        printf("Semaphore value: %d\n", getval_sem(sem));
        wait_sem(sem);

        sleep(random_int(SLEEP_IN_SECS));

        printf("-----\n");
        printf("Critical section of: %d\n", pid);
        printf("Semaphore value: %d\n", getval_sem(sem));

        ssize_t counter_descriptor = open_file("counter.txt", O_RDONLY, OPEN_MODE);
        if (read(counter_descriptor, counter_buffer, READ_CHUNK) == -1)
        {
            perror("Read function call error");
            _exit(EXIT_FAILURE);
        };
        close(counter_descriptor);

        int current_value = (int)strtod(counter_buffer, NULL);
        current_value += 1;
        int current_length = (int)floor(log10(current_value)) + 2;
        char write_buffer[current_length];
        sprintf(write_buffer, "%d", current_value);

        counter_descriptor = open_file(counter_filename, O_WRONLY | O_TRUNC, OPEN_MODE);
        if (write(counter_descriptor, write_buffer, current_length) == -1)
        {
            perror("Write function call error");
            _exit(EXIT_FAILURE);
        }
        close(counter_descriptor);
        post_sem(sem);

        printf("-----\n");
        printf("Post-critical section of: %d\n", pid);
        printf("Semaphore value: %d\n", getval_sem(sem));
    }
    close_sem(sem);
    _exit(EXIT_SUCCESS);
}

int random_int(int max_sleep_in_s)
{
    srand(time(NULL));
    return (int)(((double)rand() / (double)RAND_MAX) * max_sleep_in_s) + 1;
}

ssize_t open_file(char *name, int oflags, mode_t mode)
{
    ssize_t descriptor = open(name, oflags, mode);
    if (descriptor == -1)
    {
        perror("Open function call error");
        _exit(EXIT_FAILURE);
    }
    return descriptor;
}
