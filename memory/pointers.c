#include <stdio.h>

int main(int argc, char **argv) {
  int a = 42;    // int
  int *b = NULL; // pointer to int

  b = &a;

  *b = 16;

  int c = *b;

  *b = 32;

  b = &c;
  *b = 24;

  printf("a = %d\n", a);
  printf("*b = %d\n", *b);
  printf("c = %d\n", c);
  printf("b = %p\n", b);

  return 0;
}
