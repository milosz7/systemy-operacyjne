#include "getval_sem.h"

int getval_sem(sem_t *sem)
{
    int sem_value;

    if (sem_getvalue(sem, &sem_value) == -1)
    {
        perror("Error while retrieveing semaphore value");
        exit(EXIT_FAILURE);
    }
    return sem_value;
}