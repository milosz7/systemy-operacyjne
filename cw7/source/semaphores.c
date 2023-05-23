#include "semaphores.h"

void my_close_sem(sem_t *sem)
{
    if (sem_close(sem) == -1)
    {
        perror("sem_close error");
        exit(EXIT_FAILURE);
    }
}

sem_t *my_create_sem(char *name, mode_t mode, int oflags, int start_val)
{
    sem_t *sem = sem_open(name, oflags, mode, start_val);
    if (sem == SEM_FAILED)
    {
        perror("semaphore creation error.");
        exit(EXIT_FAILURE);
    }
    return sem;
}

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

void my_post_sem(sem_t *sem)
{
    if (sem_post(sem) == -1)
    {
        perror("sem_post error.");
        exit(EXIT_FAILURE);
    }
}

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

void my_unlink_sem(char *name)
{
    if (sem_unlink(name) == -1)
    {
        perror("sem_unlink error");
        exit(EXIT_FAILURE);
    }
}

void my_wait_sem(sem_t *sem)
{
    if (sem_wait(sem) == -1)
    {
        perror("sem_wait error");
        exit(EXIT_FAILURE);
    }
}
