#include "conn.h"
#include "uio.h"

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 2048

void usage(char *name) {
  printf("Usage: %s PORT\n", name);
  exit(1);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    usage(argv[0]);
  }

  int fd = conn_listen(argv[1]);
  if (fd < 0) {
    fprintf(stderr, "Error opening socket!\n");
    perror("listen");
    return 1;
  }

  struct sockaddr_storage client;
  socklen_t client_len;
  char client_name[MAX_NAME_LEN];
  char client_port[MAX_NAME_LEN];
  char echo_buffer[MAX_LINE_LEN];
  while (1) {
    client_len = sizeof(client);
    int conn = accept(fd, (struct sockaddr *)&client, &client_len);
    getnameinfo((struct sockaddr *)&client, client_len, client_name,
                MAX_NAME_LEN, client_port, MAX_NAME_LEN, 0);
    printf("Connection from %s:%s\n", client_name, client_port);
    while (uio_readline(echo_buffer, MAX_LINE_LEN, conn) > 0) {
      printf("> %s", echo_buffer);
      uio_write(echo_buffer, strlen(echo_buffer), conn);
    }
    close(conn);
    printf("Disconnected\n");
  }
}
