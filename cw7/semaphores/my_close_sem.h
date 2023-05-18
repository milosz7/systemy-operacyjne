#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef CLOSE_SEM_H
#define CLOSE_SEM_H
//Function to close a semaphore with error handling.
void my_close_sem(sem_t *sem);
#endif
