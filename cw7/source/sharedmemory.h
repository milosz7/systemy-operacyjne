#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/mman.h>

#ifndef SHAREDMEMORY_H
#define SHARERDMEMORY_H
// Function to close files with error handling.
void my_close(int fd);
//Function to truncate shared memory with error handling.
void my_ftruncate(int fd, off_t length);
//Function to map shared memory with error handling.
void* my_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
// Function to unmap shared memory with error handling.
void my_munmap(void *addr, size_t length);
//Function to open shared memory with error handling.
int my_shm_open(const char *name, int flags, mode_t mode);
//Function to unlink shared memory with error handling.
void my_shm_unlink(const char *name);
#endif