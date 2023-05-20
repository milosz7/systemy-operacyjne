#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#include "mqsource/my_mq_open.h"
#include "mqsource/my_mq_unlink.h"
#include "mqsource/my_mq_recieve.h"
#include "mqsource/my_mq_getattr.h"
#include "mqsource/my_mq_setattr.h"
#include "mqsource/my_mq_send.h"
#include "mqsource/my_mq_close.h"
#include "mqsource/constants.h"

void exit_cleanup();
void signal_cleanup();
double process_msg(char *msg, char *client_mq_name);
double perform_operation(double operand1, char operator, double operand2);

int main()
{
    struct mq_attr default_mq = {
        .mq_maxmsg = DEFAULT_MSG_AMT,
        .mq_msgsize = DEFAULT_MSGSIZE_IN_BYTES,
        .mq_flags = DEFAULT_MQ_FLAGS,
        .mq_curmsgs = 0};
    unsigned int prio;

    if (atexit(exit_cleanup) == -1)
    {
        perror("Atexit function call error");
        _exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, signal_cleanup) == SIG_ERR)
    {
        perror("Signal function call error");
        _exit(EXIT_FAILURE);
    }

    mqd_t server_mq = my_mq_open(SERVER_MQ_NAME, O_CREAT | O_RDONLY, OPEN_MODE, &default_mq);
    printf("This is a server process. Use ctrl + C to shut it down.\n");
    printf("Remember that shutting the server down and sending a client request afterwards will result in undefined behavior.\n");

    struct mq_attr mq_attributes;
    my_mq_getattr(server_mq, &mq_attributes);
    char msg_buffer[mq_attributes.mq_msgsize];
    char client_mq_name[MQ_NAME_CHAR_LIMIT];

    while (1)
    {
        my_mq_recieve(server_mq, msg_buffer, sizeof(msg_buffer), &prio);
        printf("Recieved request: %s\n", msg_buffer);
        sleep(COMPUTATION_TIME_IN_S);
        double result = process_msg(msg_buffer, client_mq_name);
        printf("Computation result: %lf\n", result);
        char full_result[DEFAULT_MSGSIZE_IN_BYTES / sizeof(char)];

        if (result == INFINITY)
        {
            sprintf(full_result, "%s", ZERO_DIVISION_MESSAGE);
        }
        else
        {
            sprintf(full_result, "%s%lf", RESULT_MESSAGE, result);
        }
        mqd_t client_mq = my_mq_open(client_mq_name, O_WRONLY, OPEN_MODE, NULL);
        my_mq_send(client_mq, full_result, sizeof(full_result), DEFAULT_PRIO);
        my_mq_close(client_mq);
    }

    my_mq_unlink(SERVER_MQ_NAME);
}

double process_msg(char *msg, char *client_mq_name)
{
    double operand1, operand2;
    char operator[2];
    sscanf(msg, "%[^|]|%lf%s%lf", client_mq_name, &operand1, operator, & operand2);
    double result = perform_operation(operand1, *operator, operand2);
    return result;
}

double perform_operation(double operand1, char _operator, double operand2)
{
    if (_operator == '+')
    {
        return operand1 + operand2;
    }
    if (_operator == '-')
    {
        return operand1 - operand2;
    }
    if (_operator == '*')
    {
        return operand1 * operand2;
    }
    if (_operator == '/')
    {
        if (operand2 == 0)
        {
            return INFINITY;
        }
        return operand1 / operand2;
    }
    fprintf(stderr, "Something went wrong.\n");
    exit(EXIT_FAILURE);
}

void exit_cleanup()
{
    my_mq_unlink(SERVER_MQ_NAME);
}

void signal_cleanup()
{
    exit(EXIT_SUCCESS);
}