#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "display_data.h"

int main()
{
  int status;
  printf("Parent process:\n");
  display_process_data();
  printf("Child processes:\n");
  for (int i = 0; i < 3; i++)
  {
    int pid = fork();
    if (pid == -1)
    {
      perror("fork error");
      exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
      if (setpgid(0, 0) == -1) {
        perror("Setpgid error.\n");
        exit(EXIT_FAILURE);
      }
      display_process_data();
    }
    if (pid > 0)
    {
      wait(&status);
    }
  }
}
