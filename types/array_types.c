#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // this array will ALWAYS be 5 elements long
  char chararr[] = {'h', 101, 108, 'l', 'o'};
  printf("chararr[] =");
  for (int i = 0; i < 5; i++) {
    printf(" %c", chararr[i]);
  }
  printf("\n");

  // this array will ALWAYS be 10 elements long
  int intarr[10];
  printf("Randomizing intarr...\n");
  for (int i = 0; i < 10; i++) {
    intarr[i] = rand();
  }

  printf("intarr[] =");
  for (int i = 0; i < 10; i++) {
    printf(" %d", intarr[i]);
    if (i < 9) {
      printf(",");
    } else {
      printf("\n");
    }
  }

  // this isn't ok -- how big is this?
  // int another[];

  // Strings are arrays of characters terminated by the null character (\0).
  char strarr[] = {'h', 'i', '\0', 't', 'h', 'e', 'r', 'e', '\0'};
  printf("strarr[] = ");
  for (int i = 0; i < 8; i++) {
    printf("%c ", strarr[i]);
  }
  printf("\n");
  // A pointer to zero or more characters can be treated like a string.
  char *s = &strarr[3];
  printf("strarr[] = %s\n", strarr);
  printf("s[] = %s\n", s);

  return 0;
}
