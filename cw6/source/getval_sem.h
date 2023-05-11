#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef GETVAL_SEM_H
#define GETVAL_SEM_H

//Function to retrieve a semaphore current value.
int getval_sem(sem_t *sem);

#endif
