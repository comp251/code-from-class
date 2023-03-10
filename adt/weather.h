// ensure gcc only processes this file once
#ifndef __WEATHER_H__
#define __WEATHER_H__

// weather.h
// clang-format off
struct weather {
  double temp_f;
  double humidity;
  double rads;
};

// Given measurements, create and return
// a weather struct
struct weather measure(
    double temp_f,
    double humidity,
    double rads);

// Given two points, return:
// <0 if a < b
// =0 if a == b
// >0 if a > b
int compare(
    struct weather a,
    struct weather b);
// clang-format on

#endif
