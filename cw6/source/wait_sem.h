#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef WAIT_SEM_H
#define WAIT_SEM_H
// Function to tell the program to wait for sem to be posted.
void wait_sem(sem_t *sem);
#endif