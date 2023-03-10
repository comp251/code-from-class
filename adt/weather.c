// weather.c

#include "weather.h"

struct weather measure(double temp_f, double humidity, double rads) {
  // declare, populate, and return struct.
  struct weather tmp;
  tmp.temp_f = temp_f;
  tmp.humidity = humidity;
  tmp.rads = rads;
  return tmp;
}

int compare(struct weather a, struct weather b) {
  // default to relation on rads.
  if (a.rads != b.rads) {
    return a.rads - b.rads;
  }
  if (a.temp_f != b.temp_f) {
    return a.temp_f - b.temp_f;
  }
  return a.humidity - b.humidity;
}
