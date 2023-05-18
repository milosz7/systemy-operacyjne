#include "my_shm_unlink.h"

void my_shm_unlink(const char *name)
{
    if (shm_unlink(name) == -1)
    {
        perror("Shm_unlink function call error");
        exit(EXIT_FAILURE);
    }
}