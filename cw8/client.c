#include <mqueue.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <regex.h>

#include "source/mqutils.h"

char mq_name[MQ_NAME_CHAR_LIMIT];

void exit_cleanup();
void signal_cleanup();
int validate_input(char *user_input);
void get_input(char *user_input, int input_size);

int main()
{
    struct mq_attr default_mq = {
        .mq_maxmsg = DEFAULT_MSG_AMT,
        .mq_msgsize = DEFAULT_MSGSIZE_IN_BYTES,
        .mq_flags = DEFAULT_MQ_FLAGS,
        .mq_curmsgs = 0};

    pid_t pid = getpid();
    unsigned int prio;

    sprintf(mq_name, "%s%d", MQ_PREFIX, pid);

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

    mqd_t client_mq = my_mq_open(mq_name, O_RDONLY | O_CREAT | O_EXCL, OPEN_MODE, &default_mq);
    mqd_t server_mq = my_mq_open(SERVER_MQ_NAME, O_WRONLY, OPEN_MODE, NULL);

    struct mq_attr mq_attributes;
    my_mq_getattr(server_mq, &mq_attributes);
    char msg_buffer[mq_attributes.mq_msgsize];
    char response[mq_attributes.mq_msgsize];

    while (1)
    {
        char user_input[INPUT_SIZE];
        get_input(user_input, INPUT_SIZE);

        if (*user_input == 'q')
        {
            printf("Exiting...\n");
            exit(EXIT_SUCCESS);
        }

        sprintf(msg_buffer, "%s%s%s", mq_name, QUERY_DELIM, user_input);
        my_mq_send(server_mq, msg_buffer, sizeof(msg_buffer), DEFAULT_PRIO);
        printf("Computing...\n");
        my_mq_recieve(client_mq, response, sizeof(response), &prio);
        sleep(COMPUTATION_TIME_IN_S);

        printf("%s\n", response);
    }
}

int validate_input(char *user_input)
{
    int is_valid_input;
    regex_t input_regexr;
    is_valid_input = regcomp(&input_regexr, VALID_INPUT_REGEXR, REG_EXTENDED);
    is_valid_input = regexec(&input_regexr, user_input, 0, NULL, 0);
    regfree(&input_regexr);
    if (is_valid_input == REG_NOMATCH)
    {
        fprintf(stderr, "Wrong input!\n");
        return WRONG_INPUT;
    }
    return CORRECT_INPUT;
}

void get_input(char *user_input, int input_size)
{
    int validation;

    printf("\nProvide an expression in a format <operand> <operator> <operand>\n");
    printf("Separate each expression element using a single whitespace (regexr requirement)\n");
    printf("Avaliable operands: +, -, *, /\n");
    printf("Alternatively you can type in \"q\" to exit the client program\n");
    if (fgets(user_input, input_size, stdin) == NULL)
    {
        fprintf(stderr, "Fgets function call error.\n");
        exit(EXIT_FAILURE);
    }

    validation = validate_input(user_input);
    if (validation == WRONG_INPUT)
    {
        get_input(user_input, input_size);
    }
}

void exit_cleanup()
{
    my_mq_unlink(mq_name);
}

void signal_cleanup()
{
    exit(EXIT_SUCCESS);
}
