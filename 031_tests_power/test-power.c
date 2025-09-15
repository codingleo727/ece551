#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

unsigned test_power(unsigned x, unsigned y) {
  int result = 1;
  if (y == 0) {
    return result;
  }

  for (int i = 0; i < y; i++) {
    result *= x;
  }
  return result;
}

void run_check(unsigned x, unsigned y) {
  unsigned broken_value = power(x, y);
  int correct_value = test_power(x, y);
  if (broken_value != correct_value) {
    printf("Broken: %d, Correct: %d\n", broken_value, correct_value);
    printf("x: %d, y: %d\n", x, y);
    exit(EXIT_FAILURE);
  }
}

int main() {
  for (int i = 0; i < 100; i++) {
    run_check(2, i);
    run_check(0, i);
    run_check(1, i);
    run_check(100, i);
  }

  return EXIT_SUCCESS;
}
