#include "my_mq_close.h"

void my_mq_close(mqd_t mqdes)
{
    if (mq_close(mqdes) == -1)
    {
        perror("Mq_close function call error");
        exit(EXIT_FAILURE);
    }
}
