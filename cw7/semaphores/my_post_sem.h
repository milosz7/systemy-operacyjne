#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef POST_SEM_H
#define POST_SEM_H
// Function to post a semaphore with error handling.
void my_post_sem(sem_t *sem);
#endif