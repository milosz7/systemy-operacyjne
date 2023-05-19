#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MY_MQ_SEND_H
#define MY_MQ_SEND_H
//Function to send messages to mq with error handling.
void my_mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
#endif