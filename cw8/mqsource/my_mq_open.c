#include "my_mq_open.h"

mqd_t my_mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr)
{
    mqd_t mq = mq_open(name, oflag, mode, attr);
    if (mq == -1)
    {
        perror("Mq_open function call error");
        exit(EXIT_FAILURE);
    }
    return mq;
}
