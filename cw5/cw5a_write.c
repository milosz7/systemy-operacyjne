#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define REQUIRED_ARGS_AMOUNT 3
#define WRITE_CHUNK 7
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

  char buffer[WRITE_CHUNK + 1];
  char *output_filename = argv[1];
  char *pipe_path = argv[2];
  const char recieved_msg[] = "-----\nRecieved data: ";
  ssize_t bytes_read;

  ssize_t pipedes_read = open(pipe_path, O_RDONLY, OPEN_MODE);
  ssize_t output_descriptor = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, OPEN_MODE);
  if (pipedes_read == -1 || output_descriptor == -1)
  {
    perror("Open function call error");
    exit(EXIT_FAILURE);
  }

  while ((bytes_read = read(pipedes_read, buffer, WRITE_CHUNK)))
  {
    if (bytes_read == -1)
    {
      perror("Read function call error");
      exit(EXIT_FAILURE);
    }
    if (write(output_descriptor, buffer, bytes_read) == -1)
    {
      perror("Write pipe function call error.");
      exit(EXIT_FAILURE);
    }
    if (bytes_read)
    {
      write(STDOUT_FILENO, &recieved_msg, strlen(recieved_msg));
      for (int i = 0; i < bytes_read; i++)
      {
        write(STDOUT_FILENO, &buffer[i], sizeof(char));
      }
      write(STDOUT_FILENO, "\n", sizeof(char));
    }
    if (!bytes_read)
    {
      sleep(random_sleep());
    }
  }
  close(output_descriptor);
  close(pipedes_read);
  exit(EXIT_SUCCESS);
}
