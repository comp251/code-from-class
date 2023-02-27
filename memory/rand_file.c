#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// $ gcc rand_file.c -o rand_file
// $ ./rand_file N FILENAME
// e.g.,
// $ ./rand_file 1024 nums.txt

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: rand_file NUM FILENAME\n");
    return 1;
  }
  // srand(time(NULL));
  int n = atoi(argv[1]);
  FILE *f = fopen(argv[2], "w");
  for (int i = 0; i < n; i++) {
    fprintf(f, "%d\n", rand() - RAND_MAX / 2);
  }
  fclose(f);
}
