#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MY_MQ_UNLINK_H
#define MY_MQ_UNLINK_H
//Function to unlink a mq with error handling.
void my_mq_unlink(const char *name);
#endif