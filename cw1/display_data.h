#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void display_process_data()
{
  printf("-----------------\n");
  printf("UID: %d\n", getuid());
  printf("GID: %d\n", getgid());
  printf("PID: %d\n", getpid());
  printf("PPID: %d\n", getppid());
  printf("PGID: %d\n", getpgrp());
}