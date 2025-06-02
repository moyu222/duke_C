#include <stddef.h>
size_t maxSeq(int * array, size_t n) {
  size_t len = 1;
  size_t maxlen = 1;
  if (array == NULL || n == 0) {
    return 0;
  }
  size_t start = 0;
  for (int i = start; i < n-1; i++) {
    if (array[i] < array[i+1]) {
      len += 1;
    } else {
      len = 1;
    }
    if (len > maxlen) {
      maxlen = len;
    }
  }
  return maxlen;
}
