#include "conn.h"
#include "uio.h"

#include <netdb.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// This program contains numerous vulnerabilities! Let's try to find some.

#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 2048
#define MAX_TOPICS 20

void usage(char *name) {
  printf("Usage: %s PORT\n", name);
  exit(1);
}

typedef struct topics {
  int n_topics;
  int topic_cap;
  char **topics;
  int *votes;
} topics_t;

typedef struct {
  int clientfd;
  topics_t *topics;
  struct sockaddr *client;
  socklen_t *client_len;
} client_fn_args_t;

void *handle_client(void *arg) {
  client_fn_args_t *t = arg;
  int clientfd = t->clientfd;
  topics_t *topics = t->topics;
  struct sockaddr *client = t->client;
  socklen_t client_len = *t->client_len;

  char buffer[MAX_LINE_LEN];
  char client_name[MAX_NAME_LEN];
  char client_port[MAX_NAME_LEN];
  getnameinfo(client, client_len, client_name, MAX_NAME_LEN, client_port,
              MAX_NAME_LEN, 0);

  printf("Connection from %s:%s\n", client_name, client_port);

  while (uio_readline(buffer, MAX_LINE_LEN, clientfd) > 0) {
    buffer[strchr(buffer, '\n') - buffer] = '\0';
    if (strncmp(buffer, "add", 3) == 0) {
      // add a new topic
      if (topics->n_topics >= topics->topic_cap) {
        // too many topics
        char *str = "error: too many topics\n";
        uio_write(str, strlen(str), clientfd);
        continue;
      }
      // copy input buffer to new string, add as topic
      char *topic = strchr(buffer, ' ');
      topics->topics[topics->n_topics] = malloc(strlen(topic) + 1);
      strcpy(topics->topics[topics->n_topics], topic);
      topics->votes[topics->n_topics] = 0;
      topics->n_topics++;
      char *str = "ok\n";
      uio_write(str, strlen(str), clientfd);
    } else if (strncmp(buffer, "get", 3) == 0) {
      // retrieve topic and vote counts
      sprintf(buffer, "%d\n", topics->n_topics);
      uio_write(buffer, strlen(buffer), clientfd);
      for (int i = 0; i < topics->n_topics; i++) {
        sprintf(buffer, "(%d) %s\n", topics->votes[i], topics->topics[i]);
        uio_write(buffer, strlen(buffer), clientfd);
      }
    } else if (strncmp(buffer, "vote", 4) == 0) {
      // vote -- up or down
      char *dir_start = strchr(buffer, ' ') + 1;
      int dir = atoi(dir_start) > 0 ? 1 : -1;
      char *topic_start = strchr(dir_start, ' ') + 1;
      int topic = atoi(topic_start);
      if (topic >= topics->n_topics) {
        // invalid topic
        char *str = "error: invalid topic\n";
        uio_write(str, strlen(str), clientfd);
        continue;
      }
      topics->votes[topic] += dir;
      sprintf(buffer, "ok %d\n", topics->votes[topic]);
      uio_write(buffer, strlen(buffer), clientfd);
    } else {
      // invalid command
      char *str = "error: invalid command\n";
      uio_write(str, strlen(str), clientfd);
    }
  }
  close(clientfd);
  printf("%s:%s disconnected\n", client_name, client_port);
  free(t->client_len);
  free(t->client);
  free(arg); // clean up after ourselves.
  return NULL;
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

  printf("Listening on %s\n", argv[1]);

  topics_t *topics = malloc(sizeof(topics_t));
  topics->n_topics = 0;
  topics->topic_cap = MAX_TOPICS;
  topics->topics = malloc(MAX_TOPICS * sizeof(char *));
  topics->votes = calloc(MAX_TOPICS, sizeof(int));

  while (1) {
    struct sockaddr_storage *client = malloc(sizeof(struct sockaddr_storage));
    socklen_t *client_len = malloc(sizeof(socklen_t));
    *client_len = sizeof(*client);
    int conn = accept(fd, (struct sockaddr *)client, client_len);
    // fork:
    //  - parent call accept again
    //  - child handle the client connection; after client disconnects, child
    //    "expires"
    // multiplexing:
    //  - try doing IO with each client in round-robin fashion
    // or...
    //  - use threads!
    client_fn_args_t *args = malloc(sizeof(client_fn_args_t));
    args->clientfd = conn;
    args->topics = topics;
    args->client = (struct sockaddr *)&client; // this is a bug... <-- a lie.
    args->client_len = client_len;
    // handle_client(args);
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, handle_client, args);
    pthread_detach(thread_id);
  }

  // don't bother freeing topics.
}
