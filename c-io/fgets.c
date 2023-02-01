#include <stdio.h>  // for printf/fgets
#include <string.h> // for strlen

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
  char buffer[MAX_LINE];

  while (1) {
    char *ret = fgets(buffer, MAX_LINE, stdin);
    int len = 0;
    int olen = 0;
    if (ret != NULL) {
      // strip newline
      olen = strlen(buffer);
      buffer[olen - 1] = '\0';

      // length should be one shorter
      len = strlen(buffer);
      printf("[%d -> %d] - \"%s\"\n", olen, len, buffer);
    } else {
      printf("EOF\n");
      break;
    }
  }

  return 0;
}
