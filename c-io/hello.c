#include <stdio.h> // printf and scanf

#define COUNTDOWN_START 5
#define NAME_LEN 256

void print_countdown(int n) {
  for (int i = n; i > 0; i--) {
    printf("%d\n", i);
  }
}

int main(int argc, char *argv[]) {
  int n = COUNTDOWN_START;
  int age;
  char fname[NAME_LEN];
  char lname[NAME_LEN];
  printf("Enter your first name, last name, and age separated by spaces: ");
  scanf("%s %s %d", fname, lname, &age);
  print_countdown(n);
  printf("Hello %s %s (you're %d years old)\n", fname, lname, age);
  return 0;
}
