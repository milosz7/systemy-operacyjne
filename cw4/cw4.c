#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define REQUIRED_ARGS_AMOUNT 3
#define READ_CHUNK 16
#define WRITE_CHUNK 10
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
  int filedes[2];
  ssize_t bytes_read, pipe_bytes_read;
  char *input_filename = argv[1];
  char *output_filename = argv[2];
  char read_buffer[READ_CHUNK + 1];
  char write_buffer[WRITE_CHUNK + 1];
  const char recieved_msg[] = "-----------\nRecieved data: ";
  const char sent_msg[] = "-----------\nSent data: ";

  if (pipe(filedes) == -1)
  {
    perror("Pipe function call error");
    exit(EXIT_FAILURE);
  }

  pid_t pid = fork();
  if (pid == -1)
  {
    perror("Fork function call error.");
    exit(EXIT_FAILURE);
  }

  if (pid == 0)
  {
    close(filedes[1]);

    ssize_t output_descriptor = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, OPEN_MODE);

    if (output_descriptor == -1)
    {
      perror("Open function call error.\n");
      exit(EXIT_FAILURE);
    }

    while ((pipe_bytes_read = read(filedes[0], write_buffer, WRITE_CHUNK)))
    {
      if (pipe_bytes_read == -1)
      {
        perror("Read function call error");
        exit(EXIT_FAILURE);
      }
      if (pipe_bytes_read)
      {
        write(STDOUT_FILENO, &recieved_msg, strlen(recieved_msg));
        for (int i = 0; i < pipe_bytes_read; i++)
        {
          write(STDOUT_FILENO, &write_buffer[i], sizeof(char));
        }
        write(STDOUT_FILENO, "\n", sizeof(char));
      }
      if (!pipe_bytes_read)
      {
        sleep(random_sleep());
      }
      if (write(output_descriptor, write_buffer, pipe_bytes_read) == -1)
      {
        perror("Write function call error");
        exit(EXIT_FAILURE);
      }
    }
    close(output_descriptor);
    close(filedes[0]);
    exit(EXIT_SUCCESS);
  }

  close(filedes[0]);

  ssize_t input_descriptor = open(input_filename, O_RDONLY);

  if (input_descriptor == -1)
  {
    perror("Open function call error.");
    exit(EXIT_FAILURE);
  }
  while ((bytes_read = read(input_descriptor, read_buffer, READ_CHUNK)))
  {
    if (bytes_read == -1)
    {
      perror("Read function call error.");
      exit(EXIT_FAILURE);
    }
    if (bytes_read)
    {
      write(STDOUT_FILENO, &sent_msg, strlen(sent_msg));
      for (int i = 0; i < bytes_read; i++)
      {
        write(STDOUT_FILENO, &read_buffer[i], sizeof(char));
      }
      write(STDOUT_FILENO, "\n", sizeof(char));
    }
    if (write(filedes[1], read_buffer, bytes_read) == -1)
    {
      perror("Write pipe function call error");
      exit(EXIT_FAILURE);
    }
    sleep(random_sleep());
  }
  close(input_descriptor);
  close(filedes[1]);
  exit(EXIT_SUCCESS);
}