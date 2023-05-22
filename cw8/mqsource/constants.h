#ifndef CONSTANTS_H
#define CONSTANTS_H

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
#endif
