#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x,y) != expected_ans) {
    printf("power(%u,%u) != %u", x, y, expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(2147483648, 1, 2147483648);
  run_check(0, 0, 1);
  run_check(0, 2, 0);
  run_check(3, 0, 1);
  run_check(3, 2, 9);
  exit(EXIT_SUCCESS);
}
