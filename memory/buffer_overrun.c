#include <stdio.h>
#include <stdlib.h>

// populates an array with a series of positive numbers, as entered by a user.
// returns the number of values entered into the array.
int enter_nums(int arr[]) {
  int input = 0;
  int i = 0;
  printf("enter a postivite number (zero to stop): ");
  scanf("%d", &input);
  while (input > 0) {
    arr[i] = input;
    i++;
    printf("enter a postivite number (zero to stop): ");
    scanf("%d", &input);
  }
  return i;
}

void print_arr(int arr[], int n) {
  printf("[");
  for (int i = 0; i < n; i++) {
    printf("%d%s", arr[i], i < n - 1 ? ", " : "");
  }
  printf("]\n");
}

int main(int argc, char **argv) {
  int arr[5];
  int n = enter_nums(arr);
  print_arr(arr, n);
}
