#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef UNLINK_SEM_H
#define UNLINK_SEM_H
// Function to unlink a semaphore with error handling.
void my_unlink_sem(char *name);
#endif