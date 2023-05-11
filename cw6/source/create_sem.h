#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef CREATE_SEM_H
#define CREATE_SEM_H

// Function to open a semaphore with error handling
sem_t *create_sem(char *name, mode_t mode, int oflag, int start_val);

#endif
