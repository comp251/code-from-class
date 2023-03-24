#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"

#define BUFF_LEN 80

void usage() {
  printf("i n0 n1 ...  insert values into list\n"
         "g idx        get element at idx from the list\n"
         "f            free list\n"
         "p            print list\n");
}

int main(int argc, char **argv) {

  char input_buff[BUFF_LEN];
  char *input;
  char *tmp_s;
  int tmp_i;
  int ok, val;
  int count;
  ll_t *list = NULL;

  usage();
  printf("> ");
  // Read user input until EOF
  while (fgets(input_buff, BUFF_LEN, stdin) != NULL) {
    char action = input_buff[0];
    input_buff[strnlen(input_buff, BUFF_LEN) - 1] = '\0';
    input = input_buff + 2;
    switch (action) {
    case 'i':
      // Insert a sequence of numbers:
      // num1 num2 num3 ...
      count = 0;
      tmp_s = strtok(input, " ");
      while (tmp_s != NULL) {
        // parse
        tmp_i = atoi(tmp_s);
        printf("insert %d...\n", tmp_i);

        // insert
        list = ll_insert(list, tmp_i);

        // print resulting list
        printf("    - ");
        ll_print(list);

        tmp_s = strtok(NULL, " ");
        count++;
      }
      printf("inserted %d values\n", count);
      break;
    case 'g':
      // Get element from an index
      tmp_s = strtok(input, " ");
      tmp_i = atoi(tmp_s);
      printf("getting element at index %d\n", tmp_i);
      ok = ll_at(list, tmp_i, &val);
      if (!ok) {
        printf("index %d out of range\n", tmp_i);
      } else {
        printf("list[%d] -> %d\n", tmp_i, val);
      }
      break;
    case 'f':
      // Free list
      printf("freeing list...\n");
      ll_free(list);
      list = NULL;
      ll_print(list);
      break;
    case 'p':
      // Print list
      ll_print(list);
      break;
    case '?':
    default:
      usage();
    }
    printf("> ");
  }
  return 0;
}
