#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#ifndef MY_MMAP_H
#define MY_MMAP_H
//Function to map shared memory with error handling.
void* my_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
#endif
