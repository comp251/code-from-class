#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int a = 1;
void parent();
void child();

int main(int argc, char **argv) {

  pid_t pid = fork();
  printf("pid: %d\n", pid);
  if (pid != 0) {
    printf("Parent; child pid is %d\n", pid);
    parent();
  } else {
    printf("Child; returned pid is %d\n", pid);
    child();
  }

  return 0;
}

void parent() {
  for (int i = 0; i < 10; i++) {
    a--;
    printf("a = %d (%c)\n", a, 'p');
    sleep(1);
  }
}

void child() {
  for (int i = 0; i < 10; i++) {
    a++;
    printf("a = %d (%c)\n", a, 'c');
    sleep(1);
  }
}
