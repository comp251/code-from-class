#include <stdio.h>  // for print/scanf()
#include <stdlib.h> // for rand()

#define MAX_NUM 1000
#define ROUNDS 20

void playgame(char name[]) {
  int num = ((double)rand() / RAND_MAX) * MAX_NUM;
  int guess = -1;
  int count = 0;
  printf("Hello %s! I'm thinking of a number...\n", name);
  while (guess != num && count < ROUNDS) {
    printf("Enter your guess: ");
    scanf("%d", &guess);
    if (guess < num) {
      printf("Too low!\n");
    } else if (guess > num) {
      printf("Too high!\n");
    }
    count++;
  }
  if (guess == num) {
    printf("You win! It took you %d guesses to guess %d.\n", count, num);
  } else {
    printf("You lose! The number was %d. Get good, %s\n", num, name);
  }
}

int main(int argc, char *argv[]) {
  char name[256];
  char choice;

  printf("Enter your name: ");
  scanf("%s", name);

  do {
    playgame(name);
    printf("Do you want to play again? y/n: ");
    scanf(" %c", &choice);
  } while (choice == 'y');
  printf("goodbye!\n");

  return 0;
}
