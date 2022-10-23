#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

int main(void) {
  int child = 0;
  struct timeval tv;
  time_t curtime;
  char buffer[30];
  pid_t pid[4];
  int i;
  for (i = 0; i < 4; ++i) {
    pid[i] = fork();
    if (pid[i] == 0) {
      child = 1;
      break;
    }
  }

  if (child) {
    while (1) { //infinite loop
      sleep(1);
      gettimeofday(&tv, NULL); 
      curtime = tv.tv_sec;
      strftime(buffer, 30, "%m-%d-%Y  %T.", localtime(&curtime));
      pid[0] = getpid();
      printf("time: %s%ld , pid: %d \n", buffer, tv.tv_usec, pid[0]);
    } 
  } else {
    sleep(5);
    for (i = 0; i < 4; ++i) {
      kill(pid[i], SIGKILL);
      printf("Child %d killed \n", pid[i]);
    }
  }
  return 0;
}