#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int time = uptime() / 10;
  char* unit;
  if (time < 60)
    unit = "second";
  else
  {
    time /= 60;
    if (time < 60)
      unit = "minute";
    else
    {
      time /= 60;
      if (time < 24)
	unit = "hour";
      else
      {
        time /= 24;
	unit = "day";
      }
    }
  }
  printf("up %d %s\n", time, unit);
  exit();
}
