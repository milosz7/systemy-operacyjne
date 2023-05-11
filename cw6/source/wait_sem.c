#include "wait_sem.h"

void wait_sem(sem_t *sem)
{
    if (sem_wait(sem) == -1)
    {
        perror("sem_wait error");
        exit(EXIT_FAILURE);
    }
}
