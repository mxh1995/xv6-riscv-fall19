#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

const char whitespace[] = " \t\r\n\v";

int
main(int argc, char *argv[])
{
  if(argc <= 1){
    fprintf(2, "usage: xargs command [initial-arguments...]\n");
    exit();
  }

  char *new_argv[MAXARG];
  for (int i = 0; i < argc - 1; i++)
    new_argv[i] = argv[i + 1];
  
  char s[256];
  while (gets(s, sizeof(s)) && *s)
  {
    char *p = s;
    int i;
    for (i = argc - 1; i < MAXARG; i++)
    {
      while (*p && strchr(whitespace, *p))
        p++;
      if (!*p)
        break;
      new_argv[i] = p;
      while (*p && !strchr(whitespace, *p))
        p++;
      if (*p)
      {
        *p = '\0';
        p++;
      }
    }
    while (i < MAXARG)
    {
      new_argv[i] = '\0';
      i++;
    }

    int pid = fork();
    if (pid == 0)
      exec(argv[1], new_argv);
    else if (pid > 0)
      wait();
    else
    {
      fprintf(2, "fork error\n");
      exit();
    }
  }
  exit();
}
