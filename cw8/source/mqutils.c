#include "mqutils.h"

void my_mq_close(mqd_t mqdes)
{
    if (mq_close(mqdes) == -1)
    {
        perror("Mq_close function call error");
        exit(EXIT_FAILURE);
    }
}

void my_mq_getattr(mqd_t mqdes, struct mq_attr *attr)
{
    if (mq_getattr(mqdes, attr) == -1)
    {
        perror("Mq_getattr function call error");
        exit(EXIT_FAILURE);
    }
}

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

void my_mq_recieve(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio)
{
    if (mq_receive(mqdes, msg_ptr, msg_len, msg_prio) == -1)
    {
        perror("Mq_recieve function call error");
        exit(EXIT_FAILURE);
    }
}

void my_mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio)
{
    if (mq_send(mqdes, msg_ptr, msg_len, msg_prio) == -1)
    {
        perror("Mq_send function call error");
        exit(EXIT_FAILURE);
    }
}

void my_mq_setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr)
{
    if (mq_setattr(mqdes, newattr, oldattr) == -1)
    {
        perror("Mq_setattr function call error");
        exit(EXIT_FAILURE);
    }
}

void my_mq_unlink(const char *name)
{
    if (mq_unlink(name) == -1)
    {
        perror("Mq_unlink function call error");
        exit(EXIT_FAILURE);
    }
}
