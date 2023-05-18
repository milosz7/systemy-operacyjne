#include "my_ftruncate.h"

void my_ftruncate(int fc, off_t length)
{
    if (ftruncate(fc, length) == -1)
    {
        perror("Ftruncate function call error");
        exit(EXIT_FAILURE);
    }
}
