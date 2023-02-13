#include <stdio.h>
#include <string.h>

void print_all_chars(char *arr, int len) {
  printf("str chars: ");
  for (int i = 0; i < len; i++) {
    printf("%d ", i % 10);
  }
  printf("\n");
  printf("           ");
  for (int i = 0; i < len; i++) {
    printf("%c ", arr[i] > 0 ? arr[i] : '#');
  }
  printf("\n");
}

int main(int argc, char **argv) {
  char str[46] = "this is a string; it is an array of chars";

  printf("str = %s\n", str);
  print_all_chars(str, 46);

  char *substrings[50]; // array of 50 pointers to strings
  // this is the same as memset line below.
  for (int i = 0; i < 50; i++) {
    substrings[i] = NULL;
  }
  memset(substrings, 0, sizeof(char *) * 50); // clear 50*sizeof(char*) bytes
                                              // of memory, setting each
                                              // location to NULL.
  int count = 0;

  char *substring; // pointer to zero+ characters; string
  substring = strtok(str, " ");
  substrings[count] = substring;
  count++;
  while (substring != NULL) {
    substring = strtok(NULL, " "); // note that first arg needs to be NULL!
    substrings[count] = substring;
    count++;
  }
  print_all_chars(str, 46);

  printf("strings:\n");
  for (int i = 0; i < count; i++) {
    printf("%d: %s\n", i, substrings[i]);
  }

  // char *rest;
  // int len = strlen(substring); // strlen does not include the null terminator
  // rest = &str[len + 1];
  // printf("len: %d\n", len);
  // printf("rest: %s\n", rest);

  return 0;
}
