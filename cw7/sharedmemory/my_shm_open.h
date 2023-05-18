#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#ifndef MY_SHM_OPEN_H
#define MY_SHM_OPEN_H
//Function to open shared memory with error handling.
int my_shm_open(const char *name, int flags, mode_t mode);
#endif