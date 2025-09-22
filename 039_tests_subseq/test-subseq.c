#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main() {
  int array[] = {2, 2, 2};
  if (maxSeq(array, 3) != 1) {
    return EXIT_FAILURE;
  }

  int array2[] = {-2, -6, -1, 0, 3};
  if (maxSeq(array2, 5) != 4) {
    return EXIT_FAILURE;
  }

  int array3[] = {-100, -30, -20, -10, -3};
  if (maxSeq(array3, 5) != 5) {
    return EXIT_FAILURE;
  }

  if (maxSeq(array3, 0) != 0) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
