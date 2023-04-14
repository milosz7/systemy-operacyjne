#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define REQUIRED_ARGS_AMOUNT 5
#define PARENT_SLEEP_IN_SECS 1
#define EXECUTABLE_PREFIX "./"

void add_prefix_executable(char *filename, char *file_path_pointer);
int calculate_executable_path_len(char *filename);

int main(int argc, char *argv[])
{
  if (argc < REQUIRED_ARGS_AMOUNT)
  {
    fprintf(stderr, "Wrong number of arguments provided!\n");
    exit(EXIT_FAILURE);
  }

  char *process_creator_filename = argv[1];
  char *exec_filename = argv[2];
  char *program_mode = argv[3];
  char *signal_code = argv[4];
  char exec_filename_path[calculate_executable_path_len(exec_filename)];
  char process_creator_filename_path[calculate_executable_path_len(process_creator_filename)];
  int signal_to_int = (int)strtod(signal_code, NULL);
  int status;

  add_prefix_executable(exec_filename, exec_filename_path);
  add_prefix_executable(process_creator_filename, process_creator_filename_path);

  pid_t pid = fork();

  if (pid == -1)
  {
    perror("Fork error.\n");
    exit(EXIT_FAILURE);
  }

  if (pid == 0)
  {
    if (setpgid(0, 0) == -1)
    {
      perror("Setpgid error.\n");
      exit(EXIT_FAILURE);
    }
    execlp(process_creator_filename_path,
           process_creator_filename,
           exec_filename_path,
           exec_filename,
           program_mode,
           signal_code,
           NULL);
    perror("Execlp error.\n");
    exit(EXIT_FAILURE);
  }

  if (kill(pid, 0) == 0)
  {
    sleep(PARENT_SLEEP_IN_SECS);
    kill(pid * -1, signal_to_int);
    wait(&status);
    
    printf("Process generator exited with status %d\n", WEXITSTATUS(status));
    exit(EXIT_SUCCESS);
  }
  printf("Nothing to kill.\n");
  exit(EXIT_SUCCESS);
}

void add_prefix_executable(char *filename, char *file_path_pointer)
{
  strcpy(file_path_pointer, EXECUTABLE_PREFIX);
  strcat(file_path_pointer, filename);
}

int calculate_executable_path_len(char *filename)
{
  return strlen(filename) + strlen(EXECUTABLE_PREFIX);
}