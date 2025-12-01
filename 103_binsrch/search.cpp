#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (high == low || high == low + 1) {
    return low;
  }

  int mid = (high + low) / 2;
  int mid_value = f->invoke(mid);

  if (mid_value == 0) {
    return mid;
  }
  else if (mid_value < 0) {
    return binarySearchForZero(f, mid, high);  
  }
  else {
    return binarySearchForZero(f, low, mid);
  }
  
  return low;
}
