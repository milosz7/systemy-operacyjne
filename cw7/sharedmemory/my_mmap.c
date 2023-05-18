#include "my_mmap.h"

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