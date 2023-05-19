#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "semaphores/my_unlink_sem.h"
#include "semaphores/my_create_sem.h"
#include "semaphores/my_post_sem.h"
#include "semaphores/my_sem_getvalue.h"
#include "semaphores/my_close_sem.h"
#include "sharedmemory/my_shm_unlink.h"
#include "sharedmemory/my_shm_open.h"
#include "sharedmemory/my_ftruncate.h"

#define BUF_ELEMENT_SIZE 16
#define BUF_ELEMENTS_AMOUNT 4
#define OPEN_MODE 0644
#define INITIAL_SEM_VALUE 0
#define REQUIRED_ARGS_AMOUNT 5
#define EXECUTABLE_PREFIX "./"
#define SEMAPHORE_PROD_NAME "/semaphore_prod"
#define SEMAPHORE_CONS_NAME "/semaphore_cons"
#define SHM_NAME "/sharedmem"

typedef struct
{
    char buffer[BUF_ELEMENTS_AMOUNT][BUF_ELEMENT_SIZE];
    int read_idx, write_idx;
} SharedMEM;

void exit_cleanup();
void prefix_filename(char *filename, char dest[]);

int main(int argc, char *argv[])
{
    if (argc != REQUIRED_ARGS_AMOUNT)
    {
        fprintf(stderr, "Wrong number of arguments provided!\n");
        exit(EXIT_FAILURE);
    }

    char *consumer_filename = argv[1];
    char consumer_exec[strlen(consumer_filename) + strlen(EXECUTABLE_PREFIX)];
    prefix_filename(consumer_filename, consumer_exec);
    char *producer_filename = argv[2];
    char producer_exec[strlen(producer_filename) + strlen(EXECUTABLE_PREFIX)];
    prefix_filename(producer_filename, producer_exec);
    char *input_filename = argv[3];
    char *output_filename = argv[4];

    if (atexit(exit_cleanup) == -1)
    {
        perror("Atexit function call error");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, exit_cleanup) == SIG_ERR)
    {
        perror("Signal handler error");
        exit(EXIT_FAILURE);
    }
    sem_t *consumer_sem = my_create_sem(SEMAPHORE_CONS_NAME, OPEN_MODE, O_CREAT | O_EXCL, 0);
    printf("Consumer semaphore starting value: %d\n", my_sem_getvalue(consumer_sem));
    sem_t *producer_sem = my_create_sem(SEMAPHORE_PROD_NAME, OPEN_MODE, O_CREAT | O_EXCL, 1);
    printf("Producer semaphore starting value: %d\n", my_sem_getvalue(producer_sem));
    my_close_sem(producer_sem);
    my_close_sem(consumer_sem);

    int shm_fd = my_shm_open(SHM_NAME, O_EXCL | O_RDWR | O_CREAT, OPEN_MODE);
    my_ftruncate(shm_fd, sizeof(SharedMEM));
    close(shm_fd);

    pid_t producer_pid = fork();

    if (producer_pid == -1)
    {
        perror("Fork function call error");
        exit(EXIT_FAILURE);
    }

    if (producer_pid == 0)
    {
        execlp(producer_exec, producer_filename, input_filename, SEMAPHORE_CONS_NAME, SEMAPHORE_PROD_NAME, SHM_NAME, NULL);
        perror("Execlp function call error");
        exit(EXIT_FAILURE);
    }

    pid_t consumer_pid = fork();

    if (consumer_pid == -1)
    {
        perror("Fork function call error");
        exit(EXIT_FAILURE);
    }

    if (consumer_pid == 0)
    {
        execlp(consumer_exec, consumer_filename, output_filename, SEMAPHORE_CONS_NAME, SEMAPHORE_PROD_NAME, SHM_NAME, NULL);
        perror("Execlp function call error");
        exit(EXIT_FAILURE);
    }

    wait(NULL);
    wait(NULL);
    exit(EXIT_SUCCESS);
}

void exit_cleanup()
{
    my_unlink_sem(SEMAPHORE_PROD_NAME);
    my_unlink_sem(SEMAPHORE_CONS_NAME);
    my_shm_unlink(SHM_NAME);
}

void prefix_filename(char *filename, char dest[])
{
    strcpy(dest, EXECUTABLE_PREFIX);
    strcat(dest, filename);
}
