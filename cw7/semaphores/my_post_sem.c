#include "my_post_sem.h"

void my_post_sem(sem_t *sem)
{
    if (sem_post(sem) == -1)
    {
        perror("sem_post error.");
        exit(EXIT_FAILURE);
    }
}
