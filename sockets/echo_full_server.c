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
  // arg[1] - port to listen on
  if (argc < 2) {
    fprintf(stderr, "usage: %s PORT\n", argv[0]);
  }
  char *port = argv[1];

  int conn_fd = 0; // Our socket file descriptor; step 2 will initialize.

  // Step 1: fill out addrinfo struct.
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_INET;
  hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG | AI_PASSIVE;

  struct addrinfo *result;
  ok = getaddrinfo(NULL, port, &hints, &result);
  if (ok < 0) {
    perror("getaddrinfo");
  }

  // Step 2-3: create socket and attempt to bind to it.
  struct addrinfo *cur = result;
  while (cur) {
    // addrinfo is a linked list; we will try each address available to us.
    // We could fill this out manually, but using getaddrinfo is a best
    // practice.
    // Step 2: open a socket fd of the given type (INET, SOCK_STREAM, ...)
    conn_fd = socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol);
    if (conn_fd >= 0) {
      // socket valid, attempt to bind.
      int optval = 1;
      setsockopt(conn_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
                 sizeof(int));
      // Step 3: bind the address/port to the socket.
      ok = bind(conn_fd, cur->ai_addr, cur->ai_addrlen);
      if (ok == 0) {
        // bind succeeded
        break;
      }
      // bind failed; try next address.
      perror("bind");
      close(conn_fd);
      conn_fd = -1;
    }
    cur = cur->ai_next;
  }

  freeaddrinfo(result);
  if (conn_fd < 0) {
    fprintf(stderr, "could not bind a socket!\n");
    return 1;
  }

  // Step 4: Listen on the socket. Choose large queue depth.
  ok = listen(conn_fd, 1024);
  if (ok < 0) {
    perror("listen");
    close(conn_fd);
    return 1;
  }

  struct sockaddr_storage client;
  socklen_t client_len;
  while (1) {
    client_len = sizeof(client);
    // Step 5: Accept and handle connections!
    int client_conn = accept(conn_fd, (struct sockaddr *)&client, &client_len);

    // who connected to us?
    char client_name[1024];
    char client_port[1024];
    char buffer[1024];
    getnameinfo((struct sockaddr *)&client, client_len, client_name, 1024,
                client_port, 1024, 0);
    printf("Connection from %s:%s\n", client_name, client_port);

    // read from client util EOF
    while (uio_readline(buffer, 1024, client_conn) > 0) {
      printf("received > %s", buffer);
      // echo line back to client
      uio_write(buffer, strlen(buffer), client_conn);
    }
    close(client_conn);
    printf("disconnected\n");
  }

  return 0;
}
