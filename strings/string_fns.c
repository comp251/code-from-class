#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

  char a[80] = "hello";
  char b[80] = "world";
  char c[80] = "";

  strncat(a, b, 80);
  printf("%s", a);

  return 0;
}
