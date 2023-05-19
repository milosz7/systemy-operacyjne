#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MQ_MQ_SETATTR_H
#define MQ_MQ_SETATTR_H
//Function to update attributes of mq with error handling.
void my_mq_setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr);
#endif