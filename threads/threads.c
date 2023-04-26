#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_SLEEP_MSEC ((int)(50 * 1000))

struct thread_args {
  int tid;    // thread id
  int niters; // number of iterations
};

void *hello(void *arg) {
  struct thread_args *t = arg;
  int niters = t->niters;
  int tid = t->tid;
  for (int i = 0; i < niters; i++) {
    usleep(rand() % MAX_SLEEP_MSEC);
    printf("hello from thread %d (%d)!\n", tid, i);
  }
  return NULL;
}

int main(int argc, char **argv) {
  int nthreads = atoi(argv[1]);
  int niters = atoi(argv[2]);
  srand(time(NULL));

  pthread_t *threads = malloc(sizeof(pthread_t) * nthreads);
  struct thread_args *args = malloc(sizeof(struct thread_args) * nthreads);

  printf("starting %d threads...\n", nthreads);

  for (int i = 0; i < nthreads; i++) {
    args[i].tid = i;
    args[i].niters = niters;
    int ok = pthread_create(&threads[i], NULL, hello, &args[i]);
    if (ok) {
      perror("pthread_create");
      exit(1);
    }
  }

  printf("hello from main!\n");

  printf("waiting for %d threads...\n", nthreads);

  for (int i = 0; i < nthreads; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("done!\n");
  return 0;
}
