#include "create_sem.h"

sem_t *create_sem(char *name, mode_t mode, int oflags, int start_val)
{
    sem_t *sem = sem_open(name, oflags, mode, start_val);
    if (sem == SEM_FAILED)
    {
        perror("semaphore creation error.");
        exit(EXIT_FAILURE);
    }
    return sem;
}