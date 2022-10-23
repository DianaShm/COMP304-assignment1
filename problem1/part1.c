#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

int main(void) {
  pid_t pid = 0;
  pid = fork();
  struct timeval tv;
  time_t curtime;
  char buffer[30];
  if (pid == 0) {
    while (1) { //infinite loop
      sleep(1);
      gettimeofday(&tv, NULL); 
      curtime = tv.tv_sec;
      strftime(buffer, 30, "%m-%d-%Y  %T.", localtime(&curtime));
      pid = getpid();
      printf("time: %s%ld , pid: %d \n", buffer, tv.tv_usec, pid);
    } 
  } else {
    sleep(5);
    kill(pid, SIGKILL);
    printf("Child %d killed \n", pid);
  }
  return 0;
}