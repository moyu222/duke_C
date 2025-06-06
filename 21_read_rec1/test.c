#include <stdio.h>
#include <stdlib.h>

void printDigits(int x) { // x = 297
  if (x == 0) {
    printf("0");
  }
  else if (x < 0) {
    printf("-");
    printDigits(-x);
  }
  else {
    int a = x/10;
    int b = x %10;
    printf("a=%d, b=%d\n",a,b); // a=29, b=7
    if (a != 0) {
      printDigits(a); // a=2, b=7 a=0, b=2 2
    }
    printf("%d",b);
  }
}


int main(void) {
  printDigits(297);
  printf("\n");
  return EXIT_SUCCESS;
}
