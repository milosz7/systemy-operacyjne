#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "semaphores/my_open_sem.h"
#include "semaphores/my_close_sem.h"
#include "semaphores/my_post_sem.h"
#include "semaphores/my_wait_sem.h"
#include "sharedmemory/my_shm_open.h"
#include "sharedmemory/my_mmap.h"
#include "sharedmemory/my_munmap.h"
#include "sharedmemory/my_close.h"

#define BUF_ELEMENT_SIZE 16
#define BUF_ELEMENTS_AMOUNT 4
#define OPEN_MODE 0644
#define EOF_PRESENT 1
#define EOF_NOT_PRESENT 0
#define MAX_SLEEP_IN_SECS 3

typedef struct
{
    char buffer[BUF_ELEMENTS_AMOUNT][BUF_ELEMENT_SIZE];
    int read_idx, write_idx;
} SharedMEM;

void print_data(char *data);
int random_sleep();
int isEOF(char *buf);

int main(int argc, char *argv[])
{
    char *output_filename = argv[1];
    char *consumer_semaphore_name = argv[2];
    char *producer_semaphore_name = argv[3];
    char *sharedmem_name = argv[4];
    char recieved_msg[] = "\n-----\nRecieved data: ";
    int output_filedes = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, OPEN_MODE);

    if (output_filedes == -1)
    {
        perror("Open function call error");
        _exit(EXIT_FAILURE);
    }

    sem_t *consumer_sem = my_open_sem(consumer_semaphore_name, O_RDWR);
    sem_t *producer_sem = my_open_sem(producer_semaphore_name, O_RDWR);
    int shm_fd = my_shm_open(sharedmem_name, O_RDWR, OPEN_MODE);
    SharedMEM *shm = (SharedMEM *)my_mmap(NULL, sizeof(SharedMEM), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    shm->read_idx = 0;

    while (1)
    {
        sleep(random_sleep());
        my_wait_sem(consumer_sem);
        if (isEOF(shm->buffer[shm->read_idx]) == EOF_NOT_PRESENT)
        {
            if (write(output_filedes, shm->buffer[shm->read_idx], BUF_ELEMENT_SIZE) == -1)
            {
                perror("Write function call error");
                _exit(EXIT_FAILURE);
            }
            print_data(recieved_msg);
            print_data(shm->buffer[shm->read_idx]);
        }
        if (isEOF(shm->buffer[shm->read_idx]) == EOF_PRESENT)
        {
            if (write(output_filedes, shm->buffer[shm->read_idx], strlen(shm->buffer[shm->read_idx])) == -1)
            {
                perror("Write function call error");
                _exit(EXIT_FAILURE);
            }
            print_data(recieved_msg);
            print_data(shm->buffer[shm->read_idx]);
            break;
        }
        shm->read_idx = (shm->read_idx + 1) % BUF_ELEMENTS_AMOUNT;
        my_post_sem(producer_sem);
    }
    my_close(output_filedes);
    my_close_sem(consumer_sem);
    my_close_sem(producer_sem);
    my_munmap(shm, sizeof(SharedMEM));
    exit(EXIT_SUCCESS);
}

int isEOF(char *buf)
{
    for (int i = 0; i < BUF_ELEMENT_SIZE; i++)
    {
        if (buf[i] == '\0')
            return EOF_PRESENT;
    }
    return EOF_NOT_PRESENT;
}

void print_data(char *data)
{
    if (write(STDOUT_FILENO, data, strlen(data)) == -1)
    {
        perror("Write function call error");
        _exit(EXIT_FAILURE);
    }
}

int random_sleep()
{
    srand(time(NULL));
    return (int)(((double)rand() / (double)RAND_MAX) * MAX_SLEEP_IN_SECS) + 1;
}
