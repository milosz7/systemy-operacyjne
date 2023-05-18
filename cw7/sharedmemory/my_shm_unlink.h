#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#ifndef MY_SHM_UNLINK_H
#define MY_SHM_UNLINK_H
//Function to unlink shared memory with error handling.
void my_shm_unlink(const char *name);
#endif