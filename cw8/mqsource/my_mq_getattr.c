#include "my_mq_getattr.h"

void my_mq_getattr(mqd_t mqdes, struct mq_attr *attr)
{
    if (mq_getattr(mqdes, attr) == -1)
    {
        perror("Mq_getattr function call error");
        exit(EXIT_FAILURE);
    }
}
