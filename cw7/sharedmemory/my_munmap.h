#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#ifndef MY_UNMAP_H
#define MY_UNMAP_H
//Function to unmap shared memory with error handling.
void my_unmap(void* addr, size_t length);
#endif