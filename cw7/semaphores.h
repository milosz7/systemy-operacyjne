#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef SEMAPHORES_H
#define SEMAPHORES_H
//Function to close a semaphore with error handling.
void my_close_sem(sem_t *sem);
// Function to open a semaphore with error handling
sem_t *my_create_sem(char *name, mode_t mode, int oflag, int start_val);
// Function to open a semaphore with error handling
sem_t *my_open_sem(char *name, int oflags);
// Function to post a semaphore with error handling.
void my_post_sem(sem_t *sem);
// Function to retrieve a semaphore current value.
int my_sem_getvalue(sem_t *sem);
// Function to unlink a semaphore with error handling.
void my_unlink_sem(char *name);
// Function to tell the program to wait for semaphore to be posted.
void my_wait_sem(sem_t *sem);
#endif
