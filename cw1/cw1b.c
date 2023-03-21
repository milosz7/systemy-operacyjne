#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "display_data.h"

int main()
{
  printf("Proces macierzysty:\n");
  display_process_data();
  printf("Procesy potomne:\n");
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
      display_process_data();
    }
    wait(NULL);
  }
}
