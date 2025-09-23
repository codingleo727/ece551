#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0)
    return 0;

  size_t max = 0;
  size_t store = 0;
  int * curr = array;
  for (size_t i = 0; i < n - 1; i++) {
    int left = *curr;
    int right = *(curr + 1);
    if (left < right) {
      store++;
    }
    else {
      if (store > max) {
        max = store;
      }
      store = 0;
    }
    curr++;
  }

  if (store > max) {
    return store + 1;
  }

  return max + 1;
}
