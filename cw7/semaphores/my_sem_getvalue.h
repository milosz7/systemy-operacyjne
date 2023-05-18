#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef GETVAL_SEM_H
#define GETVAL_SEM_H

// Function to retrieve a semaphore current value.
int my_sem_getvalue(sem_t *sem);

#endif
