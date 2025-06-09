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
    char ** lines = realloc(lines, (i+1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, (i));
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    readAndSort(stdin);
  }
  else if (argc == 2) {
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
      perror("Can not open the file.\n");
      return EXIT_FAILURE;
    }
    readAndSort(f);
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
  } else {
    fprintf(stderr, "Expect 0 or 1 arguments.\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
