#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef MQ_MQ_OPEN_H
#define MQ_MQ_OPEN_H
//Function to create/open a mq with error handling.
mqd_t my_mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
#endif