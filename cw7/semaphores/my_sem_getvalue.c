#include "my_sem_getvalue.h"

int my_sem_getvalue(sem_t *sem)
{
    int sem_value;

    if (sem_getvalue(sem, &sem_value) == -1)
    {
        perror("Error while retrieveing semaphore value");
        exit(EXIT_FAILURE);
    }
    return sem_value;
}