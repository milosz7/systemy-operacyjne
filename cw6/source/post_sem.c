#include "post_sem.h"

void post_sem(sem_t *sem)
{
    if (sem_post(sem) == -1)
    {
        perror("sem_post error.");
        exit(EXIT_FAILURE);
    }
}
