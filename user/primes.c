#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  int pipefd[2];
  if (pipe(pipefd))
  {
    fprintf(2, "error on pipe\n");
    exit();
  }

  int pid = fork();
  if (pid > 0)
  {
    close(pipefd[0]);
    for (int i = 2; i < 36; i++)
      write(pipefd[1], &i, sizeof(int));
    close(pipefd[1]);

    wait();
  }
  else if (pid == 0)
  {
    close(pipefd[1]);
    close(0);
    dup(pipefd[0]);
    close(pipefd[0]);

    while (1)
    {
      int prime;
      if (read(0, &prime, sizeof(int)))
        printf("prime %d\n", prime);
      else
        break;

      int pipefd2[2];
      pipe(pipefd2);

      int pid2 = fork();
      if (pid2)
      {
        close(pipefd2[0]);
        close(1);
        dup(pipefd2[1]);
        close(pipefd2[1]);
        int n;
        while (read(0, &n, sizeof(int)))
          if (n % prime)
            write(1, &n, sizeof(int));
              break;

        wait();
        break;
      }
      else
      {
        close(pipefd2[1]);
        close(0);
        dup(pipefd2[0]);
        close(pipefd2[0]);
      }
    }
  }
  else
    fprintf(2, "error on fork\n");
  
  exit();
}
