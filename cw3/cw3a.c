#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRED_ARGS_AMOUNT 3
#define MODE_DEFAULT 1
#define MODE_IGNORE 2
#define MODE_CUSTOM 3

void signal_handler(int);
void signal_error(int);

int main(int argc, char *argv[])
{
  if (argc < REQUIRED_ARGS_AMOUNT)
  {

    fprintf(stderr, "Wrong number of arguments provided!\n");
    exit(EXIT_FAILURE);
  }
  int program_mode = (int)strtod(argv[1], NULL);
  int requested_signal = (int)strtod(argv[2], NULL);


  printf("Chosen signal: %d\n", requested_signal);
  printf("PID: %d, handling mode: %s\n", getpid(), 
    program_mode == MODE_DEFAULT ? "default" :
    program_mode == 2 ? "ignore": "custom");

  if (program_mode == MODE_DEFAULT)
  {
    if (signal(requested_signal, SIG_DFL) == SIG_ERR)
    {
      signal_error(requested_signal);
    }
    pause();
  }

  if (program_mode == MODE_IGNORE)
  {
    if (signal(requested_signal, SIG_IGN) == SIG_ERR)
    {
      signal_error(requested_signal);
    }
    pause();
  }

  if (program_mode == MODE_CUSTOM)
  {
    if (signal(requested_signal, signal_handler) == SIG_ERR)
    {
      signal_error(requested_signal);
    }
    pause();
  }
  exit(EXIT_SUCCESS);
}

void signal_handler(int sig)
{
  printf("%s (%d) signal captured!\n", strsignal(sig), sig);
}

void signal_error(int requested_signal)
{
  fprintf(stderr, "%s signal error.", strsignal(requested_signal));
  perror("");
  exit(EXIT_FAILURE);
}
