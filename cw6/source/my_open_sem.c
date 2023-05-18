#include "my_open_sem.h"

sem_t *my_open_sem(char *name, int oflags)
{
    sem_t *sem;
    if ((sem = sem_open(name, oflags)) == SEM_FAILED)
    {
        perror("Error while opening a semaphore");
        exit(EXIT_FAILURE);
    }
    return sem;
}