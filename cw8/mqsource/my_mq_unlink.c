#include "my_mq_unlink.h"

void my_mq_unlink(const char *name)
{
    if (mq_unlink(name) == -1)
    {
        perror("Mq_unlink function call error");
        exit(EXIT_FAILURE);
    }
}
