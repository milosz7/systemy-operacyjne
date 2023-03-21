#include <stdio.h>
#include <sys/types.h>
#include "display_data.h"


int main (int argc, char* argv[]) {
  char* parent_ppid = argv[1];
  printf("I am a process ran by process: %s using execlp function call.\n", parent_ppid);
  printf("My details:\n");
  display_process_data();
  return 0;
}
