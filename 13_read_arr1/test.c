#include <stdio.h>
#include <stdlib.h>


int main(void) {
  int anArray[] = {5,16,33,99};
  int * p = anArray;
  printf("*p = %d\n", *p); // *p = 5
  p++;
  printf("Now *p = %d\n", *p); // Now *p = 16
  int * q = &anArray[3]; // q -> 99
  int ** x = &q;
  **x = 12; // 5,16,33,12
  *x = p; // x -> q -> 16
  **x = 42; // 5, 42, 33, 12
  q[1] = 9;
  for (int i =0; i < 4; i++){
    printf("anArray[%d] = %d\n",i, anArray[i]);
  }
  return EXIT_SUCCESS;
}
