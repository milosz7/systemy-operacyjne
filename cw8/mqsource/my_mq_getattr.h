#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MY_MQ_GETATTR_H
#define MY_MQ_GETATTR_H
// Function to retrieve attributes of mq with error handling.
void my_mq_getattr(mqd_t mqdes, struct mq_attr *attr);
#endif