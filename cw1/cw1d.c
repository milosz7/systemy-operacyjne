#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include "display_data.h"

#define SLEEP_TIME_IN_SECONDS 2
#define SLEEP_TIME_PARENT_PROCESS 10

int main()
{
  printf("Parent process:\n");
  display_process_data();
  printf("Child processes:\n");
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
  sleep(SLEEP_TIME_PARENT_PROCESS);
  return 0;
}
