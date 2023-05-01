#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define REQUIRED_ARGS_AMOUNT 3
#define READ_CHUNK 10
#define OPEN_MODE 0644
#define MAX_SLEEP_IN_SECS 3

int random_sleep()
{
  srand(time(NULL));
  return (int)(((double)rand() / (double)RAND_MAX) * MAX_SLEEP_IN_SECS) + 1;
}

int main(int argc, char *argv[])
{
  if (argc < REQUIRED_ARGS_AMOUNT)
  {
    fprintf(stderr, "Wrong number of arguments provided!\n");
    exit(EXIT_FAILURE);
  }

  char buffer[READ_CHUNK + 1];
  char *input_filename = argv[1];
  const char sent_msg[] = "-----\nSent data: ";
  char *pipe_path = argv[2];
  ssize_t bytes_read;

  ssize_t pipedes_write = open(pipe_path, O_WRONLY, OPEN_MODE);
  ssize_t input_descriptor = open(input_filename, O_RDONLY, OPEN_MODE);

  if (pipedes_write == -1 || input_descriptor == -1)
  {
    perror("Open function call error");
    exit(EXIT_FAILURE);
  }

  while ((bytes_read = read(input_descriptor, buffer, READ_CHUNK)))
  {
    if (bytes_read == -1)
    {
      perror("Read function call error");
      exit(EXIT_FAILURE);
    }
    if (write(pipedes_write, buffer, bytes_read) == -1)
    {
      perror("Write pipe function call error.");
      exit(EXIT_FAILURE);
    }
    if (bytes_read)
    {
      write(STDOUT_FILENO, &sent_msg, strlen(sent_msg));
      for (int i = 0; i < bytes_read; i++)
      {
        write(STDOUT_FILENO, &buffer[i], sizeof(char));
      }
      write(STDOUT_FILENO, "\n", sizeof(char));
    }
    sleep(random_sleep());
  }
  close(input_descriptor);
  close(pipedes_write);
  exit(EXIT_SUCCESS);
}
