#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  int mid = (high + low) / 2;
  int mid_value = f.invoke(mid);

  if (high == low + 1) {
    return low;
  }
  else if (mid_value <= 0) {
    return binarySearchForZero(f, mid, high);  
  }
  else {
    return binarySearchForZero(f, low, mid);
  }
  
  return low;
}
