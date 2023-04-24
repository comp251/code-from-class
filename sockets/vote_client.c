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
  char buffer[MAX_LINE_LEN];
  printf("Valid commands:\n");
  printf("\tadd <text>\n");
  printf("\tget\n");
  printf("\tvote <dir> <topic>\n");
  printf("> ");
  while (fgets(buffer, MAX_LINE_LEN, stdin) != NULL) {
    uio_write(buffer, strlen(buffer), fd);
    if (uio_readline(buffer, MAX_LINE_LEN, fd) <= 0) {
      close(fd);
      break;
    }
    printf("%s", buffer);
    int maybe_vals = atoi(buffer);
    for (int i = 0; i < maybe_vals; i++) {
      uio_readline(buffer, MAX_LINE_LEN, fd);
      printf("%d > %s", i, buffer);
    }
    printf("> ");
  }
  return 0;
}
