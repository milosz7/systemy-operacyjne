#include "my_munmap.h"

void my_unmap(void *addr, size_t length)
{
    if (munmap(addr, length) == -1)
    {
        perror("Munmap function call error");
        exit(EXIT_FAILURE);
    }
    return;
}