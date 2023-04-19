#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "uio.h"

int main(int argc, char **argv) {
  int ok;
  // arg[1] - host to connect to
  // arg[2] - port to connect to
  if (argc < 3) {
    fprintf(stderr, "usage: %s HOST PORT\n", argv[0]);
  }
  char *host = argv[1];
  char *port = argv[2];

  int conn_fd = 0; // Our socket file descriptor; step 2 will initialize.

  // Step 1: fill out addrinfo struct.
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_INET;
  hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;

  struct addrinfo *result;
  ok = getaddrinfo(NULL, port, &hints, &result);
  if (ok < 0) {
    perror("getaddrinfo");
  }

  // Step 2-3: create socket and attempt to connect to it.
  struct addrinfo *cur = result;
  while (cur) {
    // addrinfo is a linked list; we will try each address available to us.
    // We could fill this out manually, but using getaddrinfo is a best
    // practice.
    // Step 2: open a socket fd of the given type (INET, SOCK_STREAM, ...)
    conn_fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
    if (conn_fd >= 0) {
      // socket valid, attempt to connect.
      // Step 3: connect the address/port to the socket.
      ok = connect(conn_fd, cur->ai_addr, cur->ai_addrlen);
      if (ok == 0) {
        // connect succeeded
        break;
      }
      // connect failed; try next address.
      perror("connect");
      close(conn_fd);
      conn_fd = -1;
    }
    cur = cur->ai_next;
  }

  freeaddrinfo(result);
  if (conn_fd < 0) {
    fprintf(stderr, "could not connect a socket!\n");
    return 1;
  }

  // Step 4, use the socket!
  char buffer[1024];
  printf("send > ");
  while (fgets(buffer, 1024, stdin) != NULL) {
    // write to socket
    uio_write(buffer, strlen(buffer), conn_fd);
    // read from socket
    if (uio_readline(buffer, 1024, conn_fd) <= 0) {
      // disconnected
      close(conn_fd);
      break;
    }
    printf("recevied > %s", buffer);
    printf("send > ");
  }
  return 0;
}
