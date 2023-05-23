#include "sharedmemory.h"

void my_close(int fd)
{
    if (close(fd) == -1)
    {
        perror("Close function call error");
        exit(EXIT_FAILURE);
    }
}

void my_ftruncate(int fc, off_t length)
{
    if (ftruncate(fc, length) == -1)
    {
        perror("Ftruncate function call error");
        exit(EXIT_FAILURE);
    }
}

void *my_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    void *map = mmap(addr, length, prot, flags, fd, offset);
    if (map == MAP_FAILED)
    {
        perror("Mmap function call error");
        exit(EXIT_FAILURE);
    }
    return map;
}

int my_shm_open(const char *name, int flags, mode_t mode)
{
    int des = shm_open(name, flags, mode);
    if (des == -1)
    {
        perror("Shm_open function call error");
        exit(EXIT_FAILURE);
    }
    return des;
}

void my_shm_unlink(const char *name)
{
    if (shm_unlink(name) == -1)
    {
        perror("Shm_unlink function call error");
        exit(EXIT_FAILURE);
    }
}

void my_munmap(void *addr, size_t length)
{
    if (munmap(addr, length) == -1)
    {
        perror("Munmap function call error");
        exit(EXIT_FAILURE);
    }
    return;
}
