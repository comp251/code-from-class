#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

  char a[80] = "hello";
  char b[80] = "world";
  char c[80] = "";

  strncpy(c, a, 80);
  strncat(c, " ", 80);
  strncat(c, b, 80);
  printf("c: %s\n", c);

  return 0;
}
