#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void freq_count(int * arr, FILE * f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      int index = c - 'a';
      arr[index]++;
    }
  }
}

int find_key(int * arr, int size) {
  int max = 0;
  int index = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
      index = i;
    }
  }
  return ((index - 4) >= 0) ? index - 4 : (index + 22)%26;

}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int fileLetterCount[26] = {0};
  freq_count(fileLetterCount, f);
  fclose(f);
  int ans = find_key(fileLetterCount, 26);
  printf("Decryption key: %d\n", ans);
  return EXIT_SUCCESS;
}
