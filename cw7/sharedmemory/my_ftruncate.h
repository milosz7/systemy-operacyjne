#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef MY_FTRUNCATE_H
#define MY_FTRUNCATE_H
//Function to truncate shared memory with error handling.
void my_ftruncate(int fd, off_t length);
#endif