#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifndef MYMQ_H
#define MYMQ_H

#define DEFAULT_MSGSIZE_IN_BYTES 128 * sizeof(char)
#define DEFAULT_MSG_AMT 10
#define DEFAULT_MQ_FLAGS 0

#define OPEN_MODE 0644

#define MQ_PREFIX "/"
#define MQ_NAME_CHAR_LIMIT 12 // MAX_INT_LEN + MQ_PREFIX + '\0'
#define INPUT_SIZE 64

#define QUERY_DELIM "|"
#define QUERY_DELIM_LEN 1
#define DEFAULT_PRIO 1
#define SERVER_MQ_NAME "/server_mq"

#define WRONG_INPUT 1
#define CORRECT_INPUT 0

#define COMPUTATION_TIME_IN_S 2

#define VALID_INPUT_REGEXR "^[0-9]*\\.?[0-9]+\\s[+-/*]\\s[0-9]*\\.?[0-9]+\n$|^q\n$"

#define RESULT_MESSAGE "Result: "
#define ZERO_DIVISION_MESSAGE "You cannot divide by zero!"

//Function to close mq with error handling.
void my_mq_close(mqd_t mqdes);
// Function to retrieve attributes of mq with error handling.
void my_mq_getattr(mqd_t mqdes, struct mq_attr *attr);
//Function to create/open a mq with error handling.
mqd_t my_mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
// Function to retrieve a message from mq with error handling.
void my_mq_recieve(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned int *msg_prio);
//Function to send messages to mq with error handling.
void my_mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned int msg_prio);
//Function to update attributes of mq with error handling.
void my_mq_setattr(mqd_t mqdes, struct mq_attr *newattr, struct mq_attr *oldattr);
//Function to unlink a mq with error handling.
void my_mq_unlink(const char *name);
#endif
