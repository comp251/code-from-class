#include <stdio.h>

void f1(int);

void f3(int f3_arg) {
  int f3_local_int;
  printf("Address of %s: %p\n", "f3_arg", &f3_arg);
  printf("Address of %s: %p\n", "f3_local_int", &f3_local_int);
  f1(1);
}

void f2(int f2_arg1, int f2_arg2) {
  int f2_local_int;
  printf("f2 int: %d\n", f2_local_int);
  printf("Address of %s: %p\n", "f2_arg1", &f2_arg1);
  printf("Address of %s: %p\n", "f2_arg2", &f2_arg2);
  printf("Address of %s: %p\n", "f2_local_int", &f2_local_int);
  f3(1);
}

void f1(int f1_arg) {
  int f1_local_int = 42;
  char f1_local_char = 'z';
  printf("f1 int: %d\n", f1_local_int);
  printf("Address of %s: %p\n", "f1_arg", &f1_arg);
  printf("Address of %s: %p\n", "f1_local_int", &f1_local_int);
  printf("Address of %s: %p\n", "f1_local_char", &f1_local_char);
}

int main(int argc, char **argv, char **environ) {
  int main_local_int;
  long double main_local_ld;
  long main_local_long;
  printf("Address of %s: %p\n", "argc", &argc);
  printf("Address of %s: %p\n", "argv", &argv);
  printf("Address of %s: %p\n", "argv", &environ);
  printf("Address of %s: %p\n", "main_local_int", &main_local_int);
  printf("Address of %s: %p\n", "main_local_ld", &main_local_ld);
  printf("Address of %s: %p\n", "main_local_long", &main_local_long);
  f1(99);
  f2(1, 2);
}
