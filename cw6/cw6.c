#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <math.h>

#include "source/create_sem.h"
#include "source/getval_sem.h"
#include "source/unlink_sem.h"
#include "source/post_sem.h"

#define REQUIRED_ARGS_AMOUNT 5
#define SEMAPHORE_NAME "/semaphore"
#define OPEN_MODE 0644
#define EXECUTABLE_PREFIX "./"
#define INITIAL_SEM_VALUE 0

void exit_cleanup();
ssize_t open_file(char *name, int oflags, mode_t mode);
void assert_value(int expected_value, char *data_file);

int main(int argc, char *argv[])
{

    if (argc < REQUIRED_ARGS_AMOUNT)
    {
        fprintf(stderr, "Wrong number of arguments provided!\n");
        exit(EXIT_FAILURE);
    }

    char *process_creator_filename = argv[1];
    char process_creator_exec[strlen(argv[1]) + strlen(EXECUTABLE_PREFIX)];
    strcpy(process_creator_exec, EXECUTABLE_PREFIX);
    strcat(process_creator_exec, process_creator_filename);
    int processes_amount = (int)strtod(argv[2], NULL);
    char *process_sections_amount = argv[3];
    char *data_filename = argv[4];
    int expected_value = (int)strtod(process_sections_amount, NULL) * processes_amount;

    if (signal(SIGINT, exit_cleanup) == SIG_ERR)
    {
        perror("Signal handler error");
        exit(EXIT_FAILURE);
    }

    if (atexit(exit_cleanup) == -1)
    {
        perror("Atexit error");
        exit(EXIT_FAILURE);
    }

    sem_t *sem = create_sem(SEMAPHORE_NAME, OPEN_MODE, O_CREAT | O_EXCL, INITIAL_SEM_VALUE);
    post_sem(sem);

    printf("Semaphore starting value: %d\n", getval_sem(sem));
    printf("Process ID: %d\n", getpid());

    ssize_t counter_descriptor = open(data_filename, O_WRONLY | O_TRUNC, OPEN_MODE);
    if (counter_descriptor == -1)
    {
        perror("Open function call error");
        exit(EXIT_FAILURE);
    }
    close(counter_descriptor);

    for (int i = 0; i < processes_amount; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Fork error");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            execlp(process_creator_exec, process_creator_filename, process_sections_amount, data_filename, NULL);
            perror("execlp error");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < processes_amount; i++)
    {
        wait(NULL);
    }
    assert_value(expected_value, data_filename);
    exit(EXIT_SUCCESS);
}

void exit_cleanup()
{
    unlink_sem(SEMAPHORE_NAME);
}

ssize_t open_file(char *name, int oflags, mode_t mode)
{
    ssize_t descriptor = open(name, oflags, mode);
    if (descriptor == -1)
    {
        perror("Open function call error");
        exit(EXIT_FAILURE);
    }

    return descriptor;
}

void assert_value(int expected_value, char *data_file)
{
    int buffer_size = (int)floor(log10(expected_value)) + 2;
    char file_buffer[buffer_size];
    ssize_t descriptor = open_file("counter.txt", O_RDONLY, OPEN_MODE);
    if (read(descriptor, file_buffer, buffer_size) == -1)
    {
        perror("Read function call error");
        exit(EXIT_FAILURE);
    }
    close(descriptor);
    printf("-----\n");
    printf("Expected value: %d\n", expected_value);
    printf("File value: %s\n", file_buffer);
}
