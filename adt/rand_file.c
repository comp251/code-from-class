#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// $ gcc rand_file.c -o rand_file
// $ ./rand_file N FILENAME
// e.g.,
// $ ./rand_file 1024 nums.txt

double rand_d(double low, double high) {
  return (rand() / (double)RAND_MAX) * (high - low) + low;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: rand_file NUM FILENAME\n");
    return 1;
  }
  srand(time(NULL));
  int n = atoi(argv[1]);
  FILE *f = fopen(argv[2], "w");
  for (int i = 0; i < n; i++) {
    // temp,humidity,mR/h
    fprintf(f, "%lf,%lf,%lf\n", rand_d(20, 110), rand_d(40, 100),
            rand_d(100, 1000));
  }
  fclose(f);
}
