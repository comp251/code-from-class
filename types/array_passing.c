#include <stdio.h>

void f(int a) { a = 42; }

void print_arr(int arr[], int len) {
  printf("arr: ");
  for (int i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void modify_arr(int arr[], int len) {
  for (int i = 0; i < len; i++) {
    arr[i] = 42;
  }
  int my_bigger_arr[10];
  for (int i = 0; i < 10; i++) {
    my_bigger_arr[i] = 100;
  }
  arr = my_bigger_arr; // doesn't do what we expect!
}

// Not possible!
// int[] return_arr(int size) {
//   int arr[size];
//   return arr;
// }

int main(int argc, char **argv) {

  int a = 16;
  printf("a: %d\n", a);
  f(a);
  printf("a: %d\n", a);

  // int len;
  // printf("enter array length: ");
  // scanf("%d\n", &len);
  // int user_sized_arry[len]; // not ok to do!

  int arr[] = {5, 4, 3, 2, 1};
  print_arr(arr, 5);
  modify_arr(arr, 5);
  print_arr(arr, 5);

  return 0;
}
