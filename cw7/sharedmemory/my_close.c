#include "my_close.h"

void my_close(int fd)
{
    if (close(fd) == -1)
    {
        perror("Close function call error");
        exit(EXIT_FAILURE);
    }
}