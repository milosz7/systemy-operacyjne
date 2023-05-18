#include "my_close_sem.h"

void my_close_sem(sem_t *sem)
{
    if (sem_close(sem) == -1)
    {
        perror("sem_close error");
        exit(EXIT_FAILURE);
    }
}
