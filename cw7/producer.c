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
#include "sharedmemory/my_ftruncate.h"
#include "sharedmemory/my_close.h"

#define BUF_ELEMENT_SIZE 16
#define BUF_ELEMENTS_AMOUNT 4
#define OPEN_MODE 0644
#define MAX_SLEEP_IN_SECS 3

typedef struct
{
    char buffer[BUF_ELEMENTS_AMOUNT][BUF_ELEMENT_SIZE];
    int read_idx, write_idx;
} SharedMEM;

int random_sleep();
void print_data(char *data);

int main(int argc, char *argv[])
{
    char *input_filename = argv[1];
    char *consumer_semaphore_name = argv[2];
    char *producer_semaphore_name = argv[3];
    char *sharedmem_name = argv[4];
    char sent_msg[] = "\n-----\nSent data: ";
    int input_filedes, bytes_read;
    input_filedes = open(input_filename, O_RDONLY, OPEN_MODE);
    if (input_filedes == -1)
    {
        perror("Open function call error");
        _exit(EXIT_FAILURE);
    }

    sem_t *consumer_sem = my_open_sem(consumer_semaphore_name, O_RDWR);
    sem_t *producer_sem = my_open_sem(producer_semaphore_name, O_RDWR);
    int shm_fd = my_shm_open(sharedmem_name, O_RDWR, OPEN_MODE);
    SharedMEM *shm = (SharedMEM *)my_mmap(NULL, sizeof(SharedMEM), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    shm->write_idx = 0;

    while (1)
    {
        sleep(random_sleep());
        my_wait_sem(producer_sem);
        bytes_read = read(input_filedes, shm->buffer[shm->write_idx], BUF_ELEMENT_SIZE);
        if (bytes_read == -1)
        {
            perror("Read function call error");
            _exit(EXIT_FAILURE);
        }

        print_data(sent_msg);
        print_data(shm->buffer[shm->write_idx]);

        if (bytes_read < BUF_ELEMENT_SIZE)
        {
            shm->buffer[shm->write_idx][bytes_read] = '\0';
            my_post_sem(consumer_sem);
            break;
        }

        shm->write_idx = (shm->write_idx + 1) % BUF_ELEMENTS_AMOUNT;
        my_post_sem(consumer_sem);
    }
    my_close(input_filedes);
    my_close_sem(consumer_sem);
    my_close_sem(producer_sem);
    my_munmap(shm, sizeof(SharedMEM));
    my_close(shm_fd);
    _exit(EXIT_SUCCESS);
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
