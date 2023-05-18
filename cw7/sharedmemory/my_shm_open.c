#include "my_shm_open.h"

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
