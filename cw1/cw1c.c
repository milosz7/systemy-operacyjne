#include <stdio.h>
#include <stdlib.h>
#include "display_data.h"
#include <sys/types.h>

#define SLEEP_TIME_IN_SECONDS 2

int main()
{
  printf("Proces macierzysty:\n");
  display_process_data();
  printf("Procesy potomne:\n");
  for (int i = 0; i < 3; i++)
  {
    pid_t pid = fork();

    if (pid == -1)
    {
      perror("fork error");
      exit(1);
    }
    if (pid == 0)
    {
      sleep(SLEEP_TIME_IN_SECONDS + i);
      display_process_data();
    }
  }
  return 0;
}
