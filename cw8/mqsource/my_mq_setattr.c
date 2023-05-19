#include "my_mq_setattr.h"

void my_mq_setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr)
{
    if (mq_setattr(mqdes, newattr, oldattr) == -1)
    {
        perror("Mq_setattr function call error");
        exit(EXIT_FAILURE);
    }
}
