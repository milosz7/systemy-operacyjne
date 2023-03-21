#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "display_data.h"

#define INT_MAX_LEN 11
#define EXECUTABLE_PREFIX "./"

int main(int argc, char *argv[])
{
  char *execlp_filename = argv[1];
  char execlp_filename_exec[strlen(argv[1]) + strlen(EXECUTABLE_PREFIX)];

  strcpy(execlp_filename_exec, EXECUTABLE_PREFIX);
  strcat(execlp_filename_exec, argv[1]);

  printf("Parent process:\n");
  display_process_data();
  for (int i = 0; i < 3; i++)
  {
    int pid = fork();
    if (pid == -1)
    {
      perror("fork error");
      exit(1);
    }
    if (pid == 0)
    {
      pid_t ppid = getppid();
      char ppid_str [INT_MAX_LEN];
      sprintf(ppid_str, "%d", ppid);
      execlp(execlp_filename_exec, execlp_filename, ppid_str, NULL);
      perror("Execlp failed to run.");
      exit(errno);
    }
    wait(NULL);
  }
}
