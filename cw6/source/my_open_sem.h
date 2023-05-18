#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef OPEN_SEM_H
#define OPEN_SEM_H

// Function to open a semaphore with error handling
sem_t *my_open_sem(char *name, int oflags);

#endif
