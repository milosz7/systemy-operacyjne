#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef WAIT_SEM_H
#define WAIT_SEM_H
// Function to tell the program to wait for semaphore to be posted.
void my_wait_sem(sem_t *sem);
#endif