#include "my_mq_recieve.h"

void my_mq_recieve(mqd_t mqdes, char *msg_ptr, size_t msg_len, int *msg_prio)
{
    if (mq_receive(mqdes, msg_ptr, msg_len, msg_prio) == -1)
    {
        perror("Mq_recieve function call error");
        exit(EXIT_FAILURE);
    }
}
