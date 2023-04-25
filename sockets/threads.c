#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_SLEEP_MSEC ((int)(50 * 1000))

void *hello(void *arg) {
  for (int i = 0; i < 10; i++) {
    // usleep(rand() % MAX_SLEEP_MSEC);
    printf("hello (%d)!\n", i);
  }
  return NULL;
}

int main(int argc, char **argv) {
  int nthreads = atoi(argv[1]);
  srand(time(NULL));

  pthread_t *threads = malloc(sizeof(pthread_t) * nthreads);

  printf("starting %d threads...\n", nthreads);

  for (int i = 0; i < nthreads; i++) {
    int ok = pthread_create(&threads[i], NULL, hello, NULL);
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
