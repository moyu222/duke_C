#include <stdio.h>
#include <stdlib.h>

int* aFunction(int x, int *p, int ** q) { // x = 1, *p: {7,8,9}, **q: 4
  printf("x = %d\n", x); // x = 1
  printf("*p = %d\n", *p); // *p = 7
  printf("**q= %d\n", **q); // **q= 4
  *p = 42; // {42, 8, 9}
  **q = 99; // {99, 5, 6}
  *q = &p[1]; // *(&p) = &(anArray[2][1])
  return &p[2]; // &(anArray[2][2])
}

int main (void) {
  int anArray[3][3] = { {1,2,3},
			{4,5,6},
			{7,8,9} };

  int * p = anArray[1]; // {4, 5, 6}
  int * q = aFunction(anArray[0][0],
		      anArray[2],
		      &p);
  for (int i =0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d\n", anArray[i][j]);
    }
  }
  printf("*q=%d\n", *q);

  return EXIT_SUCCESS;
}
