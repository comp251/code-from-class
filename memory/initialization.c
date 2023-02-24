#include <stdio.h>

void function_a() {
  int a;
  printf("a = %d\n", a);
  a = 4;
}

void function_b() {
  int b;
  printf("b = %d\n", b);
  b = 15;
}

void function_c() {
  char c;
  printf("c = %d\n", c);
  printf("c -> ");
  function_b();
  c = 2;
}

int main(int argc, char *argv[]) {
  printf("main -> ");
  function_a();
  printf("main -> ");
  function_b();
  printf("main -> ");
  function_a();
  printf("main -> ");
  function_c();
  printf("main -> ");
  function_b();
  printf("main -> ");
  function_c();
}
