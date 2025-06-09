#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char matrix[10][10]) {
  char copy[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      copy[i][j] = matrix[i][j];
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[j][9 - i] = copy[i][j];
    }
  }
}

int main (int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix input\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  char matrix[10][10];
  int ch;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ch = fgetc(f);
      if (ch == '\n' || ch == EOF) {
        fprintf(stderr, "Invalid input: Line is too short.\n");
        return EXIT_FAILURE;
      }
      matrix[i][j] = ch;
    }
    ch = fgetc(f);
    if (ch != '\n' && ch != EOF) {
      fprintf(stderr, "Invalid input: Line is too long.\n");
      return EXIT_FAILURE;
    }
  }
  if ((ch = fgetc(f)) != EOF) {
    fprintf(stderr, "Invalid input: file is too long (read %d instead of EOF)", ch);
    return EXIT_FAILURE;
  }

  rotate(matrix);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }

  if (fclose(f) != 0) {
    perror("File close error.");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
