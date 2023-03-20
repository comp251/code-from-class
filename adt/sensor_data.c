#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "weather.h"

// returns the worst moment from a series of temperature and humidity
// measurements.
struct weather worst_measurement(struct weather *arr, int size) {
  struct weather worst = arr[0];
  for (int i = 0; i < size; i++) {
    if (compare(worst, arr[i]) < 0) {
      worst = arr[i];
    }
  }
  return worst;
}

int main(int argc, char **argv) {
  // read file specified as first command-line argument
  FILE *f = fopen(argv[1], "r");
  if (!f) {
    perror("fopen");
  }

  struct weather *measurements = NULL; // array of measurements
  int n_read = 0;                      // number of values read
  int size = 0;                        // size of arrays
  double temp, humidity, rads;

  char line[80];
  while (fgets(line, 80, f)) {
    if (n_read >= size) {
      // grow arrays if we have read too many values.
      size = size > 0 ? 2 * size : 1; // double the size
      measurements = realloc(measurements, sizeof(struct weather) * size);
    }
    // parse line as two doubles.
    char *end = NULL;
    temp = strtod(line, &end);
    humidity = strtod(end + 1, &end);
    rads = strtod(end + 1, NULL); // for rads
    measurements[n_read] = measure(temp, humidity, rads);
    n_read++;
  }
  printf("Read %d measurements\n", n_read);

  // compute worst day
  struct weather worst = worst_measurement(measurements, n_read);
  printf("Worst day: %lf ℉, %lf%% %lf rads\n", worst.temp_f, worst.humidity,
         worst.rads);

  free(measurements);
}
