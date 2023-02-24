#include <stdio.h>
#include <stdlib.h>

int *f() {
  int a = 5;
  return &a;
}

void g() {
  int b = 42;
  printf("b = %d\n", b);
}

int main() {
  int *c = f();
  printf("*c = %d\n", *c);
  g();
  printf("*c = %d\n", *c);
}
