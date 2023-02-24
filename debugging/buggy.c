#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 80
#define MAX_LINE 800

void tokenize(char *input, char *words[], int maxlen);

void reverse_words(char *words[]) {
  // compute length of words; swap words[i] with words[length-1-i]
  // MY BUG!
  // int wordslen = strnlen(words[0], MAX_LINE);
  int wordslen = 0;
  while (words[wordslen] != NULL) {
    wordslen++;
  }
  printf("wordslen = %d\n", wordslen);
  for (int i = 0; i < wordslen; i++) {
    printf("words[%d]: %s\n", i, words[i]);
    words[i] = words[wordslen - 1 - i];
    words[wordslen - 1 - i] = words[i];
  }
}

int main(int argc, char **argv) {
  char *words[MAX_WORDS];
  char input_buffer[MAX_LINE];
  // read a line
  printf("string? > ");
  char *ret = fgets(input_buffer, MAX_LINE, stdin);
  while (ret != NULL) {
    // while we have input, tokenize the line and then reverse the individual
    // words
    tokenize(input_buffer, words, MAX_WORDS);
    reverse_words(words);
    // print the reversed words
    printf("reversed: ");
    for (int i = 0; words[i] != NULL; i++) {
      printf("%s ", words[i]);
    }
    printf("\n");
    // read next line
    printf("string? > ");
    ret = fgets(input_buffer, MAX_LINE, stdin);
  }
}

void tokenize(char input[], char *words[], int maxlen) {
  memset(words, 0, sizeof(char *) * maxlen);
  int c = 0;
  words[c] = strtok(input, " ");
  while (words[c] != NULL && c < maxlen) {
    c++;
    words[c] = strtok(NULL, " ");
  }
  words[maxlen - 1] = NULL;
}
