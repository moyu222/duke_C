#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void readAndSort(FILE * f) {
  char * curr = NULL;
  char ** lines = NULL;
  size_t sz = 0;
  size_t i = 0;
  while((getline(&curr, &sz, f)) >= 0) {
    char ** temp = realloc(lines, (i+1) * sizeof(*lines));
    if (temp == NULL) {
      perror("Memory allocation failed");
      free(lines);
      free(curr);
      return;
    }
    lines = temp;
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    readAndSort(stdin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE *f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Could not open file\n");
        return EXIT_FAILURE;
      }
      readAndSort(f);
      if (fclose(f) != 0) {
        fprintf(stderr, "Could not close file\n");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
