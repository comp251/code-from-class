#include <stdio.h>
#include <stdlib.h>

void print_arr(int *arr, int n);
void compute_metrics(int *arr, int n, double *mean, int *max, int *min,
                     long *sum);

#define INIT_BUFFER_SIZE 16

// we've written/used functions that have this kind of signature/contract:
//
//   int read_from(FILE *src, int arr[], int max_read)
//
// arr is allocated by the caller and filled in by the function. The function
// returns the number of elements it read, up to max_read.
//
// Below, we have the function allocate the necessary memory for _all_ elements
// from the array. This isn't necessarily "better" -- it is just a motivating
// example of allocating dynamic memory.

// returns an array of integers read from a source.
// n is an out-parameter: number of integers read.
int *read_from(FILE *src, int *n) {
  // int a[INIT_BUFFER_SIZE]; // declare array with a default size
  // int *arr =
  //     malloc(INIT_BUFFER_SIZE * sizeof(int)); // pointer to array to populate
  int *arr = NULL;  // pointer to array to populate
  int arr_size = 0; // current size of array

  int in;           // temp for reading
  int num_read = 0; // number of elements read so far

  // while not EOF; read and store in array
  while (fscanf(src, "%d", &in) > 0) {
    if (num_read >= arr_size) {
      // array must grow; read enough elements to fill it.
      // if (arr_size > 0) {
      //   arr_size = arr_size * 2;
      // } else {
      //   arr_size = 1;
      // }
      // this is equivalent to the if statement above...
      printf("growing array (%d ->", arr_size);
      arr_size = arr_size > 0 ? arr_size * 2 : 1;
      arr = realloc(arr, arr_size * sizeof(int));
      printf(" %d)\n", arr_size);
    }
    arr[num_read] = in;
    num_read++;
  }
  perror("fscanf");

  *n = num_read;
  return arr;
}

int main(int argc, char **argv) {
  FILE *in = stdin;
  if (argc > 1) {
    in = fopen(argv[1], "r");
    if (!in) {
      perror("fopen");
      exit(1);
    }
    printf("Reading from %s\n", argv[1]);
  } else {
    printf("Reading from stdin\n");
  }

  int *arr = NULL;
  int n_read = 0;
  arr = read_from(in, &n_read);
  // n_read will be number of elements read.

  // print_arr(arr, n_read);
  int min, max;
  long sum;
  double mean;

  compute_metrics(arr, n_read, &mean, &max, &min, &sum);
  printf("count: %d\nsum: %ld\nmin: %d\nmax: %d\nmean %0.2f\n", n_read, sum,
         min, max, mean);
  // free array -- return memory to be reused.
  free(arr);
}

// Pretty-print an array.
void print_arr(int *arr, int n) {
  printf("[");
  for (int i = 0; i < n; i++) {
    printf("%d%s", arr[i], i < n - 1 ? ", " : "");
  }
  printf("]\n");
}

// Compute some metrics over an array with the given size.
// mean, max, min, and sum are out parameters.
void compute_metrics(int *arr, int n, double *mean, int *max, int *min,
                     long *sum) {
  if (n < 1) {
    return;
  }
  *mean = 0.0;
  *max = arr[0];
  *min = arr[0];
  *sum = 0;
  for (int i = 0; i < n; i++) {
    *sum += arr[i];
    if (arr[i] > *max) {
      *max = arr[i];
    }
    if (arr[i] < *min) {
      *min = arr[i];
    }
  }
  *mean = *sum / (double)n;
}
