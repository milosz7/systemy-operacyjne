#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define REQUIRED_ARGS_AMOUNT 4
#define PARENT_SLEEP_IN_SECS 1
#define EXECUTABLE_PREFIX "./"

int main(int argc, char *argv[])
{
  if (argc < REQUIRED_ARGS_AMOUNT)
  {
    fprintf(stderr, "Wrong number of arguments provided!\n");
    exit(EXIT_FAILURE);
  }
  char *exec_filename = argv[1];
  char exec_filename_path[strlen(argv[1]) + strlen(EXECUTABLE_PREFIX)];
  char *program_mode = argv[2];
  char *signal_code = argv[3];
  int signal_to_int = (int)strtod(signal_code, NULL);

  strcpy(exec_filename_path, EXECUTABLE_PREFIX);
  strcat(exec_filename_path, exec_filename);

  pid_t pid = fork();

  if (pid == -1)
  {
    perror("Fork error.\n");
    exit(EXIT_FAILURE);
  }

  if (pid == 0)
  {
    execlp(exec_filename_path, exec_filename, program_mode, signal_code, NULL);
    perror("Execlp failed to run.");
    exit(errno);
  }

  if (kill(pid, 0) == 0)
  {
    int status;
    sleep(PARENT_SLEEP_IN_SECS);
    kill(pid, signal_to_int);
    wait(&status);
    int signal = WTERMSIG(status);

    if (WIFSIGNALED(status))
    {
      printf("Child process with PID: %d got killed by signal %s. (%d)\n", pid, strsignal(signal), signal);
    }
    exit(EXIT_SUCCESS);
  }

  printf("Nothing to kill.\n");
  exit(EXIT_SUCCESS);
}
