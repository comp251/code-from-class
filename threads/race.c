#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  int tid;
  int iters;
  int *counter;
} thread_arg_t;

void *hello(void *arg) {
  thread_arg_t *t = arg;
  printf("[%d] starting...\n", t->tid);
  // increment count t->iters times.
  for (int i = 0; i < t->iters; i++) {
    *t->counter += 1;
  }
  printf("[%d] done...\n", t->tid);
  return NULL;
}

int main(int argc, char **argv) {
  int nthreads = atoi(argv[1]);
  int iters = atoi(argv[2]);
  srand(time(NULL));

  pthread_t *threads = malloc(sizeof(pthread_t) * nthreads);
  thread_arg_t *args = malloc(sizeof(thread_arg_t) * nthreads);

  printf("starting %d threads...\n", nthreads);

  int counter = 0;

  for (int i = 0; i < nthreads; i++) {
    // create thread arguments.
    args[i].tid = i;
    args[i].counter = &counter;
    args[i].iters = iters;

    // create thread.
    int ok = pthread_create(&threads[i], NULL, hello, &args[i]);
    if (ok) {
      perror("pthread_create");
      exit(1);
    }
  }

  printf("waiting for %d threads...\n", nthreads);

  for (int i = 0; i < nthreads; i++) {
    pthread_join(threads[i], NULL);
  }

  // print final count.
  printf("Final count: %d\n", counter);

  printf("done!\n");
  return 0;
}
