#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define CHILD_PROCESSES_AMOUNT 3

int main(int argc, char *argv[])
{
  char *exec_filename_path = argv[1];
  char *exec_filename = argv[2];
  char *program_mode = argv[3];
  char *signal_code = argv[4];
  int signal_to_int = (int)strtod(signal_code, NULL);
  int child_pids[CHILD_PROCESSES_AMOUNT];

  if (signal(signal_to_int, SIG_IGN) == SIG_ERR)
  {
    fprintf(stderr, "%s signal error.", strsignal(signal_to_int));
    perror("");
    exit(EXIT_FAILURE);
  }

  printf("process_creator PID: %d\n", getpid());

  for (int i = 0; i < CHILD_PROCESSES_AMOUNT; i++)
  {

    pid_t pid = fork();

    if (pid == -1)
    {
      perror("Fork error.\n");
      exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
      execlp(exec_filename_path, exec_filename, program_mode, signal_code, NULL);
    }
  }

  for (int i = 0; i < CHILD_PROCESSES_AMOUNT; i++)
  {
    int status;
    pid_t cpid = wait(&status);
    if (WIFSIGNALED(status))
      printf("Process with PID: %d terminated with signal %d\n", cpid, WTERMSIG(status));
    if (WIFEXITED(status))
      printf("Process with PID: %d exited with status %d\n", cpid, WEXITSTATUS(status));
  }
  exit(EXIT_SUCCESS);
}
