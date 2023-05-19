#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MY_MQ_RECIEVE_H
#define MY_MQ_RECIEVE_H
//Function to retrieve a message from mq with error handling.
void my_mq_recieve(mqd_t mqdes, char *msg_ptr, size_t msg_len, int *msg_prio);
#endif