#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "weather.h"

// returns the worst moment from a series of temperature and humidity
// measurements.
//
// "worst" is definited as highest temperature and, in the case of two equal
// temperatures, highest humidity.
//
// Args:
//   n_measurements: length of measurements
//   temp: array of temperature measurements
//   humidity: array of humidity measurements
//   worst_temp (out): temp of worst measurement
//   worst_humidity (out): temp of worst humidity
//
// worst_temp and worst_humidity are unchanged if there are zero measurements.
//
// TODO: we still need to fix the code below that calls this function!
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

  double *temp = NULL;     // array of temps
  double *humidity = NULL; // array of humidity
  int n_read = 0;          // number of values read
  int size = 0;            // size of arrays

  char line[80];
  while (fgets(line, 80, f)) {
    if (n_read >= size) {
      // grow arrays if we have read too many values.
      size = size > 0 ? 2 * size : 1; // double the size
      temp = realloc(temp, sizeof(double) * size);
      humidity = realloc(humidity, sizeof(double) * size);
    }
    // parse line as two doubles.
    char *end = NULL;
    temp[n_read] = strtod(line, &end);
    humidity[n_read] = strtod(end + 1, &end);
    // strtod(end + 1, NULL); // for rads
    n_read++;
  }
  printf("Read %d measurements\n", n_read);

  // compute worst day
  double w_temp = 0.0;
  double w_humidity = 0.0;
  worst_measurement(n_read, temp, humidity, &w_temp, &w_humidity);
  printf("Worst day: (%lf ℉, %lf%%)\n", w_temp, w_humidity);

  free(temp);
  free(humidity);
}
