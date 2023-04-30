#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

#define REQUIRED_ARGS_AMOUNT 4
#define READ_CHUNK 16
#define WRITE_CHUNK 12
#define OPEN_MODE 0644
#define MAX_SLEEP_IN_SECS 5
#define FIFO_PATH "./pipe.FIFO"
#define READ_EXEC "./cw5a_read.x"
#define WRITE_EXEC "./cw5a_write.x"

void clear_mkfifo()
{
  unlink(FIFO_PATH);
}

int main(int argc, char *argv[])
{
  if (argc < REQUIRED_ARGS_AMOUNT)
  {
    fprintf(stderr, "Wrong number of arguments provided!\n");
    exit(EXIT_FAILURE);
  }

  char *input_filename = argv[1];
  char *output_filename = argv[2];
  char *pipe_path = argv[3];

  if (atexit(clear_mkfifo) == -1)
  {
    perror("Atexit error");
    exit(EXIT_FAILURE);
  }

  if (signal(SIGINT, clear_mkfifo) == SIG_ERR)
  {
    perror("Signal handler error");
    exit(EXIT_FAILURE);
  }

  if (mkfifo(pipe_path, OPEN_MODE) == -1)
  {
    perror("Mkfifo error");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  if (pid == -1)
  {
    perror("fork error");
    exit(EXIT_FAILURE);
  }
  if (pid == 0)
  {
    execlp(WRITE_EXEC, WRITE_EXEC, output_filename, pipe_path, NULL);
    perror("execlp error");
    unlink(pipe_path);
    exit(EXIT_FAILURE);
  }

  pid_t pid2 = fork();
  if (pid2 == -1)
  {
    perror("fork error");
    exit(EXIT_FAILURE);
  }

  if (pid2 == 0)
  {
    execlp(READ_EXEC, READ_EXEC, input_filename, pipe_path, NULL);
    perror("execlp error");
    exit(EXIT_FAILURE);
  }
  waitpid(pid, NULL, 0);
  waitpid(pid2, NULL, 0);
  unlink(pipe_path);
}