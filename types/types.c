#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // integral types -- positive or negative
  char c;
  short s;
  int i;
  long l;
  long long ll; // (*)

  // unsigned integral types -- positive only
  unsigned char uc;
  unsigned short us;
  unsigned int ui;
  unsigned long ul;
  unsigned long long ull;

  // floating point types -- store real numbers (sci notification)
  float f;
  double d;
  long double ld; // (*)

  // pointer type -- store addresses
  void *v;

  // boolean type (*)
  bool b;

  // integral types
  printf("Size of char: %ld\n", sizeof(c));
  printf("Size of unsigned char: %ld\n", sizeof(uc));

  printf("Size of short: %ld\n", sizeof(s));
  printf("Size of unsigned short: %ld\n", sizeof(us));

  printf("Size of int: %ld\n", sizeof(i));
  printf("Size of unsigned int: %ld\n", sizeof(ui));

  printf("Size of long: %ld\n", sizeof(l));
  printf("Size of unsigned long: %ld\n", sizeof(ul));

  printf("Size of long long: %ld\n", sizeof(ll));
  printf("Size of unsigned long long: %ld\n", sizeof(ull));

  // floating point types
  printf("Size of float: %ld\n", sizeof(f));
  printf("Size of double: %ld\n", sizeof(d));
  printf("Size of long double: %ld\n", sizeof(ld));

  // pointer type
  printf("Size of pointer: %ld\n", sizeof(v));

  // boolean type
  printf("Size of boolean: %ld\n", sizeof(b));

  // C99 integer types (stdint.h)
  int8_t i8;
  uint8_t ui8;
  int16_t i16;
  uint16_t ui16;
  int32_t i32;
  uint32_t ui32;

  // Only available on 64-bit architectures.
  int64_t i64;
  uint64_t ui64;

  return 0;
}
