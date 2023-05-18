#include "my_unlink_sem.h"

void my_unlink_sem(char *name)
{
    if (sem_unlink(name) == -1)
    {
        perror("sem_unlink error");
        exit(EXIT_FAILURE);
    }
}
