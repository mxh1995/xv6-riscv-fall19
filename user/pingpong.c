#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  int parent_fd[2];
  int child_fd[2];
  if (pipe(parent_fd) || pipe(child_fd))
  {
    fprintf(2, "error on pipe\n");
    exit();
  }

  char buf;

  int pid = fork();
  if (pid == 0)
  {
    close(parent_fd[1]);
    close(child_fd[0]);
    read(parent_fd[0], &buf, 1);
    close(parent_fd[0]);
    printf("%d: received ping\n", getpid());
    write(child_fd[1], "world!", 6);
    close(child_fd[1]);
  }
  else if (pid > 0)
  {
    close(parent_fd[0]);
    close(child_fd[1]);
    write(parent_fd[1], "hello,", 6);
    close(parent_fd[1]);
    read(child_fd[0], &buf, 1);
    close(child_fd[0]);
    printf("%d: received pong\n", getpid());
  }
  else
  {
    fprintf(2, "error on fork\n");
    exit();
  }

  exit();
}
