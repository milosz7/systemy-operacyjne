#include "my_mq_send.h"

void my_mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio)
{
    if (mq_send(mqdes, msg_ptr, msg_len, msg_prio) == -1)
    {
        perror("Mq_send function call error");
        exit(EXIT_FAILURE);
    }
}
