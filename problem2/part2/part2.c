#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void) {
// FIFO file path
  char* myfifo1 = "/tmp/myfifo1";
  char* myfifo2 = "/tmp/myfifo2";
  // Creating the named file(FIFO)
  int fd1, fd2;
  pid_t pid[2];
  int i;
  int x;
  int child = 0;
  pid_t cpid;
  int result;
  int a, b;
  mkfifo(myfifo1, 0666);
  mkfifo(myfifo2, 0666);
  for (i = 0; i < 2; ++i) {
    pid[i] = fork();
    sleep(5);
    if (pid[i] == 0) {
      child = i + 1;
      break;
    }
  }
  cpid = getpid();
  if (!child) {
    fd1 = open(myfifo1, O_RDWR);
    fd2 = open(myfifo2, O_RDWR);
    scanf("%d", &x); // reads an integer from standard input to x;
    sleep(5);
    write(fd1, &x, sizeof(int));
    sleep(5);
    write(fd2, &x, sizeof(int));
    sleep(5);
    read(fd1, &a, sizeof(int));
    sleep(5);
    read(fd2, &b, sizeof(int));
    sleep(5);
    printf("The final sum: %d \n", a + b);
    sleep(5);
    kill(pid[0], SIGTERM);
    sleep(5);
    kill(pid[1], SIGTERM);
    close(fd1); close(fd2);
  } else {
    fd1 = child == 1 ? open(myfifo1, O_RDWR) : open(myfifo2, O_RDWR);
    sleep(5);
    read(fd1, &x, sizeof(int));
    sleep(5);
    if (child == 1) {
      result = cpid * x;
      printf("First Child: Input %d, Output %d \n", x, result);
    } else {
      result = cpid / x;
      printf("Second Child: Input %d, Output %d \n", x, result);
    }
    sleep(5);
    write(fd1, &result, sizeof(int));
    sleep(5);
    close(fd1);
  }
  return 0;
}