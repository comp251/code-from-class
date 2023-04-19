#include "conn.h"
#include "uio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LEN 2048

void usage(char *name) {
  printf("Usage: %s HOST PORT\n", name);
  exit(1);
}

int main(int argc, char **argv) {
  if (argc < 3) {
    usage(argv[0]);
  }

  int fd = conn_connect(argv[1], argv[2]);
  if (fd < 0) {
    fprintf(stderr, "Error connecting to %s:%s\n", argv[1], argv[2]);
    perror("connect");
    return 1;
  }
  char echo_buffer[MAX_LINE_LEN];
  printf("> ");
  while (fgets(echo_buffer, MAX_LINE_LEN, stdin) != NULL) {
    uio_write(echo_buffer, strlen(echo_buffer), fd);
    if (uio_readline(echo_buffer, MAX_LINE_LEN, fd) <= 0) {
      close(fd);
      break;
    }
    printf("echo: %s", echo_buffer);
    printf("> ");
  }
  return 0;
}
