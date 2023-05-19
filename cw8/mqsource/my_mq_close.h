#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MY_MQ_CLOSE_H
#define MY_MQ_CLOSE_H
//Function to close mq with error handling.
void my_mq_close(mqd_t mqdes);
#endif